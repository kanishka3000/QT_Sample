#include "BlotterCache.h"
#include <QVariant>
#include "Defs.h"
ExecReportCache::ExecReportCache(QObject* pParent)
:QAbstractTableModel(pParent)
{
}

ExecReportCache::~ExecReportCache(void)
{


}

int ExecReportCache::rowCount( const QModelIndex &parent ) const
{
	return o_ExecutionReports.count();
}

int ExecReportCache::columnCount( const QModelIndex &parent ) const
{
	return 7;
}

QVariant ExecReportCache::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant();


	if (index.row() >= o_ExecutionReports.size() || index.row() < 0)
		return QVariant();

	if(role != Qt::DisplayRole)
		return QVariant();

	ExecutionReport* pReport = o_ExecutionReports.at(index.row());

	if(!pReport)
		return QVariant();


	if (index.column() == 0)
		return pReport->s_Symbol;
	else if (index.column() == 1)
		return pReport->d_Price;
	else if(index.column() == 2)
		return pReport->d_Size;
	else if(index.column() == 3)
		return pReport->i_Side;
	else if(index.column() == 4)
		return pReport->s_TIF;
	else if(index.column() == 5)
		return pReport->s_OrderTye;
	else if(index.column() == 6)
		return pReport->s_ExpiryDate;



	return QVariant();
}

QVariant ExecReportCache::headerData( int section, Qt::Orientation orientation, int role ) const
{

	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
		     return tr("Symbol");
		case 1:
		     return tr("Price");
		case 2:
			return tr("Size");
		case 3:
			return tr("Side");
		case 4:
			return tr("TIF");
		case 5:
			return tr("Order Type");
		case 6:
			return tr("Expiry Date");

		default:
		     return QVariant();
		}
		
	}
	return QVariant();
}

Qt::ItemFlags ExecReportCache::flags( const QModelIndex &index ) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool ExecReportCache::setData( const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/ )
{
	if (!index.isValid())
		return false;


	return false;
}

bool ExecReportCache::insertRows( int position, int rows, const QModelIndex &index/*=QModelIndex()*/ )
{


	return false;
}

bool ExecReportCache::removeRows( int position, int rows, const QModelIndex &index/*=QModelIndex()*/ )
{
	return false;
}

void ExecReportCache::AddRows( ExecutionReport* pExecutionReport )
{
	int iPostion = o_ExecutionReports.count();
	beginInsertRows(QModelIndex(),iPostion,iPostion);

	o_ExecutionReports.insert(iPostion,pExecutionReport);
	

	endInsertRows();
}

ExecutionReport* ExecReportCache::GetRow( int iRow )
{
	if(iRow < 0)
		return NULL;

	return o_ExecutionReports.at(iRow);
}
