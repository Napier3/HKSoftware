// XDlgUserMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "AtsStudio.h"
#include "XDlgUserMngr.h"

#include "XDlgUser.h"

CXUserListCtrl::CXUserListCtrl()
{
	
}

CXUserListCtrl::~CXUserListCtrl()
{
	
}

void CXUserListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	ASSERT (pObj->GetClassID() == USRDCLASSID_CXUSER);
	((CXUser *)pObj)->UpdateListCtrl(this, nIndex);
}

// CXDlgUserMngr 对话框

IMPLEMENT_DYNAMIC(CXDlgUserMngr, CDialog)

CXDlgUserMngr::CXDlgUserMngr(CWnd* pParent /*=NULL*/)
	: CDialog(CXDlgUserMngr::IDD, pParent)
{
	m_pCurrSelUser = NULL;
}

CXDlgUserMngr::~CXDlgUserMngr()
{
}

void CXDlgUserMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERMNGR, m_listUserMngr);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CXDlgUserMngr, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CXDlgUserMngr::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CXDlgUserMngr::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CXDlgUserMngr::OnBnClickedButtonDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USERMNGR, &CXDlgUserMngr::OnLvnItemchangedListUsermngr)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USERMNGR, &CXDlgUserMngr::OnNMDblclkListUsermngr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USERMNGR, &CXDlgUserMngr::OnNMClickListUsermngr)
END_MESSAGE_MAP()


// CXDlgUserMngr 消息处理程序

void CXDlgUserMngr::OnBnClickedButtonAdd()
{
	CXDlgUser dlg;
	CXUser  *pNew = new CXUser();
	pNew->SetName(_T("新用户"));
	pNew->SetID(_T("NewUser"));
	pNew->SetPSW(_T(""));

	dlg.m_pCurrUser = pNew;

	if (dlg.DoModal() == IDOK)
	{
		CUserDBConstGlobal::AddUser(pNew);
		m_listUserMngr.AddObj(pNew);
	}
	else
	{
		delete pNew;
	}
}

void CXDlgUserMngr::OnBnClickedButtonEdit()
{
	if (m_pCurrSelUser == NULL)
	{
		return;
	}

	CXDlgUser dlg;
	dlg.m_pCurrUser = m_pCurrSelUser;

	if (dlg.DoModal() == IDOK)
	{
		CXUserMngr *pUserMngr = CUserDBConstGlobal::GetUserMngr();
		pUserMngr->SaveUserDB();
		m_listUserMngr.UpdateListCtrl(m_pCurrSelUser, m_nCurrSelUser);
	}
}

void CXDlgUserMngr::OnBnClickedButtonDelete()
{
	if (m_pCurrSelUser == NULL)
	{
		return;
	}

	CString strMsg;
	strMsg.Format(_T("确实要删除【%s】吗？"), m_pCurrSelUser->GetID());

	if (MessageBox(strMsg, _T("提示"), MB_YESNO | MB_ICONQUESTION) != IDYES)
	{
		return;
	}

	CXUserMngr *pUserMngr = CUserDBConstGlobal::GetUserMngr();
	pUserMngr->Delete(m_pCurrSelUser);
	m_listUserMngr.DeleteItem(m_nCurrSelUser);
	pUserMngr->SaveUserDB();
}

void CXDlgUserMngr::OnLvnItemchangedListUsermngr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

BOOL CXDlgUserMngr::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_listUserMngr.InsertColumn(0,_T("编号"), LVCFMT_LEFT, 50);
	m_listUserMngr.InsertColumn(1,_T("名称"), LVCFMT_LEFT, 130);
	m_listUserMngr.InsertColumn(2,_T("ID"),   LVCFMT_LEFT, 130);
	m_listUserMngr.InsertColumn(3,_T("密码"), LVCFMT_LEFT, 130);

	m_listUserMngr.ModifyListCtrlStyle();
	m_listUserMngr.ShowBaseList(CUserDBConstGlobal::GetUserMngr());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CXDlgUserMngr::OnNMDblclkListUsermngr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnBnClickedButtonEdit();

	*pResult = 0;
}

void CXDlgUserMngr::OnNMClickListUsermngr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	m_pCurrSelUser = NULL;
	m_nCurrSelUser = -1;

	if (pNMItemActivate->iItem >= 0)
	{
		m_pCurrSelUser = (CXUser *)m_listUserMngr.GetItemData(pNMItemActivate->iItem);
		m_nCurrSelUser = pNMItemActivate->iItem;
	}

	EnableButtons();

	*pResult = 0;
}

void CXDlgUserMngr::EnableButtons()
{
	if (m_pCurrSelUser == NULL)
	{
		m_btnDelete.EnableWindow(FALSE);
		m_btnEdit.EnableWindow(FALSE);
	}
	else
	{
		if (m_pCurrSelUser->IsAdmin())
		{
			m_btnDelete.EnableWindow(FALSE);
		}
		else
		{
			m_btnDelete.EnableWindow(TRUE);
		}

		m_btnEdit.EnableWindow(TRUE);
	}
}

