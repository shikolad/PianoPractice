#include "mw.h"
#include <QApplication>
#include <rtmidiwrapper.h>

//these one are just for test
#include <midisong.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RTMidiWrapper midiWrapper;
    mw mainWindow;
    MidiSong::loadFromFile(QDir::homePath().append(QString::fromUtf8("/midi/una-mattina.midi")));

    QObject::connect(&midiWrapper,SIGNAL(updateDeviceList(QStringList,QStringList)),
                    &mainWindow,SLOT(setMidiDeviceList(QStringList,QStringList)));
    QObject::connect(&mainWindow,SIGNAL(activeDeviceChanged(qint32,qint32)),
                     &midiWrapper,SLOT(setActiveDevices(qint32,qint32)));
    
    midiWrapper.updateDeviceList();

    mainWindow.show();

    return a.exec();
}
