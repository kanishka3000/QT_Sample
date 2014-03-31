#ifndef ORDERENTRYCENTERWND_H
#define ORDERENTRYCENTERWND_H

#include <QWidget>
#include "ui_OrderEntryCenterWnd.h"

class BaseWnd;
class NewOrder;
class Instrument;
class ExecutionReport;
class OrderEntryCenterWnd : public QWidget, public Ui::OrderEntryCenterWnd
{
	Q_OBJECT

public:
	OrderEntryCenterWnd(QWidget *parent = 0);
	~OrderEntryCenterWnd();

	void Init(BaseWnd* pParent) ;
	void PopulateFromExecutionReport(ExecutionReport* pReport);
public slots:
	void OnSubmit();
	void OnInstrumentSelected(QString sInstrument);
	void OnInstrumentSelected(Instrument* pInstrument, QString sOrderBook);

	void PopulateCurrentOrder();
	void OnSideChanged(int iIndex);

signals:
	void OnNewOrder(NewOrder* pNewOrder);

public:
	BaseWnd* p_ParentWnd;

protected:
	QString s_Instrument;
	QString s_OrderBook;
	Instrument* p_CurentInstrument;

	QMap<QString,NewOrder*> map_Tabs;
	NewOrder* p_CurrentOrder;
};

#endif // ORDERENTRYCENTERWND_H
