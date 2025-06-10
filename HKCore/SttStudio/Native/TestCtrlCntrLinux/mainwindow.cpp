#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	CLogPrint::Create(this);
    ui->setupUi(this);

	m_pParaEditView = new QSttMacroParaEditViewHtml();
	m_pParaEditView->setGeometry(30,30,860,480);
	m_pParaEditView->setParent(this);
	m_pParaEditView->show();
	m_pParaEditView->OpenHtmlFile("ZeroTest.html");

	m_pReportView = new QSttReportViewHtml();
	m_pReportView->setGeometry(30,30,860,480);
	m_pReportView->setParent(this);
	m_pReportView->hide();
	m_pReportView->OpenHtmlFile("report_demo.html");


}

MainWindow::~MainWindow()
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
    delete ui;
}

void MainWindow::LogString(long nLevel, const CString &strMsg)
{
    ui->edtMsgLog->setText(strMsg);
}

void MainWindow::LogString(long nLevel, const char *strMsg)
{
    ui->edtMsgLog->setText(strMsg);
}

void MainWindow::on_btnSetDatas_clicked()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("paras/");
	strFile += _T("ZeroTest.sttjs");

	CFile oFile;
	oFile.Open(strFile, CFile::modeRead);
	long nLen = oFile.GetLength();
	char *pszBuffer = new char [nLen + 1];
	oFile.Read(pszBuffer, nLen);
	pszBuffer[nLen] = 0;
	CString strDataset = pszBuffer;

	m_pParaEditView->SetDatas(strDataset);

	delete pszBuffer;

}

void MainWindow::on_btnParasEdit_clicked()
{
    if (m_pParaEditView->isVisible())
    {
        return;
    }

	m_pReportView->hide();
	m_pParaEditView->show();
}

void MainWindow::on_btnReportView_clicked()
{
	if (m_pReportView->isVisible())
	{
		return;
	}

	m_pParaEditView->hide();
	m_pReportView->show();
}
