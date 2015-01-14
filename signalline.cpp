#include "signalline.h"

SignalLine::SignalLine(QObject *parent)
    : QObject(parent)
{
}

void SignalLine::setTimeRange(double timeRange)
{
    this->timeRange = timeRange;
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
}

void SignalLine::setValueRange(double valueRange)
{
    this->valueRange = valueRange;
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    qcp->replot();
}

SignalLine::~SignalLine()
{

}

void SignalLine::NewData(double offset, double value)
{
    qcp->graph(0)->addData(rightPoint += offset, value);
    qcp->graph(0)->removeDataBefore(rightPoint - timeRange * 2);
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
}

void SignalLine::Reset(QCustomPlot *qcp)
{
    this->qcp = qcp;
    rightPoint = 0.0;
    timeRange = 10.0;
    valueRange = 100.0;

    this->qcp->clearGraphs();
    this->qcp->addGraph();
    this->qcp->graph(0)->addData(rightPoint - timeRange, 0.0);
    this->qcp->graph(0)->addData(rightPoint, 0.0);
    this->qcp->xAxis->setLabel("Time");
    this->qcp->yAxis->setLabel("Degree");
    this->qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    this->qcp->replot();
}
