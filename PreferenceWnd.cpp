#include "PreferenceWnd.h"

PreferenceWnd::PreferenceWnd(QWidget *parent,Trader* pTrader /*= NULL*/)
:BaseWnd(parent,pTrader)
{
	setupUi(this);
}

PreferenceWnd::~PreferenceWnd()
{

}
