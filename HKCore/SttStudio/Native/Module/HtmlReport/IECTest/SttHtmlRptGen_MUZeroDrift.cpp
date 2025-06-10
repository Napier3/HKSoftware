#include "SttHtmlRptGen_MUZeroDrift.h"

CSttHtmlRptGen_MUZeroDrift::CSttHtmlRptGen_MUZeroDrift()
{

}

CSttHtmlRptGen_MUZeroDrift::~CSttHtmlRptGen_MUZeroDrift()
{
 
}


void CSttHtmlRptGen_MUZeroDrift::GenHtml()  //生成测试报告HTML文本
{
	m_pHtmlBuffer->ZeroBuffer();
	GenRootDiv();
	GenRootDiv_H1();
	GenTestMUZeroDrift();
	GenRootDiv_End();

}
void CSttHtmlRptGen_MUZeroDrift::GenRootDiv()
{

	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());

}

void CSttHtmlRptGen_MUZeroDrift::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}

//<h1零漂测试</h1>
void CSttHtmlRptGen_MUZeroDrift::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>零漂测试</h1>");
}


//序号	通道名称	额定值（V/A）	最大比差	最小比差	平均比差	准确级	        结论
//1	  保护电流A相1  	1	         0.1	      0.1	     0.1	 保护级(5P30)   	合格
void CSttHtmlRptGen_MUZeroDrift::GenTestMUZeroDrift()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	GenMUZeroDrift_Table_th();
	GenMUZeroDrift_Table_td("RatError");
	GenModule_Table_te();
}

void CSttHtmlRptGen_MUZeroDrift::GenMUZeroDrift_Table_th()
{
	GenModule_Table_th("MUZeroDriftTest");

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("序号");
	Gen_Table_th("通道名称");
	Gen_Table_th("额定值（V/A）");
	Gen_Table_th("最大零漂(dB)");
	Gen_Table_th("最小零漂(dB)");
	Gen_Table_th("平均零漂(dB)");
	Gen_Table_th("准确级");
//	Gen_Table_th("结论");

	m_pHtmlBuffer->AppendString("</tr>");

}

void CSttHtmlRptGen_MUZeroDrift::GenMUZeroDrift_Table_td(const CString &strTypeID)
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return;
	}
	if (g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTestCB == NULL)
	{
		return;
	}

	//遍历数据集的每个data
	CDvmDataset *m_pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTestCB;
	POS pos = m_pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	int nIndex = 0;
	while (pos != NULL)
	{
		m_pHtmlBuffer->AppendString("<tr>");
		pData = (CDvmData *)m_pDataset->GetNext(pos);

		if (pData->m_nChange == 0)
		{
			continue;
		}


		if ((pData->m_strDataType == "Curr")||(pData->m_strDataType == _T("电流")))
		{
			GenMUZeroDrift_Data_td_Curr(nIndex, pData,strTypeID);
		}
		else
		{
			GenMUZeroDrift_Data_td_Vol(nIndex, pData,strTypeID);
		}

		nIndex++;
		m_pHtmlBuffer->AppendString("</tr>");

	}

}

void CSttHtmlRptGen_MUZeroDrift::GenMUZeroDrift_Data_td_Vol(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "时间"))
	{
		return;
	}

	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(g_theXSmartCapMngr->m_pX61850Cap->m_dZeroDrift_Un,3);  //额定电压
	ShowData_td(pData, strTypeID, "$MaxValue");                       //最大值
	ShowData_td(pData, strTypeID, "$MinValue");                       //最小值
	ShowData_td(pData, strTypeID, "$AverageValue");                   //平均值
	ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_U"));    //准确级
//	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));        //测试结果
	/*ShowData_td_Results(pData,strTypeID,"$Result");*/

}

void CSttHtmlRptGen_MUZeroDrift::GenMUZeroDrift_Data_td_Curr(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "时间"))
	{
		return;
	}
	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(g_theXSmartCapMngr->m_pX61850Cap->m_dZeroDrift_In,3);//额定电流
	ShowData_td(pData, strTypeID, "$MaxValue");                     //最大值
	ShowData_td(pData, strTypeID, "$MinValue");                     //最小值
	ShowData_td(pData, strTypeID, "$AverageValue");                 //平均值
	ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_I"));         //准确级
//	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));       //测试结果
}

void CSttHtmlRptGen_MUZeroDrift::ShowData_td(CDvmData *pData,CString strTypeID,CString strAttrID)
{

	CString strID = pData->m_strID + "$" + strTypeID;
	CDvmValue *pValue = (CDvmValue *)pData->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}
	strID = strID + strAttrID;
	CDvmValue *pAttr = (CDvmValue *)pValue->FindByID(strID);

	Gen_Table_td(pAttr->m_strValue, 3); 

}

