//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSystemConfig.cpp  CSttSystemConfig


#include "stdafx.h"
#include "SttSystemConfig.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSystemConfig g_oSttSystemConfig;

CSttSystemConfig::CSttSystemConfig()
{
	//初始化属性
	m_fOpenDelayTime = 4.0f;
	m_strCompanyName = _T("Ponovo");
	m_nInternationalMode = 0;

	//初始化成员变量
}

CSttSystemConfig::~CSttSystemConfig()
{
}

long CSttSystemConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOpen_Delay_TimeKey, oNode, m_fOpenDelayTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCompany_NameKey, oNode, m_strCompanyName);
	xml_GetAttibuteValue(pXmlKeys->m_strInternationalModeKey, oNode, m_nInternationalMode);
	return 0;
}

long CSttSystemConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOpen_Delay_TimeKey, oElement, m_fOpenDelayTime);
	xml_SetAttributeValue(pXmlKeys->m_strCompany_NameKey, oElement, m_strCompanyName);
	xml_SetAttributeValue(pXmlKeys->m_strInternationalModeKey, oElement, m_nInternationalMode);
	return 0;
}

long CSttSystemConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fOpenDelayTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strCompanyName);
		BinarySerializeCalLen(oBinaryBuffer, m_nInternationalMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fOpenDelayTime);
		BinarySerializeRead(oBinaryBuffer, m_strCompanyName);
		BinarySerializeRead(oBinaryBuffer, m_nInternationalMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fOpenDelayTime);
		BinarySerializeWrite(oBinaryBuffer, m_strCompanyName);
		BinarySerializeWrite(oBinaryBuffer, m_nInternationalMode);
	}
	return 0;
}

void CSttSystemConfig::InitAfterRead()
{
}

BOOL CSttSystemConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttSystemConfig *p = (CSttSystemConfig*)pObj;

	if(m_fOpenDelayTime != p->m_fOpenDelayTime)
	{
		return FALSE;
	}

	if(m_strCompanyName != p->m_strCompanyName)
	{
		return FALSE;
	}

	if(m_nInternationalMode != p->m_nInternationalMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSystemConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttSystemConfig *p = (CSttSystemConfig*)pDest;

	p->m_fOpenDelayTime = m_fOpenDelayTime;
	p->m_strCompanyName = m_strCompanyName;
	p->m_nInternationalMode = m_nInternationalMode;
	return TRUE;
}

CBaseObject* CSttSystemConfig::Clone()
{
	CSttSystemConfig *p = new CSttSystemConfig();
	Copy(p);
	return p;
}

CBaseObject* CSttSystemConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSystemConfig *p = new CSttSystemConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSystemConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTDEVCONFIG)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTMODULEUSE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttSystemConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttDevConfigKey)
	{
		pNew = new CSttDevConfig();
	}
	else if (strClassID == pXmlKeys->m_strCSttModuleUseKey)
	{
		pNew = new CSttModuleUse();
	}

	return pNew;
}

CExBaseObject* CSttSystemConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTDEVCONFIG)
	{
		pNew = new CSttDevConfig();
	}
	else if (nClassID == MNGRCLASSID_CSTTMODULEUSE)
	{
		pNew = new CSttModuleUse();
	}

	return pNew;
}

CSttDevConfig* CSttSystemConfig::GetSttDevConfig()
{
	CSttDevConfig* pSttDevConfig = (CSttDevConfig*)FindByClassID(MNGRCLASSID_CSTTDEVCONFIG);

	if (pSttDevConfig == NULL)
	{
		pSttDevConfig = new CSttDevConfig;
		AddNewChild(pSttDevConfig);
	}

	return pSttDevConfig;
}

BOOL CSttSystemConfig::OpenSystemConfig(const CString &strPath)
{
	if (!strPath.IsEmpty())
	{
		return OpenXmlFile(strPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);
	}

	CString strDefautPath;
	strDefautPath = _P_GetConfigPath();
	strDefautPath += (_T("SystemConfig.xml"));

	if (!IsFileExist(strDefautPath))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("系统配置文件(%s)不存在."),strDefautPath.GetString());
		return FALSE;
	}

	DeleteAll();
	return OpenXmlFile(strDefautPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);
}

BOOL CSttSystemConfig::SaveSystemConfig(const CString &strPath)
{
	if (!strPath.IsEmpty())
	{
		return SaveXmlFile(strPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);
	}

	CString strDefautPath;
	strDefautPath = _P_GetConfigPath();
	strDefautPath += (_T("SystemConfig.xml"));
	return SaveXmlFile(strDefautPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);
}

CString CSttSystemConfig::GetDevModel()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();

	if (pSttDevConfig->m_strCurSelModel.IsEmpty())
	{
		pSttDevConfig->m_strCurSelModel = _T("PN466");
	}

	return pSttDevConfig->m_strCurSelModel;
}

BOOL CSttSystemConfig::IsDoubleClickEdit()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return (pSttDevConfig->m_nDoubleClickEdit == 1);
}

void CSttSystemConfig::SetCurDevModel(const CString &strModel)
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	pSttDevConfig->m_strCurSelModel = strModel;
}

long CSttSystemConfig::UseSclView()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return pSttDevConfig->m_nUseSclView;
}

long CSttSystemConfig::GetLogPrintValue()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return pSttDevConfig->m_nLogPrint;
}
long CSttSystemConfig::GetFt3PrimCodeValue()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return pSttDevConfig->m_nFt3_Prim_Code_Value;
}
long CSttSystemConfig::GetLockMaps()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return pSttDevConfig->m_nLockMaps;
}
void CSttSystemConfig::SetLockMaps(const long &nLockMaps)
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	pSttDevConfig->m_nLockMaps = nLockMaps;
}


long CSttSystemConfig::GetSelSysPata()
{
	CSttDevConfig* pSttDevConfig = GetSttDevConfig();
	return pSttDevConfig->m_nSel_Sys_Pata;
}