//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgKey.cpp  CIecGenCfgKey


#include "stdafx.h"
#include "IecGenCfgKey.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgKey::CIecGenCfgKey()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgKey::~CIecGenCfgKey()
{
}

long CIecGenCfgKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CIecGenCfgKey::InitAfterRead()
{
}

BOOL CIecGenCfgKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgKey *p = (CIecGenCfgKey*)pObj;

	return TRUE;
}

BOOL CIecGenCfgKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenCfgKey *p = (CIecGenCfgKey*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgKey::Clone()
{
	CIecGenCfgKey *p = new CIecGenCfgKey();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgKey::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgKey *p = new CIecGenCfgKey();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgKey::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGCHILDKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenCfgKey::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgChildKeyKey)
	{
		pNew = new CIecGenCfgChildKey();
	}

	return pNew;
}

CExBaseObject* CIecGenCfgKey::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGCHILDKEY)
	{
		pNew = new CIecGenCfgChildKey();
	}

	return pNew;
}

BOOL CIecGenCfgKey::IsMatchSuccess(const CString &strName)
{
	if (GetCount() == 0)
	{
		if (strName.Find(m_strName)>=0)
		{
			return TRUE;
		}

		return FALSE;
	}

	CIecGenCfgChildKey *pChildKey = NULL;

	POS pos = GetHeadPosition();

	while(pos)
	{
		pChildKey = (CIecGenCfgChildKey *)GetNext(pos);

		if (!pChildKey->IsMatchSuccess(strName))//匹配失败,则返回FALSE
		{
			return FALSE;
		}
	}

	return TRUE;
}