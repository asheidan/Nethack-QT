#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "nethackscene.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;

		NethackScene *scene;
};

#endif // MAINWINDOW_H
