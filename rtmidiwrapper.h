#ifndef RTMIDIWRAPPER_H
#define RTMIDIWRAPPER_H

#include <QObject>
#include <RtMidi.h>
#include <QStringList>
#include <unistd.h>
#include <RtMidi.h>

class RTMidiWrapper : public QObject
{
    Q_OBJECT
public:
    explicit RTMidiWrapper(QObject *parent = 0);
    ~RTMidiWrapper();

signals:
    void updateDeviceList(QStringList input, QStringList output);

public slots:
    void updateDeviceList();
    void setActiveDevices(qint32 input, qint32 output);
    void sendMidiEvent(std::vector<quint8> message);
    void sendMidiEvent(std::vector<unsigned char> *message);

private:
    RtMidiIn *midiInputDevice;
    RtMidiOut *midiOutputDevice;

    QStringList getInputDeviceList();
    QStringList getOutputDeviceList();

    qint32 activeInput, activeOutput;

    static void midiInputCallback(double deltatime, std::vector< unsigned char > *message, void *userData);
};

#endif // RTMIDIWRAPPER_H
