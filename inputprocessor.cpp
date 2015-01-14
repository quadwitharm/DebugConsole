#include "inputprocessor.h"
#include <QDebug>

InputProcessor::InputProcessor(QObject *parent)
 : QObject(parent),
    idata(nullptr)
{
}

InputProcessor::~InputProcessor()
{
     if(idata)delete idata;
}

void InputProcessor::GetInput(QByteArray input)
{
    if(idata == nullptr){ // New Packet of data
        idata = new InputData(static_cast<DataOrientation>((char)input[0]));
    }else{
        QByteArray remain;
        idata->acceptData(input, remain);
        if(idata->isDataComplete() && !remain.isEmpty()){
            emit this->PacketReceived(*idata);
            delete idata;
            idata = nullptr;
            GetInput(remain);
        }
    }
}

InputData::InputData(DataOrientation dataOrientation)
{
    switch (dataOrientation) {
    case COMMAND_RETURN:
        data = new CommandReturn();
        break;
    case FLIGHT_DATA:
        data = new FlightData;
        break;
    case DEBUG_DATA:
        data = new DebugData;
        break;
    default:
        /* Something wrong here */
        break;
    }
    dataComplete = false;
}

void InputData::acceptData(const QByteArray &input, QByteArray &remain)
{
    if(data->acceptData(input,remain))
        dataComplete = true;
}
bool InputData::isDataComplete()
{
    return dataComplete;
}

InputData::~InputData()
{
    delete data;
}


bool CommandReturn::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return false; //TODO: implement
}

bool FlightData::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return false; //TODO: implement
}

bool DebugData::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return false; //TODO: implement
}
