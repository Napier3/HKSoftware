//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttJobGuide.cpp  CSttJobGuide


#include "stdafx.h"
#include "SttJobGuide.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttJobGuide::CSttJobGuide()
{
	//初始化属性

	//初始化成员变量
}

CSttJobGuide::~CSttJobGuide()
{
}

long CSttJobGuide::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttJobGuide::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttJobGuide::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

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

void CSttJobGuide::InitAfterRead()
{
	CSttItemBase::InitAfterRead();
}

BOOL CSttJobGuide::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttJobGuide *p = (CSttJobGuide*)pObj;

	return TRUE;
}

BOOL CSttJobGuide::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttJobGuide *p = (CSttJobGuide*)pDest;

	return TRUE;
}

CBaseObject* CSttJobGuide::Clone()
{
	CSttJobGuide *p = new CSttJobGuide();
	Copy(p);
	return p;
}

CBaseObject* CSttJobGuide::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttJobGuide *p = new CSttJobGuide();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttJobGuide::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttJobGuide::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttItemsKey)
	{
		pNew = new CSttItems();
	}
	else if (strClassID == pXmlKeys->m_strCSttSafetyKey)
	{
		pNew = new CSttSafety();
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttJobGuide::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		pNew = new CSttItems();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		pNew = new CSttSafety();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}
