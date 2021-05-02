#include <QString>
#include "networksystem.h"
#include <QByteArray>

NetworkSystem::NetworkSystem(const QString &host, const int port, QObject *parent) :
    QTcpSocket(parent)
{
    this->connectToHost(host,port);
    connect(this,&QTcpSocket::readyRead,[this](){
        GetToken(QString(this->readAll()));
    });
}

void NetworkSystem::requestConnect(const QString &playerID)
{
    write(playerID.toLatin1().data());
    write("\n",1);
}

void NetworkSystem::requestMove(int x, int y)
{
    write(QString("MOVE %2 %3\n").arg(x).arg(y).toLatin1());
}

void NetworkSystem::packageIntepreterMain(const QString &msg)
{
    qDebug()<<"NetworkSystem: "<<msg;
    auto sl =  msg.split(':');
    if(sl.size()<2){
        return;
    }
    auto &&sender = sl[0];
    auto &&instructions = sl[1].split(' ');
    if(instructions[0]=="JOIN"){
        emit addPlayerCommand(sender, instructions[1], instructions[2].toInt(),instructions[3].toInt());
    }else if (instructions[0] =="LEAVE"){
        emit deletePlayerCommand(sender);
    }else if(instructions[0]=="MOVE"){
        emit movePlayerCommand(sl[0], instructions[1].toInt(),instructions[2].toInt());
    }else{
        qDebug()<<"Bad msg: "<<msg;
    }
}

void NetworkSystem::GetToken(const QString &get){
    Having+=get;
    QStringList list = Having.split("\n");
    int sz = list.size();
    if(sz>1){
        for(int i=0;i<sz-1;i++){
            packageIntepreterMain(list[i]);
        }
        Having = list.back();
    }
}
