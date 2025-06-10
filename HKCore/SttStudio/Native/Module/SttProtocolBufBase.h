#pragma once

#include "../../Module/MemBuffer/ExpandMemBuf.h"
#include "SttGlobalDef_File.h"


class CSttProtocolBufBase
{
public:
	CSttProtocolBufBase();
	virtual ~CSttProtocolBufBase();

	long m_nSendIndex;
	long m_nRecvIndex;
	BYTE m_pRecvPkgHead[STT_PKG_HEAD_LEN];
	CString m_strIPLocal;
	int m_nPortLocal;
	CString m_strIPRemote;
	int m_nPortRemote;

	//Ω” ’ª∫¥Ê
	CExpandMemBuf m_oExpandRecvBuf;

public:
	virtual void OnReceiveBuffer(BYTE *pBuf, long nLen);
	virtual BOOL AnalysisRecvBuf();
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen){return FALSE;}
};

void stt_InitPktBuffer_Head(BYTE *pPkgBuffer,long nTypeCmd, long nDataLen, DWORD nIDTester, long nSendIndex, BYTE bCompress);