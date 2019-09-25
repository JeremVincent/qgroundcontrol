#ifndef USER_H
#define USER_H

#include <QWidget>
#include "../DataManager/dbmanager.h"
#include <QSqlTableModel>

namespace Ui {
class userSpace;
}

class userSpace : public QWidget
{
    Q_OBJECT

public:
    explicit userSpace(QWidget *parent = nullptr);
    explicit userSpace(QWidget *parent = nullptr, QString *username = nullptr, DbManager *db = nullptr);
    ~userSpace();

public slots:
    void addParcelle();
    void saveParcelle();
    void deleteParcelle();
    void addMission();
    void saveMission();
    void deleteMission();
    void saveFlightParam();

private:
    QString *username;
    Ui::userSpace *ui;
    DbManager *db;
    QSqlTableModel *SqlParcelleModel;
    QSqlTableModel *SqlMissionModel;

};

#endif // USER_H
