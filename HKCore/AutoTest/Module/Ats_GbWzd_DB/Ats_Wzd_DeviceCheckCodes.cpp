//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_DeviceCheckCodes.cpp  CAts_Wzd_DeviceCheckCodes


#include "stdafx.h"
#include "Ats_Wzd_DeviceCheckCodes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceCheckCodes::CAts_Wzd_DeviceCheckCodes()
{
	//��ʼ������

	//��ʼ����Ա����
}

CAts_Wzd_DeviceCheckCodes::~CAts_Wzd_DeviceCheckCodes()
{
}

long CAts_Wzd_DeviceCheckCodes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceCheckCodes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceCheckCodes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_DeviceCheckCodes::InitAfterRead()
{
}

BOOL CAts_Wzd_DeviceCheckCodes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceCheckCodes *p = (CAts_Wzd_DeviceCheckCodes*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_DeviceCheckCodes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceCheckCodes *p = (CAts_Wzd_DeviceCheckCodes*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceCheckCodes::Clone()
{
	CAts_Wzd_DeviceCheckCodes *p = new CAts_Wzd_DeviceCheckCodes();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceCheckCodes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceCheckCodes *p = new CAts_Wzd_DeviceCheckCodes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_DeviceCheckCodes::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICECHECKCODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_DeviceCheckCodes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_DeviceCheckCodeKey)
	{
		pNew = new CAts_Wzd_DeviceCheckCode();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_DeviceCheckCodes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICECHECKCODE)
	{
		pNew = new CAts_Wzd_DeviceCheckCode();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_DeviceCheckCodes::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_DeviceCheckCode();

	return pNew;
}
