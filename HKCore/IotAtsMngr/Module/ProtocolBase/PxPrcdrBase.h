#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "PxPkgBase.h"

#define PrcdrState_Step_NULL	0
#define PrcdrState_Step_1		1
#define PrcdrState_Step_2		2
#define PrcdrState_Step_3		3
#define PrcdrState_Step_4		4
#define PrcdrState_Step_End		0xff

class CPxProtocolBase;

class CPxPrcdrBase:public CExBaseList
{//子对象为发送和接收报文对象
public:
	CPxPrcdrBase();
	virtual ~CPxPrcdrBase();

public:
	//m_strID:ProcedureID
	CString m_strDeviceID;			//当前过程所属装置
	CString m_strResultEvent;		//过程结果码:0:
	long m_nProcedureState;			//过程状态机，0xFF:过程结束
	CString m_strRecordMode;		//录波模式

	CExBaseList m_listRecvPkg;	//过程接收报文引用
	CExBaseList m_listSendPkg;	//过程发送报文引用

	SYSTEMTIME m_tmBeginTime;//开始时间，用于检测报文是否过时
	DWORD m_dwBeginTime;
	long m_nOverTimeLong;	//超时参数,根据具体的状态判断是否超时

	CDvmDataset *m_pRefDataset;	//关联数据集
	CDvmData m_oDataInterface;//参数列表
	CSttCmmOptrInterface *m_pPxCmmInterface;//用于发送报文
	CPxProtocolBase *m_pPxProtocolRef;		//关联协议对象

public:
	//循环执行，判断超时或发送报文，过程结束返回TRUE
	virtual BOOL Run();
	void DeletePkgList();	//设置删除标志，清空链表引用

	BOOL IsProcedureEnd()	{return m_nProcedureState == PrcdrState_Step_End;}
	CString GetResultEvent(){return m_strResultEvent;}
	void SetResultEvent(const CString &strEventID){m_strResultEvent = strEventID;}
	void InitProcedure(const CString &strDeviceID,const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	void ResetTimer();
	void KillTimer();
	BOOL IsTimerOut(DWORD dwCurTime);
	void SetProcedureState(long nState){m_nProcedureState = nState;}
	void SetPxProtocol(CPxProtocolBase *pPxProtocol){m_pPxProtocolRef = pPxProtocol;}
	void SetPxCmmOptrInterface(CSttCmmOptrInterface *pPxCmmInterface){m_pPxCmmInterface = pPxCmmInterface;}

	//报文处理接口
public:
	//处理报文列表,若提前应答报文，返回TRUE,否则返回FALSE
	BOOL ProcessRecvPkgs();
	//处理报文逻辑，若是应答，处理应答，返回TRUE,否则返回FALSE
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail){return FALSE;}
	//处理应答报文逻辑
	virtual BOOL ProcessPackageAck(CPxPkgBase *pPkgDetail){return FALSE;}

	virtual CDvmData* GetDataInterface()	{	return &m_oDataInterface;		}
	
	virtual void UpdateNodeTimers(CDvmDataset *pAttrs){};
};
