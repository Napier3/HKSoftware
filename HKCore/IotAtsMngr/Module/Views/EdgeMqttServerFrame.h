
// iSmartTestNewTestFrame.h : CiSmartTestNewTestFrame ��Ľӿ�

#pragma once

class CEdgeMqttServerFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CEdgeMqttServerFrame)
public:
	CEdgeMqttServerFrame();

// ����
public:

// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CEdgeMqttServerFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
};
