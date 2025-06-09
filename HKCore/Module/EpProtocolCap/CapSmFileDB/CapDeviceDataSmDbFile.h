//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceDataSmDbFile.h  CCapDeviceDataSmDbFile

#pragma once

#include "CapSmDbFile.h"


class CCapDeviceDataSmDbArea : public CCapSmDbFileArea
{
public:
	CCapDeviceDataSmDbArea();
	virtual ~CCapDeviceDataSmDbArea();

public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos);

	//私有成员变量
private:
	__int64 Write(EPDEVICEDATASMNGR &oData);
	BYTE m_pEpDeviceDatasBuffer[9600];
};

class CCapDeviceDataSmDbFile : public CCapSmDbFile
{
public:
	CCapDeviceDataSmDbFile();
	virtual ~CCapDeviceDataSmDbFile();

	static const CString g_strDeviceDataSmDbFile;
	static const CString g_strDeviceDataSmDbID;

public:
	CCapDeviceDataSmDbArea      *m_pDeviceData;

public:
	void CreateDeviceDataSmDbServer(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	void LocatePos(__int64 n64BeginPos, __int64 n64CurrPos);

	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos)
	{
		m_pDeviceData->Write(pBufferMngr, posBegin, posEnd, oSmDbFilePos);
	}

	void CreateDeviceDataSmDbClient(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	__int64 GetCurrPos()	{		return m_pDeviceData->GetCurrPos();	}

//私有成员变量
private:
	CCapDeviceDataSmDbArea* CreateDbArea( __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize);
};

