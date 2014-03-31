#ifndef INDEXVIEW_H
#define INDEXVIEW_H

#include <QAbstractItemView>
#include <QObject>
#include <QWidget>
#include <QMap>
#include <QHBoxLayout>
#include "IndexItem.h"
class IndexView : public QAbstractItemView
{
	Q_OBJECT

public:
	IndexView(QWidget *parent);
	~IndexView();

	QModelIndex indexAt( const QPoint &point ) const;
	void scrollTo( const QModelIndex &index, ScrollHint hint = EnsureVisible );
	QRect visualRect( const QModelIndex &index ) const;
//
	void Init( QAbstractItemModel * sourceModel );
//
//protected:
	int horizontalOffset() const;
	bool isIndexHidden( const QModelIndex &index ) const;
	QModelIndex moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );
	void setSelection( const QRect &rect, QItemSelectionModel::SelectionFlags flags );
	int verticalOffset() const;
	QRegion visualRegionForSelection( const QItemSelection &selection ) const;
	QModelIndex* p_Index;

	QHBoxLayout* p_BottomLayout;
	void AddIndex(QString sIndexName);
	void IndexAddingBegin();
	void AddSystemItem(QWidget* pItem);

	QMap<QString,IndexItem*> mapSubscriptions;

public slots:
	void rowsInserted(QModelIndex pIndex,int iStart,int iEnd);

private:


	public slots:
		void OnDataRowsChanged(const QModelIndex  parent, int start, int end );

	
};

#endif // INDEXVIEW_H
