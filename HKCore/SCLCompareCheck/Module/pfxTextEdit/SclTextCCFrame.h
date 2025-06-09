#pragma once


// CSclTextCCFrame 框架

class CSclTextCCFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSclTextCCFrame)

protected:
	CSclTextCCFrame();           // 动态创建所使用的受保护的构造函数
	virtual        ~CSclTextCCFrame();

public:
        virtual BOOL   PreCreateWindow(CREATESTRUCT& cs);
        virtual BOOL   OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

#ifdef _DEBUG
        virtual void   AssertValid() const;
        virtual void   Dump(CDumpContext& dc) const;
#endif

protected:
        CSplitterWnd   m_wndSplitter;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};


