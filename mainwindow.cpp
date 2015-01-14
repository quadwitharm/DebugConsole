#include <QDir>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serial(this),
    ip(this),
    cs(this,&serial),
    line1(),
    line2(),
    line3()
{
    ui->setupUi(this);
    ui->portSelection->setEnabled(true);
    ui->baudRateSelection->setEnabled(true);
    ui->dataBitSelection->setEnabled(true);
    ui->paritySelection->setEnabled(true);
    ui->stopBitCheck->setEnabled(true);
    ui->openButton->setEnabled(true);

    ui->clearButton->setDisabled(true);
    ui->closeButton->setDisabled(true);
    ui->openButton->setFocus();
    refreshDevices();
    line1.Reset(ui->plotWidget1);
    line2.Reset(ui->plotWidget2);
    line3.Reset(ui->plotWidget3);
    line1.NewData(0.1,4);
    line1.NewData(0.1,6);
    line1.NewData(0.1,3);
    line1.NewData(0.1,44);
    line1.NewData(0.1,44);
    line1.NewData(0.1,45);
    line1.NewData(0.1,490);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshDevices()
{
    QStringList deviceList;
    QDir dir("/dev/");
    QStringList filters;
    filters << "ttyUSB*" << "ttyS*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files| QDir::System);
    dir.setSorting(QDir::Unsorted);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        deviceList << fileInfo.fileName();
    }
    ui->portSelection->clear();
    ui->portSelection->addItems(deviceList);
}

void MainWindow::on_openButton_pressed()
{
    serial.setDeviceName("/dev/" + ui->portSelection->currentText());
    serial.setReadWrite();
    if(!QFile(serial.getDeviceName()).exists()){
        QMessageBox::warning(this,"Error opening port","Device file not found!");
        return;
    }
    if(!serial.openDevice()){
        QMessageBox::warning(this,"Error opening port","Device file not found!");
        return;
    }
    serial.setBaudRate(static_cast<BaudRateType>(ui->baudRateSelection->currentIndex()+1
    ));
    serial.setDataBits(static_cast<DataBitsType>(ui->dataBitSelection->currentIndex()));
    serial.setParity(static_cast<ParityType>(ui->paritySelection->currentIndex()));
    if(ui->stopBitCheck->isChecked()){
        serial.setStopBits(SB2);
    }else{
        serial.setStopBits(SB1);
    }
    if(!serial.applySetting()){
        QMessageBox::warning(this,"Error opening port","Unable to apply port settings.");
        return;
    }

    ui->portSelection->setDisabled(true);
    ui->baudRateSelection->setDisabled(true);
    ui->dataBitSelection->setDisabled(true);
    ui->paritySelection->setDisabled(true);
    ui->stopBitCheck->setDisabled(true);
    ui->openButton->setDisabled(true);

    ui->clearButton->setEnabled(true);
    ui->closeButton->setEnabled(true);
    connect(&serial,&Serial::signalReceied,&ip,&InputProcessor::GetInput);
    serial.start(QThread::LowestPriority);
    serial.startThread();
}

void MainWindow::on_closeButton_pressed()
{
    disconnect(&serial,&Serial::signalReceied,&ip,&InputProcessor::GetInput);
    serial.closeDevice();

    ui->portSelection->setEnabled(true);
    ui->baudRateSelection->setEnabled(true);
    ui->dataBitSelection->setEnabled(true);
    ui->paritySelection->setEnabled(true);
    ui->stopBitCheck->setEnabled(true);
    ui->openButton->setEnabled(true);

    ui->clearButton->setDisabled(true);
    ui->closeButton->setDisabled(true);
}

void MainWindow::on_clearButton_pressed()
{
    ui->terminal->clear();
}
