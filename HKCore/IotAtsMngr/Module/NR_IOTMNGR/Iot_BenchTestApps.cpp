//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_BenchTestApps.cpp  CIot_BenchTestApps


#include "stdafx.h"
#include "Iot_BenchTestApps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_BenchTestApps::CIot_BenchTestApps()
{
	//初始化属性

	//初始化成员变量
}

CIot_BenchTestApps::~CIot_BenchTestApps()
{
}

long CIot_BenchTestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_BenchTestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_BenchTestApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_BenchTestApps::InitAfterRead()
{
}

BOOL CIot_BenchTestApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_BenchTestApps *p = (CIot_BenchTestApps*)pObj;

	return TRUE;
}

BOOL CIot_BenchTestApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_BenchTestApps *p = (CIot_BenchTestApps*)pDest;

	return TRUE;
}

CBaseObject* CIot_BenchTestApps::Clone()
{
	CIot_BenchTestApps *p = new CIot_BenchTestApps();
	Copy(p);
	return p;
}

CBaseObject* CIot_BenchTestApps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_BenchTestApps *p = new CIot_BenchTestApps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_BenchTestApps::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCHTESTAPP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_BenchTestApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_BenchTestAppKey)
	{
		pNew = new CIot_BenchTestApp();
	}

	return pNew;
}

CExBaseObject* CIot_BenchTestApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_BENCHTESTAPP)
	{
		pNew = new CIot_BenchTestApp();
	}

	return pNew;
}
CExBaseObject* CIot_BenchTestApps::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_BenchTestApp();

	return pNew;
}
