// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\NewTest.cpp : 实现文件
#include "stdafx.h"
#include "NewTestDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"
// CNewTest 对话框

IMPLEMENT_DYNAMIC(CNewTestDlg, CDialog)

//CNewTestDlg* g_pNewTestDlg = NULL;

CNewTestDlg::CNewTestDlg(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CNewTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCurrentDlg = NULL;
}

CNewTestDlg::~CNewTestDlg()
{
}

void CNewTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_AREA_SET, m_AreaSet);
	DDX_Control(pDX, IDC_LISTOPERATESTEPS, m_ListOperateSteps);
}

void CNewTestDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);

	XUI_AddWnd(&m_AreaSet, 0, 1, 1, 1);
	XUI_AddWnd(&m_ListOperateSteps, 0, 1, 1, 1);

	CXUIAdjItem_Area::XUI_OnSize();
}

BEGIN_MESSAGE_MAP(CNewTestDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_NEXT, &CNewTestDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_BACK, &CNewTestDlg::OnBnClickedBtnBack)
	ON_BN_CLICKED(IDC_BTN_RETURN, &CNewTestDlg::OnBnClickedBtnReturn)
	ON_BN_CLICKED(IDC_BTN_BACKPAGE, &CNewTestDlg::OnBnClickedBtnBackpage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CNewTestDlg::OnBnClickedBtnNextpage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTOPERATESTEPS, &CNewTestDlg::OnNMDblclkListOperateSteps)
	ON_NOTIFY(NM_CLICK, IDC_LISTOPERATESTEPS, &CNewTestDlg::OnNMClickListoperatesteps)

	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_LISTOPERATESTEPS, &CNewTestDlg::OnNMCustomdrawList2)
END_MESSAGE_MAP()

// CNewTest 消息处理程序
BOOL CNewTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	XUI_InitAdjust();
	m_static.SubclassDlgItem(IDC_STATIC_OPERATESTEP, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	// TODO:  在此添加额外的初始化
	m_ListOperateSteps.SetExtendedStyle(m_ListOperateSteps.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListOperateSteps.InsertItem(DLG_InspectType,_T("第一步：检验类型"));
	CString *strCheckType = new CString("CheckType");
	m_ListOperateSteps.SetItemData(DLG_InspectType,(DWORD_PTR)strCheckType);

	m_ListOperateSteps.InsertItem(DLG_DeviceType,_T("第二步：装置类型"));
	CString *strDeviceType = new CString("DeviceType");
	m_ListOperateSteps.SetItemData(DLG_DeviceType,(DWORD_PTR)strDeviceType);

	m_ListOperateSteps.InsertItem(DLG_PotocolType,_T("第三步：规约类型"));
	CString *strPotocolType = new CString("GuiYueType");
	m_ListOperateSteps.SetItemData(DLG_PotocolType,(DWORD_PTR)strPotocolType);

	m_ListOperateSteps.InsertItem(DLG_TestTemplate,_T("第四步：测试模板"));
	CString *strTestTemplate = new CString("TestModel");
	m_ListOperateSteps.SetItemData(DLG_TestTemplate,(DWORD_PTR)strTestTemplate);

	m_ListOperateSteps.InsertItem(DLG_DeviceIPInspect,_T("第五步：装置IP"));
	CString *strDeviceIPInspect = new CString("SetIP");
	m_ListOperateSteps.SetItemData(DLG_DeviceIPInspect,(DWORD_PTR)strDeviceIPInspect);

	m_ListOperateSteps.SetItemState(0, LVIS_DROPHILITED | LVIS_SELECTED, LVIS_DROPHILITED | LVIS_SELECTED);

	SetListCtrl(&m_ListOperateSteps);
	//初始化子界面
	m_mapDlg.clear();
	m_dlgInspectType.Create(CInspectTypeDlg::IDD,&m_AreaSet);
	m_mapDlg[DLG_InspectType] = &m_dlgInspectType;
	m_pCurrentDlg = m_mapDlg[DLG_InspectType];
	m_dlgDeviceType.Create(CDviceTypeDlg::IDD,&m_AreaSet);
	m_mapDlg[DLG_DeviceType] = &m_dlgDeviceType;
	m_dlgPotocolType.Create(CProtocolTypeDlg::IDD,&m_AreaSet);
	m_mapDlg[DLG_PotocolType] = &m_dlgPotocolType;
	m_dlgTestTemplate.Create(CTestTemplateDlg::IDD,&m_AreaSet);
	m_mapDlg[DLG_TestTemplate] = &m_dlgTestTemplate;
	/////////////////////初始化开始数据  使用装置类型默认第一个作为ID
	m_dlgTestTemplate.UpdateList(m_dlgDeviceType.GetDevID());
	///////////////////

	m_dlgDeviceIPInspect.Create(CDeviceIPInspect::IDD,&m_AreaSet);
	m_mapDlg[DLG_DeviceIPInspect] = &m_dlgDeviceIPInspect;
	SetCurrentDlg(DLG_InspectType,DLG_DeviceType);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CNewTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNewTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNewTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

int CNewTestDlg::SetCurrentIndex(int nBtnFlag)
{
	int nCurrentIndex = 0;
	int nLastIndex = 0;
	for (int i = 0;i < DLG_NUM;i++)
	{
		if(m_mapDlg[i] == m_pCurrentDlg)
		{
			nLastIndex = i;
			if(nBtnFlag == -1)
			{
				return nLastIndex;
			}
			if(nBtnFlag == 1)
			{
				if(i == DLG_InspectType)
				{
					return -1;
				}
				nCurrentIndex = i -1;
			}
			if(nBtnFlag == 2)
			{
				if(i == (DLG_NUM - 1))
				{
					return -1;
				}
				nCurrentIndex = i+1;
			}
			break;
		}
	}
	SetCurrentDlg(nCurrentIndex,nLastIndex);
	return -1;
}

void CNewTestDlg::SetCurrentDlg(int nCurrentIndex,int nLastIndex)
{
	for (int i = 0;i < DLG_NUM;i++)
	{
		if(i == nCurrentIndex)
		{
			m_mapDlg[i]->ShowWindow(SW_SHOW);
			m_pCurrentDlg = m_mapDlg[i];

			if(nCurrentIndex == DLG_TestTemplate)
			{
				CTestTemplateDlg*  pTempDlg = dynamic_cast<CTestTemplateDlg*>(m_pCurrentDlg);
				CDviceTypeDlg*  pDeviceDlg = dynamic_cast<CDviceTypeDlg*>(m_mapDlg[DLG_DeviceType]);
				pTempDlg->UpdateList(pDeviceDlg->GetDevID());
			}
		}
		else
		{
			m_mapDlg[i]->ShowWindow(SW_HIDE);
		}
	}
	
	SetListSelectRow(nCurrentIndex,nLastIndex);

	if(nCurrentIndex == DLG_InspectType)
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(false);
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(true);
	}
	else if(nCurrentIndex == (DLG_NUM - 1))
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(true);
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(false);	
	}
	else
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(true);
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(true);
	}

	if(nCurrentIndex != (DLG_NUM - 1) && nLastIndex == (DLG_NUM - 1))
	{
		GetDlgItem(IDC_BTN_BACKPAGE)->SetWindowTextA(_T("上一页"));
		GetDlgItem(IDC_BTN_NEXTPAGE)->SetWindowTextA(_T("下一页"));
	}
	else if(nCurrentIndex == (DLG_NUM - 1) && nLastIndex != (DLG_NUM - 1))
	{
		GetDlgItem(IDC_BTN_BACKPAGE)->SetWindowTextA(_T("检测IP"));
		GetDlgItem(IDC_BTN_NEXTPAGE)->SetWindowTextA(_T("开始测试"));
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
	}
}

int CNewTestDlg::ShowKeyTipBox(CString strResult)
{
	int nRes = MessageBox(("是否保存当前步骤选择的答案"),("询问"),MB_YESNO);
	ConfirmResultAnswer(nRes);
	//g_pAudioTestDlg->m_bIsAudioFlag = false;
	return nRes;

}

void CNewTestDlg::ConfirmResultAnswer(int nConfirmFlg)
{
	CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
	if(nConfirmFlg)
	{
		pDlg->GetCurrentResult();
	}
	else
	{
		pDlg->SetCurrentResult();
	}
}

void CNewTestDlg::OnBnClickedBtnNext()
{
	if(g_pAudioListener->m_bStartParse || g_pAudioListener->m_nWholeFlag == Flag_StarTest
		|| g_pAudioListener->m_nWholeFlag == Flag_StopTest)
	{
		return;
	}

	if(!g_pAudioTestDlg->m_bIsAudioFlag)
	{
		//ShowKeyTipBox();
		if(ShowKeyTipBox() == IDNO)
		{
			g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
			return;
		}
		CString strNextTipId = g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_pCurrentTipWord->m_strTip_Word_Id;
		g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(strNextTipId,Flag_Flow_OK);
		g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
	}
	g_pAudioTestDlg->m_bIsAudioFlag = false;
	SetCurrentIndex(2);

	g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = "";
	int nItem = GetCurrentSelectRow();
	if(nItem > 0)
	{
		g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = *((CString*)m_ListOperateSteps.GetItemData((nItem-1)));
	}
}

void CNewTestDlg::OnBnClickedBtnBack()
{
	if(g_pAudioListener->m_bStartParse || g_pAudioListener->m_nWholeFlag == Flag_StarTest
		|| g_pAudioListener->m_nWholeFlag == Flag_StopTest)
	{
		return;
	}
	if(!g_pAudioTestDlg->m_bIsAudioFlag)
	{
		//ShowKeyTipBox();
		if(ShowKeyTipBox() == IDNO)
		{
			g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
			return;
		}
		CString strUpTipId = g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId;
		g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(strUpTipId,Flag_Flow_OK);
		g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
	}
	SetCurrentIndex(1);
	g_pAudioTestDlg->m_bIsAudioFlag = false;

	g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = "";
	int nItem = GetCurrentSelectRow();
	if(nItem > 0)
	{
		g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = *((CString*)m_ListOperateSteps.GetItemData((nItem-1)));
	}
}

void CNewTestDlg::OnNMDblclkListOperateSteps(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(g_pAudioListener->m_bStartParse || g_pAudioListener->m_nWholeFlag == Flag_StarTest
		|| g_pAudioListener->m_nWholeFlag == Flag_StopTest)
	{
		return;
	}
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}

	if(!g_pAudioTestDlg->m_bIsAudioFlag)
	{
		if(ShowKeyTipBox() == IDNO)
		{
			g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
			return;
		}
	}

	CString strCurrentTipId = *((CString*)m_ListOperateSteps.GetItemData(pNMItemActivate->iItem));
	g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(strCurrentTipId,Flag_Flow_OK);
	g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;
	//g_pAudioListener->m_nWholeFlag = Flag_TipWord;

	g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = "";
	if(pNMItemActivate->iItem > 0)
	{
		g_pAudioListener->m_pAudioParser->m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId = *((CString*)m_ListOperateSteps.GetItemData((pNMItemActivate->iItem-1)));
	}

	int nLastIndex = SetCurrentIndex(-1);
	SetCurrentDlg(pNMItemActivate->iItem,nLastIndex);
 	*pResult = 0;
}

void CNewTestDlg::OnNMClickListoperatesteps(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnNMDblclkListOperateSteps(pNMHDR,pResult);
	*pResult = 0;
}

void CNewTestDlg::OnBnClickedBtnReturn()
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}
	CString strVoiceTip = "";
	if(g_pAudioListener->m_nWholeFlag == Flag_StarTest)
	{
		if(g_pAudioTestDlg->m_bIsAudioFlag)
		{
			strVoiceTip = _T("正在进行测试中，无法返回主界面");
			g_pAudioTestDlg->m_pAudioParser->CreateVoice(strVoiceTip);
		}
		g_pAudioTestDlg->m_bIsAudioFlag = false;
		return;
	}
	
	g_pAudioTestDlg->m_bIsAudioFlag = false;
	//g_pAudioListener->m_nWholeFlag = Flag_Flow;
	//g_pAudioListener->m_nTipWordFlag = Flag_Question_NULL;

	g_pAudioTestDlg->ReturnNewTestUI();
}

void CNewTestDlg::OnBnClickedBtnBackpage()
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}
	bool bRet = false;
	if(SetCurrentIndex(-1) == DLG_DeviceIPInspect)
	{
		CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 正在检测IP，请稍后！"));
		bRet = pDlg->DealAnswer();
		if(!bRet)
		{
			CString str = _T("请重新输入IP，IP不在局域网内");
			if(!g_pAudioTestDlg->m_bIsAudioFlag)
			{
				MessageBox(("请重新输入IP，IP不在局域网内"),("提示"),MB_OK);
			}
			else
			{
				//CLogPrint::LogString(XLOGLEVEL_INFOR,"请重新输入IP，IP不在局域网内");
				CString str = _T("请重新输入IP，IP不在局域网内");
				g_pAudioTestDlg->m_pAudioParser->CreateVoice(str);
			}
			g_pAudioListener->m_nTipWordFlag = Flag_TW_Question;

			////测试时 IP 不通过，也可以启动测试，测试功能
			GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(true);
			g_pAudioListener->m_nTipWordFlag = Flag_AnswerWait;
			g_pAudioListener->m_nWholeFlag = Flag_TestWait;

			return;
		}
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(true);
		//if(m_bIsAudioFlag)
		{
			CString str = _T("IP检测成功，现在可以开始测试了");
			g_pAudioTestDlg->m_pAudioParser->CreateVoice(str);
		}
		g_pAudioTestDlg->m_bIsAudioFlag = false;
		
		//CLogPrint::LogString(XLOGLEVEL_INFOR,"IP 检测成功");
		//IP 检测成功才可以 创建测试
		//GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(true);
		g_pAudioListener->m_nTipWordFlag = Flag_AnswerWait;
		g_pAudioListener->m_nWholeFlag = Flag_TestWait;
	}
	else
	{
		CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
		pDlg->SetBackPage();
		m_pCurrentDlg->Invalidate();
		m_pCurrentDlg->UpdateWindow();
	}
}

void CNewTestDlg::OnBnClickedBtnNextpage()
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}
	if(SetCurrentIndex(-1) == DLG_DeviceIPInspect)
	{
		//开始测试
		if(!g_pAudioTestDlg->m_bIsAudioFlag)
		{
			int nRes = MessageBox(("是否开始测试？"),("询问"),MB_YESNO);
			if(nRes == IDYES)
			{
				g_pAudioTestDlg->CreateTest();
			}
			else
			{
				return;
			}
		}
		else
		{
			g_pAudioTestDlg->CreateTest();
		}
		g_pAudioListener->m_nTipWordFlag = Flag_Question_NULL;
		g_pAudioListener->m_nWholeFlag = Flag_StarTest;
		g_pAudioTestDlg->m_bIsAudioFlag = false;
	}
	else
	{
		CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
		pDlg->SetNextPage();
		m_pCurrentDlg->Invalidate();
		m_pCurrentDlg->UpdateWindow();
	}
}

bool CNewTestDlg::DealAnswer(CString strResult)
{
	CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
	pDlg->FindSelectAnswer(strResult);
	return true;
}

CString CNewTestDlg::GetResultAnswer(int nDlgType)
{
	CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_mapDlg[nDlgType]);
	return pDlg->GetResult();
}

CString CNewTestDlg::GetPath()
{
	CDviceTypeDlg*  pDeviceDlg = dynamic_cast<CDviceTypeDlg*>(m_mapDlg[DLG_DeviceType]);
	return pDeviceDlg->GetDevID();
}

CString CNewTestDlg::GetCurrentResultAnswer()
{
	CAudioDlgBase*  pDlg = dynamic_cast<CAudioDlgBase*>(m_pCurrentDlg);
	return pDlg->GetCurrentResult();
}