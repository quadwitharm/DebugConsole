#include "commandsender.h"
#include "serial.h"

CommandSender::CommandSender(QObject *parent, Serial *serial)
 : QObject(parent), serial(serial)
{ }

CommandSender::~CommandSender()
{ }

void CommandSender::SendCommand(Command cmd)
{
    serial->writeToPort(cmd.getDataPacket().data(),cmd.getDataPacket().size());
}

Command::Command(CommandType type, QByteArray arg)
    : type(type),
    argument(arg)
{}

Command::~Command()
{ }

QByteArray Command::getDataPacket()
{
    QByteArray ret;
    ret.append( static_cast<char>(this->type) );
    ret.append( this->argument );
    qDebug().noquote() << "Command send:" << ret.toHex();
    return ret;
}

DebugCommand::DebugCommand(QString str)
    :Command(0xFF, QByteArray().append(str.size() >> 8).append(str.size()).append(str))
{  }
