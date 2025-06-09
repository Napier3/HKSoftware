//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDataSmDbFile.h  CCapDataSmDbFile

#pragma once

#include "CapSmDbFile.h"


class CCapDataSmDbArea : public CCapSmDbFileArea
{
public:
	CCapDataSmDbArea();
	virtual ~CCapDataSmDbArea();

	//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos);
//	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer);

	//私有成员变量
private:
	long WriteDeviceData(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/);
	
//	void Write(EPDEVICEDATASMNGR &oData);
	BYTE m_pEpDeviceDatasBuffer[8192];

public:
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryIndex0Ranges &oIndex0Ranges, CEpDeviceDatasMngr &oQuery);

private:
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX0EX pIndex1, PEPCAPDBBUFFERINDEX0EX pIndex2, CEpDeviceDatasMngr &oQuery);
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, volatile __int64 &n64BeginPos, volatile __int64 &n64EndPos, CEpDeviceDatasMngr &oQuery);
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, EPCAPDBDATA *pIndex, CEpDeviceDatasMngr &oQuery);
	BOOL QueryAddr(EPCAPSEARCHCONFIG &oSearchConfig, EP_ETHER_CAP_IP_GROUP &ipGroup);

};

class CCapDataSmDbFile : public CCapSmDbFile
{
public:
	CCapDataSmDbFile();
	virtual ~CCapDataSmDbFile();

	static const CString g_strCapDataSmDbFile;
	static const CString g_strCapDataSmDbID;

	CCapDataSmDbArea *m_pFrameSmDbArea;

//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos)
	{
		LocatePos(oSmDbFilePos.n64CapDataBeginPos, oSmDbFilePos.n64CapDataCurrPos);
		m_pFrameSmDbArea->Write(pBufferMngr,  oSmDbFilePos);
		m_pFrameSmDbArea->UnMap();
	}

	void LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos);
	void CreateCapDataSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	void CreateCapDataSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	volatile __int64 GetCurrPos()	{		return m_pFrameSmDbArea->GetCurrPos();	}

// 	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer)
// 	{
// 		m_pFrameSmDbArea->ReadCapBuffer(pIndex, pBuffer);
// 	}

//私有成员变量
private:
};

