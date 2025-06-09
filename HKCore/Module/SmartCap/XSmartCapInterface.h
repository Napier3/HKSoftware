#pragma once

#include "../SmDb/XSmMemBufferMngr.h"
#include "61850Cap/CapGlobalDef.h"
#include "61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.h"

#define RCD_PARSE_BUFFER_MAX_LEN   81920
#define RCD_LEFT_BUFFER_MAX_LEN     4096

//2022-4-6  lijunqing
//����ת���ӿڣ����罫AT02D����ת��Ϊ�����ֱ���
//�������ֻ�¼�����и��ֲ�ͬ�������������������뽫Э�鱨��ת��Ϊ���ֻ�����
class CXCapPkgBufferMngrInterface
{
public:
	virtual CXSmMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen) = 0;
	virtual void TransCapPkg() = 0;
	virtual void Release() = 0;
	virtual CXSmMemBufferMngr* GetXSmMemBufferMngr() = 0;
	virtual void ReadHexTestFile(const CString &strFile) = 0;
	virtual void AttachPkgTransDest(CXSmMemBufferMngr *pDestBuffer) = 0;

	virtual void ResetBuffer() = 0;  //2022-4-20  lijunqing
	virtual void LogBufferPos(){}   //2022-4-21  lijunqing ���ӻ�����λ�ã����λ�úͽ���λ��

public:
	CXCapPkgBufferMngrInterface()
	{
		m_oPkgHeadStcMngr.init();
		m_pSttRcdBuffer[0]  = 0;
		m_pLeftBuffer[0]  = 0;
		m_nLeftBufferLen = 0;
		m_pRefSttFrameBufMngr = NULL;
	}
	virtual ~CXCapPkgBufferMngrInterface()
	{

	}

protected:
	//���ڼ�¼һ���������У����ڲ������ı��ģ������ı���������һ����������
	//���ֿ����Ժܵͣ������Ȱ��ⲿ��������ţ�������������ʵ��
	BYTE m_pSttRcdBuffer[RCD_PARSE_BUFFER_MAX_LEN+10];
	BYTE m_pLeftBuffer[RCD_LEFT_BUFFER_MAX_LEN];
	long m_nLeftBufferLen;

	long m_nFrameCount;
	SST_AT02_PKT_HEAD m_oPrevHead ;
	__int64 m_n64PrevTime;
	CSttFrameMemBufferMngr *m_pRefSttFrameBufMngr;

protected:
	void ParseSttRcdBufferEx(long nBufLen);
	void ParseSttRcdBuffer(BYTE *pBuffer, long nLenCopyLeft);

//2022-6-19  lijunqing
// �����׳��ֶ����������Ϊ���ų�����ΪӦ�ó���������Դ�Ƚϴ�������ֻ��
// AT02D����ͷ������
protected:
	STT_AT02_PKT_HEAD_STC_MNGR m_oPkgHeadStcMngr;
	static long g_nXSmartCapDebugHead;

	PSTT_AT02_PKT_HEAD_STC SttAddAppID(unsigned short nAppID);
	void SttAt02HadStc(SST_AT02_PKT_HEAD &oHead);
	void AnalysisSttAT02HeadBuffer(BYTE *pBuffer, long nLenBuffer);

public:
	PSTT_AT02_PKT_HEAD_STC_MNGR GetPkgHeadStcMngr()	{	return &m_oPkgHeadStcMngr;		}
	static void XSmartCapDebugHead();
	static BOOL Is_XSmartCapDebugHead();
};

void xsmartcap_ReadHead(PEPBUFFERPOS pBufferPos, SST_AT02_PKT_HEAD &oHead);
