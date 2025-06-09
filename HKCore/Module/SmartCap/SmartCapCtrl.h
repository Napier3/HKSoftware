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
//PxiEngineGlobal.h(6) : error C2011: ��_tagEngineSystemDefine��: ��enum�������ض���
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
	CDvmDataset m_oDataset_IecDetect;   //̽�����ݼ���֧����û��ģ���ļ�ʱ������̽��

	CString m_strTemplateFile;		
	CString m_strDeviceFile;
	CString m_strIecCfgFile;
	CString m_strDeviceId;

	BOOL CloseSmartCap();
	BOOL LoadDvmFile(const CString& strDeviceFile);
	void AfterLoadDvmFile();   //������ģ���ļ��󣬶Կ��뿪����ӳ���������
	void ResetBinaryMap();     //��ʼ����ǰ�������е�ӳ��  ��Ϊ0
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

	//�ⲿ��Ϣ����
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long  m_hSysMsgWnd;
	unsigned long  m_nSysMsg;

	void CreateAt02dCmdThread();   //lijunqing 2022-4-8

	//ͨѶ����ִ��
	void ReadAin();               //������ֵ
	void ReadDin();               //��ң��
	void ReadInst(const CString &strChannelID);              //��˲ʱֵ
	void ReadTHD();               //��������
	void ReadSvDelay();           //��SV��ʱ
	void ReadDiscrete();          //��SV��ɢֵ
	void ReadSVSyn();             //��SVͬ����	
	void ReadGooseSyn();          //��GOOSEͬ����
	void WriteState();            //״̬�������
	void ReadSVCstc();            //SV����һ����
	void ReadGoCstc();            //GOOSE����һ����
	void ReadSVErr();             //SV�����쳣ģ��
	void ReadGooseErr();          //GGOSE�����쳣ģ��
	BOOL StartCap();              //����ץ��
	BOOL StopCap(BOOL bPostMsg = TRUE);               //ֹͣץ��
	BOOL DownIecfgData(const CString &strIecfgDataID);  //��������
	void ReadSoe();               //��SOE
	void Reset();                 //����
	void IecDetect(long nMode);             //SV̽��
	void WriteIecRcdStep();       //�ϲ���Ԫ����
	void ReadResponseTime();      //���ϲ���Ԫ��Ӧʱ����
	void MUTimeTest();            //ʱ�����Բ���
	void IEDTest(BOOL bReset=FALSE);               //�����ն˲���
	void IEDTest_Stop_Reset();   //�����ն˲��ԣ���ֹͣ���󸴹�
	void ReadIEDTestRslt();       //�������ն˲��Խ��
	void ReadMUTimeTestRslt();       //��ʱ�����Բ��Խ��
	void SetTestEventInterface();
	long GetStateTestTime_Long(const CString &strDatasetID);

	//���Թ����¼��ӿ�
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

	//�鲥
	void MultiCast();
#ifndef _PSX_QT_LINUX_
    CSttMulticastClientSocket *m_pSttMulticastClientSocket;
#endif

	void LOG_DEBUG_INFOR();
	CString m_strCurrAppID;
	//�����ն˲��ԣ���ʱ����ʱ����λ�������ż��仯״̬��
	CString m_strSwitchState;
	long m_nSwitchIndex;  //�����ն˲��ԣ���ʱ���ԣ���ǰ�仯�������ţ���0��ʼ
	long m_nSwitchCount;  //�����ն˲��ԣ���ʱ���ԣ���ǰ�仯�Ĵ�����
	long m_nMinGseToBinNum;  //�����ն˲��ԣ���ʱ���ԣ�GOOSE->���룬��С��ӳ����
	long m_nMinBoutToGseNum; //�����ն˲��ԣ���ʱ���ԣ�����->GOOSE����С��ӳ���ţ�
	long m_nBinaryCount;   //����������
	BOOL m_bDelayReset;   //��ʱ�����Ƿ��Ǹ���ı��
	//CString m_strCurrTestMode;  //��ǰ����ģʽ�������ն˲��ԣ�0-gse2bin��1-bout2gse
	CString m_strSwitchFlag; //�������Ƿ�ת�������� 1-��ת��0-����ת

protected:
	CString m_strCurrIecfgDataID;
	static UINT At02dCmdThread(LPVOID pPara);
	CWinThread *m_pThread;
	long m_nCurrCmd;

	BOOL DownIecfgData_Cmd();
	BOOL DownIecfgData_Cmd_Debug();
	BOOL StartCap_Cmd();              //����ץ��
	BOOL StopCap_Cmd();               //ֹͣץ��
	void WriteState_Cmd();            //״̬�������
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

