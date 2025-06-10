#include "SttHtmlRptGen_ShortTimeOver.h"
#include "../../UI/SttTestCntrCmdDefine.h"
#include "../SttXHtmlRptGenFactoryBase.h"
#include "../../UI/ShortTimeOver/QttMacroParaEditViewShortTimOver.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"


CSttHtmlRptGen_ShortTimeOver::CSttHtmlRptGen_ShortTimeOver()
{

}

CSttHtmlRptGen_ShortTimeOver::~CSttHtmlRptGen_ShortTimeOver()
{

}

void CSttHtmlRptGen_ShortTimeOver::GenHtml()
{
	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenShortTimeOver();
	GenRootDiv_End();
}

void CSttHtmlRptGen_ShortTimeOver::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>测试名称:短时过量输入</h1>");
}

void CSttHtmlRptGen_ShortTimeOver::GenRootDiv()
{
	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());
}

void CSttHtmlRptGen_ShortTimeOver::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}

void CSttHtmlRptGen_ShortTimeOver::GenShortTimeOver()
{
	GenShortTimeOver_Table_th("ShortTimeOver");
	GenShortTimeOver_Table_th_Data();
	GenModule_Table_te();
}


void CSttHtmlRptGen_ShortTimeOver::GenShortTimeOver_Table_th(const CString &strTypeID)
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("编号");
	Gen_Table_th("通道名称");
	Gen_Table_th("幅值");
	Gen_Table_th("施加次数");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_ShortTimeOver::GenShortTimeOver_Table_th_Data()
{
// 	CSttTestResourceBase *pParaSetSttTestResource = g_theTestCntrFrame->GetSttTestResource();
// 	if (pParaSetSttTestResource == NULL) 
// 	{
// 		return;
// 	}
// 	CExBaseList pCurChList = pParaSetSttTestResource->m_oCurChRsListRef;
// 	CExBaseList pVolChList = pParaSetSttTestResource->m_oVolChRsListRef;
	
	if (g_oSttTestResourceMngr.m_pTestResouce == NULL || g_pShortTimeOverTest->m_pSTOverPara == NULL)
	{
		return;
	}

	tmt_channel *pArrVOL = g_pShortTimeOverTest->m_pSTOverPara->m_uiVOL;
	tmt_channel *pArrCUR = g_pShortTimeOverTest->m_pSTOverPara->m_uiCUR;

	POS posVol = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetHeadPosition();
	long nVolIndex = 0;
	while(posVol)
	{
		CExBaseList* pChVol = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetNext(posVol);
		if (pChVol == NULL)
		{
			continue;
		}
		m_pHtmlBuffer->AppendString("<tr>");
		Gen_Table_td(nVolIndex+1);
		Gen_Table_td(pChVol->m_strName.GetString());
		Gen_Table_td(pArrVOL[nVolIndex].Harm[1].fAmp,3);
		Gen_Table_td(g_pShortTimeOverTest->m_nVolInflictCount);
		m_pHtmlBuffer->AppendString("</tr>");
		nVolIndex++;
	}


	long nCurIndex = nVolIndex;
	POS posCur = g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetHeadPosition();
	while(posCur)
	{	
		CExBaseList* pChCur = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetNext(posCur);
		if (pChCur == NULL)
		{
			continue;
		}
		m_pHtmlBuffer->AppendString("<tr>");
		Gen_Table_td(nCurIndex+1);
		Gen_Table_td(pChCur->m_strName.GetString());
		Gen_Table_td(pArrCUR[nCurIndex].Harm[1].fAmp,3);
		Gen_Table_td(g_pShortTimeOverTest->m_nCurInflictCount);
		m_pHtmlBuffer->AppendString("</tr>");
		nCurIndex++;
	}
}

