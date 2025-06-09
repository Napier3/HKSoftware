#if !defined(AFX_MULTICOLUMNCOMBOBOX_H__2EB201C4_6A51_11D4_BD73_000021479D21__INCLUDED_) 
#define AFX_MULTICOLUMNCOMBOBOX_H__2EB201C4_6A51_11D4_BD73_000021479D21__INCLUDED_ 
 
#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// MultiColumnComboBox.h : header file 
// 
 
///////////////////////////////////////////////////////////////////////////// 
// CMultiColumnComboBox window 
 
#define LEFTMARGIN_OF_DROPDOWNLIST		2 
#define LEFTMARGIN_OF_CONTROL			1 
#define RIGHTMARGIN_OF_DROPDOWNLIST		4  
#define SPACE_BETWEEN_COLUMN			1  
 
class CMultiColumnComboBox : public CComboBox 
{ 
// Construction 
public: 
	CMultiColumnComboBox(); 
	 
// Attributes 
public: 
	void	FormatComboBox(UINT TotalColumn = 2, UINT BoundColumn = 0); 
	void	SetColumnWidth(UINT ColumnWidth0, ...); 
	void	SetColumnAlignStyle(UINT ColumnAlignStyle0, ...); 
 
// Operations 
public: 
	void	ResetContent(); 
	int		AddRow(LPCTSTR lpszString0, ...); 
 
// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CMultiColumnComboBox) 
	public: 
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct); 
	//}}AFX_VIRTUAL 
 
// Implementation 
public: 
	virtual ~CMultiColumnComboBox(); 
 
	// Generated message map functions 
protected: 
private: 
	UINT			m_TotalColumn; 
	UINT			m_BoundColumn; 
	UINT			m_TextItemHeight; 
	CPen			m_LightGrayPen; 
	UINT*			m_ColumnWidth; 
	UINT*			m_ColumnAlignStyle; 
	CStringList*	m_ColumnItemList; 
 
	//{{AFX_MSG(CMultiColumnComboBox) 
	//}}AFX_MSG 
 
	DECLARE_MESSAGE_MAP() 
}; 
 
///////////////////////////////////////////////////////////////////////////// 
 
//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 
 
#endif // !defined(AFX_MULTICOLUMNCOMBOBOX_H__2EB201C4_6A51_11D4_BD73_000021479D21__INCLUDED_) 