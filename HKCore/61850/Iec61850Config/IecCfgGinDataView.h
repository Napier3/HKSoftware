#pragma once


#include "resource.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "IecCfgDataViewBase.h"
#include "..\Module\UI\IecCfgGinDataGrid.h"

// CIecCfgGinDataView ������ͼ

class CIecCfgGinDataView : public CIecCfgDataViewBase
{
	DECLARE_DYNCREATE(CIecCfgGinDataView)

public:
	virtual CIecCfgDatasBase* GetIecCfgDatas();
	virtual void CreateIecCfgDataGrid();

protected:
	CIecCfgGinDataView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIecCfgGinDataView();
	void UpdateAppMaps();

public:
	enum { IDD = IDD_IECCFG_GINCTRL_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
// 	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnAddEx();
	afx_msg void OnBnClickedBtnDeleteEx();
	afx_msg void OnBnClickedBtnPasteEx();

};


