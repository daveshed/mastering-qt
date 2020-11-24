#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H
#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "album.h"
#include "databasemanager.h"

/*
 * The model is the central point/abstraction that clients/the controller will
 * use to interact with the data. It provides a read/write interface.
 * Each time the model interacts with the view, it will see mAlbums - a memory
 * address. Therefore access will be very fast.
 */
class GALLERYCORE_EXPORT AlbumModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        IdRole = Qt::UserRole + 1,
        NameRole,
    };
    AlbumModel(QObject* parent = 0);
    QModelIndex addAlbum(const Album& album);
    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;
    bool setData(
        const QModelIndex& index,
        const QVariant& value, int role) override;
    bool removeRows(
        int row,
        int count,
        const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;
private:
    bool isValid(const QModelIndex& index) const;
    bool inRange(int row) const;

private:
    DatabaseManager& mDatabase;
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> mAlbums;
};

#endif // ALBUMMODEL_H
