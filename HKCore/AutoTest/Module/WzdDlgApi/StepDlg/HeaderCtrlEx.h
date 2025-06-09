#pragma once


// CHeaderCtrlEx

class CHeaderCtrlEx : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlEx)

public:
	CHeaderCtrlEx();
	virtual ~CHeaderCtrlEx();

	void SetHeaderCtrlFont(CFont* pFont);
	void SetHeaderCtrlBKColor(COLORREF clrBk);
	void SetHeaderCtrlFontColor(COLORREF clrFont);

protected:
	DECLARE_MESSAGE_MAP()
	void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
	//afx_msg void OnHdnBegintrack(NMHDR *pNMHDR, LRESULT *pResult);

private:
	COLORREF m_clrBK; //表头背景颜色
	COLORREF m_clrFont; //表头字体颜色
	CFont* m_pFont; //表头字体样式
	CImageList  m_ImageList;

};


