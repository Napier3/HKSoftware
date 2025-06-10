//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataCmd.cpp  CSttXuiDataCmd


#include "stdafx.h"
#include "SttXuiDataCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataCmd::CSttXuiDataCmd()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataCmd::~CSttXuiDataCmd()
{
}

long CSttXuiDataCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strData_SrcKey, oNode, m_strData_Src);
	xml_GetAttibuteValue(pXmlKeys->m_strArgvKey, oNode, m_strArgv);
	return 0;
}

long CSttXuiDataCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strData_SrcKey, oElement, m_strData_Src);
	xml_SetAttributeValue(pXmlKeys->m_strArgvKey, oElement, m_strArgv);
	return 0;
}

long CSttXuiDataCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Src);
		BinarySerializeCalLen(oBinaryBuffer, m_strArgv);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strData_Src);
		BinarySerializeRead(oBinaryBuffer, m_strArgv);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Src);
		BinarySerializeWrite(oBinaryBuffer, m_strArgv);
	}

	return 0;
}

void CSttXuiDataCmd::InitAfterRead()
{
}

BOOL CSttXuiDataCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataCmd *p = (CSttXuiDataCmd*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strData_Src != p->m_strData_Src)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataCmd *p = (CSttXuiDataCmd*)pDest;

	p->m_strType = m_strType;
	p->m_strData_Src = m_strData_Src;
	return TRUE;
}

CBaseObject* CSttXuiDataCmd::Clone()
{
	CSttXuiDataCmd *p = new CSttXuiDataCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataCmd *p = new CSttXuiDataCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttXuiDataCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttXuiDataCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
