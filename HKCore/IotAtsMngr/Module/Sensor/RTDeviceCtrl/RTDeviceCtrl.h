#pragma once

#include "../../ProtocolBase/PxProtocolImpInterface.h"
#include "../../ProtocolBase/PxProtoEventInterface.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../IotPpTemplate/IotPpTemplate.h"
#include "../XSensorPkg.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#define ENGINE_TO_PX_IOTXML	_T("IOTXML")
#define ENGINE_TO_PX_PPXML	_T("PPXML")

#define WM_ID_INSERT_RTDEVICEHISDATA  (WM_USER + 1119)

/****************************************
实时装置类：
在CreateDevice时，在g_pIotSensorSvrEngine中m_listRTDevice检查是否存在，不存在则创建
相当于协议服务类，但不是Mqtt客户端
****************************************/

class CRTDeviceCtrl:public CPxProtocolImpInterface,public CExBaseList
{//m_strID:DeviceID
public:
	CRTDeviceCtrl();
	virtual ~CRTDeviceCtrl();

	CDvmDevice m_oDvmDevice;				//数据模型
	CIotPpTemplate *m_pIotTemplate;			//规约模板指针
	BOOL m_bInsertHisDataTimer;

	//传感器业务报文列表
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	//提取所有未处理的报文，用于过程处理
	void GetNotProcessedPkgs(CExBaseList &oList);
	//删除所有无效报文，保证链表不能为空
	void DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong);

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

	//处理传感器业务报文逻辑
	void ProcessSensorPkg(char *pBuf,long nLen);

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);
	//更新指定数据集
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	//Engine调用接口，用于协议事件返回
	void OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
public:
	CPxProtoEventInterface *m_pProtoEventInterface;	//用于协议事件返回，具体指向CIotEngineToSensor

	//CloseDevice时设置删除标志，在主线程中统一删除
	BOOL m_bCanDelete;	
};

/////////////////////////////////////////////
//将数据集参数列表生成等式，保存到装置实时数据表中
void GetEqualExprFromDataset(CDvmDataset *pDataset,CString &strExpr);