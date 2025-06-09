//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DinWzdFromSclGinChs.cpp  CDinWzdFromSclGinChs


#include "stdafx.h"
#include "DinWzdFromSclGinChs.h"

CDinWzdFromSclGinChs::CDinWzdFromSclGinChs()
{
	//初始化属性

	//初始化成员变量
}

CDinWzdFromSclGinChs::~CDinWzdFromSclGinChs()
{
}

long CDinWzdFromSclGinChs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDinWzdFromSclGinChs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CDinWzdFromSclGinChs::InitAfterRead()
{
}

BOOL CDinWzdFromSclGinChs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDinWzdFromSclGinChs *p = (CDinWzdFromSclGinChs*)pObj;

	return TRUE;
}

BOOL CDinWzdFromSclGinChs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDinWzdFromSclGinChs *p = (CDinWzdFromSclGinChs*)pDest;

	return TRUE;
}

CBaseObject* CDinWzdFromSclGinChs::Clone()
{
	CDinWzdFromSclGinChs *p = new CDinWzdFromSclGinChs();
	Copy(p);
	return p;
}

CExBaseObject* CDinWzdFromSclGinChs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDinWzdFromSclGinChKey)
	{
		pNew = new CDinWzdFromSclGinCh();
	}

	return pNew;
}

CExBaseObject* CDinWzdFromSclGinChs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBWZDCLASSID_CDINWZDFROMSCLGINCH)
	{
		pNew = new CDinWzdFromSclGinCh();
	}

	return pNew;
}
