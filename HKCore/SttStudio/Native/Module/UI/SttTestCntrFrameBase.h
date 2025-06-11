#ifndef QSTTTESTCNTRFRAMEBASE_H
#define QSTTTESTCNTRFRAMEBASE_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

//#include "Webkit/SttMacroParaEditViewHtml.h"
//#include "Webkit/SttReportViewHtml.h"
#include "Interface/SttMacroParaEditViewMngr.h"

#include "Config/Frame/SttFrameConfig.h"
#include "Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "Controls/SttGuideBookTreeCtrl.h"
#include "Controls/SttPanelBase.h"
#include "Controls/SttMenuWidget.h"
#include "Controls/SttAddMacroWidget.h"
#include "Controls/SttGuideBookTreeWidget.h"
#include "Controls/SttOutPutWidget.h"
#include "Controls/SttLanguageCfgDialog.h"
#include "Controls/SttReportHeadSetDlg.h"

#include "Module/StateMonitor/QStateMonitorWidgetImp.h"
#include "Module/infoWidget/infowidget.h"
#include "Module/VectorWidget/vectorwidget.h"
#include "Module/PowerWidget/QPowerDiagramWidgetImp.h"
#include "Module/LuminousPower/LuminousPowerDlg.h"
#include "Module/FAParasSetWidget/QSttFAParasSetDialog.h"

//#include "Module/CharLibWidget/CharLibWidget.h"

//2022-12-02 �޸Ĺ���ID���������еĶ�Ҫ���룬Ч�ʵ��£����Դ�ͷ�ļ���ȥ�������κ���Ҫ�����ĵط����а���
//#include "SttTestCntrCmdDefine.h" 
#include "../SttTestCtrl/SttTestCtrlCntrBase.h"
#include "../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../RecordTest/UI/SttIecRecordMainWidget.h"
//#include "Module/CharLibWidget/CharLibWidget.h"   //2022-9-3  lijunqing  
#include "Module/CharLibWidget/CharEditMainWidget.h"
#include "../LiveUpdate/UpdateConfig/VerUpdateCfgMngr.h"
#include "../SttSocket/TestTerminal/SttClientSocketBase.h"
#include "../../../Module/MemBuffer/TxRingPtrBuffer.h"
#include "../SttSocket/Multicast/SttMulticastClientSocket.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../AutoTest/Module/Characteristic/QT/SttCharacterDrawPng.h"
#include "Module/ChRsMap/QChMapsDlg.h"
#include "IEC61850Config/SttIecConfigDialog.h"
#include "Module/DCOutput/QAuxDCOutputDlg.h"
#include "../../../Module/TestMacro/TestMacros.h"

#include "../SttCmd/GuideBook/SttContents.h"

//2022-12-02  lijunqing  
#include "../Assist/SttAssistGlobalApi.h"
#include "Module/CharLibWidget/QCharactWidgetForTest.h"
#include "Module/CharLibWidget/QCharTestPointsGrid.h"
#include "Controls/SafetyMsgCfg/SttSafetyMsgCfgs.h"
#include "RemoteCtrl/SttMacroParaEditViewRemoteCtrl.h"
#include "../SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"
#include "Module/CommConfigurationDlg/PkgMonitor/QSttCommCfgPkgMonitorWidget.h"
#include "../UI/Interface/SttHtmlViewApi.h"



class QSttTestCntrFrameBase : public QMainWindow, public CLogBase, CSttTestCtrlCntrMsgInterface,
	public CSttWndAssistInterface  //2022-12-02 lijunqing ����������صĽӿ�
{
    Q_OBJECT

public:
    explicit QSttTestCntrFrameBase(QWidget *parent);
    virtual ~QSttTestCntrFrameBase();

//CSttWndAssistInterface
public:
	//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
	//�������������ش˺�������Ϊ���ֱ�ӷ��ش���ָ�룬Ȼ��ǿ��ת��ΪCSttWndAssistInterface�������
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

public:
	//2022-3-23  ��ȡ�Ĺ�����ܺ�������Win��LINUX����ʵ��
	virtual void InitFrame(const CString &strFrameCfgFile);

	virtual void InitUI(); 
	virtual void InitIcon();
	virtual void InitIcon(const CString& strItemID, const QIcon& icon);
	virtual void InitIcon(const CString& strItemID, const CString& strIcon);
	virtual void InitPinyinLib();
	virtual void CalRectArea();
	virtual BOOL GetDatas();
	virtual void PromptToSave(CExBaseObject *pSelObj, BOOL bIsItemSame = FALSE);
	virtual BOOL IsUiParasChanged(BOOL &bChanged, CDataGroup *pParas);

	//2022-10-16  lijunqing ��¼�ͱ��浱ǰҳ�����õ�ֵ������ΪĬ��ֵ
	virtual void SaveUIParaFile(CDataGroup *pParas);
public:
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);
	virtual long OnUpdateException();//20220914 zhouhj �����쳣��Ϣ
	virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestFinished();
	virtual long OnTestStarted();
	virtual long OnTestStoped();
	virtual long OnTestCreated();
	virtual void OnReport(CExBaseObject *pItem) ;
	virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup);
	virtual void OnReport_ReadSystemState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnAtsGenerate();
	virtual void OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent=FALSE);
	virtual void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	virtual void OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList);
	virtual void OnAtsQueryItem(CExBaseObject *pItemPara);  //2022-9-13  lijunqing
	virtual void OnInputData(CSttParas *pParas,CExBaseList *pMsgs);  //SHAOLEI  2023-7-21
	virtual void OnTestDisconnected(); //shaolei 2023-9-19 ����

	virtual void FillReport(CExBaseObject *pItem);
	virtual void FillReport();
	virtual void FillReport_OnlyHtmlRpt(CExBaseObject *pItem);//ֻ����html��������,������ԭʼ����Ľ����ʾ,������ӡ���Խ��
	virtual void FillReport_HtmlRptDataByGuideBook(CExBaseList *pItems);
	virtual void FillReport_HtmlRptData();

	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void AdjustMacroEditWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI);

	virtual BOOL CanAddTestMacroUI();
	virtual void closeEvent(QCloseEvent *event);

public:
    void InitConfig(const CString &strFrameCfgFile);//��ʼ������
    void ReleaseConfig();
	void GetCharacteristicsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CString &strFile);
	void InitCharacteristics(CSttContents *pContents);  //2022-9-4  lijunqing

	//zhouhj ���α�ʶ�Ƿ�Ϊ�������л���ֹͣ,�������л�ʱ,����Ҫֹͣʸ��ͼ�͹���ͼ
	void OnViewTestStop_Common(BOOL bItemChanged = FALSE);//zhouhj 2023.8.31 �жϹ�����ͼ����

	//�����󶨲��Կ�������
	void SetTestCtrlCntrBase(CSttTestCtrlCntrBase *pTestCtrlCntrBase);
	CSttTestCtrlCntrBase* GetTestCtrlCntrBase(){return m_pTestCtrlCntrBase;  }   //��ȡ��ǰ��ܹ����󶨵Ĳ��Կ�������
	CSttTestMacroUiParas* GetTestMacroUiParas(CSttItems *pRootNodeItems ,BOOL bSetMacroTest = TRUE);

	//�����ܵĲ��֣�ÿ��ִֻ��һ������
	virtual void AddMacroTestReport();
	virtual void AddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID);
    virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes=1, long nRptTitle=0, long nTitleLevel=1);
	//zhouhj 2024.3.9 �ڶ���˹Linuxϵͳ�µ��������������δ֪ԭ�����,��Ϊ�˺���,ȥ�����һ������
	virtual void OpenMacroTestUI_Test(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes=1, long nRptTitle=0);
	virtual void OpenMacroTestUI_OnlyCreate(CSttMacroTestUI_TestMacroUI *pTestMacroUI);

	//�๦�ܲ���ģ��༭ģʽ
	virtual void AddMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID, CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void OpenMacroTestUI(CSttTestMacroUiParas *pUIParas, CSttMacroTestUI_TestMacroUI *pTestMacroUI,CSttTestMacroCharParas *pSttTestMacroCharParas);
	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI, BOOL bUseExist);
	virtual void DeleteMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID);
	//20230324 zhouhj ����2Ϊ����ID���ݸ�ID���Ҷ�Ӧ����ҳ�ļ�,����3λ���ڵ����
	virtual void UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath);
	virtual void SetMacroTest_Original(CExBaseObject *pMacroTest);
	virtual void SelectTestMacro_CmdWzd(const CString &strTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd, const CString &strTestClass, const CString &strDvmFile, long nRepeatTimes, long nRptTitle, long nTitleLevel);

	//2023-03-21 zhouhj �����л����Թ��ܽӿں���,���ڴ�����������ģ���л�ʱ,��ȡģ���е�������������,����ֱ�Ӷ������ļ�
	virtual BOOL SwitchMacroViewByCurrSel(CSttItems *pCurrSelRootNode);

	virtual void OnDeleteCurr(CExBaseObject *pCurrObj);
	virtual void OnSaveCurr(CExBaseObject *pCurrObj);

	//2022-9-11  lijunqing
	virtual void ViewCmdEditWidget(CExBaseObject *pSelObj);
	virtual void ViewMacroEditWidget(CExBaseObject *pSelObj);//2022-9-13  lijunqing
	virtual void SaveMacroParasToCurrWzd(CDataGroup *pCommCmd);  //2022-9-12 lijunqing

	virtual BOOL OpenSclFile();
	virtual CString SelIedFromScl();
	//�����Դ����
//	CSttTestResourceBase *m_pSttTestResource;//zhouhj 20220319 ����CSttTestCtrlCntrBase����

	CSttTestResourceBase* GetSttTestResource();
	CSttMacroParaEditInterface* GetCurrMacroParaEditInterface();

	void InitTestResource();
	void OnUpdateTestResource(BOOL bCreateChMaps);
//	void initLocalSysPara();

	void InsertReportHead(CDataGroup *pSttReport);//20240508 suyang �������뱨��ͷ 
	void UpdateReportHead(CDataGroup *pSttReport);
	void UpdateCustomReport();//20220924 �����Զ���ı���,���ϲ���Ԫ�Ȳ�����Ŀ�ı���
	void UpdateCharactWidgetForTest(long nPtIndex = 0);//���ڸ��²��Թ�������ʾ������ͼ,�ڿ�ʼ����ǰ�����´�ͼ,��ֹ��ֹͣ���Ժ�,��ǰ����ͼ�����ѱ��޸�
	void UpdateCharactWidgetForCurTest(long nPtIndex);
	virtual void UpdateRptHtml();
	virtual void GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath);
	void UpdateResultWidget(CSttReport *pReport,const CString &strItemName,const CString &strMacroID);//���½����ʾ����
	CString GetMacroTestResultUnit();//dingxy 20241127 ��䶯��ֵ��λ
	void OpenDialog(const CString &strDialogID);//����������ĶԻ���ID��������������ĶԻ������
	void OpenDialogModal(const CString &strDialogID, bool bNeedConnect);
	void OpenDialogModeless(const CString &strDialogID, bool bNeedConnect);

	BOOL HasManuTrigerBtn();//zhouhj 20220403 �жϵ�ǰ���Թ����Ƿ�����ֶ�����
	BOOL IsManuTriger_HtmlFaultTrigMode();//zhouhj 20220404 ���ݵ�ǰ�·�����,�ж��Ƿ�Ϊ�ֶ�����ģʽ
	CDataGroup* GetTestMacroUI_Paras(){return m_pTestMacroUI_Paras;}

	BOOL SetValues_dsRcdStep6U6I(BOOL bClearResult);//20220811 zhouhj ����ǰ�������е�6U6I��ֵ��ֵ�����ݼ������ڱȲ�ǲ����
	BOOL SetValues_dsRcdStep6U6I(CDataGroup *pDataGroup,BOOL bClearResult);//2024-5-17 wuxinyi ��Ư��ҳ������ˢ��6U6I��ֵ
	BOOL IsMenuBtn(QWidget *pWidget);
	virtual BOOL IsMenuWidget(QWidget *pWidget);
	virtual void InitSttIecRecord();//��ʼ��¼��
	//2023.6.6 zhouhj 
	virtual void InitAfterCreateSttMacroPara();//�򿪽��������,��ʼ�����ָ��Ի���������(��ϲ���Ԫ���ݴ����)
	//zhouhj 20230606 ��Ϊʹ��InitAfterCreateSttMacroPara����
//	virtual void InitSttCap_MUTerminal();//�ϲ���Ԫ�����ն˲���ʱ,��ʼ��IEC̽�⹦��
	virtual void InitAllButtonStateByTestMacroUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);//���ݲ��Թ��ܳ�ʼ���������Ȱ�ť  zhouhj 20221228
	
	//2024.1.4 zhouhj 
	virtual BOOL CreateEngineClientWidget();
	virtual BOOL CreateCommCfgPkgMnWidget(); //chenling 20240301 �������ļ�������
	virtual void UpDateUdcVal(){};//20240626 suyang �������� ���豸�и���ֱ��ֵ��ϵͳ�����и���ֱ��ͳһ
	virtual BOOL CreateRemoteCtrlWidget();//2024.8.15 chenling ����ң�صĽ���
	virtual void UpdatePrimParaSetUI(bool IsStateMonitor,bool IsVector,bool IsPowerDiagram,bool IsUseSecondParaSet){}//20240918 suyang ���Ӻ������ڸ��½���һ��/����ֵ��ʾ

public://����
	CSttFrame_Button *m_pStartTestBtn;
	CSttFrame_Button *m_pManualTriggerBtn;
	CSttFrame_Button *m_pExitBtn;
	CSttFrame_Button *m_pMenu_FrameButton;//�˵���ť
	CSttFrame_Button *GetStartTestBtn();
	CSttFrame_Button *GetManualTriggerBtn();
	CSttFrame_Button *GetExitBtn();
	QWidget* GetCharEditMainWidget(){return m_pCharLibWidget;}

	virtual void UpdateStartStopTestButton(const CString &strState);
	virtual void UpdateCmdButtonsState(const CString &strState);
	//�ڶ������������ܷ��������������������Ƿ���ʾ
	virtual void UpdateButtonStateByID(const CString &strID,bool bState,bool bShow = true);
	virtual void UpdateEnableState(const CString &strState);
	virtual void SetAddMacroEnable(bool bShow);   //2023-2-26  lijunqing  SetSelectEnable�������ǳ������������޸�
	virtual void EndBinStateOnStarting();
	virtual CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
	bool m_bInited;

	virtual void OnCmd_CustomSet(); //�Զ������ý���
	virtual void ShowCharLib()	{}
	virtual void HideCharLib()	{}

public://������ر���
    QWidget *m_MainWidget;
	QRect m_rcGbItemsArea; //����ģ����Ŀ����
	QRect m_rcWorkArea; //��������
	QRect m_rcPaneArea; //ͣ��������

    CSttFrameConfig *m_pSttFrameConfig;//������ò����������
    QFont m_gFont;

	CCharacteristics *m_pCharacteristics;
	CSttCharacterDrawPng* m_pSttCharacterDrawPng;

    QSttBarBase *m_pStatusBar;//״̬��
	QSttBarBase *m_pResultBarUI;//���Խ����ʾ��
	QSttResultPanel *m_pResultWidget;//���Խ����ʾ����
    QSttGuideBookTreeWidget *m_pSttGbTreeView;//��ߵ����ṹ
    QSttOutPutWidget *m_pOutputWidget;
	CSttResults m_oTestMacroResults;//���в��Թ��ܵĽ��ID,���ڽ������ʾ�ڽ����ʾ����
	CDataGroup  m_oBinaryInParas;//��¼ȫ��ģ�鿪��ѡ��Ĳ�����ӦID
    QSttBarDataBtnsMngr m_oDataBtnsMngr;//Data���͵İ�ť���������������ָʾ�ơ�״̬�ơ�������
	CSttSafetyMsgCfgs m_oSafetyMsgCfgs;  //����Ĭ�ϵĽ�����ʾ��Ϣ

	//zhouhj 2024.1.4 ������������
	QPpSttIotEngineClientWidget *m_pEngineClientWidget;

	QTimer m_oTimerAtsAutoSave;
	CAutoCriticSection m_oCriticSection_AutoSave;

	QTimer m_oTimerAtsTest;
	QTimer m_oTimerHtmlViewReturn;
	CAutoCriticSection m_oCriticSection_ItemStateList;//20230220 zhouhj ������Ŀ�б������º�ģ�����ɸ���
	//BOOL m_bAutoUpdateNameByTestCount;   //���ݲ��Դ������Զ�������Ŀ����

	//���е������������
	CDataGroup m_oErrorValueWzdGroup;

	//zhouhj 2024.5.20
	CDataGroup m_oOldSysParasList;//��ϵͳ����ǰ,��¼ԭ��ϵͳ�������ݵ�����

	QSttCommCfgPkgMonitorWidget *m_pSttCommCfgPkgWidget;
// 	bool m_bFirstUpadeIPowerMode;//20240516 suyang  ��һ�ν������ʱ���� ������λΪ1�� 
	enum tagAppState
	{
		APPSTATE_NULL,
		APPSTATE_OPENTEMPLATE
	};//������������ܳ��ֵĸ���BOOL��
	tagAppState m_tagAppState;

	virtual void AdjustToolBarButtons();
	virtual void AdjustStatusBarButtons();
	virtual void UpdateButtonsStateByID(const CString &strButtonID, BOOL bEnable);
	virtual void Before_OnCmd();
	virtual void UpdateStartStopButtonByItemCount();
	virtual void UpdateToolButtons_FloatPanel();//���¸��㴰��
	CSttMacroParaEditInterface* GetMacroEditView();
	QCharTestPointsGrid* GetCharTestPointsGrid();
	void ClearItemStateList();

protected:
	BOOL MUTestValid();
	//bool m_bSelMacroShow;

	long m_nSelMacroShow;
	//zhouhj 2023.8.22 ��¼OnItemStateChanged�ı�ʱ,����SeachReport��Ӧ��ItemID�͵�ǰ���Ե�ֵ�����������һ����ͬ,���������,��ֹ�ظ�
	CString m_strItemStateChanged_SearchLineString;

	//zhouhj 2023.11.7 ����Ƿ���²��Ա����ﵱǰ������Ŀ�ʼ����ʱ��
	//�ڴ�ģ��ʹ򿪲��Թ��ܡ��򿪲��Լ�¼ʱ�������Ϊδ����
	BOOL m_bHasUpdateRptStartTestTime;

	BOOL m_bIsRunningStartStopCmd;//zhouhj 2024.4.1 �������ڱ�ǵ�ǰ�Ƿ�����ִ�п�ʼ,ֹͣ����,�������ִ��,����Ե�ǰ����
	BOOL m_bIsUpdateStateTestFirstReportColor;//dingxy 20240705 �������ڱ���Ƿ񽫵�һ��������ı���״̬��Ϊ��ʼ��״̬
	BOOL m_bIsRtDataUpdateChMaps_System;//20241121 suyang ������RtData�����˵�����λ�Ȳ������Ƿ����ͨ��ӳ���Լ�ϵͳ������

protected:
	CSttTestCtrlCntrBase *m_pTestCtrlCntrBase;     //��ǰ��ܹ����󶨵Ĳ��Կ�������
	//���Թ��ܲ����༭
	CDataGroup *m_pTestMacroUI_Paras;  //��ǰ���Թ���ҳ��Ĳ���
	CExBaseObject *m_pCurrEditMacroItems;   //��ǰ���Թ��ܶ�Ӧ�Ĳ�����Ŀ�����ǲ�����Ŀ����
    CSttMacroParaEditInterface* m_pMacroEditView;		//���Թ��ܲ����༭
    //QSttMacroParaEditViewHtml* m_pSysParaEditView;  //�����༭��ͼ  2022-3-18  lijunqing
	//CExBaseObject* m_pItemState;//��ʱ��Ŷ��̴߳��ݵ�ItemState�����滻Ϊѭ������
	CTxRingPtrBuffer<CExBaseObject> m_oItemStateList;

	//�Ƹ���
	CVerUpdateCfgMngr m_oVerUpdateCfgMngr;
	CSttClientSocketBase m_oVerUpdateSocket;
	CSttMulticastClientSocket* m_pSttMulticastClientSocket;

	//���Ա�����ͼ
    //QSttReportViewHtml *m_pSttReportViewHtml;

	//ʸ��ͼ
	QVectorWidget *m_pVectorWidget;

	//״̬ͼ
	QStateMonitorWidgetImp* m_pStateMonitorWidget;

	//����ͼ
	QPowerDiagramWidgetImp* m_pPowerDiagramWidget;

	//��Ϣͼ
	QInfoWidget* m_pInfoWidget;
	
	////FA��������
    QSttFAParasSetDialog *m_pSttFaParasSetDialog;



	//��������ͼ
	//2022-9-3  lijunqing
	QCharEditMainWidget* m_pCharLibWidget;	//QCharLibWidget* m_pCharLibWidget;
	QCharactWidgetForTest *m_pCharactWidgetForTest;//20230310 ���ڲ��Թ�������ʾ��������ͼ zhouhj
	QCharTestPointsGrid *m_pCharTestPointsGrid;//20230316 ���ڲ��Թ�������ʾ���������е�ȫ�����Ե� zhouhj

	//QCharEditMainWidgetForTest* m_pCharLibWidgetForTest;


	//IEC����
	QSttIecRecordMainWidget *m_pSttIecRecordMainWidget;
	BOOL m_bHasClosedUI;//20221009 zhouhj ����رհ�ťʱ���ӱ��,��ʱ�յ�����ֹͣ��Ϣ,���ٸ��½���

	QSttMacroParaEditViewRemoteCtrl *m_pRemoteCtrlWidget; //ң�� zhangyq 2023.12.25
private:
	QIcon m_imgStart;
	QIcon m_imgStop;
	QIcon m_imgTriger;

public:
	//��ǰ��Ĵ���
	QWidget *m_pActiveWidget; 
	QWidget *m_pPrevActiveWidget; 

	typedef enum _stt_active_widget_type
	{
		ActiveWidgetType_None=0,  //��
		ActiveWidgetType_MacroUI,  //ԭ��̬��������  ���� ���Թ���HTML��������
		ActiveWidgetType_MacroUI_Original,  //ԭ��̬��������
		ActiveWidgetType_MacroUI_Html,  //���Թ���HTML��������
		ActiveWidgetType_Paras_Html,  //������������HTML����
		ActiveWidgetType_Other  //��������
	}ActiveWidgetType;
	ActiveWidgetType m_nActiveWidgetType;  //��ǰ����ڵ�����
	ActiveWidgetType m_nPrevActiveWidgetType;  //��һ����ڵ�����

public:
	QWidget* GetMacroEditWidget();
	CString GetMacroEditViewID();
	BOOL IsHtmlParasEditOpen();
	void SetActiveWidget(QWidget *pWidget, ActiveWidgetType nType=ActiveWidgetType_Other);
	void ReturnPrevActiveWidget();
	CString GetCharLibWidgetID();
    
	void InitPowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);
    void InitFAParasSetDialog(QWidget* pParent = NULL);
	void UpdatePowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList);
	void UpdatePowerData();
	void StartPowerWidget();
	void StopPowerWidget(bool bUpdate = false);
	void InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);
	void UpdateVectorRange(float fUStart, float fUEnd, float fIStart, float fIEnd);
	void UpdateVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList);
	void UpdateVectorData();
	void StartVectorWidget();
	void SetVectorGradient(bool bIsGradient);
	void StopVectorWidget(bool bUpdate = false);
	void SetPlotAcDcMaxMinValue( bool bDC,double fUMin,double fUMax,double fIMin,double fIMax );//20241030 suyang ����״̬ͼ��ѹ������С

	void InitInfoWidget(QWidget* pParent = NULL);
	void ClearInfoWidget();
	void InitIecRecordMain();
	void InitToolBtnFocusPos(const CString &strBtnID);//20230302 zhouhj ��ʼ����������ť����λ��
	CXDrawLine* GetCharLibLeftButtonLine();

	virtual void InitCharLibWidget(QWidget* pParent = NULL);
	virtual void InitCommCmdWzdMain(CExBaseList *pParentItem);
	virtual void FreeCommCmdWzdMain();

	void OnEventMsg();
	void UpdateEventMsg(CEventResult *pEventInfo);
	void PrintEventInfo();
	void UpdateToolButtons();
	tmt_BinaryConfig* GetBinaryConfig();
	void UpdateToolButtons_ParaEdit();
	void UpdateToolButtons_Bin();
	void UpdateToolButtons_Bout();
	void UpdateToolButtons_Light();
	void SyncBinOutDatas(BOOL b=TRUE);
	void InitBinaryIn_WebUI(CDataGroup *pParas);//zhouhj ��ҳ���� �Կ���ѡ����г�ʼ��

	void TemplateView_Prepare();//��ģ����ͼʱ,��ǰ׼��,�磺�ͬ���������߽������
	void CharDrawView_Prepare();//������������ͼʱ,��ǰ׼��,�磺�ͬ��ģ����ͼ�������
	void OnCmd_IecCap_Prepare();//�򿪱���̽�����ǰ,��Ҫ���еĴ���,��Ҫ����ϲ���Ԫ���Ե�ǰ�趨ֵ���ݵ�ͬ��
	//zhouhj 2023.10.16 ͨ����ǰ������Ĳ���,���¹�������
	void InitCommonParasByDatas(CDataGroup *pDataGroup_Paras);

	bool IsTestStarted();
	bool IsStateTest();
	bool IsUseStateIndex();
	bool IsMultiTestItems();//�жϵ�ǰ�������Ƿ�Ϊ�������
	bool HasCharChanged();//�ж����������Ƿ�ı�
	void AddTestPoints(double dX, double dY,BOOL bAct);
	void SetCharChanged(bool bCharChanged);
	void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);//���ݽ�������������������еĽű���������  20221022 zhouhj
	virtual bool GenerateTemplate(CExBaseObject *pParentItems, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1);  //2022-3-27  lijunqing �޸�Ϊ�麯����Win�汾��LINUX�汾����ģʽ��һ��

	virtual void InitStateMonitor(bool bIsEx = false, QWidget* pParent = NULL);
	virtual void InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget = NULL);
	virtual bool PrepStartTest();//zhouhj 20221027 ��ʼ����ǰ��׼������
	void StartStateMonitor();
	void StopStateMonitor();
	void CloseMenu();

	void SysStateReport_OnSwitchChanged(CEventResult *pEventInfo);
	void SysStateReport_OnStateChanged(CEventResult *pEventInfo);

	bool IsTestAppConnect();
	virtual void Ats_UpdateParameter();
	virtual void OpenMenuHtmlFile(const CString &strMemuFileName);//����ҳ�˵�

	virtual void Cmd_SendChMapsConfig();//zhouhj 20220316 �������ڷ���ͨ��ӳ���ļ�����
	virtual void Cmd_SendSystemConfig();//zhouhj 20220316 �������ڷ���ϵͳ������������

	void UpdateSysConfig();//zhouhj 20220409 ϵͳ�����޸ĺ�,���ʹ��ź�,���½�����ʾ,������ز���,�����������MainCore
	void UpdatePowerGear();//zhouhj 20220409 ���ʵ�λ�޸ĺ�,���ʹ��ź�,������ز���,�����������MainCore
	virtual void New_SysConfig();
	void EnableStartStopButton(BOOL bEanble);
	void EnableManualTriggerButton(BOOL bEanble);
	BOOL OpenTemplate(CString strFilePath, const CString &strDvmFile);
	BOOL OpenDscXmlFile(CString strFilePath);
	BOOL AfterOpenDscXmlFile(CString strFilePath); //��dscxml�󣬳�ʼ��ҳ��
	BOOL OpenTest(CString strFilePath, const CString &strDvmFile);
	BOOL FillRptTitle(CExBaseObject *pCurrSelGbItem);//2023.7.25 �޸ı����е�ǰitems�ı���

	void SaveMacroTestUI_ParaFile(const CString &strNameAdd);
	CEventResult* GetCurEventResult();

    //QSttReportViewHtml* GetReportViewHtml(){ return m_pSttReportViewHtml; }
public:
    virtual void LogString(long nLevel, const CString &strMsg);
    virtual void LogString(long nLevel, const char *strMsg);

	virtual void LogStringResult(long nLevel, const CString &strMsg);//zhouhj 20220417 ��ӡ���Խ��
	void ClearAll_ResultUI();
	void CloseIecCapDetect();//20220629 zhouhj �رղ��Թ��ܽ���ʱ,����ײ㻹����̽��ģʽ,�ر�̽��ͨ��
	void SendMenuButtonClick(QString strFuncID);

	CString FindNameFromTestMacros(CTestMacros* pTestMacros, CString strMacroID, CString strID);
	void SetErrorValueFromWzd(CDataGroup* pDataGroup);

	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);//20231109 suyang add 

	virtual void InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns = true);//2023-12-25  zhangyq
	void InitRemoteCtrl();
	virtual void UpdateDeviceModelRef();//�����豸����ģ�͹�����Ϣ zhouhj 2024.3.18
	virtual void keyPressEvent(QKeyEvent *event);
	bool keyPressEvent_Exec(int nKeyValue);      //20240510 xueyangfan  ��ʼ���� �ֶ����� ֹͣ���԰�����Ӧ 
	virtual BOOL IsAutoTest(){return FALSE;}

public:
	virtual void OnCmd_Menu();
	virtual void OnCmd_StartTest();
	virtual void OnCmd_TestThis();
	void OnCmd_ManuTriger();
	virtual void OnCmd_StopTest();
	virtual void OnCmd_AddMacro(BOOL bUseNameID);
	void OnCmd_ItemList();
	virtual void OnCmd_TemplateView();
	virtual void OnCmd_ReportView();
	void OnCmd_HardConfig();
	virtual void OnCmd_IECConfig();
	virtual void OnCmd_VectorDrawView();
	virtual void OnCmd_WaveDrawView();
	virtual void OnCmd_StateDrawView();
	virtual void OnCmd_PowerDrawView();
	virtual void OnCmd_CharDrawView();

	virtual void OnCmd_NewTest();
	virtual void OnCmd_OpenTemplate();
	virtual void OnCmd_SaveTemplate();
	virtual void OnCmd_SaveAsTemplate();
	virtual void OnCmd_SaveTest();
	virtual void OnCmd_SaveAsTest();
	virtual void OnCmd_SaveAsRpt();//20230607 zhouhj �����洢����
	virtual void OnCmd_ExportWordRpt();  //20230625 shaolei ����word��XML����
	virtual void OnCmd_OpenTest();
	virtual void OnCmd_SelSCLFile();
	virtual void OnCmd_SaveEdit();
	virtual void OnCmd_PpIotEngineClient();

	//2023.11.15 lichao PNS331 ����
	virtual void OnCmd_PpIotEngineClientDlg(); //װ��ͨѶ�Ի���
	virtual void OnCmd_CommConfiguration();        //ͨѶ����
	virtual void OnCmd_PkgMonitor();               //���ļ���
	virtual void OnCmd_PpXmlFileMngr();		       //��Լģ�����
	virtual void OnCmd_DvmFileMngr();              //����ļ�����
	virtual void OnCmd_RemoteCtrl(); //ң�� zhangyq 2023.12.25
	virtual void OnCmd_PkgMonitorDlg(); //���ļ����Ի���chenling20240301


	virtual void OnCmd_NetworkConfig();
	virtual void OnCmd_ClearReportRslts();
	virtual void OnCmd_ImportDvmFile();

	//2023/8/31 wjs ң�����鰴ť
	virtual void OnCmd_AinDataMapConfig();
	virtual void OnCmd_SystemParas();
	void OnCmd_GeneralParas();
	//void OnCmd_SwitchSet();
	virtual void OnCmd_DcSet();
	void OnCmd_OutputPower();
	void OnCmd_DeviceCom();
	void OnCmd_LangSettingView();
	void OnCmd_ReportSetting();
	void OnCmd_ChRsMaps();
	void OnCmd_AuxDCOutput();
	void OnCmd_IecCapDialog();
	virtual void OnCmd_TransPcapFile();

	void OnCmd_ItemListView();
	void OnCmd_DeviceComView();
//	virtual void OnCmd_CharaView();
	void OnCmd_SequenceView();
	virtual void OnCmd_InfoView();
	void OnCmd_LogView();
	void OnCmd_VersionInfo();
	virtual void OnCmd_AuxIPSet();
	virtual void OnCmd_Liveupdate();
	virtual void OnCmd_LiveupdateDevice();
	virtual void OnCmd_ULiveupdate();
	void OnCmd_CloudConfig();
	void OnCmd_UpdateAdjCoef();
	void OnCmd_RegisterRemoteTest();
	void OnCmd_RemoteRegistAssist();
	void OnCmd_DownloadTestTemplate();
	void OnCmd_DownloadPpTemplate();
	void OnCmd_UploadingReport();

	void OnCmd_DebugSetDatas();
	void OnCmd_DebugSetDatasFile(long nFileIndex);
	void OnCmd_DebugSetDatasFile1();
	void OnCmd_DebugSetDatasFile2();
	void OnCmd_DebugSaveDatasFile();
	void OnCmd_DebugGetDatas();
	void OnCmd_DebugUpdateReport();
	void OnCmd_DebugFillReport();
	void OnCmd_DebugItemStateChanged();
	virtual void OnCmd_DebugOutPutWidget();
	void OnCmd_DebugStartTest();
	void OnCmd_DebugStopTest();
	void OnCmd_ConnectApp();
	void OnCmd_Debug();
	void OnCmd_DebugSaveTest();
	void OnCmd_DebugGenForDebug();
	void OnCmd_DebugGenTemplate();
	void OnCmd_DebugSaveAsSysFiles();
	virtual void OnCmd_IecCap(); //2022-4-10  lijunqing
	virtual void OnCmd_IecCapWriteFile(); //2022-6-13  lijunqing
	virtual void OnCmd_IecCapDebugHead(); //2022-6-19  lijunqing
	void OnCmd_ScreenShot();//��������
	void OnCmd_Assist();	//2022-12-02  lijunqing

	void OnCmd_FAParasSetDialog(); //FA��������Dialog  xueyangfan 2024-1-23
	void onCmd_BinBoutCommMap();//2024.9.25 chenling ���뿪��ͨѶӳ��


	virtual void InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns = true);//2022-12-27  lijunqing  //����3Ϊ�Ƿ���ʾ�˵��Ȱ�ť,IEC̽��ʱ,����Ҫ��ʾ

	void OnCmd_FileMngr();

	void OnCmd_LumPowerView();//�⹦��chenling20230410

	virtual void OnCmd_OutputDebug(); //������� lcq 2023 8-24
	void OnCmd_Minimize();// ��С�� zhouyangyong 2024-2-26
	void OnCmd_BinConfig();//�������� zhouyangyong 2024-09-23
	void OnUpdateRtCurrModules(CDataGroup *pRtSycTime);  //20240530 xueyangfan ��ȡʵʱ���ݸ��µ���ģ��ʵʱֵ
	void OnUpdateRtInputDev(CDataGroup *pRtSycTime);	//20240530	xueyangfan ��ȡʵʱ���ݸ���������

	void OnUpdateRtHardConfig( CDataGroup *pRtSycTime );//2024-6-25 wuxinyi ����ϵͳ�����е�Ӳ��������Ϣ
	BOOL m_bUpdateHardCfgFromRealTime;//�Ƿ���Ҫ����ʵʱ���ݸ���Ӳ��������Ϣ
	BOOL m_bUpdateOutputPowerFromRealTime;//�Ƿ���Ҫ����GetSystemState���µ��������
	BOOL m_bOutputTypeHasChanged;//chenling 20250212�ж��������ѡ���Ƿ��б仯
	float m_fUdc;//dingxy 20250321 ��¼��ǰ����ֱ�����ֵ

signals:
	void sig_MenuButtonClick(QString);
	void sig_UpdateEnableState(QString);
	void sig_OnViewTestLink(bool b);
	void sig_OnViewTestStart();
	void sig_OnViewTestStop();
	void sig_UpdateToolButtons();
	void sig_OnUpdateGpsTime(CDataGroup *pRtSyncTime);
	void sig_OnUpdateException();
	void sig_UpdateTestResource();
	void sig_CloseMenu();
	void sig_UpdateRptHtml();
	void sig_FillReportImg(QString);
	void sig_MsgBox(QString,QString);//���߳��﷢���źŽ��е�����ʾ
//	void sig_LogStringResult(long nLevel,CString strMsg);

	void sig_OnItemStateChanged(CExBaseObject *);
	void sig_ShowItems_TreeView(CExBaseList *);//zhouhj 20220326 ������Ŀ�б��Ϊ�����źŷ�ʽ
	void sig_UpdateHtmlManuTrigerBtn_Testing();
	void sig_UpdateSysConfig();//zhouhj 20220409 ϵͳ�����޸ĺ�,���ʹ��ź�,���½�����ʾ,������ز���,�����������MainCore
	void sig_UpdatePowerGear();//zhouhj 20220409 ���ʵ�λ�޸ĺ�,���ʹ��ź�,������ز���,�����������MainCore
//	void sig_OnItemStateChanged_Frame(CExBaseObject *);   //��FrameBase�Ĳ�����Ŀ״̬�ı䣬Ҳ��Ϊ�źŴ���  shaolei 20220411
	void sig_OnInputData(CDataGroup *, CExBaseList *);//������ʾ��Ŀִ�У��β�ΪCSttParas* pParas, CExBaseList* pMsgs;
	void sig_OnImportDvm(CExBaseList *);  //����ģ�ͺ󣬸��������ɵ�ͨѶ��������������ͨѶ����
	void sig_InitImportDvmFile_Widget(CExBaseList *);  //������ͨѶ��������ĶԻ���
	void sig_SendChMapsConfig();//20241223 suyang�����źŷ�ʽ����ͨ��ӳ��
	void sig_UpdateReportSysState(CDataGroup* pSystemState);
	void sig_UpdateModulesGearSwitchInfo();//dingxy 20250320 ����������ʽ�������

// 	void sig_UpdateAuxDCEdit();//suyang 20240603 �ڵ�����������ֱ������½��� ����ֱ���༭��״̬

	//zhouhj 2023.12.27 ȥ��,��Ϊ�����麯���ķ�ʽ
//	void sig_UpdateEventMsgTime(CEventResult *pEventInfo);//������Ϣͼ��ʾ������

public slots:
	virtual void slot_Timer_AutoSave();
	void slot_Timer();
	void slot_OnViewTestLink(bool b);
	virtual void slot_OnViewTestStart();
	virtual void slot_OnViewTestStop();
	void slot_UpdateToolButtons();
//	void slot_LogStringResult(long nLevel,CString strMsg);

    void slot_MenuButtonClick(QString strID);
	virtual void slot_SelectTestMacro(CSttMacroTestUI_TestMacroUIRef *pTestMacroUIRef, const CString &strItemsName, const CString &strItemsID);
	//�̵߳��õ�ʱ��ᱼ�����ĳ��źŲ۵���ʽ sf 20220218
	void on_UpdateEnableState(QString strState);
	void slot_OnUpdateRtSyncTime(CDataGroup *pRtSycTime);
	void slot_OnUpdateException();

	virtual void slot_UpdateAuxDCOutput();//zhangyq 20230228 ���¸���ֱ�����
	virtual void slot_UpdateChRsMaps(BOOL bSysParasHasChanged);
	virtual void slot_ReturnPrevActiveWidget();
	void slot_IecCfgDataMngrUpdate();//zhouhj 20220315 ����IEC����
	void slot_UpdateTestResource();//���½�������������Դ	
	void slot_UpdateHtmlManuTrigerBtn_Testing();//���Թ����и����ֶ�������ť
	void slot_UpdateSysConfig();//zhouhj 20220409 ϵͳ�����޸ĺ�,���ʹ��ź�,���½�����ʾ,������ز���,�����������MainCore
	void slot_UpdatePowerGear();//zhouhj 20220409 ���ʵ�λ�޸ĺ�,���ʹ��ź�,������ز���,�����������MainCore
	virtual void slot_OnItemStateChanged_Frame(CExBaseObject *pItem);
	virtual void slot_OnInputData(CDataGroup *pParas, CExBaseList *pMsgs);
	virtual void slot_OnImportDvm(CExBaseList *pListItems);
	virtual void slot_BinBoutCommMapDataUpdate(CDataGroup *pDataGroup);//chenling 2024.9.27 ���¿��뿪��ͨѶӳ��
	virtual void slot_UpdateFAParasData(CDataGroup *pDataGroup);//FA��������


	//zhouhj 2023.10.16 �������·���,ɾ���˺���
//	virtual void slot_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);//20220825 ����ʱ�侫�Ȳ��Խ��
	virtual void slot_OnFreeCommCmdWzdWidget();
	virtual void slot_CloseMenu();
	virtual void slot_UpdateRptHtml();
	void slot_UpdateModulesGear(BOOL bMergeCurrHasChanged, BOOL bCurrModulePowerHigh);//zhouhj 20211016 ���²����ǵ�λ��Ϣ
	void slot_FillReportImg(QString strItemPath);//zhouhj 2023.8.22
	void slot_MsgBox(QString strTitle,QString strMsg);

	//zhouhj 2023.12.6 ��window��������������
	void slot_OnConfigDevice(CDataGroup *pCommCfg);
	
	void slot_SendChMapsConfig();
	void slot_UpdateReportSysState(CDataGroup* pSystemState);//dingxy 20250320 �������������CurrModules����


public:
	//shaolei 2022-03-19 ������ĿID�����²�����Ŀǰֻ������Iec61850Config��ChMapsConfig��SystemConfig
	void Ats_SetItemPara(const CString &strItemID);
	virtual void Ats_SetItemPara_RsltExpr(CExBaseObject *pItem);
	//zhangmeng 20220728
	void SaveCharacteristicsData(CString strFile = _T(""));
	virtual BOOL IsContinueCreateNew();   //�������Ѵ���ʱ���Ƿ������������
	long GetGbItemCount();
	CString GetCurrentUI_ID();
	virtual void InitTestMacroUI_by_DeviceType(CSttMacroTestUI_TestMacroUIMngr *pTestMacroUIMngr);
	CSclStation* GetSclStation();
	virtual void SetDatas(CDataGroup *pParas);
	virtual void ClearReportRslts_Html();//���HTML���������
	virtual BOOL IsNeedAddAft();//�Ƿ���Ҫ��Ӳ��Ժ�ָ�
	virtual void ItemPaste_RootNode(CSttItems *pDestItems, CExBaseObject *pCurrentSel);  //��Ŀճ���󣬴�����
	virtual void UpdateStatusBar_Btns(const CString &strID, const CString &strValue);  //���µײ�״̬��

//2024-9-10 lijunqing �Ż�ϵͳ����������Ч��
public slots:
	virtual void slot_OpenMacroTest(unsigned long nAddrParser);

signals:
	void sig_OpenMacroTest(unsigned long nAddrParser);

public:
	void emit_OpenMacroTest(unsigned long nAddrParser);
#ifdef _PSX_QT_LINUX_
	virtual void InitMeasServer();
	virtual void ExitMeasServer();
#endif

	void ShowItems_TreeView(CExBaseList *pCurTestItems);//20241016 zhangyq ���͸�����Ŀ�б��ź�
};


extern QSttTestCntrFrameBase *g_theTestCntrFrame;
extern long g_nLogDebugInfor;
extern QFont *g_pSttGlobalFont;  //2022-9-16  lijunqing
extern double g_dUIShowCoef; // ������ʾ���ű���

extern int g_nUpdateMultiMacroParaEditView;//chenling 2024.11.25��ģ�壬����ˢ���ʹ�ģ�����
//void  Stt_Global_SettingSelect(QObject *parent, const CString &sFormat, const CString &sName);	//20240815 huangliang ��Ӳ���
void  Stt_Global_SettingParent(QWidget *parent);	//20240802 huangliang ���ö�ֵ��صĸ���
void Stt_Global_SettingParent(QWidget *parent, QWidget *pDlgParent);	//20240806 huangliang ��������ģ̬�Ի�����ʹ�ýṹ���ַ�༭��ֵ����


void Stt_Global_NoticeUpdateBinBinary();	//20240912 huangliang ����֪ͨ������ˢ����Ϣ
QString Stt_Global_GetBinBoutNameForIndex(int iBin, int iIndex);	//20240913 huangliang ȡ�����뿪��������,iBinΪ0���룬1��չ���룬2������3��չ����
QString Stt_Global_GetBinBoutNameForIndex_NoUseDefault(int iBin, int iIndex);	//20241011 huangliang ��ȡӳ���Ŀ��뿪������
void Stt_Global_GetBinBoutMaxWidth();	//20241012 huangliang ��ȡ���뿪��ӳ���������

int Stt_Global_GetdesktopWidgetSizeLevel();	//20241107 huangliang ��ȡ�ֱ��ʵȼ�

extern CDataGroup *g_pGlobalDatas;
BOOL Stt_CalParaExpression(const CString &strExpress, double &dValue, BOOL bLogError, CValues *pValues=NULL);
BOOL Stt_CalParaExp_FindValue(CValues *pValues, const CString &strVarID, CString &strValue);

#endif // QSTTTESTCNTRFRAMEBASE_H
