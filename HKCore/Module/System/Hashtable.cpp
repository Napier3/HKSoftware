// Hashtable.cpp: implementation of the CHashtable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Hashtable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHashtable::CHashtable()
{
	m_listHashtable.EndIt();
}

CHashtable::~CHashtable()
{
	m_listHashtable.EndIt();
}

void CHashtable::Add(const CString &strKey,long lKeyID)
{
	CHashKeyObj *p = NULL;
	
	p = Find(strKey);
	if (p != NULL)
		return;
	p = Find(lKeyID);
	if (p != NULL)
		return;
	
	p = new CHashKeyObj(strKey,lKeyID);
	m_listHashtable.AddTail(p);
}

void CHashtable::Add(long lKeyID,const CString &strKey)
{
	Add(strKey,lKeyID);
}

CString CHashtable::operator[] (long lKeyID)
{
	CString strKey("");
	CHashKeyObj *p = Find(lKeyID);
	if (p == NULL)
	{
		throw(-1);
	}
	else
	{
		strKey = p->m_strKey;
	}
	return strKey;
}

long CHashtable::operator[] (const CString &strKeyD)
{
	long lKeyID = 0;
	CHashKeyObj *p = Find(strKeyD);
	if (p == NULL)
	{
		throw(-1);
	}
	else
	{
		lKeyID = p->m_lKeyID;
	}
	return lKeyID;
}

CString CHashtable::GetKey(long lKeyID)
{
	return (*this)[lKeyID];
}

long CHashtable::GetKey(const CString &strKeyD)
{
	return (*this)[strKeyD];
}

CHashKeyObj* CHashtable::Find(long lKeyID)
{
	CHashKeyObj *pFind = NULL;
	CHashKeyObj *pTemp = NULL;

	POSITION pos = m_listHashtable.GetHeadPosition();
	while (pos != NULL)
	{
		pTemp = (CHashKeyObj*)m_listHashtable.GetNext(pos);
		if (pTemp->m_lKeyID == lKeyID)
		{
			pFind = pTemp;
			break;
		}
	}

	return pFind;
}

CHashKeyObj* CHashtable::Find(const CString &strKey)
{
	CHashKeyObj *pFind = NULL;
	CHashKeyObj *pTemp = NULL;
	
	POSITION pos = m_listHashtable.GetHeadPosition();
	while (pos != NULL)
	{
		pTemp = (CHashKeyObj*)m_listHashtable.GetNext(pos);
		if (pTemp->m_strKey == strKey)
		{
			pFind = pTemp;
			break;
		}
	}

	return pFind;
}

