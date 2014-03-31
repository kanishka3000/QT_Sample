#ifndef INDEXMODEL_H
#define INDEXMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QList>
#include "Defs.h"

class IndexModel : public QAbstractTableModel
{
	

public:
	IndexModel(QObject *parent);
	~IndexModel();

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
	

	void AddIndex(QString sIndexID, double dIndexValue, double dIndexDiff);

	IndexObject* GetRow(int iRow);

private:

	QMap<QString,IndexObject*> map_Index;
	QList<IndexObject*> lst_Index;
	QModelIndex pIndex;
	
};

#endif // INDEXMODEL_H
