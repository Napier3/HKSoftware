//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestTaskTestapps.cpp  CIot_TestTaskTestapps


#include "stdafx.h"
#include "Iot_TestTaskTestapps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestTaskTestapps::CIot_TestTaskTestapps()
{
	//初始化属性

	//初始化成员变量
}

CIot_TestTaskTestapps::~CIot_TestTaskTestapps()
{
}

long CIot_TestTaskTestapps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestTaskTestapps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestTaskTestapps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TestTaskTestapps::InitAfterRead()
{
}

BOOL CIot_TestTaskTestapps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestTaskTestapps *p = (CIot_TestTaskTestapps*)pObj;

	return TRUE;
}

BOOL CIot_TestTaskTestapps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestTaskTestapps *p = (CIot_TestTaskTestapps*)pDest;

	return TRUE;
}

CBaseObject* CIot_TestTaskTestapps::Clone()
{
	CIot_TestTaskTestapps *p = new CIot_TestTaskTestapps();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestTaskTestapps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestTaskTestapps *p = new CIot_TestTaskTestapps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TestTaskTestapps::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TESTTASKTESTAPP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TestTaskTestapps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TestTaskTestappKey)
	{
		pNew = new CIot_TestTaskTestapp();
	}

	return pNew;
}

CExBaseObject* CIot_TestTaskTestapps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TESTTASKTESTAPP)
	{
		pNew = new CIot_TestTaskTestapp();
	}

	return pNew;
}
CExBaseObject* CIot_TestTaskTestapps::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TestTaskTestapp();

	return pNew;
}
