#include <QSqlQuery>
#include <QVariant>
#include <QUrl>
#include "PictureDao.h"
#include "Picture.h"
#include "DatabaseManager.h"

PictureDao::PictureDao(QSqlDatabase &Database)
    : mDatabase(Database)
{

}

void PictureDao::init() const
{
    QString sql = "CREATE TABLE IF NOT EXISTS picture ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "albumId INTEGER NOT NULL, "
                      "url TEXT NOT NULL"
                      ")";

    QSqlQuery query(mDatabase);
    query.exec(sql);
    DatabaseManager::debugQuery(query);
}

void PictureDao::addPictureInAlbum(Picture &picture, int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO picture (albumId, url) VALUES (:albumId, :url)");
    query.bindValue(":albumId", albumId);
    query.bindValue(":url", picture.url());
    DatabaseManager::debugQuery(query);
}

void PictureDao::deletePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM picture WHERE id = :id");
    query.bindValue(":id", id);
    DatabaseManager::debugQuery(query);
}

void PictureDao::deletePicturesInAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM picture WHERE albumId = :albumId");
    query.bindValue(":albumId", albumId);
    DatabaseManager::debugQuery(query);
}

QVector<Picture *> PictureDao::picturesInAlbum() const
{
    QSqlQuery query(mDatabase);
    QVector<Picture*> pictures;
    query.exec("SELECT id, albumId, url FROM Picture");
    DatabaseManager::debugQuery(query);
    while (query.next()) {
        Picture* picture = new Picture();
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("albumId").toInt());
        picture->setUrl(QUrl::fromLocalFile(query.value("url").toString()));
        pictures.push_back(picture);
    }
    return pictures;
}
