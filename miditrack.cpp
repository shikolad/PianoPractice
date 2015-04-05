#include "miditrack.h"

MidiTrack::MidiTrack(QObject *parent) : QObject(parent)
{

}

MidiTrack::~MidiTrack()
{

}

MidiTrack *MidiTrack::loadFromFile(QString filePath){
    QFile file;
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly)){
        return new MidiTrack();
        //todo handle error
    }

    const qint32 magic = 0x4d546864;

    qint32 file_magic;
    file.read((char*)(&file_magic),4);

    if (magic != file_magic){
        //todo not a midi file
    }


    file.close();

    return new MidiTrack();
}
