#pragma once

#include "PpSttIotEngine.h"
#include "PpSttCommConfig.h"

#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"
//#include "PpXIotEngineBase.h"

//#define WM_ENGINE_SYSTEM_MSG           (WM_USER + 1112) //zhouhj 2024.2.5 与PpXIotEngineBase.h重复,删除
//#define	WM_COMM_COMMAND				   (WM_USER + 1001)
#define	WM_CLOSE_STT_CLIENT		       (WM_USER + 1002)
//#define WM_ENGINE_EVENT_MSG            (WM_USER + 1003)

class CPpSttIotDeviceClient : public CExBaseObject
{
public:
    CPpSttIotDeviceClient();
    virtual ~CPpSttIotDeviceClient();

public:
	CString m_strProtoType;
	CString m_strCmdFilePath;

	CPpSttIotDevice *m_pPpDevice;  //多协议体系中，使用CProtocolDeviceInterface

	CString m_strTemplateFile, m_strDeviceFile, m_strDeviceID;
	//2022-10-8  lijunqing 个性化定义：通信参数
	CPpSttCommConfig m_oCommConfig;
	CString m_strProcedureID;
    CString m_strDatasetPath;

	long m_nSttCmdForat;

	PSX_OBJ_ADDR m_hEngineMsgWnd;

private:
	CDvmDevice *m_pDvmDevice;  //2023-3-9  lijunqing  关联的设备数据模型
	CDvmDataset *m_pDsReport;

public:
	void InitDvmDevice(CDvmDevice *pDvmDevice);
	void InitCommConfig(CPpSttCommConfig *pCommConfig);
	void InitCmdFilePath();
    void SendIotCmdFile(PSX_OBJ_ADDR hWnd, const CString &strCmdID);
    BOOL RunProcedure(PSX_OBJ_ADDR hWnd, const CString &strProcedureID, const CString &strDataset);

    void CreateDevice(PSX_OBJ_ADDR hWnd);
	BOOL ConnectDevice();//zhouhj 2024.1.4 修改返回值数据类型
	BOOL IsConnectSuccessful();
	void CloseDevice();
	void SetSttCmdFormat(long nSttCmdForat);

    void DisConnectForClose(BOOL bDelete);
    CDvmDataset* GetCurrDataset();
	BOOL GetRunProcedureRltValue(const CString &strID,long &nValue);//获取通讯命令运行结果 zhouhj 2024.3.14

	void GetDvmDevice(CDvmDevice *pDestDvmDevice);
	void ClearDvmDevice();
	void FinishRunProcedure();
	BOOL IsRunProcedureFinished();

	CDvmDataset* InitDvmDsReport();
	CDvmDataset* GetDvmDsReport(BOOL bCreateNew=TRUE);
	void AddToReport(CExBaseList *pList);
	void AddCurrSoeReports(CExBaseList *pList);

public:
	void Reset();
	void EnumDevice(CDvmDevice *pDevice);
	void EnumLDevice(CDvmLogicDevice *pLdevice);
	void EnumDataset(CDvmDataset *pDataset);
	void ReadDataset(CDvmDataset *pDataset);
    void ReadDataset(const CString &strDatasetPath);
	BOOL WriteDataset(CDvmDataset *pDataset);
    void WriteDataset2(CDvmDataset *pDataset, const CString &strDatasetPath);
	void ReadZone();
	void WriteZone(long nZoneIndex);
	void StartRpt(CDvmDataset *pDataset, PMMS_BRCB_CTRL_CONFIG pBrcbCfg);
	void StopReport(CDvmDataset *pDataset);
	void OpenDvmFile(CDvmDevice *pDevice);
	void SaveDvmFile(CDvmDevice *pDevice);

	void ReadDataset(CDvmDataset *pDataset, const CString &strCmdID);
    void ReadDataset(const CString &strDatasetPath, const CString &strCmdID);
    BOOL WriteDataset(CDvmDataset *pDataset, const CString &strCmdID);
    void WriteDataset(CDvmDataset *pDataset, const CString &strDatasetPath, const CString &strCmdID);
	//zhouhj 2024.1.24 增加用于写单个数据,如遥控选择、遥控执行等
	BOOL WriteSingleData(CDvmData *pData,const CString &strDatasetPath,const CString &strCmdID);

	//zhouhj 2024.1.17 读取遥测数据集
    void ReadAin(const CString &strDatasetPath);
	BOOL Initialize_Cmd();//zhouhj 2024.2.22 传统规约平台使用的总的初始化命令,初始化完成后,才能读取到SOE
	BOOL ReadSoe(const CString &strDatasetPath);

	BOOL RegisterReport_Cmd(const CString &strDatasetPath);//chenling2024.04.24 发送启动报告命令读SOE
};


class CPpSttIotEngineClientApp : public CExBaseList
{
public:
    CPpSttIotEngineClientApp();
    virtual ~CPpSttIotEngineClientApp();

    virtual long InitPpSttIotEngineClientApp();
    virtual long ExitPpSttIotEngineClientApp();

    //可以通过CPpSttIotEngine 创建，也可以直接创建
    //多装置模式下，可以通过CPpSttIotEngine创建，CPpSttIotEngine实现了创建的Device的管理
    CPpSttIotEngine m_oPpSttEngine;

public:
    void CreateDevice(CPpSttIotDeviceClient *pDevice, PSX_OBJ_ADDR hWnd);
    void CloseDevice(CPpSttIotDeviceClient *pDevice);
    CPpSttIotDeviceClient* FindDeviceClient(const CString &strDeviceSN);
};

