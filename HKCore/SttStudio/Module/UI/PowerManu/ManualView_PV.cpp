//#include "stdafx.h"
#include "ManualView_PV.h"

#include <QHeaderView>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../../../Module/XLangResource_Native.h"

QManualView_PV::QManualView_PV()
{
	m_pPUParaWidget = NULL;		//电压电流设置
	m_pTabWidget = NULL;
}

QManualView_PV::~QManualView_PV()
{

}

void QManualView_PV::InitUI(int nFuncType)
{
	if (m_pPUParaWidget != NULL)
	{
		delete m_pPUParaWidget;
		m_pPUParaWidget = NULL;
	}


	m_pPUParaWidget = new QPowerManualGrid(m_pTabWidget);
	m_pTabWidget->removeTab(0);//先删除空的占位widget
    CString strText;
	xlang_GetLangStrByFile(strText, "Manual_PV");
	m_pTabWidget->insertTab(0, m_pPUParaWidget,/* "电压功率"*/g_sLangTxt_PowerManu_VolPower);

	m_pTabWidget->setCurrentIndex(0);

}

void QManualView_PV::slot_cb_DCClicked(bool bIsChecked)
{
	QPowerManualGrid *pBasicTestParaSet = NULL;
	m_pPUParaWidget->setMaxMinAndEDVal();
	pBasicTestParaSet = (QPowerManualGrid*)m_pPUParaWidget;
	pBasicTestParaSet->DCStateChanged(P_Common, bIsChecked);
}
