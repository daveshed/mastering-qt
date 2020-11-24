#include <QSqlDatabase>

#include "databasemanager.h"

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    albumDigitalAccessObject(*mDatabase)  // dereference the pointer and pass it to the constructor
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();
    albumDigitalAccessObject.init();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}
