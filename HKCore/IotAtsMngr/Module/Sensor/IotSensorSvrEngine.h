#pragma once

#include "../../../Module/DataMngr/DvmDevices.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../EngineServer/MqttEngineBase.h"
#include "RTDeviceCtrl/RTDeviceCtrl.h"
#include "IotPpTemplate/IotPpTemplate.h"
#include "RTDeviceCtrl/IotPpProcedureRun.h"
#include "..\..\..\Module\mysqlapp\mysqlbaseapp.h"

/**************************************
传感器协议服务处理模块:
1、全局唯一变量g_pIotSensorSvrEngine，Mqtt客户端
2、订阅传感器业务报文主题Monitor；
3、管理实时装置列表m_listRTDevice，过程列表m_listPrcdr，规约模板列表m_listTemplate

在CreateDevice时，查找装置列表，不存在则创建添加装置列表和规约模板列表
在CloseDevice时，删除指定装置和关联的过程；

在全局过程处理线程Engine_ProcedureRunThread中：
循环执行过程列表中每个过程的Run,返回TRUE说明过程结束
**************************************/

class CIotSensorSvrEngine:public CMqttEngineBase,public CMySqlBaseApp
{
public:
	CIotSensorSvrEngine();
	virtual ~CIotSensorSvrEngine();

	static CIotSensorSvrEngine *Create();
	static void Release();

public:
	CExBaseList m_listPrcdr;		//执行过程总表
	CExBaseList m_listTempPrcdr;	//临时过程链表
	CExBaseList m_listRTDevice;		//实时装置列表
	CExBaseList m_listTemplate;		//规约模板链表
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listTmpPrcdr访问的互斥量
	BOOL m_bInsertHisDataTimer;

	void InitMySql();
	//检查数据库实时装置表，不存在则插入，存在则更新
	BOOL UpdateRTDeviceData(const CString &strDeviceID,CDvmDataset *pDataset,BOOL bWarning);
	//查询测试曲线数据表，写入对应的历史实时数据
	BOOL UpdateRTDeviceHisData(const CString &strDeviceID,CDvmDataset *pDataset);
	//查询设备表，判断是环境监测设备，则进行环境监测数据插入
	BOOL UpdateMonitorData(const CString &strDeviceID, CDvmDataset *pDataset);
	//更新告警事件，需要根据设备类型来确认告警内容
	BOOL UpdateWarningEvent(const CString &strDeviceType, const CString &strDeviceID, CDvmDataset *pDataset);
	//向MainFrame发消息，定时插入RTDeviceHisData
	void PostRTDeviceHisDataMessage(CRTDeviceCtrl *pDeviceCtrl);
	//遍历装置列表，删除无效装置和报文
	void DeleteUnvalidDeviceAndPkgs();
	//删除装置之前,删除所有该装置的过程
	virtual void DeleteDeviceProcedureRun(CRTDeviceCtrl *pRTDeviceCtrl);
	//绑定消息窗口，用于发起定时器，数据集刷新显示等
	void AttachMsgWnd(CWnd *pWnd)	{	m_pMsgWnd = pWnd;	}

	//Mqtt客户端初始化
	BOOL Init(const char *pszIP,long nPort);
	//Mqtt客户端数据处理入口
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);

	//获取RTDeviceCtrl,没有则创建
	CRTDeviceCtrl *GetRTDeviceCtrl(const CString &strDeviceID
		,const CString &strPpxmlFile,const CString &strDvmFile);
	//查找规约模板对象,没有则创建
	CIotPpTemplate *GetIotTemplate(const CString &strPpxmlFile);
	CRTDeviceCtrl *FindRTDeviceCtrl(const CString &strDeviceID);

	//添加到临时链表m_listTempPrcdr中，在Engine_*Thread中循环开头，将m_listTempPrcdr，添加到m_listPrcdr中
	void AddProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
		, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);

	//线程处理接口
protected:
	void OnRunProcedure();
	void StartEngineThread();
	void ExitEngineThread() ;
	BOOL m_bExitEngineThread;
	CWinThread *m_pProcedureRunThread;
	static UINT Engine_ProcedureRunThread(LPVOID pParam);

private:
	CWnd *m_pMsgWnd;
};

extern CIotSensorSvrEngine *g_pIotSensorSvrEngine;
extern long g_nIotSensorSvrEngineRef;