#ifndef CSTTDEVICEBASE_H
#define CSTTDEVICEBASE_H
#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTest/Common/Adjust/tmt_adjust_test.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/SttSystemConfig.h"
#include "../SttTest/Common/SttSystemDefaultOutput.h"
#include "../SttTest/Common/tmt_adjust_sys_para_binary_serialize.h"
#include "../SttTest/Common/tmt_system_config.h"
#include "../SttTest/Common/tmt_common_def.h"
#include "../SttTest/Common/tmt_soe_test.h"
#include "../SttTest/Common/tmt_record.h"
#include "../SttTest/Common/tmt_replay_test.h"
#include "../SttTest/Common/Swing/tmt_swing_test.h"
#include "../SttTest/Common/Syn/tmt_syn_test.h"
#include "../SttTest/Common/Meas/meas_define.h"
#include "../SttTest/Common/SttDcMeasCfg.h"
#include "../SttTestBase/SttTestBase.h"
#include"../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../RecordTest/SttRcdSendSocket.h"
#include "SttDeviceStatus.h"
#include "Module/Driver466/IEC_GlobalDefine.h"
#include "Module/FpgaUart/FpgaUart.h"
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
#include "QSemaphore"
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

extern pthread_mutex_t g_oTestResultMutex;
extern BOOL bIecDetectRun;
extern BOOL bIecRecordRun;
extern CString g_strDrvName;
extern CString g_strAppName;

class CSttDeviceMutex : public QMutex
{
public:
	CSttDeviceMutex()
	{
		m_bLocked = FALSE;
	}
	virtual ~CSttDeviceMutex()
	{

	}

	BOOL m_bLocked;
	QString m_strFile;
	QString m_strFunc;
	long m_nline;

	BOOL trylock(const char *pszFile, const char *pszFunc, long nline)
	{
		if(!m_bLocked)
		{
			QMutex::lock();
			m_bLocked = TRUE;
			m_strFile = pszFile;
			m_strFunc = pszFunc;
			m_nline = nline;
			return TRUE;
		}

		return FALSE;
	}

	void lock(const char *pszFile, const char *pszFunc, long nline)
	{
		QMutex::lock();
		m_bLocked = TRUE;
		m_strFile = pszFile;
		m_strFunc = pszFunc;
		m_nline = nline;
	}

	void unlock(const char *pszFile, const char *pszFunc, long nline)
	{
		QMutex::unlock();
		m_bLocked = FALSE;
		m_strFile = "";
		m_strFunc = "";
		m_nline = 0;
	}
};

extern CSttDeviceMutex g_oDrvMutex;
using namespace  std;

typedef struct
{
	unsigned int nType;//1:����ǰ 2:������
	unsigned int nUtcH;
	unsigned int nUtcL;
	unsigned int nCurStep;
	unsigned int nCurState;
} Drv_DegressData;

typedef struct
{
	unsigned int nWriteCount;
	unsigned int nReadCount;
	Drv_DegressData oData[STT_DRV_RTDATA_MSG_MAX_COUNT];
} Drv_DegressMsg;

typedef struct
{
	Drv_DegressMsg oDegressMsg;
	unsigned int nResultSize;
	unsigned int nRecordSize;
} Drv_MMapBuf;

typedef struct
{
	long m_nVerIdx;//
	BOOL m_bMouse;//0-�ޣ�1-��
	CString m_strKeyBoard;
} DevInputInfo;

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
	unsigned int	m_nBin[MAX_BINARYIN_COUNT]; //��ǰ״̬
	unsigned int	m_nBinEx[MAX_ExBINARY_COUNT]; //��ǰ״̬
}BI_STATUS;

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

typedef struct
{
	unsigned int nSample;//������
	unsigned int nEType[10];//0-��ѹ�ͣ�1-�սӵ���
	float fTripVolt[10];//���뷭ת�ж���ֵ
	unsigned int nMeasGear[10];//�ɼ���λ����
	float fCoef[10][ADJUST_MAX_GEAR_COUNT];//���忪��ɼ�У׼ϵ��
	float fZero[10][ADJUST_MAX_GEAR_COUNT];//���忪��ɼ�У׼��Ư
} Drv_BinarySetting;

enum BinaryGear
{
	Gear_Null = 0,//���ڿսӵ�
	Gear_600V = 0xe,
	Gear_100V = 0xd,
	Gear_10V = 0xb,//���ݹ��ʰ�սӵ�
	Gear_1V = 0x7,
	Gear_01V = 0xf
};

class CSttDeviceBase
{
public:
	static CSttDeviceBase *g_pSttDeviceBase;
	CSttDeviceBase();
	virtual ~CSttDeviceBase();
	void ProTestResults();

	int m_nCommfd;
	int m_nTouchfd;
	DeviceDAPara m_oDAPara;
	DeviceDAPara m_oDAParaForTestStop;
	DeviceDAPara m_oDAParaForState2;
	DeviceDAPara m_oDAParaForSysput;
	DeviceDAPara m_oCurDAPara;//��ǰ���ʵ�Դ
	BOOL m_bUseDAParaForState2;
	Drv_SysInfo m_oSysInfo;
	Drv_SysUtc m_oSysUtc;
	SwitchModules m_oSwitchModules;
	CString m_strMngrVer;//���Թ������汾
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
	Drv_BinarySetting m_oBinSetting;
	BI_STATUS m_oBIStatus;
	BOOL m_bTestStarting;//��SttTestBase ͬ������

	long m_nDeviceOnTimerCount;
	long m_nModuleHotCnt;
	long m_nUseIecCfgCRC;//0-ʹ��Record�·���CRC 1-ʹ��Iec61850Config�·���CRC
	long m_nIsIecMode;//0-IEC����ģʽ,1-����̽��ģʽ��2-���ļ���ģʽ
	unsigned int m_nRegCtrlAnalog;
	unsigned int m_nRegCtrlDigital;
	Drv_BlockPkg *m_pReplayModulesBuf;
	Drv_MMapBuf  *m_pMMapBuf;
	float *m_pReplayChsBuf;
	unsigned int m_nMainSTMode;
	unsigned int m_nBootMode;//330,0-����ģʽ��1-��չģʽ

	void InitDASetting();
	void InitDAData();
	virtual void InitWeekOutputDAData() {}
	void SetCurrentDApara_DC(float fSum, int nModuleIndex);
	virtual void SetVoltDApara(float fVMax, float fUdc, int nModuleIndex, BOOL bIsDC);
	void SetCurrentDApara_AC(float fSum, int nModuleIndex, float fImax = 0);
	void WriteDApara(DeviceDAPara *pDAPara, BOOL IsSysDefaultOut = FALSE);
	void WriteDAparaForTestStop();

	virtual void DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt,
								  BOOL bDC, int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_CommAsync(tmt_AsyncModules *pAsyncModules, BOOL bDC, int nDirection, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_Manu_UpdateParameter(BOOL bDC);
	virtual void DAValueCalc_AsyncManu_UpdateParameter();

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

	void SaveSystemConfig();
	void ReadSystemConfig();
	virtual void SetSystemConfig() {}
	virtual void SetCurMergeConfig();

	virtual int InitDevice(BOOL bHasAdjFile)
	{
		return 0;   //zhouhj ���ӷ���ֵ:û�з���ֵ
	}
	virtual void CloseDevice()
	{
		if(bIecDetectRun)
		{
			bIecDetectRun = FALSE;
			Sleep(120);
		}

		if(g_oSttRcdSendSocket.m_bRunning)
		{
			pthread_mutex_lock(&g_oSttRcdSendMutex);
		}
		g_oSttRcdSendSocket.m_bRunning = FALSE;
		if(bIecRecordRun)
		{
			bIecRecordRun = FALSE;
			Sleep(120);
		}

		m_nUseIecCfgCRC = 1;
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd,0xA00,0);//�ر�DMA
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

	virtual void ExitRcdSend()
	{
		m_nUseIecCfgCRC = 1;
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd,0xA00,0);//�ر�DMA
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

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
	void InitAsyncManu();
	void FreeAsyncManu();
	virtual void tmt_to_drv_AsyncManu(tmt_AsyncManualTest *pTmt, BOOL bIsStartTest = FALSE) {}

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
	void InitAsyncState();
	void FreeAsyncState();
	virtual void tmt_to_drv_AsyncStatePara(tmt_AsyncStateParas *pTmt) {}
	virtual void tmt_to_drv_AsyncStateItem(tmt_AsyncStateParas *pTmt) {}
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
	virtual void *GetIec61850CfgMngr()
	{
		return NULL;
	}
	virtual void SetBoMap(char *pszBuff) {}
	virtual void SetGooseSub(char *pszBuff) {}
	virtual void SetFT3SubMap(char *pszBuff) {}
	virtual void SetFT3SubCRC(char *pszBuff){}

	//LtReplay
	virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef) {}
	virtual int getLtReplayBufferFlag()
	{
		return 0;
	}
	BOOL CheckBufferA(int nFlag)
	{
		return nFlag & 0x02;
	}
	BOOL CheckBufferB(int nFlag)
	{
		return nFlag & 0x04;
	}
	virtual void setLtReplayBufferABLoop(unsigned int, char *, unsigned int) {}

	//ComReplay
	virtual void tmt_to_drv_ComReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef) {}

	//pt100
	virtual void SetPtValue(unsigned int nValue) {}

	//record
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

	//MUTest
	virtual void tmt_to_drv_MUTest(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE) {}
	virtual void tmt_to_drv_MUHarmTest(tmt_HarmTest *pTmt, BOOL bIsStartTest = FALSE) {}
	virtual void SetRising(int nRising) {}
	virtual void SetPPSTestStart() {}
	virtual void SetPPSTestStop() {}
	virtual void SetADMUChannel(tmt_ManualTest *pTmt){}
	virtual void SetADMUChannel(tmt_HarmTest *pTmt){}

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

	long m_nCurStateCount;
	tmt_GradientParas m_oGradientParas;//���ͳһ�Ĵ���������ݱ�ģʽ����
	tmt_GradientProcess m_oGradientProcess;//���ȫ���ݱ�ģʽ��������
	vector<int> ChannelVolts, ChannelCurrs,ChannelVolts2, ChannelCurrs2;
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
	virtual BOOL SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime) {return FALSE;}
	virtual void Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize);
	void MeasDev_Init();
	void SetIecDetect(BOOL bEnable, long nIecType);
	void SetIecFilter(IECRecordItems *pRecordItems);
	BOOL GetIecPktList();
	BOOL stt_xml_serialize_iec_rtdatas(CSttXmlSerializeBase *pXmlSerialize);
	void SetDMAType(long nDMAType);
#ifdef _PSX_QT_LINUX_
	QList<ManuRtData> m_oManuRtList;
#endif
	CDataGroup m_oUserSetting;//�洢ά���û�ϰ�������ò���
	virtual void SetSystemLocalTime(CString strTime_t){}
	long m_nSetSysTmCnt;//�Ե�һ��TEST��½�û�Ϊ׼
	DevInputInfo m_oDevInputInfo;
	virtual BOOL GetDevInputInfo(){return FALSE;}
	unsigned int m_nCurBinaryCode[10];//��ǰ�ɼ�����ֵ
	unsigned int m_nCurBinaryGear[10];//��ǰ���õĵ�λ
	unsigned int m_nCurnEType[10];//��ǰ���õ�ģʽ
	unsigned int m_nReadInCode_I;//����ֱ������������ֵ
	unsigned int m_nReadInCode_V;//����ֱ��������ѹ��ֵ
	unsigned int m_nSetAmpPowerCnt;//���ù��ŵ�Դ����
	virtual BOOL GetBinaryVolt(){return FALSE;}
	virtual BOOL GetBinConfig(){return TRUE;}

	double CalDCMeas(BOOL bVolt, unsigned int nCode)
	{
		double fRet = 0;
		double fSign = 1.0;
		if(nCode >= 0x800000)
		{
			//����
			nCode = 0x1000000 - nCode;
			fSign = -1.0;
		}

		fRet = nCode/8388607.0; //0x7FFFFF
		fRet = 5.0*fRet*fSign;

		float fCoef = 1.0f;
		double fZero = 0.0f;

		PSTT_DC_ADJUST pDC_ADJUST = NULL;
		if(bVolt)
		{
			fRet = 0 - fRet/51.0*300;
			pDC_ADJUST = &g_theDeviceSystemParameter->m_oDCV;
			if(g_oDcMeasCfg.m_nDCInGear_I == 1)
			{
				return 0.0;
			}
		}
		else
		{
			fRet = 0 - fRet/8.2*5.1/50;
			pDC_ADJUST = &g_theDeviceSystemParameter->m_oDCI;
			if(g_oDcMeasCfg.m_nDCInGear_I == 1)
			{
				fRet = fRet/16.0;
			}
		}

		long nGearCount = pDC_ADJUST->m_nGearCount;
		if(nGearCount > 0)
		{
			fCoef = pDC_ADJUST->m_oGearAdj[nGearCount - 1].m_oAdjItem.m_fCoef;
			fZero = pDC_ADJUST->m_oGearAdj[nGearCount - 1].m_oAdjItem.m_fZero;
		}

		for(int i = 0;i < nGearCount && i < ADJUST_MAX_GEAR_COUNT;i++)
		{
			if(fRet < pDC_ADJUST->m_oGearAdj[i].m_fGearValue)
			{
				fCoef = pDC_ADJUST->m_oGearAdj[i].m_oAdjItem.m_fCoef;
				fZero = pDC_ADJUST->m_oGearAdj[i].m_oAdjItem.m_fZero;
				break;
			}
		}

		fRet = fRet*(double)fCoef + fZero;

		return fRet;
	}

	float CalBinaryVolt(unsigned int nCh, unsigned int nGear, unsigned int nBinaryCode)
	{
		double fValue = 0;
		unsigned int nGearIndex = 0;
		if(nGear == Gear_Null)
		{
			return 0;
		}

		if(nBinaryCode >= 0x80000000)
		{
			nBinaryCode -= 0x80000000;
			nBinaryCode = nBinaryCode>>16;
			fValue = nBinaryCode/32767.0;
		}
		else
		{
			nBinaryCode = 0xFFFF0000 - nBinaryCode;
			nBinaryCode -= 0x80000000;
			nBinaryCode = nBinaryCode>>16;
			fValue = nBinaryCode/32767.0;
			fValue = 0 - fValue;
		}

		switch(nGear)
		{
		case Gear_01V:
		{
			nGearIndex = 0;
			fValue = fValue/2000.0;
		}
			break;
		case Gear_1V:
		{
			nGearIndex = 1;
			fValue = fValue/380.5668;
		}
			break;
		case Gear_10V:
		{
			nGearIndex = 2;
			fValue = fValue/54.4105;
		}
			break;
		case Gear_100V:
		{
			nGearIndex = 3;
			fValue = fValue/5.982;
		}
			break;
		case Gear_600V:
		{
			nGearIndex = 4;
			fValue = fValue/(0.9995002 * 1.07);
		}
			break;
		}

		fValue = fValue*(505.1 * 2.048);
		float fCoef = m_oBinSetting.fCoef[nCh][nGearIndex];
		float fZero = m_oBinSetting.fZero[nCh][nGearIndex];
		fValue -= fZero;
		if(fCoef < 0.000001)
		{
			return 0;
		}
		fValue = fValue/fCoef;

		return (float)fValue;
	}

	unsigned int GetGearIndex_ByValue(unsigned int nGear)
	{
		unsigned int nIndex = 0;
		switch(nGear)
		{
		case Gear_Null:
		{

		}
			break;
		case Gear_01V:
		{
			nIndex = 0;
		}
			break;
		case Gear_1V:
		{
			nIndex = 1;
		}
			break;
		case Gear_10V:
		{
			nIndex = 2;
		}
			break;
		case Gear_100V:
		{
			nIndex = 3;
		}
			break;
		case Gear_600V:
		{
			nIndex = 4;
		}
			break;
		}

		return nIndex;
	}

	unsigned int GetGear_ByValue(float fVolt)
	{
		if(fVolt > 140.0)
		{
			return Gear_600V;
		}
		else if(fVolt > 14.0)
		{
			return Gear_100V;
		}
		else if(fVolt > 1.4)
		{
			return Gear_10V;
		}
		else if(fVolt > 0.14)
		{
			return Gear_1V;
		}
		else
		{
			return Gear_01V;
		}
	}

	void Set_BinaryGear(Drv_BinarySetting *pBinSetting)
	{
		unsigned int nCode = 0;
		for(int i = 0;i < 8;i++)
		{
			if(pBinSetting->nEType[i])
			{
				nCode += 0xb<<4*i;//�սӵ�����ڲ�10������Դ
			}
			else
			{
				nCode += pBinSetting->nMeasGear[i]<<4*i;
			}
		}
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x70004070, nCode);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		if(pBinSetting->nEType[8])
		{
			nCode = 0xb;
		}
		else
		{
			nCode = pBinSetting->nMeasGear[8];
		}
		if(pBinSetting->nEType[9])
		{
			nCode += 0xb<<4;
		}
		else
		{
			nCode += pBinSetting->nMeasGear[9]<<4;
		}
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x70004074, nCode);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

	double TransValue_ByGear(double fTripVolt, unsigned int nGear, double fCoef, double fZero)
	{
		fTripVolt = (fTripVolt * fCoef + fZero) / (505.1 * 2.048);
		if(nGear == Gear_600V)
		{
			return fTripVolt * 0.9995002 * 1.07;
		}
		else if(nGear == Gear_100V)
		{
			return fTripVolt * 5.982;
		}
		else if(nGear == Gear_10V)
		{
			return fTripVolt * 54.4105;
		}
		else if(nGear == Gear_1V)
		{
			return fTripVolt * 380.5668;
		}
		else if(nGear == Gear_01V)
		{
			return fTripVolt * 2000;
		}
		else
		{
			return 0;
		}
	}

	void Set_BinaryConfig(Drv_BinarySetting *pBinSetting)
	{
		//����ģʽ
		unsigned int nCode = 0;
		if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
		{
			nCode |= 1<<31;//��ѹ�ɼ���·�Ϳ���
		}

		for(int i = 0;i < 10;i++)
		{
			m_nCurnEType[i] = pBinSetting->nEType[i];
			if(pBinSetting->nEType[i])
			{
				if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
				{
					m_nCurBinaryGear[i] = Gear_10V;//���ʰ�սӵ�
					nCode |= 1<<i;
				}
				else
				{
					m_nCurBinaryGear[i] = Gear_Null;
				}
			}
			else
			{
				m_nCurBinaryGear[i] = pBinSetting->nMeasGear[i];
			}
		}

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);

		unsigned int nAddr[5] = {0x70004068,0x7000406c,0x70005068,0x7000506c,0x70005070};
		ioctl(m_nCommfd, 0x7000407c, (200<<10)|nCode);//bit25~bit10 = 200

		nCode = 0;
		//���ݵ�λ��ʽ�����ÿ�����ֵ����ֵ
		double fTemp;
		double fTripVolt;
		unsigned int nTemp;
		for(int i = 0;i < 10;i++)
		{
			fTripVolt = pBinSetting->fTripVolt[i];
			long nGearIndex = GetGearIndex_ByValue(pBinSetting->nMeasGear[i]);

			if(i%2 == 0)
			{
				if(pBinSetting->nEType[i])
				{
					nCode = 0xAA00<<16;
				}
				else
				{
					fTemp = TransValue_ByGear(fTripVolt,pBinSetting->nMeasGear[i],
											  pBinSetting->fCoef[i][nGearIndex],pBinSetting->fZero[i][nGearIndex]);
					nTemp = (fTemp * 0x7FFF) + 0x8000;//������ֵ
					nCode = nTemp<<16;
				}
			}
			else
			{
				if(pBinSetting->nEType[i])
				{
					nCode += 0xAA00;//С��6.23V��պ�
				}
				else
				{
					fTemp = TransValue_ByGear(fTripVolt,pBinSetting->nMeasGear[i],
											  pBinSetting->fCoef[i][nGearIndex],pBinSetting->fZero[i][nGearIndex]);
					nTemp = (fTemp * 0x7FFF) + 0x8000;
					nCode += nTemp;
				}

				ioctl(m_nCommfd, nAddr[i/2], nCode);
			}
		}

		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

	void Reset_BinaryConfig()
	{
		Set_BinaryConfig(&m_oBinSetting);
	}
private:
	void TranGradientChannels(tmt_GradientParas &oGradientParas, vector<int> &ChannelVolts,
							  vector<int> &ChannelCurrs,vector<int> &ChannelVolts2, vector<int> &ChannelCurrs2);
	void *m_shm;// = NULL;
	int m_nShareMemoryId;// = -1;
	long m_nShmkey;// = 1234;

//UTC Info
public:
	void GetUtcInfo(Drv_SysUtc *pSysUtc);
	char *m_pDrvUtcBase;
//Module Info
public:
	virtual void GetModuleInfo(Drv_SysInfo *pSysInfo);
	char *m_pDrvModuleBase;
	BOOL GetCurDAPara()
	{
		//��ȡ��ǰӲ���Ĺ��ʲ���
		long ret;
		DeviceDAPara oCurDAPara;
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ret = read(m_nCommfd, &oCurDAPara, 0x262);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		if(ret == sizeof(DeviceDAPara))
		{
			memcpy(&m_oCurDAPara,&oCurDAPara,sizeof(DeviceDAPara));
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
};

extern MEAS_DEVICE *g_MeasDevice;
extern long g_nNeedReportUTC;
extern long g_nNeedReportRTDATA;
extern long g_nNeedReportEvents;
extern long g_nNeedReportDevExcept;
extern long g_nGetSystemStateTickCnt;
extern long g_nTmtParaMode;
extern long g_nEnableDCCurr;
extern long g_nRTDATAMode;

void *ProIecDetectThread(LPVOID pParam);
void *IecHeaderCapThread(LPVOID pParam);
void *IecPkgCapThread(LPVOID pParam);
void *ProTestResultThread(LPVOID pParam);
extern CRingMemBuf *g_pIecDetectBuf;
extern float g_fAuxVolt;//����ֱ����ѹ���
extern long g_nLogPrintIsZN;//1-���ģ�0-Ӣ��

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
