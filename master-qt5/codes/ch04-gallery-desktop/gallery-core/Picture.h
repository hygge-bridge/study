#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>
#include <QString>
#include "gallery-core_global.h"

class GALLERYCORE_EXPORT Picture
{
public:
    explicit Picture(const QUrl& url);
    explicit Picture(const QString& path = "");

    int id() const;
    void setId(int id);

    int albumId() const;
    void setAlbumId(int albumId);

    QUrl url() const;
    void setUrl(const QUrl &url);

private:
    int mId;
    int mAlbumId;
    QUrl mUrl;
};

#endif // PICTURE_H
