//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroUI.cpp  MacroUI


#include "stdafx.h"
#include "MacroUI.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMacroUI::CMacroUI()
{
	//初始化属性

	//初始化成员变量
}

CMacroUI::~CMacroUI()
{
}

long CMacroUI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUi_TypeKey, oNode, m_strUIType);
	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_GenKey, oNode, m_strTemplateGen);
	return 0;
}

long CMacroUI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUi_TypeKey, oElement, m_strUIType);
	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_GenKey, oElement, m_strTemplateGen);
	return 0;
}

long CMacroUI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strUIType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplateGen);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strUIType);
		BinarySerializeRead(oBinaryBuffer, m_strFile);
		BinarySerializeRead(oBinaryBuffer, m_strTemplateGen);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strUIType);
		BinarySerializeWrite(oBinaryBuffer, m_strFile);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplateGen);
	}
	return 0;
}

void CMacroUI::InitAfterRead()
{
}

BOOL CMacroUI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMacroUI *p = (CMacroUI*)pObj;

	if(m_strUIType != p->m_strUIType)
	{
		return FALSE;
	}

	if(m_strFile != p->m_strFile)
	{
		return FALSE;
	}

	if(m_strTemplateGen != p->m_strTemplateGen)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMacroUI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMacroUI *p = (CMacroUI*)pDest;

	p->m_strUIType = m_strUIType;
	p->m_strFile = m_strFile;
	p->m_strTemplateGen = m_strTemplateGen;
	return TRUE;
}

CBaseObject* CMacroUI::Clone()
{
	CMacroUI *p = new CMacroUI();
	Copy(p);
	return p;
}

CBaseObject* CMacroUI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMacroUI *p = new CMacroUI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

