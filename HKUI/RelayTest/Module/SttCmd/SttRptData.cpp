//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttRptData.cpp  CSttRptData


#include "stdafx.h"
#include "SttRptData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRptData::CSttRptData()
{
	//初始化属性

	//初始化成员变量
}

CSttRptData::~CSttRptData()
{
}

long CSttRptData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPrecisionKey, oNode, m_strPrecision);
	return 0;
}

long CSttRptData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPrecisionKey, oElement, m_strPrecision);
	return 0;
}

long CSttRptData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPrecision);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPrecision);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPrecision);
	}
	return 0;
}

void CSttRptData::InitAfterRead()
{
}

BOOL CSttRptData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttRptData *p = (CSttRptData*)pObj;

	if(m_strPrecision != p->m_strPrecision)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttRptData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttRptData *p = (CSttRptData*)pDest;

	p->m_strPrecision = m_strPrecision;
	return TRUE;
}

CBaseObject* CSttRptData::Clone()
{
	CSttRptData *p = new CSttRptData();
	Copy(p);
	return p;
}

CBaseObject* CSttRptData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttRptData *p = new CSttRptData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttRptData::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTRPTBKMK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttRptData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttRptBkmkKey)
	{
		pNew = new CSttRptBkmk();
	}

	return pNew;
}

CExBaseObject* CSttRptData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTRPTBKMK)
	{
		pNew = new CSttRptBkmk();
	}

	return pNew;
}
