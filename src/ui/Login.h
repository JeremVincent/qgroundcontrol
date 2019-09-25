#include "../DataManager/dbmanager.h"


#ifndef LOGIN_H
#define LOGIN_H

class Login : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString pass READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool connect READ isConnected WRITE connexion NOTIFY connectionAsked)

public:
    explicit Login(QObject *parent = nullptr, DbManager *db = nullptr);
    ~Login();

    QString userName();
    void setUserName(const QString &userName);
    QString password();
    void setPassword(const QString &userName);
    bool isConnected();
    void connexion(bool foo);

signals :
    void userNameChanged();
    void passwordChanged();
    void connectionAsked();

private:
    QObject *item;
    QString username = "";
    QString pass = "";
    DbManager *dbManager;
    bool conn = false;
};

#endif
