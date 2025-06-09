#include "SttFileSaveAsDlg.h"
#include "ui_SttFileSaveAsDlg.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../Module/CommonMethod/commonMethod.h"
#include <QMessageBox>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
//#include "../../Module/UI/SttTestCntrFrameBase.h"


QSttFileSaveAsDlg::QSttFileSaveAsDlg(const CString &strPrev, const CString &strFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttFileSaveAsDlg)
{
    ui->setupUi(this);
	CString strName;
	xlang_GetLangStrByFile(strName, "IEC_FileSaveAs");
	setWindowTitle(strName/*tr("文件另存为")*/);

// 	Qt::WindowFlags flags = Qt::Dialog;
// 	flags |= Qt::WindowCloseButtonHint;
// 	this->setWindowFlags(flags);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	xlang_SetLangStrToWidget(ui->m_lblFileFolder, "Native_FileFolder", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_lblFileName, "sFileName", XLang_Ctrls_QLabel);


	if (strFile.GetLength() == 0)
	{
		m_strFileName = InitFileByDate(strPrev, true);
	}
	else
	{
		m_strFileName = strFile;
	}
	
	m_strFolderName = InitFolderByDate("", FALSE);

	CString strOK;
	CString strCancel;
	xlang_GetLangStrByFile(strOK, "sOK");
	xlang_GetLangStrByFile(strCancel, "sCancel");
	ui->m_Btn_OK->setText(strOK/*tr("确定")*/);
	ui->m_Btn_Cancel->setText(strCancel/*tr("取消")*/);

	ui->m_wndFileName->setText(m_strFileName);
	ui->m_wndFolderName->setText(m_strFolderName);

	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
	connect(ui->m_wndFileName,SIGNAL(clicked()),this,SLOT(slot_FileNameLineEditClicked()));

	SetFileSaveFont();
}

QSttFileSaveAsDlg::~QSttFileSaveAsDlg()
{
    delete ui;
}

void QSttFileSaveAsDlg::SetFileSaveFont()
{
	ui->m_Btn_Cancel->setFont(*g_pSttGlobalFont);
	ui->m_Btn_OK->setFont(*g_pSttGlobalFont);
	ui->m_wndInfor->setFont(*g_pSttGlobalFont);
	ui->m_lblFileName->setFont(*g_pSttGlobalFont);
	ui->m_wndFileName->setFont(*g_pSttGlobalFont);
	ui->m_wndFolderName->setFont(*g_pSttGlobalFont);
	ui->m_lblFileFolder->setFont(*g_pSttGlobalFont);
}

void QSttFileSaveAsDlg::DisableFolder()
{
	ui->m_lblFileFolder->hide();
	ui->m_wndFolderName->hide();
}

CString QSttFileSaveAsDlg::InitFolderByDate(const CString &strPrev, bool bUseDay)
{
	CString strFolder;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	if (bUseDay)
	{
		strFolder.Format(_T("%d/%02d/%02d"), tm.wYear, tm.wMonth, tm.wDay);
	}
	else
	{
		strFolder.Format(_T("%02d/%02d"), tm.wYear, tm.wMonth);
	}

	return strFolder;
}

CString QSttFileSaveAsDlg::InitFileByDate(const CString &strPrev, bool bUseDay)
{
	CString strText;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	if (bUseDay)
	{
		strText.Format(_T("%d%02d%02d"), tm.wYear, tm.wMonth, tm.wDay);
	}
	else
	{
		strText.Format(_T("%02d%02d"), tm.wYear, tm.wMonth);
	}

	strText = strPrev + strText;

	return strText;
}

void QSttFileSaveAsDlg::slot_OKClick()
{
	m_strFileName = ui->m_wndFileName->text();
	m_strFolderName = ui->m_wndFolderName->text();

	CString strInfor;
	
	if (! CheckFileName(m_strFileName, strInfor))
	{
		ui->m_wndInfor->setText(strInfor);
		return;
	}

	accept();
}

void QSttFileSaveAsDlg::slot_CancelClick()
{
	reject();
}

void QSttFileSaveAsDlg::slot_FileNameLineEditClicked()
{
	QString strValue = ui->m_wndFileName->text();
	GetEngWidgetBoard_DigitData(strValue,(QWidget *)parent());
	ui->m_wndFileName->setText(strValue);
	ui->m_wndFileName->SetEditFinished();
}
