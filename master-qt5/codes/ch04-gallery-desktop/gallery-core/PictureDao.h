#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <vector>
#include <memory>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
    explicit PictureDao(QSqlDatabase& Database);

    void init() const;
    void addPictureInAlbum(Picture& picture, int albumId) const;
    void deletePicture(int id) const;
    void deletePicturesInAlbum(int albumId) const;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> picturesInAlbum(int albumId) const;

private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDAO_H
