#include "SttHtmlRptGen_MUPunctAccur.h"

CSttHtmlRptGen_MUPunctAccur::CSttHtmlRptGen_MUPunctAccur()
{

}

CSttHtmlRptGen_MUPunctAccur::~CSttHtmlRptGen_MUPunctAccur()
{
 
}
void CSttHtmlRptGen_MUPunctAccur::GenHtml()  //���ɲ��Ա���HTML�ı�
{

	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenTestMUPunctAccur();
	GenRootDiv_End();

}
void CSttHtmlRptGen_MUPunctAccur::GenRootDiv()
{

	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());

}

void CSttHtmlRptGen_MUPunctAccur::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}

//<h1>��ʱ������</h1>
void CSttHtmlRptGen_MUPunctAccur::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>��ʱ������</h1>");
}


//���	��ʱʱ��(s)	������(��s)	��С���(��s)	ƽ�����(��s)	����
//1	    100	        1.0	             1.0	         1.0	        �ϸ�
void CSttHtmlRptGen_MUPunctAccur::GenTestMUPunctAccur()
{
	GenMUPunctAccur_Table_th();
	GenMUPunctAccur_Table_Point();
	GenModule_Table_te();
}

void CSttHtmlRptGen_MUPunctAccur::GenMUPunctAccur_Table_th()
{
	GenModule_Table_th("MUPunctAccur");

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("��ʱʱ��(s)");
	Gen_Table_th("������(��s)");
	Gen_Table_th("��С���(��s)");
	Gen_Table_th("ƽ�����(��s)");
	Gen_Table_th("����");

	m_pHtmlBuffer->AppendString("</tr>");

}

void CSttHtmlRptGen_MUPunctAccur::GenMUPunctAccur_Table_Point()
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
	ShowData_td_MUPunctAccur(STT_MUTEST_HasUsingTime);  //��ʱʱ��(s)
	ShowData_td_MUPunctAccur(STT_MUTEST_MaxErrTime);//������
	ShowData_td_MUPunctAccur( STT_MUTEST_MinErrTime);//��С���(��s)
	ShowData_td_MUPunctAccur(STT_MUTEST_AverageErrTime);//ƽ�����(��s)
	ShowData_td_MUTimeResult(STT_MUTEST_MUTimeResult);//����
	
	m_pHtmlBuffer->AppendString("</tr>");
	
}
void CSttHtmlRptGen_MUPunctAccur::ShowData_td_MUPunctAccur( CString strAttrID)
{

	CDvmDataset *pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTimeRlt;
	CDvmValue *pAttr = (CDvmValue *)pDataset->FindChildByID(strAttrID);

	Gen_Table_td(pAttr->m_strValue, 3); 
}


void CSttHtmlRptGen_MUPunctAccur::ShowData_td_MUTimeResult( CString strAttrID)
{

	CDvmDataset *m_pDataset = g_theXSmartCapMngr->m_pX61850Cap->m_pDataset_MUTimeRlt;
	CDvmValue *pAttr = (CDvmValue *)m_pDataset->FindChildByID(strAttrID);


	CString strTemp;
	strTemp = _T("�ϸ�");

	if(CString_To_long(pAttr->m_strValue) == 0)
	{
		strTemp = "���ϸ�";
	}
	if(CString_To_long(pAttr->m_strValue) ==2)
	{
		strTemp = "  ";
	}

	Gen_Table_td(strTemp.GetString());
}
