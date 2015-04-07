#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <QObject>
#include <QDataStream>
#include <QList>
#include <midievent.h>

class MidiTrack : public QObject
{
    Q_OBJECT
public:
    explicit MidiTrack(QObject *parent = 0);
    ~MidiTrack();

    void addEvent(MidiEvent *event);

    friend QDataStream &operator >>(QDataStream &stream,MidiTrack &track);

signals:

public slots:

private:
    quint32 trackLength;
    QList<MidiEvent*> events;
};

#endif // MIDITRACK_H
