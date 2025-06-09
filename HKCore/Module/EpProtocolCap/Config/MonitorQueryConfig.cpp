//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MonitorCapConfig.cpp  CMonitorQueryConfig


#include "stdafx.h"
#include "MonitorQueryConfig.h"

CMonitorQueryConfig::CMonitorQueryConfig()
{
	//初始化属性
	m_strName = _T("配置管理");
	m_strID = _T("EmcNetConfig");

	//初始化成员变量
// 	m_pEmcSerialsConfig = NULL;
	m_pEmcNetsConfig = NULL;
// 	m_pEmcNetDevices = NULL;
	m_pQueryProtocols = NULL;
	m_nUseGenerator = 0;
	m_pEmcDeviceModelFiles = NULL;
}

CMonitorQueryConfig::~CMonitorQueryConfig()
{
}

long CMonitorQueryConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseGeneratorKey, oNode, m_nUseGenerator);

	return 0;
}

long CMonitorQueryConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseGeneratorKey, oElement, m_nUseGenerator);

	return 0;
}

long CMonitorQueryConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CMonitorQueryConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

// 		if (nClassID == EMCCLASSID_CEMCNETDEVICES)
// 		{
// 			m_pEmcNetDevices = (CEmcNetDevices*)p;
// 		}
// 		else if (nClassID == EMCCLASSID_CEMCSERIALSCONFIG)
// 		{
// 			m_pEmcSerialsConfig = (CEmcSerialsConfig*)p;
// 		}
// 		else 
		if (nClassID == EMCCLASSID_CEMCNETSCONFIG)
		{
			m_pEmcNetsConfig = (CEmcNetsConfig*)p;
		}
		else if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOLS)
		{
			m_pQueryProtocols = (CEmcQueryProtocols*)p;
		}
		else if (nClassID == EMCCLASSID_CEMCDEVICEMODELFILES)
		{
			m_pEmcDeviceModelFiles = (CEmcDeviceModelFiles*)p;
		}
	}

// 	if (m_pEmcNetDevices == NULL)
// 	{
// 		m_pEmcNetDevices = (CEmcNetDevices*)AddNewChild(new CEmcNetDevices());
// 	}
// 
// 	if (m_pEmcSerialsConfig == NULL)
// 	{
// 		m_pEmcSerialsConfig = (CEmcSerialsConfig*)AddNewChild(new CEmcSerialsConfig());
// 	}

	if (m_pEmcNetsConfig == NULL)
	{
		m_pEmcNetsConfig = (CEmcNetsConfig*)AddNewChild(new CEmcNetsConfig());
	}

	if (m_pQueryProtocols == NULL)
	{
		m_pQueryProtocols = (CEmcQueryProtocols*)AddNewChild(new CEmcQueryProtocols());
	}

	if (m_pEmcDeviceModelFiles == NULL)
	{
		m_pEmcDeviceModelFiles = (CEmcDeviceModelFiles*)AddNewChild(new CEmcDeviceModelFiles());
	}

	if (m_pEpCapYcAnalysisMngr == NULL)
	{
		m_pEpCapYcAnalysisMngr = (CEpCapYcAnalysisMngr*)AddNewChild(new CEpCapYcAnalysisMngr());
	}

// 	BringToHead(m_pEmcSerialsConfig);
	BringToHead(m_pEmcNetsConfig);
// 	BringToHead(m_pEmcNetDevices);
	BringToHead(m_pEmcDeviceModelFiles);
}

BOOL CMonitorQueryConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMonitorQueryConfig *p = (CMonitorQueryConfig*)pObj;

	return TRUE;
}

BOOL CMonitorQueryConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMonitorQueryConfig *p = (CMonitorQueryConfig*)pDest;

	return TRUE;
}

CBaseObject* CMonitorQueryConfig::Clone()
{
	CMonitorQueryConfig *p = new CMonitorQueryConfig();
	Copy(p);
	return p;
}

BOOL CMonitorQueryConfig::CanPaste(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCSERIALSCONFIG)
	{
		return TRUE;
	}

	if (nClassID == EMCCLASSID_CEMCNETSCONFIG)
	{
		return TRUE;
	}

	if (nClassID == EMCCLASSID_CEMCNETDEVICES)
	{
		return TRUE;
	}

	if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOLS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMonitorQueryConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcNetsConfigKey)
	{
		pNew = new CEmcNetsConfig();
	}
	else if (strClassID == pXmlKeys->m_strCEmcQueryProtocolsKey)
	{
		pNew = new CEmcQueryProtocols();
	}
	else if (strClassID == pXmlKeys->m_strCEmcDeviceModelFilesKey)
	{
		pNew = new CEmcDeviceModelFiles();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapYcAnalysisMngrKey)
	{
		pNew = new CEpCapYcAnalysisMngr();
	}

	return pNew;
}

void CMonitorQueryConfig::InitConfig()
{
	m_strFile = _P_GetConfigPath();
	m_strFile += _T("EpQueryConfig.xml");

	BOOL b = OpenXmlFile(m_strFile, CMonitorCapConfigXmlRWKeys::CMonitorCapConfigKey(), CMonitorCapConfigXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
		InitAfterRead();
	}
}

void CMonitorQueryConfig::SaveConfig()
{
	m_strFile = _P_GetConfigPath();
	m_strFile += _T("EpQueryConfig.xml");
	SaveXmlFile(m_strFile, CMonitorCapConfigXmlRWKeys::g_pXmlKeys);
}

CExBaseObject* CMonitorQueryConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCNETSCONFIG)
	{
		pNew = new CEmcNetsConfig();
	}
	else if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOLS)
	{
		pNew = new CEmcQueryProtocols();
	}

	return pNew;
}
