#include "SttIecGooseGrid_PkgStc.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../XLangResource_Native.h"

CSttIecGooseGrid_PkgStc::CSttIecGooseGrid_PkgStc(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecGooseGrid_PkgStc::~CSttIecGooseGrid_PkgStc()
{

}

void CSttIecGooseGrid_PkgStc::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset(); //dsGoose1、dsGoose2……
	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDvmDataset->GetParent();
	CDvmDataset *pGooseErr = (CDvmDataset *)pLDevice->FindByID(_T("dsGooseErr"));

	CDvmData *pData = GetDvmData(pGooseErr);
	ShowDatas(pData);
}

void CSttIecGooseGrid_PkgStc::Release()
{
	delete this;
}

void CSttIecGooseGrid_PkgStc::InitGridTitle()
{
	CString astrGridTitle[2] = {/*"项目"*/g_sLangTxt_Smv_Item, /*"数目"*/g_sLangTxt_Smv_Number};
	int iGridWidth[2]={500, 300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 2);
}

void CSttIecGooseGrid_PkgStc::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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


void CSttIecGooseGrid_PkgStc::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecGooseGrid_PkgStc::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);
}

CDvmData* CSttIecGooseGrid_PkgStc::GetDvmData(CDvmDataset *pGooseErr)
{
	if (pGooseErr == NULL)
	{
		return NULL;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pCapDevice;
	ASSERT(iecfg_IsTypeGoose(pCapDevice->m_nType));

	long nPos = pCapDevice->m_strID.Find(_T("dsGin"));   //dsGin1、dsGin2……
	CString strIndex = pCapDevice->m_strID.Mid(nPos + 5);
	CString strDataID;
	strDataID.Format(_T("Goose%s"), strIndex.GetString());//Goose1、Goose2……

	return ((CDvmData *)pGooseErr->FindByID(strDataID));
}