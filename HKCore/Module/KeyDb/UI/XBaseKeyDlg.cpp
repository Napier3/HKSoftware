// BaseKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XBaseKeyDlg.h"
#include "..\..\XLanguage\XLanguageResource.h"

// CBaseKeyDlg �Ի���

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

	CreateControls();  //�����ؼ�

	m_strName = m_pXKey->m_strName;
	m_strID = m_pXKey->m_strID;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXBaseKeyDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	CreateButton(m_btnSave, g_sLangTxt_Save/*_T("����")*/, CRect(190, 10, 240, 35),XIDC_BTN_SAVE , this);
	CreateButton(m_btnCancle, g_sLangTxt_Cancel/*_T("ȡ��")*/, CRect(190, 40, 240, 65),XIDC_BTN_CANCLE , this);

	CreateEdit(m_editKeyName, CRect(40, 10, 180, 35), XIDC_EDIT_BASEKEY_NAME, this);	
	CreateEdit(m_editKeyID, CRect(40, 40, 180, 65), XIDC_EDIT_BASEKEY_ID, this);

	CreateStatic(m_NameStatic, g_sLangTxt_Name/*_T("����")*/,CRect(5, 13, 35, 32), XIDC_STATIC_NAME, this);
	CreateStatic(m_IDStatic, _T("ID"),CRect(5, 42, 35,63), XIDC_STATIC_ID, this);

	CFont *pFont = GetFont();
	m_btnSave.SetFont(pFont);
	m_btnCancle.SetFont(pFont);
	
	m_editKeyName.SetFont(pFont);
	m_editKeyID.SetFont(pFont);
	
	m_NameStatic.SetFont(pFont);
	m_IDStatic.SetFont(pFont);
}


int CXBaseKeyDlg::DoModal()   //�����Ի���
{   
	CRect rect(0,0,170,50);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   
