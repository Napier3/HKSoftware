#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "..\Module\SCL\SclFileRead.h"
// 带有拆分器的 CSclFileFrame 框架

class CSclFileFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSclFileFrame)
protected:
	CSclFileFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CSclFileFrame();

	CSplitterWnd m_wndSplitter;
	CString m_strTscdFile;

public:
	CSclFile *m_pSclFile;
	CSclFileRead *m_pSclFileRead;
	CSclStation m_oSclStation;
	void UpdateIecCfgFilesComboBox();

	void OpenTscdFile(const CString &strTscdFile);
	void OpenTscdFile(const CString &strTscdFile, const CString &strIedId);
	void OnShowCurIED(const CString &strIedId);

	void CloseSclFileFrame();

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};


