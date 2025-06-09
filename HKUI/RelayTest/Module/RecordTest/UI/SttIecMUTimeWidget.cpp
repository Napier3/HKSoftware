#include "SttIecMUTimeWidget.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
//#include "../../UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"




QSttIecMUTimeWidget::QSttIecMUTimeWidget(/*long nMUTimeType,*/QWidget *parent)
	: QWidget(parent)
{
	m_pMain_VLayout = NULL;
	m_pSVDelayData = NULL;
//	m_nMUTimeType = nMUTimeType;
	InitUI();
	SetIecMUTimeFont();
	m_pIecRcdFuncWidget = this;
}

QSttIecMUTimeWidget::~QSttIecMUTimeWidget()
{

}

void QSttIecMUTimeWidget::InitUI()
{
	m_pMain_VLayout = new QGridLayout(this);
	CString strTmp;
	strTmp = /*"测试时长(s):"*/g_sLangTxt_Gradient_TestDuration; //lcq
	m_pTimeLong_Label = new QLabel(strTmp,this);
	m_pTimeLong_Edit = new QLineEdit;
	strTmp = /*"当前误差(μs):"*/g_sLangTxt_State_UsCurrenterror; //lcq
	m_pCurrErrorValue_Label = new QLabel(strTmp,this);
	m_pCurrErrorValue_Edit = new QLineEdit;

	strTmp = /*"最大误差(μs):"*/g_sLangTxt_State_UsMaximumerror; //lcq
	m_pMaxErrorValue_Label = new QLabel(strTmp,this);
	m_pMaxErrorValue_Edit = new QLineEdit;
	strTmp = /*"最小误差(μs):"*/g_sLangTxt_State_UsMinimumerror; //lcq
	m_pMinErrorValue_Label = new QLabel(strTmp,this);
	m_pMinErrorValue_Edit = new QLineEdit;

// 	QFont font;
// 	font.setFamily(QString::fromUtf8("Agency FB"));
// 	font.setPointSize(20);
// 	m_pTimeLong_Label->setFont(font);
// 	m_pTimeLong_Edit->setFont(font);
// 	m_pCurrErrorValue_Label->setFont(font);
// 	m_pCurrErrorValue_Edit->setFont(font);
// 
// 	m_pMaxErrorValue_Label->setFont(font);
// 	m_pMaxErrorValue_Edit->setFont(font);
// 	m_pMinErrorValue_Label->setFont(font);
// 	m_pMinErrorValue_Edit->setFont(font);

	m_pTimeLong_Edit->setReadOnly(true);
	m_pCurrErrorValue_Edit->setReadOnly(true);
	m_pMaxErrorValue_Edit->setReadOnly(true);
	m_pMinErrorValue_Edit->setReadOnly(true);

	m_pMain_VLayout->addWidget(m_pTimeLong_Label,0,0,1,1);
	m_pMain_VLayout->addWidget(m_pTimeLong_Edit,0,1,1,1);
	m_pMain_VLayout->addWidget(m_pCurrErrorValue_Label,0,2,1,1);
	m_pMain_VLayout->addWidget(m_pCurrErrorValue_Edit,0,3,1,1);

	m_pMain_VLayout->addWidget(m_pMaxErrorValue_Label,1,0,1,1);
	m_pMain_VLayout->addWidget(m_pMaxErrorValue_Edit,1,1,1,1);
	m_pMain_VLayout->addWidget(m_pMinErrorValue_Label,1,2,1,1);
	m_pMain_VLayout->addWidget(m_pMinErrorValue_Edit,1,3,1,1);
}

void QSttIecMUTimeWidget::SetIecMUTimeFont()
{
	m_pTimeLong_Label->setFont(*g_pSttGlobalFont);
	m_pTimeLong_Edit->setFont(*g_pSttGlobalFont);
	m_pCurrErrorValue_Label->setFont(*g_pSttGlobalFont);
	m_pCurrErrorValue_Edit->setFont(*g_pSttGlobalFont);

	m_pMaxErrorValue_Label->setFont(*g_pSttGlobalFont);
	m_pMaxErrorValue_Edit->setFont(*g_pSttGlobalFont);
	m_pMinErrorValue_Label->setFont(*g_pSttGlobalFont);
	m_pMinErrorValue_Edit->setFont(*g_pSttGlobalFont);
}
void QSttIecMUTimeWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1、dsSV2……
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_pDataset_SVDelay != NULL)
	{
		CString strID;
		strID = pDvmDataset->m_strID.Mid(2);
		m_pSVDelayData = (CDvmData *)pXSttCap_61850->m_pDataset_SVDelay->FindByID(strID);
	}
}

void QSttIecMUTimeWidget::Release()
{
	delete this;
}

void QSttIecMUTimeWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	if (m_pSVDelayData != NULL)
	{
		double dChDelay = 0.0f,dRealDelay = 0.0f,dMaxDelay = 0.0f,dMinDelay = 0.0f,dRealError = 0.0f,dMaxError = 0.0f,dMinError = 0.0f;
		CString strID,strTmp;
		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_ChDelay;// .Format("%s%s",m_pSVDelayData->m_strID.GetString(),STT_MUTEST_$DelayError);
		CDvmValue *pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dChDelay = CString_To_double(pCurrValue->m_strValue);
		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_RealDelay;// 
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dRealDelay = CString_To_double(pCurrValue->m_strValue);
		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_MaxDelayError;// 
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dMaxDelay = CString_To_double(pCurrValue->m_strValue);
		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_MinDelayError;// 
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dMinDelay = CString_To_double(pCurrValue->m_strValue);
		}

		dRealError = dRealDelay-dChDelay;
		dMaxError = dMaxDelay/*-dChDelay*/;
		dMinError = dMinDelay/*-dChDelay*/;
		strTmp.Format(_T("%.03lf"),dRealError);
		m_pCurrErrorValue_Edit->setText(strTmp);
		strTmp.Format(_T("%.03lf"),dMaxError);
		m_pMaxErrorValue_Edit->setText(strTmp);
		strTmp.Format(_T("%.03lf"),dMinError);
		m_pMinErrorValue_Edit->setText(strTmp);

// 		strID = m_pSVDelayData->m_strID + STT_MUTEST_$MaxError;//.Format("%s%s",m_pSVDelayData->m_strID.GetString(),STT_MUTEST_$MaxError);
// 		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);
// 
// 		if (pCurrValue != NULL)
// 		{
// 			m_pMaxErrorValue_Edit->setText(pCurrValue->m_strValue);
// 		}
// 
// 		strID = m_pSVDelayData->m_strID + STT_MUTEST_$MinError;//.Format("%s%s",m_pSVDelayData->m_strID.GetString(),STT_MUTEST_$MinError);
// 		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);
// 
// 		if (pCurrValue != NULL)
// 		{
// 			m_pMinErrorValue_Edit->setText(pCurrValue->m_strValue);
// 		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_TimeLong;//.Format("%s%s",m_pSVDelayData->m_strID.GetString(),STT_MUTEST_DL_TimeLong$TimeLong);
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			m_pTimeLong_Edit->setText(pCurrValue->m_strValue);
		}
	}
}

void QSttIecMUTimeWidget::Config()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (m_pSVDelayData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("当前延时数据为空,清空时间精度结果失败.")*/g_sLangTxt_Gradient_TheCurDelay.GetString()); //lcq
		return;
	}

	pXSttCap_61850->g_oSVDelayTickCount.Enter();
	POS pos_value = m_pSVDelayData->GetHeadPosition();

	CDvmValue *pCurrValue = NULL,*pChildValue = NULL;

	while(pos_value)
	{
		pCurrValue = (CDvmValue *)m_pSVDelayData->GetNext(pos_value);

		if ((pCurrValue->m_strID.Find(STT_MUTEST_DL_ChDelay/*_T("$ChDelay")*/) != -1)||
			(pCurrValue->m_strID.Find(STT_MUTEST_DL_RealDelay/*_T("$RealDelay")*/) != -1))
		{
			continue;
		}

		pCurrValue->m_strValue = _T("");

	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("清空时间精度结果成功.")*/g_sLangTxt_Gradient_EmptyRes.GetString()); //lcq
}

