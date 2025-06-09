// DlgBase.cpp : 实现文件
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "AppGlobals.h"
#include "DlgBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBase 对话框
IMPLEMENT_DYNAMIC(CDlgBase, CDialog)
CDlgBase::CDlgBase(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
        m_bHitHelp = false;
}

CDlgBase::~CDlgBase()
{
}

BEGIN_MESSAGE_MAP(CDlgBase, CDialog)
	ON_WM_HELPINFO()
	ON_WM_SYSCOMMAND()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgBase 消息处理程序
void CDlgBase::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
        // 如果击中标题栏上的帮助按钮，系统会发出一WM_SYSCOMMAND消息，其后会
        // 吃掉所有的鼠标消息，直至用户按钮下了鼠标键。
        m_bHitHelp = false;
	CDialog::OnNcLButtonDown(nHitTest, point);
        m_bHitHelp = false;
}

void CDlgBase::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
        if (nID == SC_CONTEXTHELP)
        {
                m_bHitHelp = true;
        }
	
        CDialog::OnSysCommand(nID, lParam);
}

BOOL CDlgBase::OnHelpInfo(HELPINFO* pHelpInfo) 
{
        UNUSED(pHelpInfo);
	// TODO: Add your message handler code here and/or call default
        GetApp()->HtmlHelp(m_nIDHelp);
        /*
        if (!m_bHitHelp) // 用户按F1键使用帮助。
        {
                GetApp()->HtmlHelp(m_nIDHelp);
        }
        else // 用户使用标题栏上帮助按钮。
        {
                HWND hWnd;
                if (pHelpInfo->iContextType != HELPINFO_WINDOW)
                {
                        hWnd = GetSafeHwnd();
                }
                else
                {
                        hWnd = (HWND)pHelpInfo->hItemHandle;
                }
                GetApp()->WinHelp(hWnd, pHelpInfo->iCtrlId);
        }
        */
        m_bHitHelp = false;
        return true;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CDlgBase::DlgIsItemVisible(CWnd* pOwner, int nIDItem)
{
        ASSERT_VALID(pOwner);
        HWND hWndItem = ::GetDlgItem(pOwner->GetSafeHwnd(), nIDItem);
        ASSERT(hWndItem != NULL);
        return ::IsWindowVisible(hWndItem);
}

void CDlgBase::DlgShowItem(CWnd* pOwner, int nIDItem, BOOL bShow)
{
        ASSERT_VALID(pOwner);
        HWND hWndItem = ::GetDlgItem(pOwner->GetSafeHwnd(), nIDItem);
        ASSERT(hWndItem != NULL);
        
        BOOL bVisible = ::IsWindowVisible(hWndItem);
        if (bShow)
        {
                if (!bVisible)
                {
                        ::ShowWindow(hWndItem, SW_SHOW);
                }
        }
        else
        {
                if (bVisible)
                {
                        ::ShowWindow(hWndItem, SW_HIDE);
                }
        }
}

BOOL CDlgBase::DlgIsItemChecked(CWnd* pOwner, int nIDItem)
{
        ASSERT_VALID(pOwner);
        return (::IsDlgButtonChecked(pOwner->GetSafeHwnd(), nIDItem) == UI_CHECK);
}

void CDlgBase::DlgCheckItem(CWnd* pOwner, int nIDItem, BOOL bCheck)
{
        ASSERT_VALID(pOwner);
        ::CheckDlgButton(pOwner->GetSafeHwnd(),
                nIDItem,
                (bCheck ? UI_CHECK : UI_UNCHECK));
}

BOOL CDlgBase::DlgIsItemEnabled(CWnd* pOwner, int nIDItem)
{
        ASSERT_VALID(pOwner);
        HWND hWndItem = ::GetDlgItem(pOwner->GetSafeHwnd(), nIDItem);
        ASSERT(hWndItem != NULL);
        return ::IsWindowEnabled(hWndItem);
}

void CDlgBase::DlgEnableItem(CWnd* pOwner, int nIDItem, BOOL bEnable)
{
        ASSERT_VALID(pOwner);
        HWND hWndItem = ::GetDlgItem(pOwner->GetSafeHwnd(), nIDItem);
        ASSERT(hWndItem != NULL);
        if (bEnable)
        {
                if (!::IsWindowEnabled(hWndItem))
                {
                        ::EnableWindow(hWndItem, true);
                }
        }
        else
        {
                if (::IsWindowEnabled(hWndItem))
                {
                        ::EnableWindow(hWndItem, false);
                }
        }
}

BOOL CDlgBase::DlgGetItemINT(CWnd* pOwner,
                             int nIDItem,
                             UINT nIDErrMsgFormat,
                             INT& iRetVal,
                             INT iMinVal,
                             INT iMaxVal)
{
        ASSERT_VALID(pOwner);
        HWND hWnd = pOwner->GetSafeHwnd();
        BOOL bTrans = false;
        INT iInt = (INT)::GetDlgItemInt(hWnd, nIDItem, &bTrans, true);

        if (bTrans && (iInt >= iMinVal) && (iInt <= iMaxVal))
        {
                iRetVal = iInt;
                return true;
        }

        appAlert2(nIDErrMsgFormat,
                MB_OK | MB_ICONINFORMATION,
                iMinVal,
                iMaxVal);

        // 为建议值设置合适的数值。
        if (iInt < iMinVal)
        {
                iInt = iMinVal;
        }

        if (iInt > iMaxVal)
        {
                iInt = iMaxVal;
        }

        // 设置合法的数值。
        ::SetDlgItemInt(hWnd, nIDItem, (UINT)iInt, true);

        // 全选。
        ::SendDlgItemMessage(hWnd, nIDItem, EM_SETSEL, 0, -1);
        ::SetFocus(::GetDlgItem(hWnd, nIDItem));
        return false;
}

BOOL CDlgBase::DlgGetItemUINT(CWnd* pOwner,
                              int nIDItem,
                              UINT nIDErrMsgFormat,
                              UINT& uRetVal,
                              UINT uMinVal,
                              UINT uMaxVal)
{
        ASSERT_VALID(pOwner);
        HWND hWnd = pOwner->GetSafeHwnd();
        BOOL bTrans = false;
        UINT uInt = (UINT)::GetDlgItemInt(hWnd, nIDItem, &bTrans, true);

        if (bTrans && (uInt >= uMinVal) && (uInt <= uMaxVal))
        {
                uRetVal = uInt;
                return true;
        }

        appAlert2(nIDErrMsgFormat,
                MB_OK | MB_ICONINFORMATION,
                uMinVal,
                uMaxVal);

        // 为建议值设置合适的数值。
        if (uInt < uMinVal)
        {
                uInt = uMinVal;
        }

        if (uInt > uMaxVal)
        {
                uInt = uMaxVal;
        }

        // 设置合法的数值。
        ::SetDlgItemInt(hWnd, nIDItem, uInt, false);

        // 全选。
        ::SendDlgItemMessage(hWnd, nIDItem, EM_SETSEL, 0, -1);
        ::SetFocus(::GetDlgItem(hWnd, nIDItem));
        return false;
}

BOOL CDlgBase::DlgGetItemFLOAT(CWnd* pOwner,
                               int nIDItem,
                               UINT nIDErrMsgFormat,
                               FLOAT& fRetVal,
                               FLOAT fMinVal,
                               FLOAT fMaxVal)
{
        ASSERT_VALID(pOwner);

        TCHAR sz[64];
        sz[0] = '\0';

        HWND hWnd = pOwner->GetSafeHwnd();
        FLOAT fResult = fMinVal;
        int cchText = ::GetDlgItemText(hWnd,
                nIDItem,
                sz,
                SIZEOF(sz));

        if (cchText > 0)
        {
                // 由于_stscanf不会理会合法字符后面的非法字符，所以要检查字
                // 符串里面是否有非法字符，只有下面的字符是合法的：
                // "+"
                // "-"
                // "."
                // _istdigit()返回非零的字符，通常是0-9。

                BOOL bStringOK = true;
                for (int i = 0; i < cchText; i++)
                {
                        TCHAR c = sz[i];

                        if ((_istdigit(c) == 0)
                                && (c != '+')
                                && (c != '-')
                                && (c != '.'))
                        {
                                bStringOK = false;
                                break;
                        }
                }

                if (bStringOK)
                {
                        int nResult = _stscanf(sz, _T("%f"), &fResult);
                        if ((nResult != 0) && (nResult != EOF))
                        {
                                if ((fResult >= fMinVal) && (fResult <= fMaxVal))
                                {
                                        fRetVal = fResult;
                                        return true;
                                }
                        }
                }
        }

        appAlert2(nIDErrMsgFormat,
                MB_OK | MB_ICONINFORMATION,
                fMinVal,
                fMaxVal);

        // 为建议值设置合适的数值。
        if (fResult < fMinVal)
        {
                fResult = fMinVal;
        }

        if (fResult > fMaxVal)
        {
                fResult = fMaxVal;
        }

        _stprintf(sz, _T("%.2f"), fResult);
        ::SetDlgItemText(hWnd, nIDItem, sz);

        // 全选。
        ::SendDlgItemMessage(hWnd, nIDItem, EM_SETSEL, 0, -1);
        ::SetFocus(::GetDlgItem(hWnd, nIDItem));

        return false;
}

LRESULT CDlgBase::DlgSimulateItemCmdMessage(CWnd* pOwner, int nIDItem, WORD wMsg)
{
        ASSERT_VALID(pOwner);
        HWND hWnd = pOwner->GetSafeHwnd();
        HWND hWndItem = ::GetDlgItem(hWnd, nIDItem);
        if (hWndItem != NULL)
        {
                return ::SendMessage(hWnd,
                        WM_COMMAND,
                        MAKEWPARAM(LOWORD(nIDItem), wMsg),
                        (LPARAM)hWndItem);
        }
        return 0;
}

LRESULT CDlgBase::DlgSimulateItemNotifyMessage(CWnd* pOwner, int nIDItem, WORD wMsg)
{
        UNUSED(pOwner);
        UNUSED(nIDItem);
        UNUSED(wMsg);
        ASSERT(false);
        return 0;
}
