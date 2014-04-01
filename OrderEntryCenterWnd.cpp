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

	cmbTIF->addItem("DAY");
	cmbTIF->addItem("GTC");
	cmbTIF->addItem("GTD");
	cmbTIF->addItem("GTT");

	cmbOrderType->addItem("LIMIT");
	cmbOrderType->addItem("MARKET");
	cmbOrderType->addItem("STOP");



}

OrderEntryCenterWnd::~OrderEntryCenterWnd()
{

	for(QMap<QString,NewOrder*>::iterator itr = map_Tabs.begin(); itr != map_Tabs.end(); itr++ )
	{
		NewOrder* pOrder = *itr;
		delete pOrder;
	}
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

	btnSubmit->setDisabled(false);

	QString sSymbol = pInstrument->map_Fields["Symbol"].toString();
	int iDecimalCount = pInstrument->map_Fields["NoOfDecimals"].toInt();
	int iLotSize = pInstrument->map_Fields["LotSize"].toInt();
	
	txtPrice->setDecimals(iDecimalCount);
	txtSize->setSingleStep(iLotSize);

	PopulateCurrentOrder();

	if(map_Tabs.contains(sSymbol))
	{
		p_CurrentOrder = map_Tabs[sSymbol];
	}
	else
	{
		p_CurrentOrder = new NewOrder;
		p_CurrentOrder->d_Price = 0.0;
		p_CurrentOrder->d_Size = 0.0;
		map_Tabs.insert(sSymbol, p_CurrentOrder);
	}
	
	txtPrice->setValue(p_CurrentOrder->d_Price);
	txtSize->setValue(p_CurrentOrder->d_Size);


}

void OrderEntryCenterWnd::PopulateCurrentOrder()
{
	if(!p_CurrentOrder)
	{
		p_CurrentOrder = new NewOrder;
	}

	p_CurrentOrder->d_Price =  txtPrice->value();
	p_CurrentOrder->d_Size = txtSize->value();
	p_CurrentOrder->i_Side = cmbSide->currentIndex();
	p_CurrentOrder->s_OrderTye = cmbOrderType->currentText();
	p_CurrentOrder->s_TIF =  cmbTIF->currentText();
	QDateTime pDt = tmeExpiry->dateTime();
	
	QString sFormat("yyyy:M:dd");

	if(p_CurrentOrder->s_TIF == "GTT")
	{
		sFormat = "hh:mm:ss";
	}

	p_CurrentOrder->s_ExpiryDate = pDt.toString(sFormat);

	p_CurrentOrder->s_Symbol = p_CurentInstrument->map_Fields["Symbol"].toString();
	p_CurrentOrder->i_OrderID = -1;
	
}

void OrderEntryCenterWnd::OnSideChanged( int iIndex )
{
	if(iIndex == 0)
	{
		CenterWidget->setStyleSheet("QWidget#OrderEntryCenterWnd{background-color: blue;}");
		btnSubmit->setText("Buy");
	}
	else
	{
		setStyleSheet(".OrderEntryColorPanel{background-color: red;}");
		btnSubmit->setText("Sell");
	}

}

void OrderEntryCenterWnd::PopulateFromExecutionReport( ExecutionReport* pReport )
{

	btnSubmit->setDisabled(false);

	txtPrice->setValue(pReport->d_Price);
	txtSize->setValue(pReport->d_Size);
	cmbSide->setCurrentIndex(pReport->i_Side);
	Trader* pTrader = p_ParentWnd->GetTrader();

	QString sInstrumentID = pTrader->ConverToInstrumentID(pReport->s_Symbol);
	p_CurentInstrument = pTrader->GetInstrument(sInstrumentID);

	PopulateCurrentOrder();

	p_CurrentOrder->i_OrderID = pReport->i_OrderID;
}

void OrderEntryCenterWnd::OnTIFChanged(QString sTif )
{
	
	
	tmeExpiry->setDateTime(QDateTime::currentDateTime());
	tmeExpiry->setDisabled(false);

	if(sTif == "GTD")
	{		
		tmeExpiry->setDisplayFormat("yyyy:M:dd");
	}
	else if (sTif == "GTT")
	{
		
		tmeExpiry->setDisplayFormat("hh:mm:ss");
	}
	else
	{
		tmeExpiry->setDisabled(true);
	}
}

void OrderEntryCenterWnd::OnOrderTypeChanged( QString sOrderType )
{
	

	if(sOrderType == "LIMIT" || sOrderType == "MARKET")
	{
		spinStopPrice->setDisabled(true);
	}
	else
	{
		spinStopPrice->setDisabled(false);
	}


}

