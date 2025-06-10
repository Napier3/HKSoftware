//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Fuc_Min.cpp  CSttGdColDef_Fuc_Min


#include "stdafx.h"
#include "SttGdColDef_Fuc_Min.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Fuc_Min::CSttGdColDef_Fuc_Min()
{
	//初始化属性

	//初始化成员变量
}

CSttGdColDef_Fuc_Min::~CSttGdColDef_Fuc_Min()
{
}

long CSttGdColDef_Fuc_Min::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Min::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Fuc_Min::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdColDef_Fuc_Min::InitAfterRead()
{
}

BOOL CSttGdColDef_Fuc_Min::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_Fuc_Min *p = (CSttGdColDef_Fuc_Min*)pObj;

	return TRUE;
}

BOOL CSttGdColDef_Fuc_Min::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_Fuc_Min *p = (CSttGdColDef_Fuc_Min*)pDest;

	return TRUE;
}

CBaseObject* CSttGdColDef_Fuc_Min::Clone()
{
	CSttGdColDef_Fuc_Min *p = new CSttGdColDef_Fuc_Min();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Fuc_Min::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Fuc_Min *p = new CSttGdColDef_Fuc_Min();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef_Fuc_Min::CanPaste(UINT nClassID)
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

CExBaseObject* CSttGdColDef_Fuc_Min::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

CExBaseObject* CSttGdColDef_Fuc_Min::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
