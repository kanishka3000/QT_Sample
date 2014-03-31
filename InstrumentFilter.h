#ifndef INSTRUMENTFILTER_H
#define INSTRUMENTFILTER_H

#include <QObject>
#include <QString>
#include <QComboBox>
#include <QVector>
#include <QSet>
#include "Defs.h"

class InstrumentFilter : public QObject
{
	Q_OBJECT

public:
	InstrumentFilter(QObject *parent);
	~InstrumentFilter();

	virtual void AddWidget(QComboBox* pWidget);;

	virtual void AddInstruments(Instrument* pInstrument);

	virtual void Reset();

	virtual void SelectAndForward(Instrument* pInstrument, QString sOrderBook);

public slots:

	virtual void DoFilter(QString sValue);

public:
	InstrumentFilter* p_Prev;
	InstrumentFilter* p_Next;

	QString s_DisplayField;

	QString s_FilterField;
	QVariant o_FilterValue;

	


protected:
	QComboBox* p_Widget;

	QVector<Instrument*> vec_Items;
	QMap<QString,int> set_UniqueItems;
	
};

#endif // INSTRUMENTFILTER_H
