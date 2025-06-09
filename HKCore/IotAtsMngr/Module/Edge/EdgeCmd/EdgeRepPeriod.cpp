//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeRepPeriod.cpp  CEdgeRepPeriod


#include "stdafx.h"
#include "EdgeRepPeriod.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeRepPeriod::CEdgeRepPeriod()
{
	//初始化属性
	m_nDevPeriod = -1;
	m_nConPeriod = -1;
	m_nAppPeriod = -1;
	m_nHeartPeriod = -1;

	//初始化成员变量
}

CEdgeRepPeriod::~CEdgeRepPeriod()
{
}

long CEdgeRepPeriod::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDevPeriodKey, oNode, m_nDevPeriod);
	xml_GetAttibuteValue(pXmlKeys->m_strConPeriodKey, oNode, m_nConPeriod);
	xml_GetAttibuteValue(pXmlKeys->m_strAppPeriodKey, oNode, m_nAppPeriod);
	xml_GetAttibuteValue(pXmlKeys->m_strHeartPeriodKey, oNode, m_nHeartPeriod);

	AddErrorInfo(pXmlKeys->m_strDevPeriodKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strConPeriodKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strAppPeriodKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strHeartPeriodKey, oNode, CJSON_Int);

	return 0;
}

long CEdgeRepPeriod::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;
 	if(m_nDevPeriod >= 0)
 		xml_SetAttributeValue(pXmlKeys->m_strDevPeriodKey, oElement, m_nDevPeriod);
 	if(m_nConPeriod >= 0)
 		xml_SetAttributeValue(pXmlKeys->m_strConPeriodKey, oElement, m_nConPeriod);
 	if(m_nAppPeriod >= 0)
 		xml_SetAttributeValue(pXmlKeys->m_strAppPeriodKey, oElement, m_nAppPeriod);
 	if(m_nHeartPeriod >= 0)
 		xml_SetAttributeValue(pXmlKeys->m_strHeartPeriodKey, oElement, m_nHeartPeriod);
	return 0;
}

long CEdgeRepPeriod::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nDevPeriod);
		BinarySerializeCalLen(oBinaryBuffer, m_nConPeriod);
		BinarySerializeCalLen(oBinaryBuffer, m_nAppPeriod);
		BinarySerializeCalLen(oBinaryBuffer, m_nHeartPeriod);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nDevPeriod);
		BinarySerializeRead(oBinaryBuffer, m_nConPeriod);
		BinarySerializeRead(oBinaryBuffer, m_nAppPeriod);
		BinarySerializeRead(oBinaryBuffer, m_nHeartPeriod);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nDevPeriod);
		BinarySerializeWrite(oBinaryBuffer, m_nConPeriod);
		BinarySerializeWrite(oBinaryBuffer, m_nAppPeriod);
		BinarySerializeWrite(oBinaryBuffer, m_nHeartPeriod);
	}
	return 0;
}

void CEdgeRepPeriod::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pDevPeriod = new CExBaseList;
	pDevPeriod->m_strID = CEdgeCmdMngrXmlRWKeys::DevPeriodKey();
	pDevPeriod->m_strName.Format("%d", m_nDevPeriod);
	AddNewChild(pDevPeriod);

	CExBaseList* pConPeriod = new CExBaseList;
	pConPeriod->m_strID = CEdgeCmdMngrXmlRWKeys::ConPeriodKey();
	pConPeriod->m_strName.Format("%d", m_nConPeriod);
	AddNewChild(pConPeriod);

	CExBaseList* pAppPeriod = new CExBaseList;
	pAppPeriod->m_strID = CEdgeCmdMngrXmlRWKeys::AppPeriodKey();
	pAppPeriod->m_strName.Format("%d", m_nAppPeriod);
	AddNewChild(pAppPeriod);

	CExBaseList* pHeartPeriod = new CExBaseList;
	pHeartPeriod->m_strID = CEdgeCmdMngrXmlRWKeys::HeartPeriodKey();
	pHeartPeriod->m_strName.Format("%d", m_nHeartPeriod);
	AddNewChild(pHeartPeriod);
}

BOOL CEdgeRepPeriod::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeRepPeriod *p = (CEdgeRepPeriod*)pObj;

	if(m_nDevPeriod != p->m_nDevPeriod)
	{
		return FALSE;
	}

	if(m_nConPeriod != p->m_nConPeriod)
	{
		return FALSE;
	}

	if(m_nAppPeriod != p->m_nAppPeriod)
	{
		return FALSE;
	}

	if(m_nHeartPeriod != p->m_nHeartPeriod)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeRepPeriod::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeRepPeriod *p = (CEdgeRepPeriod*)pDest;

	p->m_nDevPeriod = m_nDevPeriod;
	p->m_nConPeriod = m_nConPeriod;
	p->m_nAppPeriod = m_nAppPeriod;
	p->m_nHeartPeriod = m_nHeartPeriod;
	return TRUE;
}

CBaseObject* CEdgeRepPeriod::Clone()
{
	CEdgeRepPeriod *p = new CEdgeRepPeriod();
	Copy(p);
	return p;
}

CBaseObject* CEdgeRepPeriod::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeRepPeriod *p = new CEdgeRepPeriod();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeRepPeriod::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeRepPeriod::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeRepPeriod::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
