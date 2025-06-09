#include "SttIecGooseGrid_RT.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"

CSttIecGooseGrid_RT::CSttIecGooseGrid_RT(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecGooseGrid_RT::~CSttIecGooseGrid_RT()
{

}

void CSttIecGooseGrid_RT::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);
}

void CSttIecGooseGrid_RT::Release()
{
	delete this;
}

void CSttIecGooseGrid_RT::InitGridTitle()
{
	CString astrGridTitle[3];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Native_Channel"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("sDataType"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("sValue"));
	//= {"通道", "数据类型","数值"};
	int iGridWidth[4]={400, 150, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void CSttIecGooseGrid_RT::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	ShowDataEx(pChData, nRow);
	nRow++;
}

void CSttIecGooseGrid_RT::ShowDataEx(CDvmData *pChData, int nRow)
{
	Update_StaticString(pChData, nRow, 0, &pChData->m_strName);
	Update_StaticString(pChData, nRow, 1, &pChData->m_strDataType); 

	//2024-9-5 wuxinyi 修改判断条件不进导致单点时无法正确显示true和false
	if (pChData->m_strDataType == /*_T("单点")*/g_sLangTxt_GOOSE_Single/*.GetString()*/)
	{
		CString strTemp;
		if (pChData->m_strValue.IsEmpty())
		{
			Update_StaticStringColor(pChData, nRow, 2, &g_strEmptyString);
		}
		else if (pChData->m_strValue == _T("0"))
		{
			strTemp = _T("FALSE");
			Update_StaticStringColor(pChData, nRow, 2, &strTemp);
		}
		else
		{
			strTemp = _T("TRUE");
			Update_StaticStringColor(pChData, nRow, 2, &strTemp);
		}
	}
	else
	{
		Update_StaticStringColor(pChData, nRow, 2, &pChData->m_strValue);
	}
}

void CSttIecGooseGrid_RT::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	//pXSttCap_61850->UpdateDvmDeviceDatas();
	pCapDevice->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecGooseGrid_RT::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;
	ShowDataEx(pChData, nRow);
}

