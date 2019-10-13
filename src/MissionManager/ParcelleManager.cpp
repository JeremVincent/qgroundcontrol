#include "ParcelleManager.h"
#include "ui_ParcelleManager.h"
#include "DataManager/DbManager.h"
#include "ComplexMissionItem.h"
#include "SurveyComplexItem.h"
#include <QSqlTableModel>
#include "MissionController.h"
#include <QMap>
#include "Admin/List_file.h"
#include "Admin/GeoportailLink.h"
#include "ShapeFileHelper.h"


extern QString username;
extern DbManager *db;
extern QSqlTableModel *SqlParcelleModel;
extern List_file *speedParam;
extern GeoportailLink *geoportailLink;



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
    toDel = new QList<QString>();
    SqlParcelleModel->setTable("Parcelle");
    SqlParcelleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    QString filtre = QString("owner = \'") + username + QString("\'");
//    qDebug() << filtre;
//    SqlParcelleModel->setFilter(filtre);
    SqlParcelleModel->select();
    SqlParcelleModel->setHeaderData(0, Qt::Horizontal, tr("owner"));
    SqlParcelleModel->setHeaderData(1, Qt::Horizontal, tr("file"));
    SqlParcelleModel->setHeaderData(2, Qt::Horizontal, tr("type"));
    SqlParcelleModel->setHeaderData(3, Qt::Horizontal, tr("id"));

    ui->sqlView->setModel(SqlParcelleModel);

    connect(ui->mission_B, SIGNAL(clicked()), this, SLOT(addToMission()));
    connect(ui->add_B, SIGNAL(clicked()), this, SLOT(requestParcelle()));
    connect(ui->rm_B, SIGNAL(clicked()), this, SLOT(deleteParcelle()));
    connect(ui->save_B, SIGNAL(clicked()), this, SLOT(saveToDb()));
}

ParcelleManager::~ParcelleManager()
{
    delete ui;
}


void ParcelleManager::deleteParcelle() {
    qDebug() << "in userSpace::deleteParcelle";
    QModelIndexList selection = ui->sqlView->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << SqlParcelleModel->record(index.row()).value("parcelleFile").toString();
        toDel->append(SqlParcelleModel->record(index.row()).value("parcelleFile").toString());
        SqlParcelleModel->removeRow(index.row());
    }
}


void ParcelleManager::addToMission() {
    qDebug() << "in userSpace::addToMission";
    QModelIndexList selection = ui->sqlView->selectionModel()->selectedRows();
    QMap<QString, double> *KmlParcelleList= new QMap<QString, double>() ;

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        KmlParcelleList->insert(SqlParcelleModel->record(index.row()).value("parcelleFile").toString(), speedParam->at(SqlParcelleModel->record(index.row()).value("speed").toInt()).toDouble());
    }
    missionControler->insertComplexMissionFromDialog(*KmlParcelleList);
    this->deleteLater();
}

void ParcelleManager::requestParcelle() {

    QString NbIlot = "9583";
    QString APIkey = "0ktrk696j3muq3kxsxw22nya";

    QUrl foo = QUrl("https://wxs.ign.fr/" + APIkey + "/geoportail/wfs?request=GetCapabilities&SERVICE=WFS&VERSION=2.0.0&request=GetFeature&typeName=RPG.2016:parcelles_graphiques&outputFormat=kml&srsname=EPSG:2154&FILTER=%3CFilter%20xmlns=%22http://www.opengis.net/fes/2.0%22%3E%20%3CPropertyIsEqualTo%3E%20%3CValueReference%3Eid_parcel%3C/ValueReference%3E%20%3CLiteral%3E"+ NbIlot +"%3C/Literal%3E%20%3C/PropertyIsEqualTo%3E%20%3C/Filter%3E");

    geoportailLink->requestGeo(foo);
    return;
}

void ParcelleManager::requestFinished(QNetworkReply *reply) {
    qDebug() << "requestFinished";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    //tester if success !

    qDebug() << answer;
    ShapeFileHelper::savePolygonFromGeoportail("foo", answer, 2);

    return;
}


/*void ParcelleManager::closeEvent(QCloseEvent *bar) {
    bar->ignore();
    this->deleteLater();
}*/

void ParcelleManager::saveToDb() {
    for (QList<QString>::iterator i = toDel->begin(); i != toDel->end(); ++i) {
        QFile file ((*i));
        file.remove();
    }
    toDel->clear();
    SqlParcelleModel->submitAll();
}
