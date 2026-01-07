#include "Picture.h"

Picture::Picture(const QUrl& url)
    : mId(-1)
    , mAlbumId(-1)
    , mUrl(url)
{

}

Picture::Picture(const QString& path)
    : Picture(QUrl::fromLocalFile(path))
{

}

int Picture::id() const
{
    return mId;
}

void Picture::setId(int id)
{
    mId = id;
}

int Picture::albumId() const
{
    return mAlbumId;
}

void Picture::setAlbumId(int albumId)
{
    mAlbumId = albumId;
}

QUrl Picture::url() const
{
    return mUrl;
}

void Picture::setUrl(const QUrl &url)
{
    mUrl = url;
}
