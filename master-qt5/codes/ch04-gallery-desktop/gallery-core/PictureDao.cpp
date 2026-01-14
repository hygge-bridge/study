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
    query.exec();
    DatabaseManager::debugQuery(query);
}

void PictureDao::deletePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM picture WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

void PictureDao::deletePicturesInAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM picture WHERE albumId = :albumId");
    query.bindValue(":albumId", albumId);
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::unique_ptr<std::vector<std::unique_ptr<Picture>>> PictureDao::picturesInAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> pictures;
    query.prepare("SELECT id, url FROM Picture WHERE albumId = :albumId");
    query.bindValue(":albumId", albumId);
    query.exec();
    DatabaseManager::debugQuery(query);
    while (query.next()) {
        auto picture = std::make_unique<Picture>();
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(albumId);
        picture->setUrl(QUrl::fromLocalFile(query.value("url").toString()));
        pictures->push_back(std::move(picture));
    }
    return pictures;
}
