#include "MainWnd.h"
#include <QFile>
#include <QtGui/QApplication>
#include "Trader.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile styleFile(":/Style/StyleFile.qss");
	styleFile.open(QIODevice::ReadOnly );
	a.setStyleSheet(styleFile.readAll());

	Trader pTrader;
	pTrader.Init();

	return a.exec();
}
