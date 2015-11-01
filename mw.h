#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QDirModel>
#include <QFileSystemModel>
#include <QStandardPaths>

namespace Ui {
class mw;
}

class mw : public QMainWindow
{
    Q_OBJECT

public:
    explicit mw(QWidget *parent = 0);
    ~mw();

    void updateDeviceList();

signals:

    void activeDeviceChanged(qint32 input, qint32 output);
    void openFile(QString filePath);
    void play();
    void stop();
    void pause();

public slots:
    void setMidiDeviceList(QStringList inputList, QStringList outputList);
    void activeDeviceChanged(qint32 index);
private slots:

    void on_openButton_clicked();
    void directory_selected(QModelIndex index);

private:
    Ui::mw *ui;
    QDirModel *dirModel;//todo change to qfilesystemmodel
    QFileSystemModel *fileModel;
};

#endif // MW_H
