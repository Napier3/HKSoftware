#include "SttIecSmvSequenceWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"


//////////////////////////////////////////////////////////////////////////
CSttIecSmvGrid_Sequence::CSttIecSmvGrid_Sequence(QWidget* parent) 
	: CSttIecChsGridBase(parent)
{

}


void CSttIecSmvGrid_Sequence::InitGridTitle()
{
	CString astrGridTitle[3];
	astrGridTitle[0]="";
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Smv_ChName"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Native_Amplitude"));
	//= {"", "通道名", "幅值"};
	int iGridWidth[3]={50, 200, 200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);

	CString strName[6];
	xlang_GetLangStrByFile(strName[0],_T("sAphase"));
	xlang_GetLangStrByFile(strName[1],_T("sBphase"));
	xlang_GetLangStrByFile(strName[2],_T("sCphase"));
	xlang_GetLangStrByFile(strName[3],_T("Native_PositiveSeq"));
	xlang_GetLangStrByFile(strName[4],_T("Native_NegativeSeq"));
	xlang_GetLangStrByFile(strName[5],_T("Native_ZeroSeq"));

	SetRowCount(6);
	Show_StaticString(NULL, 0, 0, strName[0]/*_T("A相")*/);
	Show_StaticString(NULL, 1, 0, strName[1]/*_T("B相")*/);
	Show_StaticString(NULL, 2, 0, strName[2]/*_T("C相")*/);
	Show_StaticString(NULL, 3, 0, strName[3]/*_T("正序")*/);
	Show_StaticString(NULL, 4, 0, strName[4]/*_T("负序")*/);
	Show_StaticString(NULL, 5, 0, strName[5]/*_T("零序")*/);

	Show_StaticString(NULL, 3, 1, g_strEmptyString);//20220617 zhouhj
	Show_StaticString(NULL, 4, 1, g_strEmptyString);
	Show_StaticString(NULL, 5, 1, g_strEmptyString);
}

void CSttIecSmvGrid_Sequence::ShowVector(CDvmData *pVector, POLAR_VECTORS *pRetArrVector)
{	//可以不判断pA、pB、pC的有效性
	CDvmValue *pPositive = NULL, *pNegative = NULL, *pZero = NULL;
	CDvmValue *pA = NULL, *pB = NULL, *pC = NULL;
	CString strText;

	POLAR_VECTOR *pA_Vector = pRetArrVector->pArrVector;
	POLAR_VECTOR *pB_Vector = pRetArrVector->pArrVector + 1;
	POLAR_VECTOR *pC_Vector = pRetArrVector->pArrVector + 2;

	CString strUnit;

	if (pVector->m_strDataType == _T("I"))
	{
		strUnit = _T("A");
	}
	else if (pVector->m_strDataType == _T("U"))
	{
		strUnit = _T("V");
	}

	pRetArrVector->nEnable = 1;
	pPositive = pVector->FindByID_MmsAttr(_T("$Positive"));
	pNegative = pVector->FindByID_MmsAttr(_T("$Negative"));
	pZero = pVector->FindByID_MmsAttr(_T("$Zero"));
	pA = pVector->FindByID_MmsAttr(_T("$A"));
	pB = pVector->FindByID_MmsAttr(_T("$B"));
	pC = pVector->FindByID_MmsAttr(_T("$C"));

	Show_StaticString(pA, 0, 1, pA->m_strValue);
	Show_StaticString(pB, 1, 1, pB->m_strValue);
	Show_StaticString(pC, 2, 1, pC->m_strValue);

	strText = stt_iec_rcd_get_ch_value_string(pA, TRUE,strUnit);
	Show_StaticString(pA, 0,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pB, TRUE,strUnit);
	Show_StaticString(pB, 1,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pC, TRUE,strUnit);
	Show_StaticString(pC, 2,  2, strText);

	strText = stt_iec_rcd_get_ch_value_string(pPositive, TRUE, pA_Vector->dMag, pA_Vector->dAng,strUnit);
	Show_StaticString(pPositive, 3,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pNegative, TRUE, pB_Vector->dMag, pB_Vector->dAng,strUnit);
	Show_StaticString(pNegative, 4,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pZero, TRUE, pC_Vector->dMag, pC_Vector->dAng,strUnit);
	Show_StaticString(pZero, 5,  2, strText);
}

//////////////////////////////////////////////////////////////////////////
QSttIecSmvSequenceMainWidget::QSttIecSmvSequenceMainWidget(QWidget *parent)
    : QWidget(parent)
{
	m_pIecRcdFuncWidget = this;

	m_pLayout = new QHBoxLayout(this);
	m_pWndVector = new QSttIecSmvPolarWidget(this);
	m_pGridSequence = new CSttIecSmvGrid_Sequence(this);
	m_pGridSequence->setFont(*g_pSttGlobalFont);
	m_pGridSequence->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridSequence->InitGrid();
	m_pWndVector->setGeometry(0, 0, 200, 100);
	m_pGridSequence->setGeometry(0, 0, 200, 100);

	m_pLayout->addWidget(m_pGridSequence);
	m_pLayout->addWidget(m_pWndVector);
	m_pLayout->setStretch(0, 1);
	m_pLayout->setStretch(1, 1);
	setLayout(m_pLayout);

	m_nCurrSequenceIndex = -1;
	m_pCurrVector = NULL;
	InitSequencesMngr();  //更新矢量图绘图
}

void QSttIecSmvSequenceMainWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	GetDvmDataset();
	
	m_nCurrSequenceIndex = 0;
	m_pCurrVector = (CDvmData *)m_pDvmDataset->GetAt(m_nCurrSequenceIndex);
}

void QSttIecSmvSequenceMainWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	ShowCurrSequence();
}

void QSttIecSmvSequenceMainWidget::Release()
{
	delete this;
}


BOOL QSttIecSmvSequenceMainWidget::NeedNextAndPrev()
{
	return TRUE;
}

void QSttIecSmvSequenceMainWidget::NextPage()
{
	m_nCurrSequenceIndex++;

	if (m_nCurrSequenceIndex >= m_pDvmDataset->GetCount())
	{
		m_nCurrSequenceIndex = 0;
	}

	m_pCurrVector = (CDvmData *)m_pDvmDataset->GetAt(m_nCurrSequenceIndex);
	ShowCurrSequence();
}

void QSttIecSmvSequenceMainWidget::PrevPage()
{
	m_nCurrSequenceIndex--;

	if (m_nCurrSequenceIndex < 0)
	{
		m_nCurrSequenceIndex = m_pDvmDataset->GetCount() - 1;
	}

	m_pCurrVector = (CDvmData *)m_pDvmDataset->GetAt(m_nCurrSequenceIndex);
	ShowCurrSequence();
}

void QSttIecSmvSequenceMainWidget::ShowCurrSequence()
{
	if (m_pCurrVector == NULL)
	{
		return;
	}

	m_pGridSequence->ShowVector(m_pCurrVector, m_oVectorsMngr.GetAt(0));
	m_pWndVector->DrawTheVectors(&m_oVectorsMngr);
}

void QSttIecSmvSequenceMainWidget::InitSequencesMngr()
{
	m_oVectorsMngr.SetVectors(1);
	POLAR_VECTORS *pVectors = m_oVectorsMngr.GetAt(0);
	pVectors->SetVectors(3);
	pVectors->GetAt(0)->Init2(0);
	pVectors->GetAt(1)->Init2(1);
	pVectors->GetAt(2)->Init2(2);
}

CDvmDataset* QSttIecSmvSequenceMainWidget::GetDvmDataset()
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pCapDevice;
	ASSERT(iecfg_IsTypeAnalog(pCapDevice->m_nType));

	CDvmDataset *pDatasetRef = pCapDevice->GetDvmDataset();  //此处获取的是dsSV1、dsSV2……

	if (pDatasetRef == NULL)
	{
		return NULL;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDatasetRef->GetParent();
	CString strID = pDatasetRef->m_strID + _T("$");
	strID += CAP_DATASET_MAP_ID_Vector;

	m_pDvmDataset = ((CDvmDataset *)pLDevice->FindByID(strID));

	return m_pDvmDataset;
}

