#ifndef MIDISONG_H
#define MIDISONG_H

#include <QObject>
#include <miditrack.h>

class MidiSong : public QObject
{
    Q_OBJECT
public:
    explicit MidiSong(QObject *parent = 0);
    ~MidiSong();
    static MidiSong *loadFromFile(QString filePath);
signals:

public slots:
};

#endif // MIDISONG_H
