#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>

#ifndef GEOPORTAILLINK_H
#define GEOPORTAILLINK_H

class GeoportailLink : public QObject
{
    Q_OBJECT

public:
    explicit GeoportailLink();
    ~GeoportailLink();

    void requestGeo(QUrl url);

private:
    QNetworkAccessManager* _qnam;
    QNetworkRequest request;
};

#endif // GEOPORTAILLINK_H
