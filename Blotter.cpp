#include "Blotter.h"
#include "Defs.h"
#include "Trader.h"
#include "BlotterCache.h"
#include "ExecutionFilterModel.h"
#include "ExecutionFilterModel.h"
#include "AmendWnd.h"
Blotter::Blotter(QWidget *parent,Trader* pTrader )
	: BaseWnd(parent,pTrader)
{
	ui.setupUi(this);

	p_BlotterCache = new ExecutionFilterModel(p_Trader);
	p_BlotterCache->setSourceModel(p_Trader->p_ExecReportCache);
	ui.tableView->setModel(p_BlotterCache);

	act_Amend =  new QAction("Amend",this);

	ui.tableView->addAction(act_Amend);

	ui.tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(pTrader,SIGNAL(OnExecutionReport(ExecutionReport*)) ,this, SLOT(OnExecutionReport(ExecutionReport*)));

	connect(ui.Filter,SIGNAL(FilterApplied(ExecReportFilter*)),this,SLOT(SetFilter( ExecReportFilter*)));

	connect(act_Amend,SIGNAL(triggered()),this, SLOT(OnAmend()) );
}

Blotter::~Blotter()
{

}

void Blotter::OnExecutionReport( ExecutionReport* pExecutionReport )
{


}

void Blotter::SetModel( QAbstractItemModel* pCache )
{
	//p_BlotterCache = new ExecutionFilterModel(p_Trader);
	//p_BlotterCache->setSourceModel(p_Trader->p_ExecReportCache);
	//ui.tableView->setModel(pCache);
}

void Blotter::SetFilter( ExecReportFilter* pFilter )
{

	p_BlotterCache->SetFilter(pFilter);
}

void Blotter::OnAmend()
{

	QItemSelectionModel * pSelectuionModel =  ui.tableView->selectionModel();

	if(!pSelectuionModel->hasSelection())
	{
		return;
	}

	QModelIndexList pList = pSelectuionModel->selectedIndexes();

	QModelIndex pSymbolIndex = pList[0];//index is hardcorded, problem
	QModelIndex pPriceIndex = pList[1];
	QModelIndex pSizeIndex = pList[2];

	QVariant oSymbol = p_BlotterCache->data(pSymbolIndex);
	QVariant oPrice = p_BlotterCache->data(pPriceIndex);
	QVariant oSize = p_BlotterCache->data(pSizeIndex);

	QString sSymbol = oSymbol.toString();
	double dPrice = oPrice.toDouble();
	double dSize = oSize.toDouble();


	ExecutionReport* pExec = p_BlotterCache->GetRow(pSizeIndex.row());//if filter applied will not work. 

	
	BaseWnd* pWnd = p_Trader->CreateWnd(Defs::Amend, false);

	AmendWnd* pAmendWnd = dynamic_cast<AmendWnd*>(pWnd);
	if(pWnd)
	{
		pAmendWnd->OnAmend(pExec);
	}
	
		
}
