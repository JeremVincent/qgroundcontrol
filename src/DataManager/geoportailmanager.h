#ifndef GEOPORTAILMANAGER_H
#define GEOPORTAILMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

class GeoportailManager : QObject
{
    Q_OBJECT
public:
    GeoportailManager();
    ~GeoportailManager();
    void sendRequest();

private slots:
    void managerFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};

#endif // GEOPORTAILMANAGER_H
