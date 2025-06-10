#include "SttHtmlRptGen_MUAccuracy.h"
#include "../../UI/SttTestCntrCmdDefine.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"
#include "../SttXHtmlRptGenFactoryBase.h"

CSttHtmlRptGen_MUAccuracy::CSttHtmlRptGen_MUAccuracy()
{

}

CSttHtmlRptGen_MUAccuracy::~CSttHtmlRptGen_MUAccuracy()
{
 
}

//void CSttHtmlRptGen_MUAccuracy::InitDataset()
//{
//	//m_pDvmDevice
//
//}

void CSttHtmlRptGen_MUAccuracy::GenHtml()  //���ɲ��Ա���HTML�ı�
{
	m_pHtmlBuffer->ZeroBuffer();
	GenRootDiv();
	GenRootDiv_H1();
	GenMUAccuracy();
	GenRootDiv_End();

}

void CSttHtmlRptGen_MUAccuracy::GenRootDiv()
{
	m_pHtmlBuffer->AppendString("<div id=\"");
	m_pHtmlBuffer->AppendString(g_theHtmlRptGenFactory->m_strMacroID.GetString());
	m_pHtmlBuffer->AppendString("\">");
}

void CSttHtmlRptGen_MUAccuracy::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}

void CSttHtmlRptGen_MUAccuracy::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>׼ȷ�Ȳ���</h1>");
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy()  //���������ӱ�ڵ�
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	GenMUAccuracy_RootDiv("RatError");
	GenMUAccuracy_h2("�Ȳ����");
	GenMUAccuracy_Table_th_RatError("RatError");
	GenMUAccuracy_Point_RatError("RatError");
	GenModule_Table_te();
	GenRootDiv_End();

	GenMUAccuracy_RootDiv("AngError");
	GenMUAccuracy_h2("�ǲ����");
	GenMUAccuracy_Table_th_AngError("AngError");
	GenMUAccuracy_Point_AngError("AngError");
	GenModule_Table_te();
	GenRootDiv_End();

	GenMUAccuracy_RootDiv("CompError");
	GenMUAccuracy_h2("����������");
	GenMUAccuracy_Table_th_CompError("CompError");
	GenMUAccuracy_Point_CompError("CompError");
	GenModule_Table_te();
	GenRootDiv_End();

	GenMUAccuracy_RootDiv("ChDelay");
	GenMUAccuracy_h2("ͨ����ʱ����");
	GenMUAccuracy_Table_th_ChDelay("ChDelay");
	GenMUAccuracy_Point_ChDelay();
	GenModule_Table_te();
	GenRootDiv_End();
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_RootDiv(const CString &strTypeID)  //�����ӱ���ڵ�
{
	CString strModuleID;
	strModuleID = g_theHtmlRptGenFactory->m_strMacroID;
	strModuleID += _T("$");
	strModuleID += strTypeID;

	GenModule_RootDiv(strModuleID);

}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_h2(const CString &strName)		//�����ӱ����
{

	m_pHtmlBuffer->AppendString("<h2>");
	m_pHtmlBuffer->AppendString(strName.GetString());
	m_pHtmlBuffer->AppendString("</h2>");	
}

//void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Table(const CString &strTypeID)  //�����ӱ��<table>����
//{
//	GenMUAccuracy_Table_th(strTypeID);
//	GenMUAccuracy_Point(strTypeID);
//	GenMUAccuracy_Table_te();
//}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Table_th_RatError(const CString &strTypeID)  //�����ӱ�ͷ
{
		GenModule_Table_th(strTypeID);

		m_pHtmlBuffer->AppendString("<tr>");

		Gen_Table_th("���");
		Gen_Table_th("ͨ������");
		Gen_Table_th("�����ֵ(V/A)");
		Gen_Table_th("���Ȳ�(%)");
		Gen_Table_th("��С�Ȳ�(%)");
		Gen_Table_th("ƽ���Ȳ�(%)");
		Gen_Table_th("׼ȷ��");
		Gen_Table_th("����");

		m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Table_th_AngError(const CString &strTypeID)  //�����ӱ�ͷ
{
	GenModule_Table_th(strTypeID);

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("ͨ������");
	Gen_Table_th("����Ƕ�(��)");
	Gen_Table_th("���ǲ�(��)");
	Gen_Table_th("��С�ǲ�(��)");
	Gen_Table_th("ƽ���ǲ�(��)");
	Gen_Table_th("׼ȷ��");
	Gen_Table_th("����");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Table_th_CompError(const CString &strTypeID)  //�����ӱ�ͷ
{
	GenModule_Table_th(strTypeID);

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("ͨ������");
	Gen_Table_th("�����ֵ(A/V)");
	Gen_Table_th("����Ƕ�(��)");
	Gen_Table_th("������(%)");
	Gen_Table_th("��С���(%)");
	Gen_Table_th("ƽ�����(%)");
	Gen_Table_th("����");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Table_th_ChDelay(const CString &strTypeID)  //�����ӱ�ͷ
{
	GenModule_Table_th(strTypeID);

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("���ƿ�����");
	Gen_Table_th("ͨ����ʱ(��s)");
	Gen_Table_th("�����ʱ(��s)");
	Gen_Table_th("��С��ʱ(��s)");
	Gen_Table_th("ƽ����ʱ(��s)");
	Gen_Table_th("����");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Point_RatError(const CString &strTypeID)
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

		Gen_Data_td_RatError(nIndex, pData, strTypeID);
		m_pHtmlBuffer->AppendString("</tr>");
		nIndex++;
	}

}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Point_AngError(const CString &strTypeID)
{
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

		Gen_Data_td_AngError(nIndex,pData,strTypeID);
		m_pHtmlBuffer->AppendString("</tr>");
		nIndex++;
	}

}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Point_CompError(const CString &strTypeID)
{
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

		Gen_Data_td_CompError(nIndex, pData, strTypeID);
		m_pHtmlBuffer->AppendString("</tr>");
		nIndex++;
	}

}

void CSttHtmlRptGen_MUAccuracy::GenMUAccuracy_Point_ChDelay()
{
	CX61850CapBase *pX61850Cap = g_theXSmartCapMngr->m_pX61850Cap;

	if (pX61850Cap == NULL)
	{
		return;
	}

	if (pX61850Cap->m_pDataset_MUTestCB == NULL)
	{
		return;
	}

	if (pX61850Cap->m_pDataset_SVDelay == NULL)
	{
		return;
	}

	//�������ݼ���ÿ��data
	CDvmDataset *m_pDataset = pX61850Cap->m_pDataset_SVDelay;

	CString strSVX_Data;

	if (pX61850Cap->m_strDatasetMapID_MUTestCB.GetLength()>2)
	{
		strSVX_Data = pX61850Cap->m_strDatasetMapID_MUTestCB.Mid(2);
	} 
	else
	{
		strSVX_Data = _T("SV1");
	}

	CDvmData *pDelayData = (CDvmData*)m_pDataset->FindByID(strSVX_Data/*_T("SV1")*/);

	if (pDelayData == NULL)
	{
		return;
	}

	//POS pos = m_pDataset->GetHeadPosition();
	//CDvmData *pData = NULL;
	m_pHtmlBuffer->AppendString("<tr>");
	//pData = (CDvmData *)m_pDataset->GetNext(pos);
	Gen_Data_td_ChDelay(pX61850Cap->m_pDataset_MUTestCB->m_strName,pDelayData);
	m_pHtmlBuffer->AppendString("</tr>");

}
//SV1$ChDelay
//SV1_I1_Ia1$CompError$MaxValue

/*
<value name="���ֵ" id="SV1_I1_Ia1$CompError$MaxValue" data-type="FLOAT" value=""/>
*/
void CSttHtmlRptGen_MUAccuracy::ShowData_td(CDvmData *pData, CString strTypeID, CString strAttrID)
{
	/*if (pData->m_strDataType == "UTCTime")
	{
		return;
	}*/

	CString strID = pData->m_strID + "$" + strTypeID;
	CDvmValue *pValue = (CDvmValue *)pData->FindByID(strID);
	if (pValue == NULL)
	{
		return;
	}
	strID = strID + strAttrID;
	CDvmValue *pAttr = (CDvmValue *)pValue->FindByID(strID);

	Gen_Table_td(pAttr->m_strValue, 3); 
	/*if(strAttrID == "$Result")
	{
		int nResult = atoi(pAttr->m_strValue.GetString());
		if (nResult == 0)
		{
			pAttr->m_strValue = "���ϸ�";
		}
		else if (nResult == 1)
		{
			pAttr->m_strValue = "�ϸ�";
		}
	}*/
}


void CSttHtmlRptGen_MUAccuracy::Gen_Data_td_RatError(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "ʱ��"))
	{
		return;
	}
	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(pData->m_strValue,3);
	ShowData_td(pData, strTypeID, "$MaxValue");
	ShowData_td(pData, strTypeID, "$MinValue");
	ShowData_td(pData, strTypeID, "$AverageValue");

	if ((pData->m_strDataType == "Curr")||(pData->m_strDataType == _T("����")))
	{
		ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_I"));
	} 
	else if ((pData->m_strDataType == "Vol")||(pData->m_strDataType == _T("��ѹ")))
	{
		ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_U"));
	}

	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));
}

void CSttHtmlRptGen_MUAccuracy::Gen_Data_td_AngError(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "ʱ��"))
	{
		return;
	}

	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(pData->m_strFormat,3);
	ShowData_td(pData, strTypeID, "$MaxValue");
	ShowData_td(pData, strTypeID, "$MinValue");
	ShowData_td(pData, strTypeID, "$AverageValue");

	if ((pData->m_strDataType == "Curr")||(pData->m_strDataType == _T("����")))
	{
		ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_I"));
	} 
	else if ((pData->m_strDataType == "Vol")||(pData->m_strDataType == _T("��ѹ")))
	{
		ShowData_td_ByDataType(pData->m_nIndex,_T("SmvInAppChAccLevelDataType_U"));
	}

	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));
}

void CSttHtmlRptGen_MUAccuracy::Gen_Data_td_CompError(int nIndex, CDvmData *pData,  CString strTypeID)
{
	if ((pData->m_strDataType == "UTCTime")||(pData->m_strDataType == "ʱ��"))
	{
		return;
	}
	Gen_Table_td(nIndex);
	Gen_Table_td(pData->m_strName.GetString());
	Gen_Table_td(pData->m_strValue,3);
	Gen_Table_td(pData->m_strFormat,3);
	ShowData_td(pData, strTypeID, "$MaxValue");
	ShowData_td(pData, strTypeID, "$MinValue");
	ShowData_td(pData, strTypeID, "$AverageValue");
	ShowData_td_ByDataType(pData, strTypeID, _T("Result"),_T("TestResult"));
}

//SV1$ChDelay
void CSttHtmlRptGen_MUAccuracy::ShowData_td_ChDelay(CDvmData *pData, CString strAttrID)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pAttr = (CDvmValue *)pData->FindByID(strID);

	if (pAttr != NULL)
	{
		if (strAttrID == "$ChDelay")
		{
			Gen_Table_td(pAttr->m_strValue, 3); 
		}
		else
		{
			CString strChDelayID;
			strChDelayID = pData->m_strID + "$ChDelay";
			CDvmValue *pChDelayValue = (CDvmValue *)pData->FindByID(strChDelayID);

			if (pAttr != NULL)
			{
				double dValue = CString_To_double(pAttr->m_strValue) + CString_To_double(pChDelayValue->m_strValue);
				Gen_Table_td(dValue, 3); 
			}
		}
	}
}

void CSttHtmlRptGen_MUAccuracy::Gen_Data_td_ChDelay(const CString &strCBName,CDvmData *pData)
{
	Gen_Table_td(1);
	Gen_Table_td(strCBName.GetString());
	ShowData_td_ChDelay(pData, "$ChDelay");
	ShowData_td_ChDelay(pData, STT_MUTEST_DL_MaxDelayError/*"$MaxDelay"*/);
	ShowData_td_ChDelay(pData, STT_MUTEST_DL_MinDelayError/*"$MinDelay"*/);
	ShowData_td_ChDelay(pData, STT_MUTEST_DL_AverageDelayError/*"$AverageDelay"*/);

	CString strID = pData->m_strID + STT_MUTEST_DL_TimeLong;
	CDvmValue *pAttr = (CDvmValue *)pData->FindByID(strID);

	if (pAttr != NULL)
	{
		long nTestLong = CString_To_long(pAttr->m_strValue);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰʵ�ʲ���ʱ��(%ld)."),nTestLong);

		//����ʱ��϶�ʱ,�����ɲ��Խ���
		if (nTestLong <=6)
		{
			Gen_Table_td(_T("---"));
			return;
		}
	}

	ShowData_td_ByDataType(pData,  _T("Result"),_T("TestResult"));
}