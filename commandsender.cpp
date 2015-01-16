#include "commandsender.h"
#include "serial.h"
#include <iostream>

CommandSender::CommandSender(QObject *parent, Serial *serial)
 : QObject(parent), serial(serial)
{ }

CommandSender::~CommandSender()
{ }

void CommandSender::SendCommand(Command cmd)
{
    auto packet = cmd.getDataPacket();
    qDebug() << "Command send:" << packet.toHex();
    for(int i = 0;i < packet.size();++i){
        serial->writeToPort(packet.data()+i,1);
    }
}

Command::Command(CommandType type, QByteArray arg)
    : type(type),
    argument(arg)
{}

Command::~Command()
{ }

QByteArray Command::getDataPacket()
{
    QByteArray rawcmd;
    rawcmd.append( static_cast<char>(this->type) );
    rawcmd.append( this->argument );
    char checksum = 0;
    for(int i = 0;i < rawcmd.size();++i){
        checksum += rawcmd[i] ;
    }
    rawcmd.append(checksum);
    return rawcmd.toBase64().append((char)0xFF);
}

DebugCommand::DebugCommand(QString str)
    :Command((char)str.toInt(), QByteArray())
{  }
