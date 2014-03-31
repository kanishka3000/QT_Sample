#include "ExecutionFilterModel.h"
#include "BlotterCache.h"
#include "Defs.h"
ExecutionFilterModel::ExecutionFilterModel(QObject* pParent)
:QSortFilterProxyModel(pParent)
{
	p_Filter = NULL;
}

ExecutionFilterModel::~ExecutionFilterModel(void)
{
}

bool ExecutionFilterModel::filterAcceptsRow( int source_row, const QModelIndex & source_parent ) const
{
	if(!p_Filter)
		return true;

	QAbstractItemModel* pSource = sourceModel();

	ExecReportCache* pExecReportCache = dynamic_cast<ExecReportCache*>(pSource);

	if(!pExecReportCache)
			return true;


	ExecutionReport* pExecReport = pExecReportCache->GetRow(source_row);

	if(p_Filter->d_Price != 0)
	{
		if(p_Filter->d_Price != pExecReport->d_Price)
			return false;
	}

	if(p_Filter->d_Size != 0)
	{
		if(p_Filter->d_Size != pExecReport->d_Size)
			return false;
	}



	return true;
}

void ExecutionFilterModel::SetFilter( ExecReportFilter* pFilter )
{
	if(p_Filter)
		delete p_Filter;


	p_Filter = pFilter;
	invalidate();
}

ExecutionReport* ExecutionFilterModel::GetRow( int iRow )
{

	QAbstractItemModel* pSource = sourceModel();

	ExecReportCache* pExecReportCache = dynamic_cast<ExecReportCache*>(pSource);

	if(!pExecReportCache)
		return NULL;


	ExecutionReport* pExecReport = pExecReportCache->GetRow(iRow);

	return pExecReport;

}
