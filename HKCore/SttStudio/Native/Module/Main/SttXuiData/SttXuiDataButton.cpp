//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataButton.cpp  CSttXuiDataButton


#include "stdafx.h"
#include "SttXuiDataButton.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataButton::CSttXuiDataButton()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataButton::~CSttXuiDataButton()
{
}

long CSttXuiDataButton::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	return 0;
}

long CSttXuiDataButton::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	return 0;
}

long CSttXuiDataButton::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPic);
	}
	return 0;
}

void CSttXuiDataButton::InitAfterRead()
{
}

BOOL CSttXuiDataButton::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataButton *p = (CSttXuiDataButton*)pObj;

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataButton::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataButton *p = (CSttXuiDataButton*)pDest;

	p->m_strPic = m_strPic;
	return TRUE;
}

CBaseObject* CSttXuiDataButton::Clone()
{
	CSttXuiDataButton *p = new CSttXuiDataButton();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataButton::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataButton *p = new CSttXuiDataButton();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataButton::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATACMD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataButton::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataCmdKey)
	{
		pNew = new CSttXuiDataCmd();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataButton::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATACMD)
	{
		pNew = new CSttXuiDataCmd();
	}

	return pNew;
}
