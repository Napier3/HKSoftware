//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmContents.cpp  CDvmContents


#include "stdafx.h"
#include "DvmContents.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDvmContents::CDvmContents()
{
	//初始化属性
}

CDvmContents::~CDvmContents()
{
}

BOOL CDvmContents::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CDvmContents *p = (CDvmContents*)pDest;
	p->m_strText = m_strText;

	return TRUE;
}

CBaseObject* CDvmContents::Clone()
{
	CDvmContents *p = new CDvmContents();
	Copy(p);
	return p;
}

CBaseObject* CDvmContents::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CDvmContents *p = new CDvmContents();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CDvmContents::CanPaste(UINT nClassID)
{
	return FALSE;
}


long CDvmContents::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

    xml_GetCDATA(oNode, m_strText);

    return 0;
}

long CDvmContents::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

    xml_SetCDATA(oXMLDoc, oElement, m_strText);

    return 0;
}


CExBaseObject* CDvmContents::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}
