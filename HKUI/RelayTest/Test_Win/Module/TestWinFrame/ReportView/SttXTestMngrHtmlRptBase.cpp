#include "SttXTestMngrHtmlRptBase.h"
#include "../testwinbase.h"
#include "../../../SttStudio/Module/SttTest/Common/Impedance/tmt_distance_test.h"
#include "XLangResource_PowerTestWin.h"
/*
#define MAX_HTML_BUFFER_SIZE 1048576
*/
CSttXTestMngrHtmlRptBase *g_pSttXTestMngrHtmlRpt = NULL;

CSttXTestMngrHtmlRptBase::CSttXTestMngrHtmlRptBase()
{
	g_pSttXTestMngrHtmlRpt = this;
	m_oSttReprts.DeleteAll();
	InitReportGenCfg();
	InitStrTrFormat();

	m_pReportView = new QSttReportViewHtml();
	CTestDataTypeMngrConstGlobal::Create();
}

CSttXTestMngrHtmlRptBase::~CSttXTestMngrHtmlRptBase()
{
    if(m_pReportView != NULL)
	{
		delete m_pReportView;
		m_pReportView = NULL;
	}
	CTestDataTypeMngrConstGlobal::Release();
}

void CSttXTestMngrHtmlRptBase::InitReportGenCfg()
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += FILE_REPORTGENCFG_NAME;

	m_ReportGenCfg.OpenXmlFile(strPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);	
}

void CSttXTestMngrHtmlRptBase::InitStrTrFormat()
{
	int nGroupIndex = 0;
	CDataGroup *pGroup = (CDataGroup*)m_ReportGenCfg.FindByID(_P_GetMoudleFileName());
	if (pGroup)
	{
		//<tr id="$XID$$MacroID$Test###">  【Test为前缀，后面跟随测试点的编号】
		POS pos = pGroup->GetHeadPosition();
		CExBaseObject* pObj = pGroup->GetNext(pos);
		if(pObj->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			POS pos = pGroup->GetHeadPosition();
			while (pos)
			{
				CDataGroup* pSubGroup = (CDataGroup*)pGroup->GetNext(pos);
				m_strTrFormat[nGroupIndex] = "<tr id=\"$";
				m_strTrFormat[nGroupIndex] += _P_GetMoudleFileName();
				m_strTrFormat[nGroupIndex] += "$$%s$Test%04d\"><td name=\"index\">%d</td>";

				POS subPos = pSubGroup->GetHeadPosition();
				CDvmData *pData = NULL;
				while (subPos)
				{
					pData = (CDvmData*)pSubGroup->GetNext(subPos);
					m_strTrFormat[nGroupIndex]+="<td name=\"";
					m_strTrFormat[nGroupIndex]+=pData->m_strID;
					m_strTrFormat[nGroupIndex]+="\"></td>";
				}
				m_strTrFormat[nGroupIndex]+="</tr>";
				nGroupIndex++;
			}
		}
		else
		{
			m_strTrFormat[0] = "<tr id=\"$";
			m_strTrFormat[0] += _P_GetMoudleFileName();
			m_strTrFormat[0] += "$$%s$Test%04d\"><td name=\"index\">%d</td>";

			POS pos = pGroup->GetHeadPosition();
			CDvmData *pData = NULL;
			while (pos)
			{
				pData = (CDvmData*)pGroup->GetNext(pos);
				m_strTrFormat[0]+="<td name=\"";
				m_strTrFormat[0]+=pData->m_strID.GetString();
				m_strTrFormat[0]+="\"></td>";
			}
			m_strTrFormat[0]+="</tr>";
		}
	}
}

void CSttXTestMngrHtmlRptBase::InitTestMngrGroup() //初始化所有测试点按功能分组（每个功能模块需要重载）
{
	
}

void CSttXTestMngrHtmlRptBase::FillReportParent()
{
	FillReport();
}

void CSttXTestMngrHtmlRptBase::FillReport()  //向测试报告HTML文本中填测试参数
{
	//根据序列化内容生成m_oParas
	GetAllParas();

	//两层遍历
	//遍历每个分组
	//遍历每个分组下的每个测试点
	//获得每个测试点的参数、报告(JSON)，填写到报告中  报告试图的FillReportData
	//填写报告参见函数
	//QSttReportViewHtml::UpdateReportHead( CDataGroup *pSttReport )

	//遍历m_oParas
	CSttReports oReports;
	CSttReport *pReport = NULL;
	CDataGroup *pGroup = NULL;
	char* pszReport = NULL;

	POS pos = m_oParas.GetHeadPosition();
	while (pos != NULL)
	{
		// 遍历分组
		pGroup = (CDataGroup*)m_oParas.GetNext(pos);
		if (pGroup->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			//遍历测试点
			CDataGroup* pPoint = NULL;
			POS posPoint = pGroup->GetHeadPosition();
			while(posPoint!=NULL)
			{
				pPoint = (CDataGroup*)pGroup->GetNext(posPoint);
				CString strItemID = "$";
				strItemID += _P_GetMoudleFileName();
				strItemID += "$$";
				strItemID += pGroup->m_strID;
				strItemID += "$";
				strItemID += pPoint->m_strID;

				int nState = GetTestState(strItemID);
				FormatValueString(pPoint, nState, pGroup->m_strID);

				oReports.AddReport(pPoint);
				pReport = (CSttReport*)oReports.GetTail();
				ASSERT(pReport);
				pReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
				FillReportData("", strItemID, GetStateString(nState), pszReport);
				delete pszReport;
			}
		}
	}
}

/*
void CSttXTestMngrHtmlRptBase::InsertRptHtml()
{
	GenHtml();

	CString strParentPath = "";
	CString strItemsID = _P_GetMoudleFileName();
	char* pstrGbDatas = NULL;

	m_pReportView->SetRptFileData((char*)m_oHtmlBuffer.GetDataBuffer());
	m_pReportView->InsertRptHtml(strParentPath,strItemsID,pstrGbDatas);
}

void CSttXTestMngrHtmlRptBase::UpdateRptHtml()
{
	m_oHtmlBuffer.PosMoveByUsedLen(MAX_HTML_BUFFER_SIZE);
	memset((char*)m_oHtmlBuffer.GetDataBuffer(), 0, MAX_HTML_BUFFER_SIZE);
	GenHtml();

	CString strParentPath = "";
	CString strItemsID = _P_GetMoudleFileName();
	char* pstrGbDatas = NULL;

	m_pReportView->SetRptFileData((char*)m_oHtmlBuffer.GetDataBuffer());
	//m_pReportView->UpdateRptHtml(strParentPath,strItemsID,strGbDatas);
	m_pReportView->DeleteRptHtml(strParentPath, strItemsID);
	m_pReportView->InsertRptHtml(strParentPath,strItemsID,pstrGbDatas);
}
*/

//void CSttXTestMngrHtmlRptBase::UpdateItemState(const CString& strState)
//{
//	CString strParentPath = "";
//	CString strItemsID = _P_GetMoudleFileName();
//
//	m_pReportView->ItemStateChanged(strParentPath,strItemsID,strState);
//}
//
//更新测试报告中单个测试点的状态
void CSttXTestMngrHtmlRptBase::UpdateItemState(int nIndex, int nState)
{
	if(nIndex<0)
	{
		return;
	}

	PTMT_PARAS_HEAD pParasTest = g_theSttXTestMngrBaseApp->m_oTmtTestMngr.m_pParasBuffer[nIndex];
	CString strState = GetStateString(pParasTest->m_nTestState);
	m_pReportView->ItemStateChanged("", m_strPointID[nIndex], strState);
}

/*
void CSttXTestMngrHtmlRptBase::OpenHead()  //打开报告头ReportHeader.html
{
	ASSERT(m_pReportView);
	if(m_pReportView == NULL)
	{
		return;
	}

	m_pReportView->OpenReportFile(STT_REPORT_HEAD_HTML_FILE);
}

void CSttXTestMngrHtmlRptBase::FillHead()  //使用ReportHead_Paras.xml填充报告头html
{
	CString strReportHeaderCfg;
	strReportHeaderCfg = _P_GetDBPath();
	strReportHeaderCfg += "atsgen/";
	strReportHeaderCfg += ("ReportHead_Paras.xml");

	CDataGroup oReportHeader_Paras;

	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oReportHeader_Paras.OpenXmlFile(strReportHeaderCfg,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if(m_pReportView)
	{
		((QSttReportViewHtml*)m_pReportView)->UpdateReportHead( &oReportHeader_Paras );
	}
}
*/
void CSttXTestMngrHtmlRptBase::GenHtml()  //生成测试报告HTML文本
{
	m_bHtmlGened = false;

	//生成m_oParas
	GetAllParas();

	GenRootDiv();
	GenRootDiv_H1();
	GenTestMngr();
	GenRootDiv_End();

	m_bHtmlGened = true;
}

//<div id="$XID$"> 			//具体说明参见3.2
void CSttXTestMngrHtmlRptBase::GenRootDiv()
{
	m_oHtmlBuffer.AppendString("<div id=\"");
	m_oHtmlBuffer.AppendString(_P_GetMoudleFileName());
	m_oHtmlBuffer.AppendString("\">");
}

void CSttXTestMngrHtmlRptBase::GenRootDiv_H1()
{
	
}

void CSttXTestMngrHtmlRptBase::GenRootDiv_End()
{
	m_oHtmlBuffer.AppendString("</div>");
}

void CSttXTestMngrHtmlRptBase::GenTestMngr()  //生成整个子表节点
{
	PTMT_PARAS_MNGR pParasMngr;
	int nCount = min(m_oTmtTestMngrGroup.m_nGroupCount,TMT_TEST_MNGR_MAX_GROUP_COUNT);
	for (int i=0;i<nCount;i++)
	{
		pParasMngr = m_oTmtTestMngrGroup.m_pTestMngr[i]; //分组
		GenTestMngr_RootDiv(pParasMngr);
		GenTestMngr_h2(pParasMngr);
		GenTestMngr_Table(pParasMngr);
		GenRootDiv_End();
	}
}

//<div id="$XID$$PPDis1" class="stt_rpt" type="stt_items">
void CSttXTestMngrHtmlRptBase::GenTestMngr_RootDiv(PTMT_PARAS_MNGR pParasMngr)  //生成子表根节点
{
	ASSERT(pParasMngr != NULL);

	char* pszGroupDiv = GetGroupDivID(pParasMngr->m_pszMacroID);
	CString strModuleID;
	strModuleID = _P_GetMoudleFileName();
	strModuleID += _T("$");
	strModuleID += pszGroupDiv;

	GenModule_RootDiv(strModuleID);

/*
	m_oHtmlBuffer.AppendString("<div id=\"");
	m_oHtmlBuffer.AppendString(_P_GetMoudleFileName());
	m_oHtmlBuffer.AppendString("$");
	m_oHtmlBuffer.AppendString(pszGroupDiv);
	m_oHtmlBuffer.AppendString("\" class=\"stt_rpt\"");
	m_oHtmlBuffer.AppendString(" type=\"stt_items\">");
*/

}

//<h2>相间故障Ⅰ段定值测试</h2>
void CSttXTestMngrHtmlRptBase::GenTestMngr_h2(PTMT_PARAS_MNGR pParasMngr)		//生成子表标题
{
	ASSERT(pParasMngr != NULL);

	m_oHtmlBuffer.AppendString("<h2>");
	m_oHtmlBuffer.AppendString(pParasMngr->m_pszMacroID);
	m_oHtmlBuffer.AppendString("</h2>");
}

//<table id="$XID$$MacroID_Table" border="1" cellspacing="0" cellpadding="0" type="stt_table">
/*<tr>
	<th style="width:40px;">编号</th>
	<th style="width:90px;">故障类型</th>
	<th style="width:74px;">整定定值</th>
	<th style="width:74px;">整定时间</th>
	<th style="width:56px;">倍数</th>
	<th style="width:71px;">阻抗角</th>
	<th style="width:83px;">跳A</th>
	<th style="width:83px;">跳B</th>
	<th style="width:83px;">跳C</th>
</tr>
*/
void CSttXTestMngrHtmlRptBase::GenTestMngr_Table(PTMT_PARAS_MNGR pParasMngr)  //生成子表的<table>部分
{
	GenTestMngr_Table_th(pParasMngr);
	GenTestMngr_Point(pParasMngr);
	GenTestMngr_Table_te();
}

void CSttXTestMngrHtmlRptBase::GenTestMngr_Table_th(PTMT_PARAS_MNGR pParasMngr)  //生成子表头
{
	ASSERT(pParasMngr != NULL);

	char* pszGroupDiv = GetGroupDivID(pParasMngr->m_pszMacroID);
	CString strModuleID;
	strModuleID = pParasMngr->m_pszMacroID;
	strModuleID += "$";
	strModuleID += pszGroupDiv;


	CDataGroup *pGroup = (CDataGroup*)m_ReportGenCfg.FindByID(_P_GetMoudleFileName());

	if (pGroup)
	{
		CDataGroup* pSubGroup = (CDataGroup*)pGroup->FindByID(pszGroupDiv);
	
		if(pSubGroup)
		{
			pGroup = pSubGroup;
		}
	}

	GenModule_Table_th(strModuleID, pGroup, TRUE);

/*	m_oHtmlBuffer.AppendString("<table id=\"");
	m_oHtmlBuffer.AppendString(pParasMngr->m_pszMacroID);
	m_oHtmlBuffer.AppendString("$");
	m_oHtmlBuffer.AppendString(pszGroupDiv);
	m_oHtmlBuffer.AppendString("_Table\"");

	m_oHtmlBuffer.AppendString(" border=\"1\"");
	m_oHtmlBuffer.AppendString(" cellspacing=\"0\"");
	m_oHtmlBuffer.AppendString(" cellpadding=\"0\"");

	m_oHtmlBuffer.AppendString(" type=\"stt_table\" style=\"text-align:center;\">");

	//m_oHtmlBuffer.AppendString("<tr>");
	AppendTr();

	CDataGroup *pGroup = (CDataGroup*)m_ReportGenCfg.FindByID(_P_GetMoudleFileName());
	if (pGroup)
	{
		CDataGroup* pSubGroup = (CDataGroup*)pGroup->FindByID(pszGroupDiv);
		if(pSubGroup)
		{
			pGroup = pSubGroup;
		}

		POS pos = pGroup->GetHeadPosition();
		CDvmData *pData = NULL;

		m_oHtmlBuffer.AppendString("<th>编号</th>");

		while (pos)
		{
			pData = (CDvmData*)pGroup->GetNext(pos);
			m_oHtmlBuffer.AppendString("<th>");
			m_oHtmlBuffer.AppendString(pData->m_strName.GetString());
			m_oHtmlBuffer.AppendString("</th>");
		}
	}
	m_oHtmlBuffer.AppendString("</tr>");
*/
}

//</table>
void CSttXTestMngrHtmlRptBase::GenTestMngr_Table_te()  //生成子表尾
{
	//m_oHtmlBuffer.AppendString("</table>");
	GenModule_Table_te();
}
/*
<tr id="$XID$$MacroID$Test###">  【Test为前缀，后面跟随测试点的编号】
<td name="index">1</td>  【固定：index，表示编号】
<td name="FaultType">A相接地</td>【测试点数据，故障类型】
PHASE_A_GROUNDING       = 0,    // A相接地
PHASE_B_GROUNDING       = 1,    // B相接地
PHASE_C_GROUNDING       = 2,    // C相接地
PHASE_AB_SHORT_CIRCUIT  = 3,    // AB短路
PHASE_BC_SHORT_CIRCUIT  = 4,    // BC短路
PHASE_CA_SHORT_CIRCUIT  = 5,    // CA短路
PHASE_AB_GROUND_SHORT   = 6,    // AB接地短路
PHASE_BC_GROUND_SHORT   = 7,    // BC接地短路
PHASE_CA_GROUND_SHORT   = 8,    // CA接地短路
PHASE_ABC_SHORT_CIRCUIT = 9,    // ABC三相短路
SINGLE_PHASE_FAULT      = 10    // 单相系统

<td name="ISetting">5.000A</td>【测试点数据，整定电流】
<td name="TSetting">0.000s</td>
<td name="Rate">1.05</td>
<td name="TtripA">0.025s</td>【测试点数据，跳A动作时间】
<td name="TtripB">未动作 name</td>
<td name="TtripC">未动作</td>
</tr>
*/

void CSttXTestMngrHtmlRptBase::GenTestMngr_Point(PTMT_PARAS_MNGR pParasMngr)
{
	//遍历pParasMngr，生成每个测试点的数据
	char pszTr[1024];
	int nCount = pParasMngr->m_nCount;
	char* pszDivID = GetGroupDivID(pParasMngr->m_pszMacroID);
	int nIndex = GetGroupIndexByDivID(pszDivID);
	for(int i=0;i<nCount;i++)
	{
		sprintf(pszTr, m_strTrFormat[nIndex].GetString(), pszDivID, i+1, i+1);
		m_oHtmlBuffer.AppendString(pszTr);
	}
}

void CSttXTestMngrHtmlRptBase::FormatDataTypeString(CDataGroup* p, CString strID)
{
	CDataType *pDataType = NULL;
	pDataType = CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(strID);
	CDvmData *pData = (CDvmData*)p->FindByID(strID);
	if(pData)
	{
	int nType = atoi(pData->m_strValue.GetString());
	CDataTypeValue *pDataTypeValue = pDataType->FindByIndex(nType);
	pData->m_strValue = pDataTypeValue->m_strName;
}
}

void CSttXTestMngrHtmlRptBase::FormatFaultTypeString(CDataGroup* p,CString strID)
{
	CDvmData* pData = (CDvmData*)p->FindByID(strID);
	if(pData)
	{
		int nErrorType = atoi(pData->m_strValue.GetString());
		pData->m_strValue = getErrorTypeStringByEnum((ErrorType)nErrorType);
	}
}

void CSttXTestMngrHtmlRptBase::FormatFaultTypeVolString(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultType");
	if(pData)
	{
		int nFaultType = atoi(pData->m_strValue.GetString());
		if(nFaultType==0)
		{
			pData->m_strValue = /*"A相电压"*/g_sLangTxt_Native_PhAVoltage;
		}
		else if(nFaultType==1)
		{
			pData->m_strValue = /*"B相电压"*/g_sLangTxt_Native_PhBVoltage;
		}
		else if(nFaultType==2)
		{
			pData->m_strValue = /*"C相电压"*/g_sLangTxt_Native_PhCVoltage;
		}
		else if(nFaultType==3)
		{
			pData->m_strValue = /*"ABC相电压"*/g_sLangTxt_Native_PhABCVoltage;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatForDecString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fTtrip = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%.4f",fTtrip);
	}
}

void CSttXTestMngrHtmlRptBase::FormatThrDecString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fTtrip = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.3f",fTtrip);
	}
}

void CSttXTestMngrHtmlRptBase::FormatTwoDecString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fRate = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.2f",fRate);
	}
}

void CSttXTestMngrHtmlRptBase::FormatOneDecString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fVol = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.1f",fVol);
	}
}


void CSttXTestMngrHtmlRptBase::FormatTtripString(CDataGroup* p, const char* pszType, int nState)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fTtrip = atof(pData->m_strValue.GetString());
		if(abs(fTtrip)<0.0001)
		{
			if(nState==0)
			{
				pData->m_strValue = "--";
			}
			else
			{
				pData->m_strValue = /*"未动作"*/g_sLangTxt_State_NoActioned;
			}
		}
		else
		{
			pData->m_strValue.Format("%.4f",fTtrip);
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatErrorString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fVol = atof(pData->m_strValue.GetString());

		CDvmData* pTtripData = (CDvmData*)p->FindByID("TripTime");
		if (pTtripData)
		{
			float fTtrip = atof(pTtripData->m_strValue.GetString());
			if(abs(fTtrip)<0.0001)
			{
				pData->m_strValue = "--";
			}
			else
			{
				pData->m_strValue.Format("%.1f",fVol);
			}			
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatFaultTypeString(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultType");
	if(pData)
	{
		int nErrorType = atoi(pData->m_strValue.GetString());
		pData->m_strValue = getErrorTypeStringByEnum((ErrorType)nErrorType);
	}
}

void CSttXTestMngrHtmlRptBase::FormatTimeString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fTtrip = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.3f",fTtrip);
	}
}

void CSttXTestMngrHtmlRptBase::FormatRateString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fRate = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.2f",fRate);
	}
}

void CSttXTestMngrHtmlRptBase::FormatVoltageString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fVol = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8.1f",fVol);
	}
}

void CSttXTestMngrHtmlRptBase::FormatDirString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nDir = atoi(pData->m_strValue.GetString());
		if(nDir==0)
		{
			pData->m_strValue = /*"反方向"*/g_sLangTxt_Native_RevDirection;
		}
		else
		{
			pData->m_strValue = /*"正方向"*/g_sLangTxt_Native_PosDirection;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatAngleString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
		{
		float fAng = atof(pData->m_strValue.GetString());
		pData->m_strValue.Format("%.1f",fAng);
	}
		}

void CSttXTestMngrHtmlRptBase::FormatAngleString(CDataGroup* p, const char* pszType, int nState)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		if(nState==0)
		{
			pData->m_strValue = "";
		}
		else
		{
			float fAng = atof(pData->m_strValue.GetString());
			pData->m_strValue.Format("%.1f",fAng);
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatFaultTypeUString(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultVolType");
	if(pData)
	{
		int nFaultType = atoi(pData->m_strValue.GetString());
		if(nFaultType==0)
		{
			pData->m_strValue = /*"短路电压"*/g_sLangTxt_Native_ShortCircuitV;
		}
		else if(nFaultType==2)
		{
			pData->m_strValue = /*"负序电压"*/g_sLangTxt_Native_NegSeqVol;
		}
		else if(nFaultType==3)
		{
			pData->m_strValue = /*"零序电压"*/g_sLangTxt_Native_ZeroSeqVolt;
		}
	}
}



void CSttXTestMngrHtmlRptBase::FormatFaultType1String(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultType1");
	if(pData)
	{
		int nErrorType = atoi(pData->m_strValue.GetString());
		pData->m_strValue = getErrorTypeStringByEnum((ErrorType)nErrorType);
	}
}

void CSttXTestMngrHtmlRptBase::FormatFaultType2String(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultType1");
	if(pData)
	{
		int nErrorType = atoi(pData->m_strValue.GetString());
		pData->m_strValue = getErrorType1StringByEnum((ErrorType)nErrorType);
	}
}

void CSttXTestMngrHtmlRptBase::FormatFreqString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		float fFreq = atoi(pData->m_strValue.GetString());
		pData->m_strValue.Format("%8d",fFreq);
	}
}

void CSttXTestMngrHtmlRptBase::FormatPerString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nPer = atoi(pData->m_strValue.GetString());
		if(nPer==0)
		{
			pData->m_strValue = /*"瞬时"*/g_sLangTxt_Native_Immediate;
		}
		else
		{
			pData->m_strValue = /*"永久"*/g_sLangTxt_Native_Permanent;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatTranString(CDataGroup* p,const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nTrans = atoi(pData->m_strValue.GetString());
		if(nTrans==1)
		{
			pData->m_strValue = /*"是"*/g_sLangTxt_State_Yes;
		}
		else
		{
			pData->m_strValue = /*"否"*/g_sLangTxt_State_No;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatModString(CDataGroup* p,const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nMod = atoi(pData->m_strValue.GetString());
		if(nMod==0)
		{
			pData->m_strValue = /*"时间触发"*/g_sLangTxt_State_Trigger_Time;
		}
		else if(nMod==1)
		{
			pData->m_strValue = /*"时间+开入量触发"*/g_sLangTxt_Native_TDITrigger;
		}
		else if(nMod==2)
		{
			pData->m_strValue = /*"开入量触发"*/g_sLangTxt_State_Trigger_Bin;
		}
		else if(nMod==3)
		{
			pData->m_strValue = /*"手动触发"*/g_sLangTxt_State_Trigger_Manu;
		}
		else
		{
			pData->m_strValue = /*"GPS/B码触发"*/g_sLangTxt_State_Trigger_GPSB;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatBInString(CDataGroup* p, const char* pszType)
{	
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nBIn = atoi(pData->m_strValue.GetString());
		if(nBIn==0)
		{
			pData->m_strValue = /*"逻辑或"*/g_sLangTxt_Native_LogicOr;
		}
		else
		{
			pData->m_strValue = /*"逻辑与"*/g_sLangTxt_Native_LogicAnd;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatBOutString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nBOut = atoi(pData->m_strValue.GetString());
		if(nBOut==0)
		{
			pData->m_strValue = /*"断开"*/g_sLangTxt_SOE_Break;
		}
		else
		{
			pData->m_strValue = /*"闭合"*/g_sLangTxt_SOE_Shutting;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatTAString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nTA = atoi(pData->m_strValue.GetString());
		if(nTA==0)
		{
			pData->m_strValue = /*"指向母线"*/g_sLangTxt_Native_TowardBus;
		}
		else
		{
			pData->m_strValue = /*"指向线路"*/g_sLangTxt_Native_TowardLine;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatTVString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nTV = atoi(pData->m_strValue.GetString());
		if(nTV==0)
		{
			pData->m_strValue = /*"母线侧"*/g_sLangTxt_Native_BusSide;
		}
		else
		{
			pData->m_strValue = /*"线路侧"*/g_sLangTxt_Native_LineSide;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatIdString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nId = atoi(pData->m_strValue.GetString());
		if(nId==0)
		{
			pData->m_strValue = /*"叠加"*/g_sLangTxt_Native_Overlay;
		}
		else
		{
			pData->m_strValue = /*"不叠加"*/g_sLangTxt_Native_NoOverlay;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatBrString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nBr = atoi(pData->m_strValue.GetString());
		if(nBr==0)
		{
			pData->m_strValue = /*"不模拟"*/g_sLangTxt_Native_NoSimulation;
		}
		else
		{
			pData->m_strValue = /*"模拟"*/g_sLangTxt_ChMaps_Analog;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatChString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nCh = atoi(pData->m_strValue.GetString());
		if(nCh==0)
		{
			pData->m_strValue = /*"随机"*/g_sLangTxt_Native_Random;
		}
		else
		{
			pData->m_strValue = /*"定值"*/g_sLangTxt_FixedValue;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatSearchString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nSearch = atoi(pData->m_strValue.GetString());
		if(nSearch==0)
		{
			pData->m_strValue = /*"二分法"*/g_sLangTxt_Native_BinSearch;
		}
		else
		{
			pData->m_strValue = /*"单步逼近"*/g_sLangTxt_Native_StepApprox;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatKModeString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nKMode = atoi(pData->m_strValue.GetString());
		if(nKMode==0)
		{
			pData->m_strValue = "|K0|,Phi(K0)";
		}
		else if(nKMode==1)
		{
			pData->m_strValue = "RERL,XEXL";
		}
		else
		{
			pData->m_strValue = "|Z0/Z1|,Phi(Z0/Z1)";
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatVzDfString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nVzDf = atoi(pData->m_strValue.GetString());
		if(nVzDf==0)
		{
			pData->m_strValue = "0";
		}
		else if(nVzDf==1)
		{
			pData->m_strValue = "Va";
		}
		else if(nVzDf==2)
		{
			pData->m_strValue = "Vb";
		}
		else if(nVzDf==3)
		{
			pData->m_strValue = "Vc";
		}
		else if(nVzDf==4)
		{
			pData->m_strValue = "√3x3Vo";
		}
		else if(nVzDf==5)
		{
			pData->m_strValue = "-√3x3Vo";
		}
		else if(nVzDf==6)
		{
			pData->m_strValue = "3Vo";
		}
		else
		{
			pData->m_strValue = "-3Vo";
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatDfString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID("VzPhDefine");
	if(pData)
	{
		int nDf = atoi(pData->m_strValue.GetString());
		if(nDf==0)
		{
			pData->m_strValue = /*"Va相位"*/"Va"+g_sLangTxt_Native_Phase;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatZmodeString(CDataGroup* p, const char* pszType)
{
	CDvmData* pData = (CDvmData*)p->FindByID(pszType);
	if(pData)
	{
		int nZmode = atoi(pData->m_strValue.GetString());
		if(nZmode==0)
		{
			pData->m_strValue = /*"电流不变"*/g_sLangTxt_Native_INotChange;
		}
		else if(nZmode==1)
		{
			pData->m_strValue = /*"电压不变"*/g_sLangTxt_Native_UNotChange;
		}
		else
	{
			pData->m_strValue = /*"系统阻抗不变"*/g_sLangTxt_Native_ZNotChange;
		}
	}
}

void CSttXTestMngrHtmlRptBase::FormatFaultTypeVDfString(CDataGroup* p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("FaultVolDef");
	if(pData)
	{
		int nVolDef = atoi(pData->m_strValue.GetString());
		if(nVolDef==0)
		{
			pData->m_strValue = /*"相电压"*/g_sLangTxt_Native_PhVolt;
		}
		else if(nVolDef==1)
		{
			pData->m_strValue = /*"线电压"*/g_sLangTxt_Native_LineVolt;
	}
	}	
}

void CSttXTestMngrHtmlRptBase::FormatValueTypeString(CDataGroup *p)
{
	CDvmData* pData = (CDvmData*)p->FindByID("RefValueType");
	if(pData)
	{
		int nValueType = atoi(pData->m_strValue.GetString());
		if(nValueType==0)
		{
			pData->m_strValue = "In";
		}
		else if(nValueType==1)
		{
			pData->m_strValue = "In*Ip";
		}
	}
}

char* CSttXTestMngrHtmlRptBase::GetStateString(int nState)
{
	switch(nState)
	{
	case 0:
		return "NORMAL";
	case 1:
		return "ELIGIBLE";
	case 2:
		return "INLEGIBLE";
	default:
		return "NORMAL";
	}
}

void CSttXTestMngrHtmlRptBase::FillReport(int nIndex, int nState)  //向测试报告HTML文本中填测试参数
{
	if(nIndex<0)
	{
		return;
	}
	CSttReports oReports;
	CSttReport *pReport = NULL;
	CDataGroup *pGroup = NULL;
	char* pszReport = NULL;
	bool bFound = false;

	GetAllParas();

	POS pos = m_oParas.GetHeadPosition();
	while (pos != NULL)
	{
		// 遍历分组
		pGroup = (CDataGroup*)m_oParas.GetNext(pos);
		if (pGroup->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			//遍历测试点
			CDataGroup* pPoint = NULL;
			POS posPoint = pGroup->GetHeadPosition();
			while(posPoint!=NULL)
			{
				pPoint = (CDataGroup*)pGroup->GetNext(posPoint);

				CString strItemID = "$";
				strItemID += _P_GetMoudleFileName();
				strItemID += "$$";
				strItemID += pGroup->m_strID;
				strItemID += "$";
				strItemID += pPoint->m_strID;

				if(strItemID==m_strPointID[nIndex])
				{
					FormatValueString(pPoint, nState, pGroup->m_strID);
					oReports.AddReport(pPoint);
					pReport = (CSttReport*)oReports.GetTail();
					ASSERT(pReport);
					pReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
					FillReportData("", strItemID, GetStateString(nState), pszReport);
					delete pszReport;
					return;
				}
			}
		}
	}
}

int CSttXTestMngrHtmlRptBase::GetTestState(const CString &strItemID)
{
	int nState = 0;
	for(int i=0;i<g_theSttXTestMngrBaseApp->m_oTmtTestMngr.m_nCount;i++)
	{
		if(strItemID==m_strPointID[i])
	{
			nState = g_theSttXTestMngrBaseApp->m_oTmtTestMngr.m_pParasBuffer[i]->m_nTestState;
			break;
		}
	}
	return nState;
}

int CSttXTestMngrHtmlRptBase::GetGroupIndexByDivID(const char* pszDivID)
{
	int nGroupIndex = 0;
	CDataGroup *pGroup = (CDataGroup*)m_ReportGenCfg.FindByID(_P_GetMoudleFileName());
	if (pGroup)
	{
		if(pGroup->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			return 0;
		}
		POS pos = pGroup->GetHeadPosition();
		CDataGroup *pData = NULL;
		while (pos)
		{
			pData = (CDataGroup*)pGroup->GetNext(pos);
			if(pData->m_strID==CString(pszDivID))
			{
				return nGroupIndex;
			}
			nGroupIndex++;
	}
	}
	return 0;
}

/*
void CSttXTestMngrHtmlRptBase::FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport)
{
	m_pReportView->FillReportData(strParentItemsPath, strItemID, strState, pszReport);
}
*/

void CSttXTestMngrHtmlRptBase::FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport)
{
	CSttModuleHtmlRptGenBase::FillReportData(strParentItemsPath, strItemID, strState, pszReport);
}

QString CSttXTestMngrHtmlRptBase::getErrorType1StringByEnum( ErrorType type )
{
	QStringList errorTypeList;
	errorTypeList<</*QObject::tr("A相接地")*/g_sLangTxt_Native_GndA<</*QObject::tr("B相接地")*/g_sLangTxt_Native_GndB<</*QObject::tr("C相接地")*/g_sLangTxt_Native_GndC<</*QObject::tr("AB短路")*/g_sLangTxt_Native_ShortAB<</*QObject::tr("BC短路")*/g_sLangTxt_Native_ShortBC\
		<</*QObject::tr("CA短路")*/g_sLangTxt_Native_ShortCA<</*QObject::tr("ABC短路")*/g_sLangTxt_Native_ABCSC;

	return errorTypeList.at(type);
}

void CSttXTestMngrHtmlRptBase::AppendTr()
{
	m_oHtmlBuffer.AppendString("<tr>");
}
