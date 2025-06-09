//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CCapDbSttIndexSmDbFile.h  CCapDbSttIndexSmDbFile

#pragma once

#include "../../../Smdb/SmDbFileBase.h"
#include "../ProtocolBase/Pcap/FrameMemBufferMngr.h"

class CCapFrameIndexDbArea : public CSmDbAreaBase
{
public:
	CCapFrameIndexDbArea();
	virtual ~CCapFrameIndexDbArea();

	void InitSttPktSmIndex();
	void NewTest(); //�½�����

	//��ѯtmBegin��tmEnd֮��ı���д�빲��������ļ�λ��
	void QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmBegin, EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);
	void QueryCapFrameDbPos(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);

	//��ѯ����ͷ��ʱ�䵽tmEnd֮��ı���д�빲��������ļ�λ��
	void QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);
	void QueryCapFrameDbPos(SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);

public:
	SST_PKT_SM_INDEX *m_pSST_PKT_SM_INDEX;

};

//////////////////////////////////////////////////////////////////////////////
//xujinqiang20200612add�������ļ������
//////////////////////////////////////////////////////////////////////////////

class CCapDbSttIndexSmDbFile : public CSmDbFileBase
{
public:
	CCapDbSttIndexSmDbFile();
	virtual ~CCapDbSttIndexSmDbFile();

	//2020-06-12  �������ʿͻ���CCapFrameDbArea
	static CCapFrameIndexDbArea* CreateCapFrameIndexDbArea();
	static void CreateCapFrameIndexDbArea(CCapFrameIndexDbArea &oCapArea);

	//���غ���
public:
	virtual LPVOID LocatePos(volatile __int64 n64CurrPos)	{		return ((CCapFrameIndexDbArea*)m_pSmDbArea)->LocateAreaPos(n64CurrPos);	}
	volatile __int64 GetCurrPos()	{		return ((CCapFrameIndexDbArea*)m_pSmDbArea)->GetCurrPos();	}

	//void Write(CFrameMemBufferMngr *pBufferMngr);
	//void Write(BYTE *pBuffer, long nLen);

	void CreateSttIndexCapFrameDbServer();
	void CreateSttIndexCapFrameDbServer(volatile __int64 nDataSize, volatile __int64 nDataView, const CString &strPath);

	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
	{
		((CCapFrameIndexDbArea*)m_pSmDbArea)->ReadBuffer(pBuffer, pDestBuffer);
	}

	void Reset()
	{
		((CCapFrameIndexDbArea*)m_pSmDbArea)->Reset();
	}

	SST_PKT_SM_INDEX* CreateServer(); //��������������
	void WriteSttIndex(__int64 nBeginPos); //д������

	static void EP_ETHER_CAP_TIME2SYSTEMTIME(EP_ETHER_CAP_TIME tmSource, SYSTEMTIME &tmDest);

	//˽�г�Ա����
public:
	SST_PKT_SM_INDEX *m_pSST_PKT_SM_INDEX;
};

extern CSmDbConfig *g_pCapSmDbConfig;
