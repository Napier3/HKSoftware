//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpExprRcvTypes.cpp  CPpExprRcvTypes


#include "stdafx.h"
#include "PpExprRcvTypes.h"

CPpExprRcvTypes::CPpExprRcvTypes()
{
	//初始化属性

	//初始化成员变量
}

CPpExprRcvTypes::~CPpExprRcvTypes()
{
}

long CPpExprRcvTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprRcvTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprRcvTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpExprRcvTypes::InitAfterRead()
{
}

BOOL CPpExprRcvTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpExprRcvTypes *p = (CPpExprRcvTypes*)pObj;

	return TRUE;
}

BOOL CPpExprRcvTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpExprRcvTypes *p = (CPpExprRcvTypes*)pDest;

	return TRUE;
}

CBaseObject* CPpExprRcvTypes::Clone()
{
	CPpExprRcvTypes *p = new CPpExprRcvTypes();
	Copy(p);
	return p;
}

BOOL CPpExprRcvTypes::CanPaste(UINT nClassID)
{
	if (nClassID == EXPCLASSID_CPPEXPRTYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpExprRcvTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpExprTypeKey)
	{
		pNew = new CPpExprType();
	}

	return pNew;
}

CExBaseObject* CPpExprRcvTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EXPCLASSID_CPPEXPRTYPE)
	{
		pNew = new CPpExprType();
	}

	return pNew;
}
