#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

#include "..\Module\SCL\SclFileRead.h"
// ���в������ CSclFileFrame ���

class CSclFileFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSclFileFrame)
protected:
	CSclFileFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


