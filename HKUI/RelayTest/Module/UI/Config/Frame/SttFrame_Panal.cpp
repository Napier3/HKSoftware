//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Panal.cpp  CSttFrame_Panal


#include "stdafx.h"
#include "SttFrame_Panal.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Panal::CSttFrame_Panal()
{
	//初始化属性

	//初始化成员变量
}

CSttFrame_Panal::~CSttFrame_Panal()
{
}

long CSttFrame_Panal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSttFrame_Panal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CSttFrame_Panal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CSttFrame_Panal::InitAfterRead()
{
}

BOOL CSttFrame_Panal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttFrame_Panal *p = (CSttFrame_Panal*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_Panal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttFrame_Panal *p = (CSttFrame_Panal*)pDest;

	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CSttFrame_Panal::Clone()
{
	CSttFrame_Panal *p = new CSttFrame_Panal();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Panal::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Panal *p = new CSttFrame_Panal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_Panal::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_BUTTON)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_DATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_Panal::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_ButtonKey)
	{
		pNew = new CSttFrame_Button();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_DataKey)
	{
		pNew = new CSttFrame_Data();
	}

	return pNew;
}

CExBaseObject* CSttFrame_Panal::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_BUTTON)
	{
		pNew = new CSttFrame_Button();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_DATA)
	{
		pNew = new CSttFrame_Data();
	}

	return pNew;
}

CSttFrame_Button* CSttFrame_Panal::FindBtnByID(const CString &strBtnID)
{
	CExBaseObject *pFind = FindByID(strBtnID);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->GetClassID() == MNGRCLASSID_CSTTFRAME_BUTTON)
	{
		return (CSttFrame_Button*)pFind;
	}
	else
	{
		return NULL;
	}
}

