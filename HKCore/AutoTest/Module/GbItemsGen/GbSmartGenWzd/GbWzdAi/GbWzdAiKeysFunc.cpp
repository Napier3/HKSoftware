#include "StdAfx.h"
#include "GbWzdAiKeysFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CGbAiKeysFunc::CGbAiKeysFunc(void)
{
	m_strName = _T("Func");
	m_strID= _T("Func");
}

CGbAiKeysFunc::~CGbAiKeysFunc(void)
{
}

long CGbAiKeysFunc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbAiKeysFunc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CGbAiKeysFunc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbAiKeysFunc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataKeyKey)
	{
		return new CGbAiDataKey();
	}

	return NULL;
}

CExBaseObject* CGbAiKeysFunc::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiDATAKEY)
	{
		return new CGbAiDataKey();
	}

	return NULL;
}

void CGbAiKeysFunc::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	POS pos = GetHeadPosition();
	CGbAiDataKey *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiDataKey *)GetNext(pos);
		p->InitGbAiDataKey(pKeyDB);
	}
}

//MustHave
CGbAiKeysFuncMustHave::CGbAiKeysFuncMustHave(void)
{
	m_strName= _T("must-have");
	m_strID= _T("must-have");
}

CGbAiKeysFuncMustHave::~CGbAiKeysFuncMustHave(void)
{
}

CBaseObject* CGbAiKeysFuncMustHave::Clone()
{
	CGbAiKeysFuncMustHave* pGbWzdAiDataOptr = new CGbAiKeysFuncMustHave();
	Copy(pGbWzdAiDataOptr);

	return pGbWzdAiDataOptr;
}

DWORD CGbAiKeysFuncMustHave::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiDataKey *pKey = NULL;

	if (bAllMatchMode)
	{
		m_dwValue = 1;

		while (pos != NULL)
		{
			pKey = (CGbAiDataKey *)GetNext(pos);

			if (! pKey->Match(pXMatchObj))
			{
				m_dwValue = 0;
				break;
			}
		}
	}
	else
	{
		m_dwValue = 0;

		while (pos != NULL)
		{
			pKey = (CGbAiDataKey *)GetNext(pos);

			if (pKey->Match(pXMatchObj))
			{
				m_dwValue++;
			}
		}

		pXMatchObj->m_dwItemData = m_dwValue;
	}

	return m_dwValue;
}

//MustNotHave
CGbAiKeysFuncMustNotHave::CGbAiKeysFuncMustNotHave(void)
{
	m_strName= _T("must-not-have");
	m_strID= _T("must-not-have");
}

CGbAiKeysFuncMustNotHave::~CGbAiKeysFuncMustNotHave(void)
{
}

CBaseObject* CGbAiKeysFuncMustNotHave::Clone()
{
	CGbAiKeysFuncMustNotHave* pGbWzdAiDataOptr = new CGbAiKeysFuncMustNotHave();
	Copy(pGbWzdAiDataOptr);

	return pGbWzdAiDataOptr;
}


DWORD CGbAiKeysFuncMustNotHave::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiDataKey *pKey = NULL;
	m_dwValue = 1;

	while (pos != NULL)
	{
		pKey = (CGbAiDataKey *)GetNext(pos);

		if (pKey->Match(pXMatchObj))
		{
			m_dwValue = 0;
			break;
		}
	}

	return m_dwValue;
}
