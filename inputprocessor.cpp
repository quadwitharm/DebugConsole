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

void InputProcessor::Reset()
{
    if(data != nullptr)delete data;
    data = nullptr;
}

void InputProcessor::GetInput(QByteArray input)
{
    for(int i = 0;i < input.size();++i){
        if(input[i] != (char)0xFF){
            rawbuf.append(input[i]);
        }else{
            ProcessPacket(QByteArray::fromBase64(rawbuf));
            rawbuf.clear();
        }
    }
}

void InputProcessor::ProcessPacket(QByteArray input)
{
#if 1
    qDebug().noquote() << "0x" << input.toHex();
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
            qDebug() << "Wrong packet data, discarded.";
            return;
        }
    }
    char checksum = 0;
    for(int i = 0;i < input.size() - 1;++i){
        checksum += (char)input[i];
    }
    if( input.size() && (char)input[input.size()-1] != checksum ){
        qDebug().noquote() << "Wrong checksum: " << (int)(char)input[input.size()-1] << " - " << (int)checksum;
        return;
    }else if(input.size() == 0){
        return;
    }
    input.resize(input.size()-1);
    QByteArray remain;
    if(data->acceptData(input, remain)){
        data->process();
        delete data;
        data = nullptr;
    }
}


bool CommandReturn::acceptData(const QByteArray &input, QByteArray &remain)
{
    (void)input,(void)remain;
    return true;
}

void CommandReturn::process()
{}

bool ControllerData::acceptData(const QByteArray &input, QByteArray &remain)
{
    auto in = input.begin() + 1;
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
    case RatePIDOut: case StabPIDOut:
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
    case Vertical:
        // Size: 1 * float
        while(content.size() < 4 && in != input.end()){
            content.append(*in++);
        }
        if(content.size() == 4){
            while(in != input.end()){
                remain.append(*in++);
            }
            return true;
        }
        break;
     default: qDebug() << "Something Wrong in ControllerData, discarded.";
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
            emit ip->GotMotorOutput(data);
        case Vertical:
            emit ip->GotVertical(data[0]);
        break;
        default: qDebug() << QString("Something wrong in ControllerData, discarded.");
    }
}

bool DebugData::acceptData(const QByteArray &input, QByteArray &)
{
     ip->DebugOutput(QByteArray(input.data()+1,input.size()-1));
     return true;
}

bool SensorData::acceptData(const QByteArray &input, QByteArray &remain)
{
    auto in = input.begin() + 1;
    if(type == None){
        type = static_cast<decltype(type)>((char)*in++);
    }
    switch (type) {
        case GyroRaw: case AccelRaw: case GryoAngle: case AccelAngle:
        case ComplementFilter: case GyroKalmanFilter: case AccelLowPassFilter:
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
    default: qDebug() << "Something Wrong in SenserData, discarded.";
    };
    return false;
}

void SensorData::process()
{
    const float *data = reinterpret_cast<const float*>(content.data());
    switch(type){
        case GyroRaw:
            emit ip->GotGyroRawRoll(data[0],0);
            emit ip->GotGyroRawPitch(data[1],0);
            emit ip->GotGyroRawYaw(data[2],0);
        break;
        case AccelRaw:
            emit ip->GotAccelRawRoll(data[0],0);
            emit ip->GotAccelRawPitch(data[1],0);
            emit ip->GotAccelRawYaw(data[2],0);
        break;
        case GryoAngle: // Unused
            emit ip->GotGryoAngleRoll(data[0],0);
            emit ip->GotGryoAnglePitch(data[1],0);
            emit ip->GotGryoAngleYaw(data[2],0);
        break;
        case AccelAngle: // Unused
            emit ip->GotAccelAngleRoll(data[0],0);
            emit ip->GotAccelAnglePitch(data[1],0);
            emit ip->GotAccelAngleYaw(data[2],0);
        break;
        case ComplementFilter:
            emit ip->GotComplementFilterRoll(data[0],0);
            emit ip->GotComplementFilterPitch(data[1],0);
            emit ip->GotComplementFilterYaw(data[2],0);
        break;
        case GyroKalmanFilter: // Not yet
            emit ip->GotGyroKalmanFilterRoll(data[0],1);
            emit ip->GotGyroKalmanFilterPitch(data[1],1);
            emit ip->GotGyroKalmanFilterYaw(data[2],1);
        break;
        case AccelLowPassFilter: // Not yet
            emit ip->GotAccelLowPassFilterRoll(data[0],1);
            emit ip->GotAccelLowPassFilterPitch(data[1],1);
            emit ip->GotAccelLowPassFilterYaw(data[2],1);
        break;
        default: qDebug() << "Something Wrong in SenserData, discarded.";
    }
}
