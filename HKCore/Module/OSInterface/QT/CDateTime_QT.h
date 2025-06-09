#ifndef _CDATETIME_QT_qt_h__
#define _CDATETIME_QT_qt_h__
#include "CString_QT.h"

//申请6个连续的long型数据，分别存放服务端初始化完成标记
//用户时区下的秒、用户时区下的纳秒、用户选择的时区、开机后运行时长的秒、开机后运行时长的纳秒
#define FLAG_SERVER_INIT 0xeb90eb90

class CDateTime
{
public:
	CDateTime();
	virtual ~CDateTime();

	void ServerInit();//授时的服务端
	void GetDateZone(long &nZone);
	void SetDateTime(long nSecond,long nNSecond);//设置秒和纳秒
	void SetSystemTick(long nSecond,long nNSecond);//设置秒和纳秒

	static void CreateClientDataTime();//获取时间的客户端
	static void ReleaseClientDataTime();
	static void SetDateZone(long nZone);
	static void GetDateTime(long &nSecond,long &nNSecond);//获取秒和纳秒，已启用系统参数下载的时区
	static void GetDateTime_Zone0(long &nSecond,long &nNSecond);//获取零时区的秒和纳秒
	static void GetSystemTick(long &nSecond,long &nNSecond);//获取秒和纳秒
	static BOOL GetDateTime_HHMMSSZZZ(CString &strTimeString);
	static BOOL GetDateTime_YYYYMMDD_HHMMSS(CString &strTimeString);
	static BOOL GetDateTime_YYYYMMDD_HHMMSSZZZ(CString &strTimeString);
	static void GetTime(int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec,int &nMs);
	static void GetTime_BySecond(long nSecondCount,int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec);
	static __int64 CurrentMSecsSinceEpoch();
protected:
	BOOL ClientInit();//获取时间的客户端
	void SetDateZone_In(long nZone);
	void GetDateTime_In(long &nSecond,long &nNSecond);
	void GetDateTimeZone0_In(long &nSecond,long &nNSecond);
	void GetSystemTick_In(long &nSecond,long &nNSecond);
	BOOL GetDateTime_HHMMSSZZZ_In(CString &strTimeString);
	BOOL GetDateTime_YYYYMMDD_HHMMSS_In(CString &strTimeString);
	BOOL GetDateTime_YYYYMMDD_HHMMSSZZZ_In(CString &strTimeString);
	void GetTime_In(int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec,int &nMs);
	void GetTime_BySecond_In(long nSecondCount,int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec);
	__int64 CurrentMSecsSinceEpoch_In();
	static CDateTime* g_pDataTime;
	void *m_shm;// = NULL;
	int m_nShareMemoryId;// = -1;
	long m_nShmkey;// = 1234;
};

#endif
