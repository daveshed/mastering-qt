#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "picture.h"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORE_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PictureRole {
        FilePathRole = Qt::UserRole + 1,
    };
    PictureModel(const AlbumModel& albumModel, QObject* parent = 0);
    QModelIndex addPicture(const Picture& picture);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
};

#endif // PICTUREMODEL_H
