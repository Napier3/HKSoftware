//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndPageRefMngr.cpp  CUIWndPageRefMngr


#include "stdafx.h"
#include "UIWndPagesDef.h"

CUIWndPagesDef::CUIWndPagesDef()
{
	//��ʼ������

	//��ʼ����Ա����
}

CUIWndPagesDef::~CUIWndPagesDef()
{
	
}

long CUIWndPagesDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	
	return 0;
}

long CUIWndPagesDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CUIWndPagesDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CUIWndPagesDef::InitAfterRead()
{
}

BOOL CUIWndPagesDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIWndPagesDef *p = (CUIWndPagesDef*)pObj;

	return TRUE;
}

BOOL CUIWndPagesDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWndPagesDef *p = (CUIWndPagesDef*)pDest;

	return TRUE;
}

CBaseObject* CUIWndPagesDef::Clone()
{
	CUIWndPagesDef *p = new CUIWndPagesDef();
	Copy(p);
	return p;
}

BOOL CUIWndPagesDef::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIWNDPAGEDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIWndPagesDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIWndPageDefKey)
	{
		pNew = new CUIWndPageDef();
	}

	return pNew;
}

CExBaseObject* CUIWndPagesDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIWNDPAGEDEF)
	{
		pNew = new CUIWndPageDef();
	}

	return pNew;
}


CUIWndPage* CUIWndPagesDef::FindPage(const CString &strPageID)
{
	CUIWndPageDef *pPageDef = (CUIWndPageDef*)FindByID(strPageID);

	if (pPageDef == NULL)
	{
		return NULL;
	}

	return pPageDef->GetPage();
}

