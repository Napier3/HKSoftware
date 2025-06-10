#include "SttHtmlRptGen_MUZeroDrift.h"

CSttHtmlRptGen_MUZeroDrift::CSttHtmlRptGen_MUZeroDrift()
{

}

CSttHtmlRptGen_MUZeroDrift::~CSttHtmlRptGen_MUZeroDrift()
{
 
}


void CSttHtmlRptGen_MUZeroDrift::GenHtml()  //���ɲ��Ա���HTML�ı�
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

//<h1��Ư����</h1>
void CSttHtmlRptGen_MUZeroDrift::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>��Ư����</h1>");
}


//���	ͨ������	�ֵ��V/A��	���Ȳ�	��С�Ȳ�	ƽ���Ȳ�	׼ȷ��	        ����
//1	  ��������A��1  	1	         0.1	      0.1	     0.1	 ������(5P30)   	�ϸ�
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

	Gen_Table_th("���");
	Gen_Table_th("ͨ������");
	Gen_Table_th("�ֵ��V/A��");
	Gen_Table_th("�����Ư(dB)");
	Gen_Table_th("��С��Ư(dB)");
	Gen_Table_th("ƽ����Ư(dB)");
	Gen_Table_th("׼ȷ��");
//	Gen_Table_th("����");

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

	//�������ݼ���ÿ��data
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


		if ((pData->m_strDataType == "Curr")||(pData->m_strDataType == _T("����")))
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
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "ʱ��"))
	{
		return;
	}

	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(g_theXSmartCapMngr->m_pX61850Cap->m_dZeroDrift_Un,3);  //���ѹ
	ShowData_td(pData, strTypeID, "$MaxValue");                       //���ֵ
	ShowData_td(pData, strTypeID, "$MinValue");                       //��Сֵ
	ShowData_td(pData, strTypeID, "$AverageValue");                   //ƽ��ֵ
	ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_U"));    //׼ȷ��
//	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));        //���Խ��
	/*ShowData_td_Results(pData,strTypeID,"$Result");*/

}

void CSttHtmlRptGen_MUZeroDrift::GenMUZeroDrift_Data_td_Curr(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "ʱ��"))
	{
		return;
	}
	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(g_theXSmartCapMngr->m_pX61850Cap->m_dZeroDrift_In,3);//�����
	ShowData_td(pData, strTypeID, "$MaxValue");                     //���ֵ
	ShowData_td(pData, strTypeID, "$MinValue");                     //��Сֵ
	ShowData_td(pData, strTypeID, "$AverageValue");                 //ƽ��ֵ
	ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_I"));         //׼ȷ��
//	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));       //���Խ��
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

