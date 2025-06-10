#include "QPowerDiagramWidgetImp.h"

//////////////////////////////////////////////////////////////////////////
//

QPowerDiagramWidgetImp::QPowerDiagramWidgetImp(QWidget *parent)
: QSttInfWidgetBase(parent)
{
	m_pPowerWidget = NULL;
	m_pPowerSttTestResource = NULL;
	m_pVOL = NULL;//��ʼ��ѹ
	m_pCUR = NULL;//��ʼ����
	m_pVolChList = NULL;//ȫ����ѹͨ����Դ����
	m_pCurChList = NULL; //ȫ������ͨ����Դ����

	m_nTimerID = -1;
}

QPowerDiagramWidgetImp::~QPowerDiagramWidgetImp()
{

}


void QPowerDiagramWidgetImp::showEvent(QShowEvent *)
{
	if (m_pPowerWidget != NULL)
	{
		return;
	}

	m_pPowerWidget = new PowerDiagramWidget(this);
	InitSttInfWidget(m_pPowerWidget);

	setPropertyOfParaSet();
	setData();
	initData();
}

void QPowerDiagramWidgetImp::setPropertyOfParaSet()
{
	m_pPowerWidget->setPropertyOfParaSet(m_pPowerSttTestResource);
}

void QPowerDiagramWidgetImp::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource)
{
	m_pPowerSttTestResource = pSttTestResource;

	if (m_pPowerWidget != NULL)
	{
		setPropertyOfParaSet();
	}
}

void QPowerDiagramWidgetImp::setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList)
{
	m_pVOL = pVOL;
	m_pCUR = pCUR;

	m_pVolChList = pVolChList;
	m_pCurChList = pCurChList;

	if (m_pPowerWidget != NULL)
	{
		setData();
	}
}


void QPowerDiagramWidgetImp::setData()
{
	m_pPowerWidget->setData(m_pVOL, m_pCUR, m_pVolChList, m_pCurChList);
}

void QPowerDiagramWidgetImp::initData()
{
	if (m_pPowerWidget != NULL)
	{
		m_pPowerWidget->initData();
	}
}

void QPowerDiagramWidgetImp::updatePowerData()
{
	if (m_pPowerWidget != NULL)
	{
		m_pPowerWidget->updatePowerData();
	}
}

void QPowerDiagramWidgetImp::cmbVolSetChanged()
{
	if (m_pPowerWidget != NULL)
	{
		m_pPowerWidget->cmbVolSetChanged();
	}
}

void QPowerDiagramWidgetImp::cmbCurSetChanged()
{
	if (m_pPowerWidget != NULL)
	{
		m_pPowerWidget->cmbCurSetChanged();
	}
}

// void QPowerDiagramWidgetImp::TimerStart()
// {
// 	if (m_pPowerWidget != NULL)
// 	{
// 		m_pPowerWidget->TimerStart();
// 	}
// }

// void QPowerDiagramWidgetImp::TimerStop(bool bUpdate)
// {
// 	if (m_pPowerWidget != NULL)
// 	{
// 		m_pPowerWidget->TimerStop(bUpdate);
// 	}
// }
// 
void QPowerDiagramWidgetImp::TimerStart()
{
	m_nTimerID = startTimer(1000);
}

void QPowerDiagramWidgetImp::TimerStop(bool bUpdate)
{
	killTimer(m_nTimerID);
	m_nTimerID = -1;
}

void QPowerDiagramWidgetImp::timerEvent(QTimerEvent *event)
{
	if(m_nTimerID == event->timerId())
	{
	if (m_pPowerWidget != NULL)
	{
			m_pPowerWidget->getPowerValueTest();
			m_pPowerWidget->getVolSetChangedTest();
			m_pPowerWidget->getCurSetChangedTest();
			m_pPowerWidget->setShowVolCurPhaseEdit();
			QWidget::timerEvent( event );
		}	
	}
}

