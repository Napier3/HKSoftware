#pragma once

#include <QTimer>
#include "NGDSmartTestGlobalDefine.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgDatasMngr.h"
#include "..\SttTestAppConfig\SttTestAppConfigTool.h"
#include "..\Engine\SttTestEngineClientData.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDeviceMngr.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "..\Engine\SttTestEngineBase.h"
#include "..\TestClient\SttMacroTestInterface.h"
#include "..\..\AutoTest\Module\GuideBook\GuideBook.h"
#include "..\SmartCap\X61850CapBase.h"
#include "..\..\AutoTest\Module\XSttAtsTestClientImp.h"
#include "..\SmartTestInterface\XSmartTestEventInterface.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGinDatas.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGoutDatas.h"
#include "..\KeyDb\XKeyDB.h"

class NGDSmartTestWinFrameBase:public CSttTestMsgViewInterface, public CMacroTestEventInterface, public CXSmartTestEventInterface
{
public:
	NGDSmartTestWinFrameBase();
	~NGDSmartTestWinFrameBase();

	long m_nTestMode;//��ͬ�Ĳ��Թ����ߵ����̲�һ��
	long m_nPage;
	BOOL m_bLoadSCDFile;//�Ƿ��Ѿ�����SCD�ļ�
	CString m_strPage[7];//���ҳ���Ӧ�����ƣ�ѡ�����������ٽ��г�ʼ��
	CString m_strGbRptFile;//�Զ������õ�GbRpt�ļ�
	CString m_strSmartTestModFile;//�Զ������õ�ģ���ļ�
	CSclIed *m_pSelectIed;//��ǰѡ��ı���װ��IED��ͨ�����ȥ�����滻�Զ�����ģ������豸ģ��

	CXKeyDB m_oKeyDB;
	CX61850CapBase m_oX61850CapBase;
	CCapDeviceMngr m_oRecordDevice; //¼����װ��
	CSclCtrls m_oSelectedSclCtrlsRef;//ѡ��Ŀ��ƿ�����ͨ�����ȥSCD����IecCfg
	CDataGroup m_oTestFuntions;

	CSclStation m_oSclStation;//��Ž����õ�SCD�����ݽṹ
	CGuideBook m_oGuideBook;//�Զ������õ�ģ���ļ�
	CDvmDevice m_oDvmDevice;//����ѡ��Ŀ��ƿ��Լ�SCD���ɵ��豸����ģ�ͣ���󱣴浽�̶�·���¹�Engine�Լ��Զ�����ʹ�ã�ͨ������������豸����ģ��
	CDvmDevice m_oDvmForProtect;//����װ���õ��豸����ģ��
	CIecCfgDatasMngr m_oIecDatasMngr;//����ܵ����ɵ�Iec���ã�����̽�⵽�ķ����Լ����ж�Ӧ�Ķ��ģ�ͨ�����������Iec�����ļ�
	CIecCfgDatasMngr m_oIecDatasForDetectCbs;//̽�⵽�Ŀ��ƿ�󶨵�Iec����
	CIecCfgGinDatas* m_pIecCfgGinDatas;
	CIecCfgGoutDatas* m_pIecCfgGoutDatas;
	CIecCfgDatasMngr m_oIecDatasMngrForProtect;//����װ����
	QTimer m_oTimerForHeartBeat;//��������
	CSttTestEngineClientData *m_pXClientEngine;//�����ɹ���ö����Tool�л�ȡ
	BOOL m_bConnected;//����״̬
	BOOL m_SelectCbsChanged;//ѡ��Ŀ��ƿ��Ƿ�ı�

	CXSttAtsTestClientImp *m_pSmartTestClient;//���ں��Զ�����ͨѶ�Ŀͻ���

public://�Ͳ�����ͨѶ����ӿ�
//	virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState){};

	////////CMacroTestEventInterface/////////
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas){};
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas){};
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults){};
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults){};
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){};
	virtual long OnRtData(CSttParas *pParas);//�����ƿ�Ľӿ�


public://�Զ�����ͨѶӦ�����ӿ�
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect){return 0;};
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	//virtual long OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	//2021.0802  shaolei
	//strEventIDȡֵ��Χ��ExportBegin| ExportFinish����ExportFinishʱ���ٵ���GetReportFiles����ȡÿ�ݱ���ľ���·����
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex,
		const CString strGbrptFile, const CString strDocFile, const CString strXmlFile) { return 0; }
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent){return 0;};
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent){return 0;};
	virtual long OnTestCreated(const CString& strDeviceID){return 0;};
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID){return 0;};
	//add by shaolei  2021-08-03
	//TestID = BenchSN  strDeviceState = �ϸ�|���ϸ�
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState){return 0;};
	virtual long OnTestProcess(CExBaseList* pSttParas){return 0;};
	virtual long OnReTestFinished(CExBaseList* pSttParas){return 0;};
	//add by shaolei 20210805
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){return 0;};
	//lijunqing 2022-6-26
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){return 0;};
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){return 0;};  //lijunqing 2022-6-27  ֱ�Ӵ������ݶ��󣬷��㴦�����ת��ΪXML����JSON�Ȳ�ͬ�ĸ�ʽ
	virtual long On_Ats_CreateTest(const CString &strGbrptFile){return 0;};  //shaolei 20220707  CreateTest��REPLY������gbrptfile��ȫ·��
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd){return 0;};  //shaolei 20220718  AdjustMainWnd��REPLY������SmartTest��MainWnd

public:
	virtual void InitUI() = 0;
	virtual CString GetSmartTestModFile() = 0;
	virtual void UpdateView() = 0;//�漰������ˢ��������ӿڣ�����ʵ�ֵ��̳����Ľ�����
	void InitKeyDB();
	void InitGooseInOutData();//����m_oIecDatasMngr��ʼ��gooseIn gooseout����
	void UpdateRecordDevices();//��ѡ�����������Ҫ¼����װ��
	void InitCtrlsByRecordDevs(CCapDeviceMngr *pRecordDevs);//��¼��װ������ת��Ϊ���ƿ�����
	void InitIecCfgs();//ͨ�����ƿ�����ȥ����IecCfg
	void InitDevMods();//ͨ��ǰ�������ȥ��ʼ���豸����ģ��
	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj ����SCD,����SCD�ļ��ж�Ӧ��AppID���µ�ǰ���ƿ�����
	virtual void SendIecDetect(long bEnable);//�·�̽������
	virtual void On_IecDetect(CDataGroup *pIecCb);//���ݴ������ı�����ӿ��ƿ�
	BOOL connectTestApp(const CString &strIP,long nPort,const CString &strSoftID = STT_SOFT_ID_TEST);
	void InitResource();//��Դ�ĳ�ʼ��
	void ReleaseResource();//��Դ���ͷ�
	void InitForEntireyIntervalTest();//������������ĳ�ʼ��
	void InitForProtectorTest();//����װ�ò�����ĳ�ʼ��
	void InitForCollectExecuteUnitTest();//�ɼ�ִ�е�Ԫ������ĳ�ʼ��
	void ExportDvmModFile(CString strDvmModFilePath = _T(""));//�����豸����ģ��
	void ExportIecCfgFile(CString strIecCfgFile = _T(""));//����Iec�����ļ�
	void ReplaceIEDForSmartTest(CSclIed *pIed);//�Զ�����ģ���滻
	void CreatAutoTest();//�����Զ�����
	void OpenGbRptFile(const CString &strFilePath);
	void RemoveCapGooseDevice();
	void RemoveCap92Device();
	void AddGsInCtrlsFromGsOutCtrl(CSclCtrlGsOut  *pSclCtrlGsOut);

};

extern NGDSmartTestWinFrameBase *g_NGDSmartTestWin;