#include "SttHtmlRptGen_TerminalAuto.h"
#include "../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../Module/UI/TerminalAutoTest/SttMacroParaEditViewTerminalAutoTest.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../SttCmd/GuideBook/SttItemStateObject.h"

CSttHtmlRptGen_TerminalAuto::CSttHtmlRptGen_TerminalAuto()
{

}

CSttHtmlRptGen_TerminalAuto::~CSttHtmlRptGen_TerminalAuto()
{
 
}

void CSttHtmlRptGen_TerminalAuto::GenHtml()  //生成测试报告HTML文本
{
	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenTestIntelTerminal();
	GenRootDiv_End();
}

void CSttHtmlRptGen_TerminalAuto::GenRootDiv()
{
	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());
}

void CSttHtmlRptGen_TerminalAuto::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}


//<h1>智能终端测试</h1>
void CSttHtmlRptGen_TerminalAuto::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>智能终端自动测试</h1>");
}

void CSttHtmlRptGen_TerminalAuto::GenTestIntelTerminal()
{
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuGooseBinGrid == NULL || g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuBoutGooseGrid == NULL)
	{
		return;
	}

	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex > 0)
	{
	GenIntelTerminal_h2("GOOSE转开入");
	GenIntelTerminal_h3("测试项：智能终端测试(GOOSE转开入)");
	GenIntelTerminal_Table_th_Gout("GOOSEOUT");
	GenIntelTerminal_Table_Point_GoutPubs();
	GenModule_Table_te();
	}

	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex > 0)
	{
	GenIntelTerminal_h2("开出转GOOSE");
	GenIntelTerminal_h3("测试项：智能终端测试(开出转GOOSE)");
	GenIntelTerminal_Table_th_Gin("GOOSEIN");
	GenIntelTerminal_Table_Point_GinPubs();
	GenModule_Table_te();
	}
	
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEGooseBinGrid == NULL || g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEBoutGooseGrid == NULL)
	{
		return;
	}

	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex >= 3 || g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex >= 3)
	{
	GenIntelTerminal_h2("SOE测试");
	}

	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex >= 3)
	{
	GenIntelTerminal_h3("测试项：智能终端测试(SOE-GOOSE转开入)");
	GenIntelTerminal_Table_th_SoeGout("SOEGOOSEOUT");
	GenIntelTerminal_Table_Point_SoeGoutPubs();
	GenModule_Table_te();
	}
	
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex >= 3)
	{
	GenIntelTerminal_h3("测试项：智能终端测试(SOE-开出转GOOSE)");
	GenIntelTerminal_Table_th_SoeGin("SOEGOOSEIN");
	GenIntelTerminal_Table_Point_SoeGinPubs();
	GenModule_Table_te();
	}
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_h2(const CString &strName)		//生成子表标题
{
	m_pHtmlBuffer->AppendString("<h2>");
	m_pHtmlBuffer->AppendString(strName.GetString());
	m_pHtmlBuffer->AppendString("</h2>");	
}
void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_h3(const CString &strName)		//生成子表标题
{
	m_pHtmlBuffer->AppendString("<h3>");
	m_pHtmlBuffer->AppendString(strName.GetString());
	m_pHtmlBuffer->AppendString("</h3>");	
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_th_Gout(const CString &strTypeID)  //生成子表头
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("序号");
	Gen_Table_th("描述");
	Gen_Table_th("实测值");
	Gen_Table_th("测试结果(s)");
	Gen_Table_th("结论");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_th_Gin(const CString &strTypeID)  //生成子表头
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("序号");
	Gen_Table_th("描述");
	Gen_Table_th("实测值");
	Gen_Table_th("测试结果(s)");
	Gen_Table_th("结论");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_th_SoeGout( const CString &strTypeID )
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("序号");
	Gen_Table_th("描述");
	Gen_Table_th("实测值");
	Gen_Table_th("测试结果(s)");
	Gen_Table_th("最大分辨时间");
	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_th_SoeGin( const CString &strTypeID )
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("序号");
	Gen_Table_th("描述");
	Gen_Table_th("实测值");
	Gen_Table_th("测试结果(s)");
	Gen_Table_th("最大分辨时间");
	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_Point_GoutPubs() // GOOSE转开入
{
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget == NULL )
	{
		return;
	}
	m_pHtmlBuffer->AppendString("<tr>");
	float fValue;
	
	for(int i = 0; i < g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oBoutGooseList.GetCount(); i++)
	{
		bool bDataFound = false; 
		CExBaseObject *pData = (CExBaseObject*)g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oBoutGooseList.GetAt(i);
		Gen_Table_td(i+1);
		Gen_Table_td(pData->m_strName.GetString());

		if (!g_theTestCntrFrame->IsTestStarted())
		{
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("未测试"));
			m_pHtmlBuffer->AppendString("</tr>");
			continue;
		}

		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuBoutGooseGrid == NULL)
		{
			return;
		}
		QList <QPair<CString, float> >pGooseOutData = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuBoutGooseGrid->m_pGooseOutData;

		for(int i = 0; i < pGooseOutData.size(); i++)
		{
			QPair<CString, float> pair = pGooseOutData.at(i);
			if (pair.first == pData->m_strID)
			{
				fValue = pair.second ;
				Gen_Table_td(_T("动作"));
				Gen_Table_td(fValue, 3);
				if (fValue <= 0.007 && fValue > 0)
				{
					Gen_Table_td(_T("合格"));
				}
				else
				{
					Gen_Table_td(_T("不合格"));
				}
				bDataFound = true;
				break;
			}
		}

		if (!bDataFound)
		{
			Gen_Table_td(_T("未动作"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("不合格"));
		}

		m_pHtmlBuffer->AppendString("</tr>");
	}
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_Point_GinPubs()
{
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget == NULL)
	{
		return;
	}
	m_pHtmlBuffer->AppendString("<tr>");
	float fValue;

	for(int i = 0; i < g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oGooseBinList.GetCount(); i++)
	{
		bool bDataFound = false; 
		CExBaseObject *pData = (CExBaseObject*)g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oGooseBinList.GetAt(i);
		Gen_Table_td(i+1);
		Gen_Table_td(pData->m_strName.GetString());

		if (!g_theTestCntrFrame->IsTestStarted())
		{
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("未测试"));
			m_pHtmlBuffer->AppendString("</tr>");
			continue;
		}

		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuGooseBinGrid == NULL)
		{
			return;
		}
  		QList <QPair<CString, float> >pGooseInData = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_MuGooseBinGrid->m_pGooseInData;
 		
		for(int i = 0; i < pGooseInData.size(); i++)
		{
			QPair<CString, float> pair = pGooseInData.at(i);
			if (pair.first == pData->m_strID)
			{
				fValue = pair.second ;
				Gen_Table_td(_T("动作"));
				Gen_Table_td(fValue, 3);
				if (fValue <= 0.01 && fValue > 0)
				{
					Gen_Table_td(_T("合格"));
				}
				else
				{
					Gen_Table_td(_T("不合格"));
				}
				bDataFound = true;
				break;
			}
		}

		if (!bDataFound)
		{
			Gen_Table_td(_T("未动作"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("不合格"));
		}
		m_pHtmlBuffer->AppendString("</tr>");
	}
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_Point_SoeGoutPubs()
{
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget == NULL)
	{
		return;
	}

	CExBaseObject *pCurrTestItem = g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
	CSttItemStateObject* pObj  = (CSttItemStateObject*)pCurrTestItem;
	CString strItemID;
	if (pObj)
	{
		strItemID =  pObj->m_strItemID;
	}

	m_pHtmlBuffer->AppendString("<tr>");
	float fValue;

	int nRowCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oSOEBoutGooseList.GetCount();
	if (nRowCount < 3)
	{
		return;
	}
	for(int i = 0; i < nRowCount; i++)
	{
		bool bDataFound = false; 
		CExBaseObject *pData = (CExBaseObject*)g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oSOEBoutGooseList.GetAt(i);
		Gen_Table_td(i+1);
		Gen_Table_td(pData->m_strName.GetString());
		
		if (!g_theTestCntrFrame->IsTestStarted())
		{
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(0,3);
			m_GooseOutMaxTimeList.clear();
			m_pHtmlBuffer->AppendString("</tr>");
			continue;
		}
		
		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEBoutGooseGrid == NULL)
		{
			return;
		}
 		QList <QPair<CString, float> >pGooseOutData = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEBoutGooseGrid->m_pGooseOutData;
		for(int j = 0; j < pGooseOutData.size(); j++)
		{
			QPair<CString, float> pair = pGooseOutData.at(j);
			if (pair.first == pData->m_strID)
			{
				fValue = pair.second ;
				Gen_Table_td(_T("动作"));
				Gen_Table_td(fValue, 3);

				if (strItemID.Find(_T("SOEGout")) >= 0)
				{	
				m_GooseOutMaxTimeList.push_back(fValue);
				}
				bDataFound = true;
				break;
			}
		}

		if (!bDataFound)
		{
			Gen_Table_td(_T("未动作"));
			Gen_Table_td(_T("---"));
			fValue = 0.00f;
			m_GooseOutMaxTimeList.push_back(fValue);
		}


		Gen_Table_td(CalculateMaxDifference(m_GooseOutMaxTimeList),3);

		m_pHtmlBuffer->AppendString("</tr>");
	}
}

void CSttHtmlRptGen_TerminalAuto::GenIntelTerminal_Table_Point_SoeGinPubs()
{
	if (g_TerminalAutoTest->m_pMuTerminalTabWidget == NULL)
	{
		return;
	}
	float fValue;
	CExBaseObject *pCurrTestItem = g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
	CSttItemStateObject* pObj  = (CSttItemStateObject*)pCurrTestItem;
	CString strItemID;
	if (pObj)
	{
		strItemID =  pObj->m_strItemID;
	}
	m_pHtmlBuffer->AppendString("<tr>");

	int nRowCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oSOEGooseBinList.GetCount();
	if (nRowCount < 3)
	{
		return;
	}
	for(int i = 0; i < nRowCount; i++)
	{
		bool bDataFound = false; 
		CExBaseObject *pData = (CExBaseObject*)g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oSOEGooseBinList.GetAt(i);
		Gen_Table_td(i+1);
		Gen_Table_td(pData->m_strName.GetString());

		if (!g_theTestCntrFrame->IsTestStarted())
		{
			Gen_Table_td(_T("---"));
			Gen_Table_td(_T("---"));
			Gen_Table_td(0,3);
			m_pHtmlBuffer->AppendString("</tr>");
			m_GooseInMaxTimeList.clear();
			continue;
		}

		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEGooseBinGrid == NULL)
		{
			return;
		}
		QList <QPair<CString, float> > pGooseInData = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_SOEGooseBinGrid->m_pGooseInData;

		for(int i = 0; i < pGooseInData.size(); i++)
		{
			QPair<CString, float> pair = pGooseInData.at(i);
			if (pair.first == pData->m_strID)
			{
				fValue = pair.second ;
				Gen_Table_td(_T("动作"));
				Gen_Table_td(fValue, 3);
				if (strItemID.Find(_T("SOEGin")) >= 0)
				{
				m_GooseInMaxTimeList.push_back(fValue);
				}
				bDataFound = true;
				break;
			}
		}

		if (!bDataFound)
		{
			Gen_Table_td(_T("未动作"));
			Gen_Table_td(_T("---"));
			fValue = 0.00f;
			m_GooseInMaxTimeList.push_back(fValue);
		}
		
		Gen_Table_td(CalculateMaxDifference(m_GooseInMaxTimeList),3);
		m_pHtmlBuffer->AppendString("</tr>");
	}
}


float CSttHtmlRptGen_TerminalAuto::CalculateMaxDifference(const QList<float>& list) 
{
	if (list.size() < 2) 
	{
		return 0; 
	}

	float maxDiff = list.at(1) - list.at(0);

	for (int i = 1; i < list.size() - 1; ++i) 
	{
		float currentDiff = list.at(i + 1) - list.at(i);
		maxDiff = (std::max)(maxDiff, currentDiff);
	}

	return maxDiff;
}