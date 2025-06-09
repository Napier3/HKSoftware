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

	long m_nTestMode;//不同的测试功能走的流程不一样
	long m_nPage;
	BOOL m_bLoadSCDFile;//是否已经导入SCD文件
	CString m_strPage[7];//存放页码对应的名称，选择完测试项后再进行初始化
	CString m_strGbRptFile;//自动测试用的GbRpt文件
	CString m_strSmartTestModFile;//自动测试用的模版文件
	CSclIed *m_pSelectIed;//当前选择的保护装置IED，通过这个去生成替换自动测试模版里的设备模型

	CXKeyDB m_oKeyDB;
	CX61850CapBase m_oX61850CapBase;
	CCapDeviceMngr m_oRecordDevice; //录波的装置
	CSclCtrls m_oSelectedSclCtrlsRef;//选择的控制块链表，通过这个去SCD生成IecCfg
	CDataGroup m_oTestFuntions;

	CSclStation m_oSclStation;//存放解析好的SCD的数据结构
	CGuideBook m_oGuideBook;//自动测试用的模型文件
	CDvmDevice m_oDvmDevice;//根据选择的控制块以及SCD生成的设备数据模型，最后保存到固定路径下供Engine以及自动测试使用，通过这个来导出设备数据模型
	CDvmDevice m_oDvmForProtect;//保护装置用的设备数据模型
	CIecCfgDatasMngr m_oIecDatasMngr;//最后总的生成的Iec配置，包括探测到的发布以及所有对应的订阅，通过这个来导出Iec配置文件
	CIecCfgDatasMngr m_oIecDatasForDetectCbs;//探测到的控制块绑定的Iec配置
	CIecCfgGinDatas* m_pIecCfgGinDatas;
	CIecCfgGoutDatas* m_pIecCfgGoutDatas;
	CIecCfgDatasMngr m_oIecDatasMngrForProtect;//保护装置用
	QTimer m_oTimerForHeartBeat;//用于心跳
	CSttTestEngineClientData *m_pXClientEngine;//联机成功后该对象从Tool中获取
	BOOL m_bConnected;//联机状态
	BOOL m_SelectCbsChanged;//选择的控制块是否改变

	CXSttAtsTestClientImp *m_pSmartTestClient;//用于和自动测试通讯的客户端

public://和测试仪通讯的虚接口
//	virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState){};

	////////CMacroTestEventInterface/////////
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas){};
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas){};
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults){};
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults){};
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){};
	virtual long OnRtData(CSttParas *pParas);//传控制块的接口


public://自动测试通讯应答的虚接口
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect){return 0;};
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	//virtual long OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	//2021.0802  shaolei
	//strEventID取值范围：ExportBegin| ExportFinish。当ExportFinish时，再调用GetReportFiles，获取每份报告的绝对路径；
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex,
		const CString strGbrptFile, const CString strDocFile, const CString strXmlFile) { return 0; }
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent){return 0;};
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent){return 0;};
	virtual long OnTestCreated(const CString& strDeviceID){return 0;};
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID){return 0;};
	//add by shaolei  2021-08-03
	//TestID = BenchSN  strDeviceState = 合格|不合格
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState){return 0;};
	virtual long OnTestProcess(CExBaseList* pSttParas){return 0;};
	virtual long OnReTestFinished(CExBaseList* pSttParas){return 0;};
	//add by shaolei 20210805
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){return 0;};
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){return 0;};
	//lijunqing 2022-6-26
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){return 0;};
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){return 0;};  //lijunqing 2022-6-27  直接传入数据对象，方便处理对象转换为XML或者JSON等不同的格式
	virtual long On_Ats_CreateTest(const CString &strGbrptFile){return 0;};  //shaolei 20220707  CreateTest的REPLY，返回gbrptfile的全路径
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd){return 0;};  //shaolei 20220718  AdjustMainWnd的REPLY，返回SmartTest的MainWnd

public:
	virtual void InitUI() = 0;
	virtual CString GetSmartTestModFile() = 0;
	virtual void UpdateView() = 0;//涉及到界面刷新做成虚接口，具体实现到继承它的界面类
	void InitKeyDB();
	void InitGooseInOutData();//根据m_oIecDatasMngr初始化gooseIn gooseout数据
	void UpdateRecordDevices();//勾选结束后更新需要录波的装置
	void InitCtrlsByRecordDevs(CCapDeviceMngr *pRecordDevs);//将录波装置链表转换为控制块链表
	void InitIecCfgs();//通过控制块链表去生成IecCfg
	void InitDevMods();//通过前面的配置去初始化设备数据模型
	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj 查找SCD,根据SCD文件中对应的AppID更新当前控制块内容
	virtual void SendIecDetect(long bEnable);//下发探测命令
	virtual void On_IecDetect(CDataGroup *pIecCb);//根据传回来的报文添加控制块
	BOOL connectTestApp(const CString &strIP,long nPort,const CString &strSoftID = STT_SOFT_ID_TEST);
	void InitResource();//资源的初始化
	void ReleaseResource();//资源的释放
	void InitForEntireyIntervalTest();//整体间隔测试项的初始化
	void InitForProtectorTest();//保护装置测试项的初始化
	void InitForCollectExecuteUnitTest();//采集执行单元测试项的初始化
	void ExportDvmModFile(CString strDvmModFilePath = _T(""));//导出设备数据模型
	void ExportIecCfgFile(CString strIecCfgFile = _T(""));//导出Iec配置文件
	void ReplaceIEDForSmartTest(CSclIed *pIed);//自动测试模型替换
	void CreatAutoTest();//创建自动测试
	void OpenGbRptFile(const CString &strFilePath);
	void RemoveCapGooseDevice();
	void RemoveCap92Device();
	void AddGsInCtrlsFromGsOutCtrl(CSclCtrlGsOut  *pSclCtrlGsOut);

};

extern NGDSmartTestWinFrameBase *g_NGDSmartTestWin;