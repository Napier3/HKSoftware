//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbFileCfg.cpp  CSmDbFileCfg


#include "stdafx.h"
#include "SmDbFileCfg.h"

CSmDbFileCfg::CSmDbFileCfg()
{
	//初始化属性
	m_nSize = 0;
	m_nView = 0;

	//初始化成员变量
}

CSmDbFileCfg::~CSmDbFileCfg()
{
}

long CSmDbFileCfg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	xml_GetAttibuteValue(pXmlKeys->m_strViewKey, oNode, m_nView);
	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);
	return 0;
}

long CSmDbFileCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	xml_SetAttributeValue(pXmlKeys->m_strViewKey, oElement, m_nView);
	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	return 0;
}


CExBaseObject* CSmDbFileCfg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapDbFileAreaKey)
	{
		pNew = new CEpCapDbFileArea();
	}

	return pNew;
}


long CSmDbFileCfg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nView);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSize);
		BinarySerializeRead(oBinaryBuffer, m_nView);
		BinarySerializeRead(oBinaryBuffer, m_strFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
		BinarySerializeWrite(oBinaryBuffer, m_nView);
		BinarySerializeWrite(oBinaryBuffer, m_strFile);
	}
	return 0;
}

void CSmDbFileCfg::InitAfterRead()
{
}

BOOL CSmDbFileCfg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSmDbFileCfg *p = (CSmDbFileCfg*)pObj;

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	if(m_nView != p->m_nView)
	{
		return FALSE;
	}

	if(m_strFile != p->m_strFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmDbFileCfg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSmDbFileCfg *p = (CSmDbFileCfg*)pDest;

	p->m_nSize = m_nSize;
	p->m_nView = m_nView;
	p->m_strFile = m_strFile;
	return TRUE;
}

CBaseObject* CSmDbFileCfg::Clone()
{
	CSmDbFileCfg *p = new CSmDbFileCfg();
	Copy(p);
	return p;
}

CString  CSmDbFileCfg::GetSmDBFilePath()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += m_strFile;

	return strFile;
}

//////////////////////////////////////////////////////////////////////////
//

CEpCapDbFileArea::CEpCapDbFileArea()
{
	//初始化属性
	m_nSize = 0;
	m_nView = 0;

	//初始化成员变量
}

CEpCapDbFileArea::~CEpCapDbFileArea()
{
}

long CEpCapDbFileArea::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	xml_GetAttibuteValue(pXmlKeys->m_strViewKey, oNode, m_nView);
	xml_GetAttibuteValue(pXmlKeys->m_strBeginPosKey, oNode, m_nBeginPos);

	return 0;
}

long CEpCapDbFileArea::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSmDbConfigXmlRWKeys *pXmlKeys = (CSmDbConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	xml_SetAttributeValue(pXmlKeys->m_strViewKey, oElement, m_nView);
	xml_SetAttributeValue(pXmlKeys->m_strBeginPosKey, oElement, m_nBeginPos);

	return 0;
}

long CEpCapDbFileArea::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nView);
		BinarySerializeCalLen(oBinaryBuffer, m_nBeginPos);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSize);
		BinarySerializeRead(oBinaryBuffer, m_nView);
		BinarySerializeRead(oBinaryBuffer, m_nBeginPos);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
		BinarySerializeWrite(oBinaryBuffer, m_nView);
		BinarySerializeWrite(oBinaryBuffer, m_nBeginPos);
	}
	return 0;
}

void CEpCapDbFileArea::InitAfterRead()
{
}

BOOL CEpCapDbFileArea::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpCapDbFileArea *p = (CEpCapDbFileArea*)pObj;

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	if(m_nView != p->m_nView)
	{
		return FALSE;
	}

	if(m_nBeginPos != p->m_nBeginPos)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapDbFileArea::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEpCapDbFileArea *p = (CEpCapDbFileArea*)pDest;

	p->m_nSize = m_nSize;
	p->m_nView = m_nView;
	p->m_nBeginPos = m_nBeginPos;

	return TRUE;
}

CBaseObject* CEpCapDbFileArea::Clone()
{
	CEpCapDbFileArea *p = new CEpCapDbFileArea();
	Copy(p);
	return p;
}

