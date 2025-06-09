#pragma once
#include "pfx\pfxeditctrl.h"
#include "SclTextCCDoc.h"
#include "DlgBase.h"

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCView 视图
class CSclTextCCDoc;
class CSclTextCCView : public CPfxEditView
{
	DECLARE_DYNCREATE(CSclTextCCView)

protected:
	CSclTextCCView();           // 动态创建所使用的受保护的构造函数
	virtual        ~CSclTextCCView();
public:
	LRESULT UpdateTreeView( WPARAM wParam, LPARAM lParam);
        CSclTextCCDoc*    GetDocument() const;

		CExBaseList m_oTreeLists;

		CDlgBase *m_pDlgFind;
		CDlgBase *m_pDlgReplace;

		void SetCStringValue(CString strTextValue);

protected:
        void           OnCmdFileReload();

        void           OnCmdEditUndo();
        void           OnCmdEditRedo();
        void           OnCmdEditPaste();
        void           OnCmdEditCopy();
        void           OnCmdEditCopyAppend();
        void           OnCmdEditCut();
        void           OnCmdEditCutAppend();
        void           OnCmdEditClear();
        void           OnCmdEditClearToStartOfLine();
        void           OnCmdEditClearToStartOfDoc();
        void           OnCmdEditClearToEndOfLine();
        void           OnCmdEditClearToEndOfDoc();
        void           OnCmdEditSelectAll();
        void           OnCmdEditSelectToStartOfLine();
        void           OnCmdEditSelectToStartOfDoc();
        void           OnCmdEditSelectToEndOfLine();
        void           OnCmdEditSelectToEndOfDoc();
        void           OnCmdEditColumnSelect();
        void           OnCmdEditColumnPasteAlign();
        void           OnCmdEditColumnPasteAppend();
        void           OnCmdEditSpacesToTabs();
        void           OnCmdEditSpacesToTabsLeading();
        void           OnCmdEditTabsToSpaces();
        void           OnCmdEditTrimTrailingSpaces();
        void           OnCmdEditCaseLower();
        void           OnCmdEditCaseUpper();
        void           OnCmdEditCaseCapitalize();
        void           OnCmdEditCaseInvert();
        void           OnCmdEditMatchBrace();
        void           OnCmdEditSetWordWrap();
        void           OnCmdEditSetReadOnly();

        void           OnCmdViewRuler();
        void           OnCmdViewLineNumber();
        void           OnCmdViewLineBreak();
        void           OnCmdViewWhitespace();

        void           OnCmdSearchFind();
        void           OnCmdSearchReplace();
        void           OnCmdSearchToggleBookmark();


protected:
        virtual BOOL   PreCreateWindow(CREATESTRUCT& cs);

protected:
	DECLARE_MESSAGE_MAP()
        afx_msg void   OnUpdateGroupEdit(CCmdUI* pCmdUI);
        afx_msg void   OnUpdateGroupSearch(CCmdUI* pCmdUI);
        afx_msg void   OnUpdateGroupView(CCmdUI* pCmdUI);
        afx_msg void   OnGroupFile();
        afx_msg void   OnGroupEdit();
        afx_msg void   OnGroupView();
        afx_msg void   OnGroupSearch();
        afx_msg void   OnContextMenu(CWnd* pWnd, CPoint point);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnClose();
};

/////////////////////////////////////////////////////////////////////////////
inline void            CSclTextCCView::OnCmdEditUndo()                   { EditUndo(); }
inline void            CSclTextCCView::OnCmdEditRedo()                   { EditRedo(); }
inline void            CSclTextCCView::OnCmdEditCopy()                   { EditCopy(false); }
inline void            CSclTextCCView::OnCmdEditCopyAppend()             { EditCopy(true); }
inline void            CSclTextCCView::OnCmdEditCut()                    { EditCut(false); }
inline void            CSclTextCCView::OnCmdEditCutAppend()              { EditCut(true); }
inline void            CSclTextCCView::OnCmdEditPaste()                  { EditPaste(-1, -1); }
inline void            CSclTextCCView::OnCmdEditClear()                  { EditRemove(-1, 0, -1, 0); }
inline void            CSclTextCCView::OnCmdEditClearToStartOfLine()     { CPoint pt = GetCurrentPosition(); EditRemove(pt.y, pt.x, pt.y, 0); }
inline void            CSclTextCCView::OnCmdEditClearToStartOfDoc()      { CPoint pt = GetCurrentPosition(); EditRemove(pt.y, pt.x, 0, 0); }
inline void            CSclTextCCView::OnCmdEditClearToEndOfLine()       { CPoint pt = GetCurrentPosition(); EditRemove(pt.y, pt.x, pt.y, GetLineLength(pt.y)); }
inline void            CSclTextCCView::OnCmdEditClearToEndOfDoc()        { CPoint pt = GetCurrentPosition(); EditRemove(pt.y, pt.x, GetLineUpperBound(), GetLineLength(GetLineUpperBound())); }
inline void            CSclTextCCView::OnCmdEditSelectAll()              { EditSelect(0, 0, -1, 0); }
inline void            CSclTextCCView::OnCmdEditSelectToStartOfLine()    { CPoint pt = GetCurrentPosition(); EditSelect(pt.y, pt.x, pt.y, 0); }
inline void            CSclTextCCView::OnCmdEditSelectToStartOfDoc()     { CPoint pt = GetCurrentPosition(); EditSelect(pt.y, pt.x, 0, 0); }
inline void            CSclTextCCView::OnCmdEditSelectToEndOfLine()      { CPoint pt = GetCurrentPosition(); EditSelect(pt.y, pt.x, pt.y, GetLineLength(pt.y)); }
inline void            CSclTextCCView::OnCmdEditSelectToEndOfDoc()       { CPoint pt = GetCurrentPosition(); EditSelect(pt.y, pt.x, GetLineUpperBound(), GetLineLength(GetLineUpperBound())); }
inline void            CSclTextCCView::OnCmdEditColumnSelect()           { SetColumnSelect(); }
inline void            CSclTextCCView::OnCmdEditColumnPasteAlign()       { EditPaste(-1, -1, PFX_EC_PASTE_COLUMN_ALIGN); }
inline void            CSclTextCCView::OnCmdEditColumnPasteAppend()      { EditPaste(-1, -1, PFX_EC_PASTE_COLUMN_APPEND); }
inline void            CSclTextCCView::OnCmdEditSpacesToTabs()           { EditSpacesToTabs(false); }
inline void            CSclTextCCView::OnCmdEditSpacesToTabsLeading()    { EditSpacesToTabs(true); }
inline void            CSclTextCCView::OnCmdEditTabsToSpaces()           { EditTabsToSpaces(); }
inline void            CSclTextCCView::OnCmdEditTrimTrailingSpaces()     { EditTrimTrailingSpaces(); }
inline void            CSclTextCCView::OnCmdEditCaseLower()              { EditCaseChange(true); }
inline void            CSclTextCCView::OnCmdEditCaseUpper()              { EditCaseChange(false); }
inline void            CSclTextCCView::OnCmdEditCaseCapitalize()         { EditCaseCapitalize(); }
inline void            CSclTextCCView::OnCmdEditCaseInvert()             { EditCaseInvert(); }
inline void            CSclTextCCView::OnCmdEditMatchBrace()             { if (!EditMatchBrace()) { ::MessageBeep(MB_OK); }}
inline void            CSclTextCCView::OnCmdEditSetReadOnly()            { SetReadOnly(!IsReadOnly()); }

inline void            CSclTextCCView::OnCmdViewRuler()                  { SetViewRuler(!IsDrawRuler()); }
inline void            CSclTextCCView::OnCmdViewLineNumber()             { SetViewLineNumber(!IsDrawLineNumber()); }
inline void            CSclTextCCView::OnCmdViewLineBreak()              { SetViewLineBreak(false); }
inline void            CSclTextCCView::OnCmdViewWhitespace()             { SetViewWhitespace(!IsDrawWhitespace()); }

inline void            CSclTextCCView::OnCmdSearchToggleBookmark()       { BookmarkToggle(!IsDrawBookmark()); }

/////////////////////////////////////////////////////////////////////////////
//inline void            CSclTextCCView::SetPrintInfo(const CMyEditPrintInfo* pPrintInfo) { ASSERT(pPrintInfo != NULL); m_pPrintInfo = const_cast<CMyEditPrintInfo*>(pPrintInfo); }
inline CSclTextCCDoc*     CSclTextCCView::GetDocument() const               { return static_cast<CSclTextCCDoc*>(m_pDocument); }
/////////////////////////////////////////////////////////////////////////////
