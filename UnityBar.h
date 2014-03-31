#ifndef UNITYBAR_H
#define UNITYBAR_H

#include <QWidget>
#include "ui_UnityBar.h"
#include <QVBoxLayout>
#include "BaseWnd.h"
class Trader;
class UnityBar : public BaseWnd, public Ui::UnityBar
{
	Q_OBJECT

public:
	UnityBar(QWidget *parent,Trader* pTrader);
	~UnityBar();

	QVBoxLayout* p_MainLayout;
	

};

#endif // UNITYBAR_H
