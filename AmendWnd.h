#ifndef AMENDWND_H
#define AMENDWND_H

#include <QWidget>
#include "ui_AmendWnd.h"
#include "BaseWnd.h"
class AmendWnd : public BaseWnd, public Ui::AmendWnd
{
	Q_OBJECT

public:
	AmendWnd(QWidget *parent, Trader* pTrader);
	~AmendWnd();

	void OnAmend(ExecutionReport* pReport);
};

#endif // AMENDWND_H
