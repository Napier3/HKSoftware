//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceMergeReports.cpp  CIot_DeviceMergeReports


#include "stdafx.h"
#include "Iot_DeviceMergeReports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceMergeReports::CIot_DeviceMergeReports()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceMergeReports::~CIot_DeviceMergeReports()
{
}

long CIot_DeviceMergeReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceMergeReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceMergeReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceMergeReports::InitAfterRead()
{
}

BOOL CIot_DeviceMergeReports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceMergeReports *p = (CIot_DeviceMergeReports*)pObj;

	return TRUE;
}

BOOL CIot_DeviceMergeReports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceMergeReports *p = (CIot_DeviceMergeReports*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceMergeReports::Clone()
{
	CIot_DeviceMergeReports *p = new CIot_DeviceMergeReports();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceMergeReports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceMergeReports *p = new CIot_DeviceMergeReports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceMergeReports::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEMERGEREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceMergeReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceMergeReportKey)
	{
		pNew = new CIot_DeviceMergeReport();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceMergeReports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEMERGEREPORT)
	{
		pNew = new CIot_DeviceMergeReport();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceMergeReports::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceMergeReport();

	return pNew;
}
