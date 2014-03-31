#include "IndexModel.h"

IndexModel::IndexModel(QObject *parent)
	: QAbstractTableModel(parent)
{

}

IndexModel::~IndexModel()
{

}

int IndexModel::rowCount( const QModelIndex &parent ) const
{
	return map_Index.size();
}

int IndexModel::columnCount( const QModelIndex &parent ) const
{
	return 3;
}

QVariant IndexModel::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant();


	if (index.row() >= map_Index.size() || index.row() < 0)
		return QVariant();


	IndexObject* pIndex = lst_Index.at(index.row());

	if(!pIndex)

	{
		return QVariant();
	}
	
	if (index.column() == 0)
		return pIndex->s_IndexName;
	else if (index.column() == 1)
		return pIndex->d_IndexValue;
	else if(index.column() == 2)
		return pIndex->d_DiffFrmPrev;

	return QVariant();

	

}

QVariant IndexModel::headerData( int section, Qt::Orientation orientation, int role ) const
{


	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return tr("IndexName");

		case 1:
			return tr("IndexValue");
		case 2:
			return tr("Diff");

		default:
			return QVariant();
		}

	}
	return QVariant();

}

Qt::ItemFlags IndexModel::flags( const QModelIndex &index ) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;

}

bool IndexModel::setData( const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/ )
{
	if (!index.isValid())
		return false;


	return false;
}

bool IndexModel::insertRows( int position, int rows, const QModelIndex &index/*=QModelIndex()*/ )
{
	return false;
}

bool IndexModel::removeRows( int position, int rows, const QModelIndex &index/*=QModelIndex()*/ )
{
	return false;
}

void IndexModel::AddIndex( QString sIndexID, double dIndexValue, double dIndexDiff )
{
	QMap<QString,IndexObject*>::iterator itr = map_Index.find(sIndexID);

	IndexObject* pObject = NULL;
	int iPosition = 0;
	if(itr != map_Index.end())
	{
		pObject = *itr;
		iPosition = pObject->i_InternalIndex;
		
	}
	else
	{
		pObject = new IndexObject();
		pObject->s_IndexName = sIndexID;
		map_Index.insert(sIndexID,pObject);
		iPosition = lst_Index.size();
		pObject->i_InternalIndex = iPosition;
		lst_Index.insert(iPosition,pObject);
		
	}
	beginInsertRows(QModelIndex(), iPosition,iPosition);



	pObject->d_IndexValue = dIndexValue;
	pObject->d_DiffFrmPrev = dIndexDiff;

	endInsertRows();



}

IndexObject* IndexModel::GetRow( int iRow )
{
	return lst_Index.at(iRow);
}


