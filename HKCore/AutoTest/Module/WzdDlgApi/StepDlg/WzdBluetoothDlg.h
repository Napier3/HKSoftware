#pragma once

#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/WzdDlgList.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/GuideBook.h"
#include "../../../Module/XSmartTestClientInterface.h"
#include "../../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"
#include "../../../Module/XfileMngrBase/XFolderTreeCtrl.h"
#include "../../../Module/XfileMngrBase/XFileMngr.h"
#include "../StepCtrl/GridiSmartTestBluetWzd.h"
#include "WzdFile.h"
#include "../../BlueTooth/Module/TestTool/BlueDataPross.h"
#include "../WzdDlgSendState.h"

// CWzdBluetoothDlg �Ի���

#define SHOWSTATE_TIMER_ID  128

class CWzdBluetoothDlg : public CWzdDlgBase, public CXSmartTestEventInterface
{
	DECLARE_DYNAMIC(CWzdBluetoothDlg)

public:
	CWzdBluetoothDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzdBluetoothDlg();

// �Ի�������
	enum { IDD = IDD_WZDBlueth_DIALOG };

	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, 
		long nItemIndex, const CString& strItemID, const CString& strState, long nSelect){ return 0; }
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){ return 0; }
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){ return 0; }
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex){ return 0; }
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent){ return 0; }
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent){ return 0; }
	virtual long OnTestCreated(const CString& strDeviceID){ return 0; }
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID){ return 0; }
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, 
		long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState){ return 0; }
	virtual long OnTestProcess(CExBaseList* pSttParas){ return 0; }
	virtual long OnReTestFinished(CExBaseList* pSttParas){ return 0; }
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){ return 0; }
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){ return 0; }
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){ return 0; }
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){ return 0; }
	virtual long On_Ats_CreateTest(const CString &strGbrptFile){ return 0; }
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd) { return 0; }
	virtual long OnReport(CExBaseList* pSttParas)	{	return 0;	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

	void InitBluetooth();

private:
	CWzdDlgButton m_txtTitle;
	CWzdDlgButton m_btnIcon;
	CWzdDlgButton m_btnBottom;
	CWzdDlgNormalBtn m_btnReturn;
	CWzdDlgNormalBtn m_btnRecv;

	CStatic m_sWORD1;
	CStatic m_sWORD2;
	CWzdDlgButton m_sPIC;
	CStatic m_sLinkState;

	CGridiSmartTestBluetWzd m_DataShow;

	CFont *m_Font;

	CBlueDataPross m_BlueDataPross;

	//δʹ��ͳһ�Ľ���չʾ������Ϊ�ƶ����������Ͳ���֪ͨ�Ƿ�ֹͣ�ļ����͵�
	CWzdDlgSendState m_DlgSendS;	

	bool m_bRecvTask;	//�����������״̬

	void XUI_InitAdjust();
	void InitBtns();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnRecv();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg LRESULT OnShowRecv0x92Data(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnShowRecv0x94Data(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnStartSendFileData(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnEndSendFileData(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnStopSendFileData(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnRecordSendFileData(WPARAM wPara,LPARAM lPara);

	void SetCheckOver(int iState);

	//������ֹͣ��������
	void OpenBlueToothServer();
	void CloseBlueToothServer();
};
