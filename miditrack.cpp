#include "miditrack.h"
#include <QDebug>

MidiTrack::MidiTrack(QObject *parent) : QObject(parent)
{
}

MidiTrack::~MidiTrack()
{

}

void MidiTrack::addEvent(MidiEvent *event){
    events.append(event);
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

    quint64 trackStart = stream.device()->pos();

    qint32 time = 0;
    while (stream.device()->pos() - trackStart < trackLength){
        qDebug() << stream.device()->pos();
        MidiEvent *event = new MidiEvent(&track);
        stream >> (*event);
        time += event->getDeltaTime();
        event->setTime(time);
        track.addEvent(event);
    }

    return stream;
}

QList<MidiEvent *> MidiTrack::getEvents(qint32 time){
    QList<MidiEvent*> result;
    foreach (MidiEvent *event, events) {
        if (event->getTime() > time){
            break;
        } else if (event->getTime() == time){
            result.push_front(event);
        }

    }
    return result;
}

qint32 MidiTrack::getNextDelta(qint32 time){
    foreach (MidiEvent *event, events) {
        if (event->getTime() > time){
            return event->getDeltaTime();
        }
    }
    return -1;
}
