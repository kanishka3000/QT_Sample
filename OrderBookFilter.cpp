#include "OrderBookFilter.h"

OrderBookFilter::OrderBookFilter(QObject *parent)
:InstrumentFilter(parent)
{
}

OrderBookFilter::~OrderBookFilter(void)
{
}

void OrderBookFilter::DoFilter( QString sValue )
{
	Instrument* pInstrument = vec_Items[0];
	emit InstrumentSelected(pInstrument,sValue);
}

void OrderBookFilter::AddInstruments( Instrument* pInstrument )
{
	vec_Items.push_back(pInstrument);
	QString sItemString  = pInstrument->map_Fields[s_DisplayField].toString();
	
	QStringList sOrderBooks = sItemString.split("|");
	
	p_Widget->addItems(sOrderBooks);
}

void OrderBookFilter::SelectAndForward( Instrument* pInstrument, QString sOrderBook )
{

	QString sItemString  = pInstrument->map_Fields[s_DisplayField].toString();

	QStringList sOrderBooks = sItemString.split("|");

	p_Widget->addItems(sOrderBooks);

	p_Widget->setCurrentIndex(p_Widget->findText(sOrderBook));
}
