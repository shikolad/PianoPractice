#include "mw.h"
#include <QApplication>
#include <rtmidiwrapper.h>
#include <miditrack.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RTMidiWrapper midiWrapper;
    mw mainWindow;
    MidiTrack::loadFromFile(QString::fromUtf8("/home/shiko/midi/una-mattina.midi"));

    QObject::connect(&midiWrapper,SIGNAL(updateDeviceList(QStringList,QStringList)),
                    &mainWindow,SLOT(setMidiDeviceList(QStringList,QStringList)));
    QObject::connect(&mainWindow,SIGNAL(activeDeviceChanged(qint32,qint32)),
                     &midiWrapper,SLOT(setActiveDevices(qint32,qint32)));
    
    midiWrapper.updateDeviceList();

    mainWindow.show();

    return a.exec();
}
