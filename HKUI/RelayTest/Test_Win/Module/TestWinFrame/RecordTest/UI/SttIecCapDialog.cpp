#include "SttIecCapDialog.h"
/*#include "../../XLangResource_Native.h"*/



// #include "../../../../../../Module/XLanguage/XLanguageMngr.h"
// #include "../../../../../../Module/XLanguage/XLanguageGlobal.h"
// 
// #include "../../../../../../61850/Module/SCL/SclFileMngr/SclFileMngrGlobal.h"
// #include "../../../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
// 
// #include "../../../Module/TestWinFrame/ReportView/XLangResource_Native.h"
 #include "../../testwinbase.h"
#include "../../../../../Module/SttTestAppConfig/SttTestAppCfg.h"
#include "../../ReportView/XLangResource_PowerTestWin.h"

extern CSttTestAppCfg g_oSttTestAppCfg;
extern bool g_bTestAppConnect;

extern double g_dUIShowCoef; // 界面显示缩放比例

QSttIecCapDialog::QSttIecCapDialog(QWidget *parent, bool bIecCap)
	: QDialog(parent)
{
	m_pSttIecRecordMainWidget = NULL;
	m_bIecCapMode = bIecCap;

	if (!g_bTestAppConnect)
	{
		CString strIP = g_oSttTestAppCfg.GetTestAppIP();
		long nPort = g_oSttTestAppCfg.GetTestServerPort();

		if (!g_TestWinBase->OnConnectTestApp(strIP,nPort))//如果当前未联机,需要进行联机操作
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("联机失败[%s][%ld].")*/g_sLangTxt_Native_OnlineFailSy.GetString(),strIP.GetString(),nPort);
			g_TestWinBase->SysStateEvent_OnTestStoped();
			return;
		}
	}
	
	if (m_bIecCapMode)
	{
		g_TestWinBase->InitKeyDB();
		g_TestWinBase->InitSttIecRecord(&g_oSttTestAppCfg);
	}
}

QSttIecCapDialog::~QSttIecCapDialog()
{

}


void QSttIecCapDialog::InitUI()
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
// 	long nWidth = g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth-10;
// 	long nHeight = g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight-30;

	resize(1000*g_dUIShowCoef,600*g_dUIShowCoef);
	this->setFixedWidth(1000*g_dUIShowCoef);
	this->setFixedHeight(600*g_dUIShowCoef);

	CString strTitle,strTemp;
	strTitle = /*_T("报文探测界面")*/g_sLangTxt_Gradient_DetectMessageI;
	setWindowTitle(strTitle);
	m_pMainVLayout = new QVBoxLayout;

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setFixedWidth(60);
	m_pOK_PushButton->setText(/*"关闭"*/g_sLangTxt_Close);

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);

	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pSttIecRecordMainWidget= new QSttIecRecordMainWidget(font(),this);
	m_pSttIecRecordMainWidget->SetIecCapWriteFile(false);
 	m_pMainVLayout->addWidget(m_pSttIecRecordMainWidget);
	

		m_pSttOutPutWidget = new QSttOutPutWidget(this);
		m_pSttOutPutWidget->setFixedHeight(100);
		m_pMainVLayout->addWidget(m_pSttOutPutWidget);
		
		connect(g_TestWinBase, SIGNAL(sig_refreshLog(QString)), m_pSttOutPutWidget, SLOT(slot_refreshOutput(QString)));

	if(!m_bIecCapMode)
	{
		m_pSttIecRecordMainWidget->ClearAll_Detect();//suyang 20230706 通过弹窗打开，首先需要清除控制块
	}
  
	m_pMainVLayout->addLayout(m_pOK_CancelHLayout);
	setLayout(m_pMainVLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
}

void QSttIecCapDialog::StartDetect(bool bStartDetect)
{
	if (m_pSttIecRecordMainWidget == NULL)
	{
		return;
	}

	m_pSttIecRecordMainWidget->StartDetect();
}

void QSttIecCapDialog::slot_OKClicked()
{
 	CloseIecCapDetect();
	this->accept();
}


void QSttIecCapDialog::CloseIecCapDetect()
{
	if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->CloseIecCapDetect();
	}
}
