#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>

class TileSet
{
	public:
		TileSet(const QString &file, int width, int height);
		~TileSet();

		QPixmap antTile() const;
		QPixmap beeTile() const;
		QPixmap emptyTile() const;

	protected:
		QPixmap tile(int x, int y) const;

	private:
		int	width;
		int height;
		QPixmap pixmap;

};

#endif // TILESET_H
