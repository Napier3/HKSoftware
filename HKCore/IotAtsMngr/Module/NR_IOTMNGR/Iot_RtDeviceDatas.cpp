//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_RtDeviceDatas.cpp  CIot_RtDeviceDatas


#include "stdafx.h"
#include "Iot_RtDeviceDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RtDeviceDatas::CIot_RtDeviceDatas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIot_RtDeviceDatas::~CIot_RtDeviceDatas()
{
}

long CIot_RtDeviceDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RtDeviceDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RtDeviceDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_RtDeviceDatas::InitAfterRead()
{
}

BOOL CIot_RtDeviceDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RtDeviceDatas *p = (CIot_RtDeviceDatas*)pObj;

	return TRUE;
}

BOOL CIot_RtDeviceDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RtDeviceDatas *p = (CIot_RtDeviceDatas*)pDest;

	return TRUE;
}

CBaseObject* CIot_RtDeviceDatas::Clone()
{
	CIot_RtDeviceDatas *p = new CIot_RtDeviceDatas();
	Copy(p);
	return p;
}

CBaseObject* CIot_RtDeviceDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RtDeviceDatas *p = new CIot_RtDeviceDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_RtDeviceDatas::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CIot_RtDeviceDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CIot_RtDeviceDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
