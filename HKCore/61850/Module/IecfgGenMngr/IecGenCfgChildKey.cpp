//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgChildKey.cpp  CIecGenCfgChildKey


#include "stdafx.h"
#include "IecGenCfgChildKey.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgChildKey::CIecGenCfgChildKey()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgChildKey::~CIecGenCfgChildKey()
{
}

long CIecGenCfgChildKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLogicKey, oNode, m_strLogic);
	return 0;
}

long CIecGenCfgChildKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLogicKey, oElement, m_strLogic);
	return 0;
}

long CIecGenCfgChildKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLogic);
	}
	return 0;
}

void CIecGenCfgChildKey::InitAfterRead()
{
}

BOOL CIecGenCfgChildKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgChildKey *p = (CIecGenCfgChildKey*)pObj;

	if(m_strLogic != p->m_strLogic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenCfgChildKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenCfgChildKey *p = (CIecGenCfgChildKey*)pDest;

	p->m_strLogic = m_strLogic;
	return TRUE;
}

CBaseObject* CIecGenCfgChildKey::Clone()
{
	CIecGenCfgChildKey *p = new CIecGenCfgChildKey();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgChildKey::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgChildKey *p = new CIecGenCfgChildKey();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgChildKey::IsMatchSuccess(const CString &strName)
{
	CIecGenCfgChildKey *pChildKey = NULL;

	if (m_strLogic == _T("NOT"))//如果是非逻辑 
	{
		if (strName.Find(m_strName) >=0)//字符串中包含该子关键字则匹配失败
		{
			return FALSE;
		}

		return TRUE;//否则匹配成功
	}
	else if (strName.Find(m_strName) == -1)//如果是正常逻辑,则为与逻辑
	{
		return FALSE;//查找失败即匹配失败
	}

	return TRUE;
}

