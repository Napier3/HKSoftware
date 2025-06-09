#include "QAddSCLFilesDlg.h"
#include <QStandardItemModel>
#include <QString>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QFile>
#include "..\..\API\GlobalConfigApi.h"
#include "..\..\Log\LogPrint.h"

QAddSCLFilesDlg::QAddSCLFilesDlg(QWidget* pparent, CString strStandardFilePath, CString strBeTestedFilePath)
{
	ui.setupUi(this);
	InitFilePaths(strStandardFilePath, strBeTestedFilePath);
	InitUI();
	InitConnects();
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);
}

QAddSCLFilesDlg::~QAddSCLFilesDlg()
{

}
void QAddSCLFilesDlg::InitUI()
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	CString strTitle = _T("导入");
	m_InportBeTestedFileBtn = new QPushButton(strTitle);
	m_InportStandardFileBtn = new QPushButton(strTitle);
	strTitle = _T("清除");
	m_ClearBtn = new QPushButton(strTitle);
	ui.m_pAddSCLFileTable->verticalHeader()->setVisible(false); 
	ui.m_pAddSCLFileTable->setRowCount(2);
	ui.m_pAddSCLFileTable->setColumnCount(5);
	ui.m_pAddSCLFileTable->setWindowTitle("QTableWidget & Item");
	QStringList columnTitles;
	CString strIndex, strUse, strPath;
	strIndex = _T("序号");
	strUse = _T("文件用途");
	strPath = _T("文件路径");
	columnTitles << strIndex << strUse << strPath << ""<<"";
	ui.m_pAddSCLFileTable->setHorizontalHeaderLabels(columnTitles);
	ui.m_pAddSCLFileTable->horizontalHeader()->setStretchLastSection(true);
	ui.m_pAddSCLFileTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	ui.m_pAddSCLFileTable->setColumnWidth(0,40);
	ui.m_pAddSCLFileTable->setColumnWidth(1,160);
	ui.m_pAddSCLFileTable->setColumnWidth(2,250);
	ui.m_pAddSCLFileTable->setColumnWidth(3,90);
	ui.m_pAddSCLFileTable->setColumnWidth(4,90);
	ui.m_pAddSCLFileTable->setItem(0,0,new QTableWidgetItem("1"));
	ui.m_pAddSCLFileTable->setItem(1,0,new QTableWidgetItem("2"));
	strTitle = _T("待测/基准SCL文件");
	ui.m_pAddSCLFileTable->setItem(0,1,new QTableWidgetItem(strTitle));
	strTitle = _T("对比对象SCL文件");
	ui.m_pAddSCLFileTable->setItem(1,1,new QTableWidgetItem(strTitle));
	ui.m_pAddSCLFileTable->setItem(0,2,new QTableWidgetItem(m_strStandardFilePath));
	ui.m_pAddSCLFileTable->setItem(1,2,new QTableWidgetItem(m_strBeTestedFilePath));
	ui.m_pAddSCLFileTable->item(0,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->item(1,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->item(1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->item(0,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->item(1,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_pAddSCLFileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_pAddSCLFileTable->setCellWidget(0,3,m_InportStandardFileBtn);
	ui.m_pAddSCLFileTable->setCellWidget(1,3,m_InportBeTestedFileBtn);
	ui.m_pAddSCLFileTable->setCellWidget(1,4,m_ClearBtn);
	ui.m_pAddSCLFileTable->setRowHeight(0,60);
	ui.m_pAddSCLFileTable->setRowHeight(1,60);
	CString strPngPath = _P_GetResourcePath();
	strPngPath  += _T("Assist.png");
	this->setWindowIcon(QIcon(strPngPath));
	EnabledBtns();
}

void QAddSCLFilesDlg::InitFilePaths(CString strStandardFilePath, CString strBeTestedFilePath)
{
	m_strStandardFilePath = strStandardFilePath;
	m_strBeTestedFilePath = strBeTestedFilePath;
	QFile Standardfile(m_strStandardFilePath);
	if (!Standardfile.exists())
	{
		m_strStandardFilePath = "";
	}
	QFile BeTestedFile(m_strBeTestedFilePath);
	if (!BeTestedFile.exists())
	{
		m_strBeTestedFilePath = "";
	}
}

void QAddSCLFilesDlg::slot_m_InportBeTestedFileBtn_Clicked()
{
	QString strBeTestedFilePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.scd*)");
	if (strBeTestedFilePath != "")
	{
		m_strBeTestedFilePath = CString(strBeTestedFilePath);
	}
	ui.m_pAddSCLFileTable->item(1,2)->setText(m_strBeTestedFilePath);
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);

}

void QAddSCLFilesDlg::slot_m_InportStandardFileBtn_Clicked()
{
	QString strStandardFilePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.scd*)");
	if (strStandardFilePath != "")
	{
		m_strStandardFilePath = CString(strStandardFilePath);
	}
	ui.m_pAddSCLFileTable->item(0,2)->setText(m_strStandardFilePath);
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);
	EnabledBtns();
}

void QAddSCLFilesDlg::slot_m_ClearBtn_Clicked()
{
	ui.m_pAddSCLFileTable->item(0,2)->setText("");
	ui.m_pAddSCLFileTable->item(1,2)->setText("");
	m_strBeTestedFilePath = "";
	m_strStandardFilePath = "";
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);
	EnabledBtns();
}


void QAddSCLFilesDlg::slot_m_OK_clicked()
{
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);
	this->close();
	if (m_strBeTestedFilePath != "" || m_strStandardFilePath != "")
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("导入文件成功"));
	}
}


void QAddSCLFilesDlg::slot_m_Cancel_clicked()
{
	this->close();
}

void QAddSCLFilesDlg::InitConnects()
{
	connect(m_InportBeTestedFileBtn, SIGNAL(clicked()), this, SLOT(slot_m_InportBeTestedFileBtn_Clicked()));
	connect(m_InportStandardFileBtn, SIGNAL(clicked()), this, SLOT(slot_m_InportStandardFileBtn_Clicked()));
	connect(m_ClearBtn, SIGNAL(clicked()), this, SLOT(slot_m_ClearBtn_Clicked()));
	connect(ui.m_OK_Btn,SIGNAL(clicked()), this, SLOT(slot_m_OK_clicked()));
	connect(ui.m_Cancel_Btn,SIGNAL(clicked()), this, SLOT(slot_m_Cancel_clicked()));
}

void QAddSCLFilesDlg::DeliverPath()
{
	emit sig_m_OK_clicked(m_strStandardFilePath, m_strBeTestedFilePath);
	}

void QAddSCLFilesDlg::EnabledBtns()
{
	if (m_strStandardFilePath == "")
	{
		m_InportBeTestedFileBtn->setEnabled(false);
	}
	else
	{
		m_InportBeTestedFileBtn->setEnabled(true);
	}
}