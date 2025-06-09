//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapFrameDbFile.h  CCapFrameDbFile

#pragma once

#include "SmDbFileBase.h"
#include "..\ProtocolBase\FrameMemBufferMngr.h"

class CCapFrameDbArea : public CSmDbAreaBase
{
public:
	CCapFrameDbArea();
	virtual ~CCapFrameDbArea();

	//���غ���
public:
	void Write(CFrameMemBufferMngr *pBufferMngr);
	LPVOID Read(__int64 n64BeginPos, DWORD dwLength);
	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer);
	void LocateAreaPos(volatile __int64 n64CurrPos);
	
	volatile __int64 GetCurrPos()	{		return m_pSmFileClient->GetCurr64Pos();	}
	void Reset()	{		m_nCurrWriteIndex = 0;	}

	//˽�г�Ա����
private:
	long WriteFrame(CFrameMemBuffer *pBuffer, long nWritos/*, CapSmDbPOS &oCapSmDbPos*/);
	void Write(CFrameMemBufferMngr *pBufferMngr,long nBeginIndex, long nEndIndex);
	//BYTE m_pDeviceDatasBuffer[8192];

	long m_nCurrWriteIndex;
};

class CCapFrameDbFile : public CSmDbFileBase
{
public:
	CCapFrameDbFile();
	virtual ~CCapFrameDbFile();

// 	static const CString g_strCapFrameDbFile;
// 	static const CString g_strCapFrameDbID;

	CCapFrameDbArea *m_pFrameSmDbArea;
	__int64 m_n64CapFrameBeginPos;

//���غ���
public:
	void Write(CFrameMemBufferMngr *pBufferMngr);

	void LocatePos(volatile __int64 n64CurrPos)	{		m_pFrameSmDbArea->LocateAreaPos(n64CurrPos);	}
	void CreateCapFrameDbServer();
	void CreateCapFrameDbClient();
	void CreateCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	void CreateCapFrameDbClient(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);
	volatile __int64 GetCurrPos()	{		return m_pFrameSmDbArea->GetCurrPos();	}

	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
	{
		m_pFrameSmDbArea->ReadCapBuffer(pBuffer, pDestBuffer);
	}

	void Reset()
	{
		m_pFrameSmDbArea->Reset();
	}

//˽�г�Ա����
private:

};

