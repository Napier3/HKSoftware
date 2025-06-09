//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDbIndex0SmDbFile.h  CCapDbIndex0SmDbFile

#pragma once

#include "CapSmDbFile.h"

class CCapDbIndex0SmDbArea : public CCapSmDbFileArea
{
public:
	CCapDbIndex0SmDbArea();
	virtual ~CCapDbIndex0SmDbArea();

public:
	EPCAPDBINDEXHEAD m_oCapIndexHead;
	EPCAPDBBUFFERINDEX0MNGREX m_oIndex0Mngr;

public:
	BOOL IsNewCreate()	{	return m_bIsNewCreate;	}
	void AddIndex0(volatile __int64 &n64Pos, volatile __int64 &n64DataPos, EPTIME64 &tm, BOOL bWriteTail);
	void SetServer(BOOL bServer)
	{
		m_bServer = bServer;
	}

	void GetSmDbFilePos(EPSMDBFILEPOS &oSmDbFilePos)
	{
		oSmDbFilePos = m_oCapIndexHead.oDbFilePos;
	}

	void SetSmDbFilePos(EPSMDBFILEPOS &oSmDbFilePos);

private:
	BOOL m_bServer;
	BOOL m_bIndex0Changed;
	BOOL m_bIsNewCreate;
	virtual BYTE* MapView(volatile __int64 n64BeginPos, DWORD dwLen = 33554432, DWORD dwMinLen=1024);//32M
	void AddIndex0(volatile __int64 &n64Pos, volatile __int64 &n64DataPos, EPTIME64 &tm, long nIndex, BOOL bAddIndex);
	BYTE* MapAreaView();

	long m_nPosIndex0Mngr;
	void ReadIndex0Mngr();
	void InitIndex0Mngr();
	long GetIndex0Size();
	long GetIndex0BeginPos();



	void WriteIndexoMngr();
	void WriteIndexoMngrEx();

//////////////////////////////////////////////////////////////////////////
public:
	PEPCAPDBBUFFERINDEX0EX GetIndex0(long nIndex)
	{
		ASSERT (m_oIndex0Mngr.pIndex0s != NULL);
		return m_oIndex0Mngr.pIndex0s + nIndex;
	}

	void UpdateIndex0File()	{	SaveIndexoMngr();	}
	void OpenIndexoMngr();
	void SaveIndexoMngr();

protected:
	void SearchIndex0(EPCAPSEARCHCONFIG &oSearchConfig, PEPCAPDBBUFFERINDEX0EX &pIndex0Prev, long nBeginIndex, long nEndIndex);

//////////////////////////////////////////////////////////////////////////
public:
	void Query(EPTIME64 &tmBegin, EPTIME64 tmEnd, CEpQueryIndex0Ranges &oIndex0Ranges);

private:
	long m_nPosChangeCount;
	PEPCAPDBBUFFERINDEX0EX m_pLastIndex0;

	void GetIndex0ValidRage(CEpQueryIndex0Ranges &oIndex0Ranges);
	void GetIndex0ValidRage(PEPQUERYRANGE pRange, long nBeginIndex, long nEndIndex);
	void GetIndex0ValidRage(EPQUERYRANGE &oRange, long nBeginIndex, long nEndIndex)	{		GetIndex0ValidRage(&oRange, nBeginIndex, nEndIndex);	}
	void QueryIndex0ValidRage(EPTIME64 &tmBegin, EPTIME64 tmEnd, CEpQueryIndex0Ranges &oIndex0Ranges);
};

class CCapDbIndex0SmDbFile : public CCapSmDbFile
{
public:
	CCapDbIndex0SmDbFile();
	virtual ~CCapDbIndex0SmDbFile();

	static const CString g_strCapSmDbIndex0File;
	static const CString g_strCapSmDbIndex0ID;

public:
	CCapDbIndex0SmDbArea  *m_pDbIndexHead;

public:
	BOOL IsNewCreate()	{	return m_pDbIndexHead->IsNewCreate();	}
	void CreateCapDbIndex0SmDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
//	void Write(CCapCycleMemBufferMngr *pBufferMngr);
	void CreateCapDbIndex0SmDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	void AddIndex0(volatile __int64 &n64Pos, volatile __int64 &n64DataPos, EPTIME64 &tm, BOOL bWriteTail)
	{
		m_pDbIndexHead->AddIndex0(n64Pos, n64DataPos, tm, bWriteTail);
	}

	void GetSmDbFilePos(EPSMDBFILEPOS &oSmDbFilePos)
	{
		m_pDbIndexHead->GetSmDbFilePos(oSmDbFilePos);
	}
	void SetSmDbFilePos(EPSMDBFILEPOS &oSmDbFilePos)
	{
		m_pDbIndexHead->SetSmDbFilePos(oSmDbFilePos);
	}
	void SaveIndexoMngr()
	{
		m_pDbIndexHead->SaveIndexoMngr();
	}

	void UpdateIndex0File()		{	m_pDbIndexHead->UpdateIndex0File();	}


private:
};

