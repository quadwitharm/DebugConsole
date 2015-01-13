#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <QObject>
#include <QByteArray>

enum DataOrientation{ COMMAND_RETURN, FLIGHT_DATA, DEBUG_DATA };
typedef enum DataOrientation DataOrientation;

struct DataType{
    // ret: isDataComplete
    virtual bool acceptData(const QByteArray &input,QByteArray &remain) = 0;
    virtual ~DataType(){}
};
struct CommandReturn : DataType{
    bool acceptData(const QByteArray &input,QByteArray &remain);
    virtual ~CommandReturn(){}
};
struct FlightData : DataType{
    bool acceptData(const QByteArray &input,QByteArray &remain);
    virtual ~FlightData(){}
};
struct DebugData : DataType{
    bool acceptData(const QByteArray &input,QByteArray &remain);
    virtual ~DebugData(){}
};


class InputData{
public:
    explicit InputData(DataOrientation dataOrientation);
    void acceptData(const QByteArray &input,QByteArray &remain);
    bool isDataComplete();
    void process();
    ~InputData();
private:
    DataType *data;
    bool dataComplete;
};


class InputProcessor : public QObject
{
    Q_OBJECT
public:
    explicit InputProcessor(QObject *parent = 0);
    ~InputProcessor();

public slots:
    void GetInput(QByteArray);
private:
    InputData *idata;
};

#endif // INPUTPROCESSOR_H
