#include "stdafx.h"
#include "TCtrlSystemConfig.h"
#include "AutoTestXMLRWKeys.h"
// #include "../../Module/Interface/XML2Interface.h"
#include "../../Module/api/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTCtrlSystemConfig::CTCtrlSystemConfig()
{
	m_strDBName = _T("");
	m_strTaskMngrFile = _T("");
	m_strWorkSpaceFile = _T("");
}

CTCtrlSystemConfig::~CTCtrlSystemConfig()
{

}

BOOL CTCtrlSystemConfig::Init()
{
	CString strSytemConfigFileName = (CString)_P_GetConfigPath() + _T("SystemConfig.xml");
	return OpenXmlFile(strSytemConfigFileName, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strSystemConfigKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

long CTCtrlSystemConfig::InitAfterSerialize()
{
	return 0;
}

UINT CTCtrlSystemConfig::GetClassID()
{
	return 0;
}

long CTCtrlSystemConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CTCtrlSystemConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
  
	return 0;
}

long CTCtrlSystemConfig::XmlWriteOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CTCtrlSystemConfig::IsEqual(CExBaseObject* pObj)
{
	return 0;
}

long CTCtrlSystemConfig::Copy(CExBaseObject* pDesObj)
{
	return 0;
}

CExBaseObject* CTCtrlSystemConfig::Clone()
{
	return NULL;
}