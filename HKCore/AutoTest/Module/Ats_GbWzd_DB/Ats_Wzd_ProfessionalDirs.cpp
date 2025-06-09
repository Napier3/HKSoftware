//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_ProfessionalDirs.cpp  CAts_Wzd_ProfessionalDirs


#include "stdafx.h"
#include "Ats_Wzd_ProfessionalDirs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_ProfessionalDirs::CAts_Wzd_ProfessionalDirs()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_ProfessionalDirs::~CAts_Wzd_ProfessionalDirs()
{
}

long CAts_Wzd_ProfessionalDirs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_ProfessionalDirs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_ProfessionalDirs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_ProfessionalDirs::InitAfterRead()
{
}

BOOL CAts_Wzd_ProfessionalDirs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_ProfessionalDirs *p = (CAts_Wzd_ProfessionalDirs*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_ProfessionalDirs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_ProfessionalDirs *p = (CAts_Wzd_ProfessionalDirs*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_ProfessionalDirs::Clone()
{
	CAts_Wzd_ProfessionalDirs *p = new CAts_Wzd_ProfessionalDirs();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_ProfessionalDirs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_ProfessionalDirs *p = new CAts_Wzd_ProfessionalDirs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_ProfessionalDirs::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_ProfessionalDirs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_ProfessionalDirKey)
	{
		pNew = new CAts_Wzd_ProfessionalDir();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_ProfessionalDirs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR)
	{
		pNew = new CAts_Wzd_ProfessionalDir();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_ProfessionalDirs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_ProfessionalDir();

	return pNew;
}
