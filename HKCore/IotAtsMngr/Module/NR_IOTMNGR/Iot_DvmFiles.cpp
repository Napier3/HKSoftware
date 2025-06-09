//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DvmFiles.cpp  CIot_DvmFiles


#include "stdafx.h"
#include "Iot_DvmFiles.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DvmFiles::CIot_DvmFiles()
{
	//初始化属性

	//初始化成员变量
}

CIot_DvmFiles::~CIot_DvmFiles()
{
}

long CIot_DvmFiles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DvmFiles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DvmFiles::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DvmFiles::InitAfterRead()
{
}

BOOL CIot_DvmFiles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DvmFiles *p = (CIot_DvmFiles*)pObj;

	return TRUE;
}

BOOL CIot_DvmFiles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DvmFiles *p = (CIot_DvmFiles*)pDest;

	return TRUE;
}

CBaseObject* CIot_DvmFiles::Clone()
{
	CIot_DvmFiles *p = new CIot_DvmFiles();
	Copy(p);
	return p;
}

CBaseObject* CIot_DvmFiles::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DvmFiles *p = new CIot_DvmFiles();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DvmFiles::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DVMFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DvmFiles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DvmFileKey)
	{
		pNew = new CIot_DvmFile();
	}

	return pNew;
}

CExBaseObject* CIot_DvmFiles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DVMFILE)
	{
		pNew = new CIot_DvmFile();
	}

	return pNew;
}
CExBaseObject* CIot_DvmFiles::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DvmFile();

	return pNew;
}
