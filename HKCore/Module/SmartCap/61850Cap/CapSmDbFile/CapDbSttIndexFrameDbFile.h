//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	void NewTest(); //新建测试

	//查询tmBegin到tmEnd之间的报文写入共享服务器文件位置
	void QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmBegin, EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);
	void QueryCapFrameDbPos(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);

	//查询索引头部时间到tmEnd之间的报文写入共享服务器文件位置
	void QueryCapFrameDbPos(EP_ETHER_CAP_TIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);
	void QueryCapFrameDbPos(SYSTEMTIME tmEnd, __int64 &nBeginPos, __int64 &nEndPos);

public:
	SST_PKT_SM_INDEX *m_pSST_PKT_SM_INDEX;

};

//////////////////////////////////////////////////////////////////////////////
//xujinqiang20200612add：索引文件相关类
//////////////////////////////////////////////////////////////////////////////

class CCapDbSttIndexSmDbFile : public CSmDbFileBase
{
public:
	CCapDbSttIndexSmDbFile();
	virtual ~CCapDbSttIndexSmDbFile();

	//2020-06-12  创建访问客户端CCapFrameDbArea
	static CCapFrameIndexDbArea* CreateCapFrameIndexDbArea();
	static void CreateCapFrameIndexDbArea(CCapFrameIndexDbArea &oCapArea);

	//重载函数
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

	SST_PKT_SM_INDEX* CreateServer(); //创建索引服务器
	void WriteSttIndex(__int64 nBeginPos); //写入索引

	static void EP_ETHER_CAP_TIME2SYSTEMTIME(EP_ETHER_CAP_TIME tmSource, SYSTEMTIME &tmDest);

	//私有成员变量
public:
	SST_PKT_SM_INDEX *m_pSST_PKT_SM_INDEX;
};

extern CSmDbConfig *g_pCapSmDbConfig;
