#pragma once

#define PX_PKG_STATE_NOT_PROCESSED			0	//未处理的报文
#define PX_PKG_STATE_PROCESSED_MATCH		1	//期待应答
#define PX_PKG_STATE_PROCESSED_NOTMATCH		2	//未找到解析节点解析参数
#define PX_PKG_STATE_CAN_DELETE				3	//应答报文，过程结束设置删除标志
#define PX_PKG_STATE_ERROR			        4	//出错的报文，只保存缓存

class CPxPkgBase:public CExBaseList
{
public:
	CPxPkgBase();
	virtual ~CPxPkgBase();

public:
	__int64 m_n64Time;
	LPVOID m_pBuffer;//指向报文信息

	long m_nCmdType;
	CString m_strCmdID;

	CExBaseList m_listDatas;//解析的报文信息列表，暂不考虑
	CExBaseList *m_pRefDataset;//报文关联的数据集

public:
	void SetPkgState(long nPkgState){m_nPkgState = nPkgState;}
	BOOL IsPkgState_NotProcessed(){return m_nPkgState == PX_PKG_STATE_NOT_PROCESSED;}
	BOOL IsPkgState_Processed_Match(){return m_nPkgState == PX_PKG_STATE_PROCESSED_MATCH;}
	BOOL IsPkgState_Processed_NotMatch(){return m_nPkgState == PX_PKG_STATE_PROCESSED_NOTMATCH;}
	BOOL IsPkgState_HasProcessed(){return (IsPkgState_Processed_Match() || IsPkgState_Processed_NotMatch());}
	BOOL IsPkgState_CanDelete(){return m_nPkgState == PX_PKG_STATE_CAN_DELETE;}

	SYSTEMTIME m_tmPkg;			//接收报文的时间
	long m_nPkgState;			//报文处理状态
};