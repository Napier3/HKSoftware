//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMsg.cpp  CSttMsg


#include "stdafx.h"
#include "SttMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMsg::CSttMsg()
{
	//初始化属性
	m_nLevel = 0;
	m_nType = 0;


	//初始化成员变量
}

CSttMsg::~CSttMsg()
{
}

long CSttMsg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    //2020-11-25  lijunqing
    xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_strTime);
	xml_GetAttibuteValue(pXmlKeys->m_strLevelKey, oNode, m_nLevel);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);

	xml_GetCDATA(oNode, m_strMsg,pXmlKeys->m_strContentKey);

	return 0;
}

long CSttMsg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    //2020-11-25  lijunqing
    xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_strTime);
	xml_SetAttributeValue(pXmlKeys->m_strLevelKey, oElement, m_nLevel);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);

	xml_SetCDATA(oXMLDoc,oElement, m_strMsg,pXmlKeys->m_strContentKey);

	return 0;
}

long CSttMsg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}
	return 0;
}

void CSttMsg::InitAfterRead()
{
}

BOOL CSttMsg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMsg *p = (CSttMsg*)pObj;

	if(m_strMsg != p->m_strMsg)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttMsg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMsg *p = (CSttMsg*)pDest;

	p->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CSttMsg::Clone()
{
	CSttMsg *p = new CSttMsg();
	Copy(p);
	return p;
}

CBaseObject* CSttMsg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMsg *p = new CSttMsg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

