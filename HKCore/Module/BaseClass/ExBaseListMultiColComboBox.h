#if !defined(_ExBaseListMultiColComboBox_h__) 
#define _ExBaseListMultiColComboBox_h__ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
#include "ExBaseListComboBox.h"

// ExBaseListMultiColComboBox.h : header file 

#define MCCB_LEFTMARGIN_OF_DROPDOWNLIST		2 
#define MCCB_LEFTMARGIN_OF_CONTROL					2 
#define MCCB_RIGHTMARGIN_OF_DROPDOWNLIST		4  
#define MCCB_SPACE_BETWEEN_COLUMN					2  

class CExBaseListMultiColComboBox : public CExBaseListComboBox 
{ 
// Construction 
public: 
	CExBaseListMultiColComboBox(); 
	virtual ~CExBaseListMultiColComboBox(); 

	virtual void GetItemColText(long nIndex, long nCol, CString &strText);
	virtual void GetItemSelText(long nIndex, CString &strText);
	virtual void InitMultiColComboBox() = 0;

public:
	virtual void ShowBaseList(CExBaseList *pList);

// Attributes 
public: 
	void	FormatComboBox(UINT nTotalColumn = 2, UINT nBoundColumn = 0); 
	void	SetColumnWidth(UINT nColumnWidth0, ...); 
	void	SetColumnAlignStyle(UINT nColumnAlignStyle0, ...); 

// Operations 
public: 

public: 
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct); 

protected: 
	void FreeMultiColComboBox();

protected: 
	UINT			m_nTotalColumn; 
	UINT			m_nBoundColumn; 
	UINT			m_nTextItemHeight; 
	CPen			m_oLightGrayPen; 
	UINT*			m_pnColumnWidth; 
	UINT*			m_pnColumnAlignStyle; 
}; 

#endif // !defined(_ExBaseListMultiColComboBox_h__) 