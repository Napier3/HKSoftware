#include "stdafx.h"
#include "IntellTerminalWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewIntelligentTerminal.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"

QIntellTerminalWidget::QIntellTerminalWidget(QWidget *pParent): QWidget(pParent)
{
 
}

QIntellTerminalWidget::~QIntellTerminalWidget()
{

}

void QIntellTerminalWidget::InitUI()
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pIntellTerminalTab = new QSttTabWidget(this);
	m_pMainGridLayout->addWidget(m_pIntellTerminalTab, 0, 0, 1, 10);
	
	m_pBinarySet_PushButton = new QPushButton(g_sLangTxt_Native_Switch,this);
	m_pMainGridLayout->addWidget(m_pBinarySet_PushButton, 3, 8, 1, 2);

	m_pIntellTerminalParas = NULL;
	m_pEvent = NULL;

}

void QIntellTerminalWidget::InitConnect()
{
	connect(m_pIntellTerminalTab, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
}

void QIntellTerminalWidget::SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* m_pIntellTerminalParas,CEventResult* pEvent)
{
	m_pTestResource = pSttTestResource;
	m_pIntellTerminalParas = m_pIntellTerminalParas;
	m_pEvent = pEvent;

	UpdateData();
}

void QIntellTerminalWidget::UpdateData()
{
	if(m_pIntellTerminalParas == NULL || m_pTestResource == NULL)
	{
		return;
	}
	//开入量设置
	Global_CheckBinSelect(m_pIntellTerminalParas->m_binIn,g_nBinCount,m_pIntellTerminalParas->m_nBinLogic);
}

void QIntellTerminalWidget::StartInit()
{
	m_pBinarySet_PushButton->setDisabled(true);
}

void QIntellTerminalWidget::StopInit()
{
	m_pBinarySet_PushButton->setDisabled(false);
}

void QIntellTerminalWidget::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (g_pIntelligentTest == NULL)
	{
		return;
	}

	BOOL bVisibleBottomCtrlsGoose = (g_pIntelligentTest->m_pSttIntelGoutToBinParaWidget == m_pIntellTerminalTab->currentWidget());
	BOOL bVisibleBottomCtrlsFT3 = (g_pIntelligentTest->m_pFT3OutParaWidget == m_pIntellTerminalTab->currentWidget());
	BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);

	m_pBinarySet_PushButton->setVisible(bVisibleBottomCtrls);
}
