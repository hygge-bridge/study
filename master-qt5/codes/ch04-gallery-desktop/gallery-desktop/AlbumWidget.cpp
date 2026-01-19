#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"
#include "AlbumModel.h"
#include "ThumbnailProxyModel.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mPictureModel(nullptr)
{
    ui->setupUi(this);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel)
{
    mAlbumModel = albumModel;
    //connect(mAlbumModel, &AlbumModel::modelReset, )
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel *albumSelectionModel)
{
    ui->listView->setSelectionModel(albumSelectionModel);
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel *pictureModel)
{
    mPictureModel = pictureModel;
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel *pictureSelectionModel)
{
    ui->listView->setSelectionModel(pictureSelectionModel);
}
