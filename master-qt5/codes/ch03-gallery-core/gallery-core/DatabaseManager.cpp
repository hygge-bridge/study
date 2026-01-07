#include <QSqlDatabase>
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase()))
{

}
