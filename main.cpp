#include "mw.h"
#include <QApplication>
#include <rtmidiwrapper.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RTMidiWrapper midiWrapper;
    mw mainWindow;

    QObject::connect(&midiWrapper,SIGNAL(updateDeviceList(QStringList,QStringList)),
                    &mainWindow,SLOT(setMidiDeviceList(QStringList,QStringList)));
    midiWrapper.updateDeviceList();

    mainWindow.show();

    return a.exec();
}
