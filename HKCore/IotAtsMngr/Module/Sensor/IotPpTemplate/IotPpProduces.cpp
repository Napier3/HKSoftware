//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProduces.cpp  CIotPpProduces


#include "stdafx.h"
#include "IotPpProduces.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpProduces::CIotPpProduces()
{
	//初始化属性

	//初始化成员变量
}

CIotPpProduces::~CIotPpProduces()
{
}

long CIotPpProduces::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProduces::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProduces::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpProduces::InitAfterRead()
{
}

BOOL CIotPpProduces::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpProduces *p = (CIotPpProduces*)pObj;

	return TRUE;
}

BOOL CIotPpProduces::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpProduces *p = (CIotPpProduces*)pDest;

	return TRUE;
}

CBaseObject* CIotPpProduces::Clone()
{
	CIotPpProduces *p = new CIotPpProduces();
	Copy(p);
	return p;
}

CBaseObject* CIotPpProduces::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpProduces *p = new CIotPpProduces();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpProduces::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPPRODUCE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpProduces::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpProduceKey)
	{
		pNew = new CIotPpProduce();
	}

	return pNew;
}

CExBaseObject* CIotPpProduces::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPPRODUCE)
	{
		pNew = new CIotPpProduce();
	}

	return pNew;
}
