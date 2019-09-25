#include "geoportailmanager.h"

#include <QObject>
#include <QNetworkReply>

GeoportailManager::GeoportailManager() {
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

GeoportailManager::~GeoportailManager() {
    delete manager;
}

void GeoportailManager::sendRequest() {
    request.setUrl(QUrl("http://url"));
    manager->get(request);

}

void GeoportailManager::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    QString answer = reply->readAll();
    qDebug() << answer;
}
