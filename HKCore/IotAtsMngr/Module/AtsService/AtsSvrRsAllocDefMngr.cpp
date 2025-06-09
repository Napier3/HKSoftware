//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsAllocDefMngr.cpp  CAtsSvrRsAllocDefMngr


#include "stdafx.h"
#include "AtsSvrRsAllocDefMngr.h"

CAtsSvrRsAllocDefMngr::CAtsSvrRsAllocDefMngr()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrRsAllocDefMngr::~CAtsSvrRsAllocDefMngr()
{
}

long CAtsSvrRsAllocDefMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrRsAllocDefMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrRsAllocDefMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CAtsSvrRsAllocDefMngr::InitAfterRead()
{
}

BOOL CAtsSvrRsAllocDefMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrRsAllocDefMngr *p = (CAtsSvrRsAllocDefMngr*)pObj;

	return TRUE;
}

BOOL CAtsSvrRsAllocDefMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrRsAllocDefMngr *p = (CAtsSvrRsAllocDefMngr*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrRsAllocDefMngr::Clone()
{
	CAtsSvrRsAllocDefMngr *p = new CAtsSvrRsAllocDefMngr();
	Copy(p);
	return p;
}

BOOL CAtsSvrRsAllocDefMngr::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRRSALLOCDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrRsAllocDefMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrRsAllocDefKey)
	{
		pNew = new CAtsSvrRsAllocDef();
	}

	return pNew;
}

CExBaseObject* CAtsSvrRsAllocDefMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRRSALLOCDEF)
	{
		pNew = new CAtsSvrRsAllocDef();
	}

	return pNew;
}
