#include "dialogAddUser.h"
#include "ui_dialogAddUser.h"
#include "../DataManager/dbmanager.h"
#include <QSqlTableModel>

dialog_add_user::dialog_add_user(QWidget *parent) : QWidget(parent), ui(new Ui::dialog_add_user) {
    ui->setupUi(this);
}

dialog_add_user::dialog_add_user(QWidget *parent, QSqlTableModel *db) : QWidget(parent), ui(new Ui::dialog_add_user), db_model(db) {
    qDebug() << "in dialog add user with db";
    ui->setupUi(this);
    connect(ui->addUser, SIGNAL(clicked()), this, SLOT(addUser()));
}

dialog_add_user::~dialog_add_user() {
    delete ui;
}

void dialog_add_user::addUser() {
    QSqlRecord record = db_model->record();
    record.setValue("username", ui->input_user->text());
    record.setValue("password", ui->input_pass->text());
    record.setValue("nom", ui->input_nom->text());
    record.setValue("prenom", ui->input_prenom->text());

    db_model->insertRecord(-1, record);
    this->close();
}
