//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

	//重载函数
public:
	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer);

	//私有成员变量
private:
	long WriteFrame(CFrameMemBuffer *pBuffer, long nWritos/*, CapSmDbPOS &oCapSmDbPos*/);
};

class CCapFrameDbFile : public CSmDbFileBase
{
public:
	CCapFrameDbFile();
	virtual ~CCapFrameDbFile();

	//2020-06-12  创建访问客户端CCapFrameDbArea
	static CCapFrameDbArea* CreateCapFrameArea();
	static void CreateCapFrameArea(CCapFrameDbArea &oCapArea);

public:
	CCapDbSttIndexSmDbFile m_oIndexFileSever;//用于创建索引文件服务端
	CTickCount32 m_oIndexTick;//PC时间，用于建立索引

//重载函数
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

//私有成员变量
private:
};
