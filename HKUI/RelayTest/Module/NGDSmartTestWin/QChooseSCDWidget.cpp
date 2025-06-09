#include "QChooseSCDWidget.h"
#include "QSttSelSclFileWidget.h"
#include "NGDSmartTestWinFrameBase.h"

QChooseSCDWidget::QChooseSCDWidget(QWidget *pparent)
{
	ui.setupUi(this);
	m_strSCDFilePath = _T("");
	m_strModFileName = _T("");
	m_pSclStation = NULL;
	m_pModTypeGroup = &g_NGDSmartTestWin->m_oTestFuntions;
// 	ui.m_CombVolType->addItem(_T("110Kv"));
// 	ui.m_CombDevType->addItem(_T("母线保护"));//先手动添加，后续改成配置文件获取
// 	ui.m_CombDevType->addItem(_T("线路保护"));
	connect(ui.m_BtnChooseSCD, SIGNAL(clicked()), this, SLOT(slot_On_m_Btn_ChooseSCD_clicked()));
}

QChooseSCDWidget::~QChooseSCDWidget(void)
{
}

void QChooseSCDWidget::InitCombo()
{
	CDataGroup *pVols = (CDataGroup *)m_pModTypeGroup->FindByID(_T("VolType"));
	POS posVolType = pVols->GetHeadPosition();
	while(posVolType)
	{
		CShortData *pVol = (CShortData *)pVols->GetNext(posVolType);
		if (pVol->m_strValue == "1")
		{
			ui.m_CombVolType->addItem(pVol->m_strName);
		}
		
	}
	CDataGroup *pDevs = (CDataGroup *)m_pModTypeGroup->FindByID(_T("DevType"));
	POS posDevType = pDevs->GetHeadPosition();
	while(posDevType)
	{
		CShortData *pDev = (CShortData *)pDevs->GetNext(posDevType);
		if (pDev->m_strValue == "1")
		{
			ui.m_CombDevType->addItem(pDev->m_strName);
		}	
	}
}

void QChooseSCDWidget::SetSCLStation(CSclStation *pSclStation)
{
	m_pSclStation = pSclStation;
}

void QChooseSCDWidget::GetModFileName()
{
	CString strVolType = _T("");
	strVolType = ui.m_CombVolType->currentText();
	CString strDevType = _T("");
	strDevType = ui.m_CombDevType->currentText();
	m_strModFileName = strVolType + strDevType;
	m_strModFileName += _T("校验作业指导书");
}

CString QChooseSCDWidget::OpenSaveTemplateFileDlg(QWidget *parent,const CString &strTitle,const CString &strFilter, const CString &strFolderPath,BOOL bIsOpen)
{
	QFileDialog oFileDlg;
	oFileDlg.setWindowTitle(strTitle);
	oFileDlg.setFileMode(QFileDialog::AnyFile);
	oFileDlg.setNameFilter(strFilter);

	oFileDlg.setViewMode(QFileDialog::Detail);
	oFileDlg.setAcceptMode(QFileDialog::AcceptOpen);
	oFileDlg.setDirectory(strFolderPath);
	oFileDlg.show();

	if(bIsOpen)
	{
		oFileDlg.setAcceptMode(QFileDialog::AcceptOpen);
		oFileDlg.setLabelText(QFileDialog::Accept, "打开");
	}
	else
	{
		oFileDlg.setAcceptMode(QFileDialog::AcceptSave);
		oFileDlg.setLabelText(QFileDialog::Accept, "保存");	
	}

	CString strFileName,strSelectFilter;
	QStringList fileNames;
	if (oFileDlg.exec() == QFileDialog::Accepted)
	{
		fileNames = oFileDlg.selectedFiles();
		strFileName = fileNames.at(0);
		strSelectFilter = oFileDlg.selectedFilter();
		CString strTmp;
		long nIndex = strSelectFilter.Find("*.");

		if (nIndex>=0)
		{
			strTmp = strSelectFilter.Mid(nIndex+1);
			strTmp.Replace(_T(")"),_T(""));

			if (strFileName.Find(strTmp) == -1)
			{
				strFileName += strTmp;
			}
		}
	}
	return strFileName;
}

void QChooseSCDWidget::slot_On_m_Btn_ChooseSCD_clicked()
{
	CString strFilter = _P_GetLibraryPath();
	strFilter += _T("SCD");
	CString strTitle = _T("选择SCD文件");
	CString strReportPostfix =_T("scd文件(*.scd)");
	m_strSCDFilePath = OpenSaveTemplateFileDlg(this, strTitle, strReportPostfix, strFilter, TRUE);
	if (m_strSCDFilePath != "")
	{
		g_NGDSmartTestWin->m_bLoadSCDFile = TRUE;
		g_NGDSmartTestWin->UpdateView();
	}
	ui.m_EditSCDFilePath->setText(m_strSCDFilePath);
	Global_ParseSclFileSaveSclCfgs(m_strSCDFilePath, m_pSclStation, this, _T("01"));
	m_pSclStation->InitAfterRead();
}
