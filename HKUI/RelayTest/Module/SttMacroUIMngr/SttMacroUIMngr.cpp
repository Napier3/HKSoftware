//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroUIMngr.cpp  SttMacroUIMngr


#include "stdafx.h"
#include "SttMacroUIMngr.h"
#include "..\SttGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroUIMngr::CSttMacroUIMngr()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroUIMngr::~CSttMacroUIMngr()
{
}

long CSttMacroUIMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroUIMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroUIMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttMacroUIMngr::InitAfterRead()
{
}

BOOL CSttMacroUIMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMacroUIMngr *p = (CSttMacroUIMngr*)pObj;

	return TRUE;
}

BOOL CSttMacroUIMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMacroUIMngr *p = (CSttMacroUIMngr*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroUIMngr::Clone()
{
	CSttMacroUIMngr *p = new CSttMacroUIMngr();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroUIMngr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroUIMngr *p = new CSttMacroUIMngr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroUIMngr::CanPaste(UINT nClassID)
{
	if (nClassID == UIMNGRCLASSID_UIGROUP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMacroUIMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strUIGroupKey)
	{
		pNew = new CUIGroup();
	}

	return pNew;
}

CExBaseObject* CSttMacroUIMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UIMNGRCLASSID_UIGROUP)
	{
		pNew = new CUIGroup();
	}

	return pNew;
}

BOOL CSttMacroUIMngr::OpenMacroUIMngrFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += STT_MACRO_UI_MNGR_RELAYTEST;

	return OpenXmlFile(strFile, CSttTestMacroUIMngrXmlRWKeys::g_pXmlKeys);
}
