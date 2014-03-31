#include "OrderEntryCenterWnd.h"
#include "Defs.h"
#include "BaseWnd.h"
#include "Trader.h"
#include "Defs.h"
OrderEntryCenterWnd::OrderEntryCenterWnd(QWidget *parent)
	: QWidget(parent)
{
	p_ParentWnd = NULL;
	p_CurentInstrument = NULL;
	p_CurrentOrder = NULL;
	setupUi(this);
	cmbSide->addItem("Buy");
	cmbSide->addItem("Sell");
}

OrderEntryCenterWnd::~OrderEntryCenterWnd()
{

}

void OrderEntryCenterWnd::Init( BaseWnd* pParent )
{
	p_ParentWnd = pParent;
	connect(btnSubmit,SIGNAL(clicked(bool)),this,SLOT(OnSubmit()));
	
}

void OrderEntryCenterWnd::OnSubmit()
{
	if(!p_CurentInstrument)
	{
		return;
	}

	PopulateCurrentOrder();
	
	p_ParentWnd->GetTrader()->OnBusinessData(p_CurrentOrder);
}

void OrderEntryCenterWnd::OnInstrumentSelected( QString sInstrument )
{
	s_Instrument = sInstrument;
}

void OrderEntryCenterWnd::OnInstrumentSelected( Instrument* pInstrument, QString sOrderBook )
{
	p_CurentInstrument = pInstrument;
	s_OrderBook = sOrderBook;

	QString sSymbol = pInstrument->map_Fields["Symbol"].toString();
	int iDecimalCount = pInstrument->map_Fields["NoOfDecimals"].toInt();

	
	txtPrice->setDecimals(iDecimalCount);
	PopulateCurrentOrder();

	NewOrder* pNewOrder = NULL;
	if(map_Tabs.contains(sSymbol))
	{
		pNewOrder = map_Tabs[sSymbol];
	}
	else
	{
		pNewOrder = new NewOrder;
		pNewOrder->d_Price = 0.0;
		pNewOrder->d_Size = 0.0;
		map_Tabs.insert(sSymbol, pNewOrder);
	}
	
	p_CurrentOrder = pNewOrder;

	txtPrice->setValue(pNewOrder->d_Price);
	txtSize->setValue(pNewOrder->d_Size);


}

void OrderEntryCenterWnd::PopulateCurrentOrder()
{
	if(!p_CurrentOrder)
	{
		p_CurrentOrder = new NewOrder;
	}

	p_CurrentOrder->d_Price =  txtPrice->value();
	p_CurrentOrder->d_Size = txtSize->value();
	p_CurrentOrder->s_Symbol = p_CurentInstrument->map_Fields["Symbol"].toString();
	
}

void OrderEntryCenterWnd::OnSideChanged( int iIndex )
{
	if(iIndex == 0)
	{
		CenterWidget->setStyleSheet("background: blue;");
	}
	else
	{
		CenterWidget->setStyleSheet("background: red;");
	}

}

void OrderEntryCenterWnd::PopulateFromExecutionReport( ExecutionReport* pReport )
{

	txtPrice->setValue(pReport->d_Price);
	txtSize->setValue(pReport->d_Size);
	Trader* pTrader = p_ParentWnd->GetTrader();

	QString sInstrumentID = pTrader->ConverToInstrumentID(pReport->s_Symbol);
	p_CurentInstrument = pTrader->GetInstrument(sInstrumentID);
}
