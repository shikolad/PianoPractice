#include "mw.h"
#include <QApplication>
#include <rtmidiwrapper.h>
#include <midiplayer.h>

//these one are just for test
#include <midisong.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RTMidiWrapper midiWrapper;
    mw mainWindow;
    MidiPlayer player;


    QObject::connect(&midiWrapper,SIGNAL(updateDeviceList(QStringList,QStringList)),
                    &mainWindow,SLOT(setMidiDeviceList(QStringList,QStringList)));
    QObject::connect(&mainWindow,SIGNAL(activeDeviceChanged(qint32,qint32)),
                     &midiWrapper,SLOT(setActiveDevices(qint32,qint32)));
    QObject::connect(&mainWindow,SIGNAL(openFile(QString)),
                     &player,SLOT(openFile(QString)));
    QObject::connect(&mainWindow,SIGNAL(play()),
                     &player,SLOT(play()));
    QObject::connect(&mainWindow,SIGNAL(pause()),
                     &player,SLOT(pause()));
    QObject::connect(&mainWindow,SIGNAL(stop()),
                     &player,SLOT(stop()));

    QObject::connect(&player,SIGNAL(sendMidiMessage(std::vector<quint8>)),
                     &midiWrapper,SLOT(sendMidiEvent(std::vector<quint8>)));
    
    midiWrapper.updateDeviceList();

    mainWindow.show();

    return a.exec();
}
