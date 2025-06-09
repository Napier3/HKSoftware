#pragma once

class CWzdDlgProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CWzdDlgProgressCtrl)
public:
	CWzdDlgProgressCtrl();
	virtual ~CWzdDlgProgressCtrl();

private:
	CImage m_imgProgress;
	void DrawTransparent(CDC* pDC, CRect rc);

public:
	void OnPaint();
	BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
};