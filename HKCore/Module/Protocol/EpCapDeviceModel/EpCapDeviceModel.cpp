//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDeviceModel.cpp  CEpCapDeviceModel


#include "stdafx.h"
#include "EpCapDeviceModel.h"

CEpCapDeviceModel::CEpCapDeviceModel()
{
	//初始化属性
	m_nYxAddr = 0;
	m_nYcAddr = 0;
	m_nYtAddr = 0;

	//初始化成员变量
	m_pEcdmDatas = NULL;
	m_pEcdmProtocolAddrs = NULL;
}

CEpCapDeviceModel::~CEpCapDeviceModel()
{
}

long CEpCapDeviceModel::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strYxAddrKey, oNode, m_nYxAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strYcAddrKey, oNode, m_nYcAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strYtAddrKey, oNode, m_nYtAddr);

	return 0;
}

long CEpCapDeviceModel::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strYxAddrKey, oElement, m_nYxAddr);
	xml_SetAttributeValue(pXmlKeys->m_strYcAddrKey, oElement, m_nYcAddr);
	xml_SetAttributeValue(pXmlKeys->m_strYtAddrKey, oElement, m_nYtAddr);

	return 0;
}

BOOL CEpCapDeviceModel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapDeviceModel *p = (CEpCapDeviceModel*)pObj;

	return TRUE;
}

BOOL CEpCapDeviceModel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapDeviceModel *p = (CEpCapDeviceModel*)pDest;

	return TRUE;
}

CBaseObject* CEpCapDeviceModel::Clone()
{
	CEpCapDeviceModel *p = new CEpCapDeviceModel();
	Copy(p);
	return p;
}

BOOL CEpCapDeviceModel::CanPaste(UINT nClassID)
{
	if (nClassID == ECDMCLASSID_CECDMPROTOCOLADDRS)
	{
		return TRUE;
	}

	if (nClassID == ECDMCLASSID_CECDMDATAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapDeviceModel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCEcdmDatasKey)
	{
		pNew = new CEcdmDatas();
	}
	else if (strClassID == pXmlKeys->m_strCEcdmProtocolAddrsKey)
	{
		pNew = new CEcdmProtocolAddrs();
	}

	return pNew;
}

CExBaseObject* CEpCapDeviceModel::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECDMCLASSID_CECDMDATAS)
	{
		pNew = new CEcdmDatas();
	}
// 	else if (nClassID == ECDMCLASSID_CECDMPROTOCOLADDRS)
// 	{
// 		pNew = new CEcdmProtocolAddrs();
// 	}

	return pNew;
}
void CEpCapDeviceModel::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ECDMCLASSID_CECDMDATAS)
		{
			m_pEcdmDatas = (CEcdmDatas*)p;
		}
		else if (nClassID == ECDMCLASSID_CECDMPROTOCOLADDRS)
		{
			m_pEcdmProtocolAddrs = (CEcdmProtocolAddrs*)p;
		}
	}

	if (m_pEcdmDatas == NULL)
	{
		m_pEcdmDatas = (CEcdmDatas*)AddNewChild(new CEcdmDatas());
	}

	if (m_pEcdmProtocolAddrs != NULL)
	{
		Delete(m_pEcdmProtocolAddrs);
		m_pEcdmProtocolAddrs = NULL;
	}
// 	if (m_pEcdmProtocolAddrs == NULL)
// 	{
// 		m_pEcdmProtocolAddrs = (CEcdmProtocolAddrs*)AddNewChild(new CEcdmProtocolAddrs());
// 	}

	InitAllDatasOffset();
}

void CEpCapDeviceModel::InitAllDatasOffset()
{
// 	CEcdmProtocolAddr *pAddr = (CEcdmProtocolAddr*)m_pEcdmProtocolAddrs->GetHead();
// 
// 	if (pAddr == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pEcdmDatas->InitOffset(pAddr->m_nYxAddr, pAddr->m_nYcAddr, pAddr->m_nYtAddr);
	m_pEcdmDatas->InitOffset(m_nYxAddr, m_nYcAddr, m_nYtAddr);
}

BOOL CEpCapDeviceModel::OpenDeviceModelFile(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

	CString strDvmFile;
	strDvmFile = _P_GetConfigPath();
	strDvmFile += strFile;

	return OpenXmlFile(strDvmFile, GetXmlElementKey(), CEpCapDeviceModelXmlRWKeys::g_pXmlKeys);
}

BOOL CEpCapDeviceModel::SaveDeviceModelFile()
{
	if (m_strID.GetLength() < 3)
	{
		return FALSE;
	}

	CString strDvmFile;
	strDvmFile = _P_GetConfigPath();
	strDvmFile += m_strID;

	return SaveXmlFile(strDvmFile, CEpCapDeviceModelXmlRWKeys::g_pXmlKeys);
}

CEpCapDeviceModels::CEpCapDeviceModels()
{

}

CEpCapDeviceModels::~CEpCapDeviceModels()
{

}

CEpCapDeviceModel* CEpCapDeviceModels::AddDeviceModels(const CString &strFile)
{
	if (strFile.GetLength() < 5)
	{
		return NULL;
	}

	CEpCapDeviceModel *pNew = new CEpCapDeviceModel();

	if (!pNew->OpenDeviceModelFile(strFile))
	{
		pNew->InitAfterRead();
		pNew->SaveDeviceModelFile();
	}

	AddNewChild(pNew);

	pNew->m_strName = strFile;
	pNew->m_strID = strFile;

	return pNew;
}

