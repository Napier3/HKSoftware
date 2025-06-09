//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_Group.cpp  CSttMacroTestUI_Group


#include "stdafx.h"
#include "SttMacroTestUI_Group.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestUI_Group::CSttMacroTestUI_Group()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroTestUI_Group::~CSttMacroTestUI_Group()
{
}

long CSttMacroTestUI_Group::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_Group::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_Group::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttMacroTestUI_Group::InitAfterRead()
{
}

BOOL CSttMacroTestUI_Group::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttMacroTestUI_Group *p = (CSttMacroTestUI_Group*)pObj;

	return TRUE;
}

BOOL CSttMacroTestUI_Group::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttMacroTestUI_Group *p = (CSttMacroTestUI_Group*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroTestUI_Group::Clone()
{
	CSttMacroTestUI_Group *p = new CSttMacroTestUI_Group();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_Group::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_Group *p = new CSttMacroTestUI_Group();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroTestUI_Group::CanPaste(UINT nClassID)
{
	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP)
	{
		return TRUE;
	}

	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMacroTestUI_Group::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttMacroTestUI_GroupKey)
	{
		pNew = new CSttMacroTestUI_Group();
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroTestUI_TestMacroUIRefKey)
	{
		pNew = new CSttMacroTestUI_TestMacroUIRef();
	}

	return pNew;
}

CExBaseObject* CSttMacroTestUI_Group::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP)
	{
		pNew = new CSttMacroTestUI_Group();
	}
	else if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF)
	{
		pNew = new CSttMacroTestUI_TestMacroUIRef();
	}

	return pNew;
}
