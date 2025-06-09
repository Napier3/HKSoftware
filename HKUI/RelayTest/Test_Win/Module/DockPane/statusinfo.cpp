#include "statusinfo.h"
#include "ui_statusinfo.h"

#include <QHBoxLayout>
#include <QSpacerItem>
//#include "../../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"

StatusInfo::StatusInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusInfo)
{
    ui->setupUi(this);
	m_bBlink = false;
	layout = new QHBoxLayout;
	
	init();
}

StatusInfo::~StatusInfo()
{
    delete ui;
}

void StatusInfo::init()
{
/*
	m_A = new QToolButton;
	m_B = new QToolButton;
	m_C = new QToolButton;
	m_D = new QToolButton;
	m_E = new QToolButton;
	m_F = new QToolButton;
	m_G = new QToolButton;
	m_H = new QToolButton;

	m_1 = new QToolButton;
	m_2 = new QToolButton;
	m_3 = new QToolButton;
	m_4 = new QToolButton;
	m_5 = new QToolButton;
	m_6 = new QToolButton;
	m_7 = new QToolButton;
	m_8 = new QToolButton;

	m_IA = new QToolButton;
	m_IB = new QToolButton;
	m_IC = new QToolButton;
	m_I0 = new QToolButton;
	
	m_V = new QToolButton;
	m_OV = new QToolButton;
	m_OI = new QToolButton;
	m_OH = new QToolButton;

	m_Run = new QToolButton;
	m_DCurrent = new QToolButton;
*/
}

void StatusInfo::initToolbutton(QToolButton *pToolBtn,const QString &strTitle,const QString &strPicName)
{
	//设置文本颜色
	QPalette text_palette = pToolBtn->palette();
	text_palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	pToolBtn->setPalette(text_palette);

	//设置文本粗体
	QFont &text_font = const_cast<QFont &>(pToolBtn->font());
	text_font.setWeight(QFont::Bold);

	pToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//设置图标
	QPixmap pixmap(strPicName);
	pToolBtn->setIcon(pixmap);
	pToolBtn->setIconSize(pixmap.size());
	pToolBtn->setText(strTitle);

	//设置大小
	pToolBtn->setFixedWidth(pixmap.width());
	pToolBtn->setAutoRaise(true);

	pToolBtn->setStyleSheet("background:transparent;");
}

void StatusInfo::setRuning(bool bRun)
{
	if(bRun)
	{
		if (m_bBlink==false)
		{
//			initToolbutton(m_Run,"Run",QString(":/SwichIcon/images/icon/2.png"));
			m_bBlink = true;
			return;
		}
		if (m_bBlink==true)
		{
//			initToolbutton(m_Run,"Run",QString(":/SwichIcon/images/icon/1.png"));
			m_bBlink = false;
			return;
		}
	}
	else
	{
//		initToolbutton(m_Run,"Run",QString(":/SwichIcon/images/icon/1.png"));
	}
}

void StatusInfo::setDC(bool bDC)
{
	m_bDCState = bDC;
	if(bDC)
	{
//		initToolbutton(m_DCurrent,"Udc",QString(":/SwichIcon/images/icon/2.png"));
	}
	else
	{
//		initToolbutton(m_DCurrent,"Udc",QString(":/SwichIcon/images/icon/1.png"));
	}
}

bool StatusInfo::getDCState()
{
	return m_bDCState;
}

void StatusInfo::initSwitchButton()
{
	QLayoutItem *child;
	while((child=layout->takeAt(0))!=0)
	{
		if(child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}

	layout->setSpacing(0);
/*
	layout->addWidget(m_Run);

	layout->addSpacing(2);
	layout->addWidget(m_DCurrent);

	layout->addSpacing(5);
	layout->addWidget(m_A);
	layout->addWidget(m_B);
	layout->addWidget(m_C);
	layout->addWidget(m_D);
	layout->addWidget(m_E);
	layout->addWidget(m_F);
	layout->addWidget(m_G);
	layout->addWidget(m_H);
	
	layout->addSpacing(5);
	
	layout->addWidget(m_IA);
	layout->addWidget(m_IB);
	layout->addWidget(m_IC);
	layout->addWidget(m_I0);
	
	layout->addWidget(m_V);
	layout->addWidget(m_OV);
	layout->addWidget(m_OI);
	layout->addWidget(m_OH);

	layout->addSpacing(5);
	layout->addWidget(m_1);
	layout->addWidget(m_2);
	layout->addWidget(m_3);
	layout->addWidget(m_4);
	layout->addWidget(m_5);
	layout->addWidget(m_6);
	layout->addWidget(m_7);
	layout->addWidget(m_8);

	QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	layout->addItem(horizontalSpacer);
	layout->setContentsMargins(0,0,0,0);
	setLayout(layout);
	
	initToolbutton(m_Run,"Run",QString(":/SwichIcon/images/icon/1.png"));
	initToolbutton(m_DCurrent,"Udc",QString(":/SwichIcon/images/icon/1.png"));
	
	initToolbutton(m_A,"A",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_B,"B",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_C,"C",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_D,"D",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_E,"E",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_F,"F",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_G,"G",QString(":/SwichIcon/images/icon/5.png"));
	initToolbutton(m_H,"H",QString(":/SwichIcon/images/icon/5.png"));

	initToolbutton(m_IA,"Ia",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_IB,"Ib",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_IC,"Ic",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_I0,"I0",QString(":/SwichIcon/images/icon/circle_red.png"));
	
	initToolbutton(m_V,"U",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_OV,"OV",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_OI,"OI",QString(":/SwichIcon/images/icon/circle_red.png"));
	initToolbutton(m_OH,"OH",QString(":/SwichIcon/images/icon/circle_red.png"));

	initToolbutton(m_1,"1",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_2,"2",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_3,"3",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_4,"4",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_5,"5",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_6,"6",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_7,"7",QString(":/SwichIcon/images/icon/4.png"));
	initToolbutton(m_8,"8",QString(":/SwichIcon/images/icon/4.png"));
*/
}

void StatusInfo::setSwitchStatus(/*CEventResult *pEventResult*/)
{
/*
	if ((pBinaryIn != NULL)&&(pBinaryIn[4].nSelect == 0))
	{
		initToolbutton(m_E,"E",QString(":/SwichIcon/images/icon/5.png"));
	}
	else if (pEventResult->m_BinIn[4] == 0)
	{
		initToolbutton(m_E,"E",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_E,"E",QString(":/SwichIcon/images/icon/3.png"));
	}

	if ((pBinaryIn != NULL)&&(pBinaryIn[5].nSelect == 0))
	{
		initToolbutton(m_F,"F",QString(":/SwichIcon/images/icon/5.png"));
	}
	else if (pEventResult->m_BinIn[5] == 0)
	{
		initToolbutton(m_F,"F",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_F,"F",QString(":/SwichIcon/images/icon/3.png"));
	}

	if ((pBinaryIn != NULL)&&(pBinaryIn[6].nSelect == 0))
	{
		initToolbutton(m_G,"G",QString(":/SwichIcon/images/icon/5.png"));
	}
	else if (pEventResult->m_BinIn[6] == 0)
	{
		initToolbutton(m_G,"G",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_G,"G",QString(":/SwichIcon/images/icon/3.png"));
	}

	if ((pBinaryIn != NULL)&&(pBinaryIn[7].nSelect == 0))
	{
		initToolbutton(m_H,"H",QString(":/SwichIcon/images/icon/5.png"));
	}
	else if (pEventResult->m_BinIn[7] == 0)
	{
		initToolbutton(m_H,"H",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_H,"H",QString(":/SwichIcon/images/icon/3.png"));
	}

	if (pEventResult->m_IBreak[0] == 1)
	{
		initToolbutton(m_IA,"Ia",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_IA,"Ia",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_IBreak[1] == 1)
	{
		initToolbutton(m_IB,"Ib",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_IB,"Ib",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_IBreak[2] == 1)
	{
		initToolbutton(m_IC,"Ic",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_IC,"Ic",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_IBreak[3] == 1)
	{
		initToolbutton(m_I0,"I0",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_I0,"I0",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_nUShort == 1)
	{
		initToolbutton(m_V,"U",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_V,"U",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_nUOverLoad == 1)
	{
		initToolbutton(m_OV,"OV",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_OV,"OV",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_nIOverLoad == 1)
	{
		initToolbutton(m_OI,"OI",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_OI,"OI",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	if (pEventResult->m_nOverHeat == 1)
	{
		initToolbutton(m_OH,"OH",QString(":/SwichIcon/images/icon/circle_yellow.png"));
	}
	else
	{
		initToolbutton(m_OH,"OH",QString(":/SwichIcon/images/icon/circle_red.png"));
	}

	//开出
	if (pEventResult->m_BinOut[0] == 1)
	{
		initToolbutton(m_1,"1",QString(":/SwichIcon/images/icon/3.png"));	//合上
	}
	else if (pEventResult->m_BinOut[0] == 0)
	{
		initToolbutton(m_1,"1",QString(":/SwichIcon/images/icon/4.png"));	//断开
	}
	else
	{
		initToolbutton(m_1,"1",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[1] == 1)
	{
		initToolbutton(m_2,"2",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[1] == 0)
	{
		initToolbutton(m_2,"2",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_2,"2",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[2] == 1)
	{
		initToolbutton(m_3,"3",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[2] == 0)
	{
		initToolbutton(m_3,"3",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_3,"3",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[3] == 1)
	{
		initToolbutton(m_4,"4",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[3] == 0)
	{
		initToolbutton(m_4,"4",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_4,"4",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[4] == 1)
	{
		initToolbutton(m_5,"5",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[4] == 0)
	{
		initToolbutton(m_5,"5",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_5,"5",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[5] == 1)
	{
		initToolbutton(m_6,"6",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[5] == 0)
	{
		initToolbutton(m_6,"6",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_6,"6",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[6] == 1)
	{
		initToolbutton(m_7,"7",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[6] == 0)
	{
		initToolbutton(m_7,"7",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_7,"7",QString(":/SwichIcon/images/icon/5.png"));
	}

	if (pEventResult->m_BinOut[7] == 1)
	{
		initToolbutton(m_8,"8",QString(":/SwichIcon/images/icon/3.png"));
	}
	else if (pEventResult->m_BinOut[7] == 0)
	{
		initToolbutton(m_8,"8",QString(":/SwichIcon/images/icon/4.png"));
	}
	else
	{
		initToolbutton(m_8,"8",QString(":/SwichIcon/images/icon/5.png"));
	}
*/
}