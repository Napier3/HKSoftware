// DebugSpy.h: interface for the CDebugSpy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUGSPY_H__48A36DBA_503A_4573_93D7_1085286A8DDA__INCLUDED_)
#define AFX_DEBUGSPY_H__48A36DBA_503A_4573_93D7_1085286A8DDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BASECLASS\BaseList.h"

#define DEBUGDATA_ID_DEBUG   (CLASSID_BASECLASS+0X00000001)
#define DEBUGDATA_ID_DEBUG   (CLASSID_BASECLASS+0X00000001)


class CDebugData : public CBaseObject
{
public:
	CDebugData();
	virtual ~CDebugData();

	long m_dwBegin;
	long m_dwEnd;
	long  m_nIndex;
	long  m_nID;
 	long m_nPos;
	CString m_strInfor;

public:
	virtual UINT GetClassID()  {         return DEBUGDATA_ID_DEBUG;      }
	
	void GetEndTime()
	{
		m_dwEnd = ::GetTickCount();
	}

	void WriteFile(CFile *pFile);

};

class CDebugSpy : public CBaseList  
{
public:
	CDebugSpy();
	virtual ~CDebugSpy();

	virtual CBaseObject* CreateNewChild()                         {    return new CDebugData();     }
	virtual CBaseObject* CreateNewChild(LPCTSTR pszClassID)       {    return new CDebugData();     }
	virtual CBaseObject* CreateNewChild(long nClassID)            {    return new CDebugData();     }
	
public:
	long m_nIndex;
	CDebugData* Create(long nID, long nPos, const CString &strInfor);
	
	void AddDebugData(CDebugData *pData)
	{
		AddTail(pData);
	}

	void WriteDebugSpy(const CString &strFile);
};

#endif // !defined(AFX_DEBUGSPY_H__48A36DBA_503A_4573_93D7_1085286A8DDA__INCLUDED_)
