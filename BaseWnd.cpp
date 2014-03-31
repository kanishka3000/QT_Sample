#include "BaseWnd.h"

BaseWnd::BaseWnd(QWidget* pParent,Trader* pTrader)
:QDialog(pParent),p_Trader(pTrader)
{
}

BaseWnd::~BaseWnd(void)
{
}
