#ifndef BLOTTERFILTERPANE_H
#define BLOTTERFILTERPANE_H

#include <QWidget>
#include "ui_BlotterFilterPane.h"
#include "Defs.h"
class BlotterFilterPane : public QWidget, public Ui::BlotterFilterPane
{
	Q_OBJECT

public:
	BlotterFilterPane(QWidget *parent = 0);
	~BlotterFilterPane();

public slots:
		void OnApplyButton();
signals:
		void FilterApplied(ExecReportFilter* pFilter);
};

#endif // BLOTTERFILTERPANE_H
