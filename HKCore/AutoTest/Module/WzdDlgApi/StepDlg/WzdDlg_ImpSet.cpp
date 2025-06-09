#include "stdafx.h"
#include "WzdDlg_ImpSet.h"
#include "WzdDlg_TestSenceSel.h"
#include "WzdMainDlg.h"
#include "MessageDlg.h"
#include "SelTable.h"

IMPLEMENT_DYNAMIC(CWzdDlg_ImpSet, CDialog)

CWzdDlg_ImpSet::CWzdDlg_ImpSet(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_ImpSet::IDD, pParent)
{
	m_nSetsType = 0;
	m_bFileType = TRUE;
	m_strTipMsg = _T("");
}

CWzdDlg_ImpSet::~CWzdDlg_ImpSet()
{
}

void CWzdDlg_ImpSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_PDF_DVM, m_gridDsFile);
	DDX_Text(pDX, IDC_EDIT_REAL_CAL_MD5_PARA, m_strRealCalMd5_Parameter);
	DDX_Text(pDX, IDC_EDIT_READ_FROM_FILE_MD5_PARA, m_strReadFromFileMd5_Parameter);
	DDX_Text(pDX, IDC_EDIT_RSLT, m_strRslt);
	DDX_Control(pDX, IDC_EDIT_REAL_CAL_MD5_PARA, m_edtRealCalMd5_Parameter);
	DDX_Control(pDX, IDC_EDIT_READ_FROM_FILE_MD5_PARA, m_edtReadFromFileMd5_Parameter);
	DDX_Control(pDX, IDC_EDIT_RSLT, m_edtRslt);
	DDX_Control(pDX, IDC_STATIC_MD5_REAL_PARA, m_stcMd5Real_Parameter);
	DDX_Control(pDX, IDC_STATIC_MD5_FROMFILE_PARA, m_stcMd5FromFile_Parameter);
	DDX_Control(pDX, IDC_STATIC_RSLT, m_stcRslt);
	DDX_Control(pDX, IDC_STATIC_FROM_FILE, m_stcFromFile);
	DDX_Control(pDX, IDC_STATIC_REAL_CAL, m_stcRealCal);
	DDX_Control(pDX, IDC_STATIC_MD5_FROMFILE_SETTING, m_stcMd5FromFile_Setting);
	DDX_Control(pDX, IDC_STATIC_MD5_FROMFILE_ENA, m_stcMd5FromFile_Ena);
	DDX_Control(pDX, IDC_STATIC_MD5_REAL_SETTING, m_stcMd5Real_Setting);
	DDX_Control(pDX, IDC_STATIC_MD5_REAL_ENA, m_stcMd5Real_Ena);
	DDX_Control(pDX, IDC_EDIT_READ_FROM_FILE_MD5_SETTING, m_edtReadFromFileMd5_Setting);
	DDX_Control(pDX, IDC_EDIT_READ_FROM_FILE_MD5_ENA, m_edtReadFromFileMd5_Ena);
	DDX_Text(pDX, IDC_EDIT_READ_FROM_FILE_MD5_SETTING, m_strReadFromFileMd5_Setting);
	DDX_Text(pDX, IDC_EDIT_READ_FROM_FILE_MD5_ENA, m_strReadFromFileMd5_Ena);
	DDX_Control(pDX, IDC_EDIT_REAL_CAL_MD5_SETTING, m_edtRealCalMd5_Setting);
	DDX_Control(pDX, IDC_EDIT_REAL_CAL_MD5_ENA, m_edtRealCalMd5_Ena);
	DDX_Text(pDX, IDC_EDIT_REAL_CAL_MD5_SETTING, m_strRealCalMd5_Setting);
	DDX_Text(pDX, IDC_EDIT_REAL_CAL_MD5_ENA, m_strRealCalMd5_Ena);
	DDX_Control(pDX, IDC_TAB_PDF_DVM, m_tabPdfDvm);
	DDX_Control(pDX, IDC_BUTTON_CORRECT, m_btnCorrect);
	DDX_Control(pDX, IDC_BUTTON_TIMEUNIT, m_TimeUnit);
}

void CWzdDlg_ImpSet::OnInitialUpdate()
{
	XUI_InitAdjust();

	m_gridDsFile.InitGrid();

	m_tabPdfDvm.InsertItem(0, _T("装置参数"));
	m_tabPdfDvm.InsertItem(1, _T("保护压板"));
	m_tabPdfDvm.InsertItem(2, _T("保护定值"));
	m_tabPdfDvm.SetCurSel(0);
}


void CWzdDlg_ImpSet::ShowSets_Pdf()
{
	CDvmDataset *pSrcDatast = NULL;
	CDataSet *pGbDataset = NULL;

	switch (m_nSetsType )
	{
	case 0:
		m_oStesFilePdfTool.GetDataset(SETS_TITLE_ID_PARAMETER, SETS_TITLE_ID_PARAMETER, &pSrcDatast, &pGbDataset);
		break;
	case 1:
		m_oStesFilePdfTool.GetDataset(SETS_TITLE_ID_ENA, SETS_TITLE_ID_ENA, &pSrcDatast, &pGbDataset);
		break;
	case 2:
		m_oStesFilePdfTool.GetDataset(SETS_TITLE_ID_SETTING, SETS_TITLE_ID_SETTING, &pSrcDatast, &pGbDataset);
		break;
	default:
		break;
	}

	//20230808 huangliang 以模板数据为基准显示
	m_gridDsFile.m_pDataset = pGbDataset;
	m_gridDsFile.m_pDvmDataset = pSrcDatast;
	m_gridDsFile.ShowDatas(pGbDataset);
	//m_gridDsFile.ShowDatas(pSrcDatast);

	GetRslt_Pdf(pGbDataset);
	m_strReadFromFileMd5_Parameter = _T("无数据");
	m_strRealCalMd5_Parameter = _T("无数据");
	m_strReadFromFileMd5_Setting = _T("无数据");
	m_strRealCalMd5_Setting = _T("无数据");
	m_strReadFromFileMd5_Ena = _T("无数据");
	m_strRealCalMd5_Ena = _T("无数据");
	UpdateData(FALSE);
}

void CWzdDlg_ImpSet::ShowSets_Xml()
{
	CDvmDataset *pSrcDatast = NULL;
	CDataSet *pGbDataset = NULL;

	switch (m_nSetsType )
	{
	case 0:
		m_oSetsFileXmlTool.GetDataset(SETS_TITLE_ID_PARAMETER, SETS_TITLE_ID_PARAMETER, &pSrcDatast, &pGbDataset);
		pSrcDatast = m_oSetsFileXmlTool.GetSetsByID(SETTING_CLASS_PARAMETER);
		break;
	case 1:
		m_oSetsFileXmlTool.GetDataset(SETS_TITLE_ID_ENA, SETS_TITLE_ID_ENA, &pSrcDatast, &pGbDataset);
		pSrcDatast = m_oSetsFileXmlTool.GetSetsByID(SETTING_CLASS_RELAYENA);
		break;
	case 2:
		m_oSetsFileXmlTool.GetDataset(SETS_TITLE_ID_SETTING, SETS_TITLE_ID_SETTING, &pSrcDatast, &pGbDataset);
		pSrcDatast = m_oSetsFileXmlTool.GetSetsByID(SETTING_CLASS_SETTING);
		break;
	default:
		break;
	}

	m_gridDsFile.m_pDataset = pGbDataset;
	m_gridDsFile.ShowDatas(pSrcDatast);
	UpdateData(FALSE);
}

void CWzdDlg_ImpSet::GetRslt_Xml()
{
	CString strRslt;
	if (m_strReadFromFileMd5_Parameter != m_strRealCalMd5_Parameter)
	{
		//m_strRslt = _T("哈希值校验失败！【装置参数】实际计算的哈希值与文件中的不一致");
		strRslt.AppendFormat(_T("%s"), _T("【装置参数】"));
	}
	if (m_strReadFromFileMd5_Setting != m_strRealCalMd5_Setting)
	{
		//m_strRslt = _T("哈希值校验失败！【保护定值】实际计算的哈希值与文件中的不一致");
		strRslt.AppendFormat(_T("%s"), _T("【保护定值】"));
	}
	if (m_strReadFromFileMd5_Ena != m_strRealCalMd5_Ena)
	{
		//m_strRslt = _T("哈希值校验失败！【保护压板】实际计算的哈希值与文件中的不一致");
		strRslt.AppendFormat(_T("%s"), _T("【保护压板】"));
	}

	if (strRslt.GetLength() > 0)
	{
		m_strRslt.Format(_T("【校验失败！】哈希值校验失败！%s 实际计算的哈希值与文件中的不一致"), strRslt);
	}
	else
		m_strRslt = _T("【校验成功！】哈希值校验成功！实际计算的哈希值与文件中的一致");
}

void CWzdDlg_ImpSet::GetRslt_Pdf(CDataSet *pGbDataset)
{
	if (pGbDataset == NULL)
	{
		m_strRslt = _T("【无法校验！】当前选中的数据集为空");
		return;
	}

	POS pos = pGbDataset->GetHeadPosition();

	while (pos != NULL)
	{
		CDataObj *pData = (CDataObj *)pGbDataset->GetNext(pos);

		if (pData->m_strValue.IsEmpty() || !IsStringNumber(pData->m_strValue))
		{
			m_strRslt = _T("【校验失败！】当前选中的数据集，存在数据的值包含中文或特殊字符！");
			return;
		}
	}

	m_strRslt = _T("【校验成功！】当前选中的数据集，所有数据的值均为整数或小数！");
}

void CWzdDlg_ImpSet::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_gridDsFile, 0.0f, 0.0f, 1.0f, 1.0f);

	XUI_AddWnd(&m_stcFromFile, 0.0f, 1.0f, 0.5f, 0.0f);
	XUI_AddWnd(&m_stcRealCal, 0.5f, 1.0f, 0.5f, 0.0f);

	XUI_AddWnd(&m_btnCorrect, 0, 1.0f, 0.0f, 0.0f);
	XUI_AddWnd(&m_TimeUnit, 0, 1.0f, 0.0f, 0.0f);

	XUI_AddWnd(&m_stcMd5FromFile_Parameter, 0, 1.0, 0.0f, 0.0f);
	XUI_AddWnd(&m_stcMd5FromFile_Setting, 0, 1.0, 0.0f, 0.0f);
	XUI_AddWnd(&m_stcMd5FromFile_Ena, 0, 1.0, 0.0f, 0.0f);

	XUI_AddWnd(&m_edtReadFromFileMd5_Parameter, 0, 1.0, 0.50f, 0.0f);
	XUI_AddWnd(&m_edtReadFromFileMd5_Setting, 0, 1.0, 0.50f, 0.0f);
	XUI_AddWnd(&m_edtReadFromFileMd5_Ena, 0, 1.0, 0.50f, 0.0f);

	XUI_AddWnd(&m_stcMd5Real_Parameter, 0.5, 1.0, 0.0f, 0.0f);
	XUI_AddWnd(&m_stcMd5Real_Setting, 0.5, 1.0, 0.0f, 0.0f);
	XUI_AddWnd(&m_stcMd5Real_Ena, 0.5, 1.0, 0.0f, 0.0f);

	XUI_AddWnd(&m_edtRealCalMd5_Parameter, 0.5, 1.0, 0.50f, 0.0f);
	XUI_AddWnd(&m_edtRealCalMd5_Setting, 0.5, 1.0, 0.50f, 0.0f);
	XUI_AddWnd(&m_edtRealCalMd5_Ena, 0.5, 1.0, 0.50f, 0.0f);

	XUI_AddWnd(&m_stcRslt, 0, 1.0, 0.0f, 0.0f);
	XUI_AddWnd(&m_edtRslt, 0, 1.0, 1.0f, 0.0f);

	XUI_AddWnd(&m_tabPdfDvm, 0.0f,0.0f, 1.0f, 0.0f);

	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdDlg_ImpSet::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{

}

void CWzdDlg_ImpSet::SetFileType(BOOL bIsXml)
{
	m_bFileType = bIsXml;
}

void CWzdDlg_ImpSet::SetFilePath(const CString& strFile)
{
	m_strSetsFile = strFile;
}

void CWzdDlg_ImpSet::GetMd5(CString& strParameterMd5, CString& strSettingMd5, CString& strEnaMd5)
{
	strParameterMd5 = m_strRealCalMd5_Parameter;
	strSettingMd5 = m_strRealCalMd5_Setting;
	strEnaMd5 = m_strRealCalMd5_Ena;
}

BOOL CWzdDlg_ImpSet::CheckSetsFileFormat()
{
	if (m_bFileType)
	{
		if (m_strSetsFile.Find(_T("xml")) < 0)
		{
			return FALSE;
		}
	}
	else
	{
		if (m_strSetsFile.Find(_T("pdf")) < 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CWzdDlg_ImpSet::UpdateFileSelected(bool bCorrect)
{
	if (m_strSetsFile.IsEmpty() ||(!IsFileExist(m_strSetsFile)))
	{
		return;
	}

	if (!CheckSetsFileFormat())
	{
		MessageDlg::MessageBox("错误", "定值单格式不正确！\r\n请返回重新选择定值单文件！", MessageDlg::ERRYES);
		return;
	}

	CDevice *pDevice = (CDevice*)g_pWzdMainDlg->m_oGuideBook.GetDevice();
	if (m_bFileType)
	{
		m_oSetsFileXmlTool.SetCpus(pDevice->GetCpus());
		if(!m_oSetsFileXmlTool.ImportFile(m_strSetsFile))
		{
			return;
		}

		m_oSetsFileXmlTool.GetMd5_FromCal(SETTING_CLASS_PARAMETER, m_strRealCalMd5_Parameter);
		m_oSetsFileXmlTool.GetMd5_FromCal(SETTING_CLASS_SETTING, m_strRealCalMd5_Setting);
		m_oSetsFileXmlTool.GetMd5_FromCal(SETTING_CLASS_RELAYENA, m_strRealCalMd5_Ena);

		m_oSetsFileXmlTool.GetMd5_FromFile(SETTING_CLASS_PARAMETER, m_strReadFromFileMd5_Parameter);
		m_oSetsFileXmlTool.GetMd5_FromFile(SETTING_CLASS_SETTING, m_strReadFromFileMd5_Setting);
		m_oSetsFileXmlTool.GetMd5_FromFile(SETTING_CLASS_RELAYENA, m_strReadFromFileMd5_Ena);
		GetRslt_Xml();
		ShowSets_Xml();
	}
	else
	{
		//20230728 huangliang 设置不修正状态
		m_oStesFilePdfTool.m_bCorrect = bCorrect;
		m_oStesFilePdfTool.SetCpus(pDevice->GetCpus());
		//20240312 huangliang
		SelTable tmpDlg;

		m_oStesFilePdfTool.SetManualConfirmInterface(&tmpDlg);
		m_oStesFilePdfTool.ImportFile(m_strSetsFile);

		//20230809 huangliang 解析PDF后先对比数据，再显示
		ContrastPdfData();

		ShowSets_Pdf();

		//20230809 huangliang 显示弹出框
		if(m_strTipMsg != _T(""))
		{
			MessageDlg::MessageBox("提示", m_strTipMsg, MessageDlg::YES);
		}
	}
}

void CWzdDlg_ImpSet::ContrastPdfData()
{
	m_strTipMsg = _T("校对结果如下：\n装置参数：");
	int iParameter = ContrastPdfData(SETS_TITLE_ID_PARAMETER);

	m_strTipMsg += _T("\n保护压板：");
	int iEna = ContrastPdfData(SETS_TITLE_ID_ENA);

	m_strTipMsg += _T("\n保护定值：");
	int iSettiong = ContrastPdfData(SETS_TITLE_ID_SETTING);
	if(iParameter == 0 && iEna == 0 && iSettiong == 0)
	{
		m_strTipMsg = _T("");
	}
}
int CWzdDlg_ImpSet::ContrastPdfData(CString strTilte)
{
	CDvmDataset *pSrcDatast = NULL;
	CDataSet *pGbDataset = NULL;
	m_oStesFilePdfTool.GetDataset(strTilte, strTilte, &pSrcDatast, &pGbDataset);

	int iFailCount = 0;
	POS pos = pGbDataset->GetHeadPosition();
	while (pos != NULL)
	{
		CDataObj* pData = (CDataObj *)pGbDataset->GetNext(pos);
		if(!ContrastData(pData, pSrcDatast, pGbDataset))
		{
			iFailCount++;
		}
	}

	int iAllCount = pGbDataset->GetCount();
	CString strResult;
	strResult.Format(_T("总计：%d；成功：%d；失败：%d；"), iAllCount, iAllCount-iFailCount, iFailCount);
	m_strTipMsg += strResult;
	return iFailCount;
}
BOOL CWzdDlg_ImpSet::ContrastData(CExBaseObject *pData, CDvmDataset *pSrcDatast, CDataSet *pGbDataset)
{
	CDataObj *pDataObj = (CDataObj *)pData;
	if(pData == NULL)
		return TRUE;
	if(pSrcDatast == NULL || pGbDataset == NULL)
	{
		pDataObj->m_strDefaultValue = _T("");
		return TRUE;
	}

	CDvmData *pDvmData = NULL;
	if(pGbDataset->m_strID == "Parameter" || pGbDataset->m_strID == "Ena")
	{
		POS pos = pSrcDatast->GetHeadPosition();
		while (pos != NULL)
		{
			CDvmData* pType = (CDvmData *)pSrcDatast->GetNext(pos);
			if (pType->m_strName == pDataObj->m_strName)
			{
				pDvmData = pType;
				break;
			}
		}
	}
	else
	{
		POS pos = pSrcDatast->GetHeadPosition();
		CExBaseList oListFind;
		while (pos != NULL)
		{
			CDvmData *p = (CDvmData *)pSrcDatast->GetNext(pos);
			if (p->m_strName == pDataObj->m_strName)
			{
				oListFind.AddTail(p);
			}
		}

		if(oListFind.GetCount() == 1)
		{
			pDvmData = (CDvmData*)oListFind.GetHead();
		}
		else
		{
			POS posType = oListFind.GetHeadPosition();
			while(posType)
			{
				CDvmData* pType = (CDvmData*)oListFind.GetNext(posType);
				if(pDataObj->m_strID.Find("mms") != -1)
				{
					if(pType->m_strUnit == "s" || pType->m_strUnit == "ms")
					{
						pDvmData = pType;
						break;
					}
				}
				else if(pDataObj->m_strID.Find("Enable") != -1)
				{
					if(pType->m_strUnit != "")//认为控制字是没有单位的
						continue;
					if(CString_To_long(pType->m_strMin) == 0 && CString_To_long(pType->m_strMax) == 1)
					{
						pDvmData = pType;
						break;
					}
				}
				else
				{
					if(pType->m_strUnit == "s" || pType->m_strUnit == "ms")
						continue;
					if(CString_To_long(pType->m_strMin) == 0 && CString_To_long(pType->m_strMax) == 1)
						continue;

					pDvmData = pType;
					break;
				}
			}
		}
		oListFind.RemoveAll();
	}

	if(pDvmData)
	{
		pDataObj->m_strDefaultValue = pDvmData->m_strValue;
		if(pDataObj->m_strValue == pDataObj->m_strDefaultValue)
			return TRUE;
	}
	else
	{
		pDataObj->m_strDefaultValue = _T("");
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CWzdDlg_ImpSet, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PDF_DVM, &CWzdDlg_ImpSet::OnTcnSelchangeTabPdfDvm)
	ON_MESSAGE(WM_IMPSET_UPDATE, &CWzdDlg_ImpSet::OnUpdateMD5)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, &CWzdDlg_ImpSet::OnBnClickedButtonCorrect)
	ON_BN_CLICKED(IDC_BUTTON_TIMEUNIT, &CWzdDlg_ImpSet::OnBnClickedButtonTimeunit)
END_MESSAGE_MAP()

void CWzdDlg_ImpSet::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlg_ImpSet::OnTcnSelchangeTabPdfDvm(NMHDR *pNMHDR, LRESULT *pResult)
{
	long nIndex = m_tabPdfDvm.GetCurSel();
	switch(nIndex)
	{
	case 0: m_nSetsType = 0; break;
	case 1: m_nSetsType = 1; break;
	case 2:	m_nSetsType = 2; break;
	default:
		break;
	}

	if (m_bFileType)
	{
		ShowSets_Xml();
	}
	else
	{
		ShowSets_Pdf();
	}

	*pResult = 0;
}

HRESULT CWzdDlg_ImpSet::OnUpdateMD5(WPARAM wParam, LPARAM lParam)
{
	//CStesFileXmlTool似乎没有实现m_oSetsMap的映射重新计算MD5值
	long nIndex = m_tabPdfDvm.GetCurSel();
	
	switch(nIndex)
	{
	case 0: m_gridDsFile.CalMD5(m_strRealCalMd5_Parameter);break;
	case 1: m_gridDsFile.CalMD5(m_strRealCalMd5_Ena);break;
	case 2: m_gridDsFile.CalMD5(m_strRealCalMd5_Setting);break;
	default:
		break;
	}

	CString str;
	m_oSetsFileXmlTool.GetMd5_FromCal(SETTING_CLASS_SETTING, str);

	//20230719 huangliang 区分pdf和xml刷新时调用
	if (m_bFileType)
	{
		GetRslt_Xml();
		ShowSets_Xml();
	}
	else
	{
		ShowSets_Pdf();
	}

	//GetRslt_Xml();
	//ShowSets_Xml();
	//m_gridDsFile.UpdateDatas();
	GetParentWnd()->SendMessage(WM_IMPSET_UPDATE, 0 ,0);

	return 0;
}

void CWzdDlg_ImpSet::OnBnClickedButtonCorrect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateFileSelected(true);
}

void CWzdDlg_ImpSet::OnBnClickedButtonTimeunit()//变更时间单位
{
	if (m_bFileType)
	{
		m_oSetsFileXmlTool.Time_S_to_ms();//20231023 luozibing 改变定制单单位
		ShowSets_Xml();
	}
	else
	{
		m_oStesFilePdfTool.Time_S_to_ms();
		ShowSets_Pdf();
	}
}
