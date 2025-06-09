#pragma once

#include "PxProtoEventInterface.h"
#include "../../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CPxProtoDeviceBase;

class CPxProtocolBase// : public CExBaseList
{//m_strID:DeviceSN
public:
	CPxProtocolBase();
	virtual ~CPxProtocolBase();

	CString m_strDeviceID;

public:
	CExBaseList m_listRecvPkg;	//接收报文总表
	CExBaseList m_listSendPkg;	//发送报文总表
	CExBaseList m_listPrcdr;	//执行过程总表
	CExBaseList m_listTempPrcdr;	//临时过程链表
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listTmpPrcdr访问的互斥量

	BOOL m_bDvmDeviceAttach;	//FALSE:自身模型，TRUE:外部系统指定模型
	CDvmDevice *m_pDvmDevice;	//数据模型
	CString m_strPpxmlFile;
	CString m_strCmmCfgFile;
	CDataGroup *m_pCfgGroup;
	
//	CPxCmmInterface *m_pPxCmmInterface;	//用于报文发送
	CPxProtoEventInterface *m_pProtoEventInterface;	//用于协议事件返回

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);
	void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	virtual void UpdateDataset(CDvmDataset* pDataset, const CString &strID, const CString &strPkgData)	{};

	//提取所有未处理的报文，用于过程处理
	void GetNotProcessedPkgs(CExBaseList &oList);
	void DeleteUnvalidPkgs();

public:
	virtual CPxPrcdrBase* FindProcedure(const CString &strProcedureID);
	void AddProcedureRun(CPxProtoDeviceBase *pProtoDevice, CPxPrcdrBase *pProcedure
		, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);

public:
	void OnRunProcedure();
	virtual void StartEngineThread();
	virtual void ExitEngineThread();
	BOOL m_bExitEngineThread;
	CWinThread *m_pProcedureRunThread;
	static UINT Engine_ProcedureRunThread(LPVOID pParam);
};

