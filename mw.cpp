#include "mw.h"
#include "ui_mw.h"

#include "QFileDialog"

mw::mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mw)
{
    ui->setupUi(this);
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
    ui->inputDeviceCombo->insertItems(0,inputList);
    ui->outputDeviceCombo->insertItems(0,outputList);
}
