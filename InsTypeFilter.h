#pragma once
#include "InstrumentFilter.h"
#include <QObject>
class InstrumentSelector;
class InsTypeFilter :
	public InstrumentFilter
{
	Q_OBJECT
public:
	InsTypeFilter(InstrumentSelector* parent);
	virtual ~InsTypeFilter(void);

	virtual void DoFilter(QString sValue);

	virtual void SelectAndForward(Instrument* pInstrument, QString sOrderBook);


private:
	InstrumentSelector* p_Parent;
};
