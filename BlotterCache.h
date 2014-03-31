#pragma once

#include <QAbstractTableModel>
#include <QList>
class ExecutionReport;
class ExecReportCache: public QAbstractTableModel
{
public:
	ExecReportCache(QObject* pParent);
	virtual ~ExecReportCache(void);

//callbacks for QAbstractTableModel

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
	bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

//QAbstractTableModel

	void AddRows(ExecutionReport* pExecutionReport);

	ExecutionReport* GetRow(int iRow);

	QList<ExecutionReport*> o_ExecutionReports;

	

};
