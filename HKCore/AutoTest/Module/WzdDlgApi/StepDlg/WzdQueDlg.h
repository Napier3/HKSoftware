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
#include "../StepCtrl/GridiSmartTestWzd.h"
#include "WzdFile.h"

// CWzdQueDlg 对话框

class CWzdQueDlg : public CWzdDlgBase, public CXSmartTestEventInterface
{
	DECLARE_DYNAMIC(CWzdQueDlg)

public:
	CWzdQueDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzdQueDlg();

// 对话框数据
	enum { IDD = IDD_WZDQUE_DIALOG };

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

	void InitLoadFileData();

private:
	CWzdDlgButton m_txtTitle;
	CWzdDlgButton m_btnIcon;
	CWzdDlgButton m_btnBottom;
	CWzdDlgNormalBtn m_btnReturn;
	CWzdDlgNormalBtn m_btnDelete;
	CWzdDlgNormalBtn m_btnOpen;

	CXFileMngr m_FileMngr;
	CXFolderTreeCtrl m_treeFile;

	CStatic m_sQueTJ;
	CStatic m_sRecord;
	CStatic m_sTimeFG;

	CButton m_CheckZZMS;
	CButton m_CheckZZXH;
	CButton m_CheckJYSJ;

	CEdit m_editZZMS;
	CEdit m_editZZXH;

	CDateTimeCtrl m_startTime;
	CDateTimeCtrl m_endTime;

	CWzdDlgNormalBtn m_btnQueAll;
	CWzdDlgNormalBtn m_btnQueWhere;

	CGridiSmartTestWzd m_DataShow;

	CButton m_grpBorder;

	void XUI_InitAdjust();
	void InitBtns();
	void ExpandTreeItem(HTREEITEM rootItem);

	//缓存选择的路径
	CXFileMngr* m_pSelFileM;

	// 是否过滤
	BOOL m_bQueWhere;
	// 过滤装置描述
	CString m_sQueZZMS;
	// 过滤装置型号
	CString m_sQueZZXH;
	// 过滤检验开始时间
	COleDateTime m_sQueStartTime;
	// 过滤检验检验时间
	COleDateTime m_sQueEndTime;
	void QueRecord();
	BOOL CheckWhereData();
	void QueRecordData();

	//缓存查询到的对象
	CXFileMngr m_TempFileM;
	void FindAllFile(CXFileMngr* pSelFileM);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonQue();
	afx_msg LRESULT OnGridSelChange(WPARAM wParam, LPARAM lParam);

	void ShowDataToGrid();
	
};
