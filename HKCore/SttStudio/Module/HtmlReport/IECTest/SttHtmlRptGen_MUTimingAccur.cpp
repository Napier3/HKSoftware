#include "SttHtmlRptGen_MUTimingAccur.h"
#include "../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../XLangResource_Native.h"
#endif


CSttHtmlRptGen_MUTimingAccur::CSttHtmlRptGen_MUTimingAccur()
{
	m_bIsHasUsingTime = false;
}

CSttHtmlRptGen_MUTimingAccur::~CSttHtmlRptGen_MUTimingAccur()
{
 
}

void CSttHtmlRptGen_MUTimingAccur::GenHtml()  //生成测试报告HTML文本
{

	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenTestMUTimingAccur();
	GenRootDiv_End();

}
void CSttHtmlRptGen_MUTimingAccur::GenRootDiv()
{

	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());

}

void CSttHtmlRptGen_MUTimingAccur::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}


//<h1>对时误差测试</h1>
void CSttHtmlRptGen_MUTimingAccur::GenRootDiv_H1()
{
#ifdef NOT_USE_XLANGUAGE
	m_pHtmlBuffer->AppendString("<h1>对时误差测试</h1>");
#else
// 	m_pHtmlBuffer->AppendString((/*"<h1>对时误差测试</h1>"*/"<h1>"+g_sLangTxt_Native_MUTimingAccurTest+"</h1>").toStdString().c_str());
	m_pHtmlBuffer->AppendString((/*"<h1>对时误差测试</h1>"*/"<h1>"+g_sLangTxt_Native_MUTimingAccurTest+"</h1>").toLocal8Bit());
#endif
}


//序号	对时时长(s)	最大误差(μs)	最小误差(μs)	平均误差(μs)	结论
//1	    100	        1.0	             1.0	         1.0	        合格
void CSttHtmlRptGen_MUTimingAccur::GenTestMUTimingAccur()
{
	
	GenMUTimingAccur_Table_th();
	GenMUTimingAccur_Table_Point();
	GenModule_Table_te();
}

void CSttHtmlRptGen_MUTimingAccur::GenMUTimingAccur_Table_th()
{
	GenModule_Table_th("MUTimingAccur");

	m_pHtmlBuffer->AppendString("<tr>");

#ifdef NOT_USE_XLANGUAGE
	Gen_Table_th("序号");
	Gen_Table_th("对时时长(s)");
	Gen_Table_th("最大误差(μs)");
	Gen_Table_th("最小误差(μs)");
	Gen_Table_th("平均误差(μs)");
	Gen_Table_th("结论");
#else
	Gen_Table_th(/*"序号"*/g_sLangTxt_SerNumber.toStdString().c_str());
	Gen_Table_th(/*"对时时长(s)" */ (g_sLangTxt_Native_MUSTiming+"(s)" ).toStdString().c_str());
	Gen_Table_th(/*"最大误差(μs)"*/  (g_sLangTxt_Native_MaximumError +"(μs)").toStdString().c_str());
	Gen_Table_th(/*"最小误差(μs)"*/ (g_sLangTxt_Native_MinimumError+"(μs)").toStdString().c_str());
	Gen_Table_th(/*"平均误差(μs)"*/(g_sLangTxt_Native_AverageError+"(μs)").toStdString().c_str());
	Gen_Table_th(/*"结论"*/g_sLangTxt_Conclusion.toStdString().c_str());
#endif
	m_pHtmlBuffer->AppendString("</tr>");

}

void CSttHtmlRptGen_MUTimingAccur::GenMUTimingAccur_Table_Point()
{
	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return;
	}
	if (g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTimeRlt == NULL)
	{
		return;
	}

	m_pHtmlBuffer->AppendString("<tr>");
	Gen_Table_td(1);
	ShowData_td_MUTimingAccur(STT_MUTEST_HasUsingTime);  //对时时长(s)
	ShowData_td_MUTimingAccur(STT_MUTEST_MaxErrTime);    //最大误差
	ShowData_td_MUTimingAccur(STT_MUTEST_MinErrTime);    //最小误差(μs)
	ShowData_td_MUTimingAccur(STT_MUTEST_AverageErrTime);//平均误差(μs)
	ShowData_td_MUTimeResult(STT_MUTEST_MUTimeResult);  //结论

	m_pHtmlBuffer->AppendString("</tr>");
		
	m_bIsHasUsingTime = false;
}

void CSttHtmlRptGen_MUTimingAccur::ShowData_td_MUTimingAccur( CString strAttrID)
{

	CDvmDataset *m_pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTimeRlt;
	CDvmValue *pAttr = (CDvmValue *)m_pDataset->FindChildByID(strAttrID);
	
	if ((pAttr)&&(strAttrID == STT_MUTEST_HasUsingTime) )
	{
		double dValue = CString_To_double(pAttr->m_strValue);
		if (dValue < 60)
		{
			pAttr->m_strValue = _T("0.000");
			m_bIsHasUsingTime = TRUE;
		}
	}
	else 
	{
		if (m_bIsHasUsingTime)
		{
			pAttr->m_strValue = _T("0.000");;
		}
	}


	Gen_Table_td(pAttr->m_strValue, 3); 
}


void CSttHtmlRptGen_MUTimingAccur::ShowData_td_MUTimeResult( CString strAttrID)
{

	CDvmDataset *m_pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTimeRlt;
	CDvmValue *pAttr = (CDvmValue *)m_pDataset->FindChildByID(strAttrID);


	CString strTemp;
#ifdef NOT_USE_XLANGUAGE
	strTemp = _T("合格");
#else
	strTemp = /*_T("合格")*/g_sLangTxt_Qualified;

#endif

	if(CString_To_long(pAttr->m_strValue) == 0)
	{
#ifdef NOT_USE_XLANGUAGE
		strTemp = "不合格";
#else
		strTemp = g_sLangTxt_Unqualified;

#endif
	}
	if(CString_To_long(pAttr->m_strValue) ==2)
	{
		strTemp = "  ";
	}

	Gen_Table_td(strTemp.GetString());
}
