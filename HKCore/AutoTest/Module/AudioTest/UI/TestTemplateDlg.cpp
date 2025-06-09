// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\TestTemplateDlg.cpp : 实现文件
#include "stdafx.h"
#include "TestTemplateDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"


// CTestTemplateDlg 对话框

IMPLEMENT_DYNAMIC(CTestTemplateDlg, CDialog)

CTestTemplateDlg::CTestTemplateDlg(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CTestTemplateDlg::IDD, pParent)
{
	m_strCurrentTempId = "";
}

CTestTemplateDlg::~CTestTemplateDlg()
{
}

void CTestTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LISTCTRL_TESTTEMPLATE, m_ListCtrl_TestTemplate);
}

BEGIN_MESSAGE_MAP(CTestTemplateDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_TESTTEMPLATE, &CTestTemplateDlg::OnNMDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_TESTTEMPLATE, &CTestTemplateDlg::OnNMClickList)
END_MESSAGE_MAP()
// CTestTemplateDlg 消息处理程序

BOOL CTestTemplateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_static.SubclassDlgItem(IDC_STATIC_TESTTEMPLATE, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	// 为列表视图控件添加全行选中和栅格风格   
	m_ListCtrl_TestTemplate.SetExtendedStyle(m_ListCtrl_TestTemplate.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_ListCtrl_TestTemplate.InsertColumn(1, _T("序号"), LVCFMT_CENTER, 50);
	m_ListCtrl_TestTemplate.InsertColumn(2, _T("模板名称"), LVCFMT_CENTER, 350);
	SetListCtrl(&m_ListCtrl_TestTemplate);
	return true;
}

void CTestTemplateDlg::UpdateList(CString strID)
{
	// 在列表视图控件中插入列表项，并设置列表子项文本   
	if(m_strCurrentTempId == strID)
	{
		return;
	}
	m_strCurrentTempId = strID;
	m_ListCtrl_TestTemplate.DeleteAllItems();

	int nIndex = 0;
	CString strFilePath = _P_GetTemplatePath();
	CXFileMngr oFile;
	oFile.SetLibraryPath(strFilePath);

	g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_lstTempleteWords.clear();

	POS posxml = oFile.GetHeadPosition();
	while (posxml)
	{
		CXFolder* pFolder = (CXFolder*)oFile.GetNext(posxml);
		if(strID != pFolder->m_strID)
		{
			continue;
		}

		POS postmp = pFolder->GetHeadPosition();
		while (postmp)
		{
			CXFolder* pFileTmp = (CXFolder*)pFolder->GetNext(postmp);
			if(pFileTmp->m_strName.Find(".gbxml") == -1)
			{
				continue;
			}

			CString strIndex;
			strIndex.Format(_T("%d"),nIndex + 1);

			m_ListCtrl_TestTemplate.InsertItem(nIndex,strIndex);
			m_ListCtrl_TestTemplate.SetItemText(nIndex, 1, pFileTmp->m_strName);
			
			CString strTemplate = pFileTmp->m_strName.Mid(0, pFileTmp->m_strName.Find(".gbxml"));
			g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_lstTempleteWords.push_back(strTemplate);
			nIndex++;
		}
	}
	if(nIndex > 0)
	{
		m_ListCtrl_TestTemplate.GetScrollRange(SB_VERT,&m_nScollMin,&m_nScollMax);
		m_ListCtrl_TestTemplate.SetItemState(0,  LVIS_SELECTED,LVIS_SELECTED);
	}
	
}

void CTestTemplateDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	//int nLastSelRow = GetCurrentSelectRow();
	SetListSelectRow(pNMItemActivate->iItem);
	*pResult = 0;
}

void CTestTemplateDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnNMDblclkList(pNMHDR,pResult);
	*pResult = 0;
}


