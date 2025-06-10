#ifndef CSTTDEVICEBASE_H
#define CSTTDEVICEBASE_H
#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTest/Common/Adjust/tmt_adjust_test.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/SttSystemConfig.h"
#include "../SttTest/Common/tmt_adjust_sys_para_binary_serialize.h"
#include "../SttTest/Common/tmt_system_config.h"
#include "../SttTest/Common/tmt_common_def.h"
#include "../SttTest/Common/tmt_soe_test.h"
#include "../SttTest/Common/tmt_record.h"
#include "../SttTest/Common/tmt_replay_test.h"
#include "../SttTest/Common/Swing/tmt_swing_test.h"
#include "../SttTest/Common/Syn/tmt_syn_test.h"
#include "../SttTest/Common/Meas/meas_define.h"
#include "../SttTestBase/SttTestBase.h"
#include"../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../RecordTest/SttRcdSendSocket.h"
#include "SttDeviceStatus.h"
#include "Module/Driver466/IEC_GlobalDefine.h"
#include "vector"

#ifdef _PSX_QT_LINUX_
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "QStringList"
#include "QList"
#endif

#define CHANLEPOINT 4000
#define SINCOUNT 200000
#define CIRCLECOUNT 2000
#define G2 1.4142135623731
#define SQRT3 1.732050807

#define ABN_TYPE_NONE	0
#define ABN_TYPE_SMV	1
#define ABN_TYPE_GOOSE  2

#define DMA_TYPE_NULL						0x00
#define DMA_TYPE_SUB						0x01
#define DMA_TYPE_PROBE						0x02
#define DMA_TYPE_RECORD						0x03
#define DMA_TYPE_LIGHT_FRAME				0x04

using namespace  std;
typedef struct
{
	int m_nModulePos;//��չ������ģ��λ��
	int m_nBiCount;//��չ������ģ�鿪����
	int m_nBoCount;//��չ������ģ�鿪����
	BOOL m_bBiPos[64];
	BOOL m_bBoPos[64];
} SwitchInfo; //64IO

typedef struct
{
	int m_nModulesCount;//��չ������ģ������
	int m_nModulesBiCount;//��չ������ģ�鿪������
	int m_nModulesBoCount;//��չ������ģ�鿪������
	SwitchInfo oSWITCHINFO[ADJUST_MAX_MODULE_COUNT];
} SwitchModules;

//DAPara Send to Driver
typedef struct
{
	unsigned long nmodule[ADJUST_MAX_MODULE_COUNT];
	unsigned long nvolt[ADJUST_MAX_MODULE_COUNT];
} DeviceDAPara;

typedef struct
{
	unsigned long nCnt;
	unsigned long nmodule[ADJUST_MAX_MODULE_COUNT];
	unsigned long nOverLoad[ADJUST_MAX_MODULE_COUNT];
} DeviceOverLoad;

typedef struct
{
	unsigned int dat[11];
} Drv_FeedBack;

typedef struct
{
	Drv_FeedBack stBack[16];
} Drv_SysInfo;

typedef struct
{
	unsigned int tmFlag;        //bit; 0 GPS   1 BCode
	unsigned int tm_h;          //��
	unsigned int tm_l;          //����
} Drv_SysUtc;

typedef struct
{
	unsigned int version[14];//����+12ģ��+����
} Drv_BoardVersion;

typedef struct
{
	tmt_channel uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel uiCUR[MAX_CURRENT_COUNT];
} ManuRtData;

typedef struct
{
	float m_fTripValue;//����ֵ
	float m_fTripTime;//����ʱ��
	float m_fTripValueChl[MAX_BINARYIN_COUNT];//����ֵ��Ĭ����0
	float m_fTripValueChlEx[MAX_ExBINARY_COUNT];//����ֵ��Ĭ����0
	float m_frTimeBinAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT]; //ÿһ�������¼64�α�λʱ��
	float m_frTimeBinExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT]; //ÿһ����չ�����¼64�α�λʱ��
	int	  m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	int	  m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //��λ����
	float m_frTimeBoutAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT]; //ÿһ��������¼64�α�λʱ��
	float m_frTimeBoutExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT]; //ÿһ����չ������¼64�α�λʱ��
	int	  m_nrBoutSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	int	  m_nrBoutExSwitchCount[MAX_ExBINARY_COUNT]; //��λ����
	float m_fReturnValue;
	float m_fReturnCoef;//����ֵ/����ֵ
	float m_fReturnTime;
	int   m_nAct;//1-���� 0-û����
	float m_fPhiAngleValue;
	double m_frInTime;		//״̬�������ʱ��
	float m_frTimeStateBegin;
	int   m_nBinFirstChgState[MAX_BINARYIN_COUNT];
	int   m_nBinExFirstChgState[MAX_ExBINARY_COUNT];
	int   m_nTripStep;//����ʱ�ĵݱ䲽��
	int   m_nRampIndex[MAX_BINARYIN_COUNT];
	int   m_nRampIndexEx[MAX_ExBINARY_COUNT];//δ����Ϊ-1��0�����ʼֵ������;1����ݱ�1������

	void init()
	{
		m_frInTime = 0.0f;
		m_frTimeStateBegin = 0.0f;
		m_nAct = 0;
		m_fPhiAngleValue = 0;
		m_fTripValue = 0.0f;
		m_fTripTime = 0.0f;
		m_fReturnValue = 0.0f;
		m_fReturnTime = 0.0f;
		m_fReturnCoef = 0.0f;
		m_nTripStep = 0;

		for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_fTripValueChl[i] = 0.0f;
			m_nrBinSwitchCount[i] = 0;
			m_nrBoutSwitchCount[i] = 0;

			for(int j = 0; j < BIBO_ACTCOUNT; j++)
			{
				m_frTimeBinAct[i][j] = 0.0f;
				m_frTimeBoutAct[i][j] = 0.0f;
			}

			m_nBinFirstChgState[i] = 0;
			m_nRampIndex[i] = -1;
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_fTripValueChlEx[i] = 0.0f;
			m_nrBinExSwitchCount[i] = 0;
			m_nBinExFirstChgState[i] = 0;

			for(int j = 0; j < BIBO_ACTCOUNT; j++)
			{
				m_frTimeBinExAct[i][j] = 0.0f;
			}

			m_nRampIndexEx[i] = -1;
		}

		for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_nrBoutExSwitchCount[i] = 0;

			for(int j = 0; j < BIBO_ACTCOUNT; j++)
			{
				m_frTimeBoutExAct[i][j] = 0.0f;
			}
		}
	}
} GradientResult_Com;

typedef struct
{
	float m_fTripValueV;//��ѹ����ֵ
	float m_fTripValueF;//Ƶ�ʶ���ֵ
	double m_dTimeBinAct[8][3]; //4�������źŵ�ǰ3�α�λ��¼
	int	m_nBinSwitchCount[8]; //��λ����
	int m_nAct;
	double m_dActTime;//ͬ���źŶ���ʱ��

	void init()
	{
		m_fTripValueV = 0;
		m_fTripValueF = 0;
		m_nAct = 0;
		m_dActTime = 0;

		for(int i = 0; i < 8; i++)
		{
			m_nBinSwitchCount[i] = 0;
			m_dTimeBinAct[i][0] = 0;
			m_dTimeBinAct[i][1] = 0;
			m_dTimeBinAct[i][2] = 0;
		}
	}
} SynResult;

typedef struct state_eventrst
{
	bool     m_bUsed;
	double   m_dEventTime;
	int      m_nEventType;//0-���������� 1-״̬���� 2-״̬�ڿ����λ
	int      m_nStateIdx;
	int      m_nBinValue;//��λ��Ŀ���ֵ
	int      m_nBinIndex;//������� 0��7
} State_EventRst;

typedef struct state_eventrsts
{
	int      m_nRstCnt;//���������
	State_EventRst m_oRst[20];
	int      m_nBinTripCnt;//��������¼
	State_EventRst m_oBinTripRst[20];
} State_EventRsts;

typedef struct
{
	unsigned char   sData[12];
	BOOL bFT3;
	long nCrc;//SV,GOOSE
	long nPort_FT3;
	long nBaud_FT3;
	long nSTMode;//00-None 01:FT3 10:PPS 11:BCode
} IECDetectItem;

typedef struct
{
	long nCount;
	IECDetectItem item[200];
} IECDetectResult;

typedef struct
{
	long nFilterVal;
} IECRecordItem_61850;

typedef struct
{
	long nBaudRate;
	long nPkgLen;
	long nPort;
} IECRecordItem_6044;

typedef struct
{
	BOOL bEnable;
	BOOL bHasSmv;
	long nCount61850;
	long nCount6044;
	IECRecordItem_61850 item61850[16];
	IECRecordItem_6044 item6044[4];
} IECRecordItems;

typedef struct
{
	long nUse;
	long nTickCnt;
	long nTickTotal;
} PowerDAMngr;

typedef struct
{
	unsigned int nModule;
	long dat[DATA_MAX];
} Drv_ComData;

//������ģ�����ݽṹ
typedef struct
{
	unsigned int nVal1;
	unsigned int nVal2;//������ֵ
} structBIStatusItem;

typedef struct
{
	unsigned int 	nSec[10];
	unsigned int 	nNSec[10];
} Drv_BiActList;

//���������ݶ������ݽṹ
typedef struct
{
	unsigned int nitem0Valid;
	Drv_BiActList item0;
	structBIStatusItem	item[BIO_MODULE_MAX];//��������
} Drv_BIStatus;

typedef struct
{
	long nCount;
	long nChanLen1[255];//���255��ͨ��
	long nChanLen2[255];
	BOOL bContainCRC[255];
} FT3DbgChanInfo;

typedef struct
{
	FT3DbgChanInfo oFT3ChanInfo[16];//��Ӧ16�����
} FT3DbgChansInfo;

class CSttDeviceBase
{
public:
	static CSttDeviceBase *g_pSttDeviceBase;
	CSttDeviceBase();
	virtual ~CSttDeviceBase();

	int m_nCommfd;
	int m_nTouchfd;
	DeviceDAPara m_oDAPara;
	DeviceDAPara m_oDAParaForTestStop;
	DeviceDAPara m_oDAParaForState2;
	BOOL m_bUseDAParaForState2;
	Drv_SysInfo m_oSysInfo;
	Drv_SysUtc m_oSysUtc;
	SwitchModules m_oSwitchModules;
	CString m_strAppVer;//���Կ��Ʒ���汾
	BOOL m_bDevStaIsInit;//����������Ϣ���ƥ����
	GradientResult_Com m_oRampRestCom;
	SynResult m_oSynResult;
	BOOL m_bCurTestIsGradient;
	long m_nIECDetectIdx;
	IecRecvCfg m_oIecRecvCfg;
	Drv_IECConfigFt3 *m_pIECConfigFt3;
	PowerDAMngr m_oPowerDAMngr;
	unsigned char m_nVoltPowerRefVal;//��ѹģ�鹦�ʴ���ֵ
	unsigned char m_nCurrPowerRefVal;//����ģ�鹦�ʴ���ֵ
	int  m_nBinRefState[MAX_BINARYIN_COUNT];//�ݴ��һ̬��������ֵ
	int  m_nBinExRefState[MAX_ExBINARY_COUNT];//�ݴ��һ̬��������ֵ
	State_EventRsts m_oStateEvents;//״̬��������¼���¼
	FT3DbgChansInfo m_oFT3DbgChansInfo;//���ڴ�ӡFT3���ĸ�ʽ��

	long m_nDeviceOnTimerMs;
	long m_nDeviceOnTimerCount;
	long m_nModuleHotCnt;
	int m_nIecPkgFormat;//0-̽��̱���,1-��������
	long m_nUseIecCfgCRC;//0-ʹ��Record�·���CRC 1-ʹ��Iec61850Config�·���CRC
	long m_nIsIecMode;//1-����IECģʽ
	unsigned int m_nRegCtrlAnalog;
	unsigned int m_nRegCtrlDigital;
	Drv_BlockPkg *m_pReplayModulesBuf;
	float *m_pReplayChsBuf;
	unsigned int m_nMainSTMode;
	unsigned int m_nBootMode;//330,0-����ģʽ��1-��չģʽ

	float m_oCurrAmp[MAX_CURRENT_COUNT];
	void SetCurrAmp_Monitor(long nIndex, float fAmp);

	void InitDASetting();
	void InitDAData();
	virtual void InitWeekOutputDAData() {}
	void SetCurrentDApara_DC(float fSum, int nModuleIndex);
	virtual void SetVoltDApara(float fVMax, float fUdc, int nModuleIndex, BOOL bIsDC);
	void SetCurrentDApara_AC(float fSum, int nModuleIndex, float fImax = 0);
	void WriteDApara(DeviceDAPara *pDAPara, BOOL IsSysDefaultOut = FALSE);
	void WriteDAparaForTestStop();
	//PN����λ��4��3U3Iģ���Դ�Ǳ괦��
	void DAValue_PN_3U3I(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
						 int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt,
								  BOOL bDC, int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_Manu_UpdateParameter(BOOL bDC);

	virtual void InitModulePowerCtrl();
	void InitSwitchModule();
	int GetDriverFd()
	{
		return m_nCommfd;
	}

	virtual BOOL OnTimer(BOOL bExec = FALSE);
	virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType);
	virtual void AnalysisLightPower(Drv_FeedBack &oDrv_FeedBack, int nModulePos);
	virtual void GetVoltCurRtData() {}

	virtual void SetSystemConfig() {}
	virtual void SetCurMergeConfig();

	virtual int InitDevice(BOOL bHasAdjFile)
	{
		return 0;   //zhouhj ���ӷ���ֵ:û�з���ֵ
	}
	virtual void CloseDevice() {m_nUseIecCfgCRC = 1;}

	virtual void SetTestStart(int nTestType) {}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput = FALSE) {}
	virtual void SetTestPara(int nTestType, char *pszBuff) {}

	virtual void SetManualBI(char *pszBuff, int nLen) {}
	virtual void SetBISetting() {}

	//virtual void SetDcModuleTap(int nTap);

	virtual int UpDateFpga(char *pszBuff, int nLen, int nModule)
	{
		return 0;
	}
	virtual void SetBinaryOutTurnOnVaule(int nValue) {}
	virtual void SetBinaryOut(BOOL bOpen = FALSE) {}
	virtual void SetRegisterValue(unsigned int nAddr, unsigned int nValue) {}

	virtual void FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen) {}
	virtual int SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen)
	{
		return 0;
	}
	virtual BOOL GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset)
	{
		return FALSE;
	}

	virtual void GetPI1000ModulesFPGAInfo() {}
public:
	//systemdefaultoutput
	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt) {}

	virtual void InitDrvResult() {}
	virtual void ProCommDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}
	//manu
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE) {}

	//moduleoutput
	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt) {}
	virtual BOOL CheckCurrLoadIsSafe(tmt_channel *pChannel, BOOL bIsDc);
	virtual BOOL CheckCurrLoadIsSafe_moduleoutput(tmt_channel *pChannel, BOOL bIsDc, PSTT_MODULE pModule);
	//harm
	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt, BOOL bIsStartTest = FALSE) {}
	BOOL GetChannelContentOK(tmt_channel &oChannel, int nModuleType, int nDirection, int nHarmIndex, float fGradientAmp, float fChMax);
	BOOL GetChannelContentOK_PF300(tmt_channel &oChannel, int nDirection, int nHarmIndex, float fGradientAmp);
	float GetChannelMax(tmt_channel &oChannel, float fBaseHz, int nDirection, int nHarmIndex, float fGradientAmp);
	BOOL CheckModuleChannel(float fChanneMax, int nChannel, PSTT_MODULE pSTT_MODULE);
	virtual int CheckHarmTestPara(tmt_HarmTest *pTmt);

	//state
	virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt) {}
	virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt) {}
	virtual void ProStateDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}
	virtual void SetStateTriger() {}

	//binarytest
	virtual void tmt_to_drv_BinaryManu(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE) {}
	virtual void tmt_to_drv_BinaryStateItem(tmt_StateParas *pTmt) {}

	//cboper
	virtual void tmt_to_drv_CboperPara(tmt_ImpBaseParas *pTmt) {}
	//abnormal
	virtual void tmt_to_drv_AbnPara(tmt_StateParas *pTmt, long nAbnType) {}
	//soe
	virtual void tmt_to_drv_soe(tmt_SoeTest *pTmt) {}
	virtual void ProSoeDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}

	//IEC61850
	virtual void SetIEC61850Para() {}
	virtual void *GetIecCfgDatasMngr()
	{
		return NULL;
	}
	virtual void SetBoMap(char *pszBuff) {}
	virtual void SetGooseSub(char *pszBuff) {}
	virtual void SetFT3SubMap(char *pszBuff) {}

	//LtReplay
	virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef) {}
	virtual BOOL getLtReplayBufferAFlag()
	{
		return TRUE;
	}
	virtual BOOL getLtReplayBufferBFlag()
	{
		return TRUE;
	}
	virtual void setLtReplayBufferABLoop(unsigned int, char *, unsigned int) {}

	//ComReplay
	virtual void tmt_to_drv_ComReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef) {}

	//pt100
	virtual void SetPtValue(unsigned int nValue) {}

	//record
	virtual void tmt_to_drv_record(tmt_RecordTest *pTmt) {}
	virtual void ProRecordDrvResult() {}

	//Swing
	virtual void tmt_to_drv_SwingTestPara(tmt_SwingParas *pTmt, int nStepCnt, char *pszDrv) {}
	virtual void tmt_to_drv_SwingAcPara(tmt_StepUI *pTmt, char *pszDrv, int nStep, int nType) {}
	virtual void SetSwingPara(char *pszDrv) {}
	virtual void ProSwingDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}

	//Syn
	virtual void tmt_to_drv_SynPara(tmt_SynParas *pTmt) {}
	virtual void ProSynDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}

	//Light ����
	virtual void ProLightDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime) {}
	virtual void tmt_to_drv_lightpara(void *pTmt) {}
	virtual void tmt_to_drv_lightangle(void *pTmt, unsigned int nType) {}

	//pis2k
	virtual void tmt_to_drv_pis2k(void *pTmt) {}
	virtual void ProPis2kDrvResult(void *pTmt) {}

	//pic200D
	virtual void tmt_to_drv_pic200d(void *pTmt) {}
	virtual void ProPic200dDrvResult(void *pTmt) {}

	//pik100
	virtual void ProPik100DrvResult() {}
	virtual void tmt_to_drv_pik100(void *pTmt) {}

	//pid01
	virtual void ProPid01DrvResult() {}
	virtual void tmt_to_drv_pid01(void *pTmt) {}
	virtual void tmt_to_drv_pid16(void *pTmt) {}

	//302Step6U6I
	virtual void SetStep6U6IStart() {}
	virtual void SetStep6U6IStop() {}

	//MUTest
	virtual void tmt_to_drv_MUTest(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE) {}
	virtual void SetRising(int nRising) {}
	virtual void SetPPSTestStart() {}
	virtual void SetPPSTestStop() {}
	virtual void SetADMUChannel(tmt_ManualTest *pTmt){}

	//iecdetect
	virtual void SetIecdetectStart(tmt_RecordTest *pTmt) {}
	virtual void SetIecdetectStop(tmt_RecordTest *pTmt) {}
	virtual void ProIecdetectDrvResult() {}

	//iedtest
	virtual void SetIEDTestStart_B2G() {}
	virtual void SetIEDTestStop_B2G() {}
	virtual void tmt_to_drv_iedtest_B2G(void *pTmt) {}
	virtual void ProIEDTestDrvResult_B2G(void *pTmt, void *pPrePara) {}
	virtual void SetIEDTestStart_G2B() {}
	virtual void SetIEDTestStop_G2B() {}
	virtual void tmt_to_drv_iedtest_G2B(void *pTmt) {}
	virtual void ProIEDTestDrvResult_G2B(void *pTmt, void *pPrePara) {}

	virtual void SetAuxDcVolt(float fUdc) {}

	//Simulation
	virtual void Load_RcdData() {}

	//LcPower
	virtual void tmt_to_drv_LcPower() {}
public:
	//Gradient
	virtual void tmt_to_drv_Gradient(tmt_GradientParas *pParas) {} //���ڲ��޲���������ģʽ
	virtual void tmt_to_drv_Gradient_NeedStepsValue(tmt_GradientParas *pParas) {} //���ڲ���������20000������ȫ��ģʽ
	virtual void ProGradientDrvResult(tmt_GradientTest *pTmt) {}
	int m_nOnTimerMs;
	long m_nCurStateCount;
	tmt_GradientParas m_oGradientParas;//���ͳһ�Ĵ���������ݱ�ģʽ����
	tmt_GradientProcess m_oGradientProcess;//���ȫ���ݱ�ģʽ��������
	vector<int> ChannelVolts, ChannelCurrs;
	void CalStepValue_Gradient(tmt_GradientParas &oGradientParas, int nHarmIndex = 1);
	void SetChannelSelect(tmt_GradientParas &oGradientParas);
	void InitParaBeforeGradient(tmt_GradientParas &oGradientParas);
	BOOL CheckChannelIsGradient(int nTmtPos, BOOL IsVolt = TRUE)
	{
		if(IsVolt)
		{
			for(unsigned int nIndex = 0; nIndex < ChannelVolts.size(); nIndex++)
			{
				if(nTmtPos == ChannelVolts.at(nIndex))
				{
					return TRUE;
				}
			}

			return FALSE;
		}
		else
		{
			for(unsigned int nIndex = 0; nIndex < ChannelCurrs.size(); nIndex++)
			{
				if(nTmtPos == ChannelCurrs.at(nIndex))
				{
					return TRUE;
				}
			}

			return FALSE;
		}
	}
	float CalWaveMaxValue(float *pfAmp, float *pfAng, float *pfFre, int nChanNum, BOOL bIsDc);
	//cycle control
public:
	virtual void DAPowerCtrl() {}
	virtual void AutoControl_PTU() {}
	virtual void SetOverLoadTime_PTU(int nTime_ms);
	virtual void SetMeasModuleChanGear(int nModuleType, int nModulePos, int nChannel, int nGearId) {}
	virtual void EventProcessEx();
	virtual void SetOutputTime(tmt_ManualTest *pManualTest, tmt_HarmTest *pHarmTest) {}
	void MeasDev_Init();
	void SetIecDetect(BOOL bEnable);
	void SetIecFilter(IECRecordItems *pRecordItems);
	BOOL GetIecPktList();
	void stt_xml_serialize_iec_rtdatas(CSttXmlSerializeBase *pXmlSerialize);
	void SetDMAType(long nDMAType);
#ifdef _PSX_QT_LINUX_
	QList<ManuRtData> m_oManuRtList;
#endif
private:
	void TranGradientChannels(tmt_GradientParas &oGradientParas, vector<int> &ChannelVolts, vector<int> &ChannelCurrs);
};

extern MEAS_DEVICE *g_MeasDevice;
extern long g_nNeedReportUTC;
extern long g_nNeedReportRTDATA;
extern long g_nNeedReportEvents;
extern long g_nNeedReportDevExcept;
extern long g_nGetSystemStateTickCnt;
void *ProIecDetectThread(LPVOID pParam);
extern CRingMemBuf *g_pIecDetectBuf;
extern float g_fAuxVolt;//����ֱ����ѹ���
extern QMutex g_oDrvMutex;

inline float translateVoltBase(unsigned short nValue, float fXS)
{
	float fv = nValue;
	fv -= 2048;
	fv = (float)(fv * fXS / 2048.0);
	return fv;
}

inline float translateCurrentVolt(unsigned short nValue)
{
	float fv = nValue;
	fv -= 2048;
	fv = (float)(fv * 25.0 * 1.13 / 2048.0);
	return fv;
}

inline float translateVolt(unsigned short nValue)
{
	float fv = nValue;
	fv -= 2048;
	fv = (float)(fv * 200 * 1.25 / 2048.0);
	return fv;
}

inline CString TransVersion(unsigned int nVal)
{
	unsigned int nVal1 = (nVal >> 16) & 0xff;
	unsigned int nVal2 = (nVal >> 8) & 0xff;
	unsigned int nVal3 = nVal & 0xff;
	CString strBoardVer;
	strBoardVer.Format("%d.%d.%d", nVal1, nVal2, nVal3);
	return strBoardVer;
}

inline float translateLightPower(unsigned short nValue)
{
	float fPower;
	fPower = nValue * 0.1;
	// fPower = fPower * 0.0039;
	// fPower += nValue >> 8;
	return fPower;
}

#endif // CSTTDEVICEBASE_H
