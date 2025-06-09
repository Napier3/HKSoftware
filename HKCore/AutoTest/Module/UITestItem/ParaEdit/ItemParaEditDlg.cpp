// ItemParaEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ItemParaEditDlg.h"

#include "..\..\..\..\Module\XLanguage\XLanguageResource.h"
#include "..\..\..\..\Module\XLanguage\XLangWndAdjust.h"
#include "..\..\..\..\Module\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CItemParaEditDlg 对话框

CItemParaEditDlg::CItemParaEditDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent, TRUE)
{
	m_pItem = NULL;
// 	m_pGridFaultPara = NULL;
// 	m_pGridCommPara = NULL;
}

CItemParaEditDlg::~CItemParaEditDlg()
{
}


CExBaseObject* CItemParaEditDlg::FindVariableByID(const CString &strID)
{
	ASSERT (m_pItem != NULL);
	return Gb_FindVariableByID(m_pItem, strID);
}

CExBaseObject* CItemParaEditDlg::FindVariableByName(const CString &strName)
{
	return NULL;
}

void CItemParaEditDlg::OnExprScriptChanged(const CString &strExprScript)
{

}

void CItemParaEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}

void CItemParaEditDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_btnItemParaOk.SetLanguageID(g_sLangID_OK);
	m_btnItemParaCancel.SetLanguageID(g_sLangID_Cancel);


	CXLangWndAdjMngr oWndAdjMngr;         
	oWndAdjMngr.RegisterCols();  
	oWndAdjMngr.RegisterXCol(&m_btnItemParaOk);  
	oWndAdjMngr.RegisterXCol(&m_btnItemParaCancel); 

	oWndAdjMngr.Adjust(this, TRUE);
	xlang_InitByLgugStr(g_sLangID_TestItemParEdit, this);
}

BEGIN_MESSAGE_MAP(CItemParaEditDlg, CDynDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CItemParaEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


void CItemParaEditDlg::ShowItemPara()
{
	if (m_pItem == NULL)
	{
		return;
	}

	UINT nClassID = m_pItem->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_MACROTEST:
		ShowMacroItemPara();
		break;
	case GBCLASSID_COMMCMD:
		ShowCommCmdPara();
		break;
	default:
		break;
	}
}

void CItemParaEditDlg::ShowMacroItemPara()
{
	CTestMacro * oTestMacro = Gb_GetMacroPtr(m_pItem);

	if(oTestMacro == NULL)
	{
		return;
	}

	CTestMacros *pMacros = (CTestMacros*)oTestMacro->GetParent();
	m_oGridFaultPara.m_pDataTypesRef = pMacros->GetDataTypes();
	m_oGridCommPara.m_pDataTypesRef = pMacros->GetDataTypes();

	m_oGridFaultPara.Create(WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), &m_tabMacroItemParaType, 6001);
	m_oGridFaultPara.EnableHeaderCtrl(TRUE, g_sLangTxt_Name/*_T("参数名称")*/, g_sLangTxt_ParaValue/*_T("参数值")*/);
	m_oGridFaultPara.MarkModifiedProperties();
	m_oGridFaultPara.SetVSDotNetLook();

	m_oGridCommPara.Create(WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), &m_tabMacroItemParaType, 6002);
	m_oGridCommPara.EnableHeaderCtrl(TRUE,g_sLangTxt_Name/*_T("参数名称")*/, g_sLangTxt_ParaValue/*_T("参数值")*/);
	m_oGridCommPara.MarkModifiedProperties();
	m_oGridCommPara.SetVSDotNetLook();

	m_tabMacroItemParaType.AddTab(&m_oGridFaultPara, g_sLangTxt_FaultParameter/*L"故障参数"*/);
	m_tabMacroItemParaType.AddTab(&m_oGridCommPara, g_sLangTxt_GeneralParameter/*L"通用参数"*/);

	CShortDatas* pDatas = NULL;
	CMacroTestPara* pTestPara = ((CMacroTest*)m_pItem)->GetMacroTestPara();
	CMacroTestParaDatas *pFaultPara = pTestPara->GetFaultParaDatas();

	pDatas = oTestMacro->GetFaultParas();
	m_oFaultParas.DeleteAll();
	m_oFaultParas.AppendCloneEx(*pDatas);
	pFaultPara->SetToDatasValue(&m_oFaultParas);
	//pFaultPara->SetToDatasValue(oTestMacro, TRUE);//, listNew, listDelete);

	CDataGroup  *pDataGroup = NULL;
	pDataGroup = oTestMacro->GetFaultParasEx();
	m_oFaultParasEx.DeleteAll();
	if (pDataGroup != NULL)
	{
		m_oFaultParasEx.AppendCloneEx(*pDataGroup);
		pFaultPara->SetToDatasValue(&m_oFaultParasEx,TMCLASSID_CTMFAULTPARASEX);
	}
	
	m_oGridFaultPara.SetMacroTestDatas(&m_oFaultParasEx, &m_oFaultParas, m_pItem);

	pDatas = oTestMacro->GetSysParas();
	m_oSysParas.DeleteAll();
	m_oSysParas.AppendCloneEx(*pDatas);
	pFaultPara->SetToDatasValue(&m_oSysParas);


	m_oGridCommPara.SetMacroTestDatas(NULL, &m_oSysParas, m_pItem);
}

void CItemParaEditDlg::ShowCommCmdPara()
{
	
}

// CItemParaEditDlg 消息处理程序

BOOL CItemParaEditDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();
	m_oGridFaultPara.SetExprVariableFind(this);
	m_oGridCommPara.SetExprVariableFind(this);
	m_oGridFaultPara.EnableDescriptionArea();
	m_oGridCommPara.EnableDescriptionArea();

	CreateButton(m_btnItemParaOk, g_sLangTxt_OK, CRect(177, 490, 267, 515), IDOK, this);
	CreateButton(m_btnItemParaCancel, g_sLangTxt_Cancel, CRect(277, 490, 367, 515), IDCANCEL, this);

	m_tabMacroItemParaType.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(5, 5, 510, 485), this, 1000,CMFCTabCtrl::LOCATION_TOP);

	ShowItemPara();

	xlang_InitAndAdjust();

	CRect rcDlg;
	GetWindowRect(rcDlg);
	rcDlg.right = rcDlg.left + 520;
	rcDlg.bottom = rcDlg.top + 550;
	MoveWindow(rcDlg);
	CenterWindow();

	m_btnItemParaOk.SetFont(g_pGlobalFont11);
	m_btnItemParaCancel.SetFont(g_pGlobalFont11);
	m_tabMacroItemParaType.SetFont(g_pGlobalFont11);


	return TRUE; 
}

void CItemParaEditDlg::OnOK()
{
	DeleteAll();

	CDynDialogEx::OnOK();
}

void CItemParaEditDlg::OnCancel()
{
	DeleteAll();

	CDynDialogEx::OnCancel();
}

void CItemParaEditDlg::DeleteAll()
{
	//m_tabMacroItemParaType.RemoveAllTabs();
	//delete m_pGridFaultPara;
	//delete m_pGridCommPara;
}


void CItemParaEditDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
