#include "userSpace.h"
#include "ui_userSpace.h"
#include "../DataManager/dbmanager.h"
#include "../DataManager/flightparammanagement.h"
#include "Login.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include "dialogAddUser.h"


extern FlightParamManagement *fpara;

userSpace::userSpace(QWidget *parent) : QWidget(parent), ui(new Ui::userSpace) {
    ui->setupUi(this);
}

userSpace::userSpace(QWidget *parent, QString *username, DbManager *db) : QWidget(parent), username(username), ui(new Ui::userSpace), db(db) {
    ui->setupUi(this);

    SqlParcelleModel = new QSqlTableModel(this, db->getDB());
    SqlParcelleModel->setTable("Parcelle");
    SqlParcelleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString filtre = QString("owner = \'") + username + QString("\'");
    qDebug() << filtre;
    SqlParcelleModel->setFilter(filtre);
    SqlParcelleModel->select();
    SqlParcelleModel->setHeaderData(0, Qt::Horizontal, tr("owner"));
    SqlParcelleModel->setHeaderData(1, Qt::Horizontal, tr("polygon"));
    SqlParcelleModel->setHeaderData(2, Qt::Horizontal, tr("type"));
    SqlParcelleModel->setHeaderData(3, Qt::Horizontal, tr("id"));

    SqlMissionModel = new QSqlTableModel(this, db->getDB());
    SqlMissionModel->setTable("Mission");
    SqlMissionModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    SqlMissionModel->setFilter(filtre);
    SqlMissionModel->select();
    SqlMissionModel->setHeaderData(0, Qt::Horizontal, tr("owner"));
    SqlMissionModel->setHeaderData(1, Qt::Horizontal, tr("ordre"));
    SqlMissionModel->setHeaderData(2, Qt::Horizontal, tr("id"));


    ui->list_Mission->setModel(SqlMissionModel);
    ui->list_Parcelle->setModel(SqlParcelleModel);
    ui->inputH->setText(QString::number(fpara->getMap()->value("alertH")));
    ui->inputV->setText(QString::number(fpara->getMap()->value("alertV")));

    ui->quickWidget->setSource(QUrl::fromLocalFile("testMap.qml"));
    ui->quickWidget->show();

    connect(ui->parcelleB_create, SIGNAL(clicked()), this, SLOT(addParcelle()));
    connect(ui->parcelleB_mod, SIGNAL(clicked()), this, SLOT(saveParcelle()));
    connect(ui->parcelleB_delete, SIGNAL(clicked()), this, SLOT(deleteParcelle()));
    connect(ui->missionB_create, SIGNAL(clicked()), this, SLOT(addMission()));
    connect(ui->missionB_mod, SIGNAL(clicked()), this, SLOT(saveMission()));
    connect(ui->missionB_delete, SIGNAL(clicked()), this, SLOT(deleteMission()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFlightParam()));

}



void userSpace::addParcelle() {
    qDebug() << "in userSpace::addParcelle";
    dialog_add_user* add_widget = new dialog_add_user(nullptr, SqlParcelleModel);
    add_widget->show();
}

void userSpace::saveParcelle() {
    qDebug() << "in userSpace::saveParcelle";
    SqlParcelleModel->submitAll();
}

void userSpace::deleteParcelle() {
    qDebug() << "in userSpace::deleteParcelle";
    QModelIndexList selection = ui->list_Parcelle->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        SqlParcelleModel->removeRow(index.row());
    }
}

void userSpace::addMission() {
    qDebug() << "in userSpace::addMission";
    dialog_add_user* add_widget = new dialog_add_user(nullptr, SqlMissionModel);
    add_widget->show();
}

void userSpace::saveMission() {
    qDebug() << "in userSpace::saveMission";
    SqlMissionModel->submitAll();
}

void userSpace::deleteMission() {
    qDebug() << "in userSpace::deleteMission";
    QModelIndexList selection = ui->list_Mission->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        SqlMissionModel->removeRow(index.row());
    }
}

void userSpace::saveFlightParam() {
    int alertH = ui->inputH->text().toInt();
    int alertV = ui->inputV->text().toInt();
    if(0<alertH && 0<alertV) {
        fpara->alter("alertH", alertH);
        fpara->alter("alertV", alertV);
        fpara->saveToFile();
    }
    else
        QMessageBox::information(this, "Input Error", "A Flight Param is not valid");

}


userSpace::~userSpace()
{
    delete ui;
}
