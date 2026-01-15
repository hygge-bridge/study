#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QString>
#include <QPixmap>
#include <QHash>
#include "PictureModel.h"

class ThumbnailProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit ThumbnailProxyModel(QObject* parent = nullptr);
    ~ThumbnailProxyModel();

    QVariant data(const QModelIndex &index, int role) const override;
    void setSourceModel(QAbstractItemModel *sourceModel) override;
    PictureModel* pictureModel() const;

private:
    void reloadThumbnails();
    void generateThumbnails(int first, int last);
    void clearThumbnails();

private:
    QHash<QString, QPixmap*> mThumbnails;
};

#endif // THUMBNAILPROXYMODEL_H
