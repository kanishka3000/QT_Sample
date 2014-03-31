#include "IndexItem.h"

IndexItem::IndexItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

IndexItem::~IndexItem()
{

}

void IndexItem::SetIndexData( IndexObject* pIndex )
{
	ui.lblIndexName->setText(pIndex->s_IndexName);
	QString sIndexValue;
	sIndexValue.sprintf("%f",pIndex->d_IndexValue);
	ui.lblIndexValue->setText(sIndexValue);
	QString sIndexDiff;
	sIndexDiff.sprintf("%f",pIndex->d_DiffFrmPrev);
	ui.lblDiff->setText(sIndexDiff);

}
