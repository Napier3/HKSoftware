#include "stdafx.h"
#include "CommCmd.h"
#include "Device.h"
#include <math.h>
#include "GuideBook.h"
#include "MacroTest.h"
#include "../../../Module/API/MathApi.h"
#include "../XLanguageResourceAts.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define CAL_SOETIME_VALUE_FLAG  _T("$t")

long g_nOptrAddToAllCmdBeforeIs1 = 1;
CExBaseList *g_pOptrAddToAllCmdRootItems = NULL;

const CString CCommCmd::g_strDsvResultID_All = _T("_SOE_RPT_");
const CString CCommCmd::g_strDsvResultID_t = _T("_SOE_RPT_t");
const CString CCommCmd::g_strDsvResultID_All_Trip = _T("_SOE_RPT_trip");
const CString CCommCmd::g_strDsvResultID_More = _T("_SOE_RPT_more");
const CString CCommCmd::g_strDsvResultID_Miss= _T("_SOE_RPT_miss");
const CString CCommCmd::g_strDsvResultID_AppearForErr= _T("_SOE_RPT_err");
const CString CCommCmd::g_strDsvResultID_Trip_desc = _T("_SOE_trip_desc");
const CString CCommCmd::g_strDsvResultID_Std = _T("_SOE_STD_");
const CString CCommCmd::g_strParas_Name_Val = _T("_Paras_NmVal_");

const CString CCommCmd::g_strCmdID_ReadSoe = _T("ReadSoe");
const CString CCommCmd::g_strCmdID_ReadLog = _T("ReadLog");
const CString CCommCmd::g_strCmdID_StartRecord = _T("StartRecord"); //StartRecord
const CString CCommCmd::g_strCmdID_ReadDir = _T("ReadDir"); //ReadDir
const CString CCommCmd::g_strCmdID_ReadFile = _T("ReadFile"); //ReadFile
const CString CCommCmd::g_strCmdID_Para_TimeStart = _T("tmStart"); //tmStart
const CString CCommCmd::g_strCmdID_Para_TimeEnd = _T("tmEnd"); //tmEnd
const CString CCommCmd::g_strCmdID_LoadIecfg = _T("LoadIecfg");  //LoadIecfg
const CString CCommCmd::g_strCmdID_Para_IefcgFile = _T("IefcgFile"); 


CCommCmd::CCommCmd()
{
	if (g_bstrCommCmdDataExModeName[0].GetLength() == 0)
	{
		g_bstrCommCmdDataExModeName[0] = g_sLangTxt_CellpAdding/*_T("单元格填充")*/;
		g_bstrCommCmdDataExModeName[1] = g_sLangTxt_ColumnFillMmode/*_T("列填充模式")*/;
		g_bstrCommCmdDataExModeName[2] = g_sLangTxt_HnagFillMmode/*_T("行填充模式")*/;
	}

	m_pCmd = NULL;
	m_pRptTags = NULL;
	m_pRptDataEx = NULL;
	m_bWzdHasInitDataset = FALSE;
	m_pDsvScript = NULL;
	m_nSortSoeByT = 0;
	m_nDsvRunAfterResultScript = 0;

	m_nCmdExecModeForMgbrpt = CmdExecModeForMgbrpt_ALLRPT;
	m_nFillRptDataset = 0;
}

CCommCmd::~CCommCmd()
{
	
}

CGbItemBase* CCommCmd::CloneForTempFile()
{
	return new CCommCmd();
}

BOOL CCommCmd::GetItemParaValue(const CString &strValueID, double &dValue)
{
	return 0;
}

long CCommCmd::SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew)
{
	ASSERT (m_pCmd != NULL);

	CValue  *pValue = (CValue*)m_pCmd->FindByID(strValueID);

	if (pValue == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s[%s]) Para (%s) not exist"), m_strName.GetString(), m_strID.GetString(), strValueID.GetString());
	}
	else
	{
		pValue->m_strValue = strValue;
	}

	return 0;
}

long CCommCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeCalLen(oBinaryBuffer, m_strRwOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_nSortSoeByT);
		BinarySerializeCalLen(oBinaryBuffer, m_nDsvRunAfterResultScript);
		BinarySerializeCalLen(oBinaryBuffer, m_nCmdExecModeForMgbrpt);
		BinarySerializeCalLen(oBinaryBuffer, m_nFillRptDataset);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeRead(oBinaryBuffer, m_strRwOptr);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_19)
		{
			BinarySerializeRead(oBinaryBuffer, m_nSortSoeByT);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_32)
		{
			BinarySerializeRead(oBinaryBuffer, m_nDsvRunAfterResultScript);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_34)
		{
			BinarySerializeRead(oBinaryBuffer, m_nCmdExecModeForMgbrpt);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_43)
		{////2022-10-3  lijunqing 
			BinarySerializeRead(oBinaryBuffer, m_nFillRptDataset);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeWrite(oBinaryBuffer, m_strRwOptr);
		BinarySerializeWrite(oBinaryBuffer, m_nSortSoeByT);
		BinarySerializeWrite(oBinaryBuffer, m_nDsvRunAfterResultScript);
		BinarySerializeWrite(oBinaryBuffer, m_nCmdExecModeForMgbrpt);
		BinarySerializeWrite(oBinaryBuffer, m_nFillRptDataset);
	}

	return 0;
}

long CCommCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,pXmlRWKeys);
	
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strCommCmdID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCmdRwKey,oNode,m_strRwOptr);
	m_strRwOptr.MakeLower();

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strSortSoeByTKey,oNode,m_nSortSoeByT);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvRunAfterResultScriptKey,oNode,m_nDsvRunAfterResultScript);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCmdExecModeForMgbrptKey,oNode,m_nCmdExecModeForMgbrpt);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strFillRptDatasetKey,oNode, m_nFillRptDataset);

	return 0;
}

long CCommCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strCommCmdID);

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCmdRwKey,oElement,m_strRwOptr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strSortSoeByTKey,oElement,m_nSortSoeByT);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvRunAfterResultScriptKey,oElement,m_nDsvRunAfterResultScript);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCmdExecModeForMgbrptKey,oElement,m_nCmdExecModeForMgbrpt);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strFillRptDatasetKey,oElement,m_nFillRptDataset);

	return 0;
}

void CCommCmd::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CExBaseList oList;

	while(pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_CMD:
			m_pCmd = (CCmd*)p;
			break;
		case DTMCLASSID_CTAGS:
			m_pRptTags = (CTags*)p;
			break;
		case DTMCLASSID_CSHORTDATAS:
			m_pRptDataEx = (CShortDatas*)p;
			break;

		case DVMCLASSID_CDSVSCRIPT:
			oList.AddTail(p);
			m_pDsvScript = (CDsvScript *)p;
			break;
		}
	}

	if (m_pCmd == NULL)
	{
		m_pCmd = (CCmd*)AddNewChild(new CCmd());
	}

// 	if (m_pRptTags == NULL)
// 	{
// 		m_pRptTags = (CTags*)AddNewChild(new CTags());
// 	}

	if (m_pRptDataEx == NULL)
	{
		m_pRptDataEx = (CShortDatas*)AddNewChild(new CShortDatas());
	}

	TransToRptDataEx();

	pos = oList.Find(m_pDsvScript);

	if (pos != NULL)
	{
		oList.RemoveAt(pos);
	}

	pos = oList.GetHeadPosition();

	while(pos != NULL)
	{
		p = oList.GetNext(pos);
		Delete(p);
	}
	oList.RemoveAll();
}

void CCommCmd::TransToRptDataEx()
{
	if (m_pRptTags == NULL)
	{
		return;
	}

	POS pos = m_pRptTags->GetHeadPosition();
	CTag *pTag = NULL;

	while (pos != NULL)
	{
		pTag = (CTag *)m_pRptTags->GetNext(pos);
		m_pRptDataEx->AddNew2(pTag->m_strID, pTag->m_strID, _T(""), pTag->m_strDataType, pTag->m_strValue, 0, _T(""), _T(""));
	}

	Delete(m_pRptTags);
	m_pRptTags = NULL;
}

CExBaseObject* CCommCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCmdKey)
	{
		m_pCmd = new CCmd;
		return m_pCmd;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCTagsKey)
	{
		m_pRptTags = new CTags;
		return m_pRptTags;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCShortDatasKey)
	{
		m_pRptDataEx = new CShortDatas;
		return m_pRptDataEx;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCDsvScriptKey)
	{
		ASSERT (m_pDsvScript == NULL);

		if (m_pDsvScript != NULL)
		{
			return NULL;
		}

		m_pDsvScript = new CDsvScript();
		return m_pDsvScript;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CCommCmd::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_CMD)
	{
		m_pCmd = new CCmd;
		return m_pCmd;
	}
	else if(nClassID == DTMCLASSID_CTAGS)
	{
		m_pRptTags = new CTags;
		return m_pRptTags;
	}
	else if(nClassID == DTMCLASSID_CSHORTDATAS)
	{
		m_pRptDataEx = new CShortDatas;
		return m_pRptDataEx;
	}
	else if(nClassID == DVMCLASSID_CDSVSCRIPT)
	{
		ASSERT (m_pDsvScript == NULL);
		m_pDsvScript = new CDsvScript();
		return m_pDsvScript;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

BOOL CCommCmd::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CCommCmd::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CCommCmd* pCommCmd = (CCommCmd*)pDesObj;

	pCommCmd->m_strCommCmdID = m_strCommCmdID;
	pCommCmd->m_nSortSoeByT = m_nSortSoeByT;
	pCommCmd->m_nDsvRunAfterResultScript = m_nDsvRunAfterResultScript;
	pCommCmd->m_strRwOptr = m_strRwOptr;
	pCommCmd->m_nCmdExecModeForMgbrpt = m_nCmdExecModeForMgbrpt;
	pCommCmd->m_nFillRptDataset = m_nFillRptDataset;

	CGbItemBase::CopyOwn(pDesObj);

	return TRUE;
}

CBaseObject* CCommCmd::Clone()
{
	CCommCmd* pObj = new CCommCmd();
	Copy(pObj);

	return pObj;
}

CBaseObject* CCommCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCommCmd *p = new CCommCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCommCmd::Update(CBaseObject* pDest)
{
	CCommCmd* pCommCmd = (CCommCmd*)pDest;

	pCommCmd->m_strCommCmdID = m_strCommCmdID;
	pCommCmd->m_nSortSoeByT = m_nSortSoeByT;
	pCommCmd->m_nDsvRunAfterResultScript = m_nDsvRunAfterResultScript;
	pCommCmd->m_nCmdExecModeForMgbrpt = m_nCmdExecModeForMgbrpt;
	pCommCmd->m_nFillRptDataset = m_nFillRptDataset;
	pCommCmd->m_strRwOptr = m_strRwOptr;

	pCommCmd->Delete(pCommCmd->m_pDsvScript);
	pCommCmd->Delete(pCommCmd->m_pRptDataEx);
	pCommCmd->Delete(pCommCmd->m_pCmd);
	pCommCmd->m_pDsvScript = (CDsvScript*)m_pDsvScript->Clone();
	pCommCmd->m_pRptDataEx = (CShortDatas*)m_pRptDataEx->Clone();
	pCommCmd->m_pCmd = (CCmd*)m_pCmd->Clone();
	pCommCmd->AddNewChild(pCommCmd->m_pDsvScript);
	pCommCmd->AddNewChild(pCommCmd->m_pRptDataEx);
	pCommCmd->AddNewChild(pCommCmd->m_pCmd);

	CGbItemBase::UpdateOwn(pDest);

	return TRUE;
}

void CCommCmd::InitCmd()
{
// 	CExBaseObject *pParent = (CExBaseObject*)GetParent();
// 
// 	if (pParent->GetClassID() != GBCLASSID_MACROTEST)
// 	{
// 		return;
// 	}
// 
// 	CItems *pItems = ((CMacroTest*)pParent)->GetRsltExprScriptItems();
// 
// 	if (pItems == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (!pItems->HasItemsRsltExprScript())
// 	{
// 		return;
// 	}
	
	CCmd *pCmd = GetCmd();
	CItemsRsltExprScript *pRsltExpr = GetItemsRsltExprScript();

	if (pRsltExpr == NULL)
	{
		return;
	}

	if (pRsltExpr->m_strDatasetID.GetLength() > 0)
	{
		CString strDsID = Gb_GetDataSetID(pRsltExpr->m_strDatasetID);
		CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
		CGbCommCmdMms *pMmsCmd = pGuideBook->m_oGbCommCmdConfig.FindCmd_Read(strDsID);

		if (pMmsCmd != NULL)
		{
			m_strCommCmdID = pMmsCmd->m_strID;
		}
		else
		{
			m_strCommCmdID = _T("ReadDataset");
		}

		pCmd->m_strDatasetPath = pRsltExpr->m_strDatasetID;
	}
	else
	{
		m_strCommCmdID = g_strCmdID_ReadSoe;
	}
}

CCmd* CCommCmd::GetCmd()
{
	if (m_pCmd == NULL)
	{
		m_pCmd = new CCmd;
		AddHead(m_pCmd);
		m_pCmd->SetParent(this);
	}

	return m_pCmd;
}

CShortData* CCommCmd::FindRptDataEx(const CString &bstrID)
{
	ASSERT (m_pRptDataEx != NULL);

	if (m_pRptDataEx == NULL)
	{
		return NULL;
	}

	return (CShortData*)m_pRptDataEx->FindByID(bstrID);
}

CShortData* CCommCmd::FindRptDataExDataType(const CString &bstrDataTypeID)
{
	return NULL;
}


#ifdef GUIDEBOOK_DEV_MODE

void CCommCmd::GenerateDevReports()
{
	CreateReports();
	GetCmd();
	CReport* pReport = GetCurrReport();

	if (pReport == NULL)
	{
		pReport = AddReport(-1, -1);//2017.0518
	}
	else
	{
		pReport->m_pValues->DeleteAll();
	}

	CValues* pValues = new CValues();

	Gb_AddResultJudgeKey(pValues,0);
	pReport->m_pValues->Append(pValues);
	pValues->RemoveAll();
	delete pValues;

	if (GetCmd()->m_strDatasetPath.Find(g_strDataSetIDKey[DSID_dsAin]) > 0)
	{
		GenerateRdAnalogReports(pReport->m_pValues);
	}


	AddCommCmdRptTags(pReport->m_pValues);
}

void CCommCmd::GenerateRdAnalogReports(CValues *pValues)
{
	CDataSet *pAnalogs = GetDataset(0);

	if (pAnalogs == NULL)
	{
		return;
	}

	POS pos = pAnalogs->GetHeadPosition();
	CDataObj *pAnalog = NULL;

	while (pos != NULL)
	{
		pAnalog = (CDataObj*)pAnalogs->GetNext(pos);
		pValues->AddNew(pAnalog->m_strID, pAnalog->m_strID, _T("0"));
	}
}
// 
// CAnalogs* CCommCmd::GetOwnAnalogs()
// {
// 	CDevice* pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
// 	ASSERT( pDevice != NULL);
// 
// 	if (pDevice == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CCpus* pCpus = pDevice->GetCpus();
// 	ASSERT(pCpus != NULL);
// 
// 	if (pCpus == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	GetCmd();
// 	CCpu* pCpu = (CCpu*)pCpus->FindByID(m_pCmd->m_strDatasetPath);
// 
// 	if (pCpu == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	return pCpu->GetAnalogs();
// }

#endif

BOOL CCommCmd::IsReadSoe()
{
	return (m_strCommCmdID == g_strCmdID_ReadSoe);
}

BOOL CCommCmd::IsLoadIecfg()
{
	return (m_strCommCmdID == g_strCmdID_LoadIecfg);
}

BOOL CCommCmd::IsReadLog()
{
	return (m_strCommCmdID == g_strCmdID_ReadLog);
}

BOOL CCommCmd::IsReadLogEx()
{
	return (m_strCommCmdID.Find(g_strCmdID_ReadLog) >= 0);
}

BOOL CCommCmd::IsReset()
{
	return (m_strCommCmdID == _T("Reset"));
}

BOOL CCommCmd::IsLogCmd()
{
	return (m_strCommCmdID.Find(_T("Log")) > 0);
}

BOOL CCommCmd::IsCmdExecModeForMgbrpt_MainRpt()
{
	return (m_nCmdExecModeForMgbrpt == CmdExecModeForMgbrpt_MAINRPT);
}

BOOL CCommCmd::IsCmdExecModeForMgbrpt_AllRpt()
{
	return (m_nCmdExecModeForMgbrpt == CmdExecModeForMgbrpt_ALLRPT);
}

void CCommCmd::AddCommCmdRptTags(CValues *pValues)
{
	if (m_pRptDataEx == NULL)
	{
		return;
	}

	long nIndex = 0;
	CShortData * oRptTag = NULL;
	CValue * pValue = NULL;
	POS pos = m_pRptDataEx->GetHeadPosition();

	while (pos != NULL)
	{
		oRptTag = (CShortData*)m_pRptDataEx->GetNext(pos);
		pValue = (CValue*)pValues->FindByID(oRptTag->m_strID);

		if (pValue == NULL)
		{
			pValue = pValues->AddNew(oRptTag->m_strID, oRptTag->m_strName, oRptTag->m_strValue);
		}
		else
		{
			pValue->m_strValue = oRptTag->m_strValue;
		}
	}
}

BOOL CCommCmd::IsWrite()
{	
	if (m_strRwOptr.GetLength() > 3)
	{
		return (m_strRwOptr == g_strDeviceModelOptr_Write);	
	}

	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(m_strCommCmdID);

	if (pGbCmd == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunCmdUnExist.GetString()/*_T("通讯项目【%s】对应的通讯命令【%s】不存在")*/
                                   , m_strName.GetString(), m_strCommCmdID.GetString());
		CString strTemp = m_strCommCmdID;
		strTemp.MakeLower();
		return (strTemp.Find(g_strDeviceModelOptr_Write) >= 0);
	}

	return (pGbCmd->m_strGbRwOptr == g_strDeviceModelOptr_Write);
// 	if (m_pCmd->m_nUseConnect == pGbCmd->m_nUseConnect)
// 	{
// 		return m_pCmd->m_nUseConnect;
// 	}
// 	else
// 	{
// 		return pGbCmd->m_nUseConnect;
// 	}

}

BOOL CCommCmd::IsRead()
{	
	if (m_strRwOptr.GetLength() > 3)
	{
		return (m_strRwOptr == g_strDeviceModelOptr_Read);	
	}

	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(m_strCommCmdID);

	if (pGbCmd == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunCmdUnExist.GetString()/*_T("通讯项目【%s】对应的通讯命令【%s】不存在")*/
                                   , m_strName.GetString(), m_strCommCmdID.GetString());
	
		CString strTemp = m_strCommCmdID;
		strTemp.MakeLower();
		return (strTemp.Find(g_strDeviceModelOptr_Read) >= 0);
	}

	return (pGbCmd->m_strGbRwOptr == g_strDeviceModelOptr_Read);
}

BOOL CCommCmd::IsCmdNeedDataset()
{
	CString strTemp = m_strCommCmdID;
	strTemp.MakeLower();
	
	if (strTemp == g_strReset)
	{
		return FALSE;
	}

	return (strTemp.Find(_T("soe")) < 0);
}

BOOL CCommCmd::IsUseConnect()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(m_strCommCmdID);

	if (pGbCmd == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunCmdUnExist.GetString()/*_T("通讯项目【%s】对应的通讯命令【%s】不存在")*/, m_strName.GetString(), m_strCommCmdID.GetString());
		return m_pCmd->m_nUseConnect;
	}

	if (m_pCmd->m_nUseConnect == -1)
	{
		return pGbCmd->m_nUseConnect;
	}

	if (m_pCmd->m_nUseConnect == pGbCmd->m_nUseConnect)
	{
		return m_pCmd->m_nUseConnect;
	}
	else
	{
		return pGbCmd->m_nUseConnect;
	}
}

BOOL CCommCmd::IsFirstSubItem()
{
	if (m_pParent == NULL)
	{
		return FALSE;
	}

	if (m_pParent->GetClassID() != GBCLASSID_MACROTEST)
	{
		return FALSE;
	}

	CExBaseObject *pFind = ((CExBaseList*)m_pParent)->FindByClassID(GBCLASSID_COMMCMD);
	
	return (pFind == this);
}


BOOL CCommCmd::IsBeginModeSynchro()
{
	ASSERT( m_pCmd != NULL);

	if (m_pCmd == NULL)
	{
		return FALSE;
	}

	return m_pCmd->IsBeginModeSynchro();
}

BOOL CCommCmd::IsBeginModeAsynchronous()
{
	ASSERT( m_pCmd != NULL);

	if (m_pCmd == NULL)
	{
		return FALSE;
	}

	return m_pCmd->IsBeginModeAsynchronous();
}

void CCommCmd::SetBeginModeSynchro()
{
	ASSERT( m_pCmd != NULL);

	if (m_pCmd == NULL)
	{
		return;
	}

	m_pCmd->SetBeginModeSynchro();
}

void CCommCmd::SetBeginModeAsynchronous()
{
	ASSERT( m_pCmd != NULL);

	if (m_pCmd == NULL)
	{
		return;
	}

	m_pCmd->SetBeginModeAsynchronous();
}

BOOL CCommCmd::IsCommCmdNeedWriteRptEx()
{
	CGuideBook *pGuideBook = (CGuideBook *)GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(m_strCommCmdID);

	if (pGbCmd == NULL)
	{
		return FALSE;
	}

	return pGbCmd->m_strDataType == _T("save-to-rpt-ex");
}

CCpu* CCommCmd::GetCurrCpu()
{
	CCpu *pCpu = NULL;
	CCmd *pCmd = GetCmd();
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	pCpu = (CCpu*)pDevice->m_pCpus->FindByID(pCmd->m_strDatasetPath);

	if (pCpu == NULL)
	{
		pCpu = (CCpu*)pDevice->m_pCpus->GetHead();
	}

	return pCpu;
}

CDataSet* CCommCmd::GetDataset(const CString &strDatasetPath, long nCpusIndex)
{
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);

	CExBaseList oListDataset;
	pDevice->SelectDataSetList(strDatasetPath, oListDataset, nCpusIndex);
	CDataSet *pDataset = NULL;

	if (oListDataset.GetCount() > 0)
	{
		pDataset = (CDataSet *)oListDataset.GetHead();
	}

	oListDataset.RemoveAll();

	return pDataset;
}

CDataSet* CCommCmd::GetDataset(long nCpusIndex)
{
	return GetDataset(m_pCmd->m_strDatasetPath, nCpusIndex);
// 	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
// 	ASSERT (pDevice != NULL);
// 
// 	CExBaseList oListDataset;
// 	pDevice->SelectDataSetList(m_pCmd->m_strDatasetPath, oListDataset, nCpusIndex);
// 	CDataSet *pDataset = NULL;
// 	
// 	if (oListDataset.GetCount() > 0)
// 	{
// 		pDataset = (CDataSet *)oListDataset.GetHead();
// 	}
// 
// 	oListDataset.RemoveAll();
// 
// 	return pDataset;
}

CDataSet* CCommCmd::GetDataset()
{
	long nCpusIndex = GetCpusIndex();

	if (nCpusIndex == DSID_ALL_DVM)
	{
		nCpusIndex = 0;
	}

	return GetDataset(nCpusIndex);
}

long CCommCmd::GetWriteDataObjList(CExBaseList &oList, long nCpusIndex)
{
	CDataSet *pDataset = GetDataset(nCpusIndex);

	if (pDataset == NULL)
	{
		return 0;
	}

	ASSERT (m_pCmd != NULL);
	POS pos = m_pCmd->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)m_pCmd->GetNext(pos);
		pData = (CDataObj*)pDataset->FindByID(pValue->m_strID);

		if (pData != NULL)
		{
			oList.AddTail(pData);
		}
	}

	return oList.GetCount();
}

CShortDatas* CCommCmd::GetWriteShortDatas(long nCpusIndex)
{
	CDataSet *pDataset = GetDataset(nCpusIndex);

	if (pDataset == NULL)
	{
		return 0;
	}

	CShortDatas *pShortDatas = new CShortDatas();
	ASSERT (m_pCmd != NULL);
	POS pos = m_pCmd->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;
	CShortData *pNew = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)m_pCmd->GetNext(pos);
		pData = (CDataObj*)pDataset->FindByID(pValue->m_strID);

		if (pData != NULL)
		{
			pNew = pShortDatas->AddNew();
			pData->WriteToData(pNew);
			pShortDatas->AddTail(pData);
		}
	}

	return pShortDatas;
}

//2021-10-14  lijunqing  移植到DataObj
// CString CCommCmd::CalValue_MinMax(CExBaseObject *pDevice, CValue *pVapue, double dValue)
// {
// // 	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
// 	CDataObj *pData = ((CDevice*)pDevice)->FindDataObjByID(pVapue->m_strID, -1);
// 	CString strValue;
// 
// 	if (pData != NULL)
// 	{
// 		CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
// 
// 		//2019-10-30  定义修改定值的时候，是否判断最大最小值
// 		if (pGuideBook->m_bWSetsUseMinMax)
// 		{
// 			double d = pData->m_dMinVal - pData->m_dMaxVal;
// 
// 			if (fabs(d) > 0.001)
// 			{
// 				if (dValue >= pData->m_dMaxVal)
// 				{
// 					dValue = pData->m_dMaxVal;
// 				}
// 				else if (dValue <= pData->m_dMinVal)
// 				{
// 					dValue = pData->m_dMinVal;
// 				}
// 			}
// 		}
// 		
// 		strValue.Format(_T("%f"), dValue);
// 		pData->m_strValue = strValue;
// 	}
// 	else
// 	{
// 		strValue.Format(_T("%f"), dValue);
// 	}
// 
// 	return strValue;
// }
// 
CString CCommCmd::CalValue(CValue *pValue)
{
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	return Gb_CalValue(pDevice, pValue);
// 	if (pVapue->m_strValue.GetAt(0) == '\"')
// 	{
// 		return pVapue->m_strValue;
// 	}
// 
// 	if (pVapue->m_strValue.GetLength() == 0)
// 	{
// 		return pVapue->m_strValue;
// 	}
// 
// 	double dValue = 0;
// 	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
// 
// 	if (IsStringNumber(pVapue->m_strValue))
// 	{
// #ifdef _UNICODE
// 		dValue = _wtof(pVapue->m_strValue);
// #else
// //		dValue = atof(pVapue->m_strValue);
// 		dValue = CString_To_double(pVapue->m_strValue); //yyj 20200523
// #endif
// 		//return pVapue->m_strValue;
// 	}
// 	else
// 	{
// 		CString strValue;
// 		if (!Gb_CalParaExpressionEx(pVapue->m_strValue, pDevice, dValue, TRUE, strValue))
// 		{
// 			return strValue;
// 			//dValue = 0;
// 			//return pVapue->m_strValue;
// 		}
// 	}
// 
// 	return CalValue_MinMax(pDevice, pVapue, dValue);
}

void CCommCmd::CalWriteDvmDataset(CDataSet *pDataset, long nCpusIndex)
{
	ASSERT (m_pCmd != NULL);
	POS pos = m_pCmd->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;
	CDvmData *pNew = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)m_pCmd->GetNext(pos);
		pData = (CDataObj*)pDataset->FindByID(pValue->m_strID);

		if (pData == NULL)
		{
			pData = FindDataObj(pValue->m_strID, nCpusIndex);
		}

		if (pData != NULL)
		{
			pData->m_strValue = CalValue(pValue);//pValue->m_strValue;
		}
	}

	//执行通讯命令初始化脚本
	CString strSytexError;
	RunInitScriptScript(strSytexError);
}

void CCommCmd::WriteDataToDvm(CDataSet *pDataSet, CDvmDataset *pDvmDataset, long nCpusIndex)
{
	POS pos = NULL;
	CDataObj *pData = NULL;
	CDvmData *pNew = NULL;
	ASSERT (m_pCmd != NULL);
	pos = m_pCmd->GetHeadPosition();
	CValue *pValue = NULL;

	BOOL bIsEmptyDataset = m_pCmd->IsEmptyDataset();

	while (pos != NULL)
	{
		pValue = (CValue *)m_pCmd->GetNext(pos);
		pData = (CDataObj*)pDataSet->FindByID(pValue->m_strID);

		if (pData == NULL)
		{
			pData = FindDataObj(pValue->m_strID, nCpusIndex);
		}

		if (pData != NULL)
		{
			pNew = new CDvmData();
			pData->WriteToData(pNew);

			if (bIsEmptyDataset)
			{
				pNew->m_strValue = pValue->m_strValue;
			}
			else
			{
				pNew->m_strValue = CalValue(pValue);
			}

			pData->m_strValue = pNew->m_strValue; // 保存计算的数据
			pDvmDataset->AddTail(pNew);
		}
	}
}

/*   CDvmDatasetGroup:
<dataset-group name="边设备管理参数" id="DeviceSysPara" data-type="" write-mode="0" index="8">
	<data name="设备名称" id="devName" unit="" value="" data-type="string"/>
	<data name="CPU监控阈值" id="cpuLmt" unit="" value="" data-type="number"/>
	<data name="内存监控阈值" id="memLmt" unit="" value="" data-type="number"/>
	<data name="磁盘监控阈值" id="diskLmt" unit="" value="" data-type="number"/>
	<data name="温度监控信息" id="temperature" unit="" value="" data-type="STRUCT">
		<value name="主板温度监控低温阈值" id="temLow" unit="" value="" data-type="number"/>
		<value name="主板温度监控高温阈值" id="temHigh" unit="" value="" data-type="number"/>
	</data>
	<data name="状态主动上报时间间隔" id="repPeriod" unit="" value="" data-type="STRUCT">
		<value name="终端状态主动上报时间间隔" id="devPeriod" unit="" value="" data-type="number"/>
		<value name="容器状态主动上报时间间隔" id="conPeriod" unit="" value="" data-type="number"/>
		<value name="APP状态主动上报时间间隔" id="appPeriod" unit="" value="" data-type="number"/>
		<value name="心跳主动上报的时间间隔" id="heartPeriod" unit="" value="" data-type="number"/>
	</data>
</dataset-group>

m_pCmd的结构如下：
<cmd name="" id="" dataset-path="DeviceData$DeviceSysPara" delaybeforecmd="0" delayaftercmd="0" delaybefortry="0" maxretrytimes="0" retrytimes="0" rpt-fill-no-repeat="0" cal-mode="none" timelong="" timegap="" usecurrsetdata="1" usedeviceex="255" begin-mode="synchro" use-connect="1" zone-index="0">
	<value id="devName" value="&quot;鼓楼-省信通公司-融合终端2&quot;"/>
	<value id="cpuLmt" value="95"/>
	<value id="memLmt" value="95"/>
	<value id="diskLmt" value="95"/>
	<value id="temperature" value=""/>
	<value id="temperature$temLow" value="-10"/>
	<value id="temperature$temHigh" value="140"/>
	<value id="repPeriod" value=""/>
	<value id="repPeriod$devPeriod" value="800"/>   【对应模型中，Data下的Value】
	<value id="repPeriod$conPeriod" value="800"/>
	<value id="repPeriod$appPeriod" value="800"/>
	<value id="repPeriod$heartPeriod" value="3000"/>
</cmd>
*/
void CCommCmd::WriteDataToDvmGrp(CDataSetGroup *pDataSetGrp, CDvmDatasetGroup *pDvmDatasetGrp, long nCpusIndex)
{
	POS pos = NULL;
	CDataObj *pData = NULL;
	CDataObjValue *pDataValue = NULL;
	CDvmData *pNew = NULL;
	CDvmDatasetGroup *pNewGrp = NULL;
	ASSERT (m_pCmd != NULL);
	pos = m_pCmd->GetHeadPosition();
	CValue *pValue = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmValue *pNewValue = NULL;
	CDataSetGroup *pSrcGrp = NULL;

	BOOL bIsEmptyDataset = m_pCmd->IsEmptyDataset();

	while (pos != NULL)
	{
		pValue = (CValue *)m_pCmd->GetNext(pos);
		long nPos = pValue->m_strID.Find(_T("$"));
		pSrcGrp = pDataSetGrp;

		if (nPos > 0)
		{
			CString strLeft, strRight;
			strRight = pValue->m_strID;

			while (nPos > 0)
			{
				strLeft = strRight.Left(nPos);
				strRight = strRight.Mid(nPos + 1);
				pObj = pSrcGrp->FindByID(strLeft);
				nClassID = pObj->GetClassID();

				if (nClassID == GBCLASSID_DATASETGROUP)
				{
					CDataSetGroup *pDsGrp = (CDataSetGroup *)pObj;
					pNewGrp = (CDvmDatasetGroup *)pDvmDatasetGrp->FindByID(pDsGrp->m_strID);

					if (pNewGrp == NULL)
					{
						pNewGrp = new CDvmDatasetGroup();
						pDvmDatasetGrp->AddNewChild(pNewGrp);
					}
					
					pNewGrp->m_strID = pDsGrp->m_strID;
					pNewGrp->m_strName = pDsGrp->m_strName;

					WriteDataToDvmGrp(pDsGrp, pNewGrp, strRight, pValue, nCpusIndex);
					pSrcGrp = pDsGrp;
				}
				else if (nClassID == GBCLASSID_DATAOBJ)
				{
					pData = (CDataObj *)pObj;
					pNew = (CDvmData *)pDvmDatasetGrp->FindByID(pData->m_strID);

					if (pNew == NULL)
					{
						pNew = new CDvmData();
						pDvmDatasetGrp->AddNewChild(pNew);
					}
					
					pNew->m_strID = pData->m_strID;
					pNew->m_strName = pData->m_strName;
					pNew->m_strValue = pValue->m_strValue;
					pNew->m_strDataType = pData->m_strDataType;

					WriteDataToDvmGrp(pData, pNew, strRight, pValue, nCpusIndex);
				}

				nPos = strRight.Find(_T("$"));
			}
		}
		else
		{
			pObj = pDataSetGrp->FindByID(pValue->m_strID);

			if (pObj != NULL)
			{
				nClassID = pObj->GetClassID();

				if (nClassID == GBCLASSID_DATAOBJ)
				{
					pData = (CDataObj *)pObj;
					pNew = new CDvmData();
					pDvmDatasetGrp->AddNewChild(pNew);
					pData->WriteToData(pNew);

					if (bIsEmptyDataset)
					{
						pNew->m_strValue = pValue->m_strValue;
					}
					else
					{
						pNew->m_strValue = CalValue(pValue);
					}

					pData->m_strValue = pNew->m_strValue; // 保存计算的数据
				}
				else if (nClassID == GBCLASSID_DATASETGROUP)
				{
					CDataSetGroup *pDsGrp = (CDataSetGroup *)pObj;
					pNewGrp = new CDvmDatasetGroup();
					pDvmDatasetGrp->AddNewChild(pNewGrp);
					pNewGrp->m_strID = pDsGrp->m_strID;
					pNewGrp->m_strName = pDsGrp->m_strName;
				}
			}
		}
	}
}

void CCommCmd::WriteDataToDvmGrp(CDataSetGroup *pDataSetGrp, CDvmDatasetGroup *pDvmDatasetGrp, const CString &strDataPath, CValue *pValue, long nCpusIndex)
{
	CDataObj *pData = NULL;
	CDataObjValue *pDataValue = NULL;
	CDvmData *pNew = NULL;
	CDvmDatasetGroup *pNewGrp = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDvmValue *pNewValue = NULL;
	BOOL bIsEmptyDataset = m_pCmd->IsEmptyDataset();
	CDataSetGroup *pSrcGrp = pDataSetGrp;

	long nPos = strDataPath.Find(_T("$"));

	if (nPos > 0)
	{
		CString strLeft, strRight;
		strRight = strDataPath;

		while (nPos > 0)
		{
			strLeft = strRight.Left(nPos);
			strRight = strRight.Mid(nPos + 1);
			pObj = pSrcGrp->FindByID(strLeft);
			nClassID = pObj->GetClassID();

			if (nClassID == GBCLASSID_DATASETGROUP)
			{
				CDataSetGroup *pDsGrp = (CDataSetGroup *)pObj;
				pNewGrp = (CDvmDatasetGroup *)pDvmDatasetGrp->FindByID(pDsGrp->m_strID);

				if (pNewGrp == NULL)
				{
					pNewGrp = new CDvmDatasetGroup();
					pDvmDatasetGrp->AddNewChild(pNewGrp);
				}

				pNewGrp->m_strID = pDsGrp->m_strID;
				pNewGrp->m_strName = pDsGrp->m_strName;

				WriteDataToDvmGrp(pDsGrp, pNewGrp, strRight, pValue, nCpusIndex);
				pSrcGrp = pDsGrp;
			}
			else if (nClassID == GBCLASSID_DATAOBJ)
			{
				pData = (CDataObj *)pObj;
				pNew = (CDvmData *)pDvmDatasetGrp->FindByID(pData->m_strID);

				if (pNew == NULL)
				{
					pNew = new CDvmData();
					pDvmDatasetGrp->AddNewChild(pNew);
				}

				pNew->m_strID = pData->m_strID;
				pNew->m_strName = pData->m_strName;
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pData->m_strDataType;

				WriteDataToDvmGrp(pData, pNew, strRight, pValue, nCpusIndex);
			}

			nPos = strRight.Find(_T("$"));
		}
	}
	else
	{
		pObj = pDataSetGrp->FindByID(strDataPath);

		if (pObj != NULL)
		{
			nClassID = pObj->GetClassID();

			if (nClassID == GBCLASSID_DATASETGROUP)
			{
				CDataSetGroup *pDsGrp = (CDataSetGroup *)pObj;
				pNewGrp = new CDvmDatasetGroup();
				pDvmDatasetGrp->AddNewChild(pNewGrp);
				pNewGrp->m_strID = pDsGrp->m_strID;
				pNewGrp->m_strName = pDsGrp->m_strName;
			}
			else if (nClassID == GBCLASSID_DATAOBJ)
			{
				pData = (CDataObj *)pObj;
				pNew = new CDvmData();
				pDvmDatasetGrp->AddNewChild(pNew);
				pData->WriteToData(pNew);

				if (bIsEmptyDataset)
				{
					pNew->m_strValue = pValue->m_strValue;
				}
				else
				{
					pNew->m_strValue = CalValue(pValue);
				}

				pData->m_strValue = pNew->m_strValue; // 保存计算的数据
			}
		}	
	}
}

void CCommCmd::WriteDataToDvmGrp(CDataObj *pDataObj, CDvmData *pDvmData, const CString &strDataPath, CValue *pValue, long nCpusIndex)
{
	CDvmValue *pNew = NULL;
	CDataObjValue *pDataValue = NULL;
	long nPos = strDataPath.Find(_T("$"));
	BOOL bIsEmptyDataset = m_pCmd->IsEmptyDataset();
	CDataObj *pSrcDataObj = pDataObj;

	if (nPos > 0)
	{
		CString strLeft, strRight;
		strRight = strDataPath;

		while (nPos > 0)
		{
			strLeft = strRight.Left(nPos);
			strRight = strRight.Mid(nPos + 1);
			pDataValue = (CDataObjValue *)pSrcDataObj->FindByID(strLeft);

			if (pDataValue != NULL)
			{
				pNew = (CDvmValue *)pDvmData->FindByID(strDataPath);

				if (pNew == NULL)
				{
					pNew = new CDvmValue();	
					pDvmData->AddNewChild(pNew);
				}

				pNew->m_strID = strDataPath;
				pNew->m_strName = pDataValue->m_strName;
				pNew->m_strDataType = pDataValue->m_strDataTypeID;
				pNew->m_strValue = pValue->m_strValue;
				WriteDataToDvmGrp(pDataValue, pNew, strRight, pValue, nCpusIndex);

				if (!bIsEmptyDataset)
				{
					pNew->m_strValue = CalValue(pValue);
				}

				pDataValue->m_strValue = pNew->m_strValue; // 保存计算的数据
			}

			nPos = strRight.Find(_T("$"));
		}
	}
	else
	{
		pDataValue = (CDataObjValue *)pDataObj->FindByID(strDataPath);

		if (pDataValue != NULL)
		{
			pNew = new CDvmValue();
			pNew->m_strID = strDataPath;
			pNew->m_strName = pDataValue->m_strName;
			pNew->m_strDataType = pDataValue->m_strDataTypeID;
			pNew->m_strValue = pValue->m_strValue;
			pDvmData->AddNewChild(pNew);

			if (!bIsEmptyDataset)
			{
				pNew->m_strValue = CalValue(pValue);
			}

			pDataValue->m_strValue = pNew->m_strValue; // 保存计算的数据
		}
	}
}

void CCommCmd::WriteDataToDvmGrp(CDataObjValue *pDataObjValue, CDvmValue *pDvmValue, const CString &strDataPath, CValue *pValue, long nCpusIndex)
{
	CDvmValue *pNew = NULL;
	CDataObjValue *pDataValue = NULL;
	long nPos = strDataPath.Find(_T("$"));
	BOOL bIsEmptyDataset = m_pCmd->IsEmptyDataset();

	if (nPos > 0)
	{
		CString strLeft, strRight;
		strRight = strDataPath;

		while (nPos > 0)
		{
			strLeft = strRight.Left(nPos);
			strRight = strRight.Mid(nPos + 1);
			pDataValue = (CDataObjValue *)pDataObjValue->FindByID(strLeft);

			if (pDataValue != NULL)
			{
				pNew = (CDvmValue *)pDvmValue->FindByID(strDataPath);

				if (pNew == NULL)
				{
					pNew = new CDvmValue();	
					pDvmValue->AddNewChild(pNew);
				}

				pNew->m_strID = strDataPath;
				pNew->m_strName = pDataValue->m_strName;
				pNew->m_strDataType = pDataValue->m_strDataTypeID;
				pNew->m_strValue = pValue->m_strValue;

				if (!bIsEmptyDataset)
				{
					pNew->m_strValue = CalValue(pValue);
				}

				pDataValue->m_strValue = pNew->m_strValue; // 保存计算的数据

				WriteDataToDvmGrp(pDataValue, pNew, strRight, pValue, nCpusIndex);
			}

			nPos = strRight.Find(_T("$"));
		}
	}
	else
	{
		pDataValue = (CDataObjValue *)pDataObjValue->FindByID(strDataPath);

		if (pDataValue != NULL)
		{
			pNew = new CDvmValue();
			pNew->m_strID = strDataPath;
			pNew->m_strName = pDataValue->m_strName;
			pNew->m_strDataType = pDataValue->m_strDataTypeID;
			pNew->m_strValue = pValue->m_strValue;
			pDvmValue->AddNewChild(pNew);

			if (!bIsEmptyDataset)
			{
				pNew->m_strValue = CalValue(pValue);
			}

			pDataValue->m_strValue = pNew->m_strValue; // 保存计算的数据
		}
	}
}

CDvmDataset* CCommCmd::GetWriteDvmDataset(long nCpusIndex, CString *pStringPath)
{
	CDataSet *pDataset = GetDataset(nCpusIndex);

	if (pDataset == NULL)
	{
		return 0;
	}

	if (pStringPath != NULL)
	{
		CExBaseObject *pCpu = (CExBaseObject*)pDataset->GetParent();
        pStringPath->Format(_T("%s$%s"), pCpu->m_strID.GetString(), pDataset->m_strID.GetString());
	}

	//2021-10-14  lijunqing
	//return pDataset->GetWriteDvmDataset(m_pCmd);

	CDvmDataset *pDvmDataset = NULL;
	UINT nClassID = pDataset->GetClassID();

	if (nClassID == GBCLASSID_DATASET)
	{
		pDvmDataset = new CDvmDataset();
	}
	else
	{
		pDvmDataset = new CDvmDatasetGroup();
	}

	//2021-06-18  lijunqing 不使用当前设置数据 = 使用数据集数据
	if (m_pCmd->m_nUseCurrSetData == 0)
	{		
		if (nClassID == GBCLASSID_DATASET)
		{
			pDataset->Data_Gb_to_Dvm(pDvmDataset);
		}
		else
		{
			CDataSetGroup *pDatasetGrp = (CDataSetGroup *)pDataset;
			pDatasetGrp->Data_Gb_to_Dvm(pDvmDataset);
		}

		return pDvmDataset;

// 		pos = pDataset->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			pData = (CDataObj *)pDataset->GetNext(pos);
// 			pNew = new CDvmData();
// 			pData->WriteToData(pNew);
// 			pDvmDataset->AddNewChild(pNew);
// 		}
// 
// 		return pDvmDataset;
	}


	if (nClassID == GBCLASSID_DATASET)
	{
		//兼容之前的
		WriteDataToDvm(pDataset, pDvmDataset, nCpusIndex);
	}
	else
	{
		CDvmDatasetGroup *pDvmDatasetGrp = (CDvmDatasetGroup *)pDvmDataset;
		CDataSetGroup *pDataSetGrp = (CDataSetGroup *)pDataset;
		WriteDataToDvmGrp(pDataSetGrp, pDvmDatasetGrp, nCpusIndex);
	}

	return pDvmDataset;

}

//2021-10-14  lijunqing
CDvmDataset* CCommCmd::GetNewDvmDataset(long nCpusIndex)
{
	CDataSet *pDataset = GetDataset(nCpusIndex);

	if (pDataset == NULL)
	{
		return new CDvmDataset();
	}

	if (pDataset->GetClassID() == GBCLASSID_DATASET)
	{
		return new CDvmDataset();
	}
	else
	{
		return new CDvmDatasetGroup();
	}
}

BOOL cmd_IsDataSet(const CString &strPath, const CString &strIDKey)
{
	return (strPath.Right(strIDKey.GetLength()) == strIDKey);
}

BOOL CCommCmd::IsCmdRptDataset()
{
	ASSERT (m_pCmd != NULL);

	if (m_pCmd->m_strDatasetPath.GetLength() == 0)
	{
		m_pCmd->m_strDatasetPath = g_strDataSetIDKey[DSID_dsReport];//_T("report");
	}

	CString strTemp = m_pCmd->m_strDatasetPath;
	strTemp.MakeLower();

	if (strTemp.Find(g_strDataSetIDKey[DSID_dsReport]/*_T("report")*/) >= 0)
	{
		return TRUE;
	}

	if (cmd_IsDataSet(strTemp, g_strDataSetIDKey[DSID_dsAin]))
	{
		return TRUE;
	}

	if (cmd_IsDataSet(strTemp, g_strDataSetIDKey[DSID_dsTripInfo]))
	{
		return TRUE;
	}


	if (cmd_IsDataSet(strTemp, g_strDataSetIDKey[DSID_dsSoe]))
	{
		return TRUE;
	}

	if (cmd_IsDataSet(strTemp, g_strDataSetIDKey[DSID_dsFile]))
	{
		return TRUE;
	}

	return FALSE;
}

CDataObj* CCommCmd::FindDataObj(const CString &strPath, long nCpusIndex)
{
	CDataSet *pDataset = GetDataset(nCpusIndex);

	if (pDataset == NULL)
	{
		return NULL;
	}

	CString strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPU, TRUE);
	long nLen = strDatasetPath.GetLength();
	CString strTemp = strPath.Left(nLen);

	if (strTemp == strDatasetPath)
	{
		strTemp = strPath.Mid(nLen+1);
		CDataObj *pFind = (CDataObj*)pDataset->FindByID(strTemp);
		return pFind;
	}
	else
	{
		return NULL;
	}
}

long CCommCmd::GetCpusIndex()
{
	return m_pCmd->m_nUseDeviceEx;
}

long CCommCmd::GetCpusIndexEx()
{
	if (m_pCmd->m_nUseDeviceEx == DSID_ALL_DVM)
	{
		return 0;
	}
	else
	{
		return m_pCmd->m_nUseDeviceEx;
	}
}

CString CCommCmd::FindDataObjValue_Name(const CString &strPath, long nCpusIndex)
{
	CString strName;
	CDataSet *pDataset = GetDataset(nCpusIndex);
	CDataObj *pDataObj = NULL;
	CDataObjValue *pDataObjValue = NULL;

	if (pDataset == NULL)
	{
		return strName;
	}

	CString strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPU, TRUE);
	long nLen = strDatasetPath.GetLength();
	CString strTemp = strPath.Left(nLen);

	if (strTemp == strDatasetPath)
	{
		strTemp = strPath.Mid(nLen+1);
		CDataObj *pFind = (CDataObj*)pDataset->FindByID(strTemp);
		return pFind->m_strName;
	}
	else
	{
		strName = pDataset->FindDataObjValue_Name(strPath);
	}

	return strName;
}

CDsvScript* CCommCmd::GetDsvScript()
{
	if (m_pDsvScript == NULL)
	{
		m_pDsvScript = new CDsvScript();
		AddNewChild(m_pDsvScript);
	}

	return m_pDsvScript;
}

BOOL CCommCmd::HasDsvScript()
{
	if (m_pDsvScript == NULL)
	{
		return FALSE;
	}

	return (m_pDsvScript->GetCount() > 0);
}

CItemsRsltExprScript* CCommCmd::GetItemsRsltExprScript()
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();

	if (pParent->GetClassID() != GBCLASSID_MACROTEST)
	{
		return NULL;
	}

	CMacroTest *pMacroTest = (CMacroTest*)pParent;

	//子项目只允许一个
	if (pMacroTest->m_oSubGbItems.GetCount() > 1)
	{
		return NULL;
	}

	CItems *pItems = pMacroTest->GetRsltExprScriptItems();

	if (pItems == NULL)
	{
		return NULL;
	}

	CItemsRsltExprScript *pRsltExpr = pItems->GetItemsRsltExprScript(FALSE);
	ASSERT (pRsltExpr != NULL);

	if (pRsltExpr->m_nIsRef == 0)
	{
		//如果测试功能不一致，则返回为空
		if (pRsltExpr->m_strTestMacroID != pMacroTest->GetTestMacroID())
		{
			return NULL;
		}
		else
		{
			return pRsltExpr;
		}
	}
	else
	{
		return pRsltExpr;
// 		CItemsRsltExprScriptMngr* pExprScriptMngr = Gb_GetExprScriptMngr(this);
// 		CItemsRsltExprScript *pFind = (CItemsRsltExprScript*)pExprScriptMngr->FindByID(pRsltExpr->m_strID);
// 
// 		if (pFind != NULL)
// 		{
// 			return pRsltExpr;
// 		}
// 		else
// 		{
// 			return pRsltExpr;
// 		}
	}
}

void CCommCmd::ReplaceDsvScript(CDsvScript *pSrcDsvScript)
{
	if (m_pDsvScript == pSrcDsvScript)
	{
		return;
	}

	if (m_pDsvScript != NULL)
	{
		Delete(m_pDsvScript);
	}

	m_pDsvScript = (CDsvScript *)pSrcDsvScript->Clone();
	AddNewChild(m_pDsvScript);
}

BOOL CCommCmd::RunDsvScript(CDvmDataset **ppRptDvmDataset, CReport *pReport, BOOL bSetRsltJdg)
{
	if (pReport == NULL)
	{
		return FALSE;
	}

	if (m_pDsvScript == NULL)
	{
		return FALSE;
	}

	if (m_pDsvScript->GetCount() == 0)
	{
		return FALSE;
	}

	CDataSet *pDataset = NULL;
	m_pDsvScript->EmptyRefDatasets();

	if (m_pDsvScript->m_strInDataset.GetLength() > 0)
	{
		pDataset = GetDataset(m_pDsvScript->m_strInDataset, 0);
	}

	if (pDataset != NULL)
	{
		m_pDsvScript->SetRefDataset(pDataset);
	}

	*ppRptDvmDataset = pReport->m_pRptDvmDataset;
	m_pDsvScript->DsValidate(*ppRptDvmDataset, pReport->m_pValues, FALSE);

	if (!bSetRsltJdg)
	{
		return TRUE;
	}

	if (m_pDsvScript->m_bDsvSucc)
	{
		SetRsltJdg(1);
	}
	else
	{
		SetRsltJdg(0);
	}	

	InitDsvRpt_All(pReport->m_pValues);
	InitDsvRpt_All_Trip(pReport->m_pValues);
	InitDsvRpt_All_More(pReport->m_pValues);
	InitDsvRpt_All_Miss(pReport->m_pValues);
	InitDsvRpt_All_AppearForErr(pReport->m_pValues);
	InitDsvRpt_Std(pReport->m_pValues);

	return TRUE;
}

void CCommCmd::InitParas_NameAndVal(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strParas_Name_Val);

	if (pSoeRpt == NULL)
	{
		return;
	}

	long nCpusIndex = GetCpusIndexEx();
	CDvmDataset *pDvmDataset = GetWriteDvmDataset(nCpusIndex);

	if(pDvmDataset == NULL)
	{
		return;
	}

	pSoeRpt->m_strValue.Empty();

	POS pos = pDvmDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CString strValue;

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pDvmDataset->GetNext(pos);
		strValue = pDvmData->m_strValue;
		ChopFloatString(strValue,-1);
        pSoeRpt->m_strValue.AppendFormat(_T("%s(%s)\r\n"), pDvmData->m_strName.GetString(), strValue.GetString());
	}

	pSoeRpt->m_strValue.TrimRight();

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CommunCmdTimes.GetString()/*_T("通讯命令参数：%s")*/, pSoeRpt->m_strValue.GetString());
}

void CCommCmd::InitDsvRpt_All(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_All);

	if (pSoeRpt != NULL)
	{
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_All(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  g_sLangTxt_AllRecord.GetString()/*_T("全部报文：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

void CCommCmd::InitDsvRpt_Std(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_Std);

	if (pSoeRpt != NULL)
	{
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_Std(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_StandardRecord.GetString()/*_T("标准报文：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

CDvmValue* CCommCmd::FindDvmValue(CExBaseList *pList, const CString &strID)
{
	CDvmData *pData = NULL;
	POS pos = pList->GetHeadPosition();
	CDvmValue *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pList->GetNext(pos);

		pFind = (CDvmValue *)pData->FindByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDvmValue* CCommCmd::FindDvmValue(CExBaseList *pList, const CString &strID, const CString &strValue)
{
	if (strValue.GetLength() == 0)
	{
		return FindDvmValue(pList, strID);
	}

	CDvmData *pData = NULL;
	POS pos = pList->GetHeadPosition();
	CDvmValue *pFind = NULL, *p=NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pList->GetNext(pos);

		p = (CDvmValue *)pData->FindByID(strID);

		if (p != NULL)
		{
			if (p->m_strValue == strValue)
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

CDvmData* CCommCmd::FindDvmData(CExBaseList *pList, const CString &strID, const CString &strValue)
{
	CDvmData *pData = NULL;
	POS pos = pList->GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pList->GetNext(pos);

		if (pData->m_strID == strID && pData->m_strValue == strValue)
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}

CDvmData* CCommCmd::FindDvmDataByName(CExBaseList *pList, const CString &strName, const CString &strValue)
{
	CDvmData *pData = NULL;
	POS pos = pList->GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pList->GetNext(pos);

		if (pData->m_strName == strName && pData->m_strValue == strValue)
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}

CDvmValue* CCommCmd::FindRptValue(const CString &strID, const CString &strValue)
{
	CDvmValue *pDvmValue = NULL;
	CDvmValue *p = NULL;

	CExBaseList *pListDatas = &m_pDsvScript->m_dsDsvAll;

	POS pos = pListDatas->GetHeadPosition();
	long nLenID = strID.GetLength();
	long nLenTemp = 0;
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *) pListDatas->GetNext(pos);
		POS posValue = pData->GetHeadPosition();

		if (strID != pData->m_strID)
		{
			if (strID.Find(pData->m_strID) < 0)
			{
				continue;
			}
		}
		
		if (strValue.GetLength() > 0)
		{
			if (pData->m_strValue != strValue)
			{
				continue;
			}
		}

		while (posValue != NULL)
		{
			p = (CDvmValue *)pData->GetNext(posValue);
			nLenTemp = p->m_strID.GetLength();

			if (nLenID < nLenTemp)
			{
				continue;
			}

			if (nLenID == nLenTemp)
			{
				if (strID == p->m_strID)
				{
					pDvmValue = p;
					break;
				}
			}
			else if (strID.Right(p->m_strID.GetLength()) == p->m_strID)
			{
				if (strID.GetAt(nLenID - nLenTemp-1) == '$')
				{
					pDvmValue = p;
					break;
				}
			}
		}

		if (pDvmValue != NULL)
		{
			break;
		}
	}

	if (pDvmValue == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoRecord.GetString()/*_T("检索结果中没有报文【%s】=【%s】")*/
                                   , strID.GetString(), strValue.GetString());
	}

	return pDvmValue;
}

void CCommCmd::CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	CString strRptID, strSoeID1, strSoeID2;
	strRptID = pszRptID;
	strSoeID1 = pszSoeID1;
	strSoeID2 = pszSoeID2;

	if (strSoeID1.Right(2) != CAL_SOETIME_VALUE_FLAG)
	{
		strSoeID1 += CAL_SOETIME_VALUE_FLAG;
	}

	if (strSoeID2.Right(2) != CAL_SOETIME_VALUE_FLAG)
	{
		strSoeID2 += CAL_SOETIME_VALUE_FLAG;
	}

	CDvmValue *pData1 = NULL;
	CDvmValue *pData2 = NULL;
	CValue *pSoeRpt = (CValue*)pReport->m_pValues->FindByID(strRptID);

	if (pSoeRpt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoDefin.GetString()/*_T("没有定义【%s】")*/
                                   , strRptID.GetString());
		return;
	}

	pData1 = FindRptValue(strSoeID1);

	if (pData1 == NULL)
	{
		return;
	}

	pData2 = FindRptValue(strSoeID2);

	if (pData2 == NULL)
	{
		return;
	}

	CGpsPcTime tm1, tm2;

	tm1.FromStringEx(pData1->m_strValue);
	tm2.FromStringEx(pData2->m_strValue);

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	long nMs = ts.GetTotalMilliseconds();
	pSoeRpt->m_strValue.Format(_T("%d"), nMs);

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_RecordTimes.GetString()/*_T("报文【%s】【%s】时间差【%s】-【%s】=%d ms")*/
        , strSoeID1.GetString(), strSoeID2.GetString(), pData1->m_strValue.GetString(), pData2->m_strValue.GetString(), nMs);
}

void CCommCmd::CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	CString strRptID, strSoeID1, strSoeID2, strValue1, strValue2;
	strRptID = pszRptID;
	strSoeID1 = pszSoeID1;
	strSoeID2 = pszSoeID2;
	strValue1 = pszVal1;
	strValue2 = pszVal2;

	if (strSoeID1.Right(2) != CAL_SOETIME_VALUE_FLAG)
	{
		strSoeID1 += CAL_SOETIME_VALUE_FLAG;
	}

	if (strSoeID2.Right(2) != CAL_SOETIME_VALUE_FLAG)
	{
		strSoeID2 += CAL_SOETIME_VALUE_FLAG;
	}

	CDvmValue *pData1 = NULL;
	CDvmValue *pData2 = NULL;
	CValue *pSoeRpt = (CValue*)pReport->m_pValues->FindByID(strRptID);

	if (pSoeRpt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoDefin.GetString()/*_T("没有定义【%s】")*/, strRptID.GetString());
		return;
	}

	pData1 = FindRptValue(strSoeID1, strValue1);

	if (pData1 == NULL)
	{
		return;
	}

	pData2 = FindRptValue(strSoeID2, strValue2);

	if (pData2 == NULL)
	{
		return;
	}

	CGpsPcTime tm1, tm2;

	tm1.FromStringEx(pData1->m_strValue);
	tm2.FromStringEx(pData2->m_strValue);

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	long nMs = ts.GetTotalMilliseconds();
	pSoeRpt->m_strValue.Format(_T("%d"), nMs);

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_TimeDiff.GetString()/*_T("CalSoeTimeEx：【%s，%s】【%s，%s】时间差【%s】-【%s】=%d ms")*/
        , strSoeID1.GetString(),strValue1.GetString(), strSoeID2.GetString(), strValue2.GetString(), pData1->m_strValue.GetString(), pData2->m_strValue.GetString(), nMs);
}

void CCommCmd::SetSoeTripDesc(const char *pszRptID, const char *pszSoeID)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	CString strRptID, strSoeID;
	strRptID = pszRptID;
	strSoeID = pszSoeID;

	CValue *pSoeRpt = (CValue*)pReport->m_pValues->FindByID(strRptID);

	if (pSoeRpt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoDefin.GetString()/*_T("没有定义【%s】")*/, strRptID.GetString());
		return;
	}

	CDvmData *pData = FindDvmData(pReport->m_pRptDvmDataset, strSoeID, _T("1"));

	//找不到，再通过Name找一遍,shaolei 2019.06.17
	if (pData == NULL)
	{
		pData = FindDvmDataByName(pReport->m_pRptDvmDataset, strSoeID, _T("1"));
	}

	if (pData != NULL)
	{
		pSoeRpt->m_strValue = /*g_pszTripTimeDesc_Trip*/g_sLangTxt_Act;
	}
	else
	{
		pSoeRpt->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
	}
}

long CCommCmd::CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return 0;
	}

	CExBaseList oList;
	CString strID;
	strID = pszDsPathID;
	m_pDsvScript->m_listDsvMatch.QueryByID(strID, oList);

	if (oList.GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_RecordResult.GetString()/*_T("报文验证的结果中没有【%s】")*/, strID.GetString());
		return 0;
	}

	CValue *pAbsError = NULL;
	CValue *pRelError = NULL;
	CValue *pRptValue = NULL;
	
	if (*pszRptID != 0)
	{
		strID = pszRptID;
		pRptValue = (CValue *)pReport->m_pValues->FindByID(strID);
	}

	if (*pszAbsErrID != 0)
	{
		strID = pszAbsErrID;
		pAbsError = (CValue*)pReport->m_pValues->FindByID(strID);
	}

	if (*pszRelErrID != 0)
	{
		strID = pszRelErrID;
		pRelError = (CValue*)pReport->m_pValues->FindByID(strID);
	}

	CExBaseObject *pFind = oList.GetHead();
	double dValue = 0;

	if (pFind->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		dValue = CString_To_double(((CDvmData*)pFind)->m_strValue);
	}
	else if (pFind->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		dValue = CString_To_double(((CDvmValue*)pFind)->m_strValue);
	}
	else
	{
		pFind = NULL;
	}

	oList.RemoveAll();

	if (pFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_RecordResult.GetString()/*_T("报文验证的结果中没有【%s】")*/, pszRptID);
		return 0;
	}

	dValue = dValue * dRate;
	double dAbsCal, dRelCal;
	math_CalError(dValue, dStandVal, dAbsCal, dRelCal, FALSE);

	if (pszRptID != NULL)
	{
		pRptValue->m_strValue.Format(_T("%f"), dValue);
	}

	if (pAbsError != NULL)
	{
		pAbsError->m_strValue.Format(_T("%f"), dAbsCal);
	}

	if (pRelError != NULL)
	{
		pRelError->m_strValue.Format(_T("%f"), dRelCal);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f")
		, dValue, dStandVal, dAbsCal, dRelCal, dAbsErr, dRelErr);

	return math_CalIsInError(dAbsCal, dRelCal, dAbsErr, dRelErr);
}

long CCommCmd::CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID
							, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return 0;
	}

	CExBaseList oList;
	CString strID;
	strID = pszDsPathID;
	m_pDsvScript->m_listDsvMatch.QueryByID(strID, oList);

	if (oList.GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_RecordResult.GetString()/*_T("报文验证的结果中没有【%s】")*/, strID.GetString());
		return 0;
	}

	CValue *pAbsError = NULL;
	CValue *pRelError = NULL;
	CValue *pRptValue = NULL;

	if (*pszRptID != 0)
	{
		strID = pszRptID;
		pRptValue = (CValue *)pReport->m_pValues->FindByID(strID);
	}

	if (*pszAbsErrID != 0)
	{
		strID = pszAbsErrID;
		pAbsError = (CValue*)pReport->m_pValues->FindByID(strID);
	}

	if (*pszRelErrID != 0)
	{
		strID = pszRelErrID;
		pRelError = (CValue*)pReport->m_pValues->FindByID(strID);
	}

	CExBaseObject *pFind = oList.GetHead();
	double dValue = 0;

	if (pFind->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		dValue = CString_To_double(((CDvmData*)pFind)->m_strValue);
	}
	else if (pFind->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		dValue = CString_To_double(((CDvmValue*)pFind)->m_strValue);
	}
	else
	{
		pFind = NULL;
	}

	oList.RemoveAll();

	if (pFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_RecordResult.GetString()/*_T("报文验证的结果中没有【%s】")*/, pszRptID);
		return 0;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("dValue=%f uRate=%f"), dValue, dRate);
	dValue = dValue * dRate;
	double dAbsCal, dRelCal;
	math_CalError(dValue, dStandVal, dErrRefStandVal, dAbsCal, dRelCal, FALSE);

	if (pszRptID != NULL)
	{
		pRptValue->m_strValue.Format(_T("%f"), dValue);
	}

	if (pAbsError != NULL)
	{
		pAbsError->m_strValue.Format(_T("%f"), dAbsCal);
	}

	if (pRelError != NULL)
	{
		pRelError->m_strValue.Format(_T("%f"), dRelCal);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f")
		, dValue, dStandVal, dAbsCal, dRelCal, dAbsErr, dRelErr);

	return math_CalIsInError(dAbsCal, dRelCal, dAbsErr, dRelErr);
}

//通讯命令的参数脚本函数  2019-3-19
void CCommCmd::ClearCommCmdParas()
{
	m_pCmd->ClearCommCmdParas();
}

void CCommCmd::AddCommCmdParaValue(const CString &strValID, const CString &strValue)
{
	m_pCmd->AddCommCmdParaValue(strValID, strValue);
}

long CCommCmd::GetRepeatTimes(CString *pstrMode)
{
	if (m_pParent->GetClassID() == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)m_pParent;

		if (pMacroTest ->m_nRepeatTimes > 1)
		{
			if (pstrMode != NULL)
			{
				*pstrMode = pMacroTest->m_strReportMode;
			}

			return pMacroTest->m_nRepeatTimes;
		}
	}
	
	if (pstrMode != NULL)
	{
		*pstrMode = m_pCmd->m_strCalMode;
	}

	return m_pCmd->m_nRepeatTimes;
}

void CCommCmd::InitDsvRpt_All_Trip(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_All_Trip);

	if (pSoeRpt != NULL)
	{
		pSoeRpt->m_strValue.Empty();
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_All_ByValue(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime, _T("1"));

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_AllExpRecord.GetString()/*_T("全部出口报文：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

void CCommCmd::InitDsvRpt_All_More(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_More);

	if (pSoeRpt != NULL)
	{
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_All_More(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_Surplus.GetString()/*_T("多余：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

void CCommCmd::InitDsvRpt_All_Miss(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_Miss);

	if (pSoeRpt != NULL)
	{
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_All_Miss(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_Lack.GetString()/*_T("缺少：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

void CCommCmd::InitDsvRpt_All_AppearForErr(CValues *pValues)
{
	CValue *pSoeRpt = (CValue*)pValues->FindByID(g_strDsvResultID_AppearForErr);

	if (pSoeRpt != NULL)
	{
		BOOL bIsDsvTextWithValue = Gb_IsDsvTextWithValue(this);
		BOOL bIsDsvTextWithUtcTime = Gb_IsDsvTextWithUtcTime(this);
		pSoeRpt->m_strValue.Empty();
		m_pDsvScript->GetDsv_AppearForErr(pSoeRpt->m_strValue, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_Lack.GetString()/*_T("缺少：%s")*/, pSoeRpt->m_strValue.GetString());
	}
}

BOOL CCommCmd::RunDsvScript()  //20170523
{
	CDvmDataset *pRptDvmDataset = NULL;
	long nRsltJdg = m_nRsltJdg;

	RunDsvScript(&pRptDvmDataset);

	if (nRsltJdg == 0)
	{
		m_nRsltJdg = nRsltJdg;
	}

	return m_pDsvScript->m_bDsvSucc;
}

BOOL CCommCmd::RunDsvScript(CDvmDataset **ppRptDvmDataset)
{
	CReport *pReport = GetReport(-1);
	return RunDsvScript(ppRptDvmDataset, pReport, TRUE);
}

BOOL CCommCmd::RunResultScript()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook->IsTestError())
	{
		SetRsltJdg(1);
		return TRUE;
	}

	CString strSyntax;
	return CGbItemBase::RunResultScript(strSyntax, FALSE);
}

BOOL CCommCmd::RunResultScript(CString &strSyntax, BOOL bInitTrue)
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook->IsTestError())
	{
		SetRsltJdg(1);
		return TRUE;
	}

	CDvmDataset *pRptDvmDataset = NULL;
	long nRsltJdg = m_nRsltJdg;

	//DSV后于结果判断脚本运行
	if (IsDsvRunAfterResultScript())
	{
		CGbItemBase::RunResultScript(strSyntax, FALSE);

		nRsltJdg = m_nRsltJdg;

		RunDsvScript(&pRptDvmDataset);
		CReport *pReport = GetReport(-1);
		InitParas_NameAndVal(pReport->m_pValues);
	}
	else
	{
		RunDsvScript(&pRptDvmDataset);

		nRsltJdg = m_nRsltJdg;
		CReport *pReport = GetReport(-1);

		if (pReport != NULL)
		{
			InitParas_NameAndVal(pReport->m_pValues);
			CGbItemBase::RunResultScript(strSyntax, FALSE);
			nRsltJdg = m_nRsltJdg;
		}
	}

	if (nRsltJdg == 0)
	{
		m_nRsltJdg = nRsltJdg;
	}

	if (m_nRsltJdg == 1)
	{
		m_nState = TEST_STATE_ELIGIBLE;
	}
	else
	{
		m_nState = TEST_STATE_INLEGIBLE;
	}

	m_pReports->SetResultJudge(m_nRsltJdg);
	Gb_UpdateGbItemParentTestState(this);

	return m_nRsltJdg;
}

BOOL CCommCmd::IsCommCmdParaDS()
{
	CGbCommCmdMms *pGbCmd = GetGbCommCmd();

	if (pGbCmd == NULL)
	{
		return TRUE;
	}

	return (pGbCmd->GetCount() == 0);
}

CGbCommCmdMms* CCommCmd::GetGbCommCmd()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return NULL;
	}

	return (CGbCommCmdMms *)pGuideBook->m_oGbCommCmdConfig.FindByID(m_strCommCmdID);
}


long CCommCmd::CalTestTimeLong()
{

	return 0;
}

void CCommCmd::ClearItemInDbState()
{
	CGbItemBase::ClearItemInDbState();
}

long CCommCmd::GetItemTestCount()
{
	CGbItemBase *pParent = (CGbItemBase *)GetParent();

	return pParent->GetItemTestCount();
}