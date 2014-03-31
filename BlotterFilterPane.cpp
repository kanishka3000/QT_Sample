#include "BlotterFilterPane.h"
#include "Defs.h"
BlotterFilterPane::BlotterFilterPane(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	connect(btnApply,SIGNAL(clicked(bool)),this,SLOT(OnApplyButton()) );
}

BlotterFilterPane::~BlotterFilterPane()
{

}

void BlotterFilterPane::OnApplyButton()
{
	ExecReportFilter* pFilter = new ExecReportFilter();
	pFilter->d_Price = spinPrice->text().toDouble();
	pFilter->d_Size = spinSize->text().toDouble();

	emit FilterApplied(pFilter);

}
