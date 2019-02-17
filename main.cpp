#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QPixmap midimixIcon(":icons/midimixedit.png");
	midimixIcon = midimixIcon.scaledToWidth(48,Qt::SmoothTransformation);
	QIcon midimixedit(midimixIcon);

	a.setWindowIcon(midimixedit);
	MainWindow w;
	w.show();

	return a.exec();
}
