#include "stdafx.h"
#include "PpDevConfigDeviceModel.h"
//#include "..\Engine\DeviceModel\DeviceModelDefine.h"

long CPpDevConfigDeviceModel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strFileKey,oNode,m_strFile);
	xml_GetAttibuteValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strNameKey,oNode,m_strName);
	xml_GetAttibuteValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDebugDeviceFileKey,oNode,m_strDeviceFile);

	return 0;
}

long CPpDevConfigDeviceModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strFileKey, oElemen, m_strFile);
	xml_SetAttributeValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strNameKey,oElemen,m_strName);
	xml_SetAttributeValue(CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDebugDeviceFileKey,oElemen,m_strDeviceFile);

	return 0;
}

CExBaseObject* CPpDevConfigDeviceModel::GetDeviceModel()
{
// 	if (m_pDeviceModel != NULL)
// 	{
// 		return m_pDeviceModel;
// 	}
// 
// 	m_pDeviceModel = new CPpDeviceModelDefine();
// 	CString strFile;
// 	strFile = _P_GetConfigPath();
// 	strFile += m_strFile;
// 	m_pDeviceModel->OpenXmlFile(strFile, NULL, NULL);
// 	return m_pDeviceModel;
	return NULL;
}

