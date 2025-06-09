#ifndef CSTTTESTCTRLCNTRBASE_H
#define CSTTTESTCTRLCNTRBASE_H

#include "../UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../SttTest/Common/tmt_result_def.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../61850/Module/SCL/SclIecCfgDatas.h"

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
#include "../SttCmd/GuideBook/SttReports.h"
#endif

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
#include "../../../AutoTest/Module/GuideBook/Reports.h"
#endif
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../SttCmd/GuideBook/SttContents.h"
#include "../SttSocket/SttCmdOverTimeMsgRcv.h"

class CSttTestCtrlCntrMsgInterface
{
public:
// 	virtual long OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
// 		long nPowerAC, long nBatCap ,long nUSB){	return 0; };
        virtual long OnUpdateSyncTime(CDataGroup *pSyncTime);
	virtual long OnUpdateException(){return 0;}//20220914 zhouhj 更新异常信息
	virtual long OnItemStateChanged(CExBaseObject *pItem) = 0;
	virtual long OnTestFinished() = 0;
	virtual long OnTestStarted() = 0;
	virtual long OnTestStoped() = 0;
	virtual long OnTestCreated() = 0;
	virtual void OnReport(CExBaseObject *pItem) = 0;
        virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup);
	virtual void OnAtsGenerate() = 0;
	virtual void OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent=FALSE,BOOL bIsInternationalMode = FALSE) = 0;//zhouhj 2024.7.3 增加参数3更新控件树
	virtual void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp) = 0;
	virtual void OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList) = 0;
	virtual void OnAtsQueryItem(CExBaseObject *pItemPara) = 0;  //2022-9-13  lijunqing
	virtual void OnInputData(CSttParas *pParas,CExBaseList *pMsgs) = 0;  //SHAOLEI  2023-7-21
	virtual void OnTestDisconnected() = 0; //shaolei 2023-9-19 断链
        virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);

};

class CSttTestCtrlCntrBase
{
public:
    CSttTestCtrlCntrBase();
    virtual ~CSttTestCtrlCntrBase();

	virtual void SetSttTestCtrlCntrMsgInterface(CSttTestCtrlCntrMsgInterface *pTestCtrlCntrMsg)	{	m_pTestCtrlCntrMsg = pTestCtrlCntrMsg;	}
    virtual void SetCurrTestItem(CExBaseObject *pCurrTestItem);
    virtual CExBaseObject *GetCurrTestItem();
	virtual CExBaseObject* GetGuideBook()	;
        virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml,const CString &strParentPath);

    virtual BOOL StartTest(CDataGroup *pCurrentUIParas);
    virtual BOOL StopTest();
	virtual long SendManuTrigger();
	//add by shaolei 20220319  //根据项目ID，查找所有的项目
	virtual void GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList); 

	//2022-3-29  lijunqing
	virtual long TestItem(const CString &strItemPath);
	virtual long TestFrom(const CString &strItemPath);

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
    virtual void FillReport(CReports *pReports){}
#endif

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
  virtual void FillReport(CSttReports *pSttReports);
#endif

    virtual CExBaseList *GetReports(){ return NULL; }
        virtual void GetEventInfo(CExBaseList& oInfoList);
	virtual CExBaseList* GetTestGlobalParas(){return NULL;}//zhouhj 20220913 增加用于获取短路、过载、过热等状态

	virtual bool IsTestStarted(){ return false; };
	virtual bool IsTestAppConnect(){ return false; };

        virtual void NewTest(CDataGroup *pDevice, CDataGroup *pTestApp, CDataGroup *pCommConfig);
protected:
    CExBaseObject *m_pCurrTestItem;   //当前执行的测试项目
	CSttTestCtrlCntrMsgInterface *m_pTestCtrlCntrMsg;
	CSttMacroTestUI_TestMacroUI *m_pCurrTestMacroUI;  //2022-3-11  lijunqing  for debug

public:
	//测试功能参数编辑
	CDataGroup m_oTestMacroUI_Paras;  //当前测试功能页面的参数
	CExBaseObject *m_pCurrEditMacroItems;   //当前测试功能对应的测试项目或者是测试项目分类
	CDataGroup m_oTestReportHead;//当前报告头参数 sf 20220217
	CEventResult m_oCurrEventResult; //当前事件对象
	tmt_BinaryConfig m_oBinaryConfig;//开关量
	CSttTestResourceBase *m_pSttTestResouce;//zhouhj 总的软件资源,只有一个
	CSclStation m_oSclStation;//增加用于存储当前SCD文件中的全部控制块内容,用于IEC配置和IEC探测 zhouhj 20221206

	virtual void ConnectAtsServer();
	virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void GetMacroUI_GbItems(CString &strMacroUI_Items);
	void GetReportHeadFile(CString &strFile);
	void OpenReportHead();
	void SaveReportHead();
	void stt_OpenHdRsFile(const CString &strHdRsFile);
	CString GetCurrMacroUIParasFilePath();

	void InitDefaultHdRs();//zhouhj 20220402 初始化一个同步模式的最大化的软件资源

	//模板生成相关的接口
	virtual long Ats_GenerateTemplate();//单个功能的模板生成
	virtual long Ats_CreateTemplate();//zhouhj 2024.7.8
	virtual long Ats_UpdateReportHead();//更新报告头  zhouhj 2024.8.7
	virtual long Ats_UpdateCharacteristic(CExBaseList *pParent);//更新特性曲线  zhouhj 2024.8.14
	virtual long Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd=NULL, const CString &strDvmFile=_T(""), const CString strTestClass=_T(""), long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1, long nSynMode=STT_CMD_Send_Sync);
	virtual long Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID);
	virtual long Ats_SetItemPara_RsltExpr(const CString &strItemPath, const CString& strRlstExpr);
	virtual long Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString &strMacroID, const CString &strItemParas);
	virtual long Ats_UpdateItem(const CString &strItemPath);
	virtual long Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType=_T(""));
	virtual long Ats_QueryItem(const CString &strItemPath);
	virtual long Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas);//2023.7.7 zhouhj 增加用于辅助直流设置

	//2022-3-29  lijunqing
	virtual long Ats_NewItems(CExBaseList *pParent, CExBaseObject *pItems);
	virtual long Ats_EditItems(CExBaseList *pParent, CExBaseObject *pItems, const CString &strItemsID);
	virtual long Ats_DeleteItems(CExBaseList *pParent, CExBaseObject *pItems);
	//2022-10-20  shaolei
	virtual long Ats_MoveUpItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	virtual long Ats_MoveDownItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	//2023-2-1  shaolei
	virtual long Ats_ItemPaste(CExBaseList *pParent, const CString& strSrcItemPath);
	//2023-8-11 shaolei //添加测试前、后通讯组合
	virtual long Ats_CmdAddGrp(CExBaseList *pParent, long nAftUseReset = 1, long nAddCommCmd = 1);
	//2023-8-14 shaolei  //导入模型文件(模型映射)
	virtual long Ats_ImportDvmFile(const CString &strDvmFile, long nIsDvmMap = 0);
	virtual long Ats_ImportDvmFile(CDvmDevice *pDvmDevice, long nIsDvmMap = 0);//从当前测试数据模型ID获取文件路径路径,存储文件更新文件
	//2023-8-28 shaolei  //遥测参数映射
	virtual long Ats_AinDataMap(CDataGroup *pMapParas, CDataGroup *pAinDevRatios);
	//2023-8-29 shaolei  //配置装置
	virtual long Ats_ConfigDevice(CDataGroup *pCommCfg);

	//2024.6.28 zhouhj添加单个电气量测试项目
	virtual long Ats_AddOneMacroItem(CDataGroup *pMacroParas,const CString &strItemName,const CString &strItemID,const CString &strItemsPath,
		long nAddPos, const CString &strMacroID, const CString &strTestMacroUI_ID);
	//更新单个测试功能参数
//	virtual long Ats_UpdateOneMacroItem(CDataGroup *pMacroParas,long nSelect,const CString &strItemsPath,const CString &strMacroID);
	virtual long Ats_UpdateOneMacroItem(CSttMacroTest *pSttMacroTest);
	//删除单个测试项
	virtual long Ats_DeleteOneItem(const CString &strItemID,const CString &strParentItemsPath);

	//2022-08-31 shaolei
	virtual long Ats_GenrateItems_CmdWzd(CExBaseList *pParent, CDataGroup *pCommCmd, const CString &strMacroName, const CString &strTestClass, long nSynMode = 0);
	virtual long Ats_GenrateItems_CmdAdd(const CString &strParentItemPath, CDataGroup *pCommCmd, CSttContents *pContents);
	virtual long Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs);

	//模板、报告数据等相关的接口  2022-3-14  lijunqing
	virtual CString SaveTestFile(const CString &strRealPath, const CString &strTemplateFileName);
	virtual CString SaveSysTemplateFile(const CString &strTemplateFileName);
	virtual CString SaveTemplateFile(const CString &strTemplateFileName);
	virtual BOOL SaveTemplate(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = 0);  //0表示同步：STT_CMD_Send_Sync
	virtual BOOL SaveTest(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = 0);
	virtual BOOL ExportWordRpt(const CString &strPath, const CString &strFileName, CDataGroup *pParas);   //pParas为保留的需要传递的其它参数
	virtual BOOL OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL OpenTest(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL ClearReportsRslts(CDataGroup *pParas);  //清除报告数据，形参是预留的参数，可以不传递参数

	virtual void CloseTest(){	};//关闭测试前要干的活 sf 20220318

	//2022-4-14 lijunqing
	virtual void Ats_IecDetect(long bEnable);
	virtual void Ats_IecRecord(CDataGroup *pIecRecordParas);
	virtual void Ats_BinRecord(CDataGroup *pBinRecordParas);//20240814zhouyangyong 新增接口用于开关量录波
	virtual void Ats_BinConfig(CDataGroup *pBinConfigParas);//20240904 zhouyangyong 新增用于开入量配置

public:
	//2022-3-11 lijunqing
	void OpenMacroTestUI_ParaFile(long nFileIndex);
	void SaveMacroTestUI_ParaFile(const CString &strTitleAdd);

	void SaveCurrTestMacroUITemplateFile();
	CSttMacroTestUI_TestMacroUI* GetCurrTestMacroUI()	{	return 	m_pCurrTestMacroUI;	}
	void SetCurrTestMacroUI(CSttMacroTestUI_TestMacroUI *pSttMacroTestUI_TestMacroUI){m_pCurrTestMacroUI = pSttMacroTestUI_TestMacroUI;}

	virtual long GetGbItemCount();   //返回模板中可测的项目的数量
	virtual BOOL IsHasTestTask();   //是否已有测试任务，以是否创建测试（创建CSttDevice）为判断依据
	virtual void WaitCmdReplyProcess()	{	}
};

#endif // CSTTTESTCTRLCNTRBASE_H
