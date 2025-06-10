//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIRef.cpp  CSttMacroTestUI_TestMacroUIRef


#include "stdafx.h"
#include "SttMacroTestUI_TestMacroUIRef.h"
#include "SttMacroTestUI_TestMacroUIDB.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestUI_TestMacroUIRef::CSttMacroTestUI_TestMacroUIRef()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroTestUI_TestMacroUIRef::~CSttMacroTestUI_TestMacroUIRef()
{
}

long CSttMacroTestUI_TestMacroUIRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestUI_TestMacroUIRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttMacroTestUI_TestMacroUIRef::InitAfterRead()
{
}

BOOL CSttMacroTestUI_TestMacroUIRef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttMacroTestUI_TestMacroUIRef *p = (CSttMacroTestUI_TestMacroUIRef*)pObj;

	return TRUE;
}

BOOL CSttMacroTestUI_TestMacroUIRef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttMacroTestUI_TestMacroUIRef *p = (CSttMacroTestUI_TestMacroUIRef*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroTestUI_TestMacroUIRef::Clone()
{
	CSttMacroTestUI_TestMacroUIRef *p = new CSttMacroTestUI_TestMacroUIRef();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_TestMacroUIRef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_TestMacroUIRef *p = new CSttMacroTestUI_TestMacroUIRef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CSttMacroTestUI_TestMacroUIRef::GetDefaultRepeatTimes()
{
	CSttMacroTestUI_TestMacroUIs* pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
	ASSERT(pUIs != NULL);

	CSttMacroTestUI_TestMacroUI* pUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(m_strID);

	if (pUI == NULL)
	{
		return 1;
	}

	return pUI->m_nDefaultRepeatTimes;
}