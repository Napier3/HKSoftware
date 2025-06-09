#pragma once
#include "WzdDlgBase.h"
#include "../MmsApi/MmsApi.h"
#include "../MmsApi/MmsProgressDlg.h"
#include "../StepCtrl/DvmReadTreeCtrl.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/DvmReadGrid.h"

class CTagDAObject : public CExBaseObject
{
public:
	tagDA* m_pData;

	int m_nEntryNum;
	CString m_strEntryID;
	CString m_strLogEntryName;
	CString m_strEntryTime;

	CTagDAObject() 
	{ 
		m_pData = NULL; 
		m_nEntryNum = 0;
	}

	virtual ~CTagDAObject(){}
};

class CWzdDlg_DvmRead : public CWzdDlgBase, CMmsApi
{
	DECLARE_DYNAMIC(CWzdDlg_DvmRead)
private:
	CWzdDlgNormalBtn m_btnDvm;
	CStatic m_txtDvm;
	CDvmReadTreeCtrl m_treeDvm;
	CEdit m_editIP;

	CDvmReadGrid m_gridDvm;

	CStringArray m_astrAinColName;
	DWORD m_dwMmsNodeType;
	long m_nMmsDeviceIndex;
	long m_nMmsLDeviceIndex;
	long m_nMmsDsIndex;
	tagDA *m_pCurrSelDA;
	BOOL m_bIsCurrListHeaderAin;
	BOOL m_bIsCurrDataSetAin;
	CString m_strFileDirPath;
	int		m_nCmbIndex;
	HBRUSH	m_hBkBr;

	CMmsProgressDlg *m_pProgDlg;

public:
	CWzdDlg_DvmRead(CWnd* pParent = NULL);
	virtual ~CWzdDlg_DvmRead();

	enum { IDD = IDD_DVMREAD_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void InitListHeader();
	void UpdateList(BOOL bUpdateHead=FALSE);
	void UpdateFileDir(long nMmsDeviceIndex);
	void UpdateJournal();

	BOOL InitCurrDsAin();
	void SetListItemText(int nRow,tagDA* pDA);
	void UpdateListItemText(int nRow,tagDA* pDA);
	void UpdateDsData(BOOL bUpdateHead=FALSE);

	XMMS_FILE_SYS_OBJ* find_dir_by_path(const CString &strObjParentPath,
		const CString &strSearchPath, XMMS_FILE_SYS_OBJ *pFileDir);

	virtual BOOL DoNext();

public:
	void InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink=FALSE);
	void InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas=FALSE);
	BOOL CallFirstFunc(long nDeviceIndex);
	BOOL CallCurrFunc(long nDeviceIndex);
	BOOL CallNextFunc(long nDeviceIndex);
	void ValidateCurrFunc(long nDeviceIndex);
	void ValidateCurrFunc_ReadZone(CFuncParam *pParam);
	void StartProgress();
	void StopProgress(long nDeviceIndex);
	void ReadMmsEngineConfig();
	LRESULT OnMmsCmdFinish_Error(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsCmdFinish(WPARAM wParam,LPARAM lParam);
	BOOL IsFuncsAllFinish(long nDeviceIndex);
	LRESULT OnMmsCmdFinish_View(WPARAM wParam,LPARAM lParam);
	void ResetWriteFailErrorCode();
	void InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas);
	void InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType);
	void InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	void InitReadDeviceFuncParas(ST_INT nDeviceIndex, BOOL bReadAll, BOOL bFreeFuncParas);
	BOOL CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex);
	void InitCallReportFlagDefault(ST_INT nDeviceIndex);
	void OnUnlink(CFuncParamEx *pFuncParaEx);
	virtual long MMS_DataOpeProc(CFuncParamEx *pFuncParaEx);
	BOOL SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsNodeSelChanged(WPARAM wParam,LPARAM lParam);

public:
	ST_VOID mmsi_RecvRptData();

public:
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnDvm();
};