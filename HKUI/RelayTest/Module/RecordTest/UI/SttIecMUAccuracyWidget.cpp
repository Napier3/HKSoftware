#include "SttIecMUAccuracyWidget.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
//#include "../../UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../SttGlobalDef.h"
#include <QHeaderView>

extern CFont *g_pSttGlobalFont;

QSttIecMUAccuracyWidget::QSttIecMUAccuracyWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pIecSmvGrid_MUAccuracy = NULL;
	m_pMain_VLayout = NULL;
	m_pSVDelayData = NULL;
	InitUI();
	SetIecSmvGrid_MUAccuracyFont();
	m_pIecRcdFuncWidget = this;
}

QSttIecMUAccuracyWidget::~QSttIecMUAccuracyWidget()
{

}

void QSttIecMUAccuracyWidget::InitUI()
{
#ifdef _PSX_QT_LINUX_
	m_pIecSmvGrid_MUAccuracy = new CSttIecSmvGrid_MUAccuracy(this);
#else
	m_pIecSmvGrid_MUAccuracy = new CSttIecSmvMUAccuracyGrid(this);
#endif
	m_pIecSmvGrid_MUAccuracy->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecSmvGrid_MUAccuracy->setFont(*g_pSttGlobalFont);
	m_pIecSmvGrid_MUAccuracy->InitGrid();
	m_pBottom_HLayout = new QHBoxLayout;
	m_pMain_VLayout = new QVBoxLayout(this);
	CString strTmp;
	strTmp = /*"通道延时(μs):"*/g_sLangTxt_delay; //lcq
	m_pDelayChValue_Label = new QLabel(strTmp,this);
	m_pDelayChValue_Edit = new QLineEdit;
	strTmp = /*"实测延时(μs):"*/g_sLangTxt_Measured; //lcq
	m_pRealDelayValue_Label = new QLabel(strTmp,this);
	m_pRealDelayValue_Edit = new QLineEdit;
	strTmp = /*"延时误差(μs):"*/g_sLangTxt_error; //lcq
	m_pDelayValueError_Label = new QLabel(strTmp,this);
	m_pDelayValueError_Edit = new QLineEdit;

// 	QFont font;
// 	font.setFamily(QString::fromUtf8("Agency FB"));
// 	font.setPointSize(20);
// 	m_pDelayChValue_Label->setFont(font);
// 	m_pDelayChValue_Edit->setFont(font);
// 	m_pRealDelayValue_Label->setFont(font);
// 	m_pRealDelayValue_Edit->setFont(font);
// 	m_pDelayValueError_Label->setFont(font);
// 	m_pDelayValueError_Edit->setFont(font);
	m_pDelayChValue_Edit->setReadOnly(true);
	m_pRealDelayValue_Edit->setReadOnly(true);
	m_pDelayValueError_Edit->setReadOnly(true);

	m_pBottom_HLayout->addWidget(m_pDelayChValue_Label);
	m_pBottom_HLayout->addWidget(m_pDelayChValue_Edit);
	m_pBottom_HLayout->addWidget(m_pRealDelayValue_Label);
	m_pBottom_HLayout->addWidget(m_pRealDelayValue_Edit);
	m_pBottom_HLayout->addWidget(m_pDelayValueError_Label);
	m_pBottom_HLayout->addWidget(m_pDelayValueError_Edit);
	m_pMain_VLayout->addWidget(m_pIecSmvGrid_MUAccuracy);
	m_pMain_VLayout->addLayout(m_pBottom_HLayout);
}

void QSttIecMUAccuracyWidget::SetIecSmvGrid_MUAccuracyFont()
{
	m_pDelayChValue_Label->setFont(*g_pSttGlobalFont);
	m_pDelayChValue_Edit->setFont(*g_pSttGlobalFont);
	m_pRealDelayValue_Label->setFont(*g_pSttGlobalFont);
	m_pRealDelayValue_Edit->setFont(*g_pSttGlobalFont);
	m_pDelayValueError_Label->setFont(*g_pSttGlobalFont);
	m_pDelayValueError_Edit->setFont(*g_pSttGlobalFont);
}

void QSttIecMUAccuracyWidget::ShowDelayTimeUI(bool bShow)
{
	m_pDelayChValue_Label->setVisible(bShow);
	m_pDelayChValue_Edit->setVisible(bShow);
	m_pRealDelayValue_Label->setVisible(bShow);
	m_pRealDelayValue_Edit->setVisible(bShow);
	m_pDelayValueError_Label->setVisible(bShow);
	m_pDelayValueError_Edit->setVisible(bShow);
}

void QSttIecMUAccuracyWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (pCapDevice == NULL)
	{
		return;
	}

	m_pIecSmvGrid_MUAccuracy->m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1、dsSV2……
	m_pIecSmvGrid_MUAccuracy->ShowDatas(pDvmDataset);
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_pDataset_SVDelay != NULL)
	{
		CString strID;
		strID = pDvmDataset->m_strID.Mid(2);
		m_pSVDelayData = (CDvmData *)pXSttCap_61850->m_pDataset_SVDelay->FindByID(strID);
	}
}

void QSttIecMUAccuracyWidget::Release()
{
	delete this;
}

void QSttIecMUAccuracyWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();
	m_pIecSmvGrid_MUAccuracy->UpdateDatas();

	if ((m_pSVDelayData != NULL)&&(m_pDelayChValue_Edit->isVisible()))
	{
		CString strID,strTmp;
		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_ChDelay/*Format("%s$ChDelay",.GetString())*/;
		CDvmValue *pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);
		double dDelayError = 0.0f,dChDelay = 0.0f,dCurrDelay = 0.0f;

		if (pCurrValue != NULL)
		{
			dChDelay = CString_To_double(pCurrValue->m_strValue);
			m_pDelayChValue_Edit->setText(pCurrValue->m_strValue);
		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_RealDelay /*.Format("%s$RealDelay",m_pSVDelayData->m_strID.GetString())*/;
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dCurrDelay = CString_To_double(pCurrValue->m_strValue);
			m_pRealDelayValue_Edit->setText(pCurrValue->m_strValue);
		}

		dDelayError = dCurrDelay - dChDelay;
		strTmp.Format(_T("%.03lf"),dDelayError);
		m_pDelayValueError_Edit->setText(strTmp);
	}
}

void QSttIecMUAccuracyWidget::UpdateChName()
{
	if (m_pIecSmvGrid_MUAccuracy == NULL)
	{
		return;
	}

	m_pIecSmvGrid_MUAccuracy->UpdateChName();
}
