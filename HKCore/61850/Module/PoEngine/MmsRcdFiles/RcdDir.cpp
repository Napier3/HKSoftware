//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RcdDir.cpp  CRcdDir


#include "stdafx.h"
#include "RcdDir.h"

CRcdDir::CRcdDir()
{
	//初始化属性
	m_nDirSize = 0;
	m_fDirTime = 0;

	//初始化成员变量
}

CRcdDir::~CRcdDir()
{
}

long CRcdDir::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDirsizeKey, oNode, m_nDirSize);
	xml_GetAttibuteValue(pXmlKeys->m_strDirtimeKey, oNode, m_fDirTime);
	return 0;
}

long CRcdDir::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDirsizeKey, oElement, m_nDirSize);
	xml_SetAttributeValue(pXmlKeys->m_strDirtimeKey, oElement, m_fDirTime);
	return 0;
}

long CRcdDir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nDirSize);
		BinarySerializeCalLen(oBinaryBuffer, m_fDirTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nDirSize);
		BinarySerializeRead(oBinaryBuffer, m_fDirTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nDirSize);
		BinarySerializeWrite(oBinaryBuffer, m_fDirTime);
	}
	return 0;
}

void CRcdDir::InitAfterRead()
{
}

BOOL CRcdDir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRcdDir *p = (CRcdDir*)pObj;

	if(m_nDirSize != p->m_nDirSize)
	{
		return FALSE;
	}

	if(m_fDirTime != p->m_fDirTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRcdDir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRcdDir *p = (CRcdDir*)pDest;

	p->m_nDirSize = m_nDirSize;
	p->m_fDirTime = m_fDirTime;
	return TRUE;
}

CBaseObject* CRcdDir::Clone()
{
	CRcdDir *p = new CRcdDir();
	Copy(p);
	return p;
}

BOOL CRcdDir::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRCDDIR)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRCDFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRcdDir::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRcdDirKey)
	{
		pNew = new CRcdDir();
	}
	else if (strClassID == pXmlKeys->m_strCRcdFileKey)
	{
		pNew = new CRcdFile();
	}

	return pNew;
}

CExBaseObject* CRcdDir::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRCDDIR)
	{
		pNew = new CRcdDir();
	}
	else if (nClassID == MNGRCLASSID_CRCDFILE)
	{
		pNew = new CRcdFile();
	}

	return pNew;
}
