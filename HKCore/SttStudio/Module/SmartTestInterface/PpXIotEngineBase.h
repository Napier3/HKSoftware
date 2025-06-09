#pragma once

#include "ProtocolEngineInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../TestClient/PpSttIotClient.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../Module/BaseClass/ExBaseCycleArray.h"

#define WM_ENGINE_SYSTEM_MSG           (WM_USER + 1116)
#define	WM_COMM_COMMAND		(WM_USER+1117)
#define WM_ENGINE_EVENT_MSG           (WM_USER + 1118)

class CPpSttIotParas : public CProtocolParasInterface
{
public:
	CPpSttIotParas();
	virtual ~CPpSttIotParas();


	virtual long Reset();
	virtual long AddData(const CString &bstrID, const CString &bstrValue);
	virtual long AddData(const CString &bstrID, long nValue);

	static CPpSttIotParas* _New_ParasInterface(CExBaseList *pDataInterface)
	{
		ASSERT (pDataInterface != NULL);

		CPpSttIotParas *pPoDataInterface = new CPpSttIotParas();
		pPoDataInterface->m_pDataInterface = pDataInterface;
		return pPoDataInterface;
	}

	CExBaseList *m_pDataInterface;
};

class CPpSttIotValue : public CProtocolValueInterface
{
public:
	CPpSttIotValue();
	virtual ~CPpSttIotValue();

	virtual CString GetName();
	virtual void SetName(CString propVal);
	virtual CString GetID();
	virtual void SetID(CString propVal);
	virtual CString GetDataType();
	virtual void SetDataType(CString propVal);
	virtual CString GetValue();
	virtual void SetValue(CString propVal);
	virtual CString GetUnit();
	virtual void SetUnit(CString propVal);

    //CPxiValue *m_pValue;
};

class CPpSttIotData : public CProtocolDataInterface
{
public:
	CPpSttIotData();
	virtual ~CPpSttIotData();

	virtual long GetCount();
	virtual CProtocolValueInterface* GetItem(long nIndex);
    virtual long RegisterDataChangedWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nWMsgID);
	virtual long UnRegisterDataChangedWndMsg();
	virtual CString GetName();
	virtual void SetName(CString propVal);
	virtual CString GetID();
	virtual void SetID(CString propVal);
	virtual CString GetDataType();
	virtual void SetDataType(CString propVal);
	virtual CString GetValue();
	virtual void SetValue(CString propVal);
	virtual CString GetUnit();
	virtual void SetUnit(CString propVal);
	virtual CString GetMinValue();
	virtual void SetMinValue(CString propVal);
	virtual CString GetMaxValue();
	virtual void SetMaxValue(CString propVal);

    //CPxiData *m_pData;
};


class CPpSttIotDataset : public CProtocolDatasetInterface
{
public:
	CPpSttIotDataset();
	virtual ~CPpSttIotDataset();

	virtual void Release();

	virtual long GetCount();
	virtual CProtocolDataInterface* GetItem(long nIndex);
	virtual CProtocolDataInterface* FindDataByID(const CString &strDataID);
	virtual CProtocolDataInterface* FindDataByName(const CString &strName);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);
	virtual long DeleteAllDatas();

	//简化版本  2022-10-23  lijunqing
	virtual void UpdateDataset(CDvmDataset *pDataset);

	//2024.1.24 zhouhj 更新修改单个数据
	virtual BOOL UpdateData_Single(CDvmData *pData);

public:
    CDvmDataset *m_pDataset;	 
};

class CPpSttIotLogicDevice : public CProtocolLogicDeviceInterface
{
public:
	CPpSttIotLogicDevice();
	virtual ~CPpSttIotLogicDevice();

	virtual long GetCount();
	virtual CProtocolDatasetInterface* GetItem(long nIndex);
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDatasetPath);
	virtual CProtocolDataInterface* FindData(const CString &strPath);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);

    //CPxiLogicDevice *m_pLogicDevice;
};

class CPpSttIotDeviceBase : public CProtocolDeviceInterface
{
public:
	CPpSttIotDeviceBase();
	virtual ~CPpSttIotDeviceBase();

	CString m_strCurrProcedureID;
	BOOL m_bIsSvrDeviceConnectSucc;

	virtual long CommConfig(const CString &strCmmConfig);
	virtual long IsConnectSuccessful();
	virtual long GetCount();
	virtual CProtocolLogicDeviceInterface* GetItem(long nIndex);
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDataSetName);
	virtual CProtocolDataInterface* FindData(const CString &strPath);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath);
	virtual long RunProcedureEx(const CString &strProcedureScript);
    virtual long AttachSystemWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nMsgID);
    virtual long RegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID);
    virtual long UnRegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID);
    virtual long RegisterDataChangedWndMsg(const CString &strDataPath, PSX_OBJ_ADDR hWnd, unsigned long nWMsgID);
	virtual long UnRegisterDataChangedWndMsg(const CString &strDataPath);
	virtual long UnLoad();
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &bstrXmlData);
	virtual CString GetXmlDataEx(const CString &strDatasetPath);
	virtual CString SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData);
	virtual CProtocolParasInterface* GetDataInterface();
	virtual long ConnectDevice();
	virtual CString GetAttrByID(const CString &strAttrID);
	virtual long SetAttrByID(const CString &strAttrID, const CString &strValue);
	virtual long SaveDvmFile(const CString &strDvmFile);
	virtual long SetCommConfig(const CString &strCommConfig);
	virtual CString GetCommConfig(const CString &strCommConfig);
	virtual CString GetXmlDataLD();
	virtual CString GetLogsXml();	
    virtual CString QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName);
    virtual long SetRecordPath(const CString &strRcdPath);

public:

	//事件接口
	virtual void On_SysState_IOT(CSttSysState *pSysState);

protected:
	BOOL On_SysState_IOT_RunProcedure(CSttSysState *pSysState);
	BOOL On_SysState_Test_GetDataset(CSttSysState *pSysState);
	BOOL On_SysState_IOT_CreateDevice(CSttSysState *pSysState);
	BOOL On_SysState_IOT_CloseDevice(CSttSysState *pSysState);
	BOOL On_SysState_IOT_OnEngineEvent(CSttSysState *pSysState);
	BOOL GetDatasetFromParas(CSttSysState *pSysState);
	BOOL IsCurrProcedure_Write();

	void On_SysState_IOT_RunProcedure_Cmd(CSttSysState *pSysState);
	void On_SysState_IOT_RunProcedure_ReadZone(CSttParas *pSttParas);

    long m_nSttCmdDataFormat;

public:
	virtual long X_SendIotCmd(CSttIotCmd &oIotCmd) = 0;

    virtual void NewSttIotClient();
	virtual BOOL ConnectSttServer();
	virtual void SetSttCmdDataFormat(long nSttCmdForat);
	virtual void DisConnect();
	virtual long CloseDevice();
	virtual void DisConnectForClose(BOOL bDelete);  //断开连接
	virtual BOOL IsConnectIotServerSucc();
	virtual void SetDeviceSN(const CString &strDeviceSN);

public:
    PSX_OBJ_ADDR m_hSysMsgWnd;
	ULONG m_nSysMsgID;
    PSX_OBJ_ADDR m_hMsgWnd;
	ULONG m_nMsgID;
	CExBaseList m_listDataInterface;
	CString m_strDvmFile;
	CString m_strTemplateFile;
	CDvmDataset *m_pWriteDataset;

	//2022-10-8  lijunqing 个性化定义：通信参数
	CDataGroup m_oCommConfig;
	CExBaseList m_listDataset;   //记录通信命令返回的全部数据集

	CDataGroup m_listRunProcedureRlt;//zhouhj 2024.3.16 用于记录通讯命令运行过程执行结果(成功、失败等)

	//2023-3-4  lijunqing
	long m_nZoneIndex;

	//2023-3-8  lijunqing
	CExBaseCycleArray m_oSoeReports;

public:
	void PostDeviceSysMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceEventMessage(WPARAM wParam, LPARAM lParam);

	//2022-10-8  lijunqing 以下接口，直接使用对象，为SttPp模式
	virtual void InitCommConfig(CDataGroup *pCommConfig);
	virtual CDvmDataset* FindDataSet2(const CString &strDataSetName);

protected:
	//2023-1-29  lijunqing 用于枚举装置模型的功能
	CDvmDevice m_oDvmDeviceForEnum;
	void InitDvmDevice(CSttParas *pSttParas);

public:
	void GetDvmDevice(CDvmDevice *pDestDvmDevice);
	void ClearDvmDevice();
	void GetCurrSoeReports(CExBaseList *pList);
};


class CPpXIotEngineBase : public CProtocolEngineInterface
{
public:
	CPpXIotEngineBase();
	virtual ~CPpXIotEngineBase(void);

public:
	virtual CString GetVersion();
	virtual CProtocolDeviceInterface* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);
	virtual long GetCount();
	virtual CProtocolDeviceInterface* GetItem(long nIndex);
	virtual long ShowSpyWnd(long nShow);
	virtual long ReleaseDevice(const CString &strDeviceID);
	virtual long ReleaseAllDevice();
	virtual long CreateProject(const CString &strProjectFile);
	virtual long SetProtocolParse(long nStopFlag);
	virtual long ConfigEngine(const CString &strDvmFile);
	virtual long AttatchLogWnd(PSX_OBJ_ADDR hWnd);
	//2023-3-16 lijunqing
	virtual CProtocolDeviceInterface* CreateDevice(CPpSttCommConfig *pCommConfig) ;

public:
	virtual CPpSttIotDeviceBase* CreateNewDevice() = 0;
};
