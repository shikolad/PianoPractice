#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QTimer>
#include <midisong.h>

class MidiPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MidiPlayer(QObject *parent = 0);
    ~MidiPlayer();

signals:
    void stopped();
    void sendMidiMessage(std::vector<quint8> message);

public slots:
    void openFile(QString filePath);
    void play();
    void pause();
    void stop();

private slots:
    void midiEvent();

private:
    QTimer* timer;
    MidiSong *song;

    quint32 currentTime;
};

#endif // MIDIPLAYER_H
