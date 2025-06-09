#include "SttIecSmvVectorWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"


//////////////////////////////////////////////////////////////////////////
CSttIecSmvVectorGroup::CSttIecSmvVectorGroup()
{
	m_pVectorI = NULL;
	m_pVectorU = NULL;
}

CSttIecSmvVectorGroup::~CSttIecSmvVectorGroup()
{

}

long CSttIecSmvVectorGroup::GetVectorCount()
{
	if (m_pVectorU == NULL && m_pVectorI == NULL)
	{
		return 0;
	}

	if (m_pVectorU == NULL || m_pVectorI == NULL)
	{
		return 1;
	}

	return 2;
}

void CSttIecSmvVectorGroup::InitVectors(POLAR_VECTORS_MNGR *pVectorsMngr)
{
	POLAR_VECTORS *pVectors_I = NULL, *pVectors_U = NULL;
	pVectorsMngr->SetVectors(GetVectorCount());

	if (m_pVectorI != NULL)
	{
		if (m_pVectorU != NULL)
		{
			pVectorsMngr->SetVectors(2);
			pVectors_I = pVectorsMngr->GetAt(0);
			pVectors_I->nAxis = 0;
			pVectors_I->SetVectors(4);
			pVectors_U = pVectorsMngr->GetAt(1);
			pVectors_U->nAxis = 1;
			pVectors_U->SetVectors(4);
		}
		else
		{
			pVectorsMngr->SetVectors(1);
			pVectors_I = pVectorsMngr->GetAt(0);
			pVectors_I->nAxis = 0;
			pVectors_I->SetVectors(4);
		}
	}
	else
	{
		if (m_pVectorU != NULL)
		{
			pVectorsMngr->SetVectors(1);
			pVectors_U = pVectorsMngr->GetAt(0);
			pVectors_U->nAxis = 1;
			pVectors_U->SetVectors(4);
		}
	}
	
	if (m_pVectorI != NULL)
	{
		pVectors_I->GetAt(0)->Init("Ia", 3);
		pVectors_I->GetAt(1)->Init("Ib", 3);
		pVectors_I->GetAt(2)->Init("Ic", 3);
		pVectors_I->GetAt(3)->Init("3I0", 3);
	}

	if (m_pVectorU != NULL)
	{
		pVectors_U->GetAt(0)->Init("Ua", 3);
		pVectors_U->GetAt(1)->Init("Ub", 3);
		pVectors_U->GetAt(2)->Init("Uc", 3);
		pVectors_U->GetAt(3)->Init("3U0", 3);
	}
}

//////////////////////////////////////////////////////////////////////////
CSttIecSmvGrid_Vector::CSttIecSmvGrid_Vector(QWidget* parent) 
	: CSttIecChsGridBase(parent)
{

}


void CSttIecSmvGrid_Vector::InitGridTitle()
{
	CString astrGridTitle[3];
	astrGridTitle[0]="";
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Smv_ChName"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Native_Amplitude"));
	//= {"", "通道名", "幅值"};
	int iGridWidth[3]={50, 200, 200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);

	SetRowCount(8);
	Show_StaticString(NULL, 0, 0, _T("Ia"));
	Show_StaticString(NULL, 1, 0, _T("Ib"));
	Show_StaticString(NULL, 2, 0, _T("Ic"));
	Show_StaticString(NULL, 3, 0, _T("3I0"));
	Show_StaticString(NULL, 4, 0, _T("Ua"));
	Show_StaticString(NULL, 5, 0, _T("Ub"));
	Show_StaticString(NULL, 6, 0, _T("Uc"));
	Show_StaticString(NULL, 7, 0, _T("3U0"));
}

void CSttIecSmvGrid_Vector::ShowVector(CDvmData *pVector, long nRow, POLAR_VECTORS *pRetArrVector)
{	//可以不判断pA、pB、pC的有效性
	CDvmValue *pA = NULL, *pB = NULL, *pC = NULL;
	CString strText;

	if (pVector == NULL)
	{
		pRetArrVector->nEnable = 0;
		Show_StaticString(pVector, nRow,     1, g_strEmptyString);
		Show_StaticString(pVector, nRow+1, 1, g_strEmptyString);
		Show_StaticString(pVector, nRow+2, 1, g_strEmptyString);

		Show_StaticString(pVector, nRow+3, 1, g_strEmptyString);//20220617 zhouhj 增加用于零序的刷新

		Show_StaticString(pVector, nRow,  2, g_strEmptyString);
		Show_StaticString(pVector, nRow+1,  2, g_strEmptyString);
		Show_StaticString(pVector, nRow+2,  2, g_strEmptyString);

		Show_StaticString(pVector, nRow+3, 2, g_strEmptyString);//20220617 zhouhj 增加用于零序的刷新
		return;
	}

	if (pRetArrVector == NULL)
	{
		return;
	}

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
	pA = pVector->FindByID_MmsAttr(_T("$A"));
	pB = pVector->FindByID_MmsAttr(_T("$B"));
	pC = pVector->FindByID_MmsAttr(_T("$C"));

	Show_StaticString(pA, nRow,     1, pA->m_strValue);
	Show_StaticString(pB, nRow+1, 1, pB->m_strValue);
	Show_StaticString(pC, nRow+2, 1, pC->m_strValue);

	Show_StaticString(pVector, nRow+3, 1, g_strEmptyString);//20220617 zhouhj 增加用于零序的刷新

	strText = stt_iec_rcd_get_ch_value_string(pA, TRUE, pA_Vector->dMag, pA_Vector->dAng,strUnit,3);
	Show_StaticString(pA, nRow,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pB, TRUE, pB_Vector->dMag, pB_Vector->dAng,strUnit,3);
	Show_StaticString(pB, nRow+1,  2, strText);
	strText = stt_iec_rcd_get_ch_value_string(pC, TRUE, pC_Vector->dMag, pC_Vector->dAng,strUnit,3);
	Show_StaticString(pC, nRow+2,  2, strText);

	Show_StaticString(pVector, nRow+3, 2, g_strEmptyString);//20220617 zhouhj 增加用于零序的刷新
	pA_Vector->dMag = fabs(pA_Vector->dMag);
	pB_Vector->dMag = fabs(pB_Vector->dMag);
	pC_Vector->dMag = fabs(pC_Vector->dMag);
}

void CSttIecSmvGrid_Vector::ShowVector_Empty()
{
// 	Show_StaticString(NULL, 0,     0, g_strEmptyString);
// 	Show_StaticString(NULL, 1, 0, g_strEmptyString);
// 	Show_StaticString(NULL, 2, 0, g_strEmptyString);
// 	Show_StaticString(NULL, 3, 0, g_strEmptyString);
// 	Show_StaticString(NULL, 4,     0, g_strEmptyString);
// 	Show_StaticString(NULL, 5, 0, g_strEmptyString);
// 	Show_StaticString(NULL, 6, 0, g_strEmptyString);
// 	Show_StaticString(NULL, 7, 0, g_strEmptyString);

	Show_StaticString(NULL, 0,     1, g_strEmptyString);
	Show_StaticString(NULL, 1, 1, g_strEmptyString);
	Show_StaticString(NULL, 2, 1, g_strEmptyString);
	Show_StaticString(NULL, 3, 1, g_strEmptyString);
	Show_StaticString(NULL, 4,     1, g_strEmptyString);
	Show_StaticString(NULL, 5, 1, g_strEmptyString);
	Show_StaticString(NULL, 6, 1, g_strEmptyString);
	Show_StaticString(NULL, 7, 1, g_strEmptyString);

	Show_StaticString(NULL, 0,  2, g_strEmptyString);
	Show_StaticString(NULL, 1,  2, g_strEmptyString);
	Show_StaticString(NULL, 2,  2, g_strEmptyString);
	Show_StaticString(NULL, 3, 2, g_strEmptyString);
	Show_StaticString(NULL, 4,  2, g_strEmptyString);
	Show_StaticString(NULL, 5,  2, g_strEmptyString);
	Show_StaticString(NULL, 6,  2, g_strEmptyString);
	Show_StaticString(NULL, 7, 2, g_strEmptyString);
}

void CSttIecSmvGrid_Vector::ShowVector(CSttIecSmvVectorGroup *pVectorGroup, POLAR_VECTORS_MNGR *pRetArrVectors)
{
	if (pVectorGroup->m_pVectorI != NULL)
	{
		ShowVector(pVectorGroup->m_pVectorI, 0, pRetArrVectors->GetAt(0));

		if (pVectorGroup->m_pVectorU != NULL)
		{
			ShowVector(pVectorGroup->m_pVectorU, 4, pRetArrVectors->GetAt(1));
		}
	}
	else
	{
		ShowVector(pVectorGroup->m_pVectorU, 4, pRetArrVectors->GetAt(0));
	}
}

//////////////////////////////////////////////////////////////////////////
QSttIecSmvVectorMainWidget::QSttIecSmvVectorMainWidget(QWidget *parent)
    : QWidget(parent)
{
	m_pIecRcdFuncWidget = this;

	m_pLayout = new QHBoxLayout(this);
	m_pWndVector = new QSttIecSmvPolarWidget(this);
	m_pGridVector = new CSttIecSmvGrid_Vector(this);
	m_pGridVector->setFont(*g_pSttGlobalFont);
	m_pGridVector->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridVector->InitGrid();
	m_pWndVector->setGeometry(0, 0, 200, 100);
	m_pGridVector->setGeometry(0, 0, 200, 100);

// 	QWidgetItem *pWgtItem = new QWidgetItem(m_pGridVector);
// 	m_pLayout->addItem(pWgtItem);
// 
// 	pWgtItem = new QWidgetItem(m_pWndVector);
// 	m_pLayout->addItem(pWgtItem);

	m_pLayout->addWidget(m_pGridVector);
	m_pLayout->addWidget(m_pWndVector);
	m_pLayout->setStretch(0, 1);
	m_pLayout->setStretch(1, 1);
	setLayout(m_pLayout);

	m_nCurrVectorIndex = -1;
	m_pCurrVector = NULL;
}

void QSttIecSmvVectorMainWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	m_listVector.DeleteAll();
	GetDvmDataset();
	m_nCurrVectorIndex = 0;
	m_pCurrVector = (CSttIecSmvVectorGroup *)m_listVector.GetAt(m_nCurrVectorIndex);
	InitVectorsMngr();  //更新矢量图绘图
	m_pGridVector->ShowVector_Empty();
}

void QSttIecSmvVectorMainWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	ShowCurrVector();
}

void QSttIecSmvVectorMainWidget::Release()
{
	delete this;
}


BOOL QSttIecSmvVectorMainWidget::NeedNextAndPrev()
{
	return TRUE;
}

void QSttIecSmvVectorMainWidget::NextPage()
{
	m_nCurrVectorIndex++;

	if (m_nCurrVectorIndex >= m_listVector.GetCount())
	{
		m_nCurrVectorIndex = 0;
	}

	m_pCurrVector = (CSttIecSmvVectorGroup *)m_listVector.GetAt(m_nCurrVectorIndex);
	InitVectorsMngr();  //更新矢量图绘图
	m_pGridVector->ShowVector_Empty();
	ShowCurrVector();
}

void QSttIecSmvVectorMainWidget::PrevPage()
{
	m_nCurrVectorIndex--;

	if (m_nCurrVectorIndex < 0)
	{
		m_nCurrVectorIndex = m_listVector.GetCount() - 1;
	}

	m_pCurrVector = (CSttIecSmvVectorGroup *)m_listVector.GetAt(m_nCurrVectorIndex);
	InitVectorsMngr();  //更新矢量图绘图
	m_pGridVector->ShowVector_Empty();
	ShowCurrVector();
}

void QSttIecSmvVectorMainWidget::ShowCurrVector()
{
	if (m_pCurrVector == NULL)
	{
		return;
	}

	m_pGridVector->ShowVector(m_pCurrVector, &m_oVectorsMngr);
	m_pWndVector->DrawTheVectors(&m_oVectorsMngr);
}

void QSttIecSmvVectorMainWidget::InitVectorsMngr()
{
	if (m_pCurrVector == NULL)
	{
		return;
	}

	m_pCurrVector->InitVectors(&m_oVectorsMngr);
}

void QSttIecSmvVectorMainWidget::AddVector(CDvmData *pDvmVector)
{
	CSttIecSmvVectorGroup *pVectorGroup = NULL;

	if (pDvmVector->m_strValue.GetLength() == 0 /*|| pDvmVector->m_strValue == _T("0")*/)//20221010 zhouhj 在value等于0时出现重复添加
	{
		pVectorGroup = new CSttIecSmvVectorGroup();
		pVectorGroup->m_strID = pDvmVector->m_strValue;
		m_listVector.AddTail(pVectorGroup);
	}
	else
	{
		pVectorGroup = (CSttIecSmvVectorGroup*)m_listVector.FindByID(pDvmVector->m_strValue);

		if (pVectorGroup == NULL)
		{
			pVectorGroup = new CSttIecSmvVectorGroup();
			pVectorGroup->m_strID = pDvmVector->m_strValue;
			m_listVector.AddTail(pVectorGroup);
		}
	}

	if (pDvmVector->m_strDataType == _T("I"))
	{
		pVectorGroup->m_pVectorI = pDvmVector;
	}
	else
	{
		pVectorGroup->m_pVectorU = pDvmVector;
	}
}

CDvmDataset* QSttIecSmvVectorMainWidget::GetDvmDataset()
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
	CDvmData *p = NULL;
	POS pos = m_pDvmDataset->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmData *)m_pDvmDataset->GetNext(pos);
		AddVector(p);
	}

	return m_pDvmDataset;
}

