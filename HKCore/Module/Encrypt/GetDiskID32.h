// GetDiskID32.h: interface for the CGetDiskID32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GetDiskID32_H__)
#define _GetDiskID32_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGetDiskID32
{
public:
	CGetDiskID32();
	virtual ~CGetDiskID32();

	void GetDiskID32();
	long GetDistID32Count();
	CString GetDiskID32(long nIndex);
	CString GetDiskID32Ex();

// Ù–‘∂®“Â
private:
	CStringArray m_astrDiskID32;
	
	void AddDiskID32(const CString &strDiskID32);

};


#endif // !defined(_GetDiskID32_H__)
