#include "miditrack.h"

MidiTrack::MidiTrack(QObject *parent) : QObject(parent)
{

}

MidiTrack::~MidiTrack()
{

}

QDataStream &operator >>(QDataStream &stream,MidiTrack &track){

    //track chunks reading
    const quint32 trackMagic = 0x4d54726b;//"MTrk" string
    quint32 file_magic;

    stream >> file_magic;
    if (file_magic != trackMagic){
        //todo error reading file!!!
    }
    quint32 trackLength;
    stream >> trackLength;
    trackLength++;
    return stream;
}
