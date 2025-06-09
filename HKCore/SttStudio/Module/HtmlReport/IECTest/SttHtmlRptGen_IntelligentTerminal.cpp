#include "SttHtmlRptGen_IntelligentTerminal.h"
#include "../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../Module/UI/IntelligentTerminal/SttMacroParaEditViewIntelligentTerminal.h"

CSttHtmlRptGen_IntelligentTerminal::CSttHtmlRptGen_IntelligentTerminal()
{

}

CSttHtmlRptGen_IntelligentTerminal::~CSttHtmlRptGen_IntelligentTerminal()
{
 
}

void CSttHtmlRptGen_IntelligentTerminal::GenHtml()  //���ɲ��Ա���HTML�ı�
{

	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenTestIntelTerminal();
	GenRootDiv_End();

}
void CSttHtmlRptGen_IntelligentTerminal::GenRootDiv()
{
	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());
}

void CSttHtmlRptGen_IntelligentTerminal::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}


//<h1>�����ն˲���</h1>
void CSttHtmlRptGen_IntelligentTerminal::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>�����ն˲���</h1>");
}

void CSttHtmlRptGen_IntelligentTerminal::GenTestIntelTerminal()
{
	//GOOSE����
	//������1��
	//���	����	��������	����GOOSE�ź�	���Խ��(s)	
	GenIntelTerminal_h2("GOOSE����");
	if (g_pIntelligentTest->m_pSttIntelGoutToBinParaWidget==NULL||g_pIntelligentTest->m_pSttIntelBoutToGinParaWidget==NULL)
	{
		return;
	}

	int nGoutCount=g_pIntelligentTest->m_pSttIntelGoutToBinParaWidget->getGoosePubList().size();
	CString strGout = _T("");
	for(int i=0;i<nGoutCount;i++)
	{
		strGout.Format(_T("������G%d"),i+1);
		CString m_TestID=strGout;
		GenIntelTerminal_h3(m_TestID.GetString());
		GenIntelTerminal_Table_th_Gout("GOOSEPubs");
		GenIntelTerminal_Table_Point_GoutPubs(i);
		GenModule_Table_te();

	}

	//GOOSE����
	//������1��
	//���	����	��������	����GOOSE�ź�	���Խ��(s)	
	GenIntelTerminal_h2("GOOSE����");
	int nGinCount=g_pIntelligentTest->m_pSttIntelBoutToGinParaWidget->getGoosePubList().size();
	CString strGin = _T("");
	for(int i=0;i<nGinCount;i++)
	{
		strGin.Format(_T("������G%d"),i+1);
		CString m_TestID=strGin;

		GenIntelTerminal_h3(m_TestID.GetString());
		GenIntelTerminal_Table_th_Gin("GOOSEGinPubs");
		GenIntelTerminal_Table_Point_GinPubs(i);
		GenModule_Table_te();
	}
}

void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_h2(const CString &strName)		//�����ӱ����
{

	m_pHtmlBuffer->AppendString("<h2>");
	m_pHtmlBuffer->AppendString(strName.GetString());
	m_pHtmlBuffer->AppendString("</h2>");	
}
void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_h3(const CString &strName)		//�����ӱ����
{

	m_pHtmlBuffer->AppendString("<h3>");
	m_pHtmlBuffer->AppendString(strName.GetString());
	m_pHtmlBuffer->AppendString("</h3>");	
}
void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_Table_th_Gout(const CString &strTypeID)  //�����ӱ�ͷ
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("����");
	Gen_Table_th("��������");
	Gen_Table_th("����GOOSE�ź�");
	Gen_Table_th("���Խ��(s)");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_Table_th_Gin(const CString &strTypeID)  //�����ӱ�ͷ
{
	GenModule_Table_th(strTypeID);
	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("���");
	Gen_Table_th("����");
	Gen_Table_th("��������");
	Gen_Table_th("����GOOSE�ź�");
	Gen_Table_th("���Խ��(s)");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_Table_Point_GoutPubs(int nGoutCount)
{
	char strGooseOut[6];
	CIecCfgGoutData* pIecCfgData=g_pIntelligentTest->GetGoutData(nGoutCount);
	CIecCfgGoutChs *pIecChs = (CIecCfgGoutChs*)pIecCfgData->m_pCfgChs;
	CString appid=QString("%1").arg(pIecCfgData->m_dwAppID,4,16,QChar('0'));

	m_pHtmlBuffer->AppendString("<h3 >APPID��0X ");
	m_pHtmlBuffer->AppendString(appid.GetString());
	m_pHtmlBuffer->AppendString("&nbsp;IED���ƣ�");
	m_pHtmlBuffer->AppendString(pIecCfgData->m_strIedRefDesc.GetString());
	m_pHtmlBuffer->AppendString("</h3>");
	POS pos = pIecChs->GetHeadPosition();
	int j=0;
	while(pos)
	{			
		GetGooseSignal(g_pIntelligentTest->m_nGooseOutType[nGoutCount][j],strGooseOut);
		CIecCfgGoutCh* pIecCh = (CIecCfgGoutCh*)pIecCfgData->GetNext(pos);	
		
		m_pHtmlBuffer->AppendString("<tr>");

		Gen_Table_td(j+1);
		Gen_Table_td(pIecCh->m_strName.GetString());
		Gen_Table_td(pIecCh->m_strDataTypeName.GetString());
		Gen_Table_td(strGooseOut);
		Gen_Table_td(g_pIntelligentTest->m_fGooseOutTime[nGoutCount][j],3);

		m_pHtmlBuffer->AppendString("</tr>");

		j++;
	}

}
void CSttHtmlRptGen_IntelligentTerminal::GenIntelTerminal_Table_Point_GinPubs(int nGinCount)
{
	char strGooseIn[6];
	CIecCfgGinData* pIecCfgData=g_pIntelligentTest->GetGinData(nGinCount);
	CIecCfgGinChs *pIecChs = (CIecCfgGinChs*)pIecCfgData->m_pCfgChs;
	CString appid=QString("%1").arg(pIecCfgData->m_dwAppID,4,16,QChar('0'));

	m_pHtmlBuffer->AppendString("<h3 >APPID��0X ");
	m_pHtmlBuffer->AppendString(appid.GetString());
	m_pHtmlBuffer->AppendString("&nbsp;IED���ƣ�");
	m_pHtmlBuffer->AppendString(pIecCfgData->m_strIedRefDesc.GetString());
	m_pHtmlBuffer->AppendString("</h3>");
	POS pos = pIecChs->GetHeadPosition();
	int j=0;
	while(pos)
	{
		GetGooseSignal(g_pIntelligentTest->m_nGooseInType[nGinCount][j],strGooseIn);
		CIecCfgGinCh* pIecCh = (CIecCfgGinCh*)pIecCfgData->GetNext(pos);			
		m_pHtmlBuffer->AppendString("<tr>");

		Gen_Table_td(j+1);
		Gen_Table_td(pIecCh->m_strName.GetString());
		Gen_Table_td(pIecCh->m_strDataTypeName.GetString());
		Gen_Table_td(strGooseIn);
		Gen_Table_td(g_pIntelligentTest->m_fGooseInTime[nGinCount][j],3);

		m_pHtmlBuffer->AppendString("</tr>");
		j++;
	}
}
void CSttHtmlRptGen_IntelligentTerminal::GetGooseSignal(int nGooseType , char* m_pszGoose)
{
	if (nGooseType == 1)//��ֵ1�����ź�Ϊ"0->1"
	{
		strcpy(m_pszGoose,"0->1");
	}
	else if (nGooseType == 2)
	{
		strcpy(m_pszGoose,"1->0");
	}				
	else if (nGooseType == 3)
	{	
		strcpy(m_pszGoose,"11->00");
	}	
	else  if (nGooseType == 4)
	{
		strcpy(m_pszGoose,"10->01");		
	}
	else  if (nGooseType == 5)
	{
		strcpy(m_pszGoose,"01->10");		
	}
	else  if (nGooseType == 6)
	{
		strcpy(m_pszGoose,"00->11");		
	}
	else if(nGooseType == 0)
	{
		strcpy(m_pszGoose,"---");		
	}
}

