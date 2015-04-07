#include "miditrack.h"
#include <QDebug>

MidiTrack::MidiTrack(QObject *parent) : QObject(parent)
{

}

MidiTrack::~MidiTrack()
{

}

void MidiTrack::addEvent(MidiEvent *event){
    //todo add event
}

QDataStream &operator >>(QDataStream &stream,MidiTrack &track){

    //track chunks reading
    quint64 trackStart = stream.device()->pos();
    const quint32 trackMagic = 0x4d54726b;//"MTrk" string
    quint32 file_magic;


    stream >> file_magic;
    if (file_magic != trackMagic){
        //todo error reading file!!!
    }
    quint32 trackLength;
    stream >> trackLength;



    while (stream.device()->pos() - trackStart < trackLength){
        qDebug() << stream.device()->pos();
        MidiEvent *event = new MidiEvent(&track);
        stream >> (*event);
        track.addEvent(event);
    }

    return stream;
}
