#pragma once

#include "SclFileCtrlView.h"
#include "IecCfgViewMainBase.h"
// CSclFileDetailView ��ͼ

class CSclFileTreeView;

class CSclFileDetailView : public CIecCfgViewMainBase 
{
	DECLARE_DYNCREATE(CSclFileDetailView)

public:
	CSclFileDetailView(void);
	~CSclFileDetailView(void);

	void InitViews();
	void AttachSclFileTreeView(CView *pSclFileTreeView);
	CSclFileCtrlView* GetSclFileCtrlView();

protected:
	virtual void CreateViews(const CRect &rect, CCreateContext *pContext);

	CSclFileTreeView *m_pSclFileTreeView;
};


// 
// class CSclFileDetailView : public CView
// {
// 	DECLARE_DYNCREATE(CSclFileDetailView)
// 
// protected:
// 	CSplitterWndEx m_wndSplitter;
// 
// 	void SwitchView();
// 	BOOL m_bAdjust;
// 
// protected:
// 	CSclFileDetailView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
// 	virtual ~CSclFileDetailView();
// 
// public:
// 	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
// #ifdef _DEBUG
// 	virtual void AssertValid() const;
// #ifndef _WIN32_WCE
// 	virtual void Dump(CDumpContext& dc) const;
// #endif
// #endif
// 
// protected:
// 	DECLARE_MESSAGE_MAP()
// public:
// 	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
// 	afx_msg void OnSize(UINT nType, int cx, int cy);
// };
// 
// 
