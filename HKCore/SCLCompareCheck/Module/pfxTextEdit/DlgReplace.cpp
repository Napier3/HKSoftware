// DlgReplace.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "AppGlobals.h"

#include "..\..\SclFileTest\MainFrm.h"
#include "SclTextCCView.h"
#include "DlgReplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReplace dialog
CDlgReplace::CDlgReplace(CWnd* pParent /*=NULL*/)
        : CDlgBase(CDlgReplace::IDD, pParent)
{
        //{{AFX_DATA_INIT(CDlgReplace)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
        m_bInSelection    = false;
        m_bMatchCase      = false;
        m_bMatchWholeWord = false;
}


void CDlgReplace::DoDataExchange(CDataExchange* pDX)
{
        CDlgBase::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CDlgReplace)
        DDX_Control(pDX, IDC_SEARCH_CBX_FIND_WHAT,    m_cbxFindWhat);
        DDX_Control(pDX, IDC_SEARCH_CBX_REPLACE_WITH, m_cbxReplaceWith);
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReplace, CDlgBase)
        //{{AFX_MSG_MAP(CDlgReplace)
        ON_BN_CLICKED(IDC_SEARCH_BTN_FIND,                  OnFind)
        ON_BN_CLICKED(IDC_SEARCH_BTN_REPLACE,               OnReplace)
        ON_BN_CLICKED(IDC_SEARCH_BTN_REPLACE_ALL,           OnReplaceAll)
        ON_BN_CLICKED(IDC_SEARCH_RDO_REPLACE_IN_SELECTION,  OnRdoClickedReplaceRange)
        ON_BN_CLICKED(IDC_SEARCH_RDO_REPLACE_IN_WHOLE_FILE, OnRdoClickedReplaceRange)
        ON_CBN_SELCHANGE(IDC_SEARCH_CBX_FIND_WHAT,          OnCbxSelChangeFindWhat)
        ON_CBN_EDITCHANGE(IDC_SEARCH_CBX_FIND_WHAT,         OnCbxEdtChangeFindWhat)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReplace message handlers
BOOL CDlgReplace::OnInitDialog() 
{
        CDlgBase::OnInitDialog();
        
        // TODO: Add extra initialization here
        DoUpdateInfo(false);
        
        return true;  // return true unless you set the focus to a control
        // EXCEPTION: OCX Property Pages should return false
}

/////////////////////////////////////////////////////////////////////////////
void CDlgReplace::OnOK()
{
        OnReplace();
}

void CDlgReplace::OnCancel()
{
        DoUpdateInfo(true);
        CDlgBase::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
void CDlgReplace::OnFind() 
{
        // TODO: Add your control notification handler code here
        if (!DoUpdateInfo(true))
        {
                MessageBeep(MB_OK);
                return;
        }
        
        if (!DoFind())
        {
                return;
        }
        
        // ����ҵ�ƥ��Ķ��󣬾ͽ����뽹�����õ����滻����ť�ϣ��Է����û�
        // ���س���ո�Ϳ�ִ���滻������
        CWnd* pWnd = GetDlgItem(IDC_SEARCH_BTN_REPLACE);
        pWnd->SetFocus();
}

void CDlgReplace::OnReplace() 
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
        
        // �����ǰû�в��Ҷ����ҵ�����ѡ����Ȳ��Ҳ�ѡ�����Ե��û���һ
        // �ΰ��»س����������滻����ť��ִ�е��ǲ��Ҳ�����
        if (!IsFindTargetMatchCurrentSelection(pView))
        {
                DoFind();
        }
        else
        {
                CPoint ptFrom;
                CPoint ptTo;
                pView->GetSelRange(ptFrom, ptTo);
                
                if (pView->EditReplace(ptFrom,
                        ptTo,
                        m_strFindWhat,
                        -1,
                        m_strReplaceWith,
                        -1,
                        m_bMatchCase,
                        m_bMatchWholeWord,
                        false,  // RegExp
                        true,   // bIgnoreFindWhat
                        false)) // bInSelection
                {
                        DoFind(); // �滻������ͼ������һ��Ŀ�ꡣ
                }
        }
}

void CDlgReplace::OnReplaceAll() 
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
        if (pView->EditReplace(ptFrom,
                ptTo,
                m_strFindWhat,
                -1,
                m_strReplaceWith,
                -1,
                m_bMatchCase,
                m_bMatchWholeWord,
                false,
                false,
                m_bInSelection))
        {
        }
        else
        {
                appAlert2(IDS_P_SEARCH_STRING_NOT_FOUND,
                        MB_OK | MB_ICONEXCLAMATION,
                        m_strFindWhat);
        }
}

/////////////////////////////////////////////////////////////////////////////
void CDlgReplace::OnCbxEdtChangeFindWhat() 
{
        // TODO: Add your control notification handler code here
        BOOL bHasFindWhat = (m_cbxFindWhat.GetWindowTextLength() > 0);
        BOOL bInSelection = DlgIsItemChecked(IDC_SEARCH_RDO_REPLACE_IN_SELECTION);
        
        DlgEnableItem(IDC_SEARCH_BTN_FIND, (bHasFindWhat && !bInSelection));
        DlgEnableItem(IDC_SEARCH_BTN_REPLACE, (bHasFindWhat && !bInSelection));
        DlgEnableItem(IDC_SEARCH_BTN_REPLACE_ALL, bHasFindWhat);
}

void CDlgReplace::OnCbxSelChangeFindWhat() 
{
        // TODO: Add your control notification handler code here
        BOOL bInSelection = DlgIsItemChecked(IDC_SEARCH_RDO_REPLACE_IN_SELECTION);
        DlgEnableItem(IDC_SEARCH_BTN_FIND, !bInSelection);
        DlgEnableItem(IDC_SEARCH_BTN_REPLACE, !bInSelection);
        DlgEnableItem(IDC_SEARCH_BTN_REPLACE_ALL, true);
}

void CDlgReplace::OnRdoClickedReplaceRange()
{
        // TODO: Add your control notification handler code here
        BOOL bEnable = (!DlgIsItemChecked(IDC_SEARCH_RDO_REPLACE_IN_SELECTION)
                && (m_cbxFindWhat.GetWindowTextLength() > 0));
        
        DlgEnableItem(IDC_SEARCH_BTN_FIND, bEnable);
        DlgEnableItem(IDC_SEARCH_BTN_REPLACE, bEnable);
}

/////////////////////////////////////////////////////////////////////////////

BOOL CDlgReplace::DoUpdateInfo(BOOL bSaveAndValidate)
{
        BOOL bResult = true;
        
        if (!bSaveAndValidate)
        {          
                m_bMatchCase      = 1;
                m_bMatchWholeWord = 1;
                
                // ѡ�
                DlgCheckItem(IDC_SEARCH_CHK_MATCH_CASE, m_bMatchCase);
                DlgCheckItem(IDC_SEARCH_CHK_MATCH_WHOLE_WORD, m_bMatchWholeWord);
                
                CPoint ptFrom;
                CPoint ptTo;
                
                // �滻��Χ�����п�ѡ��ģʽ�²���ʹ�á�ѡ��Χ�ڡ���
                BOOL bInSelection  = false;
                BOOL bTextSelected = false;
                
                CSclTextCCView* pView = GetAppFrame()->TextEditGetActiveView();
                if ((pView != NULL)
                        && pView->IsTextSelected()
                        && !pView->IsColumnSelect())
                {
                        pView->GetSelRange(ptFrom, ptTo);
                        
                        // ѡ�����ݶ���һ�в��Զ����á�ѡ��Χ�ڡ���ѡ��ť��
                        bInSelection  = (ptFrom.y != ptTo.y);
                        bTextSelected = true;
                }
                
                DlgCheckItem(IDC_SEARCH_RDO_REPLACE_IN_SELECTION, bInSelection);
                DlgCheckItem(IDC_SEARCH_RDO_REPLACE_IN_WHOLE_FILE, !bInSelection);
                
                // ���û��ѡ�����ݾ�Ҫ��ֹ��ѡ��Χ�ڡ��滻�ĵ�ѡ��ť��
                DlgEnableItem(IDC_SEARCH_RDO_REPLACE_IN_SELECTION, bTextSelected);
                
                // ��䡰���Ҷ����б��
                m_cbxFindWhat.ResetContent();
                
                // ��䡰�滻���ݡ��б��
                m_cbxReplaceWith.ResetContent();
                
                // �����ǰ�༭������ѡ���ı�����ȡһ���ֻ�ȫ��ѡ�����ݣ���
                // ��ʾ��������С�
                TCHAR sz[MAX_PATH];
                if (GetAppFrame()->TextEditGetSingleLineSelContent(sz, SIZEOF(sz)) > 0)
                {
                        m_cbxFindWhat.SetWindowText(sz);
                }
                
                DlgSimulateItemCmdMessage(IDC_SEARCH_CBX_FIND_WHAT, CBN_EDITCHANGE);
                DlgSimulateItemCmdMessage((bInSelection ? IDC_SEARCH_RDO_REPLACE_IN_SELECTION : IDC_SEARCH_RDO_REPLACE_IN_WHOLE_FILE), BN_CLICKED);
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
                        // ������滻���ݡ�Ϊ�գ��͵���ɾ����
                        m_cbxReplaceWith.GetWindowText(m_strReplaceWith);
                        
                        m_bMatchCase      = DlgIsItemChecked(IDC_SEARCH_CHK_MATCH_CASE);
                        m_bMatchWholeWord = DlgIsItemChecked(IDC_SEARCH_CHK_MATCH_WHOLE_WORD);
                        m_bInSelection    = DlgIsItemChecked(IDC_SEARCH_RDO_REPLACE_IN_SELECTION);
                        
                }
        }
        return bResult;
}

BOOL CDlgReplace::DoFind()
{
        CSclTextCCView* pView = GetAppFrame()->TextEditGetActiveView();
        if (pView == NULL)
        {
                return false;
        }
        
        CPoint ptFrom;
        CPoint ptTo(0, 0);
        if (IsFindTargetMatchCurrentSelection(pView))
        {
                CPoint ptFake;
                pView->GetSelRange(ptFake, ptFrom); // ����λ��ȡѡ��Χ��ĩ�ˡ�
        }
        else
        {
                ptFrom = pView->GetCurrentPosition();
        }
        
        BOOL bFound = pView->EditFind(ptFrom,
                ptTo,
                m_strFindWhat,
                -1,
                m_bMatchCase,
                m_bMatchWholeWord,
                false, // RegExp
                true,  // bDirectDown
                false, // bMarkAll
                true); // bWrapAtEndOfFile
        if (bFound)
        {
                // �滻�Ի������û�������滻����ť��ִ���滻����Ҫ����ǰ��
                // ����ͼ�м���ʾ��
                pView->SetCurrentPosition(ptFrom.y, ptFrom.x);
                pView->EditSelect(ptFrom.y, ptFrom.x, ptTo.y, ptTo.x);
        }
        else
        {
                pView->EditSelect(-1, 0, -1, 0);
                
                appAlert2(IDS_P_SEARCH_STRING_NOT_FOUND,
                        MB_OK | MB_ICONEXCLAMATION,
                        m_strFindWhat);
        }
        return bFound;
}
/////////////////////////////////////////////////////////////////////////////
// ������
//     BOOL IsFindTargetMatchCurrentSelection(CSclTextCCView* pView)
// ���ã�
//     ���滻ǰ��鵱ǰ�ĵ������ڵ�ѡ�������Ƿ����滻����ƥ�䡣
// ������
// ���أ�
// ��ע��
/////////////////////////////////////////////////////////////////////////////
BOOL CDlgReplace::IsFindTargetMatchCurrentSelection(CSclTextCCView* pView)
{
        if ((pView == NULL)
                || !pView->IsTextSelected()
                || pView->IsColumnSelect())
        {
                return false;
        }
        
        CPoint ptSelFrom;
        CPoint ptSelTo;
        pView->GetSelRange(ptSelFrom, ptSelTo);
        
        CPoint ptFrom = ptSelFrom;
        CPoint ptTo = ptSelTo;
        
        return (pView->EditFind(ptFrom,
                ptTo,
                m_strFindWhat,
                -1,
                m_bMatchCase,
                m_bMatchWholeWord,
                false,
                true,
                false,
                false)
                && (ptSelFrom == ptFrom)
                && (ptSelTo == ptTo));
}
