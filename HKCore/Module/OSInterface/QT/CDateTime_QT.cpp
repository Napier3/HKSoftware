#include "stdafx.h"
#include "CDateTime_QT.h"
#include <sys/types.h>

#ifdef _PSX_QT_LINUX_
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

CDateTime* CDateTime::g_pDataTime = NULL;

CDateTime::CDateTime()
{
	m_shm = NULL;
	m_nShareMemoryId = -1;
	m_nShmkey = 2023;
}

CDateTime::~CDateTime()
{
}

void CDateTime::ServerInit()
{
#ifdef _PSX_QT_LINUX_
	//需要申请共享内存
	m_nShareMemoryId = shmget((key_t)m_nShmkey, 24, 0666 | IPC_CREAT);

	if(m_nShareMemoryId == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Requset CDateTime ShareMemoryId Fail"));
	}

	m_shm = shmat(m_nShareMemoryId, (void *)0, 0);

	if(m_shm == (void *) -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Requset CDateTime ShareMemoryAddr Fail"));
	}
	else
	{
		memset(m_shm, 0, 24);
		unsigned int nFlag = FLAG_SERVER_INIT;
		memcpy(m_shm, &nFlag, 4);
	}
#endif
}

void CDateTime::SetDateZone(long nZone)
{
	if (g_pDataTime != NULL)
	{
		g_pDataTime->SetDateZone_In(nZone);
	}
}

void CDateTime::SetDateZone_In(long nZone)
{
	memcpy((char*)m_shm + 12, &nZone, 4);
}

void CDateTime::GetDateZone(long &nZone)
{
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag == FLAG_SERVER_INIT)
	{
		memcpy(&nZone, (char*)m_shm + 12, 4);
	}
	else
	{
		nZone = 0;
	}
}

void CDateTime::CreateClientDataTime()
{
	if (g_pDataTime == NULL)
	{
		g_pDataTime = new CDateTime;
		g_pDataTime->ClientInit();
	}
}

void CDateTime::ReleaseClientDataTime()
{
	if (g_pDataTime != NULL)
	{
		delete g_pDataTime;
		g_pDataTime = NULL;
	}
}


BOOL CDateTime::ClientInit()
{
#ifdef _PSX_QT_LINUX_
	m_nShareMemoryId = shmget((key_t)m_nShmkey, 24, 0666 | IPC_CREAT);

	if(m_nShareMemoryId == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "CDateTime ShareMemoryId fail");
	}

	m_shm = shmat(m_nShareMemoryId, (void *)0, 0);

	if(m_shm == (void *) -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "CDateTime ShareMemoryAddr fail");
		return FALSE;
	}
	else
	{
		unsigned int nFlag = 0;
		memcpy(&nFlag, m_shm, 4);
		if(nFlag == FLAG_SERVER_INIT)
		{
			return TRUE;
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, "CDateTime ServerInit fail");
			return FALSE;
		}
	}
#endif
	return TRUE;
}

void CDateTime::SetDateTime(long nSecond, long nNSecond)
{
	memcpy((char*)m_shm + 4, &nSecond, 4);
	memcpy((char*)m_shm + 8, &nNSecond, 4);
}

void CDateTime::GetDateTime(long &nSecond, long &nNSecond)
{
	if (g_pDataTime != NULL)
	{
		g_pDataTime->GetDateTime_In(nSecond,nNSecond);
	}
}

void CDateTime::GetDateTime_Zone0(long &nSecond, long &nNSecond)
{
	if (g_pDataTime != NULL)
	{
        g_pDataTime->GetDateTimeZone0_In(nSecond,nNSecond);
	}
}

void CDateTime::GetSystemTick(long &nSecond,long &nNSecond)
{
	if (g_pDataTime != NULL)
	{
		g_pDataTime->GetSystemTick_In(nSecond,nNSecond);
	}
}

void CDateTime::GetSystemTick_In(long &nSecond,long &nNSecond)
{
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag == FLAG_SERVER_INIT)
	{
		memcpy(&nSecond, (char*)m_shm + 16, 4);
		memcpy(&nNSecond, (char*)m_shm + 20, 4);
	}
	else
	{
		nSecond = 0;
		nNSecond = 0;
	}
}

void CDateTime::SetSystemTick(long nSecond,long nNSecond)
{
	memcpy((char*)m_shm + 16, &nSecond, 4);
	memcpy((char*)m_shm + 20, &nNSecond, 4);
}

void CDateTime::GetTime(int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec,int &nMs)
{
	if (g_pDataTime != NULL)
	{
		g_pDataTime->GetTime_In(nYear, nMon, nDay, nHour, nMin, nSec,nMs);
	}
}

void CDateTime::GetTime_BySecond(long nSecondCount,int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec)
{
	if (g_pDataTime != NULL)
	{
		g_pDataTime->GetTime_BySecond_In(nSecondCount,nYear, nMon, nDay, nHour, nMin, nSec);
	}
}

__int64 CDateTime::CurrentMSecsSinceEpoch()
{
	if (g_pDataTime != NULL)
	{
		return g_pDataTime->CurrentMSecsSinceEpoch_In();
	}

	return 0;
}

BOOL CDateTime::GetDateTime_HHMMSSZZZ(CString &strTimeString)
{
	if (g_pDataTime != NULL)
	{
		return g_pDataTime->GetDateTime_HHMMSSZZZ_In(strTimeString);
	}

	return FALSE;
}

BOOL CDateTime::GetDateTime_HHMMSSZZZ_In(CString &strTimeString)
{
	int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0;
	int nMs = 0;
	GetTime_In(nYear,nMon,nDay,nHour,nMin,nSec,nMs);
	strTimeString.Format(_T("%02d:%02d:%02d.%03d"),nHour,nMin,nSec,nMs);
	return TRUE;
}

BOOL CDateTime::GetDateTime_YYYYMMDD_HHMMSS(CString &strTimeString)
{
	if (g_pDataTime != NULL)
	{
		return g_pDataTime->GetDateTime_YYYYMMDD_HHMMSS_In(strTimeString);
	}

	return FALSE;
}

BOOL CDateTime::GetDateTime_YYYYMMDD_HHMMSSZZZ(CString &strTimeString)
{
	if (g_pDataTime != NULL)
	{
		return g_pDataTime->GetDateTime_YYYYMMDD_HHMMSSZZZ_In(strTimeString);
	}

	return FALSE;
}

BOOL CDateTime::GetDateTime_YYYYMMDD_HHMMSS_In(CString &strTimeString)
{
	int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0;
	int nMs = 0;
	GetTime_In(nYear,nMon,nDay,nHour,nMin,nSec,nMs);
	strTimeString.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),nYear,nMon,nDay,nHour,nMin,nSec);
	return TRUE;
}

BOOL CDateTime::GetDateTime_YYYYMMDD_HHMMSSZZZ_In(CString &strTimeString)
{
	int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0;
	int nMs = 0;
	GetTime_In(nYear,nMon,nDay,nHour,nMin,nSec,nMs);
	strTimeString.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),nYear,nMon,nDay,nHour,nMin,nSec,nMs);
	return TRUE;
}

void CDateTime::GetDateTime_In(long &nSecond,long &nNSecond)
{
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag == FLAG_SERVER_INIT)
	{
		memcpy(&nSecond, (char*)m_shm + 4, 4);
		memcpy(&nNSecond, (char*)m_shm + 8, 4);
	}
	else
	{
		nSecond = 0;
		nNSecond = 0;
	}
}

void CDateTime::GetDateTimeZone0_In(long &nSecond,long &nNSecond)
{
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag != FLAG_SERVER_INIT)
	{
		nSecond = 0;
		nNSecond = 0;
		return;
	}

	memcpy(&nSecond, (char*)m_shm + 4, 4);
	memcpy(&nNSecond, (char*)m_shm + 8, 4);
	long nZone = 0;
	memcpy(&nZone, (char*)m_shm + 12, 4);

	if ((nZone<-24)||(nZone > 24))
	{
		return;
	}

	if (nZone>= 0)
	{
		nSecond -= nZone*8*60*60;
	} 
	else
	{
		nSecond += nZone*8*60*60;
	}
}

__int64 CDateTime::CurrentMSecsSinceEpoch_In()
{
	long nSecond = 0,nNSecond = 0;
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag == FLAG_SERVER_INIT)
	{
		memcpy(&nSecond, (char*)m_shm + 4, 4);
		memcpy(&nNSecond, (char*)m_shm + 8, 4);
	}

	__int64 n64Value = nSecond;
	n64Value *= 1000;
	n64Value += (nNSecond/1000000);
	return n64Value;
}

static short g_oLeap_year[2][12] =
{
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

void CDateTime::GetTime_In(int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec,int &nMs)
{
	long ntime_t = 0,nNSecond = 0;
	unsigned int nFlag = 0;
	memcpy(&nFlag, m_shm, 4);
	if(nFlag == FLAG_SERVER_INIT)
	{
		memcpy(&ntime_t, (char*)m_shm + 4, 4);
		memcpy(&nNSecond, (char*)m_shm + 8, 4);
	}

	nMs = nNSecond/1000000;
	GetTime_BySecond_In(ntime_t,nYear,nMon,nDay,nHour,nMin,nSec);
}

void CDateTime::GetTime_BySecond_In(long nSecondCount,int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec)
{
	nYear = 1970;
	nMon = 1;
	nDay = 1;
	nHour = nMin = nSec = 0;

	while(TRUE)
	{
		int nIsLeap = 0;

		if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
		{
			nIsLeap = 1;
		}

		int nDiff = nIsLeap ? 366 : 365;

		if(nSecondCount >= nDiff * 24 * 60 * 60)
		{
			nYear += 1;
			nSecondCount -= nDiff * 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		int nIsLeap = 0;

		if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
		{
			nIsLeap = 1;
		}

		int nLastDay = g_oLeap_year[nIsLeap][nMon - 1];

		if(nSecondCount >= nLastDay * 24 * 60 * 60)
		{
			nMon += 1;
			nSecondCount -= nLastDay * 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(nSecondCount >= 24 * 60 * 60)
		{
			nDay += 1;
			nSecondCount -= 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(nSecondCount >= 60 * 60)
		{
			nHour += 1;
			nSecondCount -= 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(nSecondCount >= 60)
		{
			nMin += 1;
			nSecondCount -= 60;
		}
		else
		{
			break;
		}
	}

	nSec = nSecondCount;
}
