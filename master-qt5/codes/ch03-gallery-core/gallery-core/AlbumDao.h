#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <vector>
#include <memory>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
    explicit AlbumDao(QSqlDatabase& database);

    void init() const;
    void addAlbum(Album& album) const;
    void deleteAlbum(int id) const;
    void updateAlbum(const Album& album) const;
    std::vector<std::unique_ptr<Album>> albums() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H
