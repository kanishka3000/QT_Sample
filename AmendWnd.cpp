#include "AmendWnd.h"
#include "Defs.h"
AmendWnd::AmendWnd(QWidget *parent,Trader* pTrader)
	: BaseWnd(parent, pTrader)
{
	setupUi(this);
	CenterWnd->Init(this);
}

AmendWnd::~AmendWnd()
{

}

void AmendWnd::OnAmend( ExecutionReport* pReport )
{
	setWindowTitle(pReport->s_Symbol);
	CenterWnd->PopulateFromExecutionReport(pReport);
}
