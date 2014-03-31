#pragma once
#include <QDialog>
#include <QWidget>
 #include <QMdiSubWindow>
class Trader;
class BaseWnd: public QDialog
{
public:
	BaseWnd(QWidget* pParent,Trader* p_Trader);
	virtual ~BaseWnd(void);

	virtual void OnCreateWnd(){};
	virtual void OnPostCreateWnd(){};
	inline Trader* GetTrader() const { return p_Trader; }
protected:
	Trader* p_Trader;
	
	
};
