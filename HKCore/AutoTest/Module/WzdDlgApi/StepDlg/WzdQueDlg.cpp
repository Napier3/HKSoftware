// D:\WorkAts\Source\AutoTest\Module\WzdDlgApi\StepDlg\WzdQueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "../../../iSmartTestWzd/iSmartTestWzdDlg.h"
#include "../../../AutoTest/Module/XSttAtsTestClientImp.h"
#include "WzdQueDlg.h"
#include "MessageDlg.h"


// CWzdQueDlg 对话框

IMPLEMENT_DYNAMIC(CWzdQueDlg, CDialog)

CWzdQueDlg::CWzdQueDlg(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdQueDlg::IDD, pParent)
, m_bQueWhere(false)
, m_sQueZZMS(_T(""))
, m_sQueZZXH(_T(""))
, m_sQueStartTime(COleDateTime::GetCurrentTime())
, m_sQueEndTime(COleDateTime::GetCurrentTime())
{
	m_pSelFileM = NULL;
}

CWzdQueDlg::~CWzdQueDlg()
{
	m_TempFileM.DeleteAll();
}

void CWzdQueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_txtTitle);
	DDX_Control(pDX, IDC_ICON_MAIN, m_btnIcon);
	DDX_Control(pDX, IDC_MAIN_BOTTOM, m_btnBottom);	

	DDX_Control(pDX, IDC_TREE_FILE, m_treeFile);

	DDX_Control(pDX, IDC_STATIC_QueTJ, m_sQueTJ);
	DDX_Control(pDX, IDC_STATIC_RECORD, m_sRecord);
	DDX_Control(pDX, IDC_STATIC_STATICTIME, m_sTimeFG);

	DDX_Control(pDX, IDC_CHECK_ZZMS, m_CheckZZMS);
	DDX_Control(pDX, IDC_CHECK_ZZXH, m_CheckZZXH);
	DDX_Control(pDX, IDC_CHECK_JYSJ, m_CheckJYSJ);

	DDX_Control(pDX, IDC_EDIT_ZZMS, m_editZZMS);
	DDX_Control(pDX, IDC_EDIT_ZZXH, m_editZZXH);

	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME, m_startTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME, m_endTime);

	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btnQueAll);
	DDX_Control(pDX, IDC_BUTTON_QUE, m_btnQueWhere);

	DDX_Control(pDX, IDD_DATA_SHOW, m_DataShow);

	DDX_Control(pDX, IDC_BTN_PREV, m_btnReturn);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_MAIN_BORDER, m_grpBorder);
	DDX_Text(pDX, IDC_EDIT_ZZMS, m_sQueZZMS);
	DDX_Text(pDX, IDC_EDIT_ZZXH, m_sQueZZXH);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_sQueStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDTIME, m_sQueEndTime);
}


BEGIN_MESSAGE_MAP(CWzdQueDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PREV, &CWzdQueDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_DEL, &CWzdQueDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CWzdQueDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CWzdQueDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_QUE, &CWzdQueDlg::OnBnClickedButtonQue)
	ON_MESSAGE(WM_USER + 1003, &CWzdQueDlg::OnGridSelChange)
END_MESSAGE_MAP()


// CWzdQueDlg 消息处理程序
void CWzdQueDlg::OnInitialUpdate()
{
	XUI_InitAdjust();
	InitBtns();

	m_DataShow.InitGrid();

	InitLoadFileData();
}

void CWzdQueDlg::InitLoadFileData()
{
	CString strRootPath = _P_GetWorkspacePath();

	m_FileMngr.m_strName = "检验记录";	
	m_FileMngr.SetRootPath(strRootPath);
	m_FileMngr.Research(TRUE, TRUE);

	m_treeFile.ShowXFileMngr(&m_FileMngr);

	HTREEITEM rootItem = m_treeFile.GetRootItem();
	ExpandTreeItem(rootItem);
}

void CWzdQueDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
 	XUI_AddWnd(&m_txtTitle, 0, 0, 1, 0);
 	XUI_AddWnd(&m_btnIcon, 0, 0, 0, 0);
	XUI_AddWnd(&m_btnBottom, 0, 1, 1, 0);

	float iMove = 0.2;
	XUI_AddWnd(&m_treeFile, 0, 0, iMove, 1);

	XUI_AddWnd(&m_sQueTJ, iMove, 0, 1-iMove, 0);

	XUI_AddWnd(&m_sTimeFG, iMove, 0, 0, 0);
	XUI_AddWnd(&m_CheckZZMS, iMove, 0, 0, 0);
	XUI_AddWnd(&m_CheckZZXH, iMove, 0, 0, 0);
	XUI_AddWnd(&m_CheckJYSJ, iMove, 0, 0, 0);
	XUI_AddWnd(&m_editZZMS, iMove, 0, 0, 0);
	XUI_AddWnd(&m_editZZXH, iMove, 0, 0, 0);
	XUI_AddWnd(&m_startTime, iMove, 0, 0, 0);
	XUI_AddWnd(&m_endTime, iMove, 0, 0, 0);
	XUI_AddWnd(&m_btnQueAll, iMove, 0, 0, 0);
	XUI_AddWnd(&m_btnQueWhere, iMove, 0, 0, 0);
	
	XUI_AddWnd(&m_sRecord, iMove, 0, 1-iMove, 1);
	XUI_AddWnd(&m_DataShow, iMove, 0, 1-iMove, 1);

 	XUI_AddWnd(&m_btnReturn, 0, 1, 0.1, 0);
 	XUI_AddWnd(&m_btnDelete, 0.3, 1, 0.1, 0);
	XUI_AddWnd(&m_btnOpen, 0.6, 1, 0.1, 0);

	XUI_AddWnd(&m_grpBorder, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdQueDlg::InitBtns()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
 	m_btnIcon.LoadImage(strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg");
 	m_btnIcon.SetImgMode(TRUE);

	m_txtTitle.LoadImage(strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png");
	m_txtTitle.SetImgMode(TRUE);

	m_btnBottom.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");
	m_btnBottom.SetImgMode(TRUE);
}

//20230621 huangliang 只展开各节点下第一组数据
void CWzdQueDlg::ExpandTreeItem(HTREEITEM rootItem)
{
	HTREEITEM childItem = m_treeFile.GetChildItem(rootItem);
	if(childItem != NULL)
	{
		m_treeFile.SelectItem(childItem);
		m_treeFile.Expand(childItem, TVE_EXPAND);

		ExpandTreeItem(childItem);
	}
}

void CWzdQueDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdQueDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_EntrySel);
}

void CWzdQueDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CXFile *pxFile = (CXFile*)m_DataShow.GetCurrCellData();
	if (pxFile == NULL)
	{
		MessageDlg::MessageBox("错误", "请选择需要删除的检测记录", MessageDlg::ERRYES);
		return;
	}

	if( MessageDlg::MessageBox("删除检验记录", "删除检验记录后无法找回，请确认", MessageDlg::YESANDNO) != IDOK )
	{
		return ;
	}

	CXFolder* pParent = (CXFolder*)pxFile->GetParent();
	if(pParent == NULL)
		return;

	CString strSelID = pxFile->m_strID;
	strSelID.Replace(_T(".gbrpt"), _T(""));

	//需删除本次记录的多个文件
	//删除.gbrpt文件
	pxFile->DeleteFileA();
	pParent->Delete(pxFile);

	//删除同一检测记录其他文件
	CExBaseObject* pObj = NULL;
	CXFile* pDelFile = NULL;
	POS pos = pParent->GetHeadPosition();
	while (pos != NULL)
	{
		pObj = pParent->GetNext(pos);
		if(pObj->GetClassID() == CLASSID_XFILE)
		{
			pDelFile = (CXFile*)pObj;
			int p = pDelFile->m_strID.Find(strSelID);
			if(p != -1)
			{
				pDelFile->DeleteFileA();
				pParent->Delete(pDelFile);
			}
		}
	}
	
	QueRecordData();
}

void CWzdQueDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CXFile *pxFile = (CXFile*)m_DataShow.GetCurrCellData();
	if (pxFile == NULL)
	{
		MessageDlg::MessageBox("错误", "请选择需要打开的检测记录", MessageDlg::ERRYES);
		return;
	}

	if( MessageDlg::MessageBox("打开检验记录", "打开检验记录默认使用创建时保存的设置，请确认", MessageDlg::YESANDNO) != IDOK )
	{
		return ;
	}

	CXFolder* pParent = (CXFolder*)pxFile->GetParent();
	if(pParent == NULL)
	{
		MessageDlg::MessageBox("错误", "文件异常，未找到路径", MessageDlg::ERRYES);
		return ;
	}

	//通知测试程序
	CString strPath = pParent->GetFolderPath() + pxFile->m_strName;
	g_pISmartTestWzdDlg->OpenGbRptFile(strPath);
}

void CWzdQueDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bQueWhere = false;

	m_sQueZZMS = _T("");
	m_sQueZZXH = _T("");

	m_CheckZZMS.SetCheck(0);
	m_CheckZZXH.SetCheck(0);
	m_CheckJYSJ.SetCheck(0);

	UpdateData(FALSE);

	QueRecord();
}

void CWzdQueDlg::OnBnClickedButtonQue()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bQueWhere = true;
	QueRecord();
}

BOOL CWzdQueDlg::CheckWhereData()
{
	UpdateData(TRUE);

	if(!m_bQueWhere)
	{
		m_sQueZZMS = _T("");
		m_sQueZZXH = _T("");
		return TRUE;
	}

	if(m_CheckZZMS.GetCheck() == 0)
	{
		m_sQueZZMS = _T("");
	}
	else
	{
		if(m_sQueZZMS == _T(""))
		{
			MessageDlg::MessageBox("错误", "装置描述不可为空", MessageDlg::ERRYES);
			return FALSE;
		}
	}

	if(m_CheckZZXH.GetCheck() == 0)
	{
		m_sQueZZXH = _T("");
	}
	else
	{
		if(m_sQueZZXH == _T(""))
		{
			MessageDlg::MessageBox("错误", "装置型号不可为空", MessageDlg::ERRYES);
			return FALSE;
		}
	}
	return TRUE;
}
void CWzdQueDlg::QueRecord()
{
	//判断过滤条件是否合格
	if(!CheckWhereData())
	{
		return ;
	}

	QueRecordData();
}
void CWzdQueDlg::QueRecordData()
{
	//获取左侧文件夹对象
	CXFileMngr* pSelFileM = (CXFileMngr*)m_treeFile.GetSelObject();
	if(pSelFileM == NULL)
	{
		if(m_pSelFileM == NULL)
		{
			MessageDlg::MessageBox("错误", "请选择左侧路径", MessageDlg::ERRYES);
			return ;
		}
		pSelFileM = m_pSelFileM;
	}
	m_pSelFileM = pSelFileM;

	//开始查询数据
	m_TempFileM.DeleteAll();
	FindAllFile(pSelFileM);

	m_TempFileM.Sort(false);
	m_DataShow.ShowDatas(&m_TempFileM);
}

void CWzdQueDlg::FindAllFile(CXFileMngr* pSelFileM)
{
	CExBaseObject* pObj = NULL;
	CXFile* pFile = NULL;
	POS pos = pSelFileM->GetHeadPosition();
	while (pos != NULL)
	{
		pObj = pSelFileM->GetNext(pos);
		if(pObj->GetClassID() == CLASSID_XFOLDER)		//文件夹
		{
			FindAllFile((CXFileMngr*)pObj);
		}
		else if(pObj->GetClassID() == CLASSID_XFILE)
		{
			pFile = (CXFile*)pObj;
			CXFolder* pParent = (CXFolder*)pObj->GetParent();
			if(pParent == NULL)
				continue;

			CWzdFile* pwzdFile = new CWzdFile;
			pFile->CopyOwn(pwzdFile);	
			pwzdFile->m_pFile = pFile;
			if(!pwzdFile->ProssData(pParent->GetFolderPath()))
			{
				delete pwzdFile;
				pwzdFile = NULL;
				continue;
			}

			//过滤数据
			if(m_bQueWhere)
			{
				if(!pwzdFile->CheckValue(m_sQueZZMS, m_sQueZZXH))
				{
					delete pwzdFile;
					pwzdFile = NULL;
					continue;
				}

				if(m_CheckJYSJ.GetCheck() != 0)
				{
					if(!pwzdFile->CheckTime(m_sQueStartTime, m_sQueEndTime))
					{
						delete pwzdFile;
						pwzdFile = NULL;
						continue;
					}	
				}
			}

			m_TempFileM.AddNewChild(pwzdFile);
		}
	}
}

LRESULT CWzdQueDlg::OnGridSelChange(WPARAM wParam, LPARAM lParam)
{
	//ShowDataToGrid();
	return 0;
}

void CWzdQueDlg::ShowDataToGrid()
{
	CXFile *pxFile = (CXFile*)m_DataShow.GetCurrCellData();
	if (pxFile == NULL)
	{
		return ;
	}
}