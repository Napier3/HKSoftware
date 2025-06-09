//#include "stdafx.h"
#include "ManualView_IV.h"

#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../../../Module/XLangResource_Native.h"

QManualView_IV::QManualView_IV()
{
	m_pUIParaWidget = NULL;		//电压电流设置
	m_pHarmUIParaWidget = NULL;
	m_pTabWidget = NULL;
}

QManualView_IV::~QManualView_IV()
{

}

void QManualView_IV::InitUI(int nFuncType)
{
	if (m_pUIParaWidget != NULL)
	{
		delete m_pUIParaWidget;
		m_pUIParaWidget = NULL;
	}

	if (m_pHarmUIParaWidget != NULL)
	{
		delete m_pHarmUIParaWidget;
		m_pHarmUIParaWidget = NULL;
	}

	m_pUIParaWidget = new QBasicTestParaSet(m_pTabWidget);
	m_pTabWidget->removeTab(0);//先删除空的占位widget
    CString strText;
	xlang_GetLangStrByFile(strText, "Manual_IV");
	m_pTabWidget->insertTab(0, m_pUIParaWidget, strText);

	if ((nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		m_pHarmUIParaWidget = new QBasicTestParaSet(m_pTabWidget);
		m_pHarmUIParaWidget->setFont(*g_pSttGlobalFont);
		//strText = _T("谐波");
		//m_pTabWidget->insertTab(1, m_pHarmUIParaWidget, strText);
        m_pTabWidget->insertTab(1, m_pHarmUIParaWidget, g_sLangTxt_State_Harmonicwave); //lcq 3.13
	}

	m_pTabWidget->setCurrentIndex(0);

}

void QManualView_IV::slot_cb_DCClicked(bool bIsChecked)
{
	QBasicTestParaSet *pBasicTestParaSet = NULL;
	pBasicTestParaSet = (QBasicTestParaSet*)m_pUIParaWidget;
	pBasicTestParaSet->DCStateChanged(P_Common, bIsChecked);
	m_pUIParaWidget->setMaxMinAndEDVal();
}
