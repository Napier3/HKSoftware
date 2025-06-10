//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Fuc_Max.cpp  CSttGdColDef_Fuc_Max


#include "stdafx.h"
#include "SttGdColDef_Fuc_Max.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Fuc_Max::CSttGdColDef_Fuc_Max()
{
	//初始化属性

	//初始化成员变量
}

CSttGdColDef_Fuc_Max::~CSttGdColDef_Fuc_Max()
{
}

long CSttGdColDef_Fuc_Max::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Max::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Max::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdColDef_Fuc_Max::InitAfterRead()
{
}

BOOL CSttGdColDef_Fuc_Max::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_Fuc_Max *p = (CSttGdColDef_Fuc_Max*)pObj;

	return TRUE;
}

BOOL CSttGdColDef_Fuc_Max::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_Fuc_Max *p = (CSttGdColDef_Fuc_Max*)pDest;

	return TRUE;
}

CBaseObject* CSttGdColDef_Fuc_Max::Clone()
{
	CSttGdColDef_Fuc_Max *p = new CSttGdColDef_Fuc_Max();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Fuc_Max::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Fuc_Max *p = new CSttGdColDef_Fuc_Max();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef_Fuc_Max::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdColDef_Fuc_Max::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDef_ParaKey)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_TextCombKey)
	{
		pNew = new CSttGdColDef_TextComb();
	}

	return pNew;
}

CExBaseObject* CSttGdColDef_Fuc_Max::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB)
	{
		pNew = new CSttGdColDef_TextComb();
	}

	return pNew;
}
