#if !defined(_MRGRIDCTRL_H__)
#define _MRGRIDCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GridCtrl.h : header file
//

#include <afxtempl.h>
#include <afxole.h>                     // This is sloppy I know...
#include "GridCellRange.h"
#include "GridCell.h"
#include "GridCtrlMemDC.h"
#include "GridRows.h"
#include "GridColumns.h"

#include "GridDefine.h"
#include "GridCellDataType.h"


#define WM_GRID_END_EDIT (WM_USER+1000)
#define CHECHBOX_EDIT_KEYVALUE   32

/////////////////////////////////////////////////////////////////////////////
// CXGridCtrlBase window

class CGridCanUseKeys
{
public:
#define  MAX_CAN_USE_KEYS 255

	CGridCanUseKeys()
	{
		memset(m_nCanUseKey, 0, MAX_CAN_USE_KEYS*sizeof(BYTE));
		m_nCanUseKeyCount = 0;
	}

	virtual ~CGridCanUseKeys()
	{

	}

private:
	BYTE        m_nCanUseKey[MAX_CAN_USE_KEYS];
	long        m_nCanUseKeyCount;

	BOOL KeyExist(BYTE nKey)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<m_nCanUseKeyCount; nIndex++)
		{
			if (m_nCanUseKey[nIndex] == nKey)
				return TRUE;
		}

		return FALSE;
	}

public:
	void AddKey(BYTE nKey)
	{
		if (!KeyExist(nKey))
		{
			m_nCanUseKey[m_nCanUseKeyCount] = nKey;
			m_nCanUseKeyCount++;
		}
	}
	void Reset()
	{
		m_nCanUseKeyCount = 0;
	}

	BOOL CanUseKey(BYTE nKey)
	{
		if (m_nCanUseKeyCount == 0)
		{
			return TRUE;
		}

		return KeyExist(nKey);
	}
};

class CXGridCtrlBase
{
	friend class CGridRow;
	friend class CGridRows;
	friend class CGridColumn;
	friend class CGridColumns;
	friend class CGridCell;
	friend class CGridCellRange;
	
public:
	CPoint ptGridOrigin;
	void CreateTitleTip();

	// Fill List Content
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	virtual void FillListItems(int nCol, LPARAM cltWnd);
	virtual void FillTreeItems(int nCol, LPARAM cltWnd);
	virtual void FillTimeCtrlItems(int nCol, LPARAM cltWnd);
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);
	virtual GRIDEDIT_FORMAT GetEditFormat(int nRow, int nCol);
	virtual void IsUseKeyMsg(BOOL bUse = TRUE)	{	m_bUseKeyMsg = bUse;	}
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual BOOL OnCellKeyDelete(const CCellID &idCell);
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);

	virtual void ResetScrollBars();
	virtual void  OnDraw(CDC* pDC);

	virtual UINT GetGridClipRect(CDC* pDC, CRect &rcClip);
	virtual void GetGridClientRect(CRect &rcClient);
	virtual void GetGridClientRect(CRect &rcClient) const ;
	virtual CCellID GetTopleftNonFixedCell() const;
	virtual CGridCellRange GetUnobstructedNonFixedCellRange() const;
	virtual CGridCellRange GetVisibleNonFixedCellRange(LPRECT pRect = NULL) const;

private:
	CWnd *m_pInplaceEditWnd;
	BOOL  m_bInplaceEdit_VKReturn;
	DWORD m_dwInplaceEditEndTick;

protected:
	CWnd *m_pGridRefWnd;

// Construction
public:
    CXGridCtrlBase(int nRows = 0, int nCols = 0, int nFixedRows = 0, int nFixedCols = 0);

    BOOL Create(CWnd* pRefWnd, CPoint pt=CPoint(0, 0));
    BOOL SubclassWindow(HWND hWnd);
	void FreeInplaceEditWnd();
	BOOL IsGridCreated()	{	return m_pGridRefWnd != NULL;	}

// Attributes
public:

    int  GetRowCount() const                    { return m_nRows; }
    int  GetColumnCount() const                 { return m_nCols; }
    int  GetFixedRowCount() const               { return m_nFixedRows; }
    int  GetFixedColumnCount() const            { return m_nFixedCols; }
    BOOL SetRowCount(int nRows = 10);
    BOOL SetColumnCount(int nCols = 10);
    BOOL SetFixedRowCount(int nFixedRows = 1);
    BOOL SetFixedColumnCount(int nFixedCols = 1);

    int  GetRowHeight(int nRow) const;
    BOOL SetRowHeight(int row, int height);
    int  GetColumnWidth(int nCol) const;
    BOOL SetColumnWidth(int col, int width);
	int  GetColumnType(int nCol) const;		///添加		2001年8月27日
	BOOL SetColumnType(int nCol, int nType);///添加		2001年8月27日

    BOOL GetCellOrigin(int nRow, int nCol, LPPOINT p) const;
    BOOL GetCellOrigin(const CCellID& cell, LPPOINT p) const;
    BOOL GetCellRect(int nRow, int nCol, LPRECT pRect) const;
    BOOL GetCellRect(const CCellID& cell, LPRECT pRect) const;

    int  GetFixedRowHeight() const;
    int  GetFixedColumnWidth() const;
    long GetVirtualWidth() const;
    long GetVirtualHeight() const;

    void     SetTextColor(COLORREF clr)           { m_crTextColour = clr;             }
    COLORREF GetTextColor() const                 { return m_crTextColour;            }
    void     SetTextBkColor(COLORREF clr)         { m_crTextBkColour = clr;           }
    COLORREF GetTextBkColor() const               { return m_crTextBkColour;          }
    void     SetBkColor(COLORREF clr)             { m_crBkColour = clr;               }
    COLORREF GetBkColor() const                   { return m_crBkColour;              }
    void     SetFixedTextColor(COLORREF clr)      { m_crFixedTextColour = clr;        }
    COLORREF GetFixedTextColor() const            { return m_crFixedTextColour;       }
    void     SetFixedBkColor(COLORREF clr)        { m_crFixedBkColour = clr;          }
    COLORREF GetFixedBkColor() const              { return m_crFixedBkColour;         } 
    void     SetGridColor(COLORREF clr)           { m_crGridColour = clr;             }
    COLORREF GetGridColor() const                 { return m_crGridColour;            }

    int GetSelectedCount() const                  { return m_SelectedCellMap.GetCount(); }


    void SetImageList(CImageList* pList)          { m_pImageList = pList;             }
    CImageList* GetImageList() const              { return m_pImageList;              }

    void SetGridLines(int nWhichLines = GVL_BOTH);
    int  GetGridLines() const                     { return m_nGridLines;              }

    void SetDrawSelCellFrame(BOOL bDrawSelCellFrame = TRUE)       { m_bDrawSelCellFrame = bDrawSelCellFrame;          }
    void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
    BOOL IsEditable() const                       { return m_bEditable;               }
    void SetModified(BOOL bModified = TRUE)       { m_bModified = bModified;          }
    BOOL GetModified() const                      { return m_bModified;               }
    void SetListMode(BOOL bEnableListMode = TRUE) { m_bListMode = bEnableListMode;    }
    BOOL GetListMode() const                      { return m_bListMode;               }
    void EnableSelection(BOOL bEnable = TRUE)     { ResetSelectedRange(); m_bEnableSelection = bEnable; ResetSelectedRange(); }
    BOOL IsSelectable() const                     { return m_bEnableSelection;        }
    void EnableDragAndDrop(BOOL bAllow = TRUE)    { m_bAllowDragAndDrop = bAllow;     }
    BOOL GetDragAndDrop() const                   { return m_bAllowDragAndDrop;       }
    void SetRowResize(BOOL bResize = TRUE)        { m_bAllowRowResize = bResize;      }
    BOOL GetRowResize() const                     { return m_bAllowRowResize;         }
    void SetColumnResize(BOOL bResize = TRUE)     { m_bAllowColumnResize = bResize;   }
    BOOL GetColumnResize() const                  { return m_bAllowColumnResize;      }
    void SetHeaderSort(BOOL bSortOnClick = TRUE)  { m_bSortOnClick = bSortOnClick;    }
    BOOL GetHeaderSort() const                    { return m_bSortOnClick;            }
    void SetHandleTabKey(BOOL bHandleTab = TRUE)  { m_bHandleTabKey = bHandleTab;     }
    BOOL GetHandleTabKey() const                  { return m_bHandleTabKey;           }
    void SetDoubleBuffering(BOOL bBuffer = TRUE)  { m_bDoubleBuffer = bBuffer;        }
    BOOL GetDoubleBuffering() const               { return m_bDoubleBuffer;           }
    void EnableTitleTips(BOOL bEnable = TRUE)     { m_bTitleTips = bEnable;           }
    BOOL GetTitleTips()                           { return m_bTitleTips;              }
	void SetUseVKDelete(BOOL bUseVKDelete = TRUE)  { m_bUseVKDelete = bUseVKDelete;   }
	void SetUseRButtonDownForSel(BOOL b = TRUE)   { m_bUseRButtonDownForSel = b;      }
	


    BOOL   SetItem(const GV_ITEM* pItem);
    BOOL   GetItem(GV_ITEM* pItem);
    BOOL   SetItemText(int nRow, int nCol, LPCTSTR str);
    virtual CString GetItemText(int nRow, int nCol);
	virtual CString* GetItemTextRef(int nRow, int nCol);
	BOOL   SetItemMaxLen(int nRow, int nCol, int iLen);
	virtual int GetItemMaxLen(int nRow, int nCol);
    BOOL   SetItemData(int nRow, int nCol, LPARAM lParam);
    LPARAM GetItemData(int nRow, int nCol) const;
    BOOL   SetItemImage(int nRow, int nCol, int iImage);
    int    GetItemImage(int nRow, int nCol) const;
    BOOL   SetItemState(int nRow, int nCol, UINT state);
    BOOL   SetItemState(CGridCell *pCell, UINT state);
    UINT   GetItemState(int nRow, int nCol) const;
    BOOL   SetItemFormat(int nRow, int nCol, UINT nFormat);
    UINT   GetItemFormat(int nRow, int nCol) const;
	BOOL   SetItemBkColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	COLORREF GetItemBkColour(int nRow, int nCol) const;
	BOOL   SetItemFgColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	COLORREF GetItemFgColour(int nRow, int nCol) const;
	BOOL SetItemFont(int nRow, int nCol, LOGFONT* lf);
	BOOL SetItemFontBold(int nRow, int nCol, BOOL bBold);
	LOGFONT* GetItemFont(int nRow, int nCol) const;
    void GetScrollMax(long &nHScrollMax, long &nVScrollMax);
	void UpdateRowsColsIndex()
	{
		m_RowData.UpdateRowsIndex();
		m_oColumns.UpdateColsIndex();
	}
// Operations
public:
    int  InsertColumn(LPCTSTR strHeading, UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE,
                      int nColumn = -1,int nType = GVET_NOEDIT);
    int  InsertRow(LPCTSTR strHeading, int nRow = -1);
    BOOL DeleteColumn(int nColumn);
    BOOL DeleteRow(int nRow);
    BOOL DeleteNonFixedRows();
    BOOL DeleteAllItems(BOOL bResetScrollBars = TRUE);
	BOOL ChangeRowPosition(long nRow1, long nRow2);

    BOOL AutoSizeRow(int nRow);
    BOOL AutoSizeColumn(int nCol);
    void AutoSizeRows();
    void AutoSizeColumns();
    void AutoSize(BOOL bSizeVert=TRUE, BOOL bSizeHorz=TRUE);
    void ExpandColumnsToFit();
    void ExpandRowsToFit();
    void ExpandToFit();

    CSize GetTextExtent(LPCTSTR str, BOOL bUseSelectedFont = TRUE);
    void EnsureVisible(CCellID &cell)       { EnsureVisible(cell.row, cell.col); }
    void EnsureVisible(int nRow, int nCol);
	void SetTopRow(int nRow);
	int  GetTopRow();
    BOOL IsCellVisible(int nRow, int nCol) const;
    BOOL IsCellVisible(CCellID cell) const;
    BOOL IsCellRangeVisible(const CGridCellRange &oCellRange) const;
    BOOL IsCellEditable(int nRow, int nCol) const;
    BOOL IsCellEditable(CCellID &cell) const;

    // SetRedraw stops/starts redraws on things like changing the # rows/columns
    // and autosizing, but not for user-intervention such as resizes
    void SetRedraw(BOOL bAllowDraw, BOOL bResetScrollBars = FALSE);
    BOOL RedrawCell(int nRow, int nCol, CDC* pDC = NULL);
    BOOL RedrawCell(const CCellID& cell, CDC* pDC = NULL);
    BOOL RedrawRow(int row);
    BOOL RedrawColumn(int col);

    void Print(); 
    BOOL Save(LPCTSTR filename);
    BOOL Load(LPCTSTR filename);

    CGridCellRange GetCellRange() const;
    CGridCellRange GetSelectedCellRange() const;
    void SetSelectedRange(const CGridCellRange& Range, BOOL bForceRepaint = FALSE);
    virtual void SetSelectedRange(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                          BOOL bForceRepaint = FALSE);
    BOOL IsValid(int nRow, int nCol) const;
    BOOL IsValid(const CCellID& cell) const;
    BOOL IsValid(const CGridCellRange& range) const;

    // Clipboard and cut n' paste operations
    virtual void CutSelectedText();
    virtual COleDataSource* CopyTextFromGrid();
    virtual BOOL PasteTextToGrid(CCellID cell, COleDataObject* pDataObject);

    void OnBeginDrag();
    DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    void OnDragLeave();
    BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);


    CCellID GetNextItem(CCellID& cell, int nFlags) const;

    BOOL SortTextItems(int nCol, BOOL bAscending);
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data = 0);

	//merge
    CGridCellRange GetCellRange();
    CGridCellRange GetSelectedCellRange();
	void Merge(const CGridCellRange &oRange);
	void Merge(long nRowMin, long nColMin, long nRowMax, long nColMax);
	CGridRows* GetRows()               {    return &m_RowData;        }
	CGridColumns* GetColumns()         {    return &m_oColumns;       }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CXGridCtrlBase)
    protected:
    //}}AFX_VIRTUAL
    public:
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

// Implementation
public:
    virtual ~CXGridCtrlBase();

public:
	CCellID SetFocusCell(CCellID cell);
    CCellID SetFocusCell(int nRow, int nCol);
	CCellID GetFocusCell() const                  { return m_idCurrentCell;           }
	CCellID GetFocusCell()                        { return m_idCurrentCell;           }
	void GetFocusCell(int &nRow, int &nCol)       { nRow = m_idCurrentCell.row;   
	nCol = m_idCurrentCell.col;        }
    CCellID GetFocusCell(CGridCell **pCell) const { *pCell = GetCell(m_idCurrentCell.row, m_idCurrentCell.col);   return m_idCurrentCell;        }
	virtual void SelectRow(int nRow)  
	{  
		m_SelectionStartCell.row = nRow; 
		m_idCurrentCell.row = nRow;
		m_idCurrentCell.col = m_nFixedCols;
		SelectRows(CCellID(nRow, 0));   
	};

	virtual void ClearSelect();
	virtual BOOL KillFocusCell();
	
	void KillFoucusEditWnd();
	void ResetSelectedRange();

protected:
   // BOOL RegisterWindowClass();
	BOOL RegisterWindowClass(HINSTANCE hInstance=NULL);
    LRESULT SendMessageToParent(int nRow, int nCol, int nMessage);

    BOOL InvalidateCellRect(const CCellID& cell);
    BOOL InvalidateCellRect(const CGridCellRange& cellRange);
    void EraseBkgnd(CDC* pDC);

    BOOL GetCellRangeRect(const CGridCellRange& cellRange, LPRECT lpRect) const;

    CGridCell* GetCell(int nRow, int nCol) const;
    BOOL SetCell(int nRow, int nCol, CGridCell* pCell);

    int  SetMouseMode(int nMode) { int nOldMode = m_MouseMode; m_MouseMode = nMode; return nOldMode; }
    int  GetMouseMode() const    { return m_MouseMode; }

    CCellID GetCellFromPt(CPoint point, BOOL bAllowFixedCellCheck = TRUE) const;


    int  GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
    BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);

    BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data, 
                   int low, int high);

	void AdjustCellDrawRect(int nRow, int nCol, CRect &rect);
// Overrrides
protected:
    // Printing    
    virtual void PrintColumnHeadings(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintFooter(CDC *pDC, CPrintInfo *pInfo);

    // Drag n' drop
    virtual CImageList* CreateDragImage(CPoint *pHotSpot);    // no longer necessary

    // Mouse Clicks
    virtual void  OnFixedColumnClick(CCellID& cell);
    virtual void  OnFixedRowClick(CCellID& cell);

    // Editing
    virtual CSize GetCellExtent(int nRow, int nCol, CDC* pDC);
    virtual void  OnEndEditCell(int nRow, int nCol, CString str, DWORD dwValue=0, DWORD dwItemData=0);
    virtual void  OnEndEditCell(int nRow, int nCol, DWORD dwValue=0, DWORD dwItemData=0);
    virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void  OnEditCellRBDblClk(int nRow, int nCol, UINT nChar);
//    virtual void  CreateInPlaceEditControl(CRect& rect, DWORD dwStyle, UINT nID,
//                                           int nRow, int nCol,
//                                           LPCTSTR szText, int nChar);

    // Drawing
	virtual BOOL DrawCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	virtual BOOL DrawFixedCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	

    // GridCell Creation and Cleanup
    virtual CGridCell* CreateCell(int nRow, int nCol);
    virtual void EmptyCell(CGridCell* pCell, int nRow, int nCol);

// Attributes
protected:
    // General attributes
    COLORREF    m_crTextColour, m_crTextBkColour, m_crBkColour,   // Grid colours
                m_crFixedTextColour, m_crFixedBkColour, m_crGridColour;
    COLORREF    m_crWindowText, m_crWindowColour, m_cr3DFace,     // System colours
                m_crShadow;    

    int         m_nGridLines;
    BOOL        m_bEditable;
    BOOL        m_bModified;
    BOOL        m_bAllowDragAndDrop;
    BOOL        m_bListMode;
    BOOL        m_bAllowDraw;
    BOOL        m_bEnableSelection;
    BOOL        m_bSortOnClick;
    BOOL        m_bHandleTabKey;
    BOOL        m_bDoubleBuffer;
    BOOL        m_bTitleTips;
	BOOL        m_bUseRButtonDownForSel;

    // Cell size details
    int         m_nRows, m_nFixedRows, m_nCols, m_nFixedCols;
    int         m_nMargin;
    int         m_nDefCellWidth, m_nDefCellHeight;
    int         m_nVScrollMax, m_nHScrollMax;

    // Fonts and images
    LOGFONT     m_Logfont;
    CFont       m_PrinterFont,  // for the printer
                m_Font;         // for the grid
    CImageList* m_pImageList;

    // Cell data
	CGridRows m_RowData;
	CGridColumns m_oColumns;

    // Mouse operations such as cell selection
    int         m_MouseMode;
    CPoint      m_LeftClickDownPoint, m_LastMousePoint;
    CCellID     m_LeftClickDownCell, m_SelectionStartCell;
    CCellID     m_idCurrentCell;
    int         m_nTimerID;
    int         m_nTimerInterval;
    int         m_nResizeCaptureRange;
    BOOL        m_bAllowRowResize, m_bAllowColumnResize;
    int         m_nRowsPerWheelNotch;
    CMap<DWORD,DWORD, CCellID, CCellID&> m_SelectedCellMap, m_PrevSelectedCellMap;

    // Drag and drop
	BOOL		m_bMustUninitOLE;		// Do we need to uninitialise OLE?
    CCellID     m_LastDragOverCell;

    // Printing information
    CSize       m_CharSize;
    int         m_nPageHeight;
    CSize       m_LogicalPageSize,      // Page size in gridctrl units.
                m_PaperSize;            // Page size in device units.

    // sorting
    int         m_bAscending;
    int         m_SortColumn;

	BOOL		m_bDrawSelCellFrame;	//lijunqing 2005.10.26
	BOOL        m_bUseVKDelete;

	BOOL		m_bUseKeyMsg;			//是否使用按键消息
	CPoint      m_posTopLeft;           //表格的位置

	CGridCanUseKeys m_oKeysMngr;

public:
	void AddKey(BYTE nKey)
	{
		m_oKeysMngr.AddKey(nKey);
	}

	virtual void AfterOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)	{};
	virtual void AfterOnMouseWheel(UINT nFlags, short zDelta, CPoint pt)			{};

public:
    void SelectAllCells();
    void SelectColumns(CCellID currentCell);
    void SelectRows(CCellID currentCell);
    void SelectCells(CCellID currentCell);
    void OnSelecting(const CCellID& currentCell);
	BOOL GetUpCell(CCellID &next);
	BOOL GetDownCell(CCellID &next);
	BOOL GetNextCell(CCellID &next, BOOL &bChangeLine);
	BOOL GetPrevCell(CCellID &next, BOOL &bChangeLine);
	BOOL GetLeftCell(CCellID &next);
	BOOL GetRightCell(CCellID &next);
	BOOL AdjustCell(const CCellID &oCurr, CCellID &next, BOOL &bTrue);

    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg UINT OnGetDlgCode();
    afx_msg BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSysColorChange();
    afx_msg void OnCaptureChanged(CWnd *pWnd);
// 	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
// 	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
// 	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	void DrawGridLines(CDC *pDC);
#if _MFC_VER >= 0x0421
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif
    afx_msg LRESULT OnSetFont(WPARAM hFont, LPARAM lParam);
    afx_msg LRESULT OnGetFont(WPARAM hFont, LPARAM lParam);
    afx_msg void OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult);	//2001.09.08	李俊庆
    afx_msg void OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult);	//2001.09.08	李俊庆

	afx_msg LRESULT OnFillComboBox(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillList(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillTree(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox);

    enum eMouseModes { MOUSE_NOTHING, MOUSE_SELECT_ALL, MOUSE_SELECT_COL, MOUSE_SELECT_ROW,
                       MOUSE_SELECT_CELLS, MOUSE_SCROLLING_CELLS,
                       MOUSE_OVER_ROW_DIVIDE, MOUSE_SIZING_ROW, 
                       MOUSE_OVER_COL_DIVIDE, MOUSE_SIZING_COL,
                       MOUSE_PREPARE_EDIT, MOUSE_PREPARE_DRAG, MOUSE_DRAGGING};

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

inline CGridCell* CXGridCtrlBase::GetCell(int nRow, int nCol) const
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) return NULL;

    CGridRow* pRow = m_RowData[nRow];
	
    if (pRow == NULL)
	{
		return NULL;
	}

    return pRow->GetAt(nCol);
}

inline BOOL CXGridCtrlBase::SetCell(int nRow, int nCol, CGridCell* pCell)
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols)
	{
		return FALSE;
	}

	BOOL bTrue = TRUE;

    CGridRow* pRow = m_RowData[nRow];

    if (pRow != NULL)
	{
		pRow->SetAt(nCol, pCell);
	}
	else
	{
		bTrue = FALSE;
	}

    CGridColumn* pColumn = m_oColumns[nCol];
	
    if (pColumn != NULL)
	{
		pColumn->SetAt(nRow, pCell);
	}
	else
	{
		bTrue = FALSE;
	}
	
    return bTrue;
}

/////////////////////////////////////////////////////////////////////////////


class CGridCtrl : public CWnd, public CXGridCtrlBase
{
// Construction
public:
	CGridCtrl(int nRows = 0, int nCols = 0, int nFixedRows = 0, int nFixedCols = 0);
	DECLARE_DYNCREATE(CGridCtrl)

	BOOL Create(const RECT& rect, CWnd* parent, UINT nID 
		, DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	BOOL SubclassWindow(HWND hWnd);

public:
	virtual UINT GetGridClipRect(CDC* pDC, CRect &rcClip);
	virtual void GetGridClientRect(CRect &rcClient);
	virtual void GetGridClientRect(CRect &rcClient) const;
	virtual CCellID GetTopleftNonFixedCell() const;
	virtual CGridCellRange GetUnobstructedNonFixedCellRange() const;
	virtual CGridCellRange GetVisibleNonFixedCellRange(LPRECT pRect = NULL) const;
	virtual void ResetScrollBars();

// Attributes
public:

// Operations
public:

public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
public:

	// Implementation
public:
	virtual ~CGridCtrl();

public:
	virtual void OnEditCut();
	virtual void OnEditCopy();
	virtual void OnEditPaste();
	virtual void OnEditSelectAll();

protected:

	// Overrrides
protected:

public:

protected:
	// Generated message map functions
	//{{AFX_MSG(CGridCtrl)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSysColorChange();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

#if _MFC_VER >= 0x0421
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif
	afx_msg LRESULT OnSetFont(WPARAM hFont, LPARAM lParam);
	afx_msg LRESULT OnGetFont(WPARAM hFont, LPARAM lParam);
	afx_msg void OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndPointEdit(NMHDR* pNMHDR, LRESULT* pResult);	//2001.09.08	李俊庆
	afx_msg void OnEndInplaceComboBoxEdit(NMHDR* pNMHDR, LRESULT* pResult);	//2001.09.08	李俊庆

	afx_msg LRESULT OnFillComboBox(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillList(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillTree(WPARAM nColumn, LPARAM pListBox);
	afx_msg LRESULT OnFillTimeCtrl(WPARAM nColumn, LPARAM pListBox);


	DECLARE_MESSAGE_MAP()

public:
	//{{AFX_VIRTUAL(CTestDlgDlg)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_MRGRIDCTRL_H__)
