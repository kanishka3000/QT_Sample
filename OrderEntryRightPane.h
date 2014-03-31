#ifndef ORDERENTRYRIGHTPANE_H
#define ORDERENTRYRIGHTPANE_H

#include <QWidget>
#include <QString>
#include <QMap>
#include "ui_OrderEntryRightPane.h"

class Instrument;

typedef QPair<Instrument*,QString> RightPaneItem;
typedef QMap<QString,RightPaneItem > RightPaneMap;

class OrderEntryRightPane : public QWidget, public Ui::OrderEntryRightPane
{
	Q_OBJECT

public:
	OrderEntryRightPane(QWidget *parent = 0);
	~OrderEntryRightPane();
	void RegisterInstrumentSelector(QObject* pInstrumentSelector);

signals:
	void OnInstrumentSelected(QString sInstrument);
	void InstrumentSelected(Instrument* pInstrument, QString sOrderBook);
	
public slots:
	void AddInstrument(QString sInstrument);
	void OnItemSelected( QListWidgetItem * current, QListWidgetItem * previous);
	void OnInstrumentSelected(Instrument* pInstrument, QString sOrderBook);

protected:
	RightPaneMap map_Items;

};

#endif // ORDERENTRYRIGHTPANE_H
