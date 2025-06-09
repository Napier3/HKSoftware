//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdCondition.cpp  CSttGdCondition


#include "stdafx.h"
#include "SttGdCondition.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdCondition::CSttGdCondition()
{
	//初始化属性

	//初始化成员变量
}

CSttGdCondition::~CSttGdCondition()
{
}

long CSttGdCondition::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLogicKey, oNode, m_strLogic);
	return 0;
}

long CSttGdCondition::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLogicKey, oElement, m_strLogic);
	return 0;
}

long CSttGdCondition::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLogic);
	}
	return 0;
}

void CSttGdCondition::InitAfterRead()
{
}

BOOL CSttGdCondition::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdCondition *p = (CSttGdCondition*)pObj;

	if(m_strLogic != p->m_strLogic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdCondition::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdCondition *p = (CSttGdCondition*)pDest;

	p->m_strLogic = m_strLogic;
	return TRUE;
}

CBaseObject* CSttGdCondition::Clone()
{
	CSttGdCondition *p = new CSttGdCondition();
	Copy(p);
	return p;
}

CBaseObject* CSttGdCondition::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdCondition *p = new CSttGdCondition();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdCondition::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDPARACONDITION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdCondition::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdParaConditionKey)
	{
		pNew = new CSttGdParaCondition();
	}

	return pNew;
}

CExBaseObject* CSttGdCondition::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDPARACONDITION)
	{
		pNew = new CSttGdParaCondition();
	}

	return pNew;
}
