#include "InsTypeFilter.h"
#include "InstrumentSelector.h"
InsTypeFilter::InsTypeFilter(InstrumentSelector* parent)
:InstrumentFilter(parent)
{
	p_Parent = parent;
}

InsTypeFilter::~InsTypeFilter(void)
{
}

void InsTypeFilter::DoFilter( QString sValue )
{
	p_Parent->RearrangeChain(sValue);

	if(sValue == "Future" || sValue == "Option")
	{
		p_Next->s_DisplayField = "Underlying";
		p_Next->s_FilterField = "Underlying";
	}
	else
	{
		p_Next->s_DisplayField = "Symbol";
		p_Next->s_FilterField = "Symbol";
	}

	InstrumentFilter::DoFilter(sValue);
}

void InsTypeFilter::SelectAndForward( Instrument* pInstrument, QString sOrderBook )
{

	QString sInsType = pInstrument->map_Fields["InstrumentType"].toString();
	p_Parent->RearrangeChain(sInsType);
	p_Parent->OnInstrumentTypeSelected(sInsType);

	
	p_Widget->setCurrentIndex(p_Widget->findText(sInsType));
	DoFilter(sInsType);

	if(p_Next)
	{
		p_Next->SelectAndForward(pInstrument,sOrderBook);
	}

}
