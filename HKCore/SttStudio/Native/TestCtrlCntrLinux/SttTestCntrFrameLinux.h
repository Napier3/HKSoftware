#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Module/UI/SttTestCntrFrameBase.h"

//2023-2-20  lijunqing ͨ��ģ��
//#include "../../Module/SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"

class QSttTestCntrFrameLinux : public QSttTestCntrFrameBase
{
    Q_OBJECT

public:
    explicit QSttTestCntrFrameLinux(QWidget *parent = 0);
    virtual ~QSttTestCntrFrameLinux();

public:
	virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestFinished();
	virtual long OnTestStarted();
	virtual long OnTestStoped();
	virtual long OnTestCreated();
	virtual void OnReport(CExBaseObject *pItem) ;
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);


	virtual void FillReport(CExBaseObject *pItem);
	virtual void FillReport();

public://������ر���
	QSttBarBase *m_pToolBar;//������
	QSttMenuWidget *m_pMenuWidget;//�˵���ť��������

	virtual void AdjustToolBarButtons();
	virtual void AdjustStatusBarButtons();

	virtual void UpdateButtonsStateByID();
	virtual void Before_OnCmd();

	virtual void InitUI(); 
	virtual void CalRectArea();

	virtual void UpdateButtonStateByID(const CString &strID,bool bState,bool bShow = true);//�ڶ������������ܷ��������������������Ƿ���ʾ
	virtual void UpdateToolButtons_FloatPanel();//���¸��㴰��
	virtual void UpdateEnableState(const CString &strState);
	virtual void InitSttIecRecord();//��ʼ��¼��
	//zhouhj 20230606 ��Ϊʹ��InitAfterCreateSttMacroPara����
//	virtual void InitSttCap_MUTerminal();//�ϲ���Ԫ�����ն˲���ʱ,��ʼ��IEC̽�⹦��
	virtual BOOL IsMenuWidget(QWidget *pWidget);
	virtual void UpdateRptHtml();
	virtual void UpDateUdcVal();//20240626 suyang �������� ���豸�и���ֱ��ֵ��ϵͳ�����и���ֱ��ͳһ

public:
	virtual void OnCmd_Menu();
	virtual void OnCmd_IecCap(); //2022-4-10  lijunqing
	virtual void OnCmd_IecCapWriteFile(); //2022-6-13  lijunqing
	virtual void OnCmd_IecCapDebugHead(); //2022-6-13  lijunqing
	virtual void InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns = true);//20220526 �Դ����������IEC��������ʼ��
	virtual void OnCmd_Liveupdate();
	virtual void OnCmd_ULiveupdate();
	virtual void OnCmd_AuxIPSet();
	virtual void OnCmd_AddMacro(BOOL bUseNameID=FALSE);
	virtual void OnCmd_StartTest();
	virtual void OnCmd_PpIotEngineClient();
	virtual void OnCmd_NetworkConfig();

	virtual void OnCmd_OpenTest();

	virtual void InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns = true);
	virtual void OnCmd_RemoteCtrl();
	virtual void OnCmd_PpIotEngineClientDlg(); //װ��ͨѶ�Ի���
	//zhouhj 2024.3.17 ֹͣ���Ժ�,���̽����Խ���ָ�,��ֹ��ʼ��ֹͣ��ť�޷�����
	virtual void OnCmd_StopTest();

//2023-2-20  lijunqing ͨ��ģ��  ���������ʵӦ�÷ŵ�QSttTestCntrFrameBase
//������������Windows�汾ʵ���ˣ�������ʱ�Ͳ��޸Ļ���QSttTestCntrFrameBase
public:
	//zhouhj 2023.1.4 �������
//	QPpSttIotEngineClientWidget *m_pEngineClientWidget;
	// zhouhj 2024.2.1 ���ӷ���ֵ,���ڱ�ʶ�Ƿ񴴽���Ӧ����,�ڴ�������Ĺ��캯����,���������
	virtual BOOL CreateEngineClientWidget();


protected:
	void FillReports(CExBaseList *pItems);
	void FillReport_ForState();
	void FillReport_OnlyHtmlRpt(CExBaseObject *pItem);//ֻ����html��������,������ԭʼ����Ľ����ʾ,������ӡ���Խ��
	BOOL ModifyReport(CSttReport *pReport,const CString &strItemID = "");//�������ȡ�����Ĳ���

signals:
	
private slots:
	virtual void slot_CloseMenu();

protected:
    virtual void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
