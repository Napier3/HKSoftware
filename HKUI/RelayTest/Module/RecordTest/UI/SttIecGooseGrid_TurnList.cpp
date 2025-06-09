#include "SttIecGooseGrid_TurnList.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGoose.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"

CSttIecGooseGrid_TurnList::CSttIecGooseGrid_TurnList(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecGooseGrid_TurnList::~CSttIecGooseGrid_TurnList()
{

}

void CSttIecGooseGrid_TurnList::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (m_pCapDevice != NULL)
	{
		CCapDeviceGoose *pDvGoose = (CCapDeviceGoose*)m_pCapDevice;
		pDvGoose->m_oBinaryTurns.m_nCurrReadIndex = 0;
	}

	ShowDatas(NULL);
	//CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	//ShowDatas(pDvmDataset);
}

void CSttIecGooseGrid_TurnList::Release()
{
	delete this;
}

void CSttIecGooseGrid_TurnList::InitGridTitle()
{
	CString astrGridTitle[4];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Goose_SwitchTime"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Goose_RelativeTime"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Goose_Value"));
	xlang_GetLangStrByFile(astrGridTitle[3], _T("Native_Channel"));
	//= {"切换时间", "相对时间/us", "值", "通道"};
	int iGridWidth[4]={400, 150, 150, 250};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

void CSttIecGooseGrid_TurnList::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	//CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	//CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	//pXSttCap_61850->UpdateDvmDeviceDatas();

	//从实时变位列表取数据
	ShowTurnList();
}

void CSttIecGooseGrid_TurnList::ShowTurnList()
{
	CCapDeviceGoose *pDvGoose = (CCapDeviceGoose*)m_pCapDevice;
	CEpGooseBinaryTurns *pTurns = &pDvGoose->m_oBinaryTurns;
	long nCount = pTurns->GetCount();
	long nIndex = pTurns->m_nCurrReadIndex;
	PEP_GOOSE_BINARY_TURN pPrev = NULL, pCurr = NULL;

	for (; nIndex<nCount; nIndex++)
	{
		pCurr = pTurns->GetAtIndex(nIndex);
		pPrev = pTurns->FindPrevTurn(pCurr);
		pTurns->CalTimeRel(pPrev,pCurr);
		ShowTurn(pPrev,pCurr, nIndex);
	}

	pTurns->m_nCurrReadIndex = nIndex;
}

void CSttIecGooseGrid_TurnList::ShowTurn(PEP_GOOSE_BINARY_TURN pPrevTurn,PEP_GOOSE_BINARY_TURN pCurrTurn, long nRow)
{
	insertRow(NULL);
	CString strText,strPrevValue,strCurrValue;

	//"切换时间"
	//????  ep_cap_timeval_to_string_us
	ep_cap_timeval_to_string_ns(pCurrTurn->n64Time, strText);
	Update_StaticString(NULL, 0, 0, &strText);

	//"相对时间/us", 
	if (pCurrTurn->nTimeRel <= 0)
	{
		strText = _T("--");
	}
	else
	{
		strText.Format(_T("%d"), pCurrTurn->nTimeRel);
	}

	Update_StaticString(NULL, 0, 1, &strText);

	
	//"值"

	if (pPrevTurn == NULL)
	{
		ep_get_CapParseData_value(pCurrTurn->nChType,pCurrTurn->nChLenth, pCurrTurn->nValue, 0, strCurrValue);
		strText = strCurrValue;
	} 
	else
	{
		ep_get_CapParseData_value(pPrevTurn->nChType,pPrevTurn->nChLenth, pPrevTurn->nValue, 0, strPrevValue);
		ep_get_CapParseData_value(pCurrTurn->nChType,pCurrTurn->nChLenth, pCurrTurn->nValue, 0, strCurrValue);
		strText.Format(_T("%s -> %s"),strPrevValue.GetString(),strCurrValue.GetString());
	}

	Update_StaticString(NULL, 0, 2, &strText);
	
	//"通道"
	if (pCurrTurn->pChRef != NULL)
	{
		strText.Format(_T("%ld:"),pCurrTurn->nChIndex+1);
		strText += pCurrTurn->pChRef->m_strName;
//		Update_StaticString(NULL, 0, 3, &pCurrTurn->pChRef->m_strName);
	}
	else
	{
		strText.Format(_T("CH-%d"), pCurrTurn->nChIndex+1);
	}	

	Update_StaticString(NULL, 0, 3, &strText);
}

void CSttIecGooseGrid_TurnList::Config()
{
	if (m_pCapDevice == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前m_pCapDevice == NULL 清除失败.")*/g_sLangTxt_Currentfailed.GetString());
		return;
	}

	CCapDeviceGoose *pDvGoose = (CCapDeviceGoose*)m_pCapDevice;
	pDvGoose->m_oBinaryTurns.Reset();
	ShowDatas(NULL);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("清空变位列表成功.")*/g_sLangTxt_changelist.GetString());
}



