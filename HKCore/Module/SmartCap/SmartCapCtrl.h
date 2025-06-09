#pragma once

#include "../DataMngr/DvmDevice.h"
#include "../../61850/Module/CfgDataMngr/IecCfgDevice.h"
#include "XSttCap_61850.h"
#include "../../SttStudio/Module/SttSocket/Multicast/SttMulticastClientSocket.h"

#define WM_EMPTYCAPDEVICE (WM_USER+2334)
#define EXIT_CAP_TIMER  1722
#define VIEW_CAP_TIMER  1724
#define UPDATEDVMDEVICEDATAS_TIMER  2032
#define STATETEST_FINISH_TIMER 2033
#define ENGINE_HEARTBEAT_TIMER 2034
#define HEART_BEAT_TIMER   1850

#define WM_CAP_CFG_MSG  (WM_USER+2333)
#define WM_BEGIN_CAP_MSG  (WM_USER+2334)

//2022-11-12  lijunqing
//PxiEngineGlobal.h(6) : error C2011: “_tagEngineSystemDefine”: “enum”类型重定义
#include "../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
// enum _tagEngineSystemDefine2
// {//2020-5-21  lijunqing
// 	engineConnectDeviceFailed= 1, //0,
// 	engineConnectDeviceSuccessful=2, //1,
// 	engineCommError = 3, //2,
// 	engineCommFinish = 4, //3,
// 	engineCommCmdError=5, //4
// 	engineException=6 //5
// } ;//_enumEngineSystemDefine;

class CSmartCapCtrl : public CMacroTestEventInterface//, public CSttDebugEventInterface
{
private:
	CSmartCapCtrl(void);
	virtual ~CSmartCapCtrl(void);

	static CSmartCapCtrl* g_pSmartCapCtrl;
	static long g_nSmartCapCtrlRef;

public:
	static CSmartCapCtrl* Create();
	static void Release();

public:
	BOOL m_bStop_PostMsg;

	BOOL IsTestAppExist();
	BOOL ConnectDevice();
	BOOL DisConnectDevice();
	static BOOL g_bConnected;
	BOOL m_bLoadedIecfg;

	CXSttCap_61850 *m_pXSttCap_61850;

	CIecCfgDevice m_oIecCfgDevice;
	CDvmDevice m_oDeviceModel;
	CDvmDataset *m_pCurrDataset;
	CDvmDataset m_oDataset_IecDetect;   //探测数据集，支持在没有模型文件时，进行探测

	CString m_strTemplateFile;		
	CString m_strDeviceFile;
	CString m_strIecCfgFile;
	CString m_strDeviceId;

	BOOL CloseSmartCap();
	BOOL LoadDvmFile(const CString& strDeviceFile);
	void AfterLoadDvmFile();   //加载完模型文件后，对开入开出的映射进行整理；
	void ResetBinaryMap();     //开始测试前，将所有的映射  改为0
	void AfterLoadDvmFile_BinaryMap(CDvmData *pData, const CString &strType);
	long SortBinID(const CString &strSrcID, const CString &strIDMap);
	BOOL LoadIecCfgFile(const CString &strIecCfgFile);
	void LoadDevices();
	void AddReportDataset();
	void CreateUpdateDvmDeviceDatasThread();
	void BeginSmartCapThread();

	BOOL HasLoadCfgDevice(){ return(m_oIecCfgDevice.GetCount()>0);}
	BOOL HasCurrCfgDatas() { return(m_oIecCfgDevice.m_pCurrDatasMngr != NULL);}
	void SetCurrDatasMngr(CIecCfgDatasMngr *pCfgDatasMngr) { m_oIecCfgDevice.SetCurrDatasMngr(pCfgDatasMngr); }
	CString GetCurrDatasMngrID();

	BOOL IsInStateOutput();
	BOOL IsStartedTest();
	
	BOOL IsEnableStartOutput();
	BOOL IsEnableStopOutput();

	BOOL IsRecordTestCalThreadCreated();
	void UpdateDvmDeviceDatas();

	//外部消息定义
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long  m_hSysMsgWnd;
	unsigned long  m_nSysMsg;

	void CreateAt02dCmdThread();   //lijunqing 2022-4-8

	//通讯命令执行
	void ReadAin();               //读测量值
	void ReadDin();               //读遥信
	void ReadInst(const CString &strChannelID);              //读瞬时值
	void ReadTHD();               //读畸变率
	void ReadSvDelay();           //读SV延时
	void ReadDiscrete();          //读SV离散值
	void ReadSVSyn();             //读SV同步差	
	void ReadGooseSyn();          //读GOOSE同步差
	void WriteState();            //状态序列输出
	void ReadSVCstc();            //SV报文一致性
	void ReadGoCstc();            //GOOSE报文一致性
	void ReadSVErr();             //SV报文异常模拟
	void ReadGooseErr();          //GGOSE报文异常模拟
	BOOL StartCap();              //启动抓包
	BOOL StopCap(BOOL bPostMsg = TRUE);               //停止抓包
	BOOL DownIecfgData(const CString &strIecfgDataID);  //下载配置
	void ReadSoe();               //读SOE
	void Reset();                 //复归
	void IecDetect(long nMode);             //SV探测
	void WriteIecRcdStep();       //合并单元测试
	void ReadResponseTime();      //读合并单元响应时间结果
	void MUTimeTest();            //时间特性测试
	void IEDTest(BOOL bReset=FALSE);               //智能终端测试
	void IEDTest_Stop_Reset();   //智能终端测试，先停止，后复归
	void ReadIEDTestRslt();       //读智能终端测试结果
	void ReadMUTimeTestRslt();       //读时间特性测试结果
	void SetTestEventInterface();
	long GetStateTestTime_Long(const CString &strDatasetID);

	//测试功能事件接口
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);	
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);	
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnReport(CSttSysState &oSysState);
	virtual void OnException(CDataGroup *pParas);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){};

	virtual long OnTestReport(CSttParas *pParas, CString strRetType);
	long OnTestEvent_SttTimeMeasureTest(CSttParas *pParas);
	long OnTestEvent_SttIecDetectTest(CDataGroup *pParas);
	long OnTestEvent_SttMUTimeTest(CDataGroup *pParas);
	long OnTestEvent_SttIEDTest(CDataGroup *pParas);
	long OnException_UTC(CDataGroup *pParas);
	void UpdateBinaryMapValue_IEDTest(long nSwitchIndex, const CString &strSwitchState);
	void ResetTestMode_IEDTest();
	long GetBinaryMapCount_IEDTest(CDvmDataset *pDataset);
	long GetIecDetect_CBCount();
	virtual long OnDisConnect();

	//SttDebugInterface
	virtual void OnRecvSttDebugData(CSttSysState &oSysState);

	//组播
	void MultiCast();
#ifndef _PSX_QT_LINUX_
    CSttMulticastClientSocket *m_pSttMulticastClientSocket;
#endif

	void LOG_DEBUG_INFOR();
	CString m_strCurrAppID;
	//智能终端测试，延时测试时，变位的索引号及变化状态；
	CString m_strSwitchState;
	long m_nSwitchIndex;  //智能终端测试，延时测试，当前变化的索引号，从0开始
	long m_nSwitchCount;  //智能终端测试，延时测试，当前变化的次数；
	long m_nMinGseToBinNum;  //智能终端测试，延时测试，GOOSE->开入，最小的映射编号
	long m_nMinBoutToGseNum; //智能终端测试，延时测试，开出->GOOSE，最小的映射编号；
	long m_nBinaryCount;   //开关量数量
	BOOL m_bDelayReset;   //延时测试是否是复归的标记
	//CString m_strCurrTestMode;  //当前测试模式，智能终端测试：0-gse2bin；1-bout2gse
	CString m_strSwitchFlag; //开关量是否翻转的配置项 1-翻转；0-不翻转

protected:
	CString m_strCurrIecfgDataID;
	static UINT At02dCmdThread(LPVOID pPara);
	CWinThread *m_pThread;
	long m_nCurrCmd;

	BOOL DownIecfgData_Cmd();
	BOOL DownIecfgData_Cmd_Debug();
	BOOL StartCap_Cmd();              //启动抓包
	BOOL StopCap_Cmd();               //停止抓包
	void WriteState_Cmd();            //状态序列输出
	BOOL ConnectDevice_Cmd(BOOL bPostMsg=TRUE);
	BOOL IecDetect_Cmd(long nMode);
	BOOL WriteIecRcdStep_Cmd();
	BOOL MUTimeTest_Cmd();

public:
	BOOL IEDTest_Cmd();
	CDvmData* FindDataByAppID_IecDetect(const CString &strAppID);

private:
	CString m_strCurrTest;
	CSttTestAppCfg *m_pSttTestAppCfg;

public:
	CString GetCurrTestStr()	{	return m_strCurrTest;	}
	void SetCurrTestStr(const CString &strCurrTest)	{	m_strCurrTest = strCurrTest;	};
	void AttachSttTestAppCfg(CSttTestAppCfg *p)	{	m_pSttTestAppCfg = p;	}

	//2022-5-2  lijunqing 
	void InitSmartCapCtrl();

};

void SmartCap_PostDeviceSysMessage(CSmartCapCtrl *pSmartCapCtrl, WPARAM wParam, LPARAM lParam);
void SmartCap_PostDeviceCommCmdMessage(CSmartCapCtrl *pSmartCapCtrl, WPARAM wParam, LPARAM lParam);

extern CSmartCapCtrl* g_theSmartCapCtrl;

