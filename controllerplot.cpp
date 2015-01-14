#include "controllerplot.h"
#include "inputprocessor.h"
ControllerPlot::ControllerPlot(QObject *parent)
    : QObject(parent),
    line0(false),
    line1(false)
{
}

void ControllerPlot::setTimeRange(double timeRange)
{
    this->timeRange = timeRange;
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
}

void ControllerPlot::setValueRange(double valueRange)
{
    this->valueRange = valueRange;
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    qcp->replot();
}

ControllerPlot::~ControllerPlot()
{
}

void ControllerPlot::NewData(double value, int line)
{
    if(line != 0 && line != 1)return;
    qcp->graph(line)->addData(rightPoint, value);
    if(line == 0)line0 = true;
    if(line == 1)line1 = true;
    if(line0 && line1){
        NextFrame(1/60);
        line0 = line1 = false;
    }
}

void ControllerPlot::NextFrame(double offset)
{
    qcp->graph(0)->removeDataBefore(rightPoint - timeRange * 2);
    qcp->graph(1)->removeDataBefore(rightPoint - timeRange * 2);
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
    rightPoint += offset;
}

void ControllerPlot::Reset(QCustomPlot *qcp)
{
    this->qcp = qcp;
    rightPoint = 0.0;
    timeRange = 10.0;
    valueRange = 100.0;

    this->qcp->clearGraphs();
    this->qcp->addGraph();
    this->qcp->addGraph();
    this->qcp->graph(0)->addData(rightPoint - timeRange, 0.0);
    this->qcp->graph(0)->addData(rightPoint, 0.0);
    this->qcp->graph(1)->addData(rightPoint - timeRange, 0.0);
    this->qcp->graph(1)->addData(rightPoint, 0.0);
    this->qcp->xAxis->setLabel("Time");
    this->qcp->yAxis->setLabel("Degree");
    this->qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    this->qcp->replot();
}
