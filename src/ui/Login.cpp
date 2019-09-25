#include "Login.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <QMessageBox>
#include <QQuickView>
#include <QCryptographicHash>
#include "../DataManager/dbmanager.h"
#include "admin.h"
#include "userSpace.h"
#include "AppSettings.h"
#include "QGCApplication.h"
#include "QGCToolbox.h"

extern QString username;

Login::Login(QObject *parent, DbManager *db) : QObject(parent), dbManager(db)
{
//    QQuickView view(QUrl::fromLocalFile("qrc:/qml/PlanView.qml"));
//    QObject item = new QObject()
//    QObject item = view.rootObject()->findChild<QObject*>("dialog_connect");

//    QObject::connect(item, SIGNAL(connect_signal()), this, SLOT(connection()));
    qDebug() << "down" ;
}

Login::~Login()
{
}

QString Login::userName()
{
    return username;
}

void Login::setUserName(const QString &user)
{
    if (username == user)
        return;

    username = user;
    emit userNameChanged();
}


QString Login::password()
{
    return pass;
}

void Login::setPassword(const QString &pass)
{
    if (this->pass == pass)
        return;

    this->pass = pass;
    emit passwordChanged();
}



bool Login::connection() {
    qDebug() << "in connection";
    if (username == "") return false;
    QString mdp = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha3_256);
    qDebug() << mdp;
    QString mdp_base = dbManager->getPassword(username);
    if(mdp_base.compare(mdp) == 0) {
        qDebug() << "true";
        if (username.compare("admin") == 0) {
            admin* admin_widget = new admin(nullptr, dbManager);
            admin_widget->show();
        }
        else {
//            userSpace* user_widget = new userSpace(nullptr, &login, dbManager);
//            user_widget->show();

        }
        return true;
    }
    else {
        qDebug() << "false";
        QMessageBox::information(nullptr, "login error", "Wrong combinaison of login / password");

        return false;
    }
}
