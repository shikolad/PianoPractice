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
