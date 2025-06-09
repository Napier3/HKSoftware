#pragma once

#include "../IotPpTemplate/IotPpTemplate.h"
#include "../XSensorPkg.h"

class CRTDeviceCtrl;

class CIotPpProcedureRun : public CExBaseObject
{//m_strID:DeviceID
private:
	CIotPpProcedureRun(){}

public:
	//传感器业务报文列表,为CRTDeviceCtrl报文链表中该过程的报文引用，析构时需RemoveAll
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	CIotPpProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
			, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual ~CIotPpProcedureRun(void);

	//用于Engine调用的外界接口
	BOOL Run();
	void DeletePkgList();//设置删除标志，清空链表引用

	CString GetResultEvent(){return m_strResultEvent;}
	void SetResultEvent(const CString &strEventID){m_strResultEvent = strEventID;}
	CRTDeviceCtrl *GetRTDeviceCtrlRef(){return m_pRTDeviceCtrlRef;}
	CDvmDataset *GetDatasetRef(){return m_pDatasetRef;}
	void ExitProcedureRun(){m_bProcedureExit=TRUE;}
	void DeleteProcedureRun(){m_bIsValid=FALSE;}

private:
	CRTDeviceCtrl *m_pRTDeviceCtrlRef;	//关联实时设备
	CIotPpProcedure *m_pProcedure;		//当前过程
	CDvmDataset *m_pDatasetRef;			//关联数据集
	CString m_strRecordMode;			//录波模式，暂不考虑
	CString m_strResultEvent;			//过程事件ID

	CIotPpNode *m_pCurrNode;			//当前执行Node
	BOOL m_bProcedureExit;				//过程结束标记
	BOOL m_bIsValid;					//过程是否有效

	//设置当前执行的Node
	void SetCurrNode(CIotPpNode *pNode);

	//执行Node:判断是否发送报文，设置超时
	void RunNode();	
	//判断超时，解析报文列表
	void ProcessNode();
	//发送报文
	void RunNodePkg(const CString &strPackageID);
	//启动定时器
	void BeginTimer(DWORD dwCurrTick);
	//判断是否超时，若超时，返回调整执行的Node节点
	BOOL IsTimerOut(DWORD dwCurTime,CIotPpNode **ppCurNode);

	//处理报文逻辑
	void ProcessRecvPkgs();
	BOOL ProcessPackageDetail(CXSensorPkg *pPkgDetail);
	BOOL ProcessPackageAck(CIotPpAck *pAck,CXSensorPkg *pPkgDetail);
	BOOL IsMatchJump(CIotPpJump *pJump,CXSensorPkg *pPkgDetail);
	CIotPpNode *GetJumpNode(CIotPpJump *pJump);
};