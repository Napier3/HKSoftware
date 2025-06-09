//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSystemConfig.cpp  CIecCfgSystemConfig


#include "stdafx.h"
#include "IecCfgSystemConfig.h"
#include "../../../Module/API/GlobalConfigApi.h"

const CString CIecCfgSystemConfig::g_strIecCfgSystemConfigFile = _T("IecCfgSystemConfig.xml");

CIecCfgSystemConfig::CIecCfgSystemConfig()
{
	//初始化属性
	m_bAutoSetUIChIndex = TRUE;

	//初始化成员变量
}

CIecCfgSystemConfig::~CIecCfgSystemConfig()
{
}

long CIecCfgSystemConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strDefaultCfgFileKey, oNode, m_strDefaultCfgFile);
	xml_GetElementText(pXmlKeys->m_strLaIecCfgFileKey, oNode, m_strLaIecCfgFile);
	xml_GetElementText(pXmlKeys->m_strUseDebugKey, oNode, m_strUseDebug);
	xml_GetElementText(pXmlKeys->m_strAutoSetUIChIndexKey, oNode, m_strAutoSetUIChIndex);

	InitAutoSetUIChIndex();

	return 0;
}

long CIecCfgSystemConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strDefaultCfgFileKey, oXMLDoc, oElement, m_strDefaultCfgFile);
	xml_SetElementText(pXmlKeys->m_strLaIecCfgFileKey, oXMLDoc, oElement, m_strLaIecCfgFile);
	xml_SetElementText(pXmlKeys->m_strUseDebugKey, oXMLDoc, oElement, m_strUseDebug);
	xml_SetElementText(pXmlKeys->m_strAutoSetUIChIndexKey, oXMLDoc, oElement, m_strAutoSetUIChIndex);

	return 0;
}

long CIecCfgSystemConfig::Open()
{
	ASSERT (CCfgDataMngrXmlRWKeys::g_pXmlKeys != NULL);

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += g_strIecCfgSystemConfigFile;

	return OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

long CIecCfgSystemConfig::Save()
{
	ASSERT (CCfgDataMngrXmlRWKeys::g_pXmlKeys != NULL);

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += g_strIecCfgSystemConfigFile;

	ClearFileReadOnlyAttr(strFile);
	SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	return 1;
}

CString CIecCfgSystemConfig::GetInitFile()
{
#ifndef _PSX_IDE_QT_
	CFileStatus status;
	
	if (m_strLaIecCfgFile.GetLength() > 0)
	{
		if (CFile::GetStatus(m_strLaIecCfgFile, status))
		{
			return m_strLaIecCfgFile;
		}
	}

	if (m_strDefaultCfgFile.GetLength() > 0)
	{
		if (CFile::GetStatus(m_strDefaultCfgFile, status))
		{
			return m_strDefaultCfgFile;
		}
	}
#endif

	return _T("");
}

CString CIecCfgSystemConfig::GetLastFile()
{
	return m_strLaIecCfgFile;
}

void CIecCfgSystemConfig::SetLaIecCfgFile(const CString &strFile)
{
	if (strFile.GetLength() == 0)
	{
		m_strDefaultCfgFile = m_strLaIecCfgFile;
	}

	m_strLaIecCfgFile = strFile;

	Save();
}

