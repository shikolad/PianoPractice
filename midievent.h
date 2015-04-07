#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <QObject>
#include <QDataStream>

class MidiEvent : public QObject
{
    Q_OBJECT
public:
    explicit MidiEvent(QObject *parent = 0);
    ~MidiEvent();
    friend QDataStream &operator >>(QDataStream &stream,MidiEvent &track);
    void setMessage(std::vector<unsigned char> &newMessage);
signals:

public slots:
private:
    static qint32 readVariableLengthQuantity(QDataStream *stream);
    std::vector<unsigned char> message;
};

#endif // MIDIEVENT_H
