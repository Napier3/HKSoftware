//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateFolders.cpp  CIot_TemplateFolders


#include "stdafx.h"
#include "Iot_TemplateFolders.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateFolders::CIot_TemplateFolders()
{
	//初始化属性

	//初始化成员变量
}

CIot_TemplateFolders::~CIot_TemplateFolders()
{
}

long CIot_TemplateFolders::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TemplateFolders::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TemplateFolders::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TemplateFolders::InitAfterRead()
{
}

BOOL CIot_TemplateFolders::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TemplateFolders *p = (CIot_TemplateFolders*)pObj;

	return TRUE;
}

BOOL CIot_TemplateFolders::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TemplateFolders *p = (CIot_TemplateFolders*)pDest;

	return TRUE;
}

CBaseObject* CIot_TemplateFolders::Clone()
{
	CIot_TemplateFolders *p = new CIot_TemplateFolders();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateFolders::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateFolders *p = new CIot_TemplateFolders();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TemplateFolders::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TemplateFolders::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TemplateFolderKey)
	{
		pNew = new CIot_TemplateFolder();
	}

	return pNew;
}

CExBaseObject* CIot_TemplateFolders::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		pNew = new CIot_TemplateFolder();
	}

	return pNew;
}
