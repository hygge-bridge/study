#include "ThumbnailProxyModel.h"

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent)
    : QIdentityProxyModel(parent)
    , mThumbnails()
{

}
