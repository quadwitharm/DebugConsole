#include <QDir>
#include <QMessageBox>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serial(this),timer(new QTimer(this)),
    controllerLine1(3), controllerLine2(3), controllerLine3(3),
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
    controllerLine1.setValueRange(180);
    controllerLine2.setValueRange(180);
    controllerLine3.setValueRange(180);
    controllerLine1.setFrequency(1.0/10.0f);
    controllerLine2.setFrequency(1.0/10.0f);
    controllerLine3.setFrequency(1.0/10.0f);
    grawLine1.Reset(ui->GyroRoll);
    grawLine2.Reset(ui->GyroPitch);
    grawLine3.Reset(ui->GyroYaw);
    grawLine1.setFrequency(1.0/10.0f);
    grawLine2.setFrequency(1.0/10.0f);
    grawLine3.setFrequency(1.0/10.0f);
    grawLine1.setValueRange(100);
    grawLine2.setValueRange(100);
    grawLine3.setValueRange(100);
    arawLine1.Reset(ui->AccelX);
    arawLine2.Reset(ui->AccelY);
    arawLine3.Reset(ui->AccelZ);
    arawLine1.setFrequency(1.0/10.0f);
    arawLine2.setFrequency(1.0/10.0f);
    arawLine3.setFrequency(1.0/10.0f);
    arawLine1.setValueRange(800);
    arawLine2.setValueRange(800);
    arawLine3.setValueRange(800);
    filterLine1.Reset(ui->filterAngleRoll);
    filterLine2.Reset(ui->filterAnglePitch);
    filterLine3.Reset(ui->filterAngleYaw);
    filterLine1.setFrequency(1.0/10.0f);
    filterLine2.setFrequency(1.0/10.0f);
    filterLine3.setFrequency(1.0/10.0f);
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

    connect(ip,&InputProcessor::GotComplementFilterRoll,&controllerLine1,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotComplementFilterPitch,&controllerLine2,&PlotHelper::NewData);
    connect(ip,&InputProcessor::GotComplementFilterYaw,&controllerLine3,&PlotHelper::NewData);

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

    connect(ui->rp,&QLineEdit::returnPressed,this,&MainWindow::sRollPIDParam);
    connect(ui->ri,&QLineEdit::returnPressed,this,&MainWindow::sRollPIDParam);
    connect(ui->rd,&QLineEdit::returnPressed,this,&MainWindow::sRollPIDParam);
    connect(ui->rrp,&QLineEdit::returnPressed,this,&MainWindow::sRollRatePIDParam);
    connect(ui->rri,&QLineEdit::returnPressed,this,&MainWindow::sRollRatePIDParam);
    connect(ui->rrd,&QLineEdit::returnPressed,this,&MainWindow::sRollRatePIDParam);

    connect(ui->pp,&QLineEdit::returnPressed,this,&MainWindow::sPitchPIDParam);
    connect(ui->pi,&QLineEdit::returnPressed,this,&MainWindow::sPitchPIDParam);
    connect(ui->pd,&QLineEdit::returnPressed,this,&MainWindow::sPitchPIDParam);
    connect(ui->ppp,&QLineEdit::returnPressed,this,&MainWindow::sPitchRatePIDParam);
    connect(ui->ppi,&QLineEdit::returnPressed,this,&MainWindow::sPitchRatePIDParam);
    connect(ui->ppd,&QLineEdit::returnPressed,this,&MainWindow::sPitchRatePIDParam);

    connect(ui->yp,&QLineEdit::returnPressed,this,&MainWindow::sYawPIDParam);
    connect(ui->yi,&QLineEdit::returnPressed,this,&MainWindow::sYawPIDParam);
    connect(ui->yd,&QLineEdit::returnPressed,this,&MainWindow::sYawPIDParam);
    connect(ui->yyp,&QLineEdit::returnPressed,this,&MainWindow::sYawRatePIDParam);
    connect(ui->yyi,&QLineEdit::returnPressed,this,&MainWindow::sYawRatePIDParam);
    connect(ui->yyd,&QLineEdit::returnPressed,this,&MainWindow::sYawRatePIDParam);

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

    connect(timer,&QTimer::timeout,this,&MainWindow::sendRollRatePIDParam);
    timer->setInterval(100);
    //timer->start();
}

void MainWindow::on_closeButton_pressed()
{
    timer->stop();

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
    float data[3] = {(float)ui->roll_kp->value()/100.0f, (float)ui->roll_ki->value()/100.0f, (float)ui->roll_kd->value()/100.0f};
    u_int8_t *a = (u_int8_t *)data;
    for(int i = 0;i < 12;++i){
        qDebug() << a[i];
    }
    qDebug() << data[0] << data[1] << data[2];
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchPIDParam()
{
    float data[3] = {(float)ui->pitch_kp_3->value()/1000.0f, (float)ui->pitch_ki_3->value()/1000.0f, (float)ui->pitch_kd_3->value()/1000.0f};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawPIDParam()
{
    float data[3] = {(float)ui->yaw_kp_2->value()/1000.0f, (float)ui->yaw_ki_2->value()/1000.0f, (float)ui->yaw_kd_2->value()/1000.0f};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x02).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendRollRatePIDParam()
{
    float data[3] = {(float)ui->roll_rate_kp->value()/1000.0f, (float)ui->roll_rate_ki->value()/1000.0f, (float)ui->roll_rate_kd->value()/1000.0f};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x03).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendPitchRatePIDParam()
{
    float data[3] = {(float)ui->pitch_rate_kp_3->value()/1000.0f, (float)ui->pitch_rate_ki_3->value()/1000.0f, (float)ui->pitch_rate_kd_3->value()/1000.0f};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendYawRatePIDParam()
{
    float data[3] = {(float)ui->yaw_rate_kp_2->value()/1000.0f, (float)ui->yaw_rate_ki_2->value()/1000.0f, (float)ui->yaw_rate_kd_2->value()/1000.0f};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x05).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
                );
}

void MainWindow::sRollPIDParam()
{
    float data[3] = {ui->rp->text().toFloat(), ui->ri->text().toFloat(), ui->rd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sPitchPIDParam()
{
    float data[3] = {ui->pp->text().toFloat(), ui->pi->text().toFloat(), ui->pd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sYawPIDParam()
{
    float data[3] = {ui->yp->text().toFloat(), ui->yi->text().toFloat(), ui->yd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x02).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sRollRatePIDParam()
{
    float data[3] = {ui->rrp->text().toFloat(), ui->rri->text().toFloat(), ui->rrd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x03).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sPitchRatePIDParam()
{
    float data[3] = {ui->ppp->text().toFloat(), ui->ppi->text().toFloat(), ui->ppd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sYawRatePIDParam()
{
    float data[3] = {ui->yyp->text().toFloat(), ui->yyi->text().toFloat(), ui->yyd->text().toFloat()};
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x05).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

void MainWindow::sendSetPoints()
{
    float data[3] = {ui->lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat(), ui->lineEdit_5->text().toFloat()};
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
    qDebug() << (float)ui->verticalSlider->value() / 1000.0f;
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*1)
        )
    );
}



void MainWindow::on_lineEdit_2_returnPressed()
{
    float data[1] = {ui->lineEdit_2->text().toFloat()};
    qDebug() << ui->lineEdit_2->text().toFloat();
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*1)
        )
    );
    ui->verticalSlider->setValue(ui->lineEdit_2->text().toFloat() * 1000.0f);
}

void MainWindow::on_lineEdit_5_returnPressed()
{
        sendSetPoints();
}

void MainWindow::on_lineEdit_4_returnPressed()
{
        sendSetPoints();
}

void MainWindow::on_lineEdit_3_returnPressed()
{
        sendSetPoints();
}
