#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <QObject>

class MidiEvent : public QObject
{
    Q_OBJECT
public:
    explicit MidiEvent(QObject *parent = 0);
    ~MidiEvent();

signals:

public slots:
};

#endif // MIDIEVENT_H
