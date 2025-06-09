#pragma once

class CAudioButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CAudioButton)
public:
	CAudioButton();
	virtual ~CAudioButton();

private:
	CString m_strImageFilePath;

	void DrawTransparent(HDC hdcDest,int nWidthDest,int nHeightDest,
		HDC hdcSrc,int nWidthSrc,int nHeightSrc,COLORREF crTransparent);
	void DrawTransparent(CDC* pDC, HBITMAP hBitmap);

public:
	void LoadBitmap(CString strFilePath);
	BOOL OnEraseBkgnd(CDC* pDC); 
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

	DECLARE_MESSAGE_MAP()
};