#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serial.h"
#include "inputprocessor.h"
#include "commandsender.h"
#include "signalline.h"

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

private:
    Ui::MainWindow *ui;
    Serial serial;
    InputProcessor ip;
    CommandSender cs;

    SignalLine line1, line2, line3;
};

#endif // MAINWINDOW_H
