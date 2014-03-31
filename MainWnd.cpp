#include "MainWnd.h"
#include "Trader.h"
#include "IndexItem.h"
#include "IndexModel.h"
#include "UnityBar.h"
MainWnd::MainWnd(QWidget *parent, Qt::WFlags flags,Trader* pTrader)
	: QMainWindow(parent, flags),p_Trader(pTrader)
{

	p_Notice =  new QLabel;	
	ui.setupUi(this);
	//setStyleSheet("background:transparent;");
	
	

	p_ActOrderEntry = NULL;
	p_ActBlotter = NULL;
	p_ActPreference = NULL;

	p_Workspace = new QWorkspace();

	SetStatusPane();

	CreateMenuBar();

}

MainWnd::~MainWnd()
{

}

void MainWnd::CreateMenuBar()
{
	QMenuBar* pMenuBar = menuBar();
	QMenu* pMarketMenu = pMenuBar->addMenu(tr("Market") );

	p_ActOrderEntry = new QAction(tr("&OrderEntry"),this);
	pMarketMenu->addAction(p_ActOrderEntry);


	p_ActBlotter = new QAction(tr("&Blotter"),this);
	pMarketMenu->addAction(p_ActBlotter);

	p_ActPreference = new QAction(tr("&Preference"),this);
	pMarketMenu->addAction(p_ActPreference);

	connect(pMenuBar,SIGNAL(triggered(QAction*)),this,SLOT(OnMenuClick(QAction*)));

	//UnityBar* pUnityBar = new UnityBar(NULL,p_Trader);

	//pUnityBar->show();

}

void MainWnd::OnMenuClick( QAction* pAction )
{
	Defs::Windows eWindow;
	if(pAction == p_ActOrderEntry)
	{
		eWindow = Defs::OrderEntry;
	}
	else if (pAction == p_ActBlotter)
	{
		eWindow = Defs::Blotter;
	}
	else if(pAction == p_ActPreference)
	{
		eWindow = Defs::PreferenceWnd;
	}

	p_Trader->CreateWnd(eWindow);
}

void MainWnd::SetStatusPane()
{
	//QHBoxLayout* pLayout = ui.BottomLayout;

	//IndexItem* pIndex1 = new IndexItem(this);
	//IndexItem* pIndex2 = new IndexItem(this);
	//pLayout->addWidget(pIndex1);
	//pLayout->addStretch();
	//pLayout->addWidget(pIndex2);
	ui.BottomPane->Init(p_Trader->p_IndexModel);

	ui.BottomPane->IndexAddingBegin();

	ui.BottomPane->AddIndex("IDX1");
	ui.BottomPane->AddIndex("S&P");
	ui.BottomPane->AddIndex("IDX2");
	

	
}

void MainWnd::AddAsChild( BaseWnd* pWnd )
{
	ui.mdiArea->addSubWindow(pWnd);
}

void MainWnd::ShowText( QString sText )
{
	p_Notice->setText(sText);
	
}


