#include "midiplayer.h"
#include <QList>
#include "QDebug"

MidiPlayer::MidiPlayer(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect (timer,SIGNAL(timeout()),
             this, SLOT(midiEvent()));
    song = NULL;
    currentTime = 0;
}

MidiPlayer::~MidiPlayer()
{

}

void MidiPlayer::openFile(QString filePath){
    if (song)
        delete song;
    song = MidiSong::loadFromFile(filePath);
    currentTime = 0;
}

void MidiPlayer::play(){
    timer->start(0);
    qDebug() << "start playing";
}

void MidiPlayer::pause(){
    timer->stop();
    //todo save position
    qDebug() << "pause playing";
}

void MidiPlayer::stop(){
    timer->stop();
    currentTime = 0;
    qDebug() << "stop playing";
}

void MidiPlayer::midiEvent(){
    currentTime += timer->interval();
    QList<MidiEvent*> messages = song->getMidiEvents(currentTime);
    foreach (MidiEvent *ev, messages) {
        if (ev->getType() == MidiEvent::META)
            continue;
        emit sendMidiMessage(ev->getMessage());
        std::vector<unsigned char> msg = ev->getMessage();
        foreach (unsigned char c,msg)
            qDebug() << (int)c;
        qDebug() << "next msg";
    }
    qint32 newDelta = song->getNextDelta(currentTime);
    if (newDelta == -1)
        timer->stop();
    else
        timer->start(newDelta);
}
