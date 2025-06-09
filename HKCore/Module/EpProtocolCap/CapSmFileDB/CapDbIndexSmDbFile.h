//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDbIndexSmDbFile.h  CCapDbIndexSmDbFile

#pragma once

#include "CapDbIndex0SmDbFile.h"

class CCapDbIndexSmDbArea : public CCapSmDbFileArea
{
public:
	CCapDbIndexSmDbArea();
	virtual ~CCapDbIndexSmDbArea();
	void CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize);

public:
//	volatile __int64 Write(CCapCycleMemBuffer *pBuffer);
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  CCapDbIndex0SmDbFile *pIndexSmDbFile, EPSMDBFILEPOS &oSmDbFilePos);
	volatile __int64 Write(EPCAPDBBUFFERINDEX &oIndex);

	volatile __int64 m_n64MaxIndexCount;

public:
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryIndex0Ranges &oIndex0Ranges, CEpQueryEpCapDbBufferIndex &oQuery);

private:
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX0EX pIndex1, PEPCAPDBBUFFERINDEX0EX pIndex2, CEpQueryEpCapDbBufferIndex &oQuery);
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, volatile __int64 &n64BeginPos, volatile __int64 &n64EndPos, CEpQueryEpCapDbBufferIndex &oQuery);
	long Query(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX pIndex, CEpQueryEpCapDbBufferIndex &oQuery);
	BOOL QueryAddr(EPCAPSEARCHCONFIG &oSearchConfig, EP_ETHER_CAP_IP_GROUP &ipGroup);
};

class CCapDbIndexSmDbFile : public CCapSmDbFile
{
public:
	CCapDbIndexSmDbFile();
	virtual ~CCapDbIndexSmDbFile();

	static const CString g_strCapSmDbIndexFile;
	static const CString g_strCapSmDbIndexID;

public:
	CCapDbIndexSmDbArea      *m_pDbIndex;
	volatile __int64   m_n64MaxIndexCount;

public:
	void CreateCapDbIndexSmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	void Write(CCapCycleMemBufferMngr *pBufferMngr,  CCapDbIndex0SmDbFile *pIndexSmDbFile, EPSMDBFILEPOS &oSmDbFilePos)
	{
		LocatePos(oSmDbFilePos.n64DbIndexBeginPos, oSmDbFilePos.n64DbIndexCurrPos);
		m_pDbIndex->Write(pBufferMngr, pIndexSmDbFile, oSmDbFilePos);
		m_pDbIndex->UnMap();
	}

	void CreateCapDbIndexSmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	volatile __int64 GetCurrPos()	{		return m_pDbIndex->GetCurrPos();	}
	void LocatePos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos);

	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer);

private:
};

