//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiberPara.cpp  CIecCfgFiberPara


#include "stdafx.h"
#include "IecCfgFiberPara.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgFiberPara::CIecCfgFiberPara()
{
	//初始化属性
	m_ntype = 1;

	//初始化成员变量
}

CIecCfgFiberPara::~CIecCfgFiberPara()
{
}

long CIecCfgFiberPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_ntype);
	return 0;
}

long CIecCfgFiberPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_ntype);
	return 0;
}

long CIecCfgFiberPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_ntype);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_ntype);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_ntype);
	}
	return 0;
}

void CIecCfgFiberPara::InitAfterRead()
{
}

BOOL CIecCfgFiberPara::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgFiberPara *p = (CIecCfgFiberPara*)pObj;

	if(m_ntype != p->m_ntype)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgFiberPara::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgFiberPara *p = (CIecCfgFiberPara*)pDest;

	p->m_ntype = m_ntype;
	return TRUE;
}

CBaseObject* CIecCfgFiberPara::Clone()
{
	CIecCfgFiberPara *p = new CIecCfgFiberPara();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgFiberPara::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgFiberPara *p = new CIecCfgFiberPara();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

