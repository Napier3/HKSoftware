// DlgFind.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "AppGlobals.h"

#include "..\..\SclFileTest\MainFrm.h"
#include "SclTextCCView.h"
#include "DlgFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFind dialog
CDlgFind::CDlgFind(CWnd* pParent /*=NULL*/)
        : CDlgBase(CDlgFind::IDD, pParent)
{
        //{{AFX_DATA_INIT(CDlgFind)
        //}}AFX_DATA_INIT
}


void CDlgFind::DoDataExchange(CDataExchange* pDX)
{
        CDlgBase::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CDlgFind)
        DDX_Control(pDX, IDC_SEARCH_CBX_FIND_WHAT,  m_cbxFindWhat);
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFind, CDlgBase)
        //{{AFX_MSG_MAP(CDlgFind)
        ON_BN_CLICKED(IDC_SEARCH_BTN_FIND,          OnFind)
        ON_BN_CLICKED(IDC_SEARCH_BTN_MARK_ALL,      OnMarkAll)
        ON_CBN_SELCHANGE(IDC_SEARCH_CBX_FIND_WHAT,  OnCbxSelChangeFindWhat)
        ON_CBN_EDITCHANGE(IDC_SEARCH_CBX_FIND_WHAT, OnCbxEdtChangeFindWhat)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFind message handlers
BOOL CDlgFind::OnInitDialog() 
{
        CDlgBase::OnInitDialog();
        
        // TODO: Add extra initialization here
        DoUpdateInfo(false);
        
        return true;  // return true unless you set the focus to a control
        // EXCEPTION: OCX Property Pages should return false
}

/////////////////////////////////////////////////////////////////////////////
void CDlgFind::OnOK()
{
        OnFind();
}

void CDlgFind::OnCancel()
{
        DoUpdateInfo(true);
        CDlgBase::OnCancel();
}

void CDlgFind::OnFind() 
{
        // TODO: Add your control notification handler code here
        if (!DoUpdateInfo(true))
        {
                MessageBeep(MB_OK);
                return;
        }
        
        CSclTextCCView* pView = GetAppFrame()->TextEditGetActiveView();
        if (pView == NULL)
        {
                return;
        }
        
        CPoint ptFrom = pView->GetCurrentPosition();
        CPoint ptTo(0, 0);
        if (!pView->EditFind(ptFrom,
                ptTo,
                m_strFindWhat,
                -1,
                m_bMatchCase,
                m_bMatchWholeWord,
                false,
                m_bDirectDown,
                false, // bMarkAll
                true)) // bWrapAtEndOfFile
        {
                pView->EditSelect(-1, 0, -1, 0);
                appAlert2(IDS_P_SEARCH_STRING_NOT_FOUND,
                        MB_OK | MB_ICONEXCLAMATION,
                        m_strFindWhat);
        }
        else
        {
                pView->EditSelect(ptFrom.y, ptFrom.x, ptTo.y, ptTo.x);
//               CDlgBase::OnOK();
        }
}

void CDlgFind::OnMarkAll() 
{
        // TODO: Add your control notification handler code here
        if (!DoUpdateInfo(true))
        {
                MessageBeep(MB_OK);
                return;
        }
        
        CSclTextCCView* pView = GetAppFrame()->TextEditGetActiveView();
        if (pView == NULL)
        {
                return;
        }
        
        CPoint ptFrom(0, 0);
        CPoint ptTo(0, 0);
        if (!pView->EditFind(ptFrom,
                ptTo,
                m_strFindWhat,
                -1,
                m_bMatchCase,
                m_bMatchWholeWord,
                false,
                true,  // bDirectDown ignored!
                true,  // bMarkAll
                true)) // bWrapAtEndOfFile ignored!
        {

        }
        else
        {
                pView->SetCurrentPosition(pView->BookmarkGetNext(-1, false), 0);
 //               CDlgBase::OnOK();
        }
}

/////////////////////////////////////////////////////////////////////////////
void CDlgFind::OnCbxEdtChangeFindWhat() 
{
        // TODO: Add your control notification handler code here
        BOOL bEnable = (m_cbxFindWhat.GetWindowTextLength() > 0);
        DlgEnableItem(IDC_SEARCH_BTN_FIND, bEnable);
        DlgEnableItem(IDC_SEARCH_BTN_MARK_ALL, bEnable);
}

void CDlgFind::OnCbxSelChangeFindWhat() 
{
        // TODO: Add your control notification handler code here
        DlgEnableItem(IDC_SEARCH_BTN_FIND, true);
        DlgEnableItem(IDC_SEARCH_BTN_MARK_ALL, true);
}

/////////////////////////////////////////////////////////////////////////////

BOOL CDlgFind::DoUpdateInfo(BOOL bSaveAndValidate)
{
        BOOL bResult = true;
        
        if (!bSaveAndValidate)
        {
                
                m_bMatchCase      = 1;
                m_bMatchWholeWord = 1;
                m_bDirectDown     = 1;
                
                // 选项。
                DlgCheckItem(IDC_SEARCH_CHK_MATCH_CASE, m_bMatchCase);
                DlgCheckItem(IDC_SEARCH_CHK_MATCH_WHOLE_WORD, m_bMatchWholeWord);
                
                // 查找方向。
                DlgCheckItem(IDC_SEARCH_RDO_UP, !m_bDirectDown);
                DlgCheckItem(IDC_SEARCH_RDO_DOWN, m_bDirectDown);
                
                // 填充“查找对象”列表框。
                m_cbxFindWhat.ResetContent();
           
                
                // 如果当前编辑窗口有选择文本就提取一部分或全部选择内容，并
                // 显示在输入框中。
                TCHAR sz[MAX_PATH];
                if (GetAppFrame()->TextEditGetSingleLineSelContent(sz, SIZEOF(sz)) > 0)
                {
                        m_cbxFindWhat.SetWindowText(sz);
                }
                
                DlgSimulateItemCmdMessage(IDC_SEARCH_CBX_FIND_WHAT, CBN_EDITCHANGE);
        }
        else
        {
                m_cbxFindWhat.GetWindowText(m_strFindWhat);
                if (m_strFindWhat.IsEmpty())
                {
                        bResult = false;
                }
                else
                {
                        m_bMatchCase      = DlgIsItemChecked(IDC_SEARCH_CHK_MATCH_CASE);
                        m_bMatchWholeWord = DlgIsItemChecked(IDC_SEARCH_CHK_MATCH_WHOLE_WORD);
                        m_bDirectDown     = DlgIsItemChecked(IDC_SEARCH_RDO_DOWN);
                        
                }
        }
        return bResult;
}
