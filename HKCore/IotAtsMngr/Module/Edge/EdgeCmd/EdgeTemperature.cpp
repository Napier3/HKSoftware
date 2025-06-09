//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeTemperature.cpp  CEdgeTemperature


#include "stdafx.h"
#include "EdgeTemperature.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeTemperature::CEdgeTemperature()
{
	//初始化属性
	m_nTemLow = 0;
	m_nTemHigh = 0;

	//初始化成员变量
}

CEdgeTemperature::~CEdgeTemperature()
{
}

long CEdgeTemperature::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTemLowKey, oNode, m_nTemLow);
	xml_GetAttibuteValue(pXmlKeys->m_strTemHighKey, oNode, m_nTemHigh);

	AddErrorInfo(pXmlKeys->m_strTemLowKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strTemHighKey, oNode, CJSON_Int);
	return 0;
}

long CEdgeTemperature::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTemLowKey, oElement, m_nTemLow);
	xml_SetAttributeValue(pXmlKeys->m_strTemHighKey, oElement, m_nTemHigh);
	return 0;
}

long CEdgeTemperature::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nTemLow);
		BinarySerializeCalLen(oBinaryBuffer, m_nTemHigh);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nTemLow);
		BinarySerializeRead(oBinaryBuffer, m_nTemHigh);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nTemLow);
		BinarySerializeWrite(oBinaryBuffer, m_nTemHigh);
	}
	return 0;
}

void CEdgeTemperature::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pTemLow = new CExBaseList;
	pTemLow->m_strID = CEdgeCmdMngrXmlRWKeys::TemLowKey();
	pTemLow->m_strName.Format("%d", m_nTemLow);
	AddNewChild(pTemLow);

	CExBaseList* pTemHigh = new CExBaseList;
	pTemHigh->m_strID = CEdgeCmdMngrXmlRWKeys::TemHighKey();
	pTemHigh->m_strName.Format("%d", m_nTemHigh);
	AddNewChild(pTemHigh);
}

BOOL CEdgeTemperature::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeTemperature *p = (CEdgeTemperature*)pObj;

	if(m_nTemLow != p->m_nTemLow)
	{
		return FALSE;
	}

	if(m_nTemHigh != p->m_nTemHigh)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeTemperature::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeTemperature *p = (CEdgeTemperature*)pDest;

	p->m_nTemLow = m_nTemLow;
	p->m_nTemHigh = m_nTemHigh;
	return TRUE;
}

CBaseObject* CEdgeTemperature::Clone()
{
	CEdgeTemperature *p = new CEdgeTemperature();
	Copy(p);
	return p;
}

CBaseObject* CEdgeTemperature::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeTemperature *p = new CEdgeTemperature();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeTemperature::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeTemperature::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeTemperature::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
