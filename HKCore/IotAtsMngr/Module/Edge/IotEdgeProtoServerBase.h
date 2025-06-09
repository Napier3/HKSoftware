#pragma once

#include "EdgeMqttEngineBase.h"
#include "../ProtocolBase/PxProtocolImpInterface.h"
#include "../ProtocolBase/PxProtocolBase.h"

#define WM_ON_EDGE_DATASET_VALUE_UPDATA WM_USER+10032

class CIotEdgeProtoServerBase : public CPxProtocolImpInterface, public CEdgeMqttEngineBase, public CPxProtocolBase
{
public:
	CIotEdgeProtoServerBase();
	virtual ~CIotEdgeProtoServerBase();

public:
	//协议被调用执行接口
	virtual long RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual long PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset);
	virtual long PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen);
	virtual long GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset);
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	virtual BOOL Init(const char *pszIP,long nPort);
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);

	//2021-8-19  lijunqing 过程和规约本身相关，没必要使用工厂模式
	virtual CPxPrcdrBase* CreateProcedure(const CString &strPrcdrID);

private:
	//解析json并在目标节点下生成对应的data或value
	void JsonToDvmValue(CExBaseList* pNode, CJSON* pJson);
	void JsonToDvmData(CDvmDataset* pDvmDataset, CJSON* pJson);
	void AddNewData(CJSON* pJson, CDvmDataset* pDvmDataset, const CString& strID);
	void AddNewValue(CJSON* pJson, CDvmData* pDvmData, const CString& strID, long nVarType);

	//linkup与边设备认证报文将在第一次procedure创建时被写入数据集
	BOOL UpdateLinkupDataset(CPxProtoDeviceBase* pDeviceBase);
	void UpdateEdgeAuthDataset(CPxProtoDeviceBase* pDeviceBase);

	//不需要进入循环的procedure
	void SetCurrentTopoID(CExBaseList* pListDatas);
	void SetEnableReport(CExBaseList* pListDatas, const CString& strProcedureID);

	//更新数据集的具体函数
	CDvmDataset* GetDvmDataset(CString& strProcedureID);
	void UpdataDvmValue(CDvmValue* pValue, CExBaseList* pParaData);
	void UpdataEdgeParaData(CDvmData* pDvmData, CExBaseList* pParaData);
	CDvmDatasetGroup* UpdateAutoReport(CPxProtoDeviceBase* pDeviceBase, const CString strType, const CString& strProcedureID, const CString& strGbkBuf);

	void UpdataDvmData(CDvmData* pDvmData, CExBaseList* pParaData);
	void UpdataDvmDataset(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_Links(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_LinkState(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_ConPara(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_DeviceInfos(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_DeviceData(CDvmDataset* pDvmDataset, const CString& strDeviceID);
	void UpdataDvmDataset_ConStatus(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_Apps(CDvmDataset* pDvmDataset, CExBaseList* pParaData);
	void UpdataDvmDataset_AppCfgs(CDvmDataset* pDvmDataset, CExBaseList* pParaData);

	//带转义符的utf8字符串转gbk字符串
	CString Utf8ToGBK(char* pBuf);

	//添加测试的备注信息
	void ParseErrorInfo(CExBaseList* pCmd);
	BOOL AddErrorInfo(long nReportType, const CString& strRemark);

public:
	//主动上报报文的更新数据集初始化,完成后将主动更新至iotEngine
	void InitUpdateDatasetCmd(const CString& strIotEngineSN, CDvmDataset* pDataset);
	//更新数据集的接口函数
	void UpdateDataset(CEdgeParaDatas* pParas, CExBaseList* pDvmDataset);
	CDvmDataset* UpdateDataset(CEdgeParaDatas* pParaDatas, CString& strProcedureID);
	CDvmDataset* UpdateDataset_Event(CEdgeParaDatas* pParaDatas, CString& strProcedureID);
	CDvmDataset* UpdateDataset_Service_Cmd_Service(CEdgeParas* pParas, CString& strProcedureID);
	void UpdataDataset_Service(CExBaseList* pList, const CString& strID, const CString& strValue);
	BOOL UpdateDataset_Service_Cmd_Service_APPDir(CEdgeParas* pParas, CDvmDataset* pDvmDataset);
	BOOL UpdateDataset_Service_Cmd_Service_APPHFile(CEdgeParas* pParas, CDvmDataset* pDvmDataset);
	BOOL UpdateDataset_Service_Cmd_Service_APPConfigDirGet(CEdgeParas* pParas, CDvmDataset* pDvmDataset);
	BOOL UpdateDataset_Service_Cmd_Service_CmdGetAppConfig(CEdgeParas* pParas, CDvmDataset* pDvmDataset);
	CDvmDataset* UpdateDataset_Service_Event(CEdgeParaDatas* pParaDatas, CString& strProcedureID, const CString& strTopoID);
};