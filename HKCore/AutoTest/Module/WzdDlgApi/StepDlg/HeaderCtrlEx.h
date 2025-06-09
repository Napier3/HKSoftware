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
	COLORREF m_clrBK; //��ͷ������ɫ
	COLORREF m_clrFont; //��ͷ������ɫ
	CFont* m_pFont; //��ͷ������ʽ
	CImageList  m_ImageList;

};


