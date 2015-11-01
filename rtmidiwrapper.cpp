#include "rtmidiwrapper.h"
#include <QDebug>

RTMidiWrapper::RTMidiWrapper(QObject *parent) : QObject(parent)
{
    midiInputDevice = NULL;
    midiOutputDevice = NULL;
    try{
        midiInputDevice = new RtMidiIn();
        midiOutputDevice = new RtMidiOut();
    }catch(RtMidiError &error){
//todo hadle error
    }

    activeInput = activeOutput = -1;
}

RTMidiWrapper::~RTMidiWrapper()
{

}

void RTMidiWrapper::updateDeviceList(){
    emit updateDeviceList(getInputDeviceList(),getOutputDeviceList());
}

QStringList RTMidiWrapper::getInputDeviceList(){
    quint32 inputDeviceCount = midiInputDevice->getPortCount();
    QStringList result;

    for (quint32 i = 0; i < inputDeviceCount; i++){
        try {
            result << QString(midiInputDevice->getPortName(i).data());
        }catch(RtMidiError &error) {
//todo hadle error
        }
    }
    return result;
}

QStringList RTMidiWrapper::getOutputDeviceList(){
    quint32 outputDeviceCount = midiOutputDevice->getPortCount();
    QStringList result;

    for (quint32 i = 0; i < outputDeviceCount; i++){
        try {
            result << QString(midiOutputDevice->getPortName(i).data());
        }catch(RtMidiError &error){
//todo hadle error
        }
    }
    return result;
}

void RTMidiWrapper::setActiveDevices(qint32 input, qint32 output){
    try {
        if (input != activeInput){
            if (activeInput != -1)
                midiInputDevice->closePort();
            if (input != -1){
                midiInputDevice->openPort(input);
                midiInputDevice->setCallback(&RTMidiWrapper::midiInputCallback,(void*)this);
            }
            activeInput = input;
        }
        if (output != activeOutput){
            if (activeOutput != -1)
                midiOutputDevice->closePort();
            if (output != -1){
                midiOutputDevice->openPort(output);
            }
            activeOutput = output;
        }
    }catch (RtMidiError &error) {
//todo handle error
    }
}

void RTMidiWrapper::sendMidiEvent(std::vector<quint8> message){
    if (midiOutputDevice != NULL)
        midiOutputDevice->sendMessage(&message);
}

void RTMidiWrapper::sendMidiEvent(std::vector<unsigned char> *message){
    if (midiOutputDevice)
        midiOutputDevice->sendMessage(message);
}

void RTMidiWrapper::midiInputCallback(double deltatime, std::vector< unsigned char > *message, void *userData){
    if (userData == NULL)
        return;
    RTMidiWrapper *wrapper = (RTMidiWrapper*)userData;
    wrapper->sendMidiEvent(message);
    qDebug() << "input message" << QString((const char*)message->data());
}
