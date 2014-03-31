#include "OrderEntry.h"
#include <QSplitter>
#include <QPainter>
#include "OrderEntryRightPane.h"
#include "InstrumentSelector.h"
#include "OrderEntryCenterWnd.h"
OrderEntry::OrderEntry(QWidget *parent,Trader* pTrader)
	: BaseWnd(parent,pTrader)
{
	ui.setupUi(this);

	
	ui.InsSelector->RegisterRightPane(ui.RightPane);
	
	
	connect(ui.InsSelector,SIGNAL(OnInstrumentSelected(QString)),ui.CenterWnd,SLOT(OnInstrumentSelected(QString)));

	connect(ui.InsSelector, SIGNAL(InstrumentSelected(Instrument* , QString )),ui.RightPane,SLOT(OnInstrumentSelected(Instrument* , QString )));

	connect(ui.RightPane, SIGNAL(InstrumentSelected(Instrument* , QString )), ui.InsSelector, SLOT(SelectInstrument(Instrument* , QString )));

	connect(ui.InsSelector, SIGNAL(InstrumentSelected(Instrument* , QString )), ui.CenterWnd, SLOT(OnInstrumentSelected(Instrument* , QString )));

	setAutoFillBackground(false);

	
	//setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowOpacity(0.5);
	//ui.CenterWnd->setWindowOpacity(1);
	//ui.CenterWnd->repaint();
}

OrderEntry::~OrderEntry()
{

}

void OrderEntry::OnPostCreateWnd()
{
	ui.InsSelector->Init(this);
	ui.CenterWnd->Init(this);

}


