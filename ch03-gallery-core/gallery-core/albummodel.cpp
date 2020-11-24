#include <memory>

#include "albummodel.h"

AlbumModel::AlbumModel(QObject* parent) :
    QAbstractListModel(parent),
    mDatabase(DatabaseManager::instance()),
    mAlbums(mDatabase.albumDigitalAccessObject.getAlbums())
{

}
/*
 * QModelIndex is an abstraction that represents the index of items in the
 * model. Bear in mind that the model will change and could be a list or table
 * or tree. We don't know which concrete instance we have.
*/
int AlbumModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mAlbums->size();
}

QVariant AlbumModel::data(const QModelIndex& index, int role) const
{
    if (!isValid(index))
    {
        // not valid so just return empty...
        return QVariant();
    }
    const Album& album = *mAlbums->at(index.row());
    switch (role)
    {
        case Roles::IdRole:
            return album.id();
        case Roles::NameRole:
        case Qt::DisplayRole:
            return album.name();
        default:
            return QVariant();
    }
}


QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";
    return roles;
}

QModelIndex AlbumModel::addAlbum(const Album& album)
{
    int rowIndex = rowCount();
    // emit signals for whoever might be interested...
    // hand the parent to this function which is the default constructed
    // QModelIndex which will point to the root of the hierarchy.
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<Album> newAlbum(new Album(album));
    mDatabase.albumDigitalAccessObject.addAlbum(*newAlbum);
    mAlbums->push_back(move(newAlbum));
    // emit again...
    endInsertRows();
    return index(rowIndex, 0);
}

// called when the view wants to update the data...
bool AlbumModel::setData(
    const QModelIndex& index, const QVariant& value, int role)
{
    if (!isValid(index)) return false;
    // this condition prevents editing anything other than the name...
    if (role != Roles::NameRole) return false;
    // get an alias to the album of interest...
    Album& album = *mAlbums->at(index.row());
    // update the name and ensure the database is consistent...
    album.setName(value.toString());
    mDatabase.albumDigitalAccessObject.updateAlbum(album);
    // notify anyone who may care about this...
    emit dataChanged(index, index);
    return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex& parent)
{
    const int first = row;
    const int last = row + count - 1;
    if (!inRange(first)) return false;
    if (!inRange(last)) return false;
    beginRemoveRows(parent, first, last);
    int remaining = count;
    while (remaining--)
    {
        const Album& album = *mAlbums->at(row + remaining);
        mDatabase.albumDigitalAccessObject.removeAlbum(album.id());
    }
    mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + row + count);
    // shouldn't this be...
    // mAlbums->erase(mAlbums->begin() + first, mAlbums->begin() + last); ??!
    endRemoveRows();
    return true;
}

// PRIVATE

bool AlbumModel::isValid(const QModelIndex& index) const
{
    return inRange(index.row()) && index.isValid();
}

bool AlbumModel::inRange(int row) const
{
    return (row > 0) && (row < rowCount());
}
