#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>

#include "albumdigitalaccessobject.h"
// if you're trying to be agnostic to the type of database then this name is
// not helping...
class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";
/*
 * A singleton that manages access to an underlying database through a public
 * digital access object.
 */
class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();
protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);
private:
    QSqlDatabase* mDatabase;

public:
    // really? a public member? Shouldn't there be a getter for this? Or do you
    // mean this should be private?
    // ok the text qualifies this at location 1931 - but you should still have
    // a getter here in case you need to change the implementation later.
    const AlbumDigitalAccessObject albumDigitalAccessObject;
};

#endif // DATABASEMANAGER_H
