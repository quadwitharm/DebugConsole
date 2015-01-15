/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"
#include "terminal.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *TabWidget;
    QWidget *consoleTab;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *portSelection;
    QComboBox *baudRateSelection;
    QComboBox *dataBitSelection;
    QComboBox *paritySelection;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QCheckBox *stopBitCheck;
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *clearButton;
    Terminal *terminal;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *lineEdit;
    QPushButton *Send;
    QWidget *plotTab;
    QGridLayout *gridLayout_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *motor1;
    QLabel *motor2;
    QLabel *motor3;
    QLabel *motor4;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_11;
    QSlider *verticalOutput;
    QSlider *verticalSlider;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *Roll;
    QHBoxLayout *horizontalLayout_5;
    QCustomPlot *plotWidget1;
    QHBoxLayout *ControlAxis;
    QSlider *roll_kp;
    QSlider *roll_ki;
    QSlider *roll_kd;
    QFrame *line;
    QSlider *roll_rate_kp;
    QSlider *roll_rate_ki;
    QSlider *roll_rate_kd;
    QDial *SetPoint;
    QWidget *Pitch;
    QHBoxLayout *horizontalLayout_7;
    QCustomPlot *plotWidget2;
    QHBoxLayout *ControlAxis_3;
    QSlider *pitch_kp_3;
    QSlider *pitch_ki_3;
    QSlider *pitch_kd_3;
    QFrame *line_3;
    QSlider *pitch_rate_kp_3;
    QSlider *pitch_rate_ki_3;
    QSlider *pitch_rate_kd_3;
    QDial *SetPoint_3;
    QWidget *Yaw;
    QHBoxLayout *horizontalLayout_6;
    QCustomPlot *plotWidget3;
    QHBoxLayout *ControlAxis_2;
    QSlider *yaw_kp_2;
    QSlider *yaw_ki_2;
    QSlider *yaw_kd_2;
    QFrame *line_2;
    QSlider *yaw_rate_kp_2;
    QSlider *yaw_rate_ki_2;
    QSlider *yaw_rate_kd_2;
    QDial *SetPoint_2;
    QWidget *sensorTab;
    QGridLayout *gridLayout_4;
    QWidget *FilterAngle;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *filterAngleRoll;
    QCustomPlot *filterAnglePitch;
    QCustomPlot *filterAngleYaw;
    QWidget *SensorInput;
    QVBoxLayout *verticalLayout_2;
    QWidget *Gyro;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *GyroRoll;
    QCustomPlot *GyroPitch;
    QCustomPlot *GyroYaw;
    QWidget *Accel;
    QHBoxLayout *horizontalLayout_3;
    QCustomPlot *AccelX;
    QCustomPlot *AccelY;
    QCustomPlot *AccelZ;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1178, 673);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        TabWidget = new QTabWidget(centralWidget);
        TabWidget->setObjectName(QStringLiteral("TabWidget"));
        TabWidget->setMinimumSize(QSize(0, 4));
        consoleTab = new QWidget();
        consoleTab->setObjectName(QStringLiteral("consoleTab"));
        gridLayout = new QGridLayout(consoleTab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(consoleTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        portSelection = new QComboBox(groupBox);
        portSelection->setObjectName(QStringLiteral("portSelection"));

        gridLayout_2->addWidget(portSelection, 0, 1, 1, 1);

        baudRateSelection = new QComboBox(groupBox);
        baudRateSelection->setObjectName(QStringLiteral("baudRateSelection"));

        gridLayout_2->addWidget(baudRateSelection, 2, 1, 1, 1);

        dataBitSelection = new QComboBox(groupBox);
        dataBitSelection->setObjectName(QStringLiteral("dataBitSelection"));

        gridLayout_2->addWidget(dataBitSelection, 3, 1, 1, 1);

        paritySelection = new QComboBox(groupBox);
        paritySelection->setObjectName(QStringLiteral("paritySelection"));

        gridLayout_2->addWidget(paritySelection, 4, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 4, 0, 1, 1);

        stopBitCheck = new QCheckBox(groupBox);
        stopBitCheck->setObjectName(QStringLiteral("stopBitCheck"));

        gridLayout_2->addWidget(stopBitCheck, 5, 0, 1, 2);

        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QStringLiteral("openButton"));

        gridLayout_2->addWidget(openButton, 6, 0, 1, 2);

        closeButton = new QPushButton(groupBox);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        gridLayout_2->addWidget(closeButton, 7, 0, 1, 2);

        clearButton = new QPushButton(groupBox);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        gridLayout_2->addWidget(clearButton, 8, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 3, 1);

        terminal = new Terminal(consoleTab);
        terminal->setObjectName(QStringLiteral("terminal"));

        gridLayout->addWidget(terminal, 0, 1, 1, 1);

        widget_2 = new QWidget(consoleTab);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setBaseSize(QSize(0, 100));
        horizontalLayout_10 = new QHBoxLayout(widget_2);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_10->addWidget(pushButton);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_10->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_10->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_10->addWidget(pushButton_2);


        gridLayout->addWidget(widget_2, 1, 1, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        lineEdit = new QLineEdit(consoleTab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_9->addWidget(lineEdit);

        Send = new QPushButton(consoleTab);
        Send->setObjectName(QStringLiteral("Send"));

        horizontalLayout_9->addWidget(Send);


        gridLayout->addLayout(horizontalLayout_9, 2, 1, 1, 1);

        TabWidget->addTab(consoleTab, QString());
        plotTab = new QWidget();
        plotTab->setObjectName(QStringLiteral("plotTab"));
        gridLayout_3 = new QGridLayout(plotTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget_4 = new QWidget(plotTab);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_12 = new QHBoxLayout(widget_4);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        motor1 = new QLabel(widget_4);
        motor1->setObjectName(QStringLiteral("motor1"));

        horizontalLayout_12->addWidget(motor1);

        motor2 = new QLabel(widget_4);
        motor2->setObjectName(QStringLiteral("motor2"));

        horizontalLayout_12->addWidget(motor2);

        motor3 = new QLabel(widget_4);
        motor3->setObjectName(QStringLiteral("motor3"));

        horizontalLayout_12->addWidget(motor3);

        motor4 = new QLabel(widget_4);
        motor4->setObjectName(QStringLiteral("motor4"));

        horizontalLayout_12->addWidget(motor4);


        gridLayout_3->addWidget(widget_4, 1, 0, 1, 1);

        widget_5 = new QWidget(plotTab);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_11 = new QHBoxLayout(widget_5);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalOutput = new QSlider(widget_5);
        verticalOutput->setObjectName(QStringLiteral("verticalOutput"));
        verticalOutput->setMaximum(1000);
        verticalOutput->setOrientation(Qt::Vertical);

        horizontalLayout_11->addWidget(verticalOutput);

        verticalSlider = new QSlider(widget_5);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setMinimumSize(QSize(32, 0));
        verticalSlider->setContextMenuPolicy(Qt::DefaultContextMenu);
        verticalSlider->setMaximum(1000);
        verticalSlider->setValue(500);
        verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout_11->addWidget(verticalSlider);

        widget = new QWidget(widget_5);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setAutoFillBackground(true);
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Roll = new QWidget(widget);
        Roll->setObjectName(QStringLiteral("Roll"));
        horizontalLayout_5 = new QHBoxLayout(Roll);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        plotWidget1 = new QCustomPlot(Roll);
        plotWidget1->setObjectName(QStringLiteral("plotWidget1"));
        plotWidget1->setMinimumSize(QSize(700, 0));

        horizontalLayout_5->addWidget(plotWidget1);

        ControlAxis = new QHBoxLayout();
        ControlAxis->setSpacing(6);
        ControlAxis->setObjectName(QStringLiteral("ControlAxis"));
        roll_kp = new QSlider(Roll);
        roll_kp->setObjectName(QStringLiteral("roll_kp"));
        roll_kp->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_kp);

        roll_ki = new QSlider(Roll);
        roll_ki->setObjectName(QStringLiteral("roll_ki"));
        roll_ki->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_ki);

        roll_kd = new QSlider(Roll);
        roll_kd->setObjectName(QStringLiteral("roll_kd"));
        roll_kd->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_kd);

        line = new QFrame(Roll);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        ControlAxis->addWidget(line);

        roll_rate_kp = new QSlider(Roll);
        roll_rate_kp->setObjectName(QStringLiteral("roll_rate_kp"));
        roll_rate_kp->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_rate_kp);

        roll_rate_ki = new QSlider(Roll);
        roll_rate_ki->setObjectName(QStringLiteral("roll_rate_ki"));
        roll_rate_ki->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_rate_ki);

        roll_rate_kd = new QSlider(Roll);
        roll_rate_kd->setObjectName(QStringLiteral("roll_rate_kd"));
        roll_rate_kd->setOrientation(Qt::Vertical);

        ControlAxis->addWidget(roll_rate_kd);

        SetPoint = new QDial(Roll);
        SetPoint->setObjectName(QStringLiteral("SetPoint"));
        SetPoint->setMinimum(-180);
        SetPoint->setMaximum(180);
        SetPoint->setPageStep(0);
        SetPoint->setInvertedAppearance(false);
        SetPoint->setInvertedControls(false);

        ControlAxis->addWidget(SetPoint);


        horizontalLayout_5->addLayout(ControlAxis);


        verticalLayout->addWidget(Roll);

        Pitch = new QWidget(widget);
        Pitch->setObjectName(QStringLiteral("Pitch"));
        horizontalLayout_7 = new QHBoxLayout(Pitch);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        plotWidget2 = new QCustomPlot(Pitch);
        plotWidget2->setObjectName(QStringLiteral("plotWidget2"));
        plotWidget2->setMinimumSize(QSize(700, 0));

        horizontalLayout_7->addWidget(plotWidget2);

        ControlAxis_3 = new QHBoxLayout();
        ControlAxis_3->setSpacing(6);
        ControlAxis_3->setObjectName(QStringLiteral("ControlAxis_3"));
        pitch_kp_3 = new QSlider(Pitch);
        pitch_kp_3->setObjectName(QStringLiteral("pitch_kp_3"));
        pitch_kp_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_kp_3);

        pitch_ki_3 = new QSlider(Pitch);
        pitch_ki_3->setObjectName(QStringLiteral("pitch_ki_3"));
        pitch_ki_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_ki_3);

        pitch_kd_3 = new QSlider(Pitch);
        pitch_kd_3->setObjectName(QStringLiteral("pitch_kd_3"));
        pitch_kd_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_kd_3);

        line_3 = new QFrame(Pitch);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        ControlAxis_3->addWidget(line_3);

        pitch_rate_kp_3 = new QSlider(Pitch);
        pitch_rate_kp_3->setObjectName(QStringLiteral("pitch_rate_kp_3"));
        pitch_rate_kp_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_rate_kp_3);

        pitch_rate_ki_3 = new QSlider(Pitch);
        pitch_rate_ki_3->setObjectName(QStringLiteral("pitch_rate_ki_3"));
        pitch_rate_ki_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_rate_ki_3);

        pitch_rate_kd_3 = new QSlider(Pitch);
        pitch_rate_kd_3->setObjectName(QStringLiteral("pitch_rate_kd_3"));
        pitch_rate_kd_3->setOrientation(Qt::Vertical);

        ControlAxis_3->addWidget(pitch_rate_kd_3);

        SetPoint_3 = new QDial(Pitch);
        SetPoint_3->setObjectName(QStringLiteral("SetPoint_3"));
        SetPoint_3->setMinimum(-180);
        SetPoint_3->setMaximum(180);
        SetPoint_3->setPageStep(0);

        ControlAxis_3->addWidget(SetPoint_3);


        horizontalLayout_7->addLayout(ControlAxis_3);


        verticalLayout->addWidget(Pitch);

        Yaw = new QWidget(widget);
        Yaw->setObjectName(QStringLiteral("Yaw"));
        horizontalLayout_6 = new QHBoxLayout(Yaw);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        plotWidget3 = new QCustomPlot(Yaw);
        plotWidget3->setObjectName(QStringLiteral("plotWidget3"));
        plotWidget3->setMinimumSize(QSize(700, 0));

        horizontalLayout_6->addWidget(plotWidget3);

        ControlAxis_2 = new QHBoxLayout();
        ControlAxis_2->setSpacing(6);
        ControlAxis_2->setObjectName(QStringLiteral("ControlAxis_2"));
        yaw_kp_2 = new QSlider(Yaw);
        yaw_kp_2->setObjectName(QStringLiteral("yaw_kp_2"));
        yaw_kp_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_kp_2);

        yaw_ki_2 = new QSlider(Yaw);
        yaw_ki_2->setObjectName(QStringLiteral("yaw_ki_2"));
        yaw_ki_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_ki_2);

        yaw_kd_2 = new QSlider(Yaw);
        yaw_kd_2->setObjectName(QStringLiteral("yaw_kd_2"));
        yaw_kd_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_kd_2);

        line_2 = new QFrame(Yaw);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        ControlAxis_2->addWidget(line_2);

        yaw_rate_kp_2 = new QSlider(Yaw);
        yaw_rate_kp_2->setObjectName(QStringLiteral("yaw_rate_kp_2"));
        yaw_rate_kp_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_rate_kp_2);

        yaw_rate_ki_2 = new QSlider(Yaw);
        yaw_rate_ki_2->setObjectName(QStringLiteral("yaw_rate_ki_2"));
        yaw_rate_ki_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_rate_ki_2);

        yaw_rate_kd_2 = new QSlider(Yaw);
        yaw_rate_kd_2->setObjectName(QStringLiteral("yaw_rate_kd_2"));
        yaw_rate_kd_2->setOrientation(Qt::Vertical);

        ControlAxis_2->addWidget(yaw_rate_kd_2);

        SetPoint_2 = new QDial(Yaw);
        SetPoint_2->setObjectName(QStringLiteral("SetPoint_2"));
        SetPoint_2->setMinimum(-180);
        SetPoint_2->setMaximum(180);
        SetPoint_2->setPageStep(0);

        ControlAxis_2->addWidget(SetPoint_2);


        horizontalLayout_6->addLayout(ControlAxis_2);


        verticalLayout->addWidget(Yaw);


        horizontalLayout_11->addWidget(widget);

        verticalSlider->raise();
        verticalOutput->raise();
        plotWidget2->raise();
        widget->raise();

        gridLayout_3->addWidget(widget_5, 0, 0, 1, 1);

        TabWidget->addTab(plotTab, QString());
        sensorTab = new QWidget();
        sensorTab->setObjectName(QStringLiteral("sensorTab"));
        gridLayout_4 = new QGridLayout(sensorTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        FilterAngle = new QWidget(sensorTab);
        FilterAngle->setObjectName(QStringLiteral("FilterAngle"));
        verticalLayout_3 = new QVBoxLayout(FilterAngle);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        filterAngleRoll = new QCustomPlot(FilterAngle);
        filterAngleRoll->setObjectName(QStringLiteral("filterAngleRoll"));

        verticalLayout_3->addWidget(filterAngleRoll);

        filterAnglePitch = new QCustomPlot(FilterAngle);
        filterAnglePitch->setObjectName(QStringLiteral("filterAnglePitch"));

        verticalLayout_3->addWidget(filterAnglePitch);

        filterAngleYaw = new QCustomPlot(FilterAngle);
        filterAngleYaw->setObjectName(QStringLiteral("filterAngleYaw"));

        verticalLayout_3->addWidget(filterAngleYaw);


        gridLayout_4->addWidget(FilterAngle, 0, 1, 1, 1);

        SensorInput = new QWidget(sensorTab);
        SensorInput->setObjectName(QStringLiteral("SensorInput"));
        verticalLayout_2 = new QVBoxLayout(SensorInput);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Gyro = new QWidget(SensorInput);
        Gyro->setObjectName(QStringLiteral("Gyro"));
        horizontalLayout_2 = new QHBoxLayout(Gyro);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        GyroRoll = new QCustomPlot(Gyro);
        GyroRoll->setObjectName(QStringLiteral("GyroRoll"));

        horizontalLayout_2->addWidget(GyroRoll);

        GyroPitch = new QCustomPlot(Gyro);
        GyroPitch->setObjectName(QStringLiteral("GyroPitch"));

        horizontalLayout_2->addWidget(GyroPitch);

        GyroYaw = new QCustomPlot(Gyro);
        GyroYaw->setObjectName(QStringLiteral("GyroYaw"));

        horizontalLayout_2->addWidget(GyroYaw);


        verticalLayout_2->addWidget(Gyro);

        Accel = new QWidget(SensorInput);
        Accel->setObjectName(QStringLiteral("Accel"));
        horizontalLayout_3 = new QHBoxLayout(Accel);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        AccelX = new QCustomPlot(Accel);
        AccelX->setObjectName(QStringLiteral("AccelX"));

        horizontalLayout_3->addWidget(AccelX);

        AccelY = new QCustomPlot(Accel);
        AccelY->setObjectName(QStringLiteral("AccelY"));

        horizontalLayout_3->addWidget(AccelY);

        AccelZ = new QCustomPlot(Accel);
        AccelZ->setObjectName(QStringLiteral("AccelZ"));

        horizontalLayout_3->addWidget(AccelZ);


        verticalLayout_2->addWidget(Accel);


        gridLayout_4->addWidget(SensorInput, 0, 0, 1, 1);

        TabWidget->addTab(sensorTab, QString());

        horizontalLayout->addWidget(TabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        TabWidget->setCurrentIndex(1);
        baudRateSelection->setCurrentIndex(12);
        dataBitSelection->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Quadcoptor Debug Console", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        baudRateSelection->clear();
        baudRateSelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "50", 0)
         << QApplication::translate("MainWindow", "75", 0)
         << QApplication::translate("MainWindow", "110", 0)
         << QApplication::translate("MainWindow", "134", 0)
         << QApplication::translate("MainWindow", "150", 0)
         << QApplication::translate("MainWindow", "200", 0)
         << QApplication::translate("MainWindow", "300", 0)
         << QApplication::translate("MainWindow", "600", 0)
         << QApplication::translate("MainWindow", "1200", 0)
         << QApplication::translate("MainWindow", "1800", 0)
         << QApplication::translate("MainWindow", "2400", 0)
         << QApplication::translate("MainWindow", "4800", 0)
         << QApplication::translate("MainWindow", "9600", 0)
         << QApplication::translate("MainWindow", "19200", 0)
         << QApplication::translate("MainWindow", "38400", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "230400", 0)
         << QApplication::translate("MainWindow", "460800", 0)
         << QApplication::translate("MainWindow", "500000", 0)
         << QApplication::translate("MainWindow", "576000", 0)
         << QApplication::translate("MainWindow", "921600", 0)
         << QApplication::translate("MainWindow", "1000000", 0)
         << QApplication::translate("MainWindow", "1152000", 0)
         << QApplication::translate("MainWindow", "1500000", 0)
         << QApplication::translate("MainWindow", "2000000", 0)
         << QApplication::translate("MainWindow", "2500000", 0)
         << QApplication::translate("MainWindow", "3000000", 0)
         << QApplication::translate("MainWindow", "3500000", 0)
         << QApplication::translate("MainWindow", "4000000", 0)
        );
        dataBitSelection->clear();
        dataBitSelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        paritySelection->clear();
        paritySelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "none", 0)
         << QApplication::translate("MainWindow", "even", 0)
         << QApplication::translate("MainWindow", "odd", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Port", 0));
        label_2->setText(QApplication::translate("MainWindow", "Baud Rate", 0));
        label_3->setText(QApplication::translate("MainWindow", "Data bits", 0));
        label_4->setText(QApplication::translate("MainWindow", "Parity", 0));
        stopBitCheck->setText(QApplication::translate("MainWindow", "2 Stop bit", 0));
        openButton->setText(QApplication::translate("MainWindow", "Open", 0));
        closeButton->setText(QApplication::translate("MainWindow", "Close", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Controller off", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Controller on", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Sensor power off", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Sensor power on", 0));
        Send->setText(QApplication::translate("MainWindow", "Send", 0));
        TabWidget->setTabText(TabWidget->indexOf(consoleTab), QApplication::translate("MainWindow", "Console", 0));
        motor1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        motor2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        motor3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        motor4->setText(QApplication::translate("MainWindow", "TextLabel", 0));
#ifndef QT_NO_STATUSTIP
        SetPoint->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        TabWidget->setTabText(TabWidget->indexOf(plotTab), QApplication::translate("MainWindow", "Plot", 0));
        TabWidget->setTabText(TabWidget->indexOf(sensorTab), QApplication::translate("MainWindow", "Sensor", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
