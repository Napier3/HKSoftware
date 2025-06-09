// DlgImportCharFromRioFile.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "DlgImportCharFromRioFile.h"


// CDlgImportCharFromRioFile 对话框

IMPLEMENT_DYNAMIC(CDlgImportCharFromRioFile, CDialog)

CDlgImportCharFromRioFile::CDlgImportCharFromRioFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImportCharFromRioFile::IDD, pParent)
	, m_strXrioFile(_T(""))
{
	m_pCharacteristic = NULL;
}

CDlgImportCharFromRioFile::~CDlgImportCharFromRioFile()
{
}

void CDlgImportCharFromRioFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_RIO_FILE, m_treeXrio);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_RIO_FILE, m_strXrioFile);
}


BEGIN_MESSAGE_MAP(CDlgImportCharFromRioFile, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgImportCharFromRioFile::OnBnClickedButtonBrowse)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_RIO_FILE, &CDlgImportCharFromRioFile::OnTvnSelchangedTreeRioFile)
END_MESSAGE_MAP()


// CDlgImportCharFromRioFile 消息处理程序

void CDlgImportCharFromRioFile::OnBnClickedButtonBrowse()
{
	if (!m_oXrioTextFile.ReadXrioTextFile(this))
	{
		return;
	}

	m_btnOK.EnableWindow(TRUE);
	m_strXrioFile = m_oXrioTextFile.m_strRioFile;
	m_oXrioTextFile.InsertTreeCtrl(&m_treeXrio, TVI_ROOT);
	UpdateData(FALSE);
	EnableOK();
}

CXrioGroup* CDlgImportCharFromRioFile::GetSelGroup()
{
	HTREEITEM hSel = m_treeXrio.GetSelectedItem();

	if (hSel == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)m_treeXrio.GetItemData(hSel);

	if (pSel == NULL)
	{
		return NULL;
	}

	if(pSel->GetClassID() == XRIOCLASSID_RIO_GROUP)
	{
		return (CXrioGroup*)pSel;
	}
	else
	{
		return NULL;
	}
}

void CDlgImportCharFromRioFile::EnableOK()
{
	m_btnOK.EnableWindow(GetSelGroup() != NULL);
}

void CDlgImportCharFromRioFile::OnOK()
{
	if (m_pCharacteristic == NULL)
	{
		m_pCharacteristic = new CCharacteristic();
	}

	CXrioGroup *pXrioGroup = GetSelGroup();

	if (pXrioGroup == NULL)
	{
		return;
	}

	CXrioTextFileToAtsCharTool oTool;

	if (!oTool.ImportCharFromRioGroup(m_pCharacteristic, pXrioGroup))
	{
		MessageBox(_T("导入特性曲线失败"));
		return;
	}

	CDialog::OnOK();
}

void CDlgImportCharFromRioFile::OnCancel()
{
	if (m_pCharacteristic != NULL)
	{
		delete m_pCharacteristic;
		m_pCharacteristic = NULL;
	}

	CDialog::OnCancel();
}

void CDlgImportCharFromRioFile::OnTvnSelchangedTreeRioFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	EnableOK();
}
