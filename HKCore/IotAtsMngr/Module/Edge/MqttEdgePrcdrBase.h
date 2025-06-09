#pragma once

#include "../ProtocolBase/PxPrcdrBase.h"
#include "MqttEdgePkgBase.h"
#include "EdgeCmd/EdgeCmd.h"
#include "EdgeProtoDevice.h"

class CMqttEdgePrcdrBase : public CPxPrcdrBase
{
public:
	CMqttEdgePrcdrBase();
	virtual ~CMqttEdgePrcdrBase();

public:
	//循环执行，判断超时或发送报文，过程结束返回TRUE
	virtual BOOL Run();

	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	virtual BOOL ProcessPackageFinished(CPxPkgBase *pPkgDetail);

	virtual	BOOL CreateRunProcedureObject(const CString& strProcedureID, CEdgeCmd* pEdgeCmd);
	virtual BOOL OnRunProcedure_Service(CString& strProcedureID) { return FALSE; }
	virtual BOOL OnRunProcedure_Device(CString& strProcedureI, CEdgeCmd* pCmd = NULL) { return FALSE; }
	virtual BOOL OnRunProcedure_Container(CString& strProcedureID) { return FALSE; }
	virtual BOOL OnRunProcedure_App(CString& strProcedureID) { return FALSE; }
	virtual CEdgeParas* InitProcedure_Server(BOOL bIsWrite);

	virtual void InitProcedure(CExBaseList* pDatas, CDvmDataset* pDataset, CEdgeProtoDevice* pDevice);
	virtual void AddTail(CEdgeProtoDevice* pDevice);
	//void RunProcedure(CString strProcedure, CExBaseList* pData = NULL, CDvmValue* pValue = NULL);

	//yzj 2021-9-13 增加发送报文过程中需要重复用到的生成函数
private:
	void SetEdgeData(CString& strEdgeData, CDvmData* pDvmData);
	void SetEdgeData(long& nEdgeData, CDvmData* pDvmData);
	void SetEdgeValue(CString& strEdgeValue, CDvmValue* pDvmValue);
	void SetEdgeValue(long& nEdgeValue, CDvmValue* pDvmValue);
	void InitUpdateDataSetCmd(const CString& strIotEngineSN, CDvmDataset* pDataset);

protected:
	virtual CEdgeParaData* AddEdgeData(CEdgeParaDatas* pPara ,CDvmDataset* pDataset, CString strVarName, CString strVarType);
	virtual void GetEdgeJson(CExBaseList* pData, CJSON* pJson);
	virtual CEdgeFile* AddEdgeFile(CDvmData* pData);
	virtual CEdgeSign* AddEdgeSign(CDvmData* pData);
	virtual CEdgeTemperature* AddEdgeTemperature(CDvmData* pData);
	virtual CEdgeRepPeriod* AddEdgeRepPeriod(CDvmData* pData);
	virtual CEdgeImage* AddEdgeImage(CDvmData* pData);
	virtual CEdgeWithApp* AddEdgeWithApp(CDvmData* pData);
	virtual CEdgeCfgCpu* AddEdgeCfgCpu(CDvmData* pData);
	virtual CEdgeCfgMem* AddEdgeCfgMem(CDvmData* pData);
	virtual CEdgeCfgDisk* AddEdgeCfgDisk(CDvmData* pData);
	virtual void UpdateReport(CExBaseObject *pCmdBase, BOOL bIsState = 0);
	virtual void UpdateReport_Topo(CExBaseObject *pCmdBase);
};