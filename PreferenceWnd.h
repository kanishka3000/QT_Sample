#ifndef PREFERENCEWND_H
#define PREFERENCEWND_H

#include "BaseWnd.h"
#include "ui_PreferenceWnd.h"

class PreferenceWnd : public BaseWnd, public Ui::PreferenceWnd
{
	Q_OBJECT

public:
	PreferenceWnd(QWidget *parent = 0,Trader* pTrader = NULL);
	~PreferenceWnd();
};

#endif // PREFERENCEWND_H
