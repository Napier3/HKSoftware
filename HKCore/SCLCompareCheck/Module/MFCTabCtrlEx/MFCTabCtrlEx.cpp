// MFCTabCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTabCtrlEx.h"


// CMFCTabCtrlEx

IMPLEMENT_DYNAMIC(CMFCTabCtrlEx, CMFCTabCtrl)

CMFCTabCtrlEx::CMFCTabCtrlEx()
{

}

CMFCTabCtrlEx::~CMFCTabCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CMFCTabCtrlEx, CMFCTabCtrl)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMFCTabCtrlEx ��Ϣ�������



void CMFCTabCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ  
    CMFCTabCtrl::OnLButtonDown(nFlags, point);

    // ��ȡTab������
    int n = GetTabsNum();

    if (n == 0) return;

    CRect rc;

    // ��ȡ����Tab����
    CalcRectEdit(rc);
    GetTabsRect(rc);
    // ��ȡ��ǰѡ����ڵ�ָ��
    CWnd *pTabWnd = GetActiveWnd();
    pTabWnd->GetClientRect(rc);

    int sel;

    // ��ȡ��ǰѡ���Tab
    sel = GetActiveTab();

    // ��ȡ����Tab����
    GetTabRect(sel, rc);

    // ��ȡ����Tab�������
    int nWidth = GetTabMaxWidth();

    // ��ȡ�رհ�ť������
    CRect rcCloseBtn;
    rcCloseBtn = GetTabCloseButton();

    if (rcCloseBtn.PtInRect(point))
    {
        if(MessageBox(_T("ȷ�Ϲرոñ�ǩҳ��"), _T("�ر���ʾ"), MB_YESNO) == IDYES)
        {
            // �ر�Tabҳ��������        
            pTabWnd->SendMessage(WM_CLOSE);  
            // ɾ��Tab  
            RemoveTab(sel);
        }
    }
           
    

}


