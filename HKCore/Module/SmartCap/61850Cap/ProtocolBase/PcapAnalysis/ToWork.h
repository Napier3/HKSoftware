#pragma once
#include "DoMessage.h"
#include "..\..\..\..\..\Module\DataMngr\DvmDevice.h"

class CToWork
{
public:
	CToWork(void);

public:
	~CToWork(void);

	static CString GetAllStatisticInfor();
	static CString GetSMVStatisticInfor();
	static CString GetGooseStatisticInfor();

	static void GetDiffertSRCMac();
	static void StartToDo();
	static void GetMMSType();
	static void Get92TimeDiffStatisticsData();
	static void Get91TimeDiffStatisticsData();
	static void Get91SMVChannelDataToDrawWave();
	static void Get92SMVFactorChange();
	static void Get92SMVChannelDataToDrawWave();
	static void Get92AbnormalPos();
	static void GetGooseAbnormalPos();

	static void  GetGooseAbnormalPosToVector( Content &content  ,  CAbnormalPos &t_Abn);
	static void  GetAbnormalPosToVector( Content &content  ,  CAbnormalPos &t_Abn);
	static void  GetSMV92ChanFactorChange( Content &content);
	static void  GetMultiNoSync();	
	static void  GetTimeDifDataToVector( Content &content  ,  CTimeDifData &TimeDifData);

	static void  GetChanValueToVector92(Content &content  ,   CMacDifWaveData &t_Mac  ,   CAbnormalPos & t_Abn);
	static void  GetChanValueToVector91(Content &content  ,  CMacDifWaveData &t_Mac);
	static long  GetMaxValue(std::vector<int> & pChanData  ,  float & fFirstArc  ,  int &nZLNum);
	static  CString  GetTimeString(int nPacket);
	static UINT ExecuteAnalysis( );

	static void SetPacketFromXSmMemBuffe(BYTE *pBuffer,  int nBufferLen=0);
	static void ClearAllData();
	static CString GetErrorInfor( int m_ID,    int m_Type,   int m_CurSelContentType, int  &nPacketNO);
	static int   GetPacketCnt();
	static int   GetErrorCnt();

	BOOL  CreateThreadToAnalysis(BOOL bBuffer = FALSE, CString strFileName="");

private:
	static unsigned int WINAPI ThreadFunc(LPVOID lpParam);  //Ïß³Ìº¯Êý
};
