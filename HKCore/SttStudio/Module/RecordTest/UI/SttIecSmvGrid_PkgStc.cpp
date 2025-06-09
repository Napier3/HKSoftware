#include "SttIecSmvGrid_PkgStc.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../XLangResource_Native.h"

CSttIecSmvGrid_PkgStc::CSttIecSmvGrid_PkgStc(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_PkgStc::~CSttIecSmvGrid_PkgStc()
{

}

void CSttIecSmvGrid_PkgStc::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	//2022-5-28  lijunqing
	CDvmDataset *pSVErr = NULL;
	CDvmData *pDataSv = NULL;

	FindDvmDataForCtrl(pCapDevice, CAP_DATASET_MAP_ID_SVERR, &pSVErr, &pDataSv);

	if (pDataSv != NULL)
	{
		ShowDatas(pDataSv);
	}

/*
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1、dsSV2……
	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDvmDataset->GetParent();
	CDvmDataset *pSVErr = (CDvmDataset *)pLDevice->FindByID(CAP_DATASET_MAP_ID_SVERR);

	CDvmData *pData = GetDvmData(pSVErr);
	ShowDatas(pData);
*/
}

void CSttIecSmvGrid_PkgStc::Release()
{
	delete this;
}

void CSttIecSmvGrid_PkgStc::InitGridTitle()
{
	CString astrGridTitle[2] = {/*"项目"*/g_sLangTxt_Smv_Item, /*"数目"*/g_sLangTxt_Smv_Number};
	int iGridWidth[2]={500, 300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 2);
}

void CSttIecSmvGrid_PkgStc::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pValue, nRow, 0, &pValue->m_strName);
	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);

	nRow++;
}


void CSttIecSmvGrid_PkgStc::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecSmvGrid_PkgStc::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);
}

/*
CDvmData* CSttIecSmvGrid_PkgStc::GetDvmData(CDvmDataset *pSVErr)
{
	if (pSVErr == NULL)
	{
		return NULL;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pCapDevice;
	ASSERT(iecfg_IsTypeAnalog(pCapDevice->m_nType));

	long nPos = pCapDevice->m_strID.Find(_T("dsSV"));   //dsSV1、dsSV2……
	CString strIndex = pCapDevice->m_strID.Mid(nPos + 4);
	CString strDataID;
	strDataID.Format(_T("SV%s"), strIndex.GetString());//SV1、SV2……

	return ((CDvmData *)pSVErr->FindByID(strDataID));
}
*/
