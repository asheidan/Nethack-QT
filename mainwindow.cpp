#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <iostream>

#include "tileset.h"

const int kMapWidth = 80;
const int kMapHeight = 20;

const int kTileWidth = 32;
const int kTileHeight = 32;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->textBrowser->append(QString("Application launched"));

	TileSet tileset(QString(":/tiles/chubby.jpg"), kTileWidth, kTileHeight);

	scene = new NethackScene();
	scene->setSceneRect(QRectF(0, 0,
							   kMapWidth * kTileWidth,
							   kMapHeight * kTileHeight));

	//ui->graphicsView->setBackgroundBrush(Qt::CrossPattern);
	ui->graphicsView->setScene(scene);
	ui->graphicsView->update();

	QGraphicsItem *item;

	for (int y = 0; y < kMapHeight; ++y) {
		for (int x = 0; x < kMapWidth; ++x) {
			item = scene->addPixmap(tileset.emptyTile());
			item->setPos(32 * x, 32 * y);
		}
	}

	item = scene->addPixmap(tileset.antTile());
	item->setPos(0, 0);

	item = scene->addPixmap(tileset.beeTile());
	item->setPos(32, 0);
}

MainWindow::~MainWindow()
{
	delete scene;
	delete ui;
}
