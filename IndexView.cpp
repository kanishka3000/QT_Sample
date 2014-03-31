#include "IndexView.h"
#include "IndexModel.h"
IndexView::IndexView(QWidget *parent)
	: QAbstractItemView(parent)
{

	p_Index = new QModelIndex;
	p_BottomLayout = new QHBoxLayout(this);
	p_BottomLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(p_BottomLayout);
}

IndexView::~IndexView()
{

}

QModelIndex IndexView::indexAt( const QPoint &point ) const
{
	
	return *p_Index;

}

void IndexView::scrollTo( const QModelIndex &index, ScrollHint hint /*= EnsureVisible */ )
{

}

QRect IndexView::visualRect( const QModelIndex &index ) const
{

	return QRect();
}

int IndexView::horizontalOffset() const
{
	return 0;
}

bool IndexView::isIndexHidden( const QModelIndex &index ) const
{
	return false;
}

QModelIndex IndexView::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
	return QModelIndex();
}

void IndexView::setSelection( const QRect &rect, QItemSelectionModel::SelectionFlags flags )
{

}

int IndexView::verticalOffset() const
{
	return 0;
}

QRegion IndexView::visualRegionForSelection( const QItemSelection &selection ) const
{
	return QRegion();
}

void IndexView::Init( QAbstractItemModel * sourceModel )
{
	QAbstractItemView::setModel(sourceModel);
	//connect(sourceModel,SIGNAL(rowsInserted( const QModelIndex, int, int  )), this,SLOT(OnDataRowsChanged( const QModelIndex , int , int  )));


}

void IndexView::OnDataRowsChanged( const QModelIndex  parent, int start, int end )
{

}

void IndexView::rowsInserted( QModelIndex pIndex,int iStart,int iEnd )
{
	QAbstractItemModel* pSource = model();

	IndexModel* pModel = dynamic_cast<IndexModel*>(pSource);

	if(!pModel)
		return;

	IndexObject* pObject = pModel->GetRow(iStart);
	QString sIndexName = pObject->s_IndexName;

	QMap<QString,IndexItem*>::iterator itr = mapSubscriptions.find(sIndexName);

	if(itr != mapSubscriptions.end())
	{
		IndexItem* pItem = *itr;
		pItem->SetIndexData(pObject);
	}

}

void IndexView::AddIndex( QString sIndexName )
{
	IndexItem* pItem = new IndexItem();
	
	p_BottomLayout->addWidget(pItem);

	mapSubscriptions.insert(sIndexName,pItem);
}

void IndexView::IndexAddingBegin()
{
	p_BottomLayout->addStretch();
}

void IndexView::AddSystemItem( QWidget* pItem )
{
	p_BottomLayout->addWidget(pItem);
}
