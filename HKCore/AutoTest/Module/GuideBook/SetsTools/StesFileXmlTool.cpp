#include "StdAfx.h"
#include "StesFileXmlTool.h"
#include "SetFilesXmlParse/SetFileXmlParseGlobal.h"

CStesFileXmlTool::CStesFileXmlTool(void)
{
	CSetFileXmlParseXmlRWKeys::Create();
}

CStesFileXmlTool::~CStesFileXmlTool(void)
{
	CSetFileXmlParseXmlRWKeys::Release();
}

BOOL CStesFileXmlTool::ExportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	return m_pRefObject->SaveXmlFile(strFile, CGbXMLKeys::g_pGbXMLKeys);
}

BOOL CStesFileXmlTool::ImportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	m_oSetsFileXml_Dsc.DeleteAll();
	m_oSetsFileXml_Dsc.m_strMd5_Cal_Ena.Empty();
	m_oSetsFileXml_Dsc.m_strMd5_Cal_Parameter.Empty();
	m_oSetsFileXml_Dsc.m_strMd5_Cal_Setting.Empty();
	m_oLogicDeviceFile.DeleteAll();
	m_oSetsFileXml_Dsc.m_pLDevice = &m_oLogicDeviceFile;
	BOOL bRet = m_oSetsFileXml_Dsc.OpenXmlFile(strFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		::MessageBox(NULL, _T("定值单文件格式错误，请重新选择！"), _T("错误"), MB_OK);
	}

	InitGbDataset();

	return bRet;
}

CDvmDataset* CStesFileXmlTool::GetSetsByID(const CString &strID)
{
	//20230612 huangliang 空值判断
	if(m_oSetsFileXml_Dsc.m_pLDevice == NULL)
		return NULL;
	CDvmDataset *pFind = (CDvmDataset *)m_oSetsFileXml_Dsc.m_pLDevice->FindByID(strID);

	return pFind;
}

void CStesFileXmlTool::GetMd5_FromFile(const CString strClass, CString &strMd5)
{
	m_oSetsFileXml_Dsc.GetMd5_FromFile(strClass, strMd5);
}

void CStesFileXmlTool::GetMd5_FromCal(const CString strClass, CString &strMd5)
{
	m_oSetsFileXml_Dsc.GetMd5_FromCal(strClass, strMd5);
}