//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Benchs.cpp  CIot_Benchs


#include "stdafx.h"
#include "Iot_Benchs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Benchs::CIot_Benchs()
{
	//初始化属性

	//初始化成员变量
}

CIot_Benchs::~CIot_Benchs()
{
}

long CIot_Benchs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Benchs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Benchs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Benchs::InitAfterRead()
{
}

BOOL CIot_Benchs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Benchs *p = (CIot_Benchs*)pObj;

	return TRUE;
}

BOOL CIot_Benchs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Benchs *p = (CIot_Benchs*)pDest;

	return TRUE;
}

CBaseObject* CIot_Benchs::Clone()
{
	CIot_Benchs *p = new CIot_Benchs();
	Copy(p);
	return p;
}

CBaseObject* CIot_Benchs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Benchs *p = new CIot_Benchs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Benchs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Benchs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_BenchKey)
	{
		pNew = new CIot_Bench();
	}

	return pNew;
}

CExBaseObject* CIot_Benchs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_BENCH)
	{
		pNew = new CIot_Bench();
	}

	return pNew;
}
CExBaseObject* CIot_Benchs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Bench();

	return pNew;
}
