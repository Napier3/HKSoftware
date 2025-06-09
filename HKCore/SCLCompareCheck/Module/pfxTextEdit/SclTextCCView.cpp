// TextEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "..\..\SclFileTest\MainFrm.h"
#include "AppGlobals.h"
#include "DlgFind.h"
#include "DlgReplace.h"
#include "SclTextCCView.h"


/////////////////////////////////////////////////////////////////////////////
// CSclTextCCView
IMPLEMENT_DYNCREATE(CSclTextCCView, CPfxEditView)
BEGIN_MESSAGE_MAP(CSclTextCCView, CPfxEditView)

	ON_MESSAGE(WM_SCLIECCFGCTRLS_SELECTED, UpdateTreeView)

        ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO,                     OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_REDO,                     OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_COPY,                     OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_COPY_APPEND,              OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CUT,                      OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CUT_APPEND,               OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE,                    OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR,                    OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_TO_START_OF_LINE,   OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_TO_END_OF_LINE,     OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_TO_START_OF_DOC,    OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_TO_END_OF_DOC,      OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL,               OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_TO_START_OF_LINE,  OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_TO_END_OF_LINE,    OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_TO_START_OF_DOC,   OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_TO_END_OF_DOC,     OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_COLUMN_SELECT,            OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_COLUMN_PASTE_ALIGN,       OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_COLUMN_PASTE_APPEND,      OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CASE_LOWER,               OnUpdateGroupEdit)
        ON_UPDATE_COMMAND_UI(ID_EDIT_CASE_UPPER,               OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_CASE_CAPITALIZE,          OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_CASE_INVERT,              OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_SPACES_TO_TABS,           OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_SPACES_TO_TABS_LEADING,   OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_TABS_TO_SPACES,           OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_TRIM_TRAILING_SPACES,     OnUpdateGroupEdit) 
        ON_UPDATE_COMMAND_UI(ID_EDIT_MATCH_BRACE,              OnUpdateGroupEdit)

        ON_UPDATE_COMMAND_UI(ID_EDIT_SET_READ_ONLY,            OnUpdateGroupEdit)

        ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND,                   OnUpdateGroupSearch)
	    ON_UPDATE_COMMAND_UI(ID_SEARCH_RP,                OnUpdateGroupSearch)
        ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND_NEXT,              OnUpdateGroupSearch)
	    ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND_PREV,              OnUpdateGroupSearch)

        ON_COMMAND(ID_FILE_RELOAD,                             OnGroupFile)

        ON_COMMAND(ID_EDIT_UNDO,                               OnGroupEdit)
        ON_COMMAND(ID_EDIT_REDO,                               OnGroupEdit)
        ON_COMMAND(ID_EDIT_COPY,                               OnGroupEdit)
        ON_COMMAND(ID_EDIT_COPY_APPEND,                        OnGroupEdit)
        ON_COMMAND(ID_EDIT_CUT,                                OnGroupEdit)
        ON_COMMAND(ID_EDIT_CUT_APPEND,                         OnGroupEdit)
        ON_COMMAND(ID_EDIT_PASTE,                              OnGroupEdit)
        ON_COMMAND(ID_EDIT_CLEAR,                              OnGroupEdit)
        ON_COMMAND(ID_EDIT_CLEAR_TO_START_OF_LINE,             OnGroupEdit)
        ON_COMMAND(ID_EDIT_CLEAR_TO_END_OF_LINE,               OnGroupEdit)
        ON_COMMAND(ID_EDIT_CLEAR_TO_START_OF_DOC,              OnGroupEdit)
        ON_COMMAND(ID_EDIT_CLEAR_TO_END_OF_DOC,                OnGroupEdit)
        ON_COMMAND(ID_EDIT_SELECT_ALL,                         OnGroupEdit)
        ON_COMMAND(ID_EDIT_SELECT_TO_START_OF_LINE,            OnGroupEdit)
        ON_COMMAND(ID_EDIT_SELECT_TO_END_OF_LINE,              OnGroupEdit)
        ON_COMMAND(ID_EDIT_SELECT_TO_START_OF_DOC,             OnGroupEdit)
        ON_COMMAND(ID_EDIT_SELECT_TO_END_OF_DOC,               OnGroupEdit)
        ON_COMMAND(ID_EDIT_COLUMN_SELECT,                      OnGroupEdit)
        ON_COMMAND(ID_EDIT_COLUMN_PASTE_ALIGN,                 OnGroupEdit)
        ON_COMMAND(ID_EDIT_COLUMN_PASTE_APPEND,                OnGroupEdit)
        
        ON_COMMAND(ID_EDIT_CASE_LOWER,                         OnGroupEdit)
        ON_COMMAND(ID_EDIT_CASE_UPPER,                         OnGroupEdit) 
        ON_COMMAND(ID_EDIT_CASE_CAPITALIZE,                    OnGroupEdit) 
        ON_COMMAND(ID_EDIT_CASE_INVERT,                        OnGroupEdit) 

        ON_COMMAND(ID_EDIT_SPACES_TO_TABS,                     OnGroupEdit) 
        ON_COMMAND(ID_EDIT_SPACES_TO_TABS_LEADING,             OnGroupEdit) 
        ON_COMMAND(ID_EDIT_TABS_TO_SPACES,                     OnGroupEdit) 
        ON_COMMAND(ID_EDIT_TRIM_TRAILING_SPACES,               OnGroupEdit)
	ON_COMMAND(ID_EDIT_MATCH_BRACE,                        OnGroupEdit)

        ON_COMMAND(ID_EDIT_SET_READ_ONLY,                      OnGroupEdit)

	ON_COMMAND(ID_SEARCH_FIND,                             OnGroupSearch)
	ON_COMMAND(ID_SEARCH_RP,                          OnGroupSearch)
	ON_COMMAND(ID_SEARCH_FIND_NEXT,                        OnGroupSearch)
	ON_COMMAND(ID_SEARCH_FIND_PREV,                        OnGroupSearch)


        ON_WM_CONTEXTMENU()
		ON_WM_CLOSE()
END_MESSAGE_MAP()

CSclTextCCView::CSclTextCCView()
{
	m_pDlgFind = NULL;
	m_pDlgReplace = NULL;
}

CSclTextCCView::~CSclTextCCView()
{
	if (m_pDlgFind != NULL)
	{
		delete m_pDlgFind;
		m_pDlgFind = NULL;
	}
	if (m_pDlgReplace != NULL)
	{
		delete m_pDlgReplace;
		m_pDlgReplace = NULL;
	}
}

BOOL CSclTextCCView::PreCreateWindow(CREATESTRUCT& cs)
{
        // TODO: 在此添加专用代码和/或调用基类
        // 由于垂直滚动条由CSplitterWnd提供，所以我们只需要水平滚动条。
        BOOL bResult = CPfxEditView::PreCreateWindow(cs);
        if (bResult)
        {
                cs.style &= ~WS_VSCROLL;
                cs.style &= ~WS_HSCROLL;
        }

        return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCView 消息处理程序
void CSclTextCCView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
        UNUSED(pWnd);
        // TODO: Add your message handler code here

        CMenu Menu;
        if (Menu.LoadMenu(IDR_MENU_TEXTDETAIL))
        {
                GetAppFrame()->CreateShortcutMenu(GetAppFrame(),
                        Menu.GetSubMenu(0),
                        point);
        }
}

/////////////////////////////////////////////////////////////////////////////
// 文件...

void CSclTextCCView::OnGroupFile()
{
        switch (GetAppFrame()->GetCurrentCommand())
        {
        
        
        case ID_FILE_RELOAD:
                OnCmdFileReload();
                break;
        
        default:
                ASSERT(false);
                break;
        }
}

void CSclTextCCView::OnCmdFileReload()
{
        CSclTextCCDoc* pDoc = GetDocument();
        if (!pDoc->IsCanReload())
        {
                return;
        }

        if (appAlert2(IDS_P_QUERY_RELOAD_FILE,
                MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON2,
                pDoc->GetPathName()) == IDOK)
        {
                pDoc->Reload();
        }
}

/////////////////////////////////////////////////////////////////////////////
// OnEdit...
void CSclTextCCView::OnUpdateGroupEdit(CCmdUI* pCmdUI)
{
        int  nCheck = UI_UNCHECK;
        BOOL bOn;
        BOOL bReadOnly = IsReadOnly();
        BOOL bNotEmpty = (GetDocSize() > 0);

        switch (pCmdUI->m_nID)
        {
        case ID_EDIT_UNDO:
                bOn = IsCanUndo();
                break;
 
        case ID_EDIT_REDO:
                bOn = IsCanRedo();
                break;
        
        case ID_EDIT_COPY:
        case ID_EDIT_COPY_APPEND:
                bOn = IsCanCopy();
                break;

        case ID_EDIT_CUT:
        case ID_EDIT_CUT_APPEND:
                bOn = IsCanCut();
                break;
        
        case ID_EDIT_PASTE:
                bOn = IsCanPaste();
                break;

        // 没有内容就无从操作。
        case ID_EDIT_CLEAR:
        case ID_EDIT_CLEAR_TO_START_OF_LINE:
        case ID_EDIT_CLEAR_TO_END_OF_LINE:
        case ID_EDIT_CLEAR_TO_START_OF_DOC:
        case ID_EDIT_CLEAR_TO_END_OF_DOC:
                bOn = IsCanDelete();
                break;
        
        case ID_EDIT_SELECT_TO_START_OF_LINE:
        case ID_EDIT_SELECT_TO_END_OF_LINE:
        case ID_EDIT_SELECT_TO_START_OF_DOC:
        case ID_EDIT_SELECT_TO_END_OF_DOC:
        case ID_EDIT_SELECT_ALL:
                bOn = bNotEmpty;
                break;
        
        case ID_EDIT_CASE_LOWER:
        case ID_EDIT_CASE_UPPER:
        case ID_EDIT_CASE_CAPITALIZE:
        case ID_EDIT_CASE_INVERT:

        case ID_EDIT_SPACES_TO_TABS:
        case ID_EDIT_TABS_TO_SPACES:
        case ID_EDIT_SPACES_TO_TABS_LEADING:
        case ID_EDIT_TRIM_TRAILING_SPACES:
                bOn = bNotEmpty && !bReadOnly;
                break;

        case ID_EDIT_COLUMN_SELECT:
                bOn = IsCanColumnSelect();
                break;

        case ID_EDIT_COLUMN_PASTE_ALIGN:
        case ID_EDIT_COLUMN_PASTE_APPEND:
                bOn = IsCanColumnPaste();
                break;

        case ID_EDIT_MATCH_BRACE:
                bOn = bNotEmpty; // will be change...
                break;


        case ID_EDIT_SET_READ_ONLY:
                bOn = true;
                nCheck = (IsReadOnly() ? UI_CHECK : UI_UNCHECK);
                pCmdUI->SetCheck(nCheck);
                break;

        default:
                bOn = false;
                break;
        }
        pCmdUI->Enable(bOn);
}

void CSclTextCCView::OnGroupEdit()
{
        ASSERT_VALID(this);
        CMainFrame* pAppFrame = GetAppFrame();

        switch (pAppFrame->GetCurrentCommand())
        {
        case ID_EDIT_UNDO:
                OnCmdEditUndo();
                break;
        
        case ID_EDIT_REDO:
                OnCmdEditRedo();
                break;
        
        case ID_EDIT_COPY:
                OnCmdEditCopy();
                break;
        
        case ID_EDIT_COPY_APPEND:
                OnCmdEditCopyAppend();
                break;
        
        case ID_EDIT_CUT:
                OnCmdEditCut();
                break;
        
        case ID_EDIT_CUT_APPEND:
                OnCmdEditCutAppend();
                break;
        
        case ID_EDIT_PASTE:
                OnCmdEditPaste();
                break;

        case ID_EDIT_CLEAR:
                OnCmdEditClear();
                break;
        
        case ID_EDIT_CLEAR_TO_START_OF_LINE:
                OnCmdEditClearToStartOfLine();
                break;
        
        case ID_EDIT_CLEAR_TO_START_OF_DOC:
                OnCmdEditClearToStartOfDoc();
                break;
        
        case ID_EDIT_CLEAR_TO_END_OF_LINE:
                OnCmdEditClearToEndOfLine();
                break;

        case ID_EDIT_CLEAR_TO_END_OF_DOC:
                OnCmdEditClearToEndOfDoc();
                break;
    
        case ID_EDIT_SELECT_ALL:
                OnCmdEditSelectAll();
                break;

        case ID_EDIT_SELECT_TO_START_OF_LINE:
                OnCmdEditSelectToStartOfLine();
                break;
        
        case ID_EDIT_SELECT_TO_START_OF_DOC:
                OnCmdEditSelectToStartOfDoc();
                break;
        
        case ID_EDIT_SELECT_TO_END_OF_LINE:
                OnCmdEditSelectToEndOfLine();
                break;

        case ID_EDIT_SELECT_TO_END_OF_DOC:
                OnCmdEditSelectToEndOfDoc();
                break;

        case ID_EDIT_COLUMN_SELECT:
                OnCmdEditColumnSelect();
                break;

        case ID_EDIT_COLUMN_PASTE_ALIGN:
                OnCmdEditColumnPasteAlign();
                break;
        
        case ID_EDIT_COLUMN_PASTE_APPEND:
                OnCmdEditColumnPasteAppend();
                break;

        case ID_EDIT_SPACES_TO_TABS:
                OnCmdEditSpacesToTabs();
                break;

        case ID_EDIT_SPACES_TO_TABS_LEADING:
                OnCmdEditSpacesToTabsLeading();
                break;

        case ID_EDIT_TABS_TO_SPACES:
                OnCmdEditTabsToSpaces();
                break;

        case ID_EDIT_TRIM_TRAILING_SPACES:
                OnCmdEditTrimTrailingSpaces();
                break;

        case ID_EDIT_CASE_LOWER:
                OnCmdEditCaseLower();
                break;

        case ID_EDIT_CASE_UPPER:
                OnCmdEditCaseUpper();
                break;

        case ID_EDIT_CASE_CAPITALIZE:
                OnCmdEditCaseCapitalize();
                break;

        case ID_EDIT_CASE_INVERT:
                OnCmdEditCaseInvert();
                break;
                
        case ID_EDIT_MATCH_BRACE:
                OnCmdEditMatchBrace();
                break;

        case ID_EDIT_SET_READ_ONLY:
                OnCmdEditSetReadOnly();
                break;

        default:
                break;
        }
}

void CSclTextCCView::OnCmdEditSetWordWrap()            
{ 
        const CPfxEditTypeInfo* pInfo = GetDocument()->GetTypeInfoPtr(); 
        SetViewWrapping(
                (IsWrapping() ? PFX_EC_WRAP_NONE : pInfo->m_nWrapStyle),
                (IsWrapping() ? 0 : pInfo->m_nWrapWidth)); 
}

/////////////////////////////////////////////////////////////////////////////
// OnView...
void CSclTextCCView::OnUpdateGroupView(CCmdUI* pCmdUI)
{
 
        pCmdUI->Enable(false);
}

void CSclTextCCView::OnGroupView()
{
        ASSERT_VALID(this);
           
        OnCmdViewLineBreak();


}

/////////////////////////////////////////////////////////////////////////////
// OnSearch...
void CSclTextCCView::OnUpdateGroupSearch(CCmdUI* pCmdUI)
{
        // TODO: 在此处添加消息处理程序代码
        BOOL bOn;
        BOOL bReadOnly = IsReadOnly();
        BOOL bNotEmpty = (GetDocSize() > 0);

        switch (pCmdUI->m_nID)
        {
        case ID_SEARCH_FIND:
        case ID_SEARCH_FIND_NEXT:
        case ID_SEARCH_FIND_PREV:
                bOn = bNotEmpty;
                break;
        
        case ID_SEARCH_RP:
                bOn = bNotEmpty && !IsReadOnly();
                break;
        
        default:
                bOn = false;
                break;
        }
        
        pCmdUI->Enable(bOn);
}

void CSclTextCCView::OnGroupSearch()
{
        ASSERT_VALID(this);

        switch (GetAppFrame()->GetCurrentCommand())
        {
        
        case ID_SEARCH_FIND:
                OnCmdSearchFind();
                break;

        case ID_SEARCH_RP:
                OnCmdSearchReplace();
                break;
     
        
        default:
                break;
        }
}

void CSclTextCCView::OnCmdSearchReplace() 
{
	// TODO: 在此处添加消息处理程序代码
	if (m_pDlgReplace == NULL)
	{
		m_pDlgReplace = new CDlgReplace;
		m_pDlgReplace->Create(IDD_SEARCH_REPLACE);
	}
	m_pDlgReplace->MoveWindow(1000 ,300 ,432 ,240);

	m_pDlgReplace->ShowWindow(SW_SHOW);
}

void CSclTextCCView::OnCmdSearchFind() 
{
	// TODO: 在此处添加消息处理程序代码
	if (m_pDlgFind == NULL)
	{
		m_pDlgFind = new CDlgFind;
		m_pDlgFind->Create(IDD_SEARCH_FIND);
	}

	 m_pDlgFind->MoveWindow(1000 ,300 ,450 ,180);

	m_pDlgFind->ShowWindow(SW_SHOW);

}
void CSclTextCCView::OnInitialUpdate()
{
	CPfxEditView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基
	pugi::xml_node oPugiNode = theApp.GetPugixmlSourceRoot();
	CString strSourText ;
	pugi::xml_string_writer wrtSour;
	oPugiNode.print(wrtSour,L"\t", 1U, pugi::encoding_auto);
	OnOpenDocFromStringAutoUtfToMulti(wrtSour.result.c_str());
}

LRESULT CSclTextCCView::UpdateTreeView( WPARAM wParam, LPARAM lParam)
{
	pugi::xml_node_struct* pStructNode = (pugi::xml_node_struct*)wParam;
	pugi::xml_node oNode(pStructNode);

	CString strName , strText;

	strText = oNode.attribute(L"name").as_string();
	strName = oNode.name();

	CPoint pStart( 0 ,0 );
	CPoint pEnd( 0 ,0 );
	EditFind(pStart,// [IN/OUT]范围起点。
		pEnd,// [OUT]范围终点。
		strName,// 查找对象，长度由cchFindWhat给出。
		-1,// 查找对象的长度，如果等于-1表示由函数自动计算长度，这时应以NULL结尾。
		1,// 是否匹配大小写。
		1,// 是否单词匹配。
		false,// 是否使用正则表达式（这时忽略单词匹配）。
		1,// 是否向下查找。
		false,// 是否用书签标记找到的对象所在行。
		true) ;  // 是否在文件尽头折回，它只当起点或终点在文档尽头才起作用。

	EditSelect(pStart.y, pStart.x, pEnd.y, pEnd.x);

	CString strAll = strText;
	if (strName != "DataTypeTemplates")
	{
		strAll ="name=\"";
		strAll += strText;
		strAll += "\"";
	}
	else
	{
		strText = *((CString*)lParam);
		strAll = strText;
	}

	if (!strText.IsEmpty())
	{
		pStart.x = 0;
		pStart.y = 0;
		EditFind(pEnd,// [IN/OUT]范围起点。
			pStart,// [OUT]范围终点。
			strAll,// 查找对象，长度由cchFindWhat给出。
			-1,// 查找对象的长度，如果等于-1表示由函数自动计算长度，这时应以NULL结尾。
			1,// 是否匹配大小写。
			1,// 是否单词匹配。
			false,// 是否使用正则表达式（这时忽略单词匹配）。
			1,// 是否向下查找。
			false,// 是否用书签标记找到的对象所在行。
			true) ;  // 是否在文件尽头折回，它只当起点或终点在文档尽头才起作用。

		EditSelect(pEnd.y, pEnd.x, pStart.y, pStart.x);
	}

	return 0;
}
void CSclTextCCView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CPfxEditView::OnClose();
}

void CSclTextCCView::SetCStringValue(CString strTextValue)
{
// 	CPoint oPoint = (0,0,0,0);
// 	PasteNormal(oPoint ,strTextValue ,strTextValue.GetLength());

	CPoint ptFrom = GetCurrentPosition();
	CharsInsert(ptFrom, strTextValue, strTextValue.GetLength(), TRUE);
}