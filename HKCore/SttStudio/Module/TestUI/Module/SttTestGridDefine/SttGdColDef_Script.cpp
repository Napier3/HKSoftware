//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Script.cpp  CSttGdColDef_Script


#include "stdafx.h"
#include "SttGdColDef_Script.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Script::CSttGdColDef_Script()
{
	//初始化属性

	//初始化成员变量
}

CSttGdColDef_Script::~CSttGdColDef_Script()
{
}

long CSttGdColDef_Script::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_IdKey, oNode, m_strDataID);
	return 0;
}

long CSttGdColDef_Script::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_IdKey, oElement, m_strDataID);
	return 0;
}

long CSttGdColDef_Script::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataID);
	}
	return 0;
}

void CSttGdColDef_Script::InitAfterRead()
{
}

BOOL CSttGdColDef_Script::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdColDef_Script *p = (CSttGdColDef_Script*)pObj;

	if(m_strDataID != p->m_strDataID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef_Script::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdColDef_Script *p = (CSttGdColDef_Script*)pDest;

	p->m_strDataID = m_strDataID;
	return TRUE;
}

CBaseObject* CSttGdColDef_Script::Clone()
{
	CSttGdColDef_Script *p = new CSttGdColDef_Script();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Script::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Script *p = new CSttGdColDef_Script();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef_Script::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_AVG)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_MAX)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_MIN)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdColDef_Script::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDef_Fuc_AvgKey)
	{
		pNew = new CSttGdColDef_Fuc_Avg();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_Fuc_MaxKey)
	{
		pNew = new CSttGdColDef_Fuc_Max();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_Fuc_MinKey)
	{
		pNew = new CSttGdColDef_Fuc_Min();
	}

	return pNew;
}

CExBaseObject* CSttGdColDef_Script::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_AVG)
	{
		pNew = new CSttGdColDef_Fuc_Avg();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_MAX)
	{
		pNew = new CSttGdColDef_Fuc_Max();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_FUC_MIN)
	{
		pNew = new CSttGdColDef_Fuc_Min();
	}

	return pNew;
}
