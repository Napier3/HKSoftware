// BaseKeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XBaseKeyDlg.h"
#include "..\..\XLanguage\XLanguageResource.h"

// CBaseKeyDlg 对话框

IMPLEMENT_DYNAMIC(CXBaseKeyDlg, CDialog)

CXBaseKeyDlg::CXBaseKeyDlg(CWnd* pParent /*=NULL*/)
:CXKeyEditDlgBase(pParent)
, m_strName(_T(""))
, m_strID(_T(""))
{

}

CXBaseKeyDlg::~CXBaseKeyDlg()
{
}

void CXBaseKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if (!::IsWindow(m_editKeyName.m_hWnd))
	{
		return;
	}
	DDX_Text(pDX, XIDC_EDIT_BASEKEY_NAME, m_strName);
	DDX_Text(pDX, XIDC_EDIT_BASEKEY_ID, m_strID);
}


BEGIN_MESSAGE_MAP(CXBaseKeyDlg, CDialog)
	ON_BN_CLICKED(XIDC_BTN_SAVE, &CXBaseKeyDlg::OnBnClickedBtnBasekeySave)
	ON_BN_CLICKED(XIDC_BTN_CANCLE, &CXBaseKeyDlg::OnBnClickedBtnBasekeyCancle)
END_MESSAGE_MAP()


void CXBaseKeyDlg::OnBnClickedBtnBasekeySave()
{
	UpdateData(TRUE);
	
	if (!ValidateKey(m_strName, m_strID))
	{
		return;
	}

	m_pXKey->m_strName = m_strName;
	m_pXKey->m_strID = m_strID;
	
	CDialog::OnOK();
}

void CXBaseKeyDlg::OnBnClickedBtnBasekeyCancle()
{
	CDialog::OnCancel();
}


BOOL CXBaseKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //创建控件

	m_strName = m_pXKey->m_strName;
	m_strID = m_pXKey->m_strID;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CXBaseKeyDlg::CreateControls()    //创建控件  name、 size、 ID、 this    //继续增加各个控件的属性，字体啊什么的
{
	CreateButton(m_btnSave, g_sLangTxt_Save/*_T("保存")*/, CRect(190, 10, 240, 35),XIDC_BTN_SAVE , this);
	CreateButton(m_btnCancle, g_sLangTxt_Cancel/*_T("取消")*/, CRect(190, 40, 240, 65),XIDC_BTN_CANCLE , this);

	CreateEdit(m_editKeyName, CRect(40, 10, 180, 35), XIDC_EDIT_BASEKEY_NAME, this);	
	CreateEdit(m_editKeyID, CRect(40, 40, 180, 65), XIDC_EDIT_BASEKEY_ID, this);

	CreateStatic(m_NameStatic, g_sLangTxt_Name/*_T("名称")*/,CRect(5, 13, 35, 32), XIDC_STATIC_NAME, this);
	CreateStatic(m_IDStatic, _T("ID"),CRect(5, 42, 35,63), XIDC_STATIC_ID, this);

	CFont *pFont = GetFont();
	m_btnSave.SetFont(pFont);
	m_btnCancle.SetFont(pFont);
	
	m_editKeyName.SetFont(pFont);
	m_editKeyID.SetFont(pFont);
	
	m_NameStatic.SetFont(pFont);
	m_IDStatic.SetFont(pFont);
}


int CXBaseKeyDlg::DoModal()   //弹出对话框
{   
	CRect rect(0,0,170,50);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   
