//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateDocExs.cpp  CIot_TemplateDocExs


#include "stdafx.h"
#include "Iot_TemplateDocExs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateDocExs::CIot_TemplateDocExs()
{
	//初始化属性

	//初始化成员变量
}

CIot_TemplateDocExs::~CIot_TemplateDocExs()
{
}

long CIot_TemplateDocExs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TemplateDocExs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TemplateDocExs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TemplateDocExs::InitAfterRead()
{
}

BOOL CIot_TemplateDocExs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TemplateDocExs *p = (CIot_TemplateDocExs*)pObj;

	return TRUE;
}

BOOL CIot_TemplateDocExs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TemplateDocExs *p = (CIot_TemplateDocExs*)pDest;

	return TRUE;
}

CBaseObject* CIot_TemplateDocExs::Clone()
{
	CIot_TemplateDocExs *p = new CIot_TemplateDocExs();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateDocExs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateDocExs *p = new CIot_TemplateDocExs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TemplateDocExs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEREPORTEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TemplateDocExs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceReportExKey)
	{
		pNew = new CIot_DeviceReportEx();
	}

	return pNew;
}

CExBaseObject* CIot_TemplateDocExs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEREPORTEX)
	{
		pNew = new CIot_DeviceReportEx();
	}

	return pNew;
}
CExBaseObject* CIot_TemplateDocExs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceReportEx();

	return pNew;
}
