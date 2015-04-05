#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <QObject>
#include <QFile>

class MidiTrack : public QObject
{
    Q_OBJECT
public:
    explicit MidiTrack(QObject *parent = 0);
    ~MidiTrack();
    static MidiTrack *loadFromFile(QString filePath);

signals:

public slots:

private:

};

#endif // MIDITRACK_H
