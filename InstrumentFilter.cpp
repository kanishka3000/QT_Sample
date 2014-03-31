#include "InstrumentFilter.h"

InstrumentFilter::InstrumentFilter(QObject *parent)
	: QObject(parent)
{
	p_Next = NULL;
	p_Prev = NULL;

}

InstrumentFilter::~InstrumentFilter()
{

}

void InstrumentFilter::AddInstruments( Instrument* pInstrument )
{
	vec_Items.push_back(pInstrument);
	QString sItemString  = pInstrument->map_Fields[s_DisplayField].toString();

	if (!set_UniqueItems.contains(sItemString))
	{
		p_Widget->addItem(sItemString);
		set_UniqueItems.insert(sItemString,1);
	}
		
}

void InstrumentFilter::Reset()
{
	vec_Items.clear();
	set_UniqueItems.clear();
	p_Widget->clear();

	if(p_Next)
	{
		p_Next->Reset();
	}
}

void InstrumentFilter::AddWidget( QComboBox* pWidget )
{
	p_Widget = pWidget;
	connect(p_Widget,SIGNAL(activated (const QString)), this, SLOT(DoFilter( QString )));
}

void InstrumentFilter::DoFilter( QString sValue )
{
	if(s_FilterField == "" )
			return;

	if(p_Next)
		p_Next->Reset();

	QVariant oValue = sValue;

	foreach(Instrument* pInst, vec_Items)
	{
		QVariant oFilterVal = pInst->map_Fields[s_FilterField];
		if( oFilterVal == oValue)
		{
			if(p_Next)
				p_Next->AddInstruments(pInst);
		}
	}
}

void InstrumentFilter::SelectAndForward( Instrument* pInstrument, QString sOrderBook )
{
	

	QString sValue = pInstrument->map_Fields[s_DisplayField].toString();
	//p_Widget->clear();
	//p_Widget->addItem(sValue);
	p_Widget->setCurrentIndex(p_Widget->findText(sValue));
	DoFilter(sValue);
	if(p_Next)
	{
		p_Next->SelectAndForward(pInstrument,sOrderBook);
	}
}
