#ifndef SIGNALLINE_H
#define SIGNALLINE_H

#include <QObject>
#include <QQueue>
#include <QVector>
#include "qcustomplot.h"

class SignalLine : public QObject
{
    Q_OBJECT
public:
    explicit SignalLine(QObject *parent = 0);
    void setTimeRange(double);
    void setValueRange(double);
    ~SignalLine();
signals:

public slots:
    void NewData(double offset,double value);
    void Reset(QCustomPlot *qcp);

private:
    double rightPoint, timeRange, valueRange;

    QCustomPlot *qcp;
};

#endif // SIGNALLINE_H
