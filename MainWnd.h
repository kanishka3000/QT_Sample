#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QMainWindow>
#include "ui_MainWnd.h"
#include <QMenu>
#include <QMenuBar>
#include <QWorkspace>
#include <QVBoxLayout>


class Trader;
class BaseWnd;
class MainWnd : public QMainWindow
{
	Q_OBJECT

public:
	MainWnd(QWidget *parent = 0, Qt::WFlags flags = 0,Trader* pTrader = NULL);

	void SetStatusPane();

	~MainWnd();
	void CreateMenuBar();

	void AddAsChild(BaseWnd* pWnd);

	void ShowText(QString sText);
	void HideText();

public slots:
	void OnMenuClick(QAction* pAction);

private:
	Ui::MainWndClass ui;
	Trader* p_Trader;

	QAction* p_ActOrderEntry;
	QAction* p_ActBlotter;
	QAction* p_ActPreference;

	QWorkspace* p_Workspace;

	QVBoxLayout* p_MainLayout;

	QWidget* p_CentralWidget;

	QLabel* p_Notice;
	
};

#endif // MAINWND_H
