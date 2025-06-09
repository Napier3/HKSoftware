// TickCount32.h: interface for the CTickCount32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TickCount32_H__)
#define TickCount32_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTickCount32  
{
public:
	 CTickCount32(bool bEnter);
    CTickCount32();
	virtual ~CTickCount32();

	void Enter();
	long GetTickCountLong(BOOL bUdate=TRUE);
	long CalTickCountLong(DWORD dwBeginTick);
	long CalTickCountLong2(DWORD dwBeginTick);
	DWORD DoEvents(long nMs);
	void EndDoEvents()	{	m_bEndDoEvents = TRUE;	}
	void LogTickCountLong(const CString &strTitle, BOOL bUdate=TRUE);

private:
	DWORD m_dwBeginTickCount;
	BOOL m_bEndDoEvents;

	long CalTickCountLong(DWORD dwEndTick, DWORD dwBeginTick);

	DWORD DoEvents_Win(long nMs);
	DWORD DoEvents_QT(long nMs);
};

#endif // !defined(TickCount32_H__)
