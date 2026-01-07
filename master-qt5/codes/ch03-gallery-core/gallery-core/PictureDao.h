#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>

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
    QVector<Picture*> picturesInAlbum() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDAO_H
