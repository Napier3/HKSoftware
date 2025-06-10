#pragma once


#include "..\Module\SCL\SclIecCfgDatasGrid.h"

// CSclFileCtrlChsView ������ͼ

class CSclFileCtrlChsView : public CFormView,  public CExBaseListGridOptrInterface
{
	DECLARE_DYNCREATE(CSclFileCtrlChsView)

public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

public:
	void ShowDatas(CExBaseList *pDatas);

protected:
	CSclFileCtrlChsView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSclFileCtrlChsView();
	CCSclIecCfgCtrlChnGrid m_oCSclIecCfgCtrlChnGrid;

public:
	enum { IDD = IDD_SCLFILE_CTRLCHS_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


