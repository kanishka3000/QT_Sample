#include "InstrumentSelector.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "InstrumentFilter.h"
#include "OrderBookFilter.h"
#include "InsTypeFilter.h"
#include "BaseWnd.h"
#include "Trader.h"

InstrumentSelector::InstrumentSelector(QWidget *parent)
	: QWidget(parent)
{
	
	setupUi(this);
	p_Parent = NULL;
	CreateFilters();



	connect(cmbOrderBook,SIGNAL(currentIndexChanged ( const QString&)), this,SLOT(OnComboSelect(QString)));
	connect(cmbInsType,SIGNAL(activated (const QString)),this, SLOT(OnInstrumentTypeSelected( QString)));
	connect(map_FilterChain["OrderBooks"],SIGNAL(InstrumentSelected(Instrument*,QString )),this, SLOT(OnOrderBookSelected( Instrument*, QString   )) );

	
}

InstrumentSelector::~InstrumentSelector()
{

}

void InstrumentSelector::RegisterRightPane( QObject* pCalback )
{
	connect(this->cmbOrderBook,SIGNAL(activated(const QString&)), pCalback, SLOT(AddInstrument(QString)));
	connect(pCalback,SIGNAL(OnInstrumentSelected(QString)),this,SLOT(AddInstrument( QString)));
}

void InstrumentSelector::OnComboSelect( QString sInstrument )
{	
	emit OnInstrumentSelected(sInstrument);
}

void InstrumentSelector::AddInstrument( QString sInstrument )
{
	int iIndex = cmbOrderBook->findText(sInstrument);
	cmbOrderBook->setCurrentIndex(iIndex);

	emit OnInstrumentSelected(sInstrument);
}

void InstrumentSelector::OnInstrumentTypeSelected( QString sType )
{


	if(sType == "Future")
	{
		cmbStrikePrice->setVisible(false);
		cmbOptionType->setVisible(false);
		cmbExpDate->setVisible(true);
		

	}
	else if (sType == "Option")
	{
		cmbStrikePrice->setVisible(true);
		cmbOptionType->setVisible(true);
		

	}
	else
	{
		cmbStrikePrice->setVisible(false);
		cmbOptionType->setVisible(false);
		cmbExpDate->setVisible(false);
		

	}

	//RearrangeChain(sType);

}

void InstrumentSelector::CreateFilters()
{

	InstrumentFilter* pInstrumentType = new InsTypeFilter(this);
	pInstrumentType->AddWidget(cmbInsType);
	pInstrumentType->s_FilterField = "InstrumentType";
	pInstrumentType->s_DisplayField = "InstrumentType";
	map_FilterChain["InstrumentType"] = pInstrumentType;

	InstrumentFilter* pInstrumentFilter = new InstrumentFilter(this);
	pInstrumentFilter->AddWidget(cmbSymbol);
	pInstrumentFilter->s_FilterField = "Symbol";
	map_FilterChain["Symbol"] = pInstrumentFilter;
	pInstrumentFilter->s_DisplayField = "Symbol";

	InstrumentFilter* ExpriyFilter = new InstrumentFilter(this);
	ExpriyFilter->AddWidget(cmbExpDate);
	ExpriyFilter->s_FilterField = "ExpiryDate";
	ExpriyFilter->s_DisplayField = "ExpiryDate";
	map_FilterChain["ExpiryDate"] = ExpriyFilter;

	InstrumentFilter* StPriceFilter = new InstrumentFilter(this);
	StPriceFilter->AddWidget(cmbStrikePrice);
	StPriceFilter->s_FilterField = "StrikePrice";
	StPriceFilter->s_DisplayField = "StrikePrice";
	map_FilterChain["StrikePrice"] = StPriceFilter;

	InstrumentFilter* OptionTypeFilter = new InstrumentFilter(this);
	OptionTypeFilter->AddWidget(cmbOptionType);
	OptionTypeFilter->s_FilterField = "OptionType";
	OptionTypeFilter->s_DisplayField = "OptionType";
	map_FilterChain["OptionType"] = OptionTypeFilter;

	InstrumentFilter* OrderFilter = new OrderBookFilter(this);
	OrderFilter->AddWidget(cmbOrderBook);
	OrderFilter->s_FilterField = "OrderBooks";
	OrderFilter->s_DisplayField = "OrderBooks";
	map_FilterChain["OrderBooks"] = OrderFilter;

	pInstrumentType->p_Next = pInstrumentFilter;

}

void InstrumentSelector::RearrangeChain(QString sType)
{


	if(sType == "Future")
	{
				
		map_FilterChain["Symbol"]->p_Next = map_FilterChain["ExpiryDate"];
		map_FilterChain["ExpiryDate"]->p_Next = map_FilterChain["OrderBooks"];


	}
	else if (sType == "Option")
	{
		map_FilterChain["Symbol"]->p_Next = map_FilterChain["ExpiryDate"];
		map_FilterChain["ExpiryDate"]->p_Next = map_FilterChain["StrikePrice"];
		map_FilterChain["StrikePrice"]->p_Next = map_FilterChain["OptionType"];
		map_FilterChain["OptionType"]->p_Next = map_FilterChain["OrderBooks"];
	}
	else
	{
		
		map_FilterChain["Symbol"]->p_Next = map_FilterChain["OrderBooks"];;
	}
	
}

void InstrumentSelector::OnOrderBookSelected( Instrument* pInstrument, QString sOrderBook )
{
	emit InstrumentSelected(pInstrument,sOrderBook);

}

void InstrumentSelector::SelectInstrument( Instrument* pInstrument, QString sOrderBook )
{
	map_FilterChain["InstrumentType"]->SelectAndForward(pInstrument,sOrderBook);	
}

void InstrumentSelector::Init( BaseWnd* pParent )
{
	p_Parent = pParent;
	Trader* pTrader = pParent->GetTrader();
	
	QList<Instrument*> lstInstruments;
	pTrader->GetAllInstruments(lstInstruments);

	foreach(Instrument* pInstrument , lstInstruments)
	{
		map_FilterChain["InstrumentType"]->AddInstruments(pInstrument);

	}

}


