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
	//Э�鱻����ִ�нӿ�
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

	//2021-8-19  lijunqing ���̺͹�Լ������أ�û��Ҫʹ�ù���ģʽ
	virtual CPxPrcdrBase* CreateProcedure(const CString &strPrcdrID);

private:
	//����json����Ŀ��ڵ������ɶ�Ӧ��data��value
	void JsonToDvmValue(CExBaseList* pNode, CJSON* pJson);
	void JsonToDvmData(CDvmDataset* pDvmDataset, CJSON* pJson);
	void AddNewData(CJSON* pJson, CDvmDataset* pDvmDataset, const CString& strID);
	void AddNewValue(CJSON* pJson, CDvmData* pDvmData, const CString& strID, long nVarType);

	//linkup����豸��֤���Ľ��ڵ�һ��procedure����ʱ��д�����ݼ�
	BOOL UpdateLinkupDataset(CPxProtoDeviceBase* pDeviceBase);
	void UpdateEdgeAuthDataset(CPxProtoDeviceBase* pDeviceBase);

	//����Ҫ����ѭ����procedure
	void SetCurrentTopoID(CExBaseList* pListDatas);
	void SetEnableReport(CExBaseList* pListDatas, const CString& strProcedureID);

	//�������ݼ��ľ��庯��
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

	//��ת�����utf8�ַ���תgbk�ַ���
	CString Utf8ToGBK(char* pBuf);

	//��Ӳ��Եı�ע��Ϣ
	void ParseErrorInfo(CExBaseList* pCmd);
	BOOL AddErrorInfo(long nReportType, const CString& strRemark);

public:
	//�����ϱ����ĵĸ������ݼ���ʼ��,��ɺ�����������iotEngine
	void InitUpdateDatasetCmd(const CString& strIotEngineSN, CDvmDataset* pDataset);
	//�������ݼ��Ľӿں���
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