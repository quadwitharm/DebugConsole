#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include "inputprocessor.h"
#include "commandsender.h"
#include "controllerplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void refreshDevices();

private slots:
    void on_openButton_pressed();

    void on_closeButton_pressed();

    void on_clearButton_pressed();

    void on_Send_pressed();

    void on_SetPoint_valueChanged(int value);

    void on_SetPoint_3_valueChanged(int value);

    void on_SetPoint_2_valueChanged(int value);

    void sendRollPIDParam(int);
    void sendPitchPIDParam(int);
    void sendYawPIDParam(int);
    void sendRollRatePIDParam(int);
    void sendPitchRatePIDParam(int);
    void sendYawRatePIDParam(int);
    void on_pushButton_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_2_pressed();

private:
    void sendSetPoints();
    Ui::MainWindow *ui;
    Serial serial;
    InputProcessor *ip;
    CommandSender *cs;

    ControllerPlot line1, line2, line3;
};

#endif // MAINWINDOW_H
