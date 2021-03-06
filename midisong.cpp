#include "midisong.h"
#include <QFile>
#include <QDataStream>

MidiSong::MidiSong(QObject *parent) : QObject(parent)
{

}

MidiSong::~MidiSong()
{

}

void MidiSong::addTrack(MidiTrack *track){
    trackList.append(track);
}

MidiSong *MidiSong::loadFromFile(QString filePath){
    QFile file;
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly)){
        return NULL;
        //todo handle error
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    //header chunk reading
    const int headerMagic = 0x4d546864;//"MThd" string

    quint32 file_magic;
    stream >> file_magic;

    if (headerMagic != file_magic){
        //todo not a midi file
    }


    quint32 headerSize;
    stream >> headerSize;

    if (headerSize != 6){
        //todo non standart midi file
    }

    qint16 format, trackNumber, division;

    stream >> format;
    stream >> trackNumber;
    stream >> division;

    MidiSong *song = new MidiSong();

    while (!stream.atEnd()){
        MidiTrack *track = new MidiTrack(song);
        stream >> (*track);
        song->addTrack(track);
    }

    file.close();

    return song;
}

QList<MidiEvent*> MidiSong::getMidiEvents(qint32 time){
    QList<MidiEvent*> result;
    foreach (MidiTrack *track, trackList) {
        QList<MidiEvent*> events = track->getEvents(time);
        foreach (MidiEvent *ev, events) {
            result.push_front(ev);
        }
    }
    return result;
}

qint32 MidiSong::getNextDelta(qint32 time){
    qint32 nextDelta = -1;
    if (!trackList.isEmpty()){
        QVector<MidiTrack*>::iterator iterator = trackList.begin() + 1;
        nextDelta = (*iterator)->getNextDelta(time);
        iterator++;
        while (iterator != trackList.end()) {
            qint32 tmp = (*iterator)->getNextDelta(time);
            if ((tmp < nextDelta) && (tmp != -1))
                nextDelta = tmp;
        }
    }
    return nextDelta;
}
