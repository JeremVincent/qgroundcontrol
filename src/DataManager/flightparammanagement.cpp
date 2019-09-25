#include "flightparammanagement.h"
#include <QFile>
#include <QMap>

FlightParamManagement::FlightParamManagement()
{
    FlightParam = new QMap<QString, int>();
}

FlightParamManagement::~FlightParamManagement() {
    delete FlightParam;
}

void FlightParamManagement::initFromFile() {
    FlightParam->clear();
    QFile file("FlightParam");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    while (!file.atEnd()) {
        QString line = file.readLine();
        FlightParam->insert(line.split("=")[0], line.split("=")[1].toInt());
    }
}

void FlightParamManagement::saveToFile() {
    QFile file("FlightParam");
    file.resize(0);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QMap<QString, int>::iterator i;
    for (i = FlightParam->begin(); i != FlightParam->end(); ++i) {
        file.write((i.key() + "=" + QString::number(i.value()) + "\n").toUtf8());
    }
}

void FlightParamManagement::alter(const QString key, const int value) {
    FlightParam->remove(key);
    FlightParam->insert(key, value);
}

QMap<QString, int>* FlightParamManagement::getMap() {
    return FlightParam;
}
