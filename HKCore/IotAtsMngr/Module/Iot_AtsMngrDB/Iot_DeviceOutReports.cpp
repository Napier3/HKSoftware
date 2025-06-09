//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceOutReports.cpp  CIot_DeviceOutReports


#include "stdafx.h"
#include "Iot_DeviceOutReports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceOutReports::CIot_DeviceOutReports()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceOutReports::~CIot_DeviceOutReports()
{
}

long CIot_DeviceOutReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceOutReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceOutReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceOutReports::InitAfterRead()
{
}

BOOL CIot_DeviceOutReports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceOutReports *p = (CIot_DeviceOutReports*)pObj;

	return TRUE;
}

BOOL CIot_DeviceOutReports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceOutReports *p = (CIot_DeviceOutReports*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceOutReports::Clone()
{
	CIot_DeviceOutReports *p = new CIot_DeviceOutReports();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceOutReports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceOutReports *p = new CIot_DeviceOutReports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceOutReports::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEOUTREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceOutReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceOutReportKey)
	{
		pNew = new CIot_DeviceOutReport();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceOutReports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEOUTREPORT)
	{
		pNew = new CIot_DeviceOutReport();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceOutReports::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceOutReport();

	return pNew;
}
