#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <QObject>
#include <QDataStream>

class MidiEvent : public QObject
{
    Q_OBJECT
public:
    enum MidiEventType{
        MIDI,
        META,
        SYSEX
    };
    explicit MidiEvent(QObject *parent = 0);
    ~MidiEvent();
    friend QDataStream &operator >>(QDataStream &stream,MidiEvent &track);
    void setMessage(std::vector<unsigned char> &newMessage);
    void setDeltaTime(qint32 newDelta);
    void setTime(qint32 newTime);
    void setType(MidiEventType newType);
    qint32 getDeltaTime();
    qint32 getTime();
    quint8 getFirstByte();
    std::vector<unsigned char> getMessage();
    MidiEventType getType();

signals:

public slots:
private:
    static qint32 readVariableLengthQuantity(QDataStream *stream);
    std::vector<unsigned char> message;
    qint32 deltaTime;
    qint32 time;
    MidiEventType type;
};

#endif // MIDIEVENT_H
