#include "OrderEntryRightPane.h"
#include "Defs.h"
OrderEntryRightPane::OrderEntryRightPane(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	connect(listWidget,SIGNAL(currentItemChanged ( QListWidgetItem* , QListWidgetItem* )),this,SLOT(OnItemSelected( QListWidgetItem* , QListWidgetItem*)));
}

OrderEntryRightPane::~OrderEntryRightPane()
{

}

void OrderEntryRightPane::AddInstrument( QString sInstrument )
{
	//listWidget->addItem(sInstrument);
}

void OrderEntryRightPane::RegisterInstrumentSelector( QObject* pInstrumentSelector )
{

	
}

void OrderEntryRightPane::OnItemSelected( QListWidgetItem * current, QListWidgetItem * previous )
{
	//emit OnInstrumentSelected(current->text());
	
	QString sSelectedText = current->text();
	
	RightPaneMap::iterator itr = map_Items.find(sSelectedText);
	if(itr!= map_Items.end())
	{
		Instrument* pInstrument = itr->first;
		QString sOrderBook = itr->second;
		emit InstrumentSelected(pInstrument, sOrderBook);
	}
	
}

void OrderEntryRightPane::OnInstrumentSelected( Instrument* pInstrument, QString sOrderBook )
{
	
	QString sInstrument = pInstrument->map_Fields["Symbol"].toString();

	RightPaneMap::iterator itr = map_Items.find(sInstrument);
	if(itr!= map_Items.end())
	{
		return;
	}
	listWidget->addItem(sInstrument);
	
	RightPaneItem oItem(pInstrument,sOrderBook);
	map_Items.insert(sInstrument,oItem);

}
