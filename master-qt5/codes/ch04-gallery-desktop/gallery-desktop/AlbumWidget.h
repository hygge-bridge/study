#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
class AlbumWidget;
}

class AlbumModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);
    void setPictureModel(ThumbnailProxyModel* pictureModel);
    void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

private:
    void addPicture();
    void editAlbum();
    void deleteAlbum();

private:
    Ui::AlbumWidget *ui;
    AlbumModel *mAlbumModel;
    ThumbnailProxyModel *mPictureModel;
};

#endif // ALBUMWIDGET_H
