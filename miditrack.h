#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <QObject>
#include <QDataStream>

class MidiTrack : public QObject
{
    Q_OBJECT
public:
    explicit MidiTrack(QObject *parent = 0);
    ~MidiTrack();

    friend QDataStream &operator >>(QDataStream &stream,MidiTrack &track);

signals:

public slots:

private:


};

#endif // MIDITRACK_H
