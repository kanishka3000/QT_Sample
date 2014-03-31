#ifndef INDEXITEM_H
#define INDEXITEM_H

#include <QWidget>
#include "ui_IndexItem.h"
#include "Defs.h"

class IndexItem : public QWidget
{
	Q_OBJECT

public:
	IndexItem(QWidget *parent = 0);
	~IndexItem();
	void SetIndexData(IndexObject* pIndex);

private:
	Ui::IndexItem ui;
};

#endif // INDEXITEM_H
