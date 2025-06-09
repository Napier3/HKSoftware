//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIs.cpp  CSttMacroTestUI_TestMacroUIs


#include "stdafx.h"
#include "SttMacroTestUI_TestMacroUIs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestUI_TestMacroUIs::CSttMacroTestUI_TestMacroUIs()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroTestUI_TestMacroUIs::~CSttMacroTestUI_TestMacroUIs()
{
}

long CSttMacroTestUI_TestMacroUIs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttMacroTestUI_TestMacroUIs::InitAfterRead()
{
}

BOOL CSttMacroTestUI_TestMacroUIs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIs *p = (CSttMacroTestUI_TestMacroUIs*)pObj;

	return TRUE;
}

BOOL CSttMacroTestUI_TestMacroUIs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIs *p = (CSttMacroTestUI_TestMacroUIs*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroTestUI_TestMacroUIs::Clone()
{
	CSttMacroTestUI_TestMacroUIs *p = new CSttMacroTestUI_TestMacroUIs();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_TestMacroUIs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_TestMacroUIs *p = new CSttMacroTestUI_TestMacroUIs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroTestUI_TestMacroUIs::CanPaste(UINT nClassID)
{
	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMacroTestUI_TestMacroUIs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttMacroTestUI_TestMacroUIKey)
	{
		pNew = new CSttMacroTestUI_TestMacroUI();
	}

	return pNew;
}

CExBaseObject* CSttMacroTestUI_TestMacroUIs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUI)
	{
		pNew = new CSttMacroTestUI_TestMacroUI();
	}

	return pNew;
}
