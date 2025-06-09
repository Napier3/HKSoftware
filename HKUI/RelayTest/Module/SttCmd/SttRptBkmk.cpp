//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttRptBkmk.cpp  CSttRptBkmk


#include "stdafx.h"
#include "SttRptBkmk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRptBkmk::CSttRptBkmk()
{
	//初始化属性

	//初始化成员变量
}

CSttRptBkmk::~CSttRptBkmk()
{
}

long CSttRptBkmk::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAttr_IdKey, oNode, m_strAttr_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strProcessKey, oNode, m_strProcess);
	xml_GetAttibuteValue(pXmlKeys->m_strFill_ModeKey, oNode, m_strFill_Mode);
	xml_GetAttibuteValue(pXmlKeys->m_strMgrp_CmbnKey, oNode, m_strMgrp_Cmbn);
	return 0;
}

long CSttRptBkmk::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAttr_IdKey, oElement, m_strAttr_Id);
	xml_SetAttributeValue(pXmlKeys->m_strProcessKey, oElement, m_strProcess);
	xml_SetAttributeValue(pXmlKeys->m_strFill_ModeKey, oElement, m_strFill_Mode);
	xml_SetAttributeValue(pXmlKeys->m_strMgrp_CmbnKey, oElement, m_strMgrp_Cmbn);
	return 0;
}

long CSttRptBkmk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAttr_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strProcess);
		BinarySerializeCalLen(oBinaryBuffer, m_strFill_Mode);
		BinarySerializeCalLen(oBinaryBuffer, m_strMgrp_Cmbn);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAttr_Id);
		BinarySerializeRead(oBinaryBuffer, m_strProcess);
		BinarySerializeRead(oBinaryBuffer, m_strFill_Mode);
		BinarySerializeRead(oBinaryBuffer, m_strMgrp_Cmbn);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAttr_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strProcess);
		BinarySerializeWrite(oBinaryBuffer, m_strFill_Mode);
		BinarySerializeWrite(oBinaryBuffer, m_strMgrp_Cmbn);
	}
	return 0;
}

void CSttRptBkmk::InitAfterRead()
{
}

BOOL CSttRptBkmk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttRptBkmk *p = (CSttRptBkmk*)pObj;

	if(m_strAttr_Id != p->m_strAttr_Id)
	{
		return FALSE;
	}

	if(m_strProcess != p->m_strProcess)
	{
		return FALSE;
	}

	if(m_strFill_Mode != p->m_strFill_Mode)
	{
		return FALSE;
	}

	if(m_strMgrp_Cmbn != p->m_strMgrp_Cmbn)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttRptBkmk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttRptBkmk *p = (CSttRptBkmk*)pDest;

	p->m_strAttr_Id = m_strAttr_Id;
	p->m_strProcess = m_strProcess;
	p->m_strFill_Mode = m_strFill_Mode;
	p->m_strMgrp_Cmbn = m_strMgrp_Cmbn;
	return TRUE;
}

CBaseObject* CSttRptBkmk::Clone()
{
	CSttRptBkmk *p = new CSttRptBkmk();
	Copy(p);
	return p;
}

CBaseObject* CSttRptBkmk::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttRptBkmk *p = new CSttRptBkmk();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

