#include "SttIecSmvGrid_Harm_Content.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#define SmvGrid_Harm_Content_MAX_ROW_NUM      33


CSttIecSmvGrid_Harm_Content::CSttIecSmvGrid_Harm_Content(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_Harm_Content::~CSttIecSmvGrid_Harm_Content()
{

}

void CSttIecSmvGrid_Harm_Content::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);
}

void CSttIecSmvGrid_Harm_Content::Release()
{
	delete this;
}

extern long g_nXSttRcdInitChDvmData_Harm;// = 31;

void CSttIecSmvGrid_Harm_Content::InitGridTitle()
{
	CString astrGridTitle[SmvGrid_Harm_Content_MAX_ROW_NUM];
	
	astrGridTitle[0] = /*_T("通道")*/g_sLangTxt_Native_Channel;
	astrGridTitle[1] = /*_T("直流(V/A)")*/g_sLangTxt_Native_DCVoltAmp;
	astrGridTitle[2] = /*_T("基波(V/A)")*/g_sLangTxt_Native_FundamentalVA;

	CString strTemp;
	strTemp = _T("次(%)");
	CString strNum[30] = {"2","3", "4", "5", "6", "7"
		,"8", "9", "10", "11", "12", "13", "14", "15"
		,"16", "17", "18", "19", "20", "21", "22", "23"
		,"24", "25", "26", "27", "28", "29", "30", "31"};
	for (int i=3; i<33;i++)
	{
		astrGridTitle[i]=strNum[i-3] + strTemp;
	}


	int iGridWidth[SmvGrid_Harm_Content_MAX_ROW_NUM]={150, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100};

	long nCols = SmvGrid_Harm_Content_MAX_ROW_NUM;

	if (g_nXSttRcdInitChDvmData_Harm < 31)
	{
		nCols = g_nXSttRcdInitChDvmData_Harm + 2;
	}

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, nCols);
}

void CSttIecSmvGrid_Harm_Content::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pData, nRow, 0, &pChData->m_strName);
	ShowDataEx(pChData, nRow);

	nRow++;
}


void CSttIecSmvGrid_Harm_Content::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecSmvGrid_Harm_Content::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;
	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_Harm_Content::ShowDataEx(CDvmData *pChData, int nRow)
{
	ShowAttrValue(pChData, nRow, 1, _T("$DC"),-1);
	ShowAttrValue(pChData, nRow, 2, _T("$Base"),-1);  

	long nHarm = 2;
	CString strID;

	for (nHarm=2; nHarm <= g_nXSttRcdInitChDvmData_Harm; nHarm++)
	{
		strID.Format(_T("$h%d"), nHarm);
		ShowAttrValue(pChData, nRow, nHarm + 1, strID, 3);
	}
}

void CSttIecSmvGrid_Harm_Content::ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);
	CString strBaseID = pData->m_strID + _T("$Base");
	CDvmValue *pBaseValue = (CDvmValue*)pData->FindByID(strBaseID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, nCol, &g_strEmptyString);
	}
	else
	{
		if (nPrecision == -1)
		{
			Show_StaticDoubleString(pData, nRow, nCol, pFind->m_strValue,3);
		}
		else
		{
			double dValue = CString_To_double(pFind->m_strValue);
			double dBaseValue = CString_To_double(pBaseValue->m_strValue);
			dValue = 100 * dValue / dBaseValue;
			CString strValue;
			strValue.Format(_T("%.3f"), dValue);
			Update_StaticString(pData, nRow, nCol, &strValue);
		}
	}
}

