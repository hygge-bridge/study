#include <QVector>
#include "AlbumModel.h"
#include "DatabaseManager.h"

AlbumModel::AlbumModel(QObject *parent)
    : QAbstractListModel(parent)
    , mDatabase(DatabaseManager::instance())
    , mAlbums(mDatabase.albumDao.albums())
{

}

void AlbumModel::addAlbum(const Album &album)
{
    int index = mAlbums->size();
    beginInsertRows(QModelIndex(), index, index);
    auto newAlbum = std::make_unique<Album>(album.name());
    mDatabase.albumDao.addAlbum(*newAlbum);
    mAlbums->push_back(std::move(newAlbum));
    endInsertRows();
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > rowCount() || count < 0 || row + count > rowCount()) {
        return false;
    }
    int last = row + count - 1;
    beginRemoveRows(parent, row, last);
    for (int i = row; i <= last; ++i) {
        mDatabase.albumDao.deleteAlbum(mAlbums->at(i)->id());
    }
    mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + last);
    endRemoveRows();
    return true;
}

int AlbumModel::rowCount(const QModelIndex &/*parent*/) const
{
    return mAlbums->size();
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const Album& album = *(mAlbums->at(index.row()));
    switch (role) {
    case IdRole:
        return album.id();
    case NameRole:
    case Qt::DisplayRole:
        return album.name();
    default:
        return QVariant();
    }
}

bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!isIndexValid(index) || role != NameRole || role != Qt::DisplayRole) {
        return false;
    }
    QString name = value.toString();
    mDatabase.albumDao.updateAlbum(Album(name));
    mAlbums->at(index.row())->setName(name);
    emit dataChanged(index, index, QVector<int>(role));
    return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}

bool AlbumModel::isIndexValid(const QModelIndex &index) const
{
    return index.isValid() && index.row() < rowCount();
}
