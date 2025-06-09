//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttContents.cpp  CSttContents


#include "stdafx.h"
#include "SttContents.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttContents::CSttContents()
{
	//初始化属性
}

CSttContents::~CSttContents()
{
}

BOOL CSttContents::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CSttContents *p = (CSttContents*)pDest;
	p->m_strText = m_strText;

	return TRUE;
}

CBaseObject* CSttContents::Clone()
{
	CSttContents *p = new CSttContents();
	Copy(p);
	return p;
}

CBaseObject* CSttContents::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttContents *p = new CSttContents();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttContents::CanPaste(UINT nClassID)
{
	return FALSE;
}


long CSttContents::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

    CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_GetCDATA(oNode, m_strText);

    return 0;
}

long CSttContents::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

    CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_SetCDATA(oXMLDoc, oElement, m_strText);
    return 0;
}


CExBaseObject* CSttContents::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}
