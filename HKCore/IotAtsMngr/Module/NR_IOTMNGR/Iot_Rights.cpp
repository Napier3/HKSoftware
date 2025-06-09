//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Rights.cpp  CIot_Rights


#include "stdafx.h"
#include "Iot_Rights.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Rights::CIot_Rights()
{
	//初始化属性

	//初始化成员变量
}

CIot_Rights::~CIot_Rights()
{
}

long CIot_Rights::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Rights::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Rights::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Rights::InitAfterRead()
{
}

BOOL CIot_Rights::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Rights *p = (CIot_Rights*)pObj;

	return TRUE;
}

BOOL CIot_Rights::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Rights *p = (CIot_Rights*)pDest;

	return TRUE;
}

CBaseObject* CIot_Rights::Clone()
{
	CIot_Rights *p = new CIot_Rights();
	Copy(p);
	return p;
}

CBaseObject* CIot_Rights::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Rights *p = new CIot_Rights();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Rights::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_RIGHT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Rights::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RightKey)
	{
		pNew = new CIot_Right();
	}

	return pNew;
}

CExBaseObject* CIot_Rights::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_RIGHT)
	{
		pNew = new CIot_Right();
	}

	return pNew;
}
CExBaseObject* CIot_Rights::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Right();

	return pNew;
}
