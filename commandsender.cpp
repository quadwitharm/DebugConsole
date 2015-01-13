#include "commandsender.h"
#include "serial.h"

CommandSender::CommandSender(QObject *parent, Serial *serial)
 : QObject(parent), serial(serial)
{
}

CommandSender::~CommandSender()
{

}

void CommandSender::SendCommand(Command &)
{

}

Command::Command(CommandType, QByteArray)
{

}

Command::~Command()
{

}

QByteArray Command::getDataPacket()
{
    QByteArray ret;
    ret.append( static_cast<char>(this->type) );
    ret.append( this->argument );
    return ret;
}
