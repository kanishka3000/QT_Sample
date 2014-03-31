#include "UnityBar.h"
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include "Trader.h"
UnityBar::UnityBar(QWidget *parent,Trader* pTrader)
	: BaseWnd(parent,pTrader)
{
	setupUi(this);
	p_MainLayout = new QVBoxLayout();
	setLayout(p_MainLayout);
	//QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect(this);
	//effect->setOpacity(0.5);

	//this->setGraphicsEffect(effect);


	QPushButton* pPushOne = new QPushButton(parent);
	pPushOne->setText("One");
	p_MainLayout->addWidget(pPushOne);

	pPushOne->setParent(parent);

	setWindowOpacity(0.5);

}

UnityBar::~UnityBar()
{

}
