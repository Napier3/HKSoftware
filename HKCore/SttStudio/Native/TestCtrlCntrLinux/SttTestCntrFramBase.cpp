#include "SttTestCntrFramBase.h"

QSttTestCntrFramBase::QSttTestCntrFramBase(QWidget *parent) :
    QMainWindow(parent)
{
	CLogPrint::Create(this);
    m_pToolBar = NULL;
    m_pStatusBar = NULL;

    InitConfig();

    resize(m_pSttFrameConfig->m_nWidth,m_pSttFrameConfig->m_nHeight);
    this->setFixedHeight(m_pSttFrameConfig->m_nHeight);
    this->setFixedWidth(m_pSttFrameConfig->m_nWidth);

    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	m_MainWidget = new QWidget(this);
	m_MainWidget->setParent(this);
	m_MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
    m_MainWidget->setFixedHeight(m_pSttFrameConfig->m_nHeight);
    m_MainWidget->setFixedWidth(m_pSttFrameConfig->m_nWidth);
	this->setCentralWidget(m_MainWidget);

	m_MainWidget->show();

    InitUI();
//	m_pParaEdit = new QSttMacroParaEditViewHtml();

//	m_pParaEdit->setGeometry(30,30,860,480);
//	m_pParaEdit->setParent(this);
//	m_pParaEdit->show();

//	m_pParaEdit->OpenHtmlFile("ZeroTest.html");
}

QSttTestCntrFramBase::~QSttTestCntrFramBase()
{
	CLogPrint::SetLog(NULL);
    CLogPrint::Release();
    ReleaseConfig();
}

void QSttTestCntrFramBase::InitConfig()
{
	m_pSttFrameConfig = new CSttFrameConfig;
    m_pSttFrameConfig->Create();

    m_pSttFrameConfig->Open();
}

void QSttTestCntrFramBase::ReleaseConfig()
{
    m_pSttFrameConfig->Release();
}

void QSttTestCntrFramBase::Test(QString str)
{
    QMessageBox *msgBox;
    msgBox = new QMessageBox(QMessageBox::NoIcon,QObject::tr("ÌבÊ¾"),
                             str,QMessageBox::Ok);
    msgBox->exec();
}

void QSttTestCntrFramBase::InitUI()
{
    m_centerWidget = new QWidget(m_MainWidget);
    m_centerWidget->setParent(this);
    m_centerWidget->setObjectName(QString::fromUtf8("centerWidget"));

    m_pHBoxLayoutCenter = new QHBoxLayout(m_centerWidget);

    CSttFrame_Font *pFont = m_pSttFrameConfig->GetFont();
    m_gFont.setFamily(pFont->m_strName);
    m_gFont.setPixelSize(pFont->m_nHeigth);
    m_gFont.setBold(pFont->m_nBold);

    CSttFrame_ToolBar *pToolBar = m_pSttFrameConfig->GetToolBar();
    CSttFrame_StatusBar *pStatusBar = m_pSttFrameConfig->GetStatusBar();

    m_centerWidget->setGeometry(0,pToolBar->m_nHeight + SttFrame_Interval,
                                m_pSttFrameConfig->m_nWidth,m_pSttFrameConfig->m_nHeight -
                                pToolBar->m_nHeight - pStatusBar->m_nHeight - 2*SttFrame_Interval);

    m_pToolBar = new QSttBarBase(pToolBar, m_oDataBtnsMngr,m_gFont,m_MainWidget);
	m_pToolBar->setGeometry(0,0,pToolBar->m_nWidth,pToolBar->m_nHeight);
	m_pStatusBar = new QSttBarBase(pStatusBar, m_oDataBtnsMngr,m_gFont,m_MainWidget);
	m_pStatusBar->setGeometry(0,m_pSttFrameConfig->m_nHeight - pStatusBar->m_nHeight,pStatusBar->m_nWidth,pStatusBar->m_nHeight);
}

void QSttTestCntrFramBase::LogString(long nLevel, const CString &strMsg)
{
    //ui->edtMsgLog->setText(strMsg);
}

void QSttTestCntrFramBase::LogString(long nLevel, const char *strMsg)
{
    //ui->edtMsgLog->setText(strMsg);
}

void QSttTestCntrFramBase::slot_ToolBarButtonClick(QString strID)
{
	if(strID == "Exit")
	{
		this->close();
	}
	else(strID == "Menu")
	{

	}
}

//void QSttTestCntrFramBase::on_btnSetDatas_clicked()
//{
//	CString strFile;
//	strFile = _P_GetDBPath();
//	strFile += _T("paras/");
//	strFile += _T("ZeroTest.sttjs");

//	CFile oFile;
//	oFile.Open(strFile, CFile::modeRead);
//	long nLen = oFile.GetLength();
//	char *pszBuffer = new char [nLen + 1];
//	oFile.Read(pszBuffer, nLen);
//	pszBuffer[nLen] = 0;
//	CString strDataset = pszBuffer;

//	m_pParaEdit->SetDatas(strDataset);

//	delete pszBuffer;

//}
