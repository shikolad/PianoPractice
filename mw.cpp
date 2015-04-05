#include "mw.h"
#include "ui_mw.h"

#include "QFileDialog"

mw::mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mw)
{
    ui->setupUi(this);
    connect(ui->inputDeviceCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(activeDeviceChanged(qint32)));
    connect(ui->outputDeviceCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(activeDeviceChanged(qint32)));
}

mw::~mw()
{
    delete ui;
}


void mw::on_openButton_clicked()
{
    QFileDialog dialog;
    QString filepath = dialog.getOpenFileName(this,
                           "Select file",
                           "",
                           "Midi Files(*.midi *.mid);;All Files(*.*)");

}

void mw::setMidiDeviceList(QStringList inputList,QStringList outputList){
    ui->inputDeviceCombo->clear();
    ui->outputDeviceCombo->clear();
    ui->inputDeviceCombo->addItem(tr("None"));
    ui->outputDeviceCombo->addItem(tr("None"));
    ui->inputDeviceCombo->insertItems(1,inputList);
    ui->outputDeviceCombo->insertItems(1,outputList);
}

void mw::activeDeviceChanged(qint32 index){
    Q_UNUSED(index)
    qint32 inputNumber = ui->inputDeviceCombo->currentIndex() - 1;
    qint32 outputNumber = ui->outputDeviceCombo->currentIndex() - 1;
    emit activeDeviceChanged(inputNumber >= -1 ? inputNumber : -1,
                             outputNumber >= -1 ? outputNumber : -1);
}
