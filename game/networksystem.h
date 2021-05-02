#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include<QTcpSocket>

class NetworkSystem : public QTcpSocket
{
    Q_OBJECT


public:
    explicit NetworkSystem(const QString &host, const int port, QObject *parent = nullptr);

    void requestConnect(const QString &playerID);
    void requestMove(int x,int y);

signals:
    void joinPlayerCommand(QString playerId,QString playerName);
    void spawnPlayerCommand(QString playerId,int x,int y);
    void movePlayerCommand(QString playerId,int x,int y);
    void killPlayerCommand(QString playerId);
    void leavePlayerCommand(QString playerId);

private:
    void packageIntepreterMain(const QString &pkg);
    void GetToken(const QString &get);
    QString Having;

};

#endif // NETWORKSYSTEM_H
