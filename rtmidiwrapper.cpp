#include "rtmidiwrapper.h"

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
