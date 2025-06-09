#include "qsttselsclfilewidget.h"
#include "../../../../Module/API/StringApi.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../../61850/Module/SCL_Qt/QScdFileRWDlg.h"
#include "QSttSelSclIedWidget.h"

#ifndef _PSX_QT_LINUX_
#include "../../../../61850/Module/SCL/SclFileRead.h"
#include "../../../../Module/System/TickCount32.h"
// #include "../src/gui/dialogs/qfiledialog.h"
#include <QFileDialog>
#include <QFile>
#endif

QSttSelSclFileWidget *g_pSttSelSclFileWidget = NULL;

QSttSelSclFileWidget::QSttSelSclFileWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pBtns_HBoxLayout = NULL;
	m_pMainVLayout = NULL;
	m_pClearAll_Btn = NULL;
	m_pDelCurr_Btn = NULL;
	m_pAddScl_Btn = NULL;
	m_pSclIedSelect_Btn= NULL;
	m_pSttSelSclFileGrid = NULL;
}

QSttSelSclFileWidget::~QSttSelSclFileWidget()
{

}

void QSttSelSclFileWidget::InitUI()
{
	m_pMainVLayout = new QVBoxLayout;
	m_pBtns_HBoxLayout = new QHBoxLayout;
	m_pSttSelSclFileGrid = new CSttSelSclFileGrid(this);
	m_pSttSelSclFileGrid->SetTableFont(this->font());
	m_pSttSelSclFileGrid->InitGrid();
	CString strText;
	strText = _T("新增SCL");
	m_pAddScl_Btn = new QPushButton(strText,this);
	strText = _T("删除当前");
	m_pDelCurr_Btn = new QPushButton(strText,this);
	strText = _T("清空全部");
	m_pClearAll_Btn = new QPushButton(strText,this);
	strText = _T("IED选择");
	m_pSclIedSelect_Btn = new QPushButton(strText,this);
	m_pSclIedSelect_Btn->setVisible(false);
	m_pBtns_HBoxLayout->addWidget(m_pAddScl_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pDelCurr_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pClearAll_Btn);
	m_pBtns_HBoxLayout->addWidget(m_pSclIedSelect_Btn);
	m_pBtns_HBoxLayout->addStretch();
	m_pMainVLayout->addWidget(m_pSttSelSclFileGrid);
	m_pMainVLayout->addLayout(m_pBtns_HBoxLayout);
	setLayout(m_pMainVLayout);
	InitDatas();
	m_pSttSelSclFileGrid->AttachDataViewOptrInterface(this);
	EnableButtons();
	connect(m_pAddScl_Btn, SIGNAL(clicked()), this, SLOT(slot_AddScl_Clicked()));
	connect(m_pDelCurr_Btn, SIGNAL(clicked()), this, SLOT(slot_DelCurr_Clicked()));
	connect(m_pClearAll_Btn, SIGNAL(clicked()), this, SLOT(slot_ClearAll_Clicked()));
	connect(m_pSclIedSelect_Btn, SIGNAL(clicked()), this, SLOT(slot_SclIedSelect_Clicked()));
}

void QSttSelSclFileWidget::InitDatas()
{
	m_pSttSelSclFileGrid->ShowDatas(&g_oXSclFileMngr);

	if (g_oXSclFileMngr.GetCount()>0)
	{
		m_pSttSelSclFileGrid->SelectRow(1);
	}
}

void QSttSelSclFileWidget::slot_AddScl_Clicked()
{	
	CString strFilePath;
	long nSize = 0;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetLibraryPath();
	astrPostfix<<"*.scd"<<"*.icd"<<"*.cid";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}

	nSize = oOpenDlg.GetFileSize();
#else
	CString strText = _T("选择SCL文件");
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
	//strText = _T("SCD文件(*.scd);;ICD文件(*.icd);;CID文件(*.cid)");
	strText = _T("SCL文件(*.scd *.icd *.cid)");
	dlg.setNameFilter(strText);

	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetLibraryPath();
	dlg.setDirectory(strPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	strText = _T("打开");
	dlg.setLabelText(QFileDialog::Accept, strText);

	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFilePath = fileNames.at(0);

		QFile oFile(strFilePath);

		if (oFile.open(QFile::ReadOnly | QIODevice::Text))
		{
			nSize = oFile.size();
			oFile.close();
		}
	}
#endif

	CXSclFileObj *pXSclFileObj = (CXSclFileObj*)g_oXSclFileMngr.FindByID(strFilePath);

	if (pXSclFileObj != NULL)
	{
		if (pXSclFileObj->m_nUse == 0)
		{
			pXSclFileObj->m_nUse = 1;
			g_oXSclFileMngr.ValidSetSelectState(pXSclFileObj);
			m_pSttSelSclFileGrid->slot_UpdateSelectState();
			g_oXSclFileMngr.SaveSclFileMngrCfg();
		} 

		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前文件(%s)已打开."),strFilePath.GetString());
//		m_pSttSelSclFileGrid->setBackgroundRole();
		return;
	}

	pXSclFileObj = new CXSclFileObj;
	g_oXSclFileMngr.AddNewChild(pXSclFileObj);
	pXSclFileObj->m_nSize = nSize;
	pXSclFileObj->m_strName = GetFileNameFromFilePath(strFilePath);
	pXSclFileObj->m_strID = strFilePath;
	pXSclFileObj->m_nUse = 1;
#ifdef _PSX_QT_LINUX_
	pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs(strFilePath,&m_oSclStation,this);
#else
	pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs_EX(strFilePath,&m_oSclStation,this);
#endif

	if (!IsFileExist(pXSclFileObj->m_strSsclPath))
	{
		g_oXSclFileMngr.Delete(pXSclFileObj);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("生成解析文件(%s)失败,可能原SCL文件名包含中文信息导致."),
			pXSclFileObj->m_strSsclPath.GetString());
		return;
	}

	m_pSttSelSclFileGrid->InsertData(pXSclFileObj);

	if (!g_oXSclFileMngr.ValidSetSelectState(pXSclFileObj))
	{
		m_pSttSelSclFileGrid->slot_UpdateSelectState();
	} 

	m_pSttSelSclFileGrid->SelectRow(g_oXSclFileMngr.GetCount());
	EnableButtons();
	g_oXSclFileMngr.SaveSclFileMngrCfg();
}

void QSttSelSclFileWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	EnableButtons();
}

void QSttSelSclFileWidget::EnableButtons()
{
	if (m_pSttSelSclFileGrid->GetCurrSelData())
	{
		m_pDelCurr_Btn->setEnabled(true);
		m_pSclIedSelect_Btn->setEnabled(true);
	}
	else
	{
		m_pDelCurr_Btn->setEnabled(false);
		m_pSclIedSelect_Btn->setEnabled(false);
	}

	if (g_oXSclFileMngr.GetCount()>0)
	{
		m_pClearAll_Btn->setEnabled(true);
	} 
	else
	{
		m_pClearAll_Btn->setEnabled(false);
	}
}

void QSttSelSclFileWidget::slot_DelCurr_Clicked()
{
	CXSclFileObj *pXSclFileObj = (CXSclFileObj*)m_pSttSelSclFileGrid->GetCurrSelData();

	if (pXSclFileObj == NULL)
	{
		return;
	}

	CString strFolderPath;
	strFolderPath = GetPathFromFilePathName(pXSclFileObj->m_strSsclPath);
	DeleteAllDirectorys(strFolderPath);
	m_pSttSelSclFileGrid->DeleteDataRow(pXSclFileObj);
	g_oXSclFileMngr.SaveSclFileMngrCfg();
}

void QSttSelSclFileWidget::slot_ClearAll_Clicked()
{
	CString strMsg;
	strMsg = "请确认,是否清空全部SCL文件？";
	int result = CXMessageBox::information(this, tr("提示"), strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	g_oXSclFileMngr.ClearAll_WithFolderFiles();
	m_pSttSelSclFileGrid->ShowDatas(&g_oXSclFileMngr);
	g_oXSclFileMngr.SaveSclFileMngrCfg();
	EnableButtons();
}

void QSttSelSclFileWidget::slot_SclIedSelect_Clicked()
{
	QSttSelSclIedWidget oSttSelSclIedWidget(this);
	oSttSelSclIedWidget.InitUI();
	oSttSelSclIedWidget.InitDatas(&m_oSclStation);
	oSttSelSclIedWidget.exec();
}

CString Global_ParseSclFileSaveSclCfgs(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent)
{
	pSclStation->DeleteAll();
	CScdFileRWDlg oScdFileRWDlg(pParent);
	QSclFileRead  oSclFileRead;
	oSclFileRead.SetProgressInterface(&oScdFileRWDlg);
	oSclFileRead.ReadSclFile(strSclFilePath,pSclStation);

	return Global_SaveSclCfgs(strSclFilePath, pSclStation);
}

#ifndef _PSX_QT_LINUX_
CString Global_ParseSclFileSaveSclCfgs_EX(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent)
{
	pSclStation->DeleteAll();
	CScdFileRWDlg oScdFileRWDlg(pParent);
	CSclFileRead  oSclFileRead;
	
	oSclFileRead.SetIedSaveDvm(FALSE);
	oSclFileRead.SetProgessInterface(&oScdFileRWDlg);
	oSclFileRead.ReadSclFile(strSclFilePath,NULL, pSclStation);
	CTickCount32 oWait;

	while( oSclFileRead.IsInReadState() )
	{
		oWait.DoEvents(100);
	}

	return Global_SaveSclCfgs(strSclFilePath, pSclStation);
}
#endif

CString Global_SaveSclCfgs(const CString &strSclFilePath, CSclStation *pSclStation)
{
	CString strTscdPath,strFileName,strFileNameWithPostfix,strSsclPath;
	//	const char *pString = NULL;
	strTscdPath = _P_GetLibraryPath();
	strFileNameWithPostfix = GetPathFileNameFromFilePathName(strSclFilePath);
	strFileName = GetFileTitleFromFilePath(strFileNameWithPostfix);
	strTscdPath += _T("SCL/");
	strTscdPath += strFileName;
	strTscdPath += _T("/");	
	CreateAllDirectories(strTscdPath);
	strTscdPath += strFileName;
	strTscdPath += _T(".tscd");
	//	pString = strTscdPath.GetString();
	pSclStation->SaveXmlFile(strTscdPath,CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	pSclStation->m_strTscdFile = strTscdPath;
	strSsclPath = ChangeFilePostfix(strTscdPath,_T("sscl"));
	pSclStation->SaveSsclFiles(strSsclPath);
	return strSsclPath;
}