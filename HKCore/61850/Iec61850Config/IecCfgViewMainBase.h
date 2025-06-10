#pragma once


// CIecCfgViewMainBase 视图

class CIecCfgViewMainBase : public CView
{
	DECLARE_DYNCREATE(CIecCfgViewMainBase)

protected:
	CSplitterWndEx m_wndSplitter;

	void SwitchView();
	BOOL m_bAdjust;

	virtual void CreateViews(const CRect &rect, CCreateContext *pContext);

public:
	CIecCfgViewMainBase();           // 动态创建所使用的受保护的构造函数
	virtual ~CIecCfgViewMainBase();
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
	virtual void PostNcDestroy();
public:
	afx_msg void OnDestroy();
};


