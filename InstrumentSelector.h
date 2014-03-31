#ifndef INSTRUMENTSELECTOR_H
#define INSTRUMENTSELECTOR_H

#include <QWidget>
#include <QString>
#include "ui_InstrumentSelector.h"
#include "InstrumentFilter.h"
class InstrumentSelectorCalback;
class BaseWnd;
class Trader;
class InstrumentSelector : public QWidget, public Ui::InstrumentSelector
{
	Q_OBJECT

public:
	InstrumentSelector(QWidget *parent = 0);

	void CreateFilters();

	~InstrumentSelector();
	void RegisterRightPane(QObject* pCalback);
	void Init(BaseWnd* pParent);

signals:
	void OnInstrumentSelected(QString sInstrument);
	void InstrumentSelected(Instrument* pInstrument, QString sOrderBook);

public slots:
	void OnComboSelect(QString sInstrument);
	void AddInstrument(QString sInstrument);
	void OnInstrumentTypeSelected(QString sType);

	void RearrangeChain(QString sType);

	void OnOrderBookSelected(Instrument* pInstrument, QString sOrderBook);
	void SelectInstrument(Instrument* pInstrument, QString sOrderBook);
	

protected:
	QMap<QString,InstrumentFilter*> map_FilterChain;
	BaseWnd* p_Parent;


};

#endif // INSTRUMENTSELECTOR_H
