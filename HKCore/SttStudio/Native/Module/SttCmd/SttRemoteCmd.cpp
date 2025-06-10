//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttRemoteCmd.cpp  CSttRemoteCmd


#include "stdafx.h"
#include "SttRemoteCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRemoteCmd::CSttRemoteCmd()
{
	//初始化属性

	//初始化成员变量
	m_strTestor = g_strIDSoft;
}

CSttRemoteCmd::~CSttRemoteCmd()
{
}

long CSttRemoteCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestorKey, oNode, m_strTestor);
	return 0;
}

long CSttRemoteCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestorKey, oElement, m_strTestor);
	return 0;
}

long CSttRemoteCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttCmdBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTestor);
	}
	return 0;
}

BOOL CSttRemoteCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttRemoteCmd *p = (CSttRemoteCmd*)pObj;

	if(m_strTestor != p->m_strTestor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttRemoteCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttRemoteCmd *p = (CSttRemoteCmd*)pDest;

	p->m_strTestor = m_strTestor;
	return TRUE;
}

CBaseObject* CSttRemoteCmd::Clone()
{
	CSttRemoteCmd *p = new CSttRemoteCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttRemoteCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttRemoteCmd *p = new CSttRemoteCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttRemoteCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

long CSttRemoteCmd::GetRegisterMode()
{
	if (m_strTestor == STT_REGISTER_MODE_OWN)
	{
		return STT_SOCKET_TYPE_OWN;
	}

	return STT_SOCKET_TYPE_LOCAL;
}