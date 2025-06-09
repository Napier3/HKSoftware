// SelDatasetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmMapSelDatasetDlg.h"
#include "..\..\..\..\Module\DataMngr\DvmCmp\DvmLDeviceMap.h"

// CDvmMap_SelDatasetDlg 对话框

IMPLEMENT_DYNAMIC(CDvmMap_SelDatasetDlg, CDialog)

CDvmMap_SelDatasetDlg::CDvmMap_SelDatasetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDvmMap_SelDatasetDlg::IDD, pParent)
{
	m_pDvmDevice = NULL;
	m_pDvmDataset = NULL;
	m_pDatasetMap = NULL;
}

CDvmMap_SelDatasetDlg::~CDvmMap_SelDatasetDlg()
{
}

void CDvmMap_SelDatasetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DVMDEVICE, m_treeDvmDevice);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnSeldataSelCancel);
}


BEGIN_MESSAGE_MAP(CDvmMap_SelDatasetDlg, CDialog)
	ON_MESSAGE(DVMOBJ_SEL_CHANGED, OnDvmTreeSelObjChanged)
	ON_BN_CLICKED(IDCANCEL, &CDvmMap_SelDatasetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// void CDvmMap_SelDatasetDlg::xlang_InitAndAdjust()
// {
// 	if (xlang_IsCurrXLanguageChinese())
// 	{
// 		return;
// 	}
// 
// 	m_btnOK.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_OK);
// 	m_btnSeldataSelCancel.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_Cancel);
// 
// 
// 	CXLangWndAdjMngr oWndAdjMngr;         
// 	oWndAdjMngr.RegisterCols(); 
// 	oWndAdjMngr.RegisterXCol(&m_btnOK);
// 	oWndAdjMngr.RegisterXCol(&m_btnSeldataSelCancel);
// 	oWndAdjMngr.Adjust(this, TRUE);
// 
// 	xlang_InitByLgugStr(CXLanguageResourceDvm_DvmMap::g_sLangTxt_SelDataMap, this);
// }

// CDvmMap_SelDatasetDlg 消息处理程序

BOOL CDvmMap_SelDatasetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_treeDvmDevice.ShowDvmDevice(m_pDvmDevice, this, FALSE);

//	xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CDvmMap_SelDatasetDlg::OnDvmTreeSelObjChanged(WPARAM wParam, LPARAM lParam)
{
	CExBaseObject *pSel = (CExBaseObject*)wParam;

	if (pSel == NULL)
	{
		m_btnOK.SetEnabled(FALSE);
		return 0;
	}

	if (pSel->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		m_btnOK.SetEnabled(FALSE);
		return 0;
	}

	m_pDvmDataset = (CDvmDataset *)pSel;

	if (HasSameMap())
	{
		m_btnOK.SetEnabled(FALSE);
		return 0;
	}

	m_btnOK.SetEnabled(TRUE);

	return 0;
}


void CDvmMap_SelDatasetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL CDvmMap_SelDatasetDlg::HasSameMap()
{
	ASSERT(m_pDatasetMap != NULL);

	if (m_pDatasetMap == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("当前选中的数据集映射为空，程序出错！"));
		return FALSE;
	}

	if (m_pDatasetMap->m_pMap == m_pDvmDataset)
	{
		return TRUE;
	}

	CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)m_pDatasetMap->GetParent();
	CDvmDatasetMap *pFind = (CDvmDatasetMap*)pLDeviceMap->FindDvmMapObj(m_pDatasetMap->m_pStand, m_pDvmDataset);

	if (pFind == NULL)
	{
		pFind = (CDvmDatasetMap *)pLDeviceMap->FindDvmMapObj_ByStandID(m_pDatasetMap->m_pStand->m_strID, m_pDvmDataset);
	}

	if (pFind != NULL)
	{
		return TRUE;
	}

	return FALSE;
}