// Hashtable.h: interface for the CHashtable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHTABLE_H__CE4FEBF1_2B4F_476B_AD08_AD3E35DFA497__INCLUDED_)
#define AFX_HASHTABLE_H__CE4FEBF1_2B4F_476B_AD08_AD3E35DFA497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseObject\BaseObject.h"

class CHashKeyObj : public CBaseObject  
{
public:
	CHashKeyObj(const CString &strKey,long lKeyID)
	{
		m_strKey = strKey;
		m_lKeyID = lKeyID;			
	}
	virtual ~CHashKeyObj()
	{
	}
	
	CString m_strKey;
	long m_lKeyID;
	
private:
	CHashKeyObj()
	{
	}
};

class CHashtable : public CBaseObject  
{
public:
	CHashtable();
	virtual ~CHashtable();

	void Add(const CString &strKey,long lKeyID);
	void Add(long lKeyID,const CString &strKey);

	CString operator[] (long lKeyID);
	long operator[] (const CString &strKeyD);
	CString GetKey(long lKeyID);
	long GetKey(const CString &strKeyD);

private:
	CBaseObjectList m_listHashtable;
	CHashKeyObj* Find(long lKeyID);
	CHashKeyObj* Find(const CString &strKey);
};

#endif // !defined(AFX_HASHTABLE_H__CE4FEBF1_2B4F_476B_AD08_AD3E35DFA497__INCLUDED_)
