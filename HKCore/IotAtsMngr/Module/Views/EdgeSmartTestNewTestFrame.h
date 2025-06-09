
// iSmartTestNewTestFrame.h : CiSmartTestNewTestFrame 类的接口

#pragma once

class CEdgeSmartTestNewTestFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CEdgeSmartTestNewTestFrame)
public:
	CEdgeSmartTestNewTestFrame();

// 属性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CEdgeSmartTestNewTestFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
