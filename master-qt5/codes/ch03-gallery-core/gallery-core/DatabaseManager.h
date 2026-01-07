#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include "gallery-core_global.h"
#include "AlbumDao.h"
#include "PictureDao.h"

class QSqlDatabase;
class QSqlQuery;

const QString DATABASE_NAME = "gallery.db";

class GALLERYCORE_EXPORT DatabaseManager
{
public:
    static DatabaseManager& instance();
    static void debugQuery(const QSqlQuery& query);
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& databaseName = DATABASE_NAME);
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    QSqlDatabase* mDatabase;

public:
    const AlbumDao albumDao;
    const PictureDao pictureDao;
};

#endif // DATABASEMANAGER_H
