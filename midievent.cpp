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

QDataStream &operator >>(QDataStream &stream,MidiEvent &track){
    qint32 time = 0;
    quint32 i;
    //read time
    time = MidiEvent::readVariableLengthQuantity(&stream);
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
        stream >> byte;//type
        eventDataSize = MidiEvent::readVariableLengthQuantity(&stream);
        for (i = 0; i < eventDataSize; i++){
            stream >> byte;
            message.push_back(byte);
        }
        break;
    default:
        break;
    }
    track.setMessage(message);
    return stream;
}

qint32 MidiEvent::readVariableLengthQuantity(QDataStream *stream){
    qint32 value = 0;
    qint8 byte;
    do{
        (*stream) >> byte;
        value = (value << 7) + (byte & 0b01111111);

    }while (byte & 0b10000000 != 0);
    return value;
}
