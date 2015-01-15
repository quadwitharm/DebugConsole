#include "controllerplot.h"
#include "inputprocessor.h"

PlotHelper::PlotHelper(int enableLine, QObject *parent)
    : QObject(parent),
    lineReady(enableLine),
    enableLine(enableLine)
{

// TODO: properly handle enableLine
}

void PlotHelper::setTimeRange(double timeRange)
{
    this->timeRange = timeRange;
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
}

void PlotHelper::setFrequency(double frequency)
{
    this->frequency=frequency;
}

void PlotHelper::setValueRange(double valueRange)
{
    this->valueRange = valueRange;
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    qcp->replot();
}


PlotHelper::~PlotHelper()
{
}

void PlotHelper::NewData(double value, int line)
{
    if(line > enableLine)return;
    qcp->graph(line)->addData(rightPoint, value);
    lineReady[line] = true;
    bool Allready = true;
    for(int i = 0;i < enableLine;++i){
        if(!lineReady[i])Allready = false;
    }
    if(Allready){
        NextFrame(frequency);
        for(int i = 0;i < enableLine;++i){
            lineReady[i] = false;
        }
    }
}

void PlotHelper::NextFrame(double offset)
{
    for(int i = 0;i < enableLine;++i){
        qcp->graph(i)->removeDataBefore(rightPoint - timeRange * 2);
    }
    qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    qcp->replot();
    rightPoint += offset;
}

void PlotHelper::Reset(QCustomPlot *qcp)
{
    this->qcp = qcp;
    rightPoint = 0.0;
    timeRange = 10.0;
    valueRange = 100.0;
    frequency = 1.0 / 60.0;
    this->qcp->clearGraphs();
    for(int i = 0;i < enableLine;++i){
        this->qcp->addGraph();
        this->qcp->graph(i)->addData(rightPoint - timeRange, 0.0);
        this->qcp->graph(i)->addData(rightPoint, 0.0);
    }
    this->qcp->xAxis->setLabel("Time");
    this->qcp->yAxis->setLabel("Degree");
    this->qcp->xAxis->setRange(rightPoint - timeRange, rightPoint);
    this->qcp->yAxis->setRange(0 - valueRange, 0 + valueRange);
    this->qcp->replot();
}
