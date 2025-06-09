//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MonitorCapConfig.cpp  CMonitorCapConfig


#include "stdafx.h"
#include "MonitorCapConfig.h"

CMonitorCapConfig::CMonitorCapConfig()
{
	//��ʼ������
	m_strName = _T("���ù���");
	m_strID = _T("EmcNetConfig");

	//��ʼ����Ա����
	m_pEmcSerialsConfig = NULL;
// 	m_pEmcNetsConfig = NULL;
	m_pEmcNetDevices = NULL;
// 	m_pQueryProtocols = NULL;
	m_nUseGenerator = 0;
// 	m_pEmcDeviceModelFiles = NULL;
}

CMonitorCapConfig::~CMonitorCapConfig()
{
}

long CMonitorCapConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseGeneratorKey, oNode, m_nUseGenerator);

	return 0;
}

long CMonitorCapConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseGeneratorKey, oElement, m_nUseGenerator);

	return 0;
}

long CMonitorCapConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMonitorCapConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EMCCLASSID_CEMCNETDEVICES)
		{
			m_pEmcNetDevices = (CEmcNetDevices*)p;
		}
		else if (nClassID == EMCCLASSID_CEMCSERIALSCONFIG)
		{
			m_pEmcSerialsConfig = (CEmcSerialsConfig*)p;
		}
// 		else if (nClassID == EMCCLASSID_CEMCNETSCONFIG)
// 		{
// 			m_pEmcNetsConfig = (CEmcNetsConfig*)p;
// 		}
// 		else if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOLS)
// 		{
// 			m_pQueryProtocols = (CEmcQueryProtocols*)p;
// 		}
// 		else if (nClassID == EMCCLASSID_CEMCDEVICEMODELFILES)
// 		{
// 			m_pEmcDeviceModelFiles = (CEmcDeviceModelFiles*)p;
// 		}
	}

	if (m_pEmcNetDevices == NULL)
	{
		m_pEmcNetDevices = (CEmcNetDevices*)AddNewChild(new CEmcNetDevices());
	}

	if (m_pEmcSerialsConfig == NULL)
	{
		m_pEmcSerialsConfig = (CEmcSerialsConfig*)AddNewChild(new CEmcSerialsConfig());
	}

// 	if (m_pEmcNetsConfig == NULL)
// 	{
// 		m_pEmcNetsConfig = (CEmcNetsConfig*)AddNewChild(new CEmcNetsConfig());
// 	}

// 	if (m_pQueryProtocols == NULL)
// 	{
// 		m_pQueryProtocols = (CEmcQueryProtocols*)AddNewChild(new CEmcQueryProtocols());
// 	}
// 
// 	if (m_pEmcDeviceModelFiles == NULL)
// 	{
// 		m_pEmcDeviceModelFiles = (CEmcDeviceModelFiles*)AddNewChild(new CEmcDeviceModelFiles());
// 	}

	BringToHead(m_pEmcSerialsConfig);
// 	BringToHead(m_pEmcNetsConfig);
	BringToHead(m_pEmcNetDevices);
// 	BringToHead(m_pEmcDeviceModelFiles);
}

BOOL CMonitorCapConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMonitorCapConfig *p = (CMonitorCapConfig*)pObj;

	return TRUE;
}

BOOL CMonitorCapConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMonitorCapConfig *p = (CMonitorCapConfig*)pDest;

	return TRUE;
}

CBaseObject* CMonitorCapConfig::Clone()
{
	CMonitorCapConfig *p = new CMonitorCapConfig();
	Copy(p);
	return p;
}

BOOL CMonitorCapConfig::CanPaste(UINT nClassID)
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

CExBaseObject* CMonitorCapConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcSerialsConfigKey)
	{
		pNew = new CEmcSerialsConfig();
	}
// 	else if (strClassID == pXmlKeys->m_strCEmcNetsConfigKey)
// 	{
// 		pNew = new CEmcNetsConfig();
// 	}
	else if (strClassID == pXmlKeys->m_strCEmcNetDevicesKey)
	{
		pNew = new CEmcNetDevices();
	}
// 	else if (strClassID == pXmlKeys->m_strCEmcQueryProtocolsKey)
// 	{
// 		pNew = new CEmcQueryProtocols();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCEmcDeviceModelFilesKey)
// 	{
// 		pNew = new CEmcDeviceModelFiles();
// 	}

	return pNew;
}

void CMonitorCapConfig::InitConfig()
{
	m_strFile = _P_GetConfigPath();
	m_strFile += _T("EpCapConfig.xml");
	
	BOOL b = OpenXmlFile(m_strFile, CMonitorCapConfigXmlRWKeys::CMonitorCapConfigKey(), CMonitorCapConfigXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
		InitAfterRead();
	}
}

void CMonitorCapConfig::SaveConfig()
{
	m_strFile = _P_GetConfigPath();
	m_strFile += _T("EpCapConfig.xml");
	SaveXmlFile(m_strFile, CMonitorCapConfigXmlRWKeys::g_pXmlKeys);
}

CExBaseObject* CMonitorCapConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCSERIALSCONFIG)
	{
		pNew = new CEmcSerialsConfig();
	}
// 	else if (nClassID == EMCCLASSID_CEMCNETSCONFIG)
// 	{
// 		pNew = new CEmcNetsConfig();
// 	}
	else if (nClassID == EMCCLASSID_CEMCNETDEVICES)
	{
		pNew = new CEmcNetDevices();
	}
// 	else if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOLS)
// 	{
// 		pNew = new CEmcQueryProtocols();
// 	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
