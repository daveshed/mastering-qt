#ifndef PICTUREDIGITALACCESSOBJECT_H
#define PICTUREDIGITALACCESSOBJECT_H
#include <QVector>

class QSqlDatabase;
class Picture;
// very similar to AlbumDigitalAccessObject just it has a foreign key to an
// album. It must be conditioned by an albumId parameter.
class PictureDigitalAccessObject
{
public:
    explicit PictureDigitalAccessObject(QSqlDatabase& database);
    void init() const;

    void addPictureInAlbum(int albumId, Picture& picture) const;
    void removePicture(int id) const;
    void removePictures(int albumId) const;
    QVector<Picture*> picturesForAlbum(int albumId) const;

private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDIGITALACCESSOBJECT_H
