#ifndef SIGNALLINE_H
#define SIGNALLINE_H

#include <QObject>
#include <QQueue>
#include <QVector>
#include "qcustomplot.h"

class PlotHelper : public QObject
{
    Q_OBJECT
public:
    explicit PlotHelper(int enableLine,QObject *parent = 0);
    ~PlotHelper();

    void setTimeRange(double);
    void setFrequency(double);
    void setValueRange(double);
    void NewData(double value,int line);
    void NextFrame(double offset);
    void Reset(QCustomPlot *qcp);

private:
    double rightPoint, timeRange, valueRange, frequency;
    QVector<bool> lineReady;
    int enableLine;
    QCustomPlot *qcp;
};

#endif // SIGNALLINE_H
