#ifndef DIALOGADDUSER_H
#define DIALOGADDUSER_H

#include <QWidget>
#include "../DataManager/dbmanager.h"
#include <QSqlTableModel>

namespace Ui {
class dialog_add_user;
}

class dialog_add_user : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_add_user(QWidget *parent = nullptr);
    explicit dialog_add_user(QWidget *parent = nullptr, QSqlTableModel *db = nullptr);
    ~dialog_add_user();

public slots:
    void addUser();

private:
    Ui::dialog_add_user *ui;
    QSqlTableModel *db_model;
};

#endif // DIALOGADDUSER_H
