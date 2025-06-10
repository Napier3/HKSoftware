//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttDebugCmd.cpp  CSttDebugCmd


#include "stdafx.h"
#include "SttDebugCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttDebugCmd::CSttDebugCmd()
{
	//初始化属性

	//初始化成员变量
	m_strTestor = STT_SOFT_ID_DEBUG;
}

CSttDebugCmd::~CSttDebugCmd()
{
}

long CSttDebugCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestorKey, oNode, m_strTestor);
	return 0;
}

long CSttDebugCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestorKey, oElement, m_strTestor);
	return 0;
}

long CSttDebugCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSttDebugCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttDebugCmd *p = (CSttDebugCmd*)pObj;

	if(m_strTestor != p->m_strTestor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttDebugCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttDebugCmd *p = (CSttDebugCmd*)pDest;

	p->m_strTestor = m_strTestor;
	return TRUE;
}

CBaseObject* CSttDebugCmd::Clone()
{
	CSttDebugCmd *p = new CSttDebugCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttDebugCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttDebugCmd *p = new CSttDebugCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttDebugCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

