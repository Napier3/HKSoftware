
// iSmartTestNewTestFrame.h : CiSmartTestNewTestFrame 类的接口

#pragma once

class CEdgeMqttServerFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CEdgeMqttServerFrame)
public:
	CEdgeMqttServerFrame();

// 属性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CEdgeMqttServerFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
