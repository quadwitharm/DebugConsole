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

    ip = new InputProcessor(this);
    cs = new CommandSender(this,&serial);

    connect(ip,&InputProcessor::DebugOutput,ui->terminal,&Terminal::DebugOutput);

    connect(ip,&InputProcessor::GotControllerRoll,&line1,&ControllerPlot::NewData);
    connect(ip,&InputProcessor::GotControllerPitch,&line2,&ControllerPlot::NewData);
    connect(ip,&InputProcessor::GotControllerYaw,&line3,&ControllerPlot::NewData);

    connect(ui->roll_kp,&QSlider::sliderMoved,this,&MainWindow::sendRollPIDParam);
    connect(ui->roll_ki,&QSlider::sliderMoved,this,&MainWindow::sendRollPIDParam);
    connect(ui->roll_kd,&QSlider::sliderMoved,this,&MainWindow::sendRollPIDParam);

    connect(ui->pitch_kp_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pitch_ki_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pitch_kd_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchPIDParam);

    connect(ui->yaw_kp_2,&QSlider::sliderMoved,this,&MainWindow::sendYawPIDParam);
    connect(ui->yaw_ki_2,&QSlider::sliderMoved,this,&MainWindow::sendYawPIDParam);
    connect(ui->yaw_kd_2,&QSlider::sliderMoved,this,&MainWindow::sendYawPIDParam);

    connect(ui->roll_rate_kp,&QSlider::sliderMoved,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->roll_rate_ki,&QSlider::sliderMoved,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->roll_rate_kd,&QSlider::sliderMoved,this,&MainWindow::sendRollRatePIDParam);

    connect(ui->pitch_rate_kp_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->pitch_rate_ki_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->pitch_rate_kd_3,&QSlider::sliderMoved,this,&MainWindow::sendPitchRatePIDParam);

    connect(ui->yaw_rate_kp_2,&QSlider::sliderMoved,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yaw_rate_ki_2,&QSlider::sliderMoved,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yaw_rate_kd_2,&QSlider::sliderMoved,this,&MainWindow::sendYawRatePIDParam);
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

    connect(&serial,&Serial::signalReceied,ip,&InputProcessor::GetInput);
    serial.start(QThread::LowestPriority);
    serial.startThread();
}

void MainWindow::on_closeButton_pressed()
{
    disconnect(&serial,&Serial::signalReceied,ip,&InputProcessor::GetInput);
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

void MainWindow::on_Send_pressed()
{
    cs->SendCommand(DebugCommand(ui->lineEdit->text()));
}
// Roll
void MainWindow::on_SetPoint_valueChanged(int) { sendSetPoints(); }
// Pitch
void MainWindow::on_SetPoint_3_valueChanged(int) { sendSetPoints(); }
// Yaw
void MainWindow::on_SetPoint_2_valueChanged(int) { sendSetPoints(); }

void MainWindow::sendRollPIDParam(int)
{
    float data[3] = {(float)ui->roll_kp->value(), (float)ui->roll_ki->value(), (float)ui->roll_kd->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchPIDParam(int)
{
    float data[3] = {(float)ui->pitch_kp_3->value(), (float)ui->pitch_ki_3->value(), (float)ui->pitch_kd_3->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawPIDParam(int)
{
    float data[3] = {(float)ui->yaw_kp_2->value(), (float)ui->yaw_ki_2->value(), (float)ui->yaw_kd_2->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x02).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendRollRatePIDParam(int)
{
    float data[3] = {(float)ui->roll_rate_kp->value(), (float)ui->roll_rate_ki->value(), (float)ui->roll_rate_kd->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x03).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchRatePIDParam(int)
{
    float data[3] = {(float)ui->pitch_rate_kp_3->value(), (float)ui->pitch_rate_ki_3->value(), (float)ui->pitch_rate_kd_3->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawRatePIDParam(int)
{
    float data[3] = {(float)ui->yaw_rate_kp_2->value(), (float)ui->yaw_rate_ki_2->value(), (float)ui->yaw_rate_kd_2->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x05).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendSetPoints()
{
    float data[3] = {(float)ui->SetPoint->value(), (float)ui->SetPoint_3->value(), (float)ui->SetPoint_2->value()};
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::on_pushButton_pressed()
{
// Controller off
    cs->SendCommand( Command(0x00, QByteArray() ) );
}

void MainWindow::on_pushButton_4_pressed()
{
// Controller on
    cs->SendCommand( Command(0x01, QByteArray() ) );
}

void MainWindow::on_pushButton_3_pressed()
{
// Sensor power off
    cs->SendCommand( Command(0x02, QByteArray() ) );
}

void MainWindow::on_pushButton_2_pressed()
{
// Sensor power on
    cs->SendCommand( Command(0x03, QByteArray() ) );
}
