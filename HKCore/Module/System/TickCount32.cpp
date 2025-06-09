// TickCount32.cpp: implementation of the CTickCount32 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TickCount32.h"

#ifdef _PSX_IDE_QT_
#include "../OSInterface/QT/XGlobalDefine_QT.h"
#include <QEventLoop>
#include <QTimer>
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTickCount32::CTickCount32(bool bEnter)
{
    if (bEnter)
    {
        Enter();
    }
    else
    {
        m_dwBeginTickCount = 0;
    }
	m_bEndDoEvents = FALSE;
}

CTickCount32::CTickCount32()
{
	Enter();
	m_bEndDoEvents = FALSE;
}

CTickCount32::~CTickCount32()
{
	
}

void CTickCount32::Enter()
{
//#ifndef _PSX_QT_LINUX_
	m_dwBeginTickCount = GetTickCount();
//#else
//	m_dwBeginTickCount = 0;
//#endif
}

long CTickCount32::GetTickCountLong(BOOL bUdate)
{
	DWORD dwEnd = GetTickCount();
	DWORD dwLong = 0;

	dwLong = CalTickCountLong(dwEnd, m_dwBeginTickCount);

	if (bUdate)
	{
		m_dwBeginTickCount = dwEnd;
	}

	return dwLong;
}

void CTickCount32::LogTickCountLong(const CString &strTitle, BOOL bUdate)
{
	long nLong = GetTickCountLong(bUdate);
	
#ifndef _no_use_CLogPrint
	if (strTitle.GetLength() > 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s: %d"), strTitle.GetString(), nLong);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%d"), nLong);
	}
#endif
}

long CTickCount32::CalTickCountLong(DWORD dwBeginTick)
{
	DWORD dwEnd = GetTickCount();
	return CalTickCountLong(dwEnd, dwBeginTick);
}

long CTickCount32::CalTickCountLong2(DWORD dwBeginTick)
{
	return CalTickCountLong(m_dwBeginTickCount, dwBeginTick);
}

DWORD CTickCount32::DoEvents(long nMs)
{
    DWORD keyCode=0;

#ifdef _PSX_IDE_QT_
	DoEvents_QT(nMs);
#else
	DoEvents_Win(nMs);
#endif

	return keyCode;
}

DWORD CTickCount32::DoEvents_QT(long nMs)
{
	DWORD keyCode=0;

#ifdef _PSX_IDE_QT_
	QEventLoop loop;
	QTimer::singleShot(nMs, &loop, SLOT(quit()));
	loop.exec();

#endif

	return keyCode;
}

DWORD CTickCount32::DoEvents_Win(long nMs)
{
	DWORD keyCode=0;

#ifndef _PSX_IDE_QT_
    Enter();

	MSG msg;

	while(GetTickCountLong(FALSE) <= nMs && keyCode==0)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_bEndDoEvents)
		{
			m_bEndDoEvents = FALSE;
			break;
		}
	}
#endif

	if ((GetTickCountLong(FALSE) - nMs) > 100 )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "DoEvent Error   nMs = %d  GetTickCountLong = %d", nMs, GetTickCountLong(FALSE));
	}
	return keyCode;
}

long CTickCount32::CalTickCountLong(DWORD dwEndTick, DWORD dwBeginTick)
{
	DWORD dwLong = 0;

	if (dwEndTick < dwBeginTick)
	{
		dwLong = 0xFFFFFFFF - dwBeginTick;
		dwLong += dwEndTick;
	}
	else
	{
		dwLong = dwEndTick - dwBeginTick;
	}

	return dwLong;
}

