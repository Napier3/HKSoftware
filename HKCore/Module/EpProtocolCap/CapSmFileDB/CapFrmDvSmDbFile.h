//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapFrmDvSmDbFile.h  CCapFrmDvSmDbFile

#pragma once

#include "CapSmDbFile.h"


class CCapFrmDvSmDbArea : public CCapSmDbFileArea
{
public:
	CCapFrmDvSmDbArea();
	virtual ~CCapFrmDvSmDbArea();

	//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos);
	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer);

	//私有成员变量
private:
	long WriteFrame(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/);
	//long WriteDeviceData(CCapCycleMemBuffer *pBuffer, long nWritePos/*, EPSMDBFILEPOS &oSmDbFilePos*/);
	
//	void Write(EPDEVICEDATASMNGR &oData);
	BYTE m_pEpDeviceDatasBuffer[8192];

};

class CCapFrmDvSmDbFile : public CCapSmDbFile
{
public:
	CCapFrmDvSmDbFile();
	virtual ~CCapFrmDvSmDbFile();

	static const CString g_strCapFrmDvSmDbFile;
	static const CString g_strCapFrmDvSmDbID;

	CCapFrmDvSmDbArea *m_pFrameSmDbArea;

//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  EPSMDBFILEPOS &oSmDbFilePos)
	{
		LocatePos(oSmDbFilePos.n64CapFrmDvBeginPos, oSmDbFilePos.n64CapFrmDvCurrPos);
		m_pFrameSmDbArea->Write(pBufferMngr,  oSmDbFilePos);
		m_pFrameSmDbArea->UnMap();
	}

	void LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos);
	void CreateCapFrmDvSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	void CreateCapFrmDvSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	volatile __int64 GetCurrPos()	{		return m_pFrameSmDbArea->GetCurrPos();	}

	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer)
	{
		m_pFrameSmDbArea->ReadCapBuffer(pIndex, pBuffer);
	}

//私有成员变量
private:
};

