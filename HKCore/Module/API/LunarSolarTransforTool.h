#pragma once

typedef CArray <SYSTEMTIME> CArraySystemTime;

//ĳ�����й�����������
extern CArraySystemTime g_ArrHoldayDates;

//�����������в���ָ�������Ƿ����
int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm);

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
void GetFixedDate(SYSTEMTIME &tmCurr,long nDays=1);

void InitPublicHoldayDate(WORD nYear,CArraySystemTime &tmArr);

BOOL GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday
							  ,SYSTEMTIME tmBegin,SYSTEMTIME tmEnd);