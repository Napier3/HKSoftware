///////////////////////////////////////////////////////////////////////////
// Definition
//-------------------------------------------------------------------------
// File........................HexEditBase.h
// Version.....................1.1.0.0
// Autor(s)....................Ch. Kuendig / kuendigc@spectraweb.ch
// Operating system(s).........Windows NT/2000/[95?/98?]
// Compiler(s).................MS VC++, SP3, SP5
//-------------------------------------------------------------------------
// CHexEditBase is a Hex-Edit-Control based on MFC and the CWnd class.
// It implements basic behavior to edit/view Data in hexadecimal view 
// (binary). It's been a fast implementation and it's not that carefully
// designed and as a result of that it doesn't support all the features
// one can dream of. Scrolling is a little slow with slow computers because
// basiacally the whole control is redrawn instead of bitblittering parts
// of the existing control.
//
// Features:
// - multi- / singleline (depending on the windows-style)
// - automatical scrolling when multiline
// - horizontal scrolling without scrollbars when singleline
// - show Address (on/off)
// - variable Address-Size 
// - show Binary (on/off)
// - cursor navigation (arrows, home, end, page up/down)
// - copy/paste (ctrl + c / ctrl + v)
// - context menue (copy / paste)
//   --> strings from resources, when defined: IDS_CONTROL_COPY, IDS_CONTROL_PASTE
// - edit (only hex-data, not binary)
// - selection (only hex-data)
// - special highlighting of a section (not selection)
// - show selection always (only multiline mode)
// - set how many bytes per row or let it calculate (automatic)
// - set colours (every colour can be set)
//   - address: text & background
//   - hexdata: 
//	   - normal: text, background
//     - selected & focus: text & background
//     - selected & no focus: text & background
//	   - highlighted section: text, background and frame (border)
//   - bindata: text & background
//   - unused area (window-background)
// - set readonly (enabled/disabled: no colour-difference) 
//   (derive from CHexEditBase and override SetReadonly: change colours there)
//
// Basic Instructions:
// - Use folowing Code in the InitInstance:
//	 AfxOleInit();
//	 CHexEditBase::RegisterClass();	 (when using the CHexEditBase_SC windows-class)
// - Use the view or/and the control (depending on project)
// - Using the view is bloody simple (check the demo-project: HexEditCtrl)
// - Using the control is easy as well (easiest way:)
//   - Edit the dialogresource and insert edit-controls where you want 
//     to see the hex-control later. Set multiline-flag when you want to 
//     use the control as a multiline.
//   - Use the ClassWizard to connect a member-variable (control (NOT value))
//     with the previously inserted edit-control. (Give class CEdit first)
//   - When this is done, use the code editor and replace the CEdit (int the h-file)
//     with CHexEditBase. Don't forget to include "HexEditBase.h" there.
//	 - Go to the InitDialog (or insert it) and use the m_HexEdit (or how ever your
//     member is called) to set data: m_HexEdit.SetData((BYTE*)"dummydata", 9);
//   - Use other members to set other attributes (set bUbdate (usually last parameter for set-methodes)
//     only with the last SetXXXXX-Methode:
//	   (example for use in a view-class derived from CHexEditBaseView)
//	   GetHexEditCtrl().SetAddressSize(4, false);
//	   GetHexEditCtrl().SetShowAddress(true, false);
//     GetHexEditCtrl().SetShowAscii(true, false);
//     GetHexEditCtrl().SetBytesPerRow(16, true, true);
//
// Legal Notices:
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
// 
// How much time I'll put into maintaining this control depends highly
// on the feedback/help/support I get from people using this control.
// People modifiying and improving this component are asked to send me
// the new source-code. 
// Coordination for extending the control would be nice, so we don't
// land up with 20 differnt hex-controls where none is really working.
//
//
// 
// greetings goes to
// - Maarten Hoeben for his great CReportCtrl & legal notices
//-------------------------------------------------------------------------
// dependencies on libraries and frameworks:
//
// Name            | Version | Description
//-----------------+---------+---------------------------------------------
// MFC             | 4.2     | Microsoft Foundation Classes
//-----------------+---------+---------------------------------------------
//                 |         | 
//-----------------+---------+---------------------------------------------
//                 |         | 
//-----------------+---------+---------------------------------------------
//                 |         | 
//-----------------+---------+---------------------------------------------
//
//
///////////////////////////////////////////////////////////////////////////
// history:
//
// date	     | signature | descritpion of modification
//-----------+-----------+-------------------------------------------------
// 11.01.01  | kuendig   | version 0.0.0.1 
//           |           | - first test version
//-----------+-----------+-------------------------------------------------
// 13.01.01  | kuendig   | version 0.0.0.2 
//           |           | - context menue 
//           |           |   use OnExtendContextMenu to extend the 
//           |           |   context menue in a derived class
//           |           | - paste methode
//           |           | - Windows-Class registering
//           |           |   - CHexEditBase: for use with DDX / Edit-Control
//           |           |   - CHexEditBase_SC: when not using DDX
//           |           | - several small changes
//-----------+-----------+-------------------------------------------------
// 19.01.01  | kuendig   | version 0.0.0.3
//           |           | - bug in CreateHighlightingPolygons
//           |           |   (when scrolling highlighting out of window on 
//           |           |   top, sometimes the address got overpainted
//           |           |   by some parts of the highlighting section)
//-----------+-----------+-------------------------------------------------
// 04.02.01  | kuendig   | version 1.0.0.0 (official release)
//           |           | - MakeVisible is now smarter
//           |           | - SetFont, GetFont WM_SETFONT, WM_GETFONT works now
//-----------+-----------+-------------------------------------------------
// 24.05.01  | kuendig   | version 1.1.0.0
//           |           | - Fixed the 16Bit Scrollrange limitation when
//           |           |   thumbtracking (see OnVScroll)
//           |           | - Modified SetFont to only accept fixed-pitched
//           |           |   fonts
//           |           | - Replaced some GetSafeHwnd() with 
//           |           |   ::IsWindow(m_hWnd), since it's rather what's
//           |           |   beeing checked. (Even when GetSafeHwnd worked
//           |           |   in most of the cases)
//           |           | - Call DestroyWnd from the Destructor, to get
//           |           |   rid of the TRACE from "CWnd::~CWnd ..."
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
// --.--.--  |           | 
//-----------+-----------+-------------------------------------------------
///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
#ifndef __hexeditbase_h
#define __hexeditbase_h
#if _MSC_VER > 1000
#pragma once
#endif

#include "..\BaseClass\BaseList.h"

class CHexEditBase;
class CHexEditBlocks;

class CHexEditBlock : public CBaseObject
{
public:
	CHexEditBlock()											{	SetPos(-1, -1);						}
	CHexEditBlock(long nBeginPos, long nEndPos)	{	SetPos(nBeginPos, nEndPos);	}
	virtual ~CHexEditBlock(){};

	void SetPos(long nBeginPos, long nEndPos)
	{
		m_nBeginPos = nBeginPos;
		m_nEndPos = nEndPos;
	}

	BOOL IsInBlock(long nPos)	{	return ( ( m_nBeginPos <= nPos) && (nPos <= m_nEndPos) );	 }
	BOOL IsBlockIntersect(long nBeginPos, long nEndPos)
	{
		CRect rc1(m_nBeginPos, 1, m_nEndPos, 10);
		CRect rc2(nBeginPos, 1, nEndPos, 10);
		CRect rc;
		return rc.IntersectRect(rc1, rc2);
	}

	void AttachHexEdit(CHexEditBase *pHexEdit)	{	m_pRefHexEdit = pHexEdit;	}
	long GetLength()		{		return m_nEndPos - m_nBeginPos + 1;	}

	void Offset(long nPos, long nOffset)
	{	
		if (m_nBeginPos > nPos)
		{
			m_nBeginPos -= nOffset;
			m_nEndPos -= nOffset;
		}
	}

	long GetBeginPos()	{	return m_nBeginPos;	}
	long GetEndPos()	{	return m_nEndPos;		}
	COLORREF GetLineColor()	{	return m_crLineColor;	}
	COLORREF GetBackCoor()	{	return m_crBackCoor;	}

private:
	long m_nBeginPos;
	long m_nEndPos;
	COLORREF m_crLineColor;
	COLORREF m_crBackCoor;

	CHexEditBase *m_pRefHexEdit; 

	friend class CHexEditBlocks;
};

class CHexEditBlocks : public CBaseList
{
public:
	CHexEditBlocks();
	virtual ~CHexEditBlocks();

	CHexEditBlock* AddBlock(long nBeginPos, long nEndPos);
	CHexEditBlock* AddBlockEx(long nBeginPos, long nLen);
	CHexEditBlock* InsertBlock(long nBeginPos, long nEndPos);
	CHexEditBlock* InsertBlockEx(long nBeginPos, long nLen);
	CHexEditBlock* FindBlock(long nPos);
	BOOL IsInBlock(long nPos);
	BOOL IsAreaHasBlock(long nBeginPos, long nEndPos);
	void DeleteBlock(long nPos, BOOL bOffsetOthers);
	void OnDeleteChar(long nPos, long nLen, BOOL bOffsetBlocks);
	void OnInsertChar(long nPos, long nLen, BOOL bOffsetBlocks);

	void AttachHexEdit(CHexEditBase *pHexEdit)	{	m_pRefHexEdit = pHexEdit;	}
	void DeleteAllBloks();

private:
	void OffsetBlocks(long nPos, long nOffset);
	CHexEditBlock* FindPrev(long nPos);
	CHexEditBlock* FindNext(long nPos);
	BOOL AssertPos(long nBeginPos, long nEndPos);
	BOOL IsBlockIntersect(long nBeginPos, long nEndPos);

	CHexEditBlock* NewBlock(long nBeginPos, long nEndPos);

	CHexEditBase *m_pRefHexEdit;
};

/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////
#define NOSECTION_VAL				0xffffffff

// notification codes
#define WM_HEN_CHANGE					(WM_USER+1347)

#define HEX_EDIT_DEFAULT_BUFFER_LEN  65536   //64k
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditBase
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class CHexEditBase : public CWnd
{
public:
	CHexEditBase();
	virtual ~CHexEditBase();

	void SetShowAddress(bool bShow, bool bUpdate = true);
	void SetShowAscii(bool bShow, bool bUpdate = true);
	UINT GetCurrentAddress()	{	return m_nCurrentAddress;	}
	void SetCurrentAddress(UINT nAddr);
	
	void FreeData();
	void SetBufferLength(UINT nBufferLength = HEX_EDIT_DEFAULT_BUFFER_LEN, BOOL bCopySrcData=TRUE);
	void CopyData(const BYTE *pData, UINT nLen, bool bUpdate = true);
	void SetData(const BYTE *pData, UINT nLen, bool bUpdate = true);
	void SetDirectDataPtr(BYTE *pData, UINT nLen, bool bUpdate = true); // won't copy data and won't free memory
	UINT GetData(BYTE *pByte, UINT nLength);
	UINT GetAllDataRef(BYTE **ppByte, UINT &nLength);
	UINT GetDataSize() const { return m_nDataLength; }
	UINT GetBufferLength() const {	return m_nBufferLength;	}
	void InsertData(BYTE *pData, UINT nBegin, UINT nLen);
	void DeleteData(UINT nBegin, UINT nLen);
	
	void SetHighlighted(UINT nBegin, UINT nEnd, bool bMakeVisible = true, bool bUpdate = true);
	bool GetHighlighted(UINT& nBegin, UINT& nEnd) const;
	bool IsHighlighted() const;

	void SetSelection(UINT nBegin, UINT nEnd, bool bMakeVisible = true, bool bUpdate = true);
	bool GetSelection(UINT& nBegin, UINT& nEnd) const;
	bool IsSelection() const;
	
	void MakeVisible(UINT nBegin, UINT nEnd, bool bUpdate=true);
	void SetBytesPerRow(UINT nBytesPerRow, bool bAuto = false, bool bUpdate = true);

	void SetAddressSize(BYTE nAdrSize, bool bUpdate = true);

	void SetAdrColor(COLORREF crAdrBkg, COLORREF crAdrTxt, bool bUpdate = true);
	void SetAsciiColor(COLORREF crAsciiBkg, COLORREF crAsciiTxt, bool bUpdate = true);
	void SetHighlightColor(COLORREF crHighlightFrame, COLORREF crHighlightBkg, COLORREF crHighlightTxt, bool bUpdate = true);
	void SetHexColor(COLORREF crHexBkg, COLORREF crHexTxt, bool bUpdate = true);
	void SetSelectedNoFocusColor(COLORREF crSelectedNoFocusBkg, COLORREF crSelectedNoFocusTxt, bool bUpdate = true);
	void SetSelectedFocusColor(COLORREF crSelectedFousTxt, COLORREF crSelectedFousBkg, bool bUpdate = true);
	void SetNotUsedColor(COLORREF crNotUsedBk, bool bUpdate = true);

	virtual void SetReadonly(bool bReadOnly, bool bUpdate = true);

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);	
	static void RegisterClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

	void SetContextCopyStr(const CString& cStr) { m_cContextCopy = cStr; }
	void SetContextPasteStr(const CString& cStr) { m_cContextPaste = cStr; }

	CHexEditBlocks* GetHexEditBlocks()		{	return &m_oHexEditBlocks;		}

protected:
	CHexEditBlocks m_oHexEditBlocks;

	struct PAINTINGDETAILS 
	{
		UINT nFullVisibleLines;   //完整可见的行数
		UINT nLastLineHeight;  //最后一样的高度
		UINT nVisibleLines;  //可视的行数
		UINT nLineHeight;   //每行的高度
		UINT nCharacterWidth;  //字符宽度
		UINT nBytesPerRow;   //每行的字符数
		UINT nHexPos;   //HEX的位置
		UINT nHexLen;  //HEX的宽度
		UINT nAsciiPos;   //ASCII的起始位置
		UINT nAsciiLen;    //ASCII的宽度
		UINT nAddressPos;  //地址栏的起始位置 == 0
		UINT nAddressLen;  //地址栏的宽度
		CRect cPaintingRect;  //绘图的区域
	};

	BYTE *m_pData;            //缓冲区指针
	UINT m_nDataLength;     //缓冲区数据长度
	UINT m_nBufferLength;   //缓冲区长度，m_nBufferLength总是大于等于m_nDataLength

	bool m_bSelfCleanup;
	bool m_bCanDeleteData;
	PAINTINGDETAILS m_tPaintDetails;
	UINT m_nBytesPerRow;
	UINT m_nAdrSize;
	UINT m_nHighlightedEnd;
	UINT m_nHighlightedBegin;
	UINT m_nSelectionBegin;
	UINT m_nSelectionEnd;
	UINT m_nCurrentAddress;
	UINT m_nCurCaretHeight; 
	UINT m_nScrollPostionY;	
	UINT m_nScrollRangeY;
	UINT m_nScrollPostionX;	
	UINT m_nScrollRangeX;
	UINT m_nCurCaretWidth;
	UINT m_nSelectingBeg;
	UINT m_nSelectingEnd;
	UINT m_nBinDataClipboardFormat;	
	bool m_bRecalc;
	bool m_bHasCaret;
	bool m_bHighBits;
	bool m_bAutoBytesPerRow;
	bool m_bShowAddress;
	bool m_bShowAscii;
	bool m_bAddressIsWide;
	bool m_bShowCategory;
	bool m_bReadOnly;
	COLORREF m_crAdrBkg;
	COLORREF m_crAdrTxt;
	COLORREF m_crAsciiBkg;
	COLORREF m_crAsciiTxt;
	COLORREF m_crHighlightBkg;
	COLORREF m_crHighlightTxt;
	COLORREF m_tHighlightFrameColor;
	COLORREF m_tHexTxtColor;
	COLORREF m_tHexBkgColor;
	COLORREF m_tNotUsedBkColor;
	COLORREF m_tSelectedNoFocusTxtColor;
	COLORREF m_tSelectedNoFocusBkgColor;
	COLORREF m_tSelectedFousTxtColor;
	COLORREF m_tSelectedFousBkgColor;	
	CString m_cContextCopy;
	CString m_cContextPaste;	
	CFont m_cFont;	
	CRect m_cDragRect;
	CPoint m_cMouseRepPoint;
	int m_iMouseRepDelta;
	WORD m_nMouseRepSpeed;
	WORD m_nMouseRepCounter;
	bool m_bIsMouseRepActive;

	// overrideables
	virtual void OnExtendContextMenu(CMenu&) {} // override this to add your own context-menue-items

	void NotifyParent(WORD wNBotifictionCode);
	void CalculatePaintingDetails(CDC& cDC);
	void PaintAddresses(CDC& cDC);
	void PaintHexData(CDC& cDC);
	void PaintHhighlight(CDC& cDC, const CRect cHexRect, BYTE **ppHighlightedPtrBegin, BYTE **ppHighlightedPtrEnd);
	void PaintAsciiData(CDC& cDC);	
	void CreateEditCaret(UINT nCaretHeight, UINT nCaretWidth);
	void DestoyEditCaret();
	void SetEditCaretPos(UINT nOffset, bool bHighBits);
	bool OnEditInput(WORD nInput);
	void MoveCurrentAddress(int iDeltaAdr, bool bHighBits);
	void SetScrollPositionY(UINT nPosition, bool bUpdate=false);
	void SetScrollPositionX(UINT nPosition, bool bUpdate=false);
	void SetScrollbarRanges();
	void MoveScrollPostionY(int iDelta, bool bUpdate=false);
	void MoveScrollPostionX(int iDelta, bool bUpdate=false);
	void StartMouseRepeat(const CPoint& cPoint, int iDelta, WORD nSpeed);
	void StopMouseRepeat();
	void GetAddressFromPoint(const CPoint& cPt, UINT& nAddress, bool& bHighByte);
	UINT CreateBlockPolygons(const CRect& cHexRect, UINT nBegin, UINT nEnd, POINT *pPoints);

	//{{AFX_VIRTUAL(CHexEditBase)
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHexEditBase)
	afx_msg void OnDestroy(); 
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint cPoint);
	afx_msg LRESULT OnWMChar(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnWMSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUmSetScrollRange(WPARAM, LPARAM);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd*);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar*);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar*);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg void OnLButtonDown(UINT, CPoint point);
	afx_msg void OnLButtonDblClk(UINT, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT, CPoint);
	afx_msg void OnKeyDown(UINT nChar, UINT, UINT);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	//}}AFX_MSG
	DECLARE_DYNCREATE(CHexEditBase)
	DECLARE_MESSAGE_MAP()
};

#endif
