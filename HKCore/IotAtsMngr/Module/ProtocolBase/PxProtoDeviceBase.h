#pragma once

#include "PxProtocolImpInterface.h"
#include "PxProtoEventInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "PxProtocolBase.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

class CPxProtoDeviceBase:public CPxProtocolImpInterface,public CExBaseList
{//m_strID:DeviceID
public:
	CPxProtoDeviceBase();
	virtual ~CPxProtoDeviceBase();

	CDvmDevice m_oDvmDevice;				//数据模型
	CPxProtocolBase *m_pPxProtocol;			//规约模板指针
	CString m_strIotEngineSN;//当前测试的iotengine

	//报文列表
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	CWnd* m_pDatasetView;

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);

public:
	//协议被调用执行接口
	virtual long RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual long PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset);
	virtual long PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen);
	virtual long GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset);
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	//初始化协议服务模块
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	//提取所有未处理的报文，用于过程处理
	void GetNotProcessedPkgs(CExBaseList &oList);
	
	//删除所有无效报文，保证链表不能为空
	void DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong);

	//处理传感器业务报文逻辑
	void ProcessPkg(char *pBuf,long nLen);


	//更新指定数据集
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	
	//Engine调用接口，用于协议事件返回
	void OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
public:
	CPxProtoEventInterface *m_pProtoEventInterface;	//用于协议事件返回，具体指向CIotEngineTo

	//CloseDevice时设置删除标志，在主线程中统一删除
	BOOL m_bCanDelete;	
};
