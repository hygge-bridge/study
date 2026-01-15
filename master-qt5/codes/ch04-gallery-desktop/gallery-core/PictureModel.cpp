#include "PictureModel.h"
#include "AlbumModel.h"
#include "DatabaseManager.h"

const int INVALID_ALBUMID = -1;

PictureModel::PictureModel(const AlbumModel& albumModel, QObject *parent)
    : QAbstractListModel(parent)
    , mDatabase(DatabaseManager::instance())
    , mAlbumId(INVALID_ALBUMID)
    , mPictures(new std::vector<std::unique_ptr<Picture>>())
{
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rowIndex= rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    auto newPicture = std::make_unique<Picture>(picture.url());
    mDatabase.pictureDao.addPictureInAlbum(*newPicture, mAlbumId);
    mPictures->push_back(std::move(newPicture));
    endInsertRows();
    return index(rowIndex);
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > rowCount() || count < 0 || row + count > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; ++i) {
        mDatabase.pictureDao.deletePicture(mPictures->at(i)->id());
    }
    mPictures->erase(mPictures->begin() + row, mPictures->end() + row + count);
    endRemoveRows();
    return true;
}

int PictureModel::rowCount(const QModelIndex &/*parent*/) const
{
    return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const Picture& picture = *(mPictures->at(index.row()));
    switch (role) {
    case Qt::DisplayRole:
        return picture.url().fileName();
    case FilePathRole:
        return picture.url().toLocalFile();
    case UrlRole:
        return picture.url();
    default:
        return QVariant();
    }

}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UrlRole] = "url";
    roles[FilePathRole] = "filePath";
    return roles;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(albumId);
    endResetModel();
}

void PictureModel::deletePicturesForAlbum()
{
    mDatabase.pictureDao.deletePicturesInAlbum(mAlbumId);
    clearPicturesForAlbum();
}

void PictureModel::clearPicturesForAlbum()
{
    setAlbumId(INVALID_ALBUMID);
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId == INVALID_ALBUMID) {
        mPictures.reset(new std::vector<std::unique_ptr<Picture>>());
        return;
    }
    mPictures = mDatabase.pictureDao.picturesInAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    return index.isValid() && index.row() >= 0 && index.row() < rowCount();
}

