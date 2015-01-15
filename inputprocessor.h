#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <QObject>
#include <QByteArray>

enum DataOrientation{ COMMAND_RETURN, SENSOR_DATA, FLIGHT_DATA, DEBUG_DATA };
typedef enum DataOrientation DataOrientation;

class InputProcessor;
class DataType{
public:
    DataType(InputProcessor *ip) : ip(ip) {}
    // ret: isDataComplete
    virtual bool acceptData(const QByteArray &input,QByteArray &remain) = 0;
    virtual void process() = 0;
    virtual ~DataType(){}
protected:
    InputProcessor *ip;
};
struct CommandReturn : public DataType{
    CommandReturn(InputProcessor *ip) : DataType(ip) {}
    bool acceptData(const QByteArray &input,QByteArray &remain);
    void process();
    virtual ~CommandReturn(){}
};
struct SensorData : public DataType{
    SensorData(InputProcessor *ip) : DataType(ip), type(None) {}
    bool acceptData(const QByteArray &input,QByteArray &remain);
    void process();
    virtual ~SensorData(){}
    enum{ GyroRaw, AccelRaw, GryoAngle , AccelAngle, ComplementFilter, GyroKalmanFilter, AccelLowPassFilter, None} type;
    QByteArray content;
};
struct ControllerData : public DataType{
    ControllerData(InputProcessor *ip) : DataType(ip), type(None) {}
    bool acceptData(const QByteArray &input,QByteArray &remain);
    void process();
    virtual ~ControllerData(){}
private:
    enum{ MotorOut, RatePIDOut, StabPIDOut, Vertical, None } type;
    QByteArray content;
};
struct DebugData : public DataType{
    DebugData(InputProcessor *ip) : DataType(ip), size(),a(false),b(false){}
    bool acceptData(const QByteArray &input, QByteArray &);
    void process(){}
    virtual ~DebugData(){}
private:
    u_int8_t size[2];
    bool a,b;
    QByteArray content;
};


class InputProcessor : public QObject
{
    Q_OBJECT
public:
    explicit InputProcessor(QObject *parent = 0);
    ~InputProcessor();
public slots:
    void Reset();
    void GetInput(QByteArray);
signals:
    // Controller
    void GotControllerRoll(double value, int line);
    void GotControllerPitch(double value, int line);
    void GotControllerYaw(double value, int line);

    void GotVertical(float value);
    void GotMotorOutput(const float value[]);

    // Debug
    void DebugOutput(QByteArray);

    // Sensor
    void GotGyroRawRoll(double value, int line);
    void GotGyroRawPitch(double value, int line);
    void GotGyroRawYaw(double value, int line);

    void GotAccelRawRoll(double value, int line);
    void GotAccelRawPitch(double value, int line);
    void GotAccelRawYaw(double value, int line);

    void GotGryoAngleRoll(double value, int line);
    void GotGryoAnglePitch(double value, int line);
    void GotGryoAngleYaw(double value, int line);

    void GotAccelAngleRoll(double value, int line);
    void GotAccelAnglePitch(double value, int line);
    void GotAccelAngleYaw(double value, int line);

    void GotComplementFilterRoll(double value, int line);
    void GotComplementFilterPitch(double value, int line);
    void GotComplementFilterYaw(double value, int line);

    void GotGyroKalmanFilterRoll(double value, int line);
    void GotGyroKalmanFilterPitch(double value, int line);
    void GotGyroKalmanFilterYaw(double value, int line);

    void GotAccelLowPassFilterRoll(double value, int line);
    void GotAccelLowPassFilterPitch(double value, int line);
    void GotAccelLowPassFilterYaw(double value, int line);

private:
    DataType *data;
};

#endif // INPUTPROCESSOR_H
