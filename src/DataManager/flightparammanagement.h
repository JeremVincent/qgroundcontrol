#ifndef FLIGHTPARAMMANAGEMENT_H
#define FLIGHTPARAMMANAGEMENT_H

#include <QStringListModel>
#include <QString>


class FlightParamManagement
{
public:
    FlightParamManagement();
    ~FlightParamManagement();
    void saveToFile();
    void initFromFile();
    void alter(const QString key, const int value);
    QMap<QString, int>* getMap();

private:
    QMap <QString, int> *FlightParam;
};

#endif // FLIGHTPARAMMANAGEMENT_H
