#include <QInputDialog>
#include "AlbumListWidget.h"
#include "ui_AlbumListWidget.h"
#include "AlbumModel.h"

AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget),
    mAlbumModel(new AlbumModel(this))
{
    ui->setupUi(this);
    connect(ui->createButton, &QPushButton::clicked, this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
    delete ui;
}

void AlbumListWidget::setModel(AlbumModel *model)
{
    mAlbumModel = model;
    ui->listView->setModel(mAlbumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->listView->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
    if (mAlbumModel == nullptr) { return; }
    bool ok = false;
    QString name = QInputDialog::getText(this, "Create a album", "Album name", QLineEdit::Normal, "album name", &ok);
    if (ok && !name.isEmpty()) {
        Album newAlbum(name);
        QModelIndex index = mAlbumModel->addAlbum(newAlbum);
        ui->listView->setCurrentIndex(index);
    }

}
