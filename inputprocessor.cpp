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

static int consoleDebugColumn = 0;
void InputProcessor::GetInput(QByteArray input)
{
#if 1
    qDebug().noquote() << "0x" << input.toHex() << " : " << qPrintable(input);
#endif
    if(data == nullptr){ // New Packet of data
        switch (static_cast<DataOrientation>((char)input[0])) {
        case COMMAND_RETURN:
            data = new CommandReturn(this);
            break;
        case SENSOR_DATA:
            data = new SensorData(this);
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
        input = QByteArray(input.data()+1,input.size()-1);
    }
    if(input.isEmpty())return;
    QByteArray remain;
    if(data->acceptData(input, remain)){
        data->process();
        delete data; data = nullptr;
        if(!remain.isEmpty())
            GetInput(remain);
    }
}


bool CommandReturn::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return true; //TODO: implement
}

void CommandReturn::process()
{}

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
    default: qDebug() << "Unknown Command!"; while(1);
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
        case MotorOut:
            qDebug() << "Not Handle Motor Output yet";
        break;
        default: qDebug() << QString("Invalid controll data : ") + type + QString("!!!") ; while(1);
    }
}

bool DebugData::acceptData(const QByteArray &input, QByteArray &remain)
{
    QByteArray in = input;
    if(!a && !in.isEmpty()){
        a = true;
        size[0] = in.data()[0];
        in = QByteArray(in.data()+1,in.size()-1);
    }
    if(!b && !in.isEmpty()){
        b = true;
        size[1] = in.data()[0];
        in = QByteArray(in.data()+1,in.size()-1);
    }
    if(a && b){
        u_int16_t Size = (size[1] << 8) + size[0];
        if(content.size() + in.size() < Size){
            content.append(in);
        }else{
            content.append(in.data(),Size-content.size());
            ip->DebugOutput(content);
            qDebug() << content;
            remain.append(remain.data()+Size-content.size(),remain.size()-Size+content.size());
            return true;
        }
        return false;
    }
    return false;
}

bool SensorData::acceptData(const QByteArray &input, QByteArray &remain)
{
    auto in = input.begin();
    if(type == None){
        type = static_cast<decltype(type)>((char)*in++);
    }
    switch (type) {
        case GyroRaw: case AccelRaw: case GryoAngle: case AccelAngle:
        case ComplementFilter: case GyroKalmanFilter: case AccelLowPassFilter:
        // Size: 3 * float
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
    default: qDebug() << "Unknown Command!"; while(1);
    };
    return false;
}

void SensorData::process()
{
    const float *data = reinterpret_cast<const float*>(content.data());
    switch(type){
        case GyroRaw: case AccelRaw: case GryoAngle: case AccelAngle:
        case ComplementFilter: case GyroKalmanFilter: case AccelLowPassFilter:
            emit ip->GotControllerRoll(data[0],0);
            emit ip->GotControllerPitch(data[1],0);
            emit ip->GotControllerYaw(data[2],0);
        break;
        default: qDebug() << QString("Invalid controll data : ") + type + QString("!!!") ; while(1);
    }
}
