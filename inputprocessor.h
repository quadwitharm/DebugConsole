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
    SensorData(InputProcessor *ip) : DataType(ip) {}
    bool acceptData(const QByteArray &input,QByteArray &remain);
    void process();
    virtual ~SensorData(){}
};
struct ControllerData : public DataType{
    ControllerData(InputProcessor *ip) : DataType(ip) {}
    bool acceptData(const QByteArray &input,QByteArray &remain);
    void process();
    virtual ~ControllerData(){}
private:
    enum{ MotorOut, RatePIDOut, StabPIDOut, None } type;
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
    void GetInput(QByteArray);
signals:
    void GotControllerRoll(double value, int line);
    void GotControllerPitch(double value, int line);
    void GotControllerYaw(double value, int line);
    void DebugOutput(QByteArray);
private:
    DataType *data;
};

#endif // INPUTPROCESSOR_H
