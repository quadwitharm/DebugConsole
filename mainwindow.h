#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include "inputprocessor.h"
#include "commandsender.h"
#include "plothelper.h"

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
    void sendmotor();
public slots:
    void refreshDevices();

private slots:
    void on_openButton_pressed();
    void on_closeButton_pressed();
    void on_clearButton_pressed();
    void on_Send_pressed();

    void rollPIDPressed();
    void pitchPIDPressed();
    void yawPIDPressed();
    void rollRatePIDPressed();
    void pitchRatePIDPressed();
    void yawRatePIDPressed();

    void rollSliderChanged();
    void pitchSliderChanged();
    void yawSliderChanged();
    void rollRateSliderChanged();
    void pitchRateSliderChanged();
    void yawRateSliderChanged();

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


    void on_lineEdit_2_returnPressed();
    void on_lineEdit_5_returnPressed();
    void on_lineEdit_4_returnPressed();
    void on_lineEdit_3_returnPressed();
signals:

    void rollPIDReleased();
    void pitchPIDReleased();
    void yawPIDReleased();
    void rollRatePIDReleased();
    void pitchRatePIDReleased();
    void yawRatePIDReleased();

private:
    void sendSetPoints();
    Ui::MainWindow *ui;
    Serial serial;
    InputProcessor *ip;
    CommandSender *cs;
    QTimer *timer;

    PlotHelper controllerLine1, controllerLine2, controllerLine3;
    PlotHelper grawLine1, grawLine2, grawLine3;
    PlotHelper arawLine1, arawLine2, arawLine3;
    PlotHelper filterLine1, filterLine2, filterLine3;
};

#endif // MAINWINDOW_H
