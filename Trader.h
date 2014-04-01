#pragma once

#include <QObject>
#include <QMap>
#include <QList>
#include "MainWnd.h"
#include "BaseWnd.h"
#include "Defs.h"

class ExecReportCache;
class ExecutionFilterModel;
class IndexModel;

class Trader:public QObject
{
	Q_OBJECT
public:
	Trader(void);
	virtual ~Trader(void);

	void SaveExecReports();

	void Init();

	void LoadExecReports();

	virtual BaseWnd* CreateWnd(Defs::Windows eWindow, bool bSingleInstance = false);
	virtual void LoadInstruments();
	void GetAllInstruments(QList<Instrument*>& lstInstruments);
	QString ConverToInstrumentID(QString sInstrumentID);
	Instrument* GetInstrument(QString sInstrumentID);
	void OnBusinessData(NewOrder* pNewOrder);
	double d_Time;
	int i_OrderIDCount;
	

signals:
	void OnExecutionReport(ExecutionReport* pExecutionReport);

public slots:
	void OnTimer();
	
public:
	MainWnd* p_MainWnd;
	QMap<int,QList<BaseWnd*>> map_Windows;
	ExecReportCache* p_ExecReportCache;
	IndexModel* p_IndexModel;
	bool b_LoadUpComplete;

protected:
	QMap<QString,Instrument*> map_Instruments;

	QMap<QString,QString> map_SymbolToInstID;

};
