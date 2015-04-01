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
    dialog.getOpenFileName(this,
                           "Select file",
                           "",
                           "Midi Files(*.midi *.mid);;All Files(*.*)");

}
