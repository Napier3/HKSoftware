#include "SttIecSmvGrid_Harm.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#define SmvGrid_Harm_MAX_ROW_NUM      33


CSttIecSmvGrid_Harm::CSttIecSmvGrid_Harm(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_Harm::~CSttIecSmvGrid_Harm()
{

}

void CSttIecSmvGrid_Harm::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);
}

void CSttIecSmvGrid_Harm::Release()
{
	delete this;
}

extern long g_nXSttRcdInitChDvmData_Harm;// = 31;

void CSttIecSmvGrid_Harm::InitGridTitle()
{
	//暂时先写到31次谐波
	CString astrGridTitle[SmvGrid_Harm_MAX_ROW_NUM];
	
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Native_Channel"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Native_DC"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Native_Fundamental"));

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,_T("Harm_Times"));
	CString strNum[30] = {"2","3", "4", "5", "6", "7"
		,"8", "9", "10", "11", "12", "13", "14", "15"
		,"16", "17", "18", "19", "20", "21", "22", "23"
		,"24", "25", "26", "27", "28", "29", "30", "31"};
	for (int i=3; i<33;i++)
	{
		astrGridTitle[i]=strNum[i-3] + strTemp;
	}
	/*= {"通道", "直流","基波","2次", "3次", "4次", "5次", "6次", "7次"
									,"8次", "9次", "10次", "11次", "12次", "13次", "14次", "15次"
									,"16次", "17次", "18次", "19次", "20次", "21次", "22次", "23次"
									,"24次", "25次", "26次", "27次", "28次", "29次", "30次", "31次"};*/

	int iGridWidth[SmvGrid_Harm_MAX_ROW_NUM]={150, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
						, 100, 100, 100};

	long nCols = SmvGrid_Harm_MAX_ROW_NUM;

	if (g_nXSttRcdInitChDvmData_Harm < 31)
	{
		nCols = g_nXSttRcdInitChDvmData_Harm + 2;
	}

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, nCols);
}

void CSttIecSmvGrid_Harm::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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


void CSttIecSmvGrid_Harm::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecSmvGrid_Harm::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;
	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_Harm::ShowDataEx(CDvmData *pChData, int nRow)
{
	ShowAttrValue(pChData, nRow, 1, _T("$DC"));
	ShowAttrValue(pChData, nRow, 2, _T("$Base"));   //？？？？以前的ATO2D的模型中，没有基波？？？

	long nHarm = 2;
	CString strID;

	for (nHarm=2; nHarm <= g_nXSttRcdInitChDvmData_Harm; nHarm++)
	{
		strID.Format(_T("$h%d"), nHarm);
		ShowAttrValue(pChData, nRow, nHarm + 1, strID, 3);
	}
}