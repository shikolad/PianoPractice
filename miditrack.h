#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <QObject>

class MidiTrack : public QObject
{
    Q_OBJECT
public:
    explicit MidiTrack(QObject *parent = 0);
    ~MidiTrack();

signals:

public slots:

private:

};

#endif // MIDITRACK_H
