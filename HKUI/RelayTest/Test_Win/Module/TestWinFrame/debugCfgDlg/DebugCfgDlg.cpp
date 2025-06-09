#include "DebugCfgDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../Module/TestWinFrame/testwinbase.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

CDebugCfgDlg::CDebugCfgDlg(QWidget *pParent)
	:QDialog(pParent)
{
	this->setWindowTitle(/*QObject::tr("底层信息打印设置")*/g_sLangTxt_Native_bottominfo_printset);
	this->setWindowIcon (QPixmap("./images/setSetting.png"));
	initUI(); 
	initConnections();
	initData();
}

CDebugCfgDlg::~CDebugCfgDlg()
{

}

void CDebugCfgDlg::initUI()
{
	m_chb_printLog = new QCheckBox(/*tr("是否打印底层日志信息")*/g_sLangTxt_Native_bottomloginfo_printornot,this);
	m_chb_saveFile = new QCheckBox(/*tr("是否保存底层测试信息")*/g_sLangTxt_Native_bottomtestinfo_saveornot,this);

	QHBoxLayout *pHLay1 = new QHBoxLayout;
	pHLay1->addWidget(m_chb_printLog);
	pHLay1->addWidget(m_chb_saveFile);

	m_pbtnOK = new QPushButton(/*tr("确定")*/g_sLangTxt_OK);
	m_pbtnCancel = new QPushButton(/*tr("取消")*/g_sLangTxt_Cancel);
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addStretch();
	pHLay2->addWidget(m_pbtnOK);
	pHLay2->addWidget(m_pbtnCancel);

	QVBoxLayout *pVLay=new QVBoxLayout;
	pVLay->addLayout(pHLay1);
	pVLay->addLayout(pHLay2);
	
	setLayout(pVLay); //设置为窗体的主布局

	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void CDebugCfgDlg::initConnections()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void CDebugCfgDlg::initData()
{
	m_chb_printLog->setChecked(g_bPrintLog);
	m_chb_saveFile->setChecked(g_bSaveFile);
}

void CDebugCfgDlg::slot_OKClicked()
{
	long nValue = 0;
	if (m_chb_printLog->isChecked())
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}
	g_TestWinBase->SetPrintLog(nValue);

	if (m_chb_saveFile->isChecked())
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}
	g_TestWinBase->SetSaveFile(nValue);

	close();
}

void CDebugCfgDlg::slot_CancelClicked()
{
	close();
}
