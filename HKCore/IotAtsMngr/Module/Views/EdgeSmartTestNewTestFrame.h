
// iSmartTestNewTestFrame.h : CiSmartTestNewTestFrame ��Ľӿ�

#pragma once

class CEdgeSmartTestNewTestFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CEdgeSmartTestNewTestFrame)
public:
	CEdgeSmartTestNewTestFrame();

// ����
public:

// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CEdgeSmartTestNewTestFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
