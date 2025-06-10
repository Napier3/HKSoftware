#include "QStateMonitorWidgetImp.h"

//////////////////////////////////////////////////////////////////////////
//

QStateMonitorWidgetImp::QStateMonitorWidgetImp(QWidget *parent)
: QSttInfWidgetBase(parent)
{
	m_pStateMonitor = NULL;

	m_bModeIsSingle = false;

	//数据过程太复杂，暂时无法优化
	m_pStateMonitor = new  QStateMonitorWidget(this);
	InitSttInfWidget(m_pStateMonitor);
}

QStateMonitorWidgetImp::~QStateMonitorWidgetImp()
{
	delete m_pStateMonitor;
	m_pStateMonitor = NULL;
}

void QStateMonitorWidgetImp::showEvent(QShowEvent *)
{
	
}


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

void QStateMonitorWidgetImp::SetPlotDigitMaxMinValue()
{
	//低周 更新最大最小值显示 suyang 20240527
	if (m_pStateMonitor)
	{
		m_pStateMonitor->ChangeListType(fre_type,40,60,40,60);
	}
}