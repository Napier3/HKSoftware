//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroToolBar.cpp  CTestMacroToolBar


#include "stdafx.h"
#include "TestMacroToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacroToolBar::CTestMacroToolBar()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTestMacroToolBar::~CTestMacroToolBar()
{
}

long CTestMacroToolBar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTestMacroToolBar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTestMacroToolBar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTestMacroToolBar::InitAfterRead()
{
}

BOOL CTestMacroToolBar::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTestMacroToolBar *p = (CTestMacroToolBar*)pObj;

	return TRUE;
}

BOOL CTestMacroToolBar::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTestMacroToolBar *p = (CTestMacroToolBar*)pDest;

	return TRUE;
}

CBaseObject* CTestMacroToolBar::Clone()
{
	CTestMacroToolBar *p = new CTestMacroToolBar();
	Copy(p);
	return p;
}

CBaseObject* CTestMacroToolBar::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTestMacroToolBar *p = new CTestMacroToolBar();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTestMacroToolBar::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTESTMACROGROUP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTestMacroToolBar::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacroGroupKey)
	{
		pNew = new CTestMacroGroup();
	}

	return pNew;
}

CExBaseObject* CTestMacroToolBar::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTESTMACROGROUP)
	{
		pNew = new CTestMacroGroup();
	}

	return pNew;
}
