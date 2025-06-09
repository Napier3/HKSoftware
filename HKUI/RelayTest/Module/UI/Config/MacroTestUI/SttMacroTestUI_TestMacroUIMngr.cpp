//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIMngr.cpp  CSttMacroTestUI_TestMacroUIMngr


#include "stdafx.h"
#include "SttMacroTestUI_TestMacroUIMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestUI_TestMacroUIMngr::CSttMacroTestUI_TestMacroUIMngr()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroTestUI_TestMacroUIMngr::~CSttMacroTestUI_TestMacroUIMngr()
{
}

long CSttMacroTestUI_TestMacroUIMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttMacroTestUI_TestMacroUIMngr::InitAfterRead()
{
}

BOOL CSttMacroTestUI_TestMacroUIMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIMngr *p = (CSttMacroTestUI_TestMacroUIMngr*)pObj;

	return TRUE;
}

BOOL CSttMacroTestUI_TestMacroUIMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIMngr *p = (CSttMacroTestUI_TestMacroUIMngr*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroTestUI_TestMacroUIMngr::Clone()
{
	CSttMacroTestUI_TestMacroUIMngr *p = new CSttMacroTestUI_TestMacroUIMngr();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_TestMacroUIMngr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_TestMacroUIMngr *p = new CSttMacroTestUI_TestMacroUIMngr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroTestUI_TestMacroUIMngr::CanPaste(UINT nClassID)
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

CExBaseObject* CSttMacroTestUI_TestMacroUIMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

CExBaseObject* CSttMacroTestUI_TestMacroUIMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
