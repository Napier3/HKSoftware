//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpExprSendTypes.cpp  CPpExprSendTypes


#include "stdafx.h"
#include "PpExprSendTypes.h"

CPpExprSendTypes::CPpExprSendTypes()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPpExprSendTypes::~CPpExprSendTypes()
{
}

long CPpExprSendTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprSendTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpExprSendTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpExprSendTypes::InitAfterRead()
{
}

BOOL CPpExprSendTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpExprSendTypes *p = (CPpExprSendTypes*)pObj;

	return TRUE;
}

BOOL CPpExprSendTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpExprSendTypes *p = (CPpExprSendTypes*)pDest;

	return TRUE;
}

CBaseObject* CPpExprSendTypes::Clone()
{
	CPpExprSendTypes *p = new CPpExprSendTypes();
	Copy(p);
	return p;
}

BOOL CPpExprSendTypes::CanPaste(UINT nClassID)
{
	if (nClassID == EXPCLASSID_CPPEXPRTYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpExprSendTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpExprTypeKey)
	{
		pNew = new CPpExprType();
	}

	return pNew;
}

CExBaseObject* CPpExprSendTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EXPCLASSID_CPPEXPRTYPE)
	{
		pNew = new CPpExprType();
	}

	return pNew;
}
