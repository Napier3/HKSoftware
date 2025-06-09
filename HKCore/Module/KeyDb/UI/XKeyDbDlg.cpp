// CXKeyDbDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XKeyDbDlg.h"

#include "..\..\Module\API\FileApi.h"
#include "..\..\Module\DialogBase\DynDialogEx.h"
#include "XBaseKeyDlg.h"
#include "XMultiKeyDlg.h"
#include "XAnalyzeDlg.h"

#include "..\KeyDb\XMatchObject.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\XLanguage\XLanguageMngr.h"


// CXKeyDbDlg 对话框

IMPLEMENT_DYNAMIC(CXKeyDbDlg, CDialog)

CXKeyDbDlg::CXKeyDbDlg(CXKeyDB *pXKeyDB, CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
, m_strAnalyze(_T(""))
{
	m_pKeyDb = pXKeyDB;
	m_nCurrSelIndex = -1;
	m_bKeyDbChanged = FALSE;
}

CXKeyDbDlg::~CXKeyDbDlg()
{

}

void CXKeyDbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if (!::IsWindow(m_combFilterKey.m_hWnd))
	{
		return;
	}
	DDX_Text(pDX, XIDC_EDIT_ANALYZE, m_strAnalyze);
}


BEGIN_MESSAGE_MAP(CXKeyDbDlg, CDialog)
	ON_BN_CLICKED(XIDC_BTN_BASEKEYNEW, &CXKeyDbDlg::OnBnClickedBtnBasekeynew)
	ON_BN_CLICKED(XIDC_BTN_MULTIKEYNEW, &CXKeyDbDlg::OnBnClickedBtnMultikeynew)
	ON_BN_CLICKED(XIDC_BTN_KEYDELETE, &CXKeyDbDlg::OnBnClickedBtnKeydelete)
	ON_BN_CLICKED(XIDC_BTN_FILTER, &CXKeyDbDlg::OnBnClickedBtnFilter)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, XIDC_LIST_KEYDB, &CXKeyDbDlg::OnNMDblclkListKeydb)
	ON_NOTIFY(NM_CLICK, XIDC_LIST_KEYDB, &CXKeyDbDlg::OnNMClickListKeydb)
	ON_BN_CLICKED(XIDC_BTN_XKEYDB_VALIDATE, &CXKeyDbDlg::OnBnClickedBtnValidateXkeyDb)
	ON_BN_CLICKED(XIDC_BTN_INKEYDB, &CXKeyDbDlg::OnBnClickedBtnInportkeydb)
	ON_BN_CLICKED(XIDC_BTN_ANALYZE, &CXKeyDbDlg::OnBnClickedBtnAnalyze)
END_MESSAGE_MAP()


//
BOOL CXKeyDbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //创建控件

	ShowList();
	SetWindowText(m_pKeyDb->m_strXKeyDbFile);

	CString strFile = m_pKeyDb->m_strXKeyDbFile;
	long nPos = strFile.ReverseFind('.');
	strFile = strFile.Left(nPos);
	strFile += _T("Filter.xml");
	m_oFilterTextMngr.OpenXmlFile(strFile);

	m_combFilterKey.InitFilterText(&m_oFilterTextMngr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CXKeyDbDlg::CreateControls()    //创建控件  name、 size、 ID、 this    //继续增加各个控件的属性，字体啊什么的
{	
	m_combFilterKey.Create(STYLE_COMBOBOX_DROPDOWN,CRect(5, 13, 280, 35), this,XIDC_COMB_FILTER);
	CreateButton(m_btnFilter,/* _T("过滤")*/g_sLangTxt_Filter, CRect(290, 10, 355, 35), XIDC_BTN_FILTER, this);
	CreateButton(m_btnCinKeyDb,/* _T("合并文件")*/g_sLangTxt_CinKeyDb, CRect(365, 10, 430, 35), XIDC_BTN_INKEYDB, this);

	CreateButton(m_btnBaseKeyNew, /*_T("新建关键字")*/g_sLangTxt_BaseKeyNew, CRect(5, 470, 105, 495), XIDC_BTN_BASEKEYNEW, this);
	CreateButton(m_btnMultiKeyNew,/* _T("新建复合关键字")*/g_sLangTxt_MultiKeyNew, CRect(110, 470, 210, 495),XIDC_BTN_MULTIKEYNEW , this);
	CreateButton(m_btnDeleteKey, /*_T("删除关键字")*/g_sLangTxt_DeleteKey, CRect(215, 470, 315, 495), XIDC_BTN_KEYDELETE, this);
	CreateButton(m_btnSelectSameKey,/* _T("查找无效关键字")*/g_sLangTxt_SelectSameKey, CRect(330, 470, 430, 495), XIDC_BTN_XKEYDB_VALIDATE, this);


	CreateListCtrl(m_listKeyDB, CRect(5, 45, 430, 460), XIDC_LIST_KEYDB, this,STYLE_LISTCTRL_LIST);

	CreateButton(m_btnAnalyze,/*_T("关键字分析")*/g_sLangTxt_AnalyzeKey,CRect(330,505,430,530),XIDC_BTN_ANALYZE,this);
	CreateEdit(m_editAnalyze,CRect(5,508,315,530),XIDC_EDIT_ANALYZE,this);


	CFont *pFont = GetFont();
	m_btnFilter.SetFont(pFont);
	m_btnBaseKeyNew.SetFont(pFont);
	m_btnMultiKeyNew.SetFont(pFont);
	m_btnDeleteKey.SetFont(pFont);
	m_btnSelectSameKey.SetFont(pFont);
	m_btnCinKeyDb.SetFont(pFont);

	m_combFilterKey.SetFont(pFont);
	m_listKeyDB.SetFont(g_pGlobalFont);

	m_btnAnalyze.SetFont(pFont);
	m_editAnalyze.SetFont(pFont);

}


int CXKeyDbDlg::DoModal()   //弹出对话框
{   
	CRect rect(0,0,290,335);    
	SetDlgRect(rect);
	
	//AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect,this);   
	int iRet = CDynDialogEx::DoModal();   

	if (m_bKeyDbChanged)
	{
		m_pKeyDb->InitKeyRefBuffer();
	}

	m_pKeyDb = NULL;

	return iRet;   
}   


// CXKeyDbDlg 消息处理程序
// CString CXKeyDbDlg::SearchKeyDbname(const CString &strXmlPath)
// {
// 
// 	int nIndex = strXmlPath.GetLength() - 1;
// 	char letter = strXmlPath.GetAt(nIndex);
// 	while(letter != '\\')
// 	{
// 		nIndex--;
// 		letter = strXmlPath.GetAt(nIndex);
// 	}
// 
// 	return strXmlPath.Mid(nIndex+1);
// 
// }


void CXKeyDbDlg::OpenXml(const CString &strXmlName)
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += strXmlName;

	m_pKeyDb->OpenXmlFile(strFile, CKeyDbXmlRWKeys::CXKeyDBKey(), CKeyDbXmlRWKeys::g_pXmlKeys);

	m_strKeyDbPath = strFile;
}

void CXKeyDbDlg::SaveXml(const CString &strXmlName)
{
	
}

void CXKeyDbDlg::ShowList()
{
	ASSERT (m_pKeyDb != NULL);

	m_listKeyDB.DeleteAllItems();

	long nIndex = 0;
	InsertXKeys(m_pKeyDb->GetXKeyMngr(), nIndex);
	InsertXKeys(m_pKeyDb->GetXKeyMaps(), nIndex);

	m_listKeyDB.SetColumnWidth(0, 140);
}

void CXKeyDbDlg::InsertXKeys(CExBaseList *pList, long &nIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pKey = NULL;

	while (pos != NULL)
	{
		pKey = pList->GetNext(pos);   

		if (pKey->m_dwReserved != 0)
		{
			InsertXKey(pKey, nIndex);
			nIndex++;
		}
	}
}

void CXKeyDbDlg::InsertXKey(CExBaseObject *pKey, long nIndex)
{
	//CString strKey;
	//strKey.Format(_T("%s【%s】"), pKey->m_strName, pKey->m_strID);
	long nItem = m_listKeyDB.InsertItem(nIndex, _T(""));
	UpdateXKey(pKey, nItem);
	//m_listKeyDB.SetItemData(nItem, (DWORD)pKey);
}

void CXKeyDbDlg::UpdateXKey(CExBaseObject *pKey, long nIndex)
{
	CString strKey;
	strKey.Format(_T("%s(%s)"), pKey->m_strName, pKey->m_strID);

	if (pKey->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
	{
		CExBaseList *pList = (CExBaseList*)pKey;
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = (CExBaseObject *)pList->GetNext(pos);
			strKey.AppendFormat(_T("[%s]"), p->m_strName);
		}
	}

	long nItem = m_listKeyDB.SetItemText(nIndex, 0, strKey);
	m_listKeyDB.SetItemData(nIndex, (DWORD)pKey);
}


void CXKeyDbDlg::PopDlg(CExBaseObject *pKey)
{
	if (pKey == NULL)
	{
		return;
	}

	UINT nClassID = pKey->GetClassID(); 

	switch(nClassID)
	{
	case KDBCLASSID_CXKEYBASE:
		PopBaseKeyDlg(pKey);
		break;

	case KDBCLASSID_CXMULTIKEYBASE:
		PopMultiKeyDlg(pKey);
		break;

	default:
		break;
	}
}

void CXKeyDbDlg::PopBaseKeyDlg(CExBaseObject *pKey)  //需要更改
{
	CXBaseKeyDlg BaseKeyDlg;
	
	if (BaseKeyDlg.EditKey(pKey) == IDOK)
	{
		BaseKeyDlg.m_pXKey->Copy(pKey);
		UpdateXKey(m_pCurrSelKey, m_nCurrSelIndex);
		m_bKeyDbChanged = TRUE;
	}
}

void CXKeyDbDlg::PopMultiKeyDlg(CExBaseObject *pKey)
{
	CXMultiKeyDlg MultiKeyDlg;

	if (MultiKeyDlg.EditKey(pKey) == IDOK)
	{
		MultiKeyDlg.m_pXKey->Copy(pKey);
		UpdateXKey(m_pCurrSelKey, m_nCurrSelIndex);
		m_bKeyDbChanged = TRUE;
	}
}

void CXKeyDbDlg::UpdateList(CExBaseObject *pKey,const int &nIndex)  //刷新替换当前值
{
	m_listKeyDB.DeleteItem(nIndex);

	CString strKey;
	strKey.Format(_T("%s【%s】"), pKey->m_strName, pKey->m_strID);
	m_listKeyDB.InsertItem(nIndex, strKey);
	m_listKeyDB.SetItemData(nIndex, (DWORD)pKey);
}

void CXKeyDbDlg::AddNewKey(CExBaseObject *pKey)  //new时，增加list中的数据
{
	int nIndex = 0;
	m_pKeyDb->AddNewChild(pKey);

	CString strKey;
	strKey.Format(_T("%s【%s】"), pKey->m_strName, pKey->m_strID);

	m_listKeyDB.InsertItem(nIndex, strKey);
	m_listKeyDB.SetItemData(nIndex, (DWORD)pKey);
	m_bKeyDbChanged = TRUE;
}


void CXKeyDbDlg::KeySelectSimple(CExBaseObject *pKeyBase,const int &nBegin)  //寻找相同的key
{
// 	int nNum = 0;
// 	CExBaseObject *pKey = NULL;
// 	int Num = m_pKeyDb->GetCount();
// 
// 	for (nNum = nBegin +1 ; nNum<Num ; nNum++)
// 	{
// 		pKey = m_pKeyDb->GetAtIndex(nNum);
// 
// 		if ((pKeyBase->m_strID == pKey->m_strID) || (pKeyBase->m_strName == pKey->m_strName))
// 		{	
// 			a[nNum] = false;	
// 			a[nBegin] = false;	
// 		}
// 	}
}


void CXKeyDbDlg::InsertListKeyDb()  //寻找重复关键字
{
// 	CExBaseObject *pKey;
// 	CString strKey;
// 	int nIndex = 0;
// 
// 	m_listKeyDB.DeleteAllItems();
// 
// 	for (int i=0;i<m_pKeyDb->GetCount();i++)
// 	{
// 		if (!a[i])
// 		{
// 			pKey = m_pKeyDb->GetAtIndex(i);
// 			strKey.Format(_T("%s【%s】"), pKey->m_strName, pKey->m_strID);
// 			nIndex =m_listKeyDB.InsertItem(nIndex, strKey);
// 			m_listKeyDB.SetItemData(nIndex, (DWORD)pKey); 
// 		}
// 	}

}
//控件操作

// 
// void CXKeyDbDlg::OnBnClickedBtnFilesave() // save file
// {
// 	if (m_pKeyDb == NULL)
// 	{
// 		MessageBox(_T("无数据，不能保存！"));
// 		return;
// 	}
// 
// 	if (m_strKeyDbName.IsEmpty())
// 	{
// 		OnBnClickedBtnFilesaveas();
// 		return;
// 	}
// 
// 	SaveXml(m_strKeyDbName);
// }
void CXKeyDbDlg::OnBnClickedBtnAnalyze()
{	
	UpdateData(TRUE);

	m_oXKeyAnalyse.m_strName = m_strAnalyze;

	CXMatchObject oXMatchObject;
	oXMatchObject.Init(&m_oXKeyAnalyse, m_pKeyDb);

	CString strKeyAnalyse;

	POS pos  = oXMatchObject.m_listMatchXKeys.GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyMatchRef *)oXMatchObject.m_listMatchXKeys.GetNext(pos);

		if (p->m_pXKeyRef != NULL)
		{
			strKeyAnalyse.AppendFormat(_T("%s\r\n"), p->m_pXKeyRef->m_strName);
		}
	}

	if (strKeyAnalyse.GetLength() == 0)
	{
		strKeyAnalyse = /*_T("没有匹配成功关键字")*/g_sLangTxt_AnalyzeKeyUnsu;
	}
	
	MessageBox(strKeyAnalyse,/* _T("匹配成功的关键字")*/g_sLangTxt_AnalyzeKeySu, MB_OK | MB_ICONINFORMATION);
}


void CXKeyDbDlg::OnBnClickedBtnBasekeynew()  // basekey new
{
	CExBaseObject *pKey = new CXKeyBase();
	pKey->SetParent(m_pKeyDb);
	CXBaseKeyDlg dlg;
	
	if (dlg.NewKey(pKey) == IDOK)
	{
		long nCount = m_pKeyDb->GetCount();
		m_pKeyDb->AddNewChild(pKey);
		InsertXKey(pKey, nCount);
		m_bKeyDbChanged = TRUE;
	}
	else
	{
		delete pKey;
	}
}

void CXKeyDbDlg::OnBnClickedBtnMultikeynew()  // multikey new
{
	CExBaseObject *pKey = new CXMultiKeyBase();
	pKey->SetParent(m_pKeyDb);
	CXMultiKeyDlg dlg;

	if (dlg.NewKey(pKey) == IDOK)
	{
		long nCount = m_pKeyDb->GetCount();
		m_pKeyDb->AddNewChild(pKey);
		InsertXKey(pKey, nCount);
		m_bKeyDbChanged = TRUE;
	}
	else
	{
		delete pKey;
	}
}

void CXKeyDbDlg::OnBnClickedBtnKeydelete()  // delete key
{
	if (m_nCurrSelIndex == -1)
	{
		MessageBox(/*_T("请选择要删除的对象！")*/g_sLangTxt_DeleteKeyObj);
		return;
	}

	CExBaseObject *pDel = m_pCurrSelKey;
	m_listKeyDB.DeleteItem(m_nCurrSelIndex);
	m_pKeyDb->Delete(pDel);
	m_nCurrSelIndex = -1;
	m_pCurrSelKey = NULL;
	m_bKeyDbChanged = TRUE;
}

void CXKeyDbDlg::OnBnClickedBtnFilter()  //filter key
{
	CString strFilter;
	m_combFilterKey.GetFilterText(strFilter);
	m_pKeyDb->Filter(strFilter);
	ShowList();
}

void CXKeyDbDlg::OnDestroy()
{
	//delete m_pKeyDb;
//	m_pKeyDb = NULL;

	//delete m_pKeyDbIn;
	//m_pKeyDbIn = NULL;

//	CKeyDbXmlRWKeys::Release();

	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CXKeyDbDlg::OnNMDblclkListKeydb(NMHDR *pNMHDR, LRESULT *pResult) //double
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_nCurrSelIndex = pNMItemActivate->iItem;

	if (m_nCurrSelIndex != -1)
	{
		m_pCurrSelKey = (CExBaseObject*) m_listKeyDB.GetItemData(m_nCurrSelIndex);
		PopDlg(m_pCurrSelKey);
	}
	else
	{
		m_pCurrSelKey = NULL;
	}

	*pResult = 0;
}

void CXKeyDbDlg::OnNMClickListKeydb(NMHDR *pNMHDR, LRESULT *pResult)  //single
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_nCurrSelIndex = pNMItemActivate->iItem;

	if (m_nCurrSelIndex != -1)
	{
		m_pCurrSelKey = (CExBaseObject*) m_listKeyDB.GetItemData(m_nCurrSelIndex);
	}
	else
	{
		m_pCurrSelKey = NULL;
	}

	*pResult = 0;
}

void CXKeyDbDlg::OnBnClickedBtnValidateXkeyDb()
{
	POS posCurr = m_pKeyDb->GetHeadPosition();
	POS pos = m_pKeyDb->GetHeadPosition();
	CExBaseObject *pCurr = NULL;
	CExBaseObject *p = NULL;


	while (posCurr != NULL)
	{
		pCurr = (CExBaseObject*)m_pKeyDb->GetNext(posCurr);
		pCurr->m_dwReserved = 0;
	}

	posCurr = m_pKeyDb->GetHeadPosition();

	while (posCurr != NULL)
	{
		pCurr = (CExBaseObject*)m_pKeyDb->GetNext(posCurr);

		if (pCurr->m_dwReserved == 0)
		{
			continue;
		}

		pos = m_pKeyDb->GetHeadPosition();

		while (pos != NULL)
		{
			p = (CExBaseObject *)m_pKeyDb->GetNext(pos);

			if (p == pCurr)
			{
				continue;
			}

			if ((p->m_strName == pCurr->m_strName) || (p->m_strID == pCurr->m_strID))
			{
				pCurr->m_dwReserved = 1;
				p->m_dwReserved = 1;
			}
		}
	}
	
	ShowList();
}

void CXKeyDbDlg::OnBnClickedBtnInportkeydb()
{
	CString strFilter = _T("关键字库文件(*.xml)|*.xml||");
	CString strRoot;
	strRoot = _P_GetSoftRegKey();
	CString strFile;

	if (!PopupOpenFileDialog(this,strFile, strRoot, _T("KeyDbPath"),strFilter, _T("xml")))
	{
		return;
	}

	CXKeyDB oXKeyDBIn;
	if (strFile.IsEmpty())
	{
		return;
	}

	oXKeyDBIn.OpenXmlFile(strFile, CKeyDbXmlRWKeys::CXKeyDBKey(), CKeyDbXmlRWKeys::g_pXmlKeys);

	POS pos = oXKeyDBIn.GetHeadPosition();
	CExBaseObject *pKey = NULL;
	CExBaseObject *pNew = NULL;
	long nCount = m_pKeyDb->GetCount();

	while(pos != NULL)
	{
		pKey = oXKeyDBIn.GetNext(pos);

		if ( (m_pKeyDb->FindByName(pKey->m_strName)== NULL) && (m_pKeyDb->FindByID(pKey->m_strID)== NULL))
		{
			pNew =( CExBaseObject*) pKey->Clone();
			m_pKeyDb->AddNewChild(pNew);
			InsertXKey(pKey, nCount);
			nCount++;
		}
	}

	m_bKeyDbChanged = TRUE;
}
