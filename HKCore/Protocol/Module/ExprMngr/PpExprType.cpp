//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpExprType.cpp  CPpExprType


#include "stdafx.h"
#include "PpExprType.h"

CPpExprType::CPpExprType()
{
	//初始化属性

	//初始化成员变量
}

CPpExprType::~CPpExprType()
{
}

long CPpExprType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpExprType::InitAfterRead()
{
}

BOOL CPpExprType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpExprType *p = (CPpExprType*)pObj;

	return TRUE;
}

BOOL CPpExprType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpExprType *p = (CPpExprType*)pDest;

	return TRUE;
}

CBaseObject* CPpExprType::Clone()
{
	CPpExprType *p = new CPpExprType();
	Copy(p);
	return p;
}

BOOL CPpExprType::CanPaste(UINT nClassID)
{
	if (nClassID == EXPCLASSID_CPPEXPR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpExprType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpExprKey)
	{
		pNew = new CPpExpr();
	}

	return pNew;
}

CExBaseObject* CPpExprType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EXPCLASSID_CPPEXPR)
	{
		pNew = new CPpExpr();
	}

	return pNew;
}
