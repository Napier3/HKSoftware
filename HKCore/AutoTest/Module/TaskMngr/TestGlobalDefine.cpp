#include "stdafx.h"
#include "TestGlobalDefine.h"
#include "../AutoTestXMLRWKeys.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceCmmConfig.h"
#endif

/*
说明：m_pExpandDatasAutoSet，根据装置属性中带有通道数的属性（例如型号），取其数字，自动设置测试任务的组数
*/

CTestGlobalDefine::CTestGlobalDefine()
{
	m_pExpandDatas = NULL;
	m_pExpandDatasAutoSet = NULL;
	m_pReportSNGen = NULL;
	m_pTaskReportSNGen = NULL;
	m_pDeviceAttrsDefine = NULL;
	m_pTestAppDefine = NULL;

	m_nShowWordRpt = REPORTFILL_INDEX_NONE;
}

CTestGlobalDefine::~CTestGlobalDefine()
{
	
}

BOOL CTestGlobalDefine::OpenTestDefineFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys)
{
	m_strTestGlobalDefineFile = strFile;

	return OpenXmlFile(strFile, bstrElementKey, pXmlRWKeys);
}

BOOL CTestGlobalDefine::SaveTestDefineFile(CXmlRWKeys *pXmlRWKeys)
{
#ifdef _PSX_QT_LINUX_
    return TRUE;
#endif

	if (!IsFileExist(m_strTestGlobalDefineFile))
	{
		return FALSE;
	}

	return SaveXmlFile(m_strTestGlobalDefineFile, pXmlRWKeys);
}

BSTR CTestGlobalDefine::GetXmlElementKey()
{
	return CGbXMLKeys::TestDefineKey();
}


CExBaseObject* CTestGlobalDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDvmLogicDevice::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

void CTestGlobalDefine::InitAfterRead()
{
	m_pExpandDatas = (CDvmDataset*)FindByID(DSID_COMMCMDMCONFIG);
	m_pExpandDatasAutoSet = (CDvmDataset*)FindByID(DSID_COMMCMDMCONFIG_AUTOSET);
	m_pReportSNGen = (CDvmDataset*)FindByID(DSID_REPORT_SN_GEN);
	m_pTaskReportSNGen = (CDvmDataset*)FindByID(DSID_TASK_REPORT_SN_GEN);
	m_pTestAppDefine = (CDvmDataset*)FindByID(DSID_TESTAPP_DEF);
	m_pDeviceAttrsDefine = (CDvmDataset*)FindByID(DSID_DEVICEATTR);
}


long CTestGlobalDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strShowWordRptKey,oNode,m_nShowWordRpt);

	return 0;
}

long CTestGlobalDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strShowWordRptKey,oElement,m_nShowWordRpt);

	return 0;
}
