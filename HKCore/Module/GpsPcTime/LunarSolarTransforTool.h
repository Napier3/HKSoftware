#pragma once

typedef CArray <SYSTEMTIME> CArraySystemTime;

//ĳ�����й�����������
//extern CArraySystemTime g_ArrHoldayDates;

//debugģʽ�´�ӡ������Ϣ
void TraceDateInfo(CArraySystemTime &tmArr,const WORD &nBeginYear,const WORD &nEndYear
				   ,const CString &strInfo);
void TraceDateInfo(CArraySystemTime &tmArr,const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd
				   ,const CString &strInfo);

//�����������в���ָ�������Ƿ����
int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm);

BOOL IsTimeIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd);
BOOL IsDateIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd);
BOOL IsDuring_TimeInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const SYSTEMTIME &tmCurTime);
BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const SYSTEMTIME &tmCurTime);
BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const CTime &tmCurTime);

void GetDateString(SYSTEMTIME &tm,CString &strTime,BOOL bDayOfWeek=FALSE);
void GenrerateDateString(CArraySystemTime &tmArr,CString &strTime,BOOL bDayOfWeek=FALSE);

//�ж��Ƿ�������
BOOL IsLeapYear(WORD nYear);

WORD GetWeekDay(SYSTEMTIME &tm);

//��������nLunarYear��������·ݣ���û�з���0
long GetLeapMonth(WORD nLunarYear);

//��������nLunarYear��nLunarMonth�µ�����
long GetLunarMonthDays(WORD nLunarYear, WORD nLunarMonth);

//��������nLunarYear��ڶ������µ�������û�����·���0
long GetLunarLeapMonthDays(WORD nLunarYear);

//��ȡ����nLunarYear�괺�ڹ�������
BOOL GetLunarSpringDate(WORD nLunarYear, WORD &nSolarMonth, WORD &nSolarDay);

//������������Ƿ���ȷ
BOOL CheckLunarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay);

//������������Ƿ���ȷ
BOOL CheckSolarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay);

//����ת��������
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,WORD &nSolarYear, WORD &nSolarMonth, WORD &nSolarDay);
//����ת��������
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,SYSTEMTIME &tm);

//����ת��������
BOOL SolarToLunarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay
					  ,WORD &nLunarYear, WORD &nLunarMonth, WORD &nLunarDay);

//��ȡָ������
void GetFixedDate(const SYSTEMTIME &tmCurr,SYSTEMTIME &tmFixed,long nDays=1);

void InitPublicHoldayDate(WORD nYear,CArraySystemTime &tmArr);
void InitPublicHoldayDate(WORD nBeginYear,WORD nEndYear,CArraySystemTime &tmArrHoliday);

//���ؿ�ʼʱ�䡢����ʱ��֮�乲������
long GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday,const SYSTEMTIME &tmBegin
								,const SYSTEMTIME &tmEnd);

//��ʼʱ�䡢����ʱ��֮��������,����������tmArrUnExistDate��bFilterHoliday�Ƿ������Ϣ��
BOOL FilterUnExistDateArrBetweenDates(CArraySystemTime &tmArrExistDate
								,CArraySystemTime &tmArrUnExistDate
								,CArraySystemTime &tmArrHolidayDate
								,const SYSTEMTIME &tmBegin ,const SYSTEMTIME &tmEnd
								,BOOL bFilterHoliday=TRUE);

///////////////////////////////////////////////////////

void OA_GetTime(CDateTimeCtrl *pDateTimeCtrl, SYSTEMTIME &tmOA, BOOL bShortTime=TRUE);

//��ʼ�����ڿؼ�
void InitQueryBeginTime(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd,int nDays);
//���ʱ��ؼ��Ƿ���ȷ������mysql�����ַ���
BOOL CheckTimeIsRight(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd
					  ,const CString &strTmPK,CString &strFilter_Date);
BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd
					  ,const CString &strTmPK,CString &strFilter_Date);
BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd);
void ModifyQueryEndTime(SYSTEMTIME& tmEnd);