// DlgXFileNameGen.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgXFileNameGen.h"
#include "..\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"

// CDlgXFileNameGen 对话框

#define CONNFLAG_COMBOBOX_WIDTH  40

IMPLEMENT_DYNAMIC(CDlgXFileNameGen, CDialog)

CDlgXFileNameGen::CDlgXFileNameGen(const CString &strNameGenConfigFile,CWnd* pParent)
: CDynDialogEx(pParent)
{
	m_strNameGenConfigFile = strNameGenConfigFile;
	CDataMngrXmlRWKeys::Create();
	m_oFngDataset.OpenXmlFile(strNameGenConfigFile, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);

	CDvmValue *pValue = new CDvmValue();
	pValue->m_strID = _T("+");	
	pValue->m_strName = pValue->m_strID;
	m_oDataFlag.AddNewChild(pValue);

	pValue = new CDvmValue();
	pValue->m_strID = _T("_");
	pValue->m_strName = pValue->m_strID;
	m_oDataFlag.AddNewChild(pValue);

	pValue = new CDvmValue();
	pValue->m_strID = _T("-");
	pValue->m_strName = pValue->m_strID;
	m_oDataFlag.AddNewChild(pValue);

}

CDlgXFileNameGen::~CDlgXFileNameGen()
{
	CDataMngrXmlRWKeys::Release();
}

void CDlgXFileNameGen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgXFileNameGen, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgXFileNameGen::OnBnClickedOk)
	XON_CBN_SELCHANGE_RANGE(XIDC_COMBO_DATA, XIDC_COMBO_DATAMAX, &CDlgXFileNameGen::OnCbnSelchangeDataType)
	XON_CBN_EDITCHANGE_RANGE(XIDC_COMBO_DATA, XIDC_COMBO_DATAMAX, &CDlgXFileNameGen::OnCbnEditchangeDataType)
END_MESSAGE_MAP()


int CDlgXFileNameGen::DoModal()   
{   
	CRect rect(0,0,200,200);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

// CDlgXFileNameGen 消息处理程序
void CDlgXFileNameGen::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgXFileNameGen::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_strFileName.Empty();
	CDvmData *pData = NULL;
	POS pos = m_oFngDataset.GetHeadPosition();
	long nIndex = 0;
	long nCount = m_oFngDataset.GetCount();
	CString strText;
	BOOL bSave = FALSE;
	CString strFlag;

	while (nIndex<nCount)
	{
		CExBaseListComboBox *pComboBox = &m_cmbDataType[nIndex];
		CExBaseListComboBox *pComboBoxFlag = &m_cmbConnFlag[nIndex];
		pData = (CDvmData *)m_oFngDataset.GetAtIndex(nIndex);
		pComboBox->GetWindowText(strText);
		if (::IsWindow(pComboBoxFlag->m_hWnd))
		{
			strFlag =  pComboBoxFlag->GetSelectID();
		}
		else
		{
			strFlag.Empty();
		}

		if (pData->m_strID != strText)
		{
			bSave = TRUE;
		}

		pData->m_strID = strText;

		if (pData->m_strUnit != strFlag)
		{
			pData->m_strUnit = strFlag;
			bSave = TRUE;
		}

		if (strText.GetLength() > 0)
		{
			if (pData->FindByName(strText) == NULL)
			{
				CDvmValue *pValue = new CDvmValue();
				pValue->m_strName = strText;
				pValue->m_strID = strText;
				pData->AddNewChild(pValue);
				bSave = TRUE;
			}


// 			if (m_strFileName.GetLength() == 0)
// 			{
// 				m_strFileName = strText;
// 			}
// 			else
			{
				m_strFileName.AppendFormat(_T("%s%s"), strText,strFlag);
			}

		}
		
		nIndex++;
	}

	if (bSave)
	{
		m_oFngDataset.SaveXmlFile(m_strNameGenConfigFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

	OnOK();
}

void CDlgXFileNameGen::CreateControls()
{
	CDvmData *pData = NULL;
	POS pos = m_oFngDataset.GetHeadPosition();
	CRect rcTitle(14, 13, 80, 27);
	CRect rcComboBox(90, 10, 360, 30);
	long nIndex = 0;
	BOOL bAddEmpty = FALSE;
	BOOL bDynamic = FALSE;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oFngDataset.GetNext(pos);
		CreateStatic(m_stcTitle[nIndex], pData->m_strName, rcTitle, XIDC_COMBO_TITLE + nIndex, this);

		if (pData->m_strFormat == _T("dynamic"))
		{
			CreateComboBox_DropDown(m_cmbDataType[nIndex], rcComboBox, XIDC_COMBO_DATA+nIndex, this);
			bDynamic = TRUE;
		}
		else
		{
			CreateComboBox_DropList(m_cmbDataType[nIndex], rcComboBox, XIDC_COMBO_DATA+nIndex, this);
			bDynamic = FALSE;
		}

		if (pos != NULL)
		{
			CRect rcFlag = rcComboBox;
			rcFlag.left = rcComboBox.right + 5;
			rcFlag.right = rcFlag.left + CONNFLAG_COMBOBOX_WIDTH;
			CreateComboBox_DropList(m_cmbConnFlag[nIndex], rcFlag, XIDC_COMBO_CONNFLAG+nIndex, this);
			m_cmbConnFlag[nIndex].ShowBaseList(&m_oDataFlag);
			m_cmbConnFlag[nIndex].SetSelByID(pData->m_strUnit);
			m_cmbConnFlag[nIndex].SetFont(g_pGlobalFont12);
		}

#ifdef UNICODE
		bAddEmpty = pData->m_strValue == _T("0");
#else
		bAddEmpty = pData->m_strValue[0] =='0';
#endif
		m_cmbDataType[nIndex].SetAddEmptyString(bAddEmpty);
		m_cmbDataType[nIndex].ShowBaseList(pData);
		//m_cmbDataType[nIndex].SetCurSel(bAddEmpty ? 1 : 0);
		m_cmbDataType[nIndex].SetSelByName(pData->m_strID);

		m_stcTitle[nIndex].SetFont(g_pGlobalFont12);
		m_cmbDataType[nIndex].SetFont(g_pGlobalFont12);

		rcTitle.OffsetRect(0, 30);
		rcComboBox.OffsetRect(0, 30);

		nIndex++;

		if (nIndex >= XIDC_COMBO_MAX)
		{
			break;
		}
	}
	
	rcTitle.bottom += 10;
	m_nDlgWidth = rcComboBox.right + 10 + CONNFLAG_COMBOBOX_WIDTH+5;
	CreateButton(m_btnOK, g_sLangTxt_OK/*_T("确定")*/, rcTitle, IDOK, this);
	rcTitle.OffsetRect(rcTitle.Width()+10, 0);
	CreateButton(m_btnCancel, g_sLangTxt_Cancel/*_T("取消")*/, rcTitle, IDCANCEL, this);
	
	m_nDlgHeight = rcTitle.bottom + 10;
	m_nDlgHeight += 30;
	m_btnOK.SetFont(g_pGlobalFont12);
	m_btnCancel.SetFont(g_pGlobalFont12);

	m_btnOK.SetFocus();
}


BOOL CDlgXFileNameGen::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();

	CRect rcDlg;
	GetWindowRect(&rcDlg);
	rcDlg.right = rcDlg.left + m_nDlgWidth;
	rcDlg.bottom = rcDlg.top + m_nDlgHeight;
	MoveWindow(rcDlg, TRUE);
	CenterWindow();
	
	SetWindowText(g_sLangTxt_GnrtFileNm/*_T("组合生成文件名称")*/);

	CDvmData *pData = NULL;
	POS pos = m_oFngDataset.GetHeadPosition();
	long nIndex = 0;
	long nLen = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oFngDataset.GetNext(pos);
		nLen = m_cmbDataType[nIndex].GetWindowTextLength();

		if (pData->m_strFormat == _T("dynamic"))
		{
			m_cmbDataType[nIndex].SetEditSel(0, nLen);
			m_cmbDataType[nIndex].SetEditSel(0, 0);
		}

		nIndex++;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgXFileNameGen::SaveXmlFile()
{
// 	CString strInfo;
// 	CString strFileName= m_strFileName + m_strFilePostfix;
// 	CXFolder* pFolderSelect = (CXFolder*)m_folderTree.GetItemData(m_folderTree.GetSelectedItem());
// 
// 	CXFile* pFileSelect = (CXFile*)pFolderSelect->FindByLowerName(strFileName);
// 	BOOL bFlag = (pFileSelect != NULL) ? (TRUE) : (FALSE);		//标识文件是否已经存在
// 	CXFile* pFile = NULL;
// 
// 	CWnd* pParentWnd = GetParent();
// 	ASSERT(pParentWnd != NULL);
// 
// 	if(bFlag)
// 	{
// 		strInfo.Format(_T("%s 文件已经存在，是否覆盖?"),strFileName);
// 		if( MessageBox(strInfo,_T("文件重名"),MB_ICONQUESTION |MB_OKCANCEL ) == IDOK )
// 		{	
// 			if(!pFileSelect->m_bIsOpen)
// 			{
// 				pFile = pFolderSelect->AddFile(NULL,strFileName/*,m_strPostFixDes*/,TRUE);
// 				pFile->m_bIsOpen = TRUE;
// 
// 				AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this);
// 				if( !m_bIsSaveAs)
// 				{
// 					pParentWnd->SendMessage(WM_PARENT_SAVE_XML_FILE,0,(LPARAM)(char*)(_bstr_t)this->GetFileName());
// 				}
// 
// 				return TRUE;
// 			}
// 			else
// 			{
// 				strInfo.Format(_T("%s 已经被打开，文件覆盖失败"),pFileSelect->m_strName);
// 				MessageBox(strInfo,_T("文件覆盖失败"),MB_OK);
// 			}
// 		}
// 
// 		return FALSE;
// 	}
// 	else
// 	{
// 		pFile = pFolderSelect->AddFile(NULL,strFileName/*,m_strPostFixDes*/,FALSE);
// 		pFile->m_bIsOpen = TRUE;
// 		m_pFileMngrBase->SaveXMLFile();
// 
// 		AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this);
// 		pParentWnd->SendMessage(WM_PARENT_SAVE_XML_FILE,0,(LPARAM)(char*)(_bstr_t)this->GetFileName());
// 
// 		return TRUE;
// 	}

	return FALSE;
}

BOOL CDlgXFileNameGen::OpenXmlFile()
{
// 	CString strFileName = GetFileName();
// 	CWnd* pParentWnd = GetParent();
// 	m_pFileSelect->m_bIsOpen = TRUE;
// 	CString_to_char(strFileName, g_pszFileName);
// 	LRESULT nRet = pParentWnd->SendMessage(WM_PARENT_OPEN_XML_FILE, (WPARAM)m_pFileSelect, (LPARAM)g_pszFileName);
//
//	return (nRet == 0);
	return FALSE;
}

void CDlgXFileNameGen::OnCbnEditchangeDataType(UINT nID)
{
	long nIndex = nID - XIDC_COMBO_DATA;

	if (nIndex < 0 || nIndex > XIDC_COMBO_MAX)
	{
		return;
	}
}

void CDlgXFileNameGen::OnCbnSelchangeDataType(UINT nID)
{
	long nIndex = nID - XIDC_COMBO_DATA;

	if (nIndex < 0 || nIndex > XIDC_COMBO_MAX)
	{
		return;
	}

	CExBaseListComboBox *pComboBox = &m_cmbDataType[ nIndex ];
	nIndex = pComboBox->GetCurSel();

// 	if (nIndex == CB_ERR)
// 	{
// 		return;
// 	}

	//CFilterText *pText = (CFilterText*)m_cmbHistory.GetItemDataPtr(nIndex);
	//SelectFile(pText);
}
