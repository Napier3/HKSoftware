#pragma once

#include "../SttCmd/SttCmdDefineGlobal.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

#include "SttTestEngineClientData.h"
#include "SttTestEngineBase.h"
#include "../SttTestAppConfig/SttTestAppConfigTool.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../SttTest/Common/tmt_result_def.h"
#include "../SttTest/Common/tmt_system_config.h"
#include "../SttTest/Common/tmt_pt_test.h"

#define MACROID_SttSystemDefaultOutput	"SystemDefaultOutput"
#define MACROID_SttSystemPara			"SystemConfig"
#define MACROID_PTTestPara				"SttPtTest"

extern TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;
extern STT_SystemParas g_oSystemParas;
extern tmt_PtPara g_oPTTestPara;
extern bool g_bPrintLog;
extern bool g_bSaveFile;

typedef struct stt_event_info
{
	CString m_strEventID;
	double m_fTime;
}SttEventInfo;

class CSttPowerTestEngineBase : public CSttTestMsgViewInterface, public CMacroTestEventInterface
{
public:
	CSttPowerTestEngineBase();
	virtual ~CSttPowerTestEngineBase();

public:
	CSttTestEngineClientData *m_pXClientEngine;//�����ɹ���ö����Tool�л�ȡ
	void FreeXClientEngine();

	virtual BOOL connectTestApp(const CString &strIP,long nPort,const CString &strSoftID = STT_SOFT_ID_TEST);
	virtual long SendStartCmd();
	virtual long SendStopCmd();
	virtual long SendDefaultOutputCmd();
	virtual long SendUpdateParameter();
	virtual long SendTrigger();
	virtual long SendSystemParaCmd();
	virtual long SendAuxDCOutputCmd();//zhouhj 20211016 ���͸���ֱ���������
	virtual long SendModulesGearSwitchCmd();//zhouhj 20211016 ���͸���ֱ���������
	virtual long SendChMapsConfig();
	virtual long SendIECParaCmd();
	virtual long SendPTTestParaCmd();
	virtual long SendReadDeviceParameter();//��һ�������ɹ��󣬴�װ�ö�ȡDevice��Ϣ
	virtual long SendDebugLogCmd(long nValue);//yyj add ���Ƶײ㷢�͵�����Ϣ

	virtual long Process_SysState_Log(CSttSysState &oSysState); //yyj 20210809	

	virtual void GenerateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true){};
	virtual void GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd);//zhouhj 20211016 ���ò�����ֹͣ�󱣳����������ֵ,��Ĭ�����ֵ
	virtual void GenerateTestCmdFromAuxDCOutput(CSttTestCmd &oSttTestCmd);//���ø���ֱ�����
	virtual void GenerateTestCmdFromModulesGearSwitch(CSttTestCmd &oSttTestCmd);//����ģ�鵵λ

	virtual void UpdateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true){};
	virtual void GenerateTestCmdFromSystemParas(CSttTestCmd &oSttTestCmd);
	virtual void GenerateTestCmdFromIEC(CSttParas &oSttParas){};
	virtual void GenerateTestCmdFromChMaps(CSttParas &oSttParas);
	virtual void GenerateTestCmdFromPTTestParas(CSttTestCmd &oSttTestCmd);

	/////////CSttTestMsgViewInterface//////////
	virtual void OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
	virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState){};

	////////CMacroTestEventInterface/////////
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);
	virtual void OnException(CDataGroup *pParas);
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual void OnReport(CDataGroup *pParas);
	virtual long OnUpdate(CSttParas *pParas);
	virtual long OnDisConnect();
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas);//��ȡDevice��Report��������
	virtual long OnRtData(CSttParas *pParas);
	virtual void OnTestResults(CDataGroup *pResults){};
	virtual void OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas){};
	//virtual void OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend){};//zhouhj 20210827����Gpsʱ��  OnUpdateSyncTime
	virtual long OnUpdateSyncTime(CDataGroup *pSyncTime){ return 0;};//zhouhj 2022-6-9  lijunqing 
	void UpdateIBreakUShortOverHeat(long nIBreak,long nUShort,long nOverHeat);

	//֪ͨӦ�ý���ˢ��
	CEventResult m_oCurrEventResult;	//����ˢ��
	CEventResult *m_pLastEventResult;	//�¼����һ��
	CExBaseList m_oLastEventList;//��Ż�ȡ������������һ��Event�¼�,���¼���ʱ����ɾ�� ��Ҫ���� ɾ��
//	CExBaseList m_oEventResultList;		//���Թ������ܵ��¼�����  zhouhj 20210930 û���õ�,��ʱ������ʱ,������ᵼ���ڴ�ռ������

	CEventResult *InitEvent(const CString &strEventID,double fTime,double fRealTime,const CString &strTimeStr); //yyj modify 20210902

	BOOL m_bLockFlag; //1:ͨ�����顢г����0:����
	void SetLockFlag(){ m_bLockFlag = 1; }

public:
	virtual void InitXmlKeys();
	virtual void ReleaseXmlKeys();

	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oFlushEventList;
	void AppenEventInfo(CEventResult *pEventInfo);
	void GetEventInfo(CExBaseList &oEventInfoList);

	BOOL OpenSysOutputParaFile();
//	BOOL OpenSystemParasFile();

public:
	//suyang 20230710 ����̽������
#ifdef _PSX_IDE_QT_
        virtual void SendIecDetect(long bEnable,long nFT3_CRRType,long nIecType,QList<QVector<int> > oPkgLenthList);
#endif
	virtual void SendIecRecord(CDataGroup *pIecRecordParas);


	//2022-4-13  lijunqing
	virtual void On_IecDetect(CDataGroup *pIecCb) {}

	bool m_bStarted;//2023-11-30 suyang ʹ������̨���Կ���һ̨����������£�һ̨���Կ�ʼ��������һ̨����Ӧ����
	bool m_bUpdateRtData; //20240328 suyang �Ƿ����ʵʱ����


};

extern CSttTestAppConfigTool g_oSttTestAppConfigTool;
extern CSttTestAppCfg g_oSttTestAppCfg;   

double CalcSpanTime(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd);
void InitDefaultSystemParas();
void InitDefualtSysOutputPara();
void InitDefaultPtTestPara();
void stt_xml_serialize_write_SysOutput();
