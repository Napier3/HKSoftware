#include "SttIecFT3OriginalMsgWidget.h"
#include "../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../UI/Module/CommonMethod/commonMethod.h"

CSttIecFT3OriginalMsgWidget::CSttIecFT3OriginalMsgWidget(QWidget* pparent)
{
	m_pIecRcdFuncWidget = this;
	m_pLineNumberPlan = new QSttIecFT3LineNumberPlanTextEdit();
	m_pMainLayout = new QHBoxLayout();
	m_pMainLayout->addWidget(m_pLineNumberPlan);
	this->setLayout(m_pMainLayout);
}

CSttIecFT3OriginalMsgWidget::~CSttIecFT3OriginalMsgWidget()
{

}

void CSttIecFT3OriginalMsgWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
}

void CSttIecFT3OriginalMsgWidget::Release()
{
	delete this;
}

void CSttIecFT3OriginalMsgWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CCapDevice6044 *pCapDevice6044 = (CCapDevice6044 *)pCapDevice;
	m_pLineNumberPlan->SetHexValue(pCapDevice6044->m_szPkgDatas,pCapDevice6044->m_nPkgDatasLenth/*strlen(pCapDevice6044->m_szPkgDatas)*/);
}
