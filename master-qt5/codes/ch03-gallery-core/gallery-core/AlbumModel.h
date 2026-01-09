#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>
#include <QVariant>
#include <QModelIndex>
#include "Album.h"
#include "gallery-core_global.h"

class DatabaseManager;

class GALLERYCORE_EXPORT AlbumModel : public QAbstractListModel
{
public:
    enum Role {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    explicit AlbumModel(QObject *parent = nullptr);

    void addAlbum(const Album& album);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDatabase;
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> mAlbums;
};

#endif // ALBUMMODEL_H
