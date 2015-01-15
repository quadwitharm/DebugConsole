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
    void verticalSlider();
public slots:
    void refreshDevices();

private slots:
    void on_openButton_pressed();

    void on_closeButton_pressed();

    void on_clearButton_pressed();

    void on_Send_pressed();

    void sendRollPIDParam();
    void sendPitchPIDParam();
    void sendYawPIDParam();
    void sendRollRatePIDParam();
    void sendPitchRatePIDParam();
    void sendYawRatePIDParam();
    void on_pushButton_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_2_pressed();

    void on_SetPoint_sliderReleased();

    void on_SetPoint_3_sliderReleased();

    void on_SetPoint_2_sliderReleased();

private:
    void sendSetPoints();
    Ui::MainWindow *ui;
    Serial serial;
    InputProcessor *ip;
    CommandSender *cs;

    PlotHelper controllerLine1, controllerLine2, controllerLine3;
    PlotHelper grawLine1, grawLine2, grawLine3;
    PlotHelper arawLine1, arawLine2, arawLine3;
    PlotHelper filterLine1, filterLine2, filterLine3;
};

#endif // MAINWINDOW_H
