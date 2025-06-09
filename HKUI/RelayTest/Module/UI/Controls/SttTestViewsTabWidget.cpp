#include "SttTestViewsTabWidget.h"
#include <QEvent>
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../SttTestCntrFrameBase.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSttTestViewsTabWidget::QSttTestViewsTabWidget(QWidget* pParent) : QTabWidget(pParent)
{
	m_pCurrMacroView = NULL;
	m_pCurrTabView = NULL;
	m_bHasInitView = false;
	m_bHasClosed = false;
	InitConnects();
}

QSttTestViewsTabWidget::~QSttTestViewsTabWidget()
{
	
}

void QSttTestViewsTabWidget::InitConnects()
{
	connect(this, SIGNAL(currentChanged(int)), this, SLOT(slot_CurrChangedTabWidget(int)));
}

void QSttTestViewsTabWidget::SetCurrMacroView(QWidget *pMacroView)
{
	m_pCurrMacroView = pMacroView;
	m_bHasInitView = false;
}

void QSttTestViewsTabWidget::slot_CurrChangedTabWidget(int nTabIndex)
{
	if (m_bHasClosed)
	{
		return;
	}

	if (nTabIndex<0)
	{
		return;
	}

	QWidget* pWidget = widget(nTabIndex);

	if (pWidget == m_pCurrTabView)
	{
		return;
	}

	QWidget *pCharWidget = g_theTestCntrFrame->GetCharEditMainWidget();

	if (pCharWidget == NULL)
	{
		m_pCurrTabView = pWidget;
		return;
	}
//	m_pCurrTabView = pWidget;

	if ((pWidget == m_pCurrMacroView)&&(!m_bHasInitView))
	{
		m_pCurrTabView = pWidget;
		m_bHasInitView = true;
		return;
	}

// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("XXXXXXXXXXXXX-----------1"));
	if (m_pCurrTabView == m_pCurrMacroView)
	{
		g_theTestCntrFrame->CharDrawView_Prepare();
	} 
	else if (m_pCurrTabView == pCharWidget)
	{
		g_theTestCntrFrame->TemplateView_Prepare();
	}


	m_pCurrTabView = pWidget;
//	emit sig_CurrClickChanged(nTabIndex);
}

