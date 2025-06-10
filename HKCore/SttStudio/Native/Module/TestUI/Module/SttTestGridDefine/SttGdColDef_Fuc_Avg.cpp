//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Fuc_Avg.cpp  CSttGdColDef_Fuc_Avg


#include "stdafx.h"
#include "SttGdColDef_Fuc_Avg.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Fuc_Avg::CSttGdColDef_Fuc_Avg()
{
	//初始化属性

	//初始化成员变量
}

CSttGdColDef_Fuc_Avg::~CSttGdColDef_Fuc_Avg()
{
}

long CSttGdColDef_Fuc_Avg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Avg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Avg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttGdColDef_Fuc_Avg::InitAfterRead()
{
}

BOOL CSttGdColDef_Fuc_Avg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_Fuc_Avg *p = (CSttGdColDef_Fuc_Avg*)pObj;

	return TRUE;
}

BOOL CSttGdColDef_Fuc_Avg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_Fuc_Avg *p = (CSttGdColDef_Fuc_Avg*)pDest;

	return TRUE;
}

CBaseObject* CSttGdColDef_Fuc_Avg::Clone()
{
	CSttGdColDef_Fuc_Avg *p = new CSttGdColDef_Fuc_Avg();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Fuc_Avg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Fuc_Avg *p = new CSttGdColDef_Fuc_Avg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef_Fuc_Avg::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdColDef_Fuc_Avg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDef_TextCombKey)
	{
		pNew = new CSttGdColDef_TextComb();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_ParaKey)
	{
		pNew = new CSttGdColDef_Para();
	}

	return pNew;
}

CExBaseObject* CSttGdColDef_Fuc_Avg::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB)
	{
		pNew = new CSttGdColDef_TextComb();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		pNew = new CSttGdColDef_Para();
	}

	return pNew;
}
