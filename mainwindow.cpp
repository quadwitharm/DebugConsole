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

    // TODO: implement Start, End send parameter slot, and a generic send command method
    connect(ui->roll_kp,&QSlider::sliderPressed,this,&MainWindow::rollPIDPressed);


    connect(ui->roll_kp,&QSlider::sliderReleased,this,&MainWindow::rollSliderChanged);
    connect(ui->roll_ki,&QSlider::sliderReleased,this,&MainWindow::rollSliderChanged);
    connect(ui->roll_kd,&QSlider::sliderReleased,this,&MainWindow::rollSliderChanged);
    connect(ui->pitch_kp_3,&QSlider::sliderReleased,this,&MainWindow::pitchSliderChanged);
    connect(ui->pitch_ki_3,&QSlider::sliderReleased,this,&MainWindow::pitchSliderChanged);
    connect(ui->pitch_kd_3,&QSlider::sliderReleased,this,&MainWindow::pitchSliderChanged);

    connect(ui->yaw_kp_2,&QSlider::sliderReleased,this,&MainWindow::yawSliderChanged);
    connect(ui->yaw_ki_2,&QSlider::sliderReleased,this,&MainWindow::yawSliderChanged);
    connect(ui->yaw_kd_2,&QSlider::sliderReleased,this,&MainWindow::yawSliderChanged);
    connect(ui->roll_rate_kp,&QSlider::sliderReleased,this,&MainWindow::rollRateSliderChanged);
    connect(ui->roll_rate_ki,&QSlider::sliderReleased,this,&MainWindow::rollRateSliderChanged);
    connect(ui->roll_rate_kd,&QSlider::sliderReleased,this,&MainWindow::rollRateSliderChanged);

    connect(ui->pitch_rate_kp_3,&QSlider::sliderReleased,this,&MainWindow::pitchRateSliderChanged);
    connect(ui->pitch_rate_ki_3,&QSlider::sliderReleased,this,&MainWindow::pitchRateSliderChanged);
    connect(ui->pitch_rate_kd_3,&QSlider::sliderReleased,this,&MainWindow::pitchRateSliderChanged);
    connect(ui->yaw_rate_kp_2,&QSlider::sliderReleased,this,&MainWindow::yawRateSliderChanged);
    connect(ui->yaw_rate_ki_2,&QSlider::sliderReleased,this,&MainWindow::yawRateSliderChanged);
    connect(ui->yaw_rate_kd_2,&QSlider::sliderReleased,this,&MainWindow::yawRateSliderChanged);

    connect(ui->rp,&QLineEdit::returnPressed,this,&MainWindow::sendRollPIDParam);
    connect(ui->ri,&QLineEdit::returnPressed,this,&MainWindow::sendRollPIDParam);
    connect(ui->rd,&QLineEdit::returnPressed,this,&MainWindow::sendRollPIDParam);
    connect(ui->rrp,&QLineEdit::returnPressed,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->rri,&QLineEdit::returnPressed,this,&MainWindow::sendRollRatePIDParam);
    connect(ui->rrd,&QLineEdit::returnPressed,this,&MainWindow::sendRollRatePIDParam);

    connect(ui->pp,&QLineEdit::returnPressed,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pi,&QLineEdit::returnPressed,this,&MainWindow::sendPitchPIDParam);
    connect(ui->pd,&QLineEdit::returnPressed,this,&MainWindow::sendPitchPIDParam);
    connect(ui->ppp,&QLineEdit::returnPressed,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->ppi,&QLineEdit::returnPressed,this,&MainWindow::sendPitchRatePIDParam);
    connect(ui->ppd,&QLineEdit::returnPressed,this,&MainWindow::sendPitchRatePIDParam);

    connect(ui->yp,&QLineEdit::returnPressed,this,&MainWindow::sendYawPIDParam);
    connect(ui->yi,&QLineEdit::returnPressed,this,&MainWindow::sendYawPIDParam);
    connect(ui->yd,&QLineEdit::returnPressed,this,&MainWindow::sendYawPIDParam);
    connect(ui->yyp,&QLineEdit::returnPressed,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yyi,&QLineEdit::returnPressed,this,&MainWindow::sendYawRatePIDParam);
    connect(ui->yyd,&QLineEdit::returnPressed,this,&MainWindow::sendYawRatePIDParam);

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

#define REPEAT_CMD_SEND 0
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

    connect(timer,&QTimer::timeout,this,&MainWindow::rollRateSliderChanged);
    timer->setInterval(100);
#if REPEAT_CMD_SEND
    timer->start();
#endif
}

// Close port and stop command send timer
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

// Clear text terminal
void MainWindow::on_clearButton_pressed()
{
    ui->terminal->clear();
}

// Debug(Text) commands
void MainWindow::on_Send_pressed()
{
    cs->SendCommand(DebugCommand(ui->lineEdit->text()));
}

#define SLIDER_COMMAND_INTERVAL 150

void MainWindow::rollPIDPressed()
{
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::rollPIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::rollSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

void MainWindow::pitchPIDPressed(){
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::pitchPIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::pitchSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

void MainWindow::yawPIDPressed(){
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::yawPIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::yawSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

void MainWindow::rollRatePIDPressed(){
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::rollRatePIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::rollRateSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

void MainWindow::pitchRatePIDPressed(){
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::pitchRatePIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::pitchRateSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

void MainWindow::yawRatePIDPressed(){
    QTimer *timer = new QTimer(this);
    connect(this,&MainWindow::yawRatePIDReleased,[timer](){
        timer->stop();
        timer->deleteLater();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::yawRateSliderChanged);
    timer->start(SLIDER_COMMAND_INTERVAL);
}

#define ROLL_PID_SCALE 1000.0f
// Roll stab pid parameter
void MainWindow::sendRollPIDParam()
{
    float data[3] = {ui->rp->text().toFloat(), ui->ri->text().toFloat(), ui->rd->text().toFloat()};
    ui->roll_kp->setValue(data[0] * ROLL_PID_SCALE);
    ui->roll_ki->setValue(data[1] * ROLL_PID_SCALE);
    ui->roll_kd->setValue(data[2] * ROLL_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::rollSliderChanged()
{
    ui->rp->setText(QString::number(ui->roll_kp->value() / ROLL_PID_SCALE));
    ui->ri->setText(QString::number(ui->roll_ki->value() / ROLL_PID_SCALE));
    ui->rd->setText(QString::number(ui->roll_kd->value() / ROLL_PID_SCALE));
    sendRollPIDParam();
}

#define PITCH_PID_SCALE 1000.0f
// Pitch stab pid parameter
void MainWindow::sendPitchPIDParam()
{
    float data[3] = {ui->pp->text().toFloat(), ui->pi->text().toFloat(), ui->pd->text().toFloat()};
    ui->pitch_kp_3->setValue(data[0] * PITCH_PID_SCALE);
    ui->pitch_ki_3->setValue(data[1] * PITCH_PID_SCALE);
    ui->pitch_kd_3->setValue(data[2] * PITCH_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::pitchSliderChanged()
{
    ui->pp->setText(QString::number(ui->pitch_kp_3->value() / PITCH_PID_SCALE));
    ui->pi->setText(QString::number(ui->pitch_ki_3->value() / PITCH_PID_SCALE));
    ui->pd->setText(QString::number(ui->pitch_kd_3->value() / PITCH_PID_SCALE));
    sendPitchPIDParam();
}

#define YAW_PID_SCALE 1000.0f
// Yaw stab pid parameter
void MainWindow::sendYawPIDParam()
{
    float data[3] = {ui->yp->text().toFloat(), ui->yi->text().toFloat(), ui->yd->text().toFloat()};
    ui->yaw_kp_2->setValue(data[0] * YAW_PID_SCALE);
    ui->yaw_ki_2->setValue(data[1] * YAW_PID_SCALE);
    ui->yaw_kd_2->setValue(data[2] * YAW_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x02).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::yawSliderChanged()
{
    ui->yp->setText(QString::number(ui->yaw_kp_2->value() / YAW_PID_SCALE));
    ui->yi->setText(QString::number(ui->yaw_ki_2->value() / YAW_PID_SCALE));
    ui->yd->setText(QString::number(ui->yaw_kd_2->value() / YAW_PID_SCALE));
    sendYawPIDParam();
}

#define ROLL_RATE_PID_SCALE 1000.0f
// Roll rate pid parameter
void MainWindow::sendRollRatePIDParam()
{
    float data[3] = {ui->rrp->text().toFloat(), ui->rri->text().toFloat(), ui->rrd->text().toFloat()};
    ui->roll_rate_kp->setValue(data[0] * ROLL_RATE_PID_SCALE);
    ui->roll_rate_ki->setValue(data[1] * ROLL_RATE_PID_SCALE);
    ui->roll_rate_kd->setValue(data[2] * ROLL_RATE_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x03).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::rollRateSliderChanged()
{
    ui->rrp->setText(QString::number(ui->roll_rate_kp->value() / ROLL_RATE_PID_SCALE));
    ui->rri->setText(QString::number(ui->roll_rate_ki->value() / ROLL_RATE_PID_SCALE));
    ui->rrd->setText(QString::number(ui->roll_rate_kd->value() / ROLL_RATE_PID_SCALE));
    sendRollRatePIDParam();
}

#define PITCH_RATE_PID_SCALE 1000.0f
// Pitch rate pid parameter
void MainWindow::sendPitchRatePIDParam()
{
    float data[3] = {ui->ppp->text().toFloat(), ui->ppi->text().toFloat(), ui->ppd->text().toFloat()};
    ui->pitch_rate_kp_3->setValue(data[0] * PITCH_RATE_PID_SCALE);
    ui->pitch_rate_ki_3->setValue(data[1] * PITCH_RATE_PID_SCALE);
    ui->pitch_rate_kd_3->setValue(data[2] * PITCH_RATE_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::pitchRateSliderChanged()
{
    ui->ppp->setText(QString::number(ui->pitch_rate_kp_3->value() / PITCH_RATE_PID_SCALE));
    ui->ppi->setText(QString::number(ui->pitch_rate_ki_3->value() / PITCH_RATE_PID_SCALE));
    ui->ppd->setText(QString::number(ui->pitch_rate_kd_3->value() / PITCH_RATE_PID_SCALE));
    sendPitchRatePIDParam();
}

#define YAW_RATE_PID_SCALE 1000.0f
// Yaw rate pid parameter
void MainWindow::sendYawRatePIDParam()
{
    float data[3] = {ui->yyp->text().toFloat(), ui->yyi->text().toFloat(), ui->yyd->text().toFloat()};
    ui->yaw_rate_kp_2->setValue(data[0] * YAW_RATE_PID_SCALE);
    ui->yaw_rate_ki_2->setValue(data[1] * YAW_RATE_PID_SCALE);
    ui->yaw_rate_kd_2->setValue(data[2] * YAW_RATE_PID_SCALE);
    cs->SendCommand(
        Command(0x04,
            QByteArray().append((char)0x04).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}
void MainWindow::yawRateSliderChanged()
{
    ui->yyp->setText(QString::number(ui->yaw_rate_kp_2->value() / YAW_RATE_PID_SCALE));
    ui->yyi->setText(QString::number(ui->yaw_rate_ki_2->value() / YAW_RATE_PID_SCALE));
    ui->yyd->setText(QString::number(ui->yaw_rate_kd_2->value() / YAW_RATE_PID_SCALE));
    sendYawRatePIDParam();
}


// Roll, pitch, yaw Setpoints
void MainWindow::sendSetPoints()
{
    float data[3] = {ui->lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat(), ui->lineEdit_5->text().toFloat()};
    qDebug() << "Set point changed: " << ui->lineEdit_3->text().toFloat() << ui->lineEdit_4->text().toFloat() << ui->lineEdit_5->text().toFloat();
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x00).append(reinterpret_cast<const char*>(data),sizeof(float)*3)
        )
    );
}

// Controller off
void MainWindow::on_pushButton_pressed()
{
    cs->SendCommand( Command(0x00, QByteArray() ) );
}

// Controller on
void MainWindow::on_pushButton_4_pressed()
{
    cs->SendCommand( Command(0x01, QByteArray() ) );
}

// Sensor power off
void MainWindow::on_pushButton_3_pressed()
{
    cs->SendCommand( Command(0x02, QByteArray() ) );
}

// Sensor power on
void MainWindow::on_pushButton_2_pressed()
{
    cs->SendCommand( Command(0x03, QByteArray() ) );
}

// Throttle value slidebar
void MainWindow::verticalSlider()
{
    float data[1] = {(float)ui->verticalSlider->value() / 1000.0f};
    ui->lineEdit_2->setText(QString::number(ui->verticalSlider->value() / 1000.0f));
    qDebug() << (float)ui->verticalSlider->value() / 1000.0f;
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*1)
        )
    );
}

// Throttle value textbox
void MainWindow::on_lineEdit_2_returnPressed()
{
    float data[1] = {ui->lineEdit_2->text().toFloat()};
    qDebug() << ui->lineEdit_2->text().toFloat();
    ui->verticalSlider->setValue(ui->lineEdit_2->text().toFloat() * 1000.0f);
    cs->SendCommand(
        Command(0x05,
            QByteArray().append((char)0x01).append(reinterpret_cast<const char*>(data),sizeof(float)*1)
        )
    );
}


// Set Points textbox
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
