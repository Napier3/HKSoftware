//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_Factorys.cpp  CAts_Wzd_Factorys


#include "stdafx.h"
#include "Ats_Wzd_Factorys.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_Factorys::CAts_Wzd_Factorys()
{
	//��ʼ������

	//��ʼ����Ա����
}

CAts_Wzd_Factorys::~CAts_Wzd_Factorys()
{
}

long CAts_Wzd_Factorys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_Factorys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_Factorys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_Factorys::InitAfterRead()
{
}

BOOL CAts_Wzd_Factorys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_Factorys *p = (CAts_Wzd_Factorys*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_Factorys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_Factorys *p = (CAts_Wzd_Factorys*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_Factorys::Clone()
{
	CAts_Wzd_Factorys *p = new CAts_Wzd_Factorys();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_Factorys::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_Factorys *p = new CAts_Wzd_Factorys();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_Factorys::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_FACTORY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_Factorys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_FactoryKey)
	{
		pNew = new CAts_Wzd_Factory();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_Factorys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_FACTORY)
	{
		pNew = new CAts_Wzd_Factory();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_Factorys::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_Factory();

	return pNew;
}
