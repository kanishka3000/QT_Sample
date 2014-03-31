#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSplashScreen>

#include "Trader.h"
#include "OrderEntry.h"
#include "Blotter.h"
#include "BlotterCache.h"
#include "ExecutionFilterModel.h"
#include "PreferenceWnd.h"
#include "IndexModel.h"
#include "AmendWnd.h"

Trader::Trader(void)
:p_MainWnd(0)
{
	d_Time = 0.0;
	b_LoadUpComplete = false;
}

Trader::~Trader(void)
{
}

void Trader::Init()
{
	
	p_IndexModel = new IndexModel(this);
	p_ExecReportCache = new ExecReportCache(this);
	

	p_MainWnd = new MainWnd(NULL,NULL,this);
	p_MainWnd->show();
	
	p_MainWnd->setWindowTitle("Loading Instruments");
	
	QPixmap pixmap(":/Images/F:/tmp/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);

	splash->show();
	
	LoadInstruments();
	


	p_MainWnd->setWindowTitle("Exchange Plus Trader");
	
	splash->finish(p_MainWnd);
	
	p_IndexModel->AddIndex("ASI",5.0,3.2);

	QTimer* pTimer = new QTimer(this);

	connect(pTimer,SIGNAL(timeout()),this,SLOT(OnTimer()));

	pTimer->start(5000);

	
}	

BaseWnd* Trader::CreateWnd( Defs::Windows eWindow, bool bSingleInstance /*= false*/ )
{
	BaseWnd* pWnd = NULL;
	switch (eWindow)
	{
	case Defs::PreferenceWnd:
		{
			pWnd = new PreferenceWnd(p_MainWnd,this);
			
			break;
		}
	case Defs::OrderEntry:
		{
			pWnd = new OrderEntry(p_MainWnd,this);		
			break;
		}
	case Defs::Blotter:
		{
			pWnd = new Blotter(p_MainWnd,this);
			break;
		}
	case Defs::Amend:
		{
			pWnd = new AmendWnd(p_MainWnd, this);

		}
	}
	if(pWnd)
	{
		//p_MainWnd->AddAsChild(pWnd);
		pWnd->OnCreateWnd();
		pWnd->show();
		pWnd->OnPostCreateWnd();
	}
	return pWnd;
}

void Trader::OnBusinessData( NewOrder* pNewOrder )
{

	ExecutionReport* pEx = new ExecutionReport();
	pEx->d_Price = pNewOrder->d_Price;
	pEx->d_Size = pNewOrder->d_Size;
	pEx->s_Symbol = pNewOrder->s_Symbol;
	emit OnExecutionReport(pEx);

	//delete pEx;

	p_ExecReportCache->AddRows(pEx);

	

}

void Trader::OnTimer()
{
	d_Time++;
	p_IndexModel->AddIndex("IDX1",d_Time, d_Time);
	p_IndexModel->AddIndex("S&P",d_Time + 1, d_Time);
	p_IndexModel->AddIndex("IDX2",d_Time + 1, d_Time);

}

void Trader::LoadInstruments()
{


	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("H:\\Projects\\Spatial\\SP2-3.6.28i\\_distribute\\Debug\\Instr.db");
	db.open();
	QSqlQueryModel *p_SymbolModel = new QSqlQueryModel;
	QString sQuery = "select * from SP2_INSTRUMENTS";
	p_SymbolModel->setQuery(sQuery);

	int iRowCount = p_SymbolModel->rowCount();
	for(int i =0; i < iRowCount * 3; i++)
	{
		Instrument* pInstrument = new Instrument;
		for(int j = 0; j < 15; j++)
		{
			QString sFieldName = p_SymbolModel->record(i).fieldName(j);
			QVariant sFieldValue = p_SymbolModel->record(i).value(sFieldName);
			pInstrument->map_Fields[sFieldName] = sFieldValue;
		
		}

		map_Instruments.insert(pInstrument->map_Fields["InstrumentID"].toString(), pInstrument);
		
		map_SymbolToInstID.insert(pInstrument->map_Fields["Symbol"].toString(), pInstrument->map_Fields["InstrumentID"].toString());
	}
	db.close();

	b_LoadUpComplete = true;

}

void Trader::GetAllInstruments( QList<Instrument*>& lstInstruments )
{
	if(!b_LoadUpComplete)
	{
		return;
	}

	foreach(Instrument* pInstrument, map_Instruments)
	{
		lstInstruments.push_back(pInstrument);
	}
}

QString Trader::ConverToInstrumentID( QString sInstrumentID )
{

	return map_SymbolToInstID[sInstrumentID];

}

Instrument* Trader::GetInstrument( QString sInstrumentID )
{
	QMap<QString,Instrument*>::iterator itr = map_Instruments.find(sInstrumentID);
	if(itr != map_Instruments.end())
	{
		return *itr;

	}
	return NULL;
}


