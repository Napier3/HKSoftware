#pragma once
#include "WzdDlgBase.h"
#include "../../../Module/GuideBook/SetsTools/StesFileXmlTool.h"
#include "../../../Module/GuideBook/SetsTools/StesFilePdfTool.h"
#include "../../../Module/GuideBook/GuideBook.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/ImpSetGrid.h"
#include "../StepCtrl/WzdDlgTabCtrl.h"
#include "afxwin.h"

class CWzdDlg_ImpSet : public CWzdDlgBase, public CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CWzdDlg_ImpSet)
private:
	CStatic m_stcFromFile;
	CStatic m_stcRealCal;

	CStatic m_stcMd5FromFile_Parameter;
	CStatic m_stcMd5FromFile_Setting;
	CStatic m_stcMd5FromFile_Ena;

	CEdit m_edtReadFromFileMd5_Parameter;
	CEdit m_edtReadFromFileMd5_Setting;
	CEdit m_edtReadFromFileMd5_Ena;

	CString m_strReadFromFileMd5_Parameter;
	CString m_strReadFromFileMd5_Setting;
	CString m_strReadFromFileMd5_Ena;

	CStatic m_stcMd5Real_Parameter;
	CStatic m_stcMd5Real_Setting;
	CStatic m_stcMd5Real_Ena;

	CEdit m_edtRealCalMd5_Parameter;
	CEdit m_edtRealCalMd5_Setting;
	CEdit m_edtRealCalMd5_Ena;

	CString m_strRealCalMd5_Parameter;
	CString m_strRealCalMd5_Setting;
	CString m_strRealCalMd5_Ena;

	CStatic m_stcRslt;
	CEdit m_edtRslt;
	CString m_strRslt;

	CWzdDlgTabCtrl m_tabPdfDvm;

	int m_nSetsType;
	CString m_strSetsFile;
	BOOL m_bFileType;

	CImpSetGrid m_gridDsFile;
	CStesFilePdfTool m_oStesFilePdfTool;
	CStesFileXmlTool m_oSetsFileXmlTool;

public:
	CWzdDlg_ImpSet(CWnd* pParent = NULL);
	virtual ~CWzdDlg_ImpSet();

	enum { IDD = IDD_IMPSET_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual void OnInitialUpdate();
	void ShowSets_Pdf();
	void ShowSets_Xml();
	void GetRslt_Xml();
	void GetRslt_Pdf(CDataSet *pGbDataset);
	void UpdateFileSelected(bool bCorrect = false);
	BOOL CheckSetsFileFormat();
	void SetFileType(BOOL bIsXml);
	void SetFilePath(const CString& strFile);
	void GetMd5(CString& strParameterMd5, CString& strSettingMd5, CString& strEnaMd5);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTcnSelchangeTabPdfDvm(NMHDR *pNMHDR, LRESULT *pResult);
	HRESULT OnUpdateMD5(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonCorrect();

	CWzdDlgNormalBtn m_btnCorrect;
	CWzdDlgNormalBtn m_TimeUnit;				//20231020 luozibing 变更时间单位

	//20230810 huangliang 添加数据对比
	CString m_strTipMsg;
	void ContrastPdfData();
	int ContrastPdfData(CString strTilte);
	BOOL ContrastData(CExBaseObject *pData, CDvmDataset *pSrcDatast, CDataSet *pGbDataset);
	afx_msg void OnBnClickedButtonTimeunit();
	
};