#pragma once
#include "WzdDlgMngr.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/WzdDlgList.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/GuideBook.h"
#include "../../../Module/XSmartTestClientInterface.h"
#include "../../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"
#include "../../../../BlueTooth/Module/TestTool/OrderInfo0x92.h"

#include "ThreadPrgsDlg.h"
#include "../WzdDlgSendState.h"
#include "WzdDlg_AutoTest.h"

//2023-4-16  lijunqing  �ر�
#define TIMER_ID_CLOSE_WZD   1144

//ģ������ص���Ŀ�������ù̶�ID�ģ���Ҫ������⴦��
#define ID_CONSTANT_ITEM_RPTVIEW        _T("UIRpt")    //���ڻ��ܴ洢��Ŀ����İ�ȫ��ʩ��Ŀ��ID
#define ID_CONSTANT_DATA_ERRANALYSE     _T("Unqualified_Analysis")    //������ȫ��ʩ�У������ϸ����ڴ洢���ϸ��������ı�������ID
#define ID_CONSTANT_DATA_PREFIX_SHORT   _T("S_")  //��ȫ��ʩ�У����ڶ����ݣ�һ��չʾ�������ݣ�����ID�ù̶�ǰ׺
#define ID_CONSTANT_ITEM_PREFIX_CONFIRM _T("Confirm_")  //��ȫ��ʩ������Ҫ�˹�ȷ�ϵ���Ŀ����ĿID�Ĺ̶�ǰ׺

//����״̬
enum tagNetState
{
	NetState_BlueTooth = 0,
	NetState_Ethernet
};

class CWzdMainDlg : public CWzdDlgBase, public CXSmartTestEventInterface 
{
	DECLARE_DYNAMIC(CWzdMainDlg)
private:
	CWzdDlgButton m_txtTitle;
	CWzdDlgButton m_btnIcon;
	CWzdDlgButton m_btnBottom;
	CWzdDlgNormalBtn m_btnPrev;
	CWzdDlgNormalBtn m_btnNext;
	CButton m_grpBorder;
	CDialog m_listStep;
	CDialog m_dlgStep;
	CFont m_font;
	CWzdDlgMngr m_oStepsMngr;//DVM������
	CWzdDlgList* m_pStepList;
	
	CString m_strIecfgFile;
	CString m_strGbXmlFile;
	CString m_strGbRptFile;
	CString m_strReportFile;
	CString m_strExRptFile;

	CString m_strFileCfg;
	CString m_strFileVolt;
	CString m_strFileType;
	CString m_strFileTest;
	CString m_strComm;

	CXSmartTestClientInterface *m_pSmartTestClient;

private:
	//�Զ��������ļ�
	CString m_strParameterMd5;
	CString m_strSettingMd5;
	CString m_strEnaMd5;
	CString m_strIP;
	CString m_strFactory;

	//ƴ��·��ʹ��
	CString m_strUser;
	CString m_strSCDFile;

	//ƴ������ʹ��
	CString m_strIedName;   //װ�����ơ������������ױ�
	CString m_strIedModel;   //װ���ͺ�
	CString m_strStationName;   //���վ����
	CString m_strIedDesc;  //װ�����������������/�������ơ�

public:
	CIecCfgFile* m_pCurIecCfgFile;
	CSclStation m_oSclStation;
	CGuideBook m_oGuideBook;
	CString m_strGuideBookIecfgFile;
	CDvmDataset m_Recv0x92Data;
	CDataTypes m_oDataTypes;
	//���һ�����Խ���
	CWzdDlg_AutoTest* m_pAutoTest;


public:
	CWzdMainDlg(CWnd* pParent = NULL);
	virtual ~CWzdMainDlg();

	enum { IDD = IDD_WZDMAIN_DIALOG };

	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, 
		long nItemIndex, const CString& strItemID, const CString& strState, long nSelect);
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(CSttParas *pParas);	//20231026 huangliang 
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent);
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent);
	virtual long OnTestCreated(const CString& strDeviceID);
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID);
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, 
		long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState);
	virtual long OnTestProcess(CExBaseList* pSttParas);
	virtual long OnReTestFinished(CExBaseList* pSttParas);
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles);
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs);
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs);
	virtual long On_Ats_CreateTest(const CString &strGbrptFile){ return 0; }
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd) { return 0; }
	virtual long OnReport(CExBaseList* pSttParas);

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg LRESULT OnSenSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelTestChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelCfg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelComm(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOpenSclFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDvmMapDoNext(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStepListChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableNext(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnablePrev(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableReturn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImpSetUpdateMd5(WPARAM wParam, LPARAM lParam);
	CRect GetDlgRect();
	CRect GetListRect();
	void InitDlgs();
	void InitList();
	void InitBtns();
	CWzdDlgButton* InitListItem(const CString& strText, BOOL bImg, void* pItemData);
	void CreateNewTest();
	void GenerateFileName();
	void SaveWzdXmlFile();

public:
	void SetIEDInfo(const CString &strIedName, const CString &strIedModel
		, const CString &strStationName, const CString &strIedDesc);
	void SetIedInfoToGlobal();
	afx_msg LRESULT OnIEDSelText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIEDSelSelect(WPARAM wParam, LPARAM lParam);
	void CmpDeviceFile_LoadIecFile(const CString &strFile, const CString &strIecfg);

	//20230619 huangliang ��ʼ��IED�ļ���ѡ��
	void InitIECFileChoose();

public:
	virtual void OnInitialUpdate();
	virtual void JumpToPrevDlg();
	virtual void JumpToNextDlg();
	virtual void SetActiveDlg(const CString& strID);
	virtual BOOL InitUI(CDataGroup* pDataGroup); //�½�����ʱ�ĳ�ʼ��UI
	virtual void LoadUI(); //���ز���ʱ�ĳ�ʼ��UI
	CDataGroup* IsLoadCfgXml() { return m_pDataCfg; }
	void ClearCfgXml();
	void OnWindowPosChanging();
	DECLARE_MESSAGE_MAP()


//2023-4-18  lijunqing
public:
	void CWzdDlg_IEDSel_DoNext(CWzdDlgBase *pDlg);

	void OpenGbRptForQue(const CString &strFilePath);
	void OpenGbRptFile(const CString &strFilePath);

	//20230609 huangliang 
	void SetDataInGlobal(CDvmDataset *dataG);
	void SetRecv0x92DataInGlobal();
	void ClearBlueData();
	void CloseTestClient();	

	//20231023 huangliang ��ӻ�ȡ������Ϣ��¼
	CString GetFactory(){ return m_strFactory; }

	//20231025 huangliang
	void TestClientExportRpt();
	void TestClientStartTest();
	void TestClientStopTest();
	void SetItemState(CString strMacroID, long nSelect);
	void SetTestParas(const CString &strDeviceID, CString &strTestParas);

	void SetNetState(long nState);
	void FinishInputData(CExBaseList* pDatas);

	void TestCurrentItem(CString strPath);
	void TestFromItem(CString strPath);

private:
	//CThreadPrgsDlg *m_pThreadPrgsDlg;
	CWzdDlgSendState *m_pThreadPrgsDlg;
};

extern CWzdMainDlg* g_pWzdMainDlg;