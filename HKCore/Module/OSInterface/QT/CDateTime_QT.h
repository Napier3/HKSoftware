#ifndef _CDATETIME_QT_qt_h__
#define _CDATETIME_QT_qt_h__
#include "CString_QT.h"

//����6��������long�����ݣ��ֱ��ŷ���˳�ʼ����ɱ��
//�û�ʱ���µ��롢�û�ʱ���µ����롢�û�ѡ���ʱ��������������ʱ�����롢����������ʱ��������
#define FLAG_SERVER_INIT 0xeb90eb90

class CDateTime
{
public:
	CDateTime();
	virtual ~CDateTime();

	void ServerInit();//��ʱ�ķ����
	void GetDateZone(long &nZone);
	void SetDateTime(long nSecond,long nNSecond);//�����������
	void SetSystemTick(long nSecond,long nNSecond);//�����������

	static void CreateClientDataTime();//��ȡʱ��Ŀͻ���
	static void ReleaseClientDataTime();
	static void SetDateZone(long nZone);
	static void GetDateTime(long &nSecond,long &nNSecond);//��ȡ������룬������ϵͳ�������ص�ʱ��
	static void GetDateTime_Zone0(long &nSecond,long &nNSecond);//��ȡ��ʱ�����������
	static void GetSystemTick(long &nSecond,long &nNSecond);//��ȡ�������
	static BOOL GetDateTime_HHMMSSZZZ(CString &strTimeString);
	static BOOL GetDateTime_YYYYMMDD_HHMMSS(CString &strTimeString);
	static BOOL GetDateTime_YYYYMMDD_HHMMSSZZZ(CString &strTimeString);
	static void GetTime(int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec,int &nMs);
	static void GetTime_BySecond(long nSecondCount,int &nYear, int &nMon, int &nDay, int &nHour, int &nMin, int &nSec);
	static __int64 CurrentMSecsSinceEpoch();
protected:
	BOOL ClientInit();//��ȡʱ��Ŀͻ���
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
