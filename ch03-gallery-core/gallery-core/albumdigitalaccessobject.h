#ifndef ALBUMDIGITALACCESSOBJECT_H
#define ALBUMDIGITALACCESSOBJECT_H
#include <memory>
#include <vector>

#include <QVector>

/*
This declaration specifies an interface to the database persistence layer. This
means that clients can be agnostic to the details of the database - it's just
another abstraction basically. This should probably be an abstract base class
though.
*/
class Album;
class QSqlDatabase;

class AlbumDigitalAccessObject
{
public:
    AlbumDigitalAccessObject(QSqlDatabase& database);
    void init(void) const;
    void addAlbum(Album& album) const;
    void updateAlbum(const Album& album) const;
    void removeAlbum(int id) const;
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> getAlbums() const;
private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDIGITALACCESSOBJECT_H
