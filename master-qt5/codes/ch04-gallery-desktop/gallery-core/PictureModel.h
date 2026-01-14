#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>
#include <QVariant>
#include <QModelIndex>
#include "Picture.h"

class AlbumModel;
class DatabaseManager;

class PictureModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    explicit PictureModel(const AlbumModel& albumModel, QObject *parent = nullptr);

    QModelIndex addPicture(const Picture& picture);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setAlbumId(int albumId);

private slots:
    void deletePicturesForAlbum();

private:
    void clearPicturesForAlbum();
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDatabase;
    int mAlbumId;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> mPictures;
};

#endif // PICTUREMODEL_H
