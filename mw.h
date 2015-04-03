#ifndef MW_H
#define MW_H

#include <QMainWindow>

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
    void updateInputDeviseList();
    void updateOutputDeviceList();

public slots:
    void setMidiDeviceList(QStringList inputList, QStringList outputList);

private slots:

    void on_openButton_clicked();

private:
    Ui::mw *ui;
};

#endif // MW_H
