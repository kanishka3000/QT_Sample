#ifndef ORDERENTRY_H
#define ORDERENTRY_H

#include "BaseWnd.h"
#include "ui_OrderEntry.h"
class Trader;
class OrderEntry : public BaseWnd
{
	Q_OBJECT

public:
	OrderEntry(QWidget *parent = 0,Trader* pTrader = NULL);
	~OrderEntry();

	void OnPostCreateWnd();

	

private:
	Ui::OrderEntry ui;
};

#endif // ORDERENTRY_H
