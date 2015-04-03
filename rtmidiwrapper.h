#ifndef RTMIDIWRAPPER_H
#define RTMIDIWRAPPER_H

#include <QObject>
#include <RtMidi.h>
#include <QStringList>

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

private:
    RtMidiIn *midiInputDevice;
    RtMidiOut *midiOutputDevice;

    QStringList getInputDeviceList();
    QStringList getOutputDeviceList();
};

#endif // RTMIDIWRAPPER_H
