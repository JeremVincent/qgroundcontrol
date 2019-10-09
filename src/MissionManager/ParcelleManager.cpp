#include "ParcelleManager.h"
#include "ui_ParcelleManager.h"
//#include "DbManager.h"
#include "ComplexMissionItem.h"
#include "SurveyComplexItem.h"
#include <QSqlTableModel>
#include "MissionController.h"


extern QString username;
//extern DbManager *db;



ParcelleManager::ParcelleManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParcelleManager)
{
    ui->setupUi(this);
}


ParcelleManager::ParcelleManager(QWidget *parent, MissionController *missionControler) :
    QDialog(parent),
    ui(new Ui::ParcelleManager),
    missionControler(missionControler)
{
    ui->setupUi(this);
//    SqlParcelleModel = new QSqlTableModel(this, db->getDB());
//    SqlParcelleModel->setTable("Parcelle");
//    SqlParcelleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    QString filtre = QString("owner = \'") + username + QString("\'");
//    qDebug() << filtre;
//    SqlParcelleModel->setFilter(filtre);
//    SqlParcelleModel->select();
//    SqlParcelleModel->setHeaderData(0, Qt::Horizontal, tr("owner"));
//    SqlParcelleModel->setHeaderData(1, Qt::Horizontal, tr("polygon"));
//    SqlParcelleModel->setHeaderData(2, Qt::Horizontal, tr("type"));
//    SqlParcelleModel->setHeaderData(3, Qt::Horizontal, tr("id"));
}

ParcelleManager::~ParcelleManager()
{
    delete ui;
}


void ParcelleManager::deleteParcelle() {
    qDebug() << "in userSpace::deleteParcelle";
    QModelIndexList selection = ui->DBwidget->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        SqlParcelleModel->removeRow(index.row());
    }
}


void ParcelleManager::addToMission() {
    qDebug() << "in userSpace::addToMission";
    QModelIndexList selection = ui->DBwidget->selectionModel()->selectedRows();
    QList<QString> *KmlParcelleList= new QList<QString>() ;

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        KmlParcelleList->append("foo"); // ici il faudra mettre le path
    }

    missionControler->insertComplexMissionFromDialog(*KmlParcelleList);
}

void ParcelleManager::showParcelleManager(MissionController *missionControler) {
    ParcelleManager* parcelleManager = new ParcelleManager(nullptr,missionControler);
    parcelleManager->exec();

}

void ParcelleManager::closeEvent(QCloseEvent *bar)
{
    // Do something
    this->close();
}
