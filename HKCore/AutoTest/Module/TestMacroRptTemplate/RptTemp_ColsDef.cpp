//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ColsDef.cpp  CRptTemp_ColsDef


#include "stdafx.h"
#include "RptTemp_ColsDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ColsDef::CRptTemp_ColsDef()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_ColsDef::~CRptTemp_ColsDef()
{
}

long CRptTemp_ColsDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ColsDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ColsDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_ColsDef::InitAfterRead()
{
}

BOOL CRptTemp_ColsDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_ColsDef *p = (CRptTemp_ColsDef*)pObj;

	return TRUE;
}

BOOL CRptTemp_ColsDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_ColsDef *p = (CRptTemp_ColsDef*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_ColsDef::Clone()
{
	CRptTemp_ColsDef *p = new CRptTemp_ColsDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ColsDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ColsDef *p = new CRptTemp_ColsDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ColsDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_COLDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_ColsDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ColDefKey)
	{
		pNew = new CRptTemp_ColDef();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ColsDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_COLDEF)
	{
		pNew = new CRptTemp_ColDef();
	}

	return pNew;
}
