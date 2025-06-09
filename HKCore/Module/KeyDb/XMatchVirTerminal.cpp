#include "stdafx.h"
#include "XMatchVirTerminal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchVirTerminal::CXMatchVirTerminal()
{

}

CXMatchVirTerminal::~CXMatchVirTerminal()
{
	m_listMatchInputKeys.DeleteAll();
	m_listMatchOutputKeys.DeleteAll();
}

bool CXMatchVirTerminal::Match(CString strInDesc ,CString strOutDesc ,CXKeyDB *pKeyDb  ,CString &strKeysDesc)
{
	ASSERT(pKeyDb != NULL);

	m_listMatchInputKeys.DeleteAll();
	m_listMatchOutputKeys.DeleteAll();

	pKeyDb->QueryKeys(strInDesc, &m_listMatchInputKeys);
	pKeyDb->QueryKeys(strOutDesc, &m_listMatchOutputKeys);

	if (Match(&m_listMatchInputKeys , &m_listMatchOutputKeys ,strKeysDesc))
	{
		return TRUE;
	}

	return FALSE;
}

bool CXMatchVirTerminal::Match(CXKeyMatchRefList *pInputXKeys, CXKeyMatchRefList *pOutputXKeys ,CString &strKeysDesc)
{
	ASSERT (pInputXKeys != NULL && pOutputXKeys != NULL);

	POS pos = pInputXKeys->GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	BOOL bIsSubKey = FALSE;

	while (pos != NULL)
	{
		p = pInputXKeys->GetNext(pos);

		bIsSubKey = pOutputXKeys->Match(p);

		if ((!bIsSubKey)&&(p->m_pXKeyRef != NULL))
		{
			if (p->m_pXKeyRef->m_nImportance == 100)
			{
				strKeysDesc += " ";
				strKeysDesc += p->m_pXKeyRef->m_strName;
			}
		}
	}

	pos = pOutputXKeys->GetHeadPosition();
	while (pos != NULL)
	{
		p = pOutputXKeys->GetNext(pos);

		bIsSubKey = pInputXKeys->Match(p);

		if ((!bIsSubKey)&&(p->m_pXKeyRef != NULL))
		{
			if (p->m_pXKeyRef->m_nImportance == 100)
			{
				strKeysDesc += " ";
				strKeysDesc += p->m_pXKeyRef->m_strName;
			}
		}
	}

	if (strKeysDesc.IsEmpty())
	{
		return TRUE;
	}

	return FALSE;
}