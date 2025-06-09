//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndTime.cpp  CUIWndTime


#include "stdafx.h"
#include "UIWndTime.h"

CUIWndTime::CUIWndTime()
{
	//初始化属性

	//初始化成员变量
}

CUIWndTime::~CUIWndTime()
{
}

long CUIWndTime::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndTime::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndTime::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CUIWndTime::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndTime::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndTime *p = (CUIWndTime*)pObj;

	return TRUE;
}

BOOL CUIWndTime::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndTime *p = (CUIWndTime*)pDest;

	return TRUE;
}

CBaseObject* CUIWndTime::Clone()
{
	CUIWndTime *p = new CUIWndTime();
	Copy(p);
	return p;
}

BOOL CUIWndTime::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndTime::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CUIWndTime::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
