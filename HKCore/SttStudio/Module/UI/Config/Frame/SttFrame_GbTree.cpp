//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_GbTree.cpp  CSttFrame_GbTree


#include "stdafx.h"
#include "SttFrame_GbTree.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_GbTree::CSttFrame_GbTree()
{
	//初始化属性

	//初始化成员变量
	m_pFont = NULL;
	m_pSize = NULL;
}

CSttFrame_GbTree::~CSttFrame_GbTree()
{
}

long CSttFrame_GbTree::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_GbTree::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_GbTree::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttFrame_GbTree::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
		{
			m_pFont = (CSttFrame_Font*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
		{
			m_pSize = (CSttFrame_Size*)p;
		}
	}

	if (m_pFont == NULL)
	{
		m_pFont = (CSttFrame_Font*)AddNewChild(new CSttFrame_Font());
	}

	if (m_pSize == NULL)
	{
		m_pSize = (CSttFrame_Size*)AddNewChild(new CSttFrame_Size());
	}

}

BOOL CSttFrame_GbTree::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_GbTree *p = (CSttFrame_GbTree*)pObj;

	return TRUE;
}

BOOL CSttFrame_GbTree::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_GbTree *p = (CSttFrame_GbTree*)pDest;

	return TRUE;
}

CBaseObject* CSttFrame_GbTree::Clone()
{
	CSttFrame_GbTree *p = new CSttFrame_GbTree();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_GbTree::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_GbTree *p = new CSttFrame_GbTree();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_GbTree::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_GbTree::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_SizeKey)
	{
		pNew = new CSttFrame_Size();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_FontKey)
	{
		pNew = new CSttFrame_Font();
	}

	return pNew;
}

CExBaseObject* CSttFrame_GbTree::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_SIZE)
	{
		pNew = new CSttFrame_Size();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		pNew = new CSttFrame_Font();
	}

	return pNew;
}
