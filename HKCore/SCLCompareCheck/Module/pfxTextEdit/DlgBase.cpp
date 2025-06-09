// DlgBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "AppGlobals.h"
#include "DlgBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBase �Ի���
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
// CDlgBase ��Ϣ�������
void CDlgBase::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
        // ������б������ϵİ�����ť��ϵͳ�ᷢ��һWM_SYSCOMMAND��Ϣ������
        // �Ե����е������Ϣ��ֱ���û���ť����������
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
        if (!m_bHitHelp) // �û���F1��ʹ�ð�����
        {
                GetApp()->HtmlHelp(m_nIDHelp);
        }
        else // �û�ʹ�ñ������ϰ�����ť��
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

        // Ϊ����ֵ���ú��ʵ���ֵ��
        if (iInt < iMinVal)
        {
                iInt = iMinVal;
        }

        if (iInt > iMaxVal)
        {
                iInt = iMaxVal;
        }

        // ���úϷ�����ֵ��
        ::SetDlgItemInt(hWnd, nIDItem, (UINT)iInt, true);

        // ȫѡ��
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

        // Ϊ����ֵ���ú��ʵ���ֵ��
        if (uInt < uMinVal)
        {
                uInt = uMinVal;
        }

        if (uInt > uMaxVal)
        {
                uInt = uMaxVal;
        }

        // ���úϷ�����ֵ��
        ::SetDlgItemInt(hWnd, nIDItem, uInt, false);

        // ȫѡ��
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
                // ����_stscanf�������Ϸ��ַ�����ķǷ��ַ�������Ҫ�����
                // ���������Ƿ��зǷ��ַ���ֻ��������ַ��ǺϷ��ģ�
                // "+"
                // "-"
                // "."
                // _istdigit()���ط�����ַ���ͨ����0-9��

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

        // Ϊ����ֵ���ú��ʵ���ֵ��
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

        // ȫѡ��
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
