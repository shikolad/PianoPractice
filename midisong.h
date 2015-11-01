#ifndef MIDISONG_H
#define MIDISONG_H

#include <QObject>
#include <miditrack.h>
#include <QVector>
#include <QList>

class MidiSong : public QObject
{
    Q_OBJECT
public:
    explicit MidiSong(QObject *parent = 0);
    ~MidiSong();

    void addTrack(MidiTrack *track);
    QList<MidiEvent *> getMidiEvents(qint32 time);
    qint32 getNextDelta(qint32 time);

    static MidiSong *loadFromFile(QString filePath);
signals:

public slots:
private :
    QVector<MidiTrack*> trackList;
};

#endif // MIDISONG_H
