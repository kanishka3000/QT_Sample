#pragma once
#include "InstrumentFilter.h"
#include <QObject>
class OrderBookFilter :public InstrumentFilter
{
	Q_OBJECT
public:
	OrderBookFilter(QObject *parent);
	virtual ~OrderBookFilter(void);
	virtual void AddInstruments(Instrument* pInstrument);
	virtual void DoFilter(QString sValue);
	virtual void SelectAndForward( Instrument* pInstrument, QString sOrderBook );

signals:
	void InstrumentSelected(Instrument* pInstrument, QString sOrderBook);
};
