// MultiKey.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XMultiKeyDlg.h"

#include "..\..\Module\KeyDb\XMultiKeyBase.h"
#include "..\..\XLanguage\XLanguageMngr.h"

// CMultiKey �Ի���

IMPLEMENT_DYNAMIC(CXMultiKeyDlg, CDialog)

CXMultiKeyDlg::CXMultiKeyDlg(CWnd* pParent /*=NULL*/)
:CXKeyEditDlgBase(pParent)
, m_strName(_T(""))
, m_strID(_T(""))
, m_strKeyBase(_T(""))
{
	m_pKey = NULL;
	m_pMultiKeyBase = NULL;
	m_nCurrSelIndex = -1;
}

CXMultiKeyDlg::~CXMultiKeyDlg()
{
}

void CXMultiKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if (!::IsWindow(m_editName.m_hWnd))
	{
		return;
	}
	DDX_Text(pDX, XIDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, XIDC_EDIT_ID, m_strID);
	DDX_Control(pDX, XIDC_LIST_MULTIKEY, m_listMultiKey);
	DDX_Text(pDX,XIDC_EDIT_BASEKEYNAME, m_strKeyBase);
}


BEGIN_MESSAGE_MAP(CXMultiKeyDlg, CDialog)
	ON_BN_CLICKED(XIDC_BTN_SAVE, &CXMultiKeyDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(XIDC_BTN_INSERT, &CXMultiKeyDlg::OnBnClickedBtnInsert)
	ON_BN_CLICKED(XIDC_BTN_DELETE, &CXMultiKeyDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(XIDC_BTN_CANCLE, &CXMultiKeyDlg::OnBnClickedBtnCancle)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, XIDC_LIST_MULTIKEY, &CXMultiKeyDlg::OnNMClickListMultikey)
END_MESSAGE_MAP()

//����

void CXMultiKeyDlg::ShowMultiKeyList()
{
	m_listMultiKey.DeleteAllItems();
	long nIndex = 0;
	CString strKey;
	CXMultiKeyBase *pMultiKey = (CXMultiKeyBase*)m_pXKey;

	POS pos = pMultiKey->GetHeadPosition();
	CExBaseObject *pKey = NULL;

	while (pos != NULL)
	{
		pKey = pMultiKey->GetNext(pos);                             //posָ����һ��pos��keyΪ��ǰֵ
		strKey.Format(_T("%s"), pKey->m_strName);
		nIndex = m_listMultiKey.InsertItem(nIndex, strKey);
		m_listMultiKey.SetItemData(nIndex, (DWORD)pKey);
	}
}
// CMultiKey ��Ϣ�������

void CXMultiKeyDlg::OnBnClickedBtnSave()
{
	UpdateData(TRUE);
	
	if (!ValidateKey(m_strName, m_strID))
	{
		return;
	}

	m_pXKey->m_strName = m_strName;
	m_pXKey->m_strID = m_strID;

	CDialog::OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CXMultiKeyDlg::OnBnClickedBtnCancle()
{
	CDialog::OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CXMultiKeyDlg::OnBnClickedBtnInsert()
{	
	UpdateData(TRUE);
	
	if (m_strKeyBase.IsEmpty())
	{
		MessageBox(/*_T("�����ݣ����ܲ��룡")*/g_sLangTxt_NoDataNotInsert);
		return;
	}

	CXKeyDB *pKeyDb = (CXKeyDB*)m_pKeyParent;

	CExBaseObject *pFind = pKeyDb->FindByKeyName(m_strKeyBase);

	if (pFind != NULL)
	{
		CString strMsg;
		strMsg.Format(/*_T("��%s���Ѿ�����")*/g_sLangTxt_Exist, m_strKeyBase);
		MessageBox(strMsg, /*_T("��ʾ")*/g_sLangTxt_Message, MB_OK | MB_ICONWARNING);
		return;
	}

	CXMultiKeyBase *pMultiKey = (CXMultiKeyBase*)m_pXKey;
	CExBaseObject *pKey = new CXKeyBase();
	pKey->m_strName = m_strKeyBase;

	pMultiKey->AddNewChild(pKey);
	ShowMultiKeyList();
}

void CXMultiKeyDlg::OnBnClickedBtnDelete()
{
	if (m_nCurrSelIndex == -1)
	{
		MessageBox(/*_T("��ѡ��Ҫɾ���Ķ���")*/g_sLangTxt_DeleteKeyObj);
		return;
	}

	CXMultiKeyBase *pMultiKey = (CXMultiKeyBase*)m_pXKey;
	pMultiKey->Delete(m_pKey);
	m_listMultiKey.DeleteItem(m_nCurrSelIndex);

	m_pKey = NULL;
	m_nCurrSelIndex = -1;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CXMultiKeyDlg::OnNMClickListMultikey(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_nCurrSelIndex = pNMItemActivate->iItem;

	if (m_nCurrSelIndex != -1)
	{
		m_pKey = (CExBaseObject*) m_listMultiKey.GetItemData(m_nCurrSelIndex);
	}
	else
	{
		m_pKey = NULL;
	}

	*pResult = 0;
}


void CXMultiKeyDlg::OnDestroy()
{
	//�ڴ˴�����һ��deleteʱ����Ϊ�Ի�����ʧʱ������û�д�������,����m_KeyDbʱ��������list�б�Ҳ���ܻ�����ݣ�������
	// 	delete m_pMultiKey;
	// 	m_pMultiKey = NULL;

	CDialog::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}

BOOL CXMultiKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //�����ؼ�

	m_strName = m_pXKey->m_strName;
	m_strID = m_pXKey->m_strID;
	UpdateData(FALSE);

	ShowMultiKeyList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CXMultiKeyDlg::CreateControls()    //�����ؼ�  name�� size�� ID�� this    //�������Ӹ����ؼ������ԣ����尡ʲô��
{
	CreateStatic(m_NameStatic, _T("Name"),CRect(5, 7, 35, 30), XIDC_STATIC_NAME, this);
	CreateStatic(m_IDStatic, _T("ID"),CRect(5, 35, 35,55 ), XIDC_STATIC_ID, this);

	CreateEdit(m_editName, CRect(40, 5,220, 27), XIDC_EDIT_NAME, this);	
	CreateEdit(m_editID, CRect(40, 32, 220, 55), XIDC_EDIT_ID, this);

	CreateListCtrl(m_listMultiKey, CRect( 5, 60, 220, 204), XIDC_LIST_MULTIKEY, this,STYLE_LISTCTRL_LIST);

	CreateEdit(m_editKeyBase, CRect(5, 210, 220, 235), XIDC_EDIT_BASEKEYNAME, this);
	
	CreateButton(m_btnInsert, /*_T("����")*/g_sLangTxt_MdtInsert, CRect(5, 240, 55, 262), XIDC_BTN_INSERT, this);
	CreateButton(m_btnDelete, /*_T("ɾ��")*/g_sLangTxt_Delete, CRect(60, 240, 110, 262), XIDC_BTN_DELETE, this);
	CreateButton(m_btnSave, /*_T("����")*/g_sLangTxt_Save, CRect(115, 240, 165, 262),XIDC_BTN_SAVE , this);
	CreateButton(m_btnCancle, /*_T("ȡ��")*/g_sLangTxt_Cancel, CRect(170, 240, 220, 262),XIDC_BTN_CANCLE , this);

	CFont *pFont = GetFont();
	m_btnSave.SetFont(pFont);
	m_btnInsert.SetFont(pFont);
	m_btnDelete.SetFont(pFont);
	m_listMultiKey.SetFont(pFont);
	m_editName.SetFont(pFont);
	m_editID.SetFont(pFont);
	m_editKeyBase.SetFont(pFont);

	m_NameStatic.SetFont(pFont);
	m_IDStatic.SetFont(pFont);

	m_btnCancle.SetFont(pFont);
}


int CXMultiKeyDlg::DoModal()   //�����Ի���
{   
	CRect rect(0,0,150,170);   
	SetDlgRect(rect);
	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST1);   
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   


