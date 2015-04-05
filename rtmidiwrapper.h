#ifndef RTMIDIWRAPPER_H
#define RTMIDIWRAPPER_H

#include <QObject>
#include <RtMidi.h>
#include <QStringList>
#include <unistd.h>

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

private:
    RtMidiIn *midiInputDevice;
    RtMidiOut *midiOutputDevice;

    QStringList getInputDeviceList();
    QStringList getOutputDeviceList();

    qint32 activeInput, activeOutput;
};

#endif // RTMIDIWRAPPER_H
