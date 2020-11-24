#include <memory>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "album.h"
#include "albumdigitalaccessobject.h"

using namespace std;

class QSqlDatabase;

// create the connection to the actual database.
AlbumDigitalAccessObject::AlbumDigitalAccessObject(QSqlDatabase& database) :
    mDatabase(database)
{
}

// why bother with an initialiser method when you could just use the
// the constructor for this instead? This is considered bad programming style
// and should be refactored.
// https://stackoverflow.com/questions/3786853/why-use-an-initialization-method-instead-of-a-constructor
void AlbumDigitalAccessObject::init() const
{
    if (!mDatabase.tables().contains("albums"))
    {
        QSqlQuery query(mDatabase);
        // query should always return true on success false on error.
        assert(query.exec("CREATE TABLE"
            "albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)"));
    }
}

void AlbumDigitalAccessObject::addAlbum(Album& album) const
{
    QSqlQuery query(mDatabase);
    // query contains placeholders for fields that will be filled in later...
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    // this call expects a QVariant therefore we need to include that header -
    // it's a generic data holder.
    query.bindValue(":name", album.name());
    // bound values are properly replaced. Executing the query modifies the
    // state of the query itself.
    query.exec();
    // here we modify the album so this parameter cannot be marked as const.
    album.setId(query.lastInsertId().toInt());
}

void AlbumDigitalAccessObject::updateAlbum(const Album& album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
//    DatabaseManager::debugQuery(query);
}

void AlbumDigitalAccessObject::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
//    DatabaseManager::debugQuery(query);
}

/*
 The following code is dangerous. An exception raised while reading the query
 could mean that the album pointer is never appended to the list and returned.
 They will accumulate leading to a memory leak. To guard against this, we can
 leverage C++11's memory management features.
*/
#if 0
// Dynamically creates albums and adds them to a list that's returned at the
// end of execution.
QVector<Album*> AlbumDigitalAccessObject::getAlbums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);
    // to walk through multiple rows for a given request, query handles an
    // internal cursor pointing to the current row.
    query.exec();
    QVector<Album*> list;
    while (query.next())
    {
        Album* album = new Album();
        // note that these queries return a QVariant that must be cast to the
        // proper type.
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list.append(album);
    }
    return list;
}
#endif

/*
 The following alternative uses a smart pointer to address this: specifically a
 unique pointer - only one client has the ownership at one time.
*/
unique_ptr<vector<unique_ptr<Album>>>
AlbumDigitalAccessObject::getAlbums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);
    query.exec();
    unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>);
    while (query.next())
    {
        unique_ptr<Album> album(new Album);
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(move(album));
    }
    return list;
}
