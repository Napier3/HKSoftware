//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapFrameDbFile.h  CCapFrameDbFile

#pragma once

#include "../../../Smdb/SmDbFileBase.h"
#include "../ProtocolBase/Pcap/FrameMemBufferMngr.h"

#include "CapDbSttIndexFrameDbFile.h"

class CCapFrameDbArea : public CSmDbAreaBase
{
public:
	CCapFrameDbArea();
	virtual ~CCapFrameDbArea();

	//���غ���
public:
	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer);

	//˽�г�Ա����
private:
	long WriteFrame(CFrameMemBuffer *pBuffer, long nWritos/*, CapSmDbPOS &oCapSmDbPos*/);
};

class CCapFrameDbFile : public CSmDbFileBase
{
public:
	CCapFrameDbFile();
	virtual ~CCapFrameDbFile();

	//2020-06-12  �������ʿͻ���CCapFrameDbArea
	static CCapFrameDbArea* CreateCapFrameArea();
	static void CreateCapFrameArea(CCapFrameDbArea &oCapArea);

public:
	CCapDbSttIndexSmDbFile m_oIndexFileSever;//���ڴ��������ļ������
	CTickCount32 m_oIndexTick;//PCʱ�䣬���ڽ�������

//���غ���
public:
	virtual LPVOID LocatePos(volatile __int64 n64CurrPos)	{		return ((CCapFrameDbArea*)m_pSmDbArea)->LocateAreaPos(n64CurrPos);	}
	volatile __int64 GetCurrPos()	{		return ((CCapFrameDbArea*)m_pSmDbArea)->GetCurrPos();	}

	virtual long Write(CXSmMemBufferMngr *pBufferMngr);
	virtual void Write(BYTE *pBuffer, long nLen);

	void CreateCapFrameDbServer();
	void CreateCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);

	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
	{
		if (m_pSmDbArea == NULL)
			return;
		((CCapFrameDbArea*)m_pSmDbArea)->ReadCapBuffer(pBuffer, pDestBuffer);
	}

	void Reset()
	{
		if (m_pSmDbArea == NULL)
			return;
		((CCapFrameDbArea*)m_pSmDbArea)->Reset();
	}

//˽�г�Ա����
private:
};
