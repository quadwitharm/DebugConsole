#ifndef SIGNALLINE_H
#define SIGNALLINE_H

#include <QObject>
#include <QQueue>
#include <QVector>
#include "qcustomplot.h"

class ControllerPlot : public QObject
{
    Q_OBJECT
public:
    explicit ControllerPlot(QObject *parent = 0);
    ~ControllerPlot();

    void setTimeRange(double);
    void setValueRange(double);
    void NewData(double value,int line);
    void NextFrame(double offset);
    void Reset(QCustomPlot *qcp);

private:
    double rightPoint, timeRange, valueRange;
    bool line0, line1;
    QCustomPlot *qcp;
};

#endif // SIGNALLINE_H
