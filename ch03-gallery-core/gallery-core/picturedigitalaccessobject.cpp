#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>

#include "databasemanager.h"
#include "picturedigitalaccessobject.h"

PictureDigitalAccessObject::PictureDigitalAccessObject(QSqlDatabase& database) :
    mDatabase(database)
{
}

void PictureDigitalAccessObject::init() const
{
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures")
        + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
        + "album_id INTEGER, "
        + "url TEXT)");
//        DatabaseManager::debugQuery(query);
    }
}
