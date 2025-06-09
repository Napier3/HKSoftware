//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_RightPanes.cpp  CSttFrame_RightPanes


#include "stdafx.h"
#include "SttFrame_RightPanes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_RightPanes::CSttFrame_RightPanes()
{
	//初始化属性

	//初始化成员变量
	m_pSize = NULL;
}

CSttFrame_RightPanes::~CSttFrame_RightPanes()
{
}

long CSttFrame_RightPanes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_RightPanes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_RightPanes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CSttFrame_RightPanes::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
		{
			m_pSize = (CSttFrame_Size*)p;
		}
	}

	if (m_pSize == NULL)
	{
		m_pSize = (CSttFrame_Size*)AddNewChild(new CSttFrame_Size());
	}

}

BOOL CSttFrame_RightPanes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_RightPanes *p = (CSttFrame_RightPanes*)pObj;

	return TRUE;
}

BOOL CSttFrame_RightPanes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_RightPanes *p = (CSttFrame_RightPanes*)pDest;

	return TRUE;
}

CBaseObject* CSttFrame_RightPanes::Clone()
{
	CSttFrame_RightPanes *p = new CSttFrame_RightPanes();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_RightPanes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_RightPanes *p = new CSttFrame_RightPanes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_RightPanes::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_RightPanes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_SizeKey)
	{
		pNew = new CSttFrame_Size();
	}

	return pNew;
}

CExBaseObject* CSttFrame_RightPanes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
	{
		pNew = new CSttFrame_Size();
	}

	return pNew;
}
