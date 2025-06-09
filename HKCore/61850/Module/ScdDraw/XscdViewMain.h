#pragma once

#include "..\IecCfgTool\IecCfgFile.h"
#include "XScdDrawViewCfg.h"
#include "XScdDrawViewStationThumbnail.h"
#include "XScdDrawViewIedThumbnail.h"
#include "XScdDrawViewIedDetail.h"
#include "..\..\..\Module\BaseClass\MemBufferDC.H"
// CXscdViewMainBase 视图

class CXscdViewMainBase : public CScrollView , public CXDrawBaseInterface_ViewWindow
{
protected:
	DECLARE_DYNCREATE(CXscdViewMainBase)

//////////////////////////////////////////////////////////////////////////
//CXDrawBaseInterface_ViewWindow
public:
	virtual void ViewToWindow(CPoint &point);
	virtual void WindowToView(CPoint &point);

	virtual void ViewToWindow(CRect &rect);
	virtual void WindowToView(CRect &rect);

	virtual void OnXScdElementLDblClk(CXDrawElement *pElement)	{	};
	virtual BOOL  OnXScdElementRButtonDown(UINT nFlags, CPoint point);

protected:
// 	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	CXScdDrawViewBase *m_pXScdDrawView;
	CExBaseObject     *m_pXScdDataRef;

	CMemBufferDC m_oMemDC;

	BOOL m_bOnMouseDragViewState;
	CPoint m_pointOrigin;

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	CXscdViewMainBase();           // 动态创建所使用的受保护的构造函数
	virtual ~CXscdViewMainBase();
	void SetRefDoc(CDocument *pDoc)	{	m_pDocument = pDoc;	}

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg void OnFilePrintPreview();
	virtual void PostNcDestroy();
public:
	//afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnInitialUpdate();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg LRESULT OnSetFont(WPARAM hFont, LPARAM lParam);
	afx_msg LRESULT OnGetFont(WPARAM hFont, LPARAM lParam);
	afx_msg LRESULT OnXScdDrawChanged(WPARAM hFont, LPARAM lParam);

};

//////////////////////////////////////////////////////////////////////////
//CXscdViewCfgMain
class CXscdViewCfgMain : public CXscdViewMainBase
{
protected:
	DECLARE_DYNCREATE(CXscdViewCfgMain)

public:
	CXscdViewCfgMain();
	virtual ~CXscdViewCfgMain();

	CIecCfgDatasMngr *m_pIecCfgDatasMngr;
	CXScdDrawViewCfg m_oXScdDrawViewCfg;

	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

};


//////////////////////////////////////////////////////////////////////////
//CXscdViewCfgMain
class CXscdViewStationThumbMain : public CXscdViewMainBase
{
protected:
	DECLARE_DYNCREATE(CXscdViewStationThumbMain)

public:
	CXscdViewStationThumbMain();
	virtual ~CXscdViewStationThumbMain();

	CXScdDrawViewStationThumbnail m_oXScdDrawViewThumbnail;
	CSclStation *m_pSclStation;

	void CreateXscdViewThumbMain(CSclStation *pSclStation);
};

//////////////////////////////////////////////////////////////////////////
//CXscdViewCfgMain
class CXscdViewIedThumbMain : public CXscdViewMainBase
{
protected:
	DECLARE_DYNCREATE(CXscdViewIedThumbMain)

public:
	CXscdViewIedThumbMain();
	virtual ~CXscdViewIedThumbMain();

	CXScdDrawViewIedThumbnail m_oXScdDrawViewThumbnail;
	CXScdDrawIedThumbnail *m_pXScdDrawIedThumb;

	void CreateXscdViewThumbMain(CXScdDrawIedThumbnail *pXScdDrawIedThumb);
};

//////////////////////////////////////////////////////////////////////////
//CXscdViewIedDetailMain
class CXscdViewIedDetailMain : public CXscdViewMainBase
{
protected:
	DECLARE_DYNCREATE(CXscdViewIedDetailMain)

public:
	CXscdViewIedDetailMain();
	virtual ~CXscdViewIedDetailMain();

	CXScdDrawViewIedDetail m_oXScdDrawViewIedDetail;

	void CreateXscdViewIedDetailMain(CXScdDrawLine_Ctrls *pXScdDrawLine_Ctrls);
};

