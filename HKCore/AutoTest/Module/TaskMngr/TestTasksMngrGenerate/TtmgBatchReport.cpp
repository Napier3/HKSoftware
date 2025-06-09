//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgBatchReport.cpp  CTtmgBatchReport


#include "stdafx.h"
#include "TtmgBatchReport.h"
#include "TestTasksMngrGenerate.h"
#include "..\ReportSNGen.h"
#include "..\..\..\..\System\Module\XAtsSysSvrClient.h"

CTtmgBatchReport::CTtmgBatchReport()
{
	//初始化属性
	m_nHasGenerated = 0;

	//初始化成员变量
	m_pTtmgReportRef = NULL;
	m_pTtmgReportRefDestructive = NULL;
	m_pTtmgReportRefNonDestructive = NULL;
	m_pTtmgReportRefSum = NULL;
	m_nRptIndex = 0;

	//ZeroMemory(m_chRptGenState, 4);
	m_nRptGenStateIndex = -1;
}

CTtmgBatchReport::~CTtmgBatchReport()
{
}

long CTtmgBatchReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceAttrKey, oNode, m_strDeviceAttr);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcRptKey, oNode, m_strSrcRpt);
	xml_GetAttibuteValue(pXmlKeys->m_strDestRptKey, oNode, m_strDestRpt);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorTypeKey, oNode, m_strErrorType);
	xml_GetAttibuteValue(pXmlKeys->m_strHasGeneratedKey, oNode, m_nHasGenerated);

	return 0;
}

long CTtmgBatchReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceAttrKey, oElement, m_strDeviceAttr);
	xml_SetAttributeValue(pXmlKeys->m_strSrcRptKey, oElement, m_strSrcRpt);
	xml_SetAttributeValue(pXmlKeys->m_strDestRptKey, oElement, m_strDestRpt);
	xml_SetAttributeValue(pXmlKeys->m_strErrorTypeKey, oElement, m_strErrorType);
	xml_SetAttributeValue(pXmlKeys->m_strHasGeneratedKey, oElement, m_nHasGenerated);
	return 0;
}

long CTtmgBatchReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceAttr);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrcRpt);
		BinarySerializeCalLen(oBinaryBuffer, m_strDestRpt);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorType);
		BinarySerializeCalLen(oBinaryBuffer, m_nHasGenerated);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceAttr);
		BinarySerializeRead(oBinaryBuffer, m_strSrcRpt);
		BinarySerializeRead(oBinaryBuffer, m_strDestRpt);
		BinarySerializeRead(oBinaryBuffer, m_strErrorType);
		BinarySerializeRead(oBinaryBuffer, m_nHasGenerated);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceAttr);
		BinarySerializeWrite(oBinaryBuffer, m_strSrcRpt);
		BinarySerializeWrite(oBinaryBuffer, m_strDestRpt);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorType);
		BinarySerializeWrite(oBinaryBuffer, m_nHasGenerated);
	}
	return 0;
}

void CTtmgBatchReport::InitAfterRead()
{
}

BOOL CTtmgBatchReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgBatchReport *p = (CTtmgBatchReport*)pObj;

	if(m_strDeviceAttr != p->m_strDeviceAttr)
	{
		return FALSE;
	}

	if(m_strSrcRpt != p->m_strSrcRpt)
	{
		return FALSE;
	}

	if(m_strDestRpt != p->m_strDestRpt)
	{
		return FALSE;
	}

	if(m_strErrorType != p->m_strErrorType)
	{
		return FALSE;
	}

	if(m_nHasGenerated != p->m_nHasGenerated)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTtmgBatchReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgBatchReport *p = (CTtmgBatchReport*)pDest;

	p->m_strDeviceAttr = m_strDeviceAttr;
	p->m_strSrcRpt = m_strSrcRpt;
	p->m_strDestRpt = m_strDestRpt;
	p->m_strErrorType = m_strErrorType;
	p->m_nHasGenerated = m_nHasGenerated;
	return TRUE;
}

CBaseObject* CTtmgBatchReport::Clone()
{
	CTtmgBatchReport *p = new CTtmgBatchReport();
	Copy(p);
	return p;
}

void CTtmgBatchReport::Generate(CThreadProgressInterface *pGenThread)
{
	//拷贝报告
// 	CString strDestPath;
// 	CTtmgBatch *pBatch = (CTtmgBatch*)GetParent();
// 
// 	if (m_strErrorType.GetLength() > 0)
// 	{
// 		strDestPath.Format(_T("%s%s-未通过\\"), pBatch->m_strFolder, m_strFolderName);
// 	}
// 	else
// 	{
// 		strDestPath.Format(_T("%s%s\\"), pBatch->m_strFolder, m_strFolderName);
// 	}
// 
// 	CreateAllDirectories(strDestPath);
	Generate_CreateDir(pGenThread);
	
	if (m_nRptGenStateIndex == -1)
	{
		m_nRptGenStateIndex = TTMG_RPTGENSTATE_INDEX_Test;
	}
	else
	{
		if (m_pTtmgReportRefDestructive != NULL)
		{
			m_nRptGenStateIndex++;
		}
		else
		{
			m_nRptGenStateIndex = TTMG_RPTGENSTATE_INDEX_Sum;
		}
	}

	switch (m_nRptGenStateIndex)
	{
	case TTMG_RPTGENSTATE_INDEX_Test:
		Generate_Test(pGenThread);
		break;

	case TTMG_RPTGENSTATE_INDEX_Destructive:
		Generate_Destructive(pGenThread);
		break;

	case TTMG_RPTGENSTATE_INDEX_NonDestructive:
		Generate_NonDestructive(pGenThread);
		break;

	case TTMG_RPTGENSTATE_INDEX_Sum:
		Generate_Sum(pGenThread);
		break;
	}

// 	if (m_chRptGenState[TTMG_RPTGENSTATE_INDEX_Test] == 0)
// 	{
// 		Generate_Test(pGenThread);
// 		return;
// 	}
}

void CTtmgBatchReport::FinishGenerate(CThreadProgressInterface *pGenThread)
{
	if (m_nRptGenStateIndex == TTMG_RPTGENSTATE_INDEX_Sum)	
	{
		m_nHasGenerated = 1;
	}
}

void CTtmgBatchReport::Generate_CreateDir(CThreadProgressInterface *pGenThread)
{
	if (m_strDestPath.GetLength() > 3)
	{
		return;
	}

	//拷贝报告
	CTtmgBatch *pBatch = (CTtmgBatch*)GetParent();

	if (m_strErrorType.GetLength() > 0)
	{
		m_strDestPath.Format(_T("%s%s-未通过\\"), pBatch->m_strFolder, m_strFolderName);
	}
	else
	{
		m_strDestPath.Format(_T("%s%s\\"), pBatch->m_strFolder, m_strFolderName);
	}

	CreateAllDirectories(m_strDestPath);
}

void CTtmgBatchReport::Generate_Test(CThreadProgressInterface *pGenThread)
{
	CString strSrcFile, strDestFile;
	strSrcFile = m_pTtmgReportRef->m_pXFile->GetRelativePath(TRUE);
	strDestFile.Format(_T("%s%s.%s"), m_strDestPath, m_strID, g_strGuideBookBinaryPostfix);
	::CopyFile(strSrcFile, strDestFile, FALSE);

	strSrcFile = ChangeFilePostfix(strSrcFile, g_strDocFilePostfix);
	strDestFile = ChangeFilePostfix(strDestFile, g_strDocFilePostfix);
	::CopyFile(strSrcFile, strDestFile, FALSE);

	//启动自动测试程序，编辑报告
	strDestFile = ChangeFilePostfix(strDestFile, g_strGuideBookBinaryPostfix);
	pGenThread->ShowMsg(m_strID);
	CString strDeviceAttr;
	GetDeviceAttrXML(strDeviceAttr);
	CXAtsSysSvrClient::OpenAutoTest_XTestDB(strDestFile, strDeviceAttr);
}

void CTtmgBatchReport::Generate_Destructive(CThreadProgressInterface *pGenThread)
{
	Generate_XXX(pGenThread, m_pTtmgReportRefNonDestructive
		, CTestTasksMngrGenerate::GetGbxml2());
}

void CTtmgBatchReport::Generate_NonDestructive(CThreadProgressInterface *pGenThread)
{
	Generate_XXX(pGenThread, m_pTtmgReportRefNonDestructive
		, CTestTasksMngrGenerate::GetGbxml3());
}

void CTtmgBatchReport::Generate_Sum(CThreadProgressInterface *pGenThread)
{
	Generate_XXX(pGenThread, m_pTtmgReportRefSum, _T("汇总表"));
}

void CTtmgBatchReport::Generate_XXX(CThreadProgressInterface *pGenThread
									, CTtmgReport *pTtmgReport, const CString &strGbxml)
{
	CString strSrcFile, strDestFile;
	strSrcFile = pTtmgReport->m_pXFile->GetRelativePath(TRUE);
	strDestFile.Format(_T("%s%s_%s.%s"), m_strDestPath, m_strFolderName
		, strGbxml, g_strGuideBookBinaryPostfix);
	::CopyFile(strSrcFile, strDestFile, FALSE);

	strSrcFile = ChangeFilePostfix(strSrcFile, g_strDocFilePostfix);
	strDestFile = ChangeFilePostfix(strDestFile, g_strDocFilePostfix);
	::CopyFile(strSrcFile, strDestFile, FALSE);

	//启动自动测试程序，编辑报告
	strDestFile = ChangeFilePostfix(strDestFile, g_strGuideBookBinaryPostfix);
	pGenThread->ShowMsg(GetPathFileNameFromFilePathName(strDestFile));

	CString strDeviceAttr;
	GetDeviceAttrXML(strDeviceAttr);
	CXAtsSysSvrClient::OpenAutoTest_XTestDB(strDestFile, strDeviceAttr);
}

void CTtmgBatchReport::InitReport(CTtmgReport *pRpt, CTtmgReport *pRptDestructive, CTtmgReport *pRptNonDestructive, CTtmgReport *pReportSum)
{
	m_strSrcRpt = pRpt->m_pXFile->GetRelativePath(TRUE);
	m_strErrorType = pRpt->m_strReportType;
	m_pTtmgReportRef = pRpt;
	m_pTtmgReportRefDestructive = pRptDestructive;
	m_pTtmgReportRefNonDestructive = pRptNonDestructive;
	m_pTtmgReportRefSum = pReportSum;
}

void CTtmgBatchReport::AddDeviceAttr(const CString &strName, const CString &strValue)
{
	m_oDvmDeviceAttr.AddNewData(strName, strName, _T(""), strValue);
}

void CTtmgBatchReport::InitDeviceAttr()
{
	GetDeviceAttr(m_strDeviceAttr);
}

void CTtmgBatchReport::GetDeviceAttr(CString &strDeviceAttr)
{
	strDeviceAttr.Empty();

	POS pos = m_oDvmDeviceAttr.GetHeadPosition();
	long nCount = m_oDvmDeviceAttr.GetCount();
	CDvmData *pTail = (CDvmData*)m_oDvmDeviceAttr.GetAtIndex(nCount-4);
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oDvmDeviceAttr.GetNext(pos);

		if (pData != pTail)
		{
			strDeviceAttr.AppendFormat(_T("%s：%s，"), pData->m_strName, pData->m_strValue);
		}
		else
		{
			break;
		}
	}

	strDeviceAttr.AppendFormat(_T("%s：%s"), pTail->m_strName, pTail->m_strValue);
}

void CTtmgBatchReport::GetDeviceAttrXML(CString &strXML)
{
	strXML.Empty();
	m_oDvmDeviceAttr.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXML);
}

void CTtmgBatchReport::InitDestRpt()
{
	CReportSNGen oRptSnGen;
	CTestProject *pProject = CTestTasksMngrGenerate::GetTestProject();

	//pProject->m_strTemplateFile = CTestTasksMngrGenerate::GetGbxml1();
	pProject->tsk_SetGbxmlFile(CTestTasksMngrGenerate::GetGbxml1());

	oRptSnGen.m_pDataset = &m_oDvmDeviceAttr;
	oRptSnGen.m_pCurrTestProject = pProject;

	CString strReportSN;
	//报告路径文件名称
	oRptSnGen.ReportSNGen(CTestTasksMngrGenerate::GetTaskReportSNGen(), m_strFolderName);

	//报告文件名称
	oRptSnGen.ReportSNGen(CTestTasksMngrGenerate::GetReportSNGen(), strReportSN);
	m_strName = strReportSN;
	m_strID = strReportSN;
	m_oDvmDeviceAttr.m_strName = strReportSN;
	m_oDvmDeviceAttr.m_strID = strReportSN;

	if (m_strFolderName.GetLength() == 0)
	{
		m_strFolderName = strReportSN;
	}
}

