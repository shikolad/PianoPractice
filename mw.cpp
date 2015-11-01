#include "mw.h"
#include "ui_mw.h"

#include "QFileDialog"
#include <QDebug>

mw::mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mw)
{
    ui->setupUi(this);
    connect(ui->inputDeviceCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(activeDeviceChanged(qint32)));
    connect(ui->outputDeviceCombo,SIGNAL(currentIndexChanged(int)),
            this,SLOT(activeDeviceChanged(qint32)));

    connect(ui->playButton,SIGNAL(clicked()),SIGNAL(play()));
    connect(ui->pauseButton,SIGNAL(clicked()),SIGNAL(pause()));
    connect(ui->stopButton,SIGNAL(clicked()),SIGNAL(stop()));

    connect(ui->foldersTreeView,SIGNAL(entered(QModelIndex)),
            SLOT(directory_selected(QModelIndex)));

    dirModel = new QDirModel();
    dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    ui->foldersTreeView->setModel(dirModel);
    for (qint32 i = 1; i < dirModel->columnCount();i++){
        ui->foldersTreeView->setColumnHidden(i,true);
    }

    fileModel = new QFileSystemModel();
    fileModel->setFilter(QDir::Files);
    ui->fileListView->setModel(fileModel);

    QModelIndex index = dirModel->index(QStandardPaths::standardLocations(
                              QStandardPaths::HomeLocation).first());
    ui->foldersTreeView->scrollTo(index);
}

mw::~mw()
{
    delete ui;
}


void mw::on_openButton_clicked()
{
    QFileDialog dialog;
    QString filePath = dialog.getOpenFileName(this,
                           "Select file",
                           "",
                           "Midi Files(*.midi *.mid);;All Files(*.*)");
    emit openFile(filePath);

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

void mw::directory_selected(QModelIndex index){
    QString dirPath = dirModel->filePath(index);
    fileModel->setRootPath(dirPath);
}
