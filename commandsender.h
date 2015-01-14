#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include <QObject>
#include <QByteArray>

using CommandType = u_int8_t;
class Serial;

class Command
{
public :
    Command(CommandType, QByteArray);
    ~Command();
    QByteArray getDataPacket();
protected:
    CommandType type;
    QByteArray argument;
};

class DebugCommand : public Command{
public:
    DebugCommand(QString str);
};

class CommandSender : public QObject
{
    Q_OBJECT
public:
    explicit CommandSender(QObject *parent, Serial *serial);
    ~CommandSender();

    void SendCommand(Command);
private:
    Serial *serial;
};

#endif // COMMANDSENDER_H
