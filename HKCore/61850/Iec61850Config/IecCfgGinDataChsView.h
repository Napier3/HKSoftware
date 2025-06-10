#pragma once


#include "resource.h"
#include "IecCfgDataChsViewBase.h"
#include "..\Module\UI\IecCfgGinDataChsGrid.h"
#include "..\Module\UI\IecCfgGinAppChMapGrid.h"
// CIecCfgGinDataChsView ������ͼ

class CIecCfgGinDataChsView : public CIecCfgDataChsViewBase
{
	DECLARE_DYNCREATE(CIecCfgGinDataChsView)

public:
	virtual void CreateChsGrid();
	virtual void ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData);

	void ShowIecCfgGinAppMaps();

protected:
	CIecCfgGinDataChsView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIecCfgGinDataChsView();
	CIecCfgGinAppChMapGrid *m_pGinAppChMapGrid;

	CIecCfgGinDatas *m_pGinDatas;    //������ʾ�Ŀ��ƿ����ݶ���

public:
	enum { IDD = IDD_IECCFG_GINCTRL_CHS_VIEW };
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
	afx_msg LRESULT OnGetCurrSelGinCh(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnUpdateGinCh(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnGinChAppIDChanged(WPARAM wParam, LPARAM lParam); 
};


