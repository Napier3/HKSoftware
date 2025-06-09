//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjustCmd.cpp  CSttAdjustCmd


#include "stdafx.h"
#include "SttAdjustCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttAdjustCmd::CSttAdjustCmd()
{
	//初始化属性

	//初始化成员变量
	m_strTestor = g_strIDSoft;
}

CSttAdjustCmd::~CSttAdjustCmd()
{
}

long CSttAdjustCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestorKey, oNode, m_strTestor);
	return 0;
}

long CSttAdjustCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestorKey, oElement, m_strTestor);
	return 0;
}

long CSttAdjustCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSttAdjustCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttAdjustCmd *p = (CSttAdjustCmd*)pObj;

	if(m_strTestor != p->m_strTestor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttAdjustCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttAdjustCmd *p = (CSttAdjustCmd*)pDest;

	p->m_strTestor = m_strTestor;
	return TRUE;
}

CBaseObject* CSttAdjustCmd::Clone()
{
	CSttAdjustCmd *p = new CSttAdjustCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttAdjustCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttAdjustCmd *p = new CSttAdjustCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttAdjustCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

// void CSttAdjustCmd::SetParameter(const CString &strMacroID, CDataGroup *pParas)
// {
// 	if (strMacroID.GetLength() > 0)
// 	{
// 		CSttMacro *pMacro = GetSttMacro();
// 		pMacro->SetParameter(strMacroID, pParas);
// 	}
// 	else
// 	{
// 		GetSttParas();
// 	}
// }