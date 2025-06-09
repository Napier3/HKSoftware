#include "QStateMonitorWidgetImp.h"

#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
//////////////////////////////////////////////////////////////////////////
//

QStateMonitorWidgetImp::QStateMonitorWidgetImp(QWidget *parent)
: QSttInfWidgetBase(parent)
{
	m_pStateMonitor = NULL;
	m_bModeIsSingle = false;
	m_bHasInitFinished = false;  //是否已经初始化完成，没有初始化，不能进行操作
	m_nParaSetSecondValue = 1;
	m_dUMin = 0;
	m_dUMax = 0;
	m_dIMin = 0;
	m_dIMax = 0;

}

void QStateMonitorWidgetImp::showEvent(QShowEvent *event)
{
	InitStateMonitorWidget();
	QSttInfWidgetBase::showEvent(event);
}

void QStateMonitorWidgetImp::InitStateMonitorWidget()
{
	if (m_bHasInitFinished != NULL)
	{
		return;
	}

	m_bHasInitFinished = true;
	m_pStateMonitor = new  QStateMonitorWidget(this);
	m_pStateMonitor->m_nParaSetSecondValue = m_nParaSetSecondValue;
	m_pStateMonitor->SetChangedType(m_nType);
	m_pStateMonitor->SetSingle(m_bModeIsSingle);//dingxy 20240923 构造被覆盖，再次设置单通道
	if (m_bModeIsSingle)
	{
		m_pStateMonitor->InitStateMonitor(m_nChannel, m_nType, m_bStart, m_pConnectWidget);
	}
	else
	{
		m_pStateMonitor->SetParaSetSecondValue(m_nParaSetSecondValue);//20241029 suyang 一次值多通道需要更新单位
	}

	InitSttInfWidget(m_pStateMonitor);
	SetPlotDigitMaxMinValue(m_nType,m_dUMin,m_dUMax,m_dIMin,m_dIMax);
	
}


QStateMonitorWidgetImp::~QStateMonitorWidgetImp()
{
	if (m_pStateMonitor != 0)
	{
	delete m_pStateMonitor;
	m_pStateMonitor = NULL;
	}
}
// 
// void QStateMonitorWidgetImp::showEvent(QShowEvent *)
// {
// 	
// }


void QStateMonitorWidgetImp::InitStateMonitor(int nChannel, int nType, bool bStart, QWidget* pConnectWidget)
{
	m_nChannel = nChannel;
	m_nType = nType;
	m_bStart = bStart;
	m_pConnectWidget = pConnectWidget;

	if (m_pStateMonitor != NULL)
	{
		InitStateMonitor();
	}
}

void QStateMonitorWidgetImp::InitStateMonitor()
{
	m_pStateMonitor->InitStateMonitor(m_nChannel, m_nType, m_bStart, m_pConnectWidget);
}

void QStateMonitorWidgetImp::AddBinBoutPoint(long nIndex, double x, double y)
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->AddBinBoutPoint(nIndex, x, y);
	}
}


void QStateMonitorWidgetImp::OnRtDataChanged()
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->OnRtDataChanged();
	}
}

void QStateMonitorWidgetImp::StopStateMonitor()
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->StopStateMonitor();
	}
}

void QStateMonitorWidgetImp::StartStateMonitor()
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->StartStateMonitor();
	}
}

void QStateMonitorWidgetImp::UpdateLocalTime(double dLocalTime)
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->UpdateLocalTime(dLocalTime);
	}
}

void QStateMonitorWidgetImp::UpdateStateMonitorChs()
{
	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->UpdateStateMonitorChs();
	}
}


void QStateMonitorWidgetImp::SetSingle(bool bSingle)
{
	m_bModeIsSingle = bSingle;

	if (m_pStateMonitor != NULL)
	{
		m_pStateMonitor->SetSingle(m_bModeIsSingle);
	}
}


void QStateMonitorWidgetImp::SetSingle()
{
	m_pStateMonitor->SetSingle(m_bModeIsSingle);
}

// void QStateMonitorWidgetImp::SetPlotDigitMaxMinValue(int nChangedType)
// {
// // 	if (m_pStateMonitor)
// // 	{
// // 		m_pStateMonitor->UpdatePlotMaxMinValue(nChangedType);
// // 	}
// 	m_nType = nChangedType;
// }

void QStateMonitorWidgetImp::SetPlotDigitMaxMinValue( int nChangedType,double fUMin,double fUMax,double fIMin,double fIMax )
{
	if (m_nType != nChangedType)
	{
		m_nType = nChangedType;
	}

	m_dUMin = fUMin;
	m_dUMax = fUMax;
	m_dIMin = fIMin;
	m_dIMax = fIMax;

	if (m_pStateMonitor)
	{
		m_pStateMonitor->ChangeListType(m_nType,fUMin,fUMax,fIMin,fIMax);
	}
}

void QStateMonitorWidgetImp::SetParaSetSecondValue(int nParaSetSecondValue)
{
	m_nParaSetSecondValue = nParaSetSecondValue;
	if (m_pStateMonitor)
	{
		m_pStateMonitor->SetParaSetSecondValue(m_nParaSetSecondValue);
	}
}