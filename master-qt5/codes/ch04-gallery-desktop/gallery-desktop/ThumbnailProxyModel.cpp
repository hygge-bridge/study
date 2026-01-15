#include "ThumbnailProxyModel.h"

constexpr int THUMBNAIL_SIZE = 300;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent)
    : QIdentityProxyModel(parent)
    , mThumbnails()
{

}

ThumbnailProxyModel::~ThumbnailProxyModel()
{
    clearThumbnails();
}

QVariant ThumbnailProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && (index.row() < 0 || index.row() >=rowCount())) {
        return QVariant();
    }
    if (role != Qt::DecorationRole) {
        return QIdentityProxyModel::data(index, role);
    }
    auto filePath = index.model()->data(index, PictureModel::FilePathRole).toString();
    return *mThumbnails[filePath];
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    connect(sourceModel, &QAbstractItemModel::modelReset, [this]{ reloadThumbnails(); });
    connect(sourceModel, &QAbstractItemModel::rowsInserted, [this](const QModelIndex &/*parent*/, int first, int last){
        generateThumbnails(first, last);
    });
}

PictureModel *ThumbnailProxyModel::pictureModel() const
{
    return static_cast<PictureModel*>(sourceModel());
}

void ThumbnailProxyModel::reloadThumbnails()
{
    clearThumbnails();
    generateThumbnails(0, rowCount() - 1);
}

void ThumbnailProxyModel::generateThumbnails(int first, int last)
{
    for (int i = first; i <= last; ++i) {
        auto filePath = QIdentityProxyModel::data(index(i, 0), PictureModel::FilePathRole).toString();
        QPixmap pixmap(filePath);
        QPixmap* thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE, THUMBNAIL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mThumbnails[filePath] = thumbnail;
    }
}

void ThumbnailProxyModel::clearThumbnails()
{
    qDeleteAll(mThumbnails);
    mThumbnails.clear();
}
