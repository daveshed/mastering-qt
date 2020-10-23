#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "album.h"
#include "albumdigitalaccessobject.h"

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
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
}
