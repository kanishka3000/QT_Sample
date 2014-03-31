#ifndef BLOTTER_H
#define BLOTTER_H

#include "BaseWnd.h"
#include <QAction>
#include "ui_Blotter.h"
#include <QItemSelectionModel >

class ExecutionReport;
class ExecReportCache;
class ExecutionFilterModel;
class Blotter : public BaseWnd
{
	Q_OBJECT

public:
	Blotter(QWidget *parent = 0,Trader* pTrader = NULL);
	~Blotter();

	void SetModel(QAbstractItemModel* pCache);
	
public slots:
	void OnExecutionReport(ExecutionReport* pExecutionReport);

	void SetFilter(ExecReportFilter* pFilter);

	void OnAmend();

protected:
	Ui::Blotter ui;
	ExecutionFilterModel* p_BlotterCache;
	QAction* act_Amend;
};

#endif // BLOTTER_H
