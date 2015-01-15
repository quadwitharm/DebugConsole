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
    controllerLine1(2), controllerLine2(2), controllerLine3(2),
    grawLine1(1), grawLine2(1), grawLine3(1),
    arawLine1(1), arawLine2(1), arawLine3(1),
    filterLine1(1), filterLine2(1), filterLine3(1)
{
    ui->setupUi(this);
    ui->portSelection->setEnabled(true);
    ui->baudRateSelection->setEnabled(true);
    ui->dataBitSelection->setEnabled(true);
    ui->paritySelection->setEnabled(true);
    ui->stopBitCheck->setEnabled(true);
    ui->openButton->setEnabled(true);

    ui->clearButton->setEnabled(true);
    ui->closeButton->setDisabled(true);
    ui->openButton->setFocus();
    refreshDevices();
    controllerLine1.Reset(ui->plotWidget1);
    controllerLine2.Reset(ui->plotWidget2);
    controllerLine3.Reset(ui->plotWidget3);
    grawLine1.Reset(ui->GyroRoll);
    grawLine2.Reset(ui->GyroPitch);
    grawLine3.Reset(ui->GyroYaw);
    grawLine1.setFrequency(1.0/10.0);
    grawLine2.setFrequency(1.0/10.0);
    grawLine3.setFrequency(1.0/10.0);
    grawLine1.setValueRange(3200);
    grawLine2.setValueRange(3200);
    grawLine3.setValueRange(3200);
    arawLine1.Reset(ui->AccelX);
    arawLine2.Reset(ui->AccelY);
    arawLine3.Reset(ui->AccelZ);
    arawLine1.setFrequency(1.0/10.0);
    arawLine2.setFrequency(1.0/10.0);
    arawLine3.setFrequency(1.0/10.0);
    arawLine1.setValueRange(800);
    arawLine2.setValueRange(800);
    arawLine3.setValueRange(800);
    filterLine1.Reset(ui->filterAngleRoll);
    filterLine2.Reset(ui->filterAnglePitch);
    filterLine3.Reset(ui->filterAngleYaw);
    filterLine1.setFrequency(1.0/10.0);
    filterLine2.setFrequency(1.0/10.0);
    filterLine3.setFrequency(1.0/10.0);
    filterLine1.setValueRange(180);
    filterLine2.setValueRange(180);
    filterLine3.setValueRange(180);

    ip = new InputProcessor(this);
    cs = new CommandSender(this,&serial);

    connect(ip,&InputProcessor::DebugOutput,ui->terminal,&Terminal::DebugOutput);

    // Controller output
    connect(ip,&InputProcessor::GotControllerRoll,&controllerLine1,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotControllerPitch,&controllerLine2,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotControllerYaw,&controllerLine3,&PlotHelper::NewData);

    connect(ip,&InputProcessor::GotVertical, [this](float value){ui->verticalOutput->setValue(value);});
    connect(ip,&InputProcessor::GotMotorOutput, [this](const float value[]){
        ui->motor1->setText(QString::number(value[0]));
        ui->motor2->setText(QString::number(value[1]));
        ui->motor3->setText(QString::number(value[2]));
        ui->motor4->setText(QString::number(value[3]));
    });

    // Sensor output
    connect(ip,&InputProcessor::GotGyroRawRoll,&grawLine1,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotGyroRawPitch,&grawLine2,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotGyroRawYaw,&grawLine3,&PlotHelper::NewData);

    connect(ip,&InputProcessor::GotAccelRawRoll,&arawLine1,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotAccelRawPitch,&arawLine2,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotAccelRawYaw,&arawLine3,&PlotHelper::NewData);

    connect(ip,&InputProcessor::GotComplementFilterRoll,&filterLine1,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotComplementFilterPitch,&filterLine2,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotComplementFilterYaw,&filterLine3,&PlotHelper::NewData);

    // Parameter Set
    connect(ui->roll_kp,&QSlider::sliderReleased,this,&MainWindow::sendRollPIDParam);
    connect(ui->roll_ki,&QSlider::sliderReleased,this,&MainWindow::sendRollPIDParam);
    connect(ui->roll_kd,&QSlider::sliderReleased,this,&MainWindow::sendRollPIDParam);

    connect(ui->pitch_kp_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pitch_ki_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pitch_kd_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchPIDParam);

    connect(ui->yaw_kp_2,&QSlider::sliderReleased,this,&MainWindow::sendYawPIDParam);
    connect(ui->yaw_ki_2,&QSlider::sliderReleased,this,&MainWindow::sendYawPIDParam);
    connect(ui->yaw_kd_2,&QSlider::sliderReleased,this,&MainWindow::sendYawPIDParam);

    connect(ui->roll_rate_kp,&QSlider::sliderReleased,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->roll_rate_ki,&QSlider::sliderReleased,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->roll_rate_kd,&QSlider::sliderReleased,this,&MainWindow::sendRollRatePIDParam);

    connect(ui->pitch_rate_kp_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->pitch_rate_ki_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->pitch_rate_kd_3,&QSlider::sliderReleased,this,&MainWindow::sendPitchRatePIDParam);

    connect(ui->yaw_rate_kp_2,&QSlider::sliderReleased,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yaw_rate_ki_2,&QSlider::sliderReleased,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yaw_rate_kd_2,&QSlider::sliderReleased,this,&MainWindow::sendYawRatePIDParam);

    connect(ui->verticalSlider,&QSlider::sliderReleased,this,&MainWindow::verticalSlider);
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

    ui->closeButton->setEnabled(true);

    ip->Reset();
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

void MainWindow::sendRollPIDParam()
{
    float data[3] = {(float)ui->roll_kp->value(), (float)ui->roll_ki->value(), (float)ui->roll_kd->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchPIDParam()
{
    float data[3] = {(float)ui->pitch_kp_3->value(), (float)ui->pitch_ki_3->value(), (float)ui->pitch_kd_3->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawPIDParam()
{
    float data[3] = {(float)ui->yaw_kp_2->value(), (float)ui->yaw_ki_2->value(), (float)ui->yaw_kd_2->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendRollRatePIDParam()
{
    float data[3] = {(float)ui->roll_rate_kp->value(), (float)ui->roll_rate_ki->value(), (float)ui->roll_rate_kd->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x03).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchRatePIDParam()
{
    float data[3] = {(float)ui->pitch_rate_kp_3->value(), (float)ui->pitch_rate_ki_3->value(), (float)ui->pitch_rate_kd_3->value()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawRatePIDParam()
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

void MainWindow::verticalSlider()
{
    float data[1] = {(float)ui->verticalSlider->value() / 1000.0f};
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*1)
        )
    );
}

// Roll
void MainWindow::on_SetPoint_sliderReleased()
{
    sendSetPoints();
}

// Pitch
void MainWindow::on_SetPoint_3_sliderReleased()
{
    sendSetPoints();
}

// Yaw
void MainWindow::on_SetPoint_2_sliderReleased()
{
    sendSetPoints();
}
