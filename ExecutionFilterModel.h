#pragma once
#include <QSortFilterProxyModel>
#include "Defs.h"
class ExecutionFilterModel: public QSortFilterProxyModel
{
public:
	ExecutionFilterModel(QObject* pParent);
	virtual ~ExecutionFilterModel(void);


	virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;

	void SetFilter(ExecReportFilter* pFilter);

	ExecutionReport* GetRow(int iRow);
private:
	ExecReportFilter* p_Filter;
	
	

};
