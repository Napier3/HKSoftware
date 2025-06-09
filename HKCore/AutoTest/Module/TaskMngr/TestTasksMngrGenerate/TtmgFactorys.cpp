//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgFactorys.cpp  CTtmgFactorys


#include "stdafx.h"
#include "TtmgFactorys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgFactorys::CTtmgFactorys()
{
	//初始化属性

	//初始化成员变量
}

CTtmgFactorys::~CTtmgFactorys()
{
}

long CTtmgFactorys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgFactorys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgFactorys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTtmgFactorys::InitAfterRead()
{
}

BOOL CTtmgFactorys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTtmgFactorys *p = (CTtmgFactorys*)pObj;

	return TRUE;
}

BOOL CTtmgFactorys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTtmgFactorys *p = (CTtmgFactorys*)pDest;

	return TRUE;
}

CBaseObject* CTtmgFactorys::Clone()
{
	CTtmgFactorys *p = new CTtmgFactorys();
	Copy(p);
	return p;
}

BOOL CTtmgFactorys::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGFACTORY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgFactorys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgFactoryKey)
	{
		pNew = new CTtmgFactory();
	}

	return pNew;
}

CExBaseObject* CTtmgFactorys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGFACTORY)
	{
		pNew = new CTtmgFactory();
	}

	return pNew;
}
