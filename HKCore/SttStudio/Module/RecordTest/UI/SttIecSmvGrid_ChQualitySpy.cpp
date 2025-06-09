#include "SttIecSmvGrid_ChQualitySpy.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"


CSttIecSmvGrid_ChQualitySpy::CSttIecSmvGrid_ChQualitySpy(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_ChQualitySpy::~CSttIecSmvGrid_ChQualitySpy()
{

}

void CSttIecSmvGrid_ChQualitySpy::IecRcdFunc(CCapDeviceBase *pCapDevice)
{

	m_pCapDevice = pCapDevice;
	ShowDatas(pCapDevice);
}

void CSttIecSmvGrid_ChQualitySpy::Release()
{
	delete this;
}

void CSttIecSmvGrid_ChQualitySpy::InitGridTitle()
{
	CString astrGridTitle[4];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Native_Channel"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Native_Validity"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Native_Overhaul"));
	xlang_GetLangStrByFile(astrGridTitle[3], _T("IEC_Quality"));
	//= {"通道" , "有效性" , "检修" , "品质" };
	int iGridWidth[SmvGrid_ChQualitySpy_MAX_ROW_NUM]={400, 150, 150, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SmvGrid_ChQualitySpy_MAX_ROW_NUM);
}
 
void CSttIecSmvGrid_ChQualitySpy::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCapDeviceSmvCh *pSmvChData = (CCapDeviceSmvCh*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pSmvChData, nRow, 0, &pSmvChData->m_strName);
	ShowSpy(pSmvChData,nRow);
	nRow++;
}


void CSttIecSmvGrid_ChQualitySpy::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	pXSttCap_61850->UpdateDvmDeviceDatas();
	UpdateDatas();
}


void CSttIecSmvGrid_ChQualitySpy::UpdateData(CExBaseObject *pData, int nRow)
{
	CCapDeviceSmvCh *pSmvChData = (CCapDeviceSmvCh*)pData;
	ShowSpy(pSmvChData,nRow);
}

void CSttIecSmvGrid_ChQualitySpy::ShowSpy(CCapDeviceSmvCh *pSmvChData,int& nRow)
{

	DWORD dwQuality = pSmvChData->m_dwQuality & 0X0000FFFF;
	CString strHexQuality;
	strHexQuality.Format(_T("0x%04X"),dwQuality);
	CString strBinQuality = HexToBin(strHexQuality);

	CString strOverhaul;
	if (dwQuality>>11 & 0x01)
	{
		strOverhaul = /*_T("1:测试")*/g_sLangTxt_IEC_test; //lcq
	} 
	else
	{
		strOverhaul = /*_T("0:正常")*/g_sLangTxt_IEC_normal;//lcq
	}

	int nValidity = dwQuality & 0x03;//dxy 20240204 按照16进制保留最后两个字节
	CString strValidity;
	switch (nValidity)
	{
	case 0:
		strValidity = /*_T("00:好")*/g_sLangTxt_IEC_good;//lcq
		break;
	case 1:
		strValidity = /*_T("01:无效")*/g_sLangTxt_IEC_invalid; //lcq
		break;
	case 2:
		strValidity = /*_T("10:保留")*/g_sLangTxt_IEC_reserved;//lcq
		break;
	case 3:
		strValidity = /*_T("11:可疑")*/g_sLangTxt_IEC_questionable; //lcq
		break;
	}

	Show_StaticString(pSmvChData,nRow,1,&strValidity);
	Show_StaticString(pSmvChData,nRow,2,&strOverhaul);
	Show_StaticString(pSmvChData,nRow,3,&strHexQuality);
}