#include "midievent.h"

MidiEvent::MidiEvent(QObject *parent) : QObject(parent)
{

}

MidiEvent::~MidiEvent()
{

}

void MidiEvent::setMessage(std::vector<unsigned char> &newMessage){
    message = newMessage;
}

void MidiEvent::setDeltaTime(qint32 newDelta){
    deltaTime = newDelta;
}

void MidiEvent::setTime(qint32 newTime){
    time = newTime;
}

void MidiEvent::setType(MidiEventType newType){
    type = newType;
}

qint32 MidiEvent::getDeltaTime(){
    return deltaTime;
}

qint32 MidiEvent::getTime(){
    return time;
}

MidiEvent::MidiEventType MidiEvent::getType(){
    return type;
}

std::vector<unsigned char>  MidiEvent::getMessage(){
    return message;
}

QDataStream &operator >>(QDataStream &stream,MidiEvent &track){
    qint32 dTime = 0;
    quint32 i;
    //read time
    dTime = MidiEvent::readVariableLengthQuantity(&stream);
    //read event
    quint32 eventDataSize;
    quint8 byte;
    stream >> byte;
    std::vector<unsigned char> message;
    bool add_0xF7_to_end = false;
    switch (byte){
    case 0xF0:
        add_0xF7_to_end = true;
    case 0xF7:
        track.setType(MidiEvent::SYSEX);
        eventDataSize = MidiEvent::readVariableLengthQuantity(&stream);
        message.push_back(byte);
        for (i = 0; i < eventDataSize; i++){
            stream >> byte;
            message.push_back(byte);
        }
        if (add_0xF7_to_end && (byte != 0xF7))
            message.push_back(0xF7);
        break;
    case 0xFF:
        track.setType(MidiEvent::META);
        stream >> byte;//type
        eventDataSize = MidiEvent::readVariableLengthQuantity(&stream);//data length
        for (i = 0; i < eventDataSize; i++){//data
            stream >> byte;
            message.push_back(byte);
        }
        break;
    default:
        track.setType(MidiEvent::MIDI);
        if ((byte >= 0xC0) && (byte <= 0xDF)){//2 byte midi event
            message.push_back(byte);
            stream >> byte;
            message.push_back(byte);
        }else if ((byte >= 0x80) && (byte <= 0xEF)){//3 byte midi event
            message.push_back(byte);
            stream >> byte;
            message.push_back(byte);
            stream >> byte;
            message.push_back(byte);
        }else {//short notation
            message.push_back(byte);
            stream >> byte;
            message.push_back(byte);
        }
        break;
    }

    track.setMessage(message);
    track.setDeltaTime(dTime);

    return stream;
}

qint32 MidiEvent::readVariableLengthQuantity(QDataStream *stream){
    qint32 value = 0;
    qint8 byte;
    do{
        (*stream) >> byte;
        value = (value << 7) + (byte & 0b01111111);

    }while ((byte & 0b10000000) != 0);
    return value;
}

quint8 MidiEvent::getFirstByte(){
    Q_ASSERT(type == MidiEvent::MIDI);
    return message[0];
}
