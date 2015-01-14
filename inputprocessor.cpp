#include "inputprocessor.h"
#include <QDebug>

InputProcessor::InputProcessor(QObject *parent)
 : QObject(parent),
    data(nullptr)
{
}

InputProcessor::~InputProcessor()
{
     if(data)delete data;
}

void InputProcessor::GetInput(QByteArray input)
{
    if(data == nullptr){ // New Packet of data
        switch (static_cast<DataOrientation>((char)input[0])) {
        case COMMAND_RETURN:
            data = new CommandReturn(this);
            break;
        case FLIGHT_DATA:
            data = new ControllerData(this);
            break;
        case DEBUG_DATA:
            data = new DebugData(this);
            break;
        default:
            qDebug() << "Magic number error!!";
            /* Something wrong here */
            break;
        }
    }else{
        QByteArray remain;
        if(data->acceptData(input, remain)){
            data->process();
            delete data; data = nullptr;
            if(!remain.isEmpty())
                GetInput(remain);
        }
    }
}


bool CommandReturn::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return false; //TODO: implement
}

void CommandReturn::process()
{

}

bool ControllerData::acceptData(const QByteArray &input, QByteArray &remain)
{
    auto in = input.begin();
    if(type == None){
        type = static_cast<decltype(type)>((char)*in++);
    }
    switch (type) {
    case MotorOut:
        // Size: 4 * float
        while(content.size() < 16 && in != input.end()){
            content.append(*in++);
        }
        if(content.size() == 16){
            while(in != input.end()){
                remain.append(*in++);
            }
            return true;
        }
        break;
    case RatePIDOut:
        // Size: 3 * float
        while(content.size() < 12 && in != input.end()){
            content.append(*in++);
        }
        if(content.size() == 12){
            while(in != input.end()){
                remain.append(*in++);
            }
            return true;
        }
        break;
    case StabPIDOut:
        // Size: 3 * float
        while(content.size() < 12 && in != input.end()){
            content.append(*in++);
        }
        if(content.size() == 12){
            while(in != input.end()){
                remain.append(*in++);
            }
            return true;
        }
        break;
    default: while(1);
    };
    return false;
}

void ControllerData::process()
{
    const float *data = reinterpret_cast<const float*>(content.data());
    switch(type){
        case RatePIDOut:
            emit ip->GotControllerRoll(data[0],0);
            emit ip->GotControllerPitch(data[1],0);
            emit ip->GotControllerYaw(data[2],0);
        break;
        case StabPIDOut:
            emit ip->GotControllerRoll(data[0],1);
            emit ip->GotControllerPitch(data[1],1);
            emit ip->GotControllerYaw(data[2],1);
        break;
        case MotorOut: break;

    }
}

bool DebugData::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return false; //TODO: implement
}

void DebugData::process()
{

}
