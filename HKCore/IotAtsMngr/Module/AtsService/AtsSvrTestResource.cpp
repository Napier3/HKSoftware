//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestResource.cpp  CAtsSvrTestResource


#include "stdafx.h"
#include "AtsSvrTestResource.h"

CAtsSvrTestResource::CAtsSvrTestResource()
{
	//初始化属性

	//初始化成员变量
	m_pRsAllocDefMngr = NULL;
	m_pTestApp = NULL;
}

CAtsSvrTestResource::~CAtsSvrTestResource()
{
}

long CAtsSvrTestResource::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestResource::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestResource::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAtsSvrTestResource::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ATSVRCLASSID_CATSSVRRSALLOCDEFMNGR)
		{
			m_pRsAllocDefMngr = (CAtsSvrRsAllocDefMngr*)p;
		}
		else if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPP)
		{
			m_pTestApp = (CAtsSvrRsTestApp*)p;
		}
	}

	if (m_pRsAllocDefMngr == NULL)
	{
		m_pRsAllocDefMngr = (CAtsSvrRsAllocDefMngr*)AddNewChild(new CAtsSvrRsAllocDefMngr());
	}

	if (m_pTestApp == NULL)
	{
		m_pTestApp = (CAtsSvrRsTestApp*)AddNewChild(new CAtsSvrRsTestApp());
	}

}

BOOL CAtsSvrTestResource::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrTestResource *p = (CAtsSvrTestResource*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestResource::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrTestResource *p = (CAtsSvrTestResource*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestResource::Clone()
{
	CAtsSvrTestResource *p = new CAtsSvrTestResource();
	Copy(p);
	return p;
}

CExBaseObject* CAtsSvrTestResource::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrRsTestAppKey)
	{
		pNew = new CAtsSvrRsTestApp();
	}
	else if (strClassID == pXmlKeys->m_strCAtsSvrRsAllocDefMngrKey)
	{
		pNew = new CAtsSvrRsAllocDefMngr();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestResource::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPP)
	{
		pNew = new CAtsSvrRsTestApp();
	}
	else if (nClassID == ATSVRCLASSID_CATSSVRRSALLOCDEFMNGR)
	{
		pNew = new CAtsSvrRsAllocDefMngr();
	}

	return pNew;
}
