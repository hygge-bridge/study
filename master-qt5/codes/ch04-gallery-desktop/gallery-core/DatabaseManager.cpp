#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "DatabaseManager.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}

DatabaseManager::DatabaseManager(const QString& databaseName)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", databaseName)))
    , albumDao(*mDatabase)
    , pictureDao(*mDatabase)
{
    mDatabase->open();

    albumDao.init();
    pictureDao.init();
}


