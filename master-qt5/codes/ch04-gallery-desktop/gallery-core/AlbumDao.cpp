#include <QSqlQuery>
#include <QVariant>
#include "AlbumDao.h"
#include "Album.h"
#include "DatabaseManager.h"

AlbumDao::AlbumDao(QSqlDatabase &database)
    : mDatabase(database)
{

}

void AlbumDao::init() const
{
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS album (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name VARCHAR(255) NOT NULL
        )
    )";

    QSqlQuery query(mDatabase);
    query.exec(createTableSQL);
}

void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO album (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
    DatabaseManager::debugQuery(query);
}

void AlbumDao::deleteAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM album WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE album SET name = :name WHERE id = :id");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const
{
    QSqlQuery query(mDatabase);
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums;
    query.exec("SELECT id, name FROM album");
    DatabaseManager::debugQuery(query);
    while (query.next()) {
        auto album = std::make_unique<Album>();
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        albums->push_back(std::move(album));
    }
    return albums;
}
