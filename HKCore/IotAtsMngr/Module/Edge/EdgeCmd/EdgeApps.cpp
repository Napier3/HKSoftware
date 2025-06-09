//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeApps.cpp  CEdgeApps


#include "stdafx.h"
#include "EdgeApps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeApps::CEdgeApps()
{
	//初始化属性
	m_nSrvNumber = 0;
	m_nLifeTime = 0;

	//初始化成员变量
	m_pEdgeProcess = NULL;
}

CEdgeApps::~CEdgeApps()
{
}

long CEdgeApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strAppHashKey, oNode, m_strAppHash);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvNumberKey, oNode, m_nSrvNumber);
	xml_GetAttibuteValue(pXmlKeys->m_strLifeTimeKey, oNode, m_nLifeTime);
	return 0;
}

long CEdgeApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strAppHashKey, oElement, m_strAppHash);
	xml_SetAttributeValue(pXmlKeys->m_strSrvNumberKey, oElement, m_nSrvNumber);
	xml_SetAttributeValue(pXmlKeys->m_strLifeTimeKey, oElement, m_nLifeTime);
	return 0;
}

long CEdgeApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strAppHash);
		BinarySerializeCalLen(oBinaryBuffer, m_nSrvNumber);
		BinarySerializeCalLen(oBinaryBuffer, m_nLifeTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strApp);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strAppHash);
		BinarySerializeRead(oBinaryBuffer, m_nSrvNumber);
		BinarySerializeRead(oBinaryBuffer, m_nLifeTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strAppHash);
		BinarySerializeWrite(oBinaryBuffer, m_nSrvNumber);
		BinarySerializeWrite(oBinaryBuffer, m_nLifeTime);
	}
	return 0;
}

void CEdgeApps::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGEPROCESS)
		{
			m_pEdgeProcess = (CEdgeProcess*)p;
		}
	}

	m_strID = GetXmlElementKey();

	CExBaseList* pApp = new CExBaseList;
	pApp->m_strID = CEdgeCmdMngrXmlRWKeys::AppKey();
	pApp->m_strName = m_strApp;
	AddNewChild(pApp);

	CExBaseList* pVersion = new CExBaseList;
	pVersion->m_strID = CEdgeCmdMngrXmlRWKeys::VersionKey();
	pVersion->m_strName = m_strVersion;
	AddNewChild(pVersion);

	CExBaseList* pAppHash = new CExBaseList;
	pAppHash->m_strID = CEdgeCmdMngrXmlRWKeys::AppHashKey();
	pAppHash->m_strName = m_strAppHash;
	AddNewChild(pAppHash);

	CExBaseList* pSrvNumber = new CExBaseList;
	pSrvNumber->m_strID = CEdgeCmdMngrXmlRWKeys::SrvNumberKey();
	pSrvNumber->m_strName.Format("%d", m_nSrvNumber);
	AddNewChild(pSrvNumber);

	CExBaseList* pLifeTime = new CExBaseList;
	pLifeTime->m_strID = CEdgeCmdMngrXmlRWKeys::LifeTimeKey();
	pLifeTime->m_strName.Format("%d", m_nLifeTime);
	AddNewChild(pLifeTime);
}

BOOL CEdgeApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeApps *p = (CEdgeApps*)pObj;

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strAppHash != p->m_strAppHash)
	{
		return FALSE;
	}

	if(m_nSrvNumber != p->m_nSrvNumber)
	{
		return FALSE;
	}

	if(m_nLifeTime != p->m_nLifeTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeApps *p = (CEdgeApps*)pDest;

	p->m_strApp = m_strApp;
	p->m_strVersion = m_strVersion;
	p->m_strAppHash = m_strAppHash;
	p->m_nSrvNumber = m_nSrvNumber;
	p->m_nLifeTime = m_nLifeTime;
	return TRUE;
}

CBaseObject* CEdgeApps::Clone()
{
	CEdgeApps *p = new CEdgeApps();
	Copy(p);
	return p;
}

CBaseObject* CEdgeApps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeApps *p = new CEdgeApps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeApps::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEPROCESS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeProcessKey)
	{
		pNew = new CEdgeProcess();
	}

	return pNew;
}

CExBaseObject* CEdgeApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEPROCESS)
	{
		pNew = new CEdgeProcess();
	}

	return pNew;
}
