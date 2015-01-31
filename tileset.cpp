#include "tileset.h"

TileSet::TileSet(const QString &file, int width, int height)
	: width(width), height(height), pixmap(file)
{}

TileSet::~TileSet()
{}

QPixmap TileSet::tile(int x, int y) const
{
	return pixmap.copy(width * x, height * y, width, height);
}

QPixmap TileSet::antTile() const
{
	return tile(0, 0);
}

QPixmap TileSet::beeTile() const
{
	return tile(1, 0);
}

QPixmap TileSet::emptyTile() const
{
	return tile(8, 21);
}
