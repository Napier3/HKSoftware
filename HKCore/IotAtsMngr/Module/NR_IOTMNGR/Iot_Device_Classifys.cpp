//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Device_Classifys.cpp  CIot_Device_Classifys


#include "stdafx.h"
#include "Iot_Device_Classifys.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Device_Classifys::CIot_Device_Classifys()
{
	//初始化属性

	//初始化成员变量
}

CIot_Device_Classifys::~CIot_Device_Classifys()
{
}

long CIot_Device_Classifys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Device_Classifys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Device_Classifys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Device_Classifys::InitAfterRead()
{
}

BOOL CIot_Device_Classifys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Device_Classifys *p = (CIot_Device_Classifys*)pObj;

	return TRUE;
}

BOOL CIot_Device_Classifys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Device_Classifys *p = (CIot_Device_Classifys*)pDest;

	return TRUE;
}

CBaseObject* CIot_Device_Classifys::Clone()
{
	CIot_Device_Classifys *p = new CIot_Device_Classifys();
	Copy(p);
	return p;
}

CBaseObject* CIot_Device_Classifys::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Device_Classifys *p = new CIot_Device_Classifys();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Device_Classifys::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Device_Classifys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_Device_ClassifyKey)
	{
		pNew = new CIot_Device_Classify();
	}

	return pNew;
}

CExBaseObject* CIot_Device_Classifys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		pNew = new CIot_Device_Classify();
	}

	return pNew;
}
CExBaseObject* CIot_Device_Classifys::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Device_Classify();

	return pNew;
}
