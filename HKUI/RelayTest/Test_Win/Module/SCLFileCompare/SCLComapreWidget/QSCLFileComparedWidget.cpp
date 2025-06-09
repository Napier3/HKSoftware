#include "QSCLFileComparedWidget.h"


QSCLFileComparedWidget::QSCLFileComparedWidget(QWidget *parent,CString strSCLFilePath, CString strCompareFilePath):QWidget(parent)
{
	m_pFileComparedLayout = NULL;
	m_pMainFileComparedSplitter = NULL;
	m_pRightComparedSplitter = NULL;
	m_pSCLComparedTextWidget = NULL;
	m_pSCLComparedTreeCtrl = NULL;
	m_pSCLXmlComparedTree = NULL;

	m_strCompareFilePath = strCompareFilePath;
	m_strSCLFilePath = strSCLFilePath;
	InitUI();
	
	connect(m_pSCLComparedTreeCtrl,SIGNAL(sig_UpdateXmlComparedTree(QDeliverPugiNode*)),m_pSCLXmlComparedTree,SLOT(UpdateTreeView(QDeliverPugiNode*)));
	connect(m_pSCLXmlComparedTree,SIGNAL(sig_UpdateComparedTextView(CString &,CString &)),m_pSCLComparedTextWidget,SLOT(ShowText(CString&, CString&)));
	connect(m_pSCLXmlComparedTree,SIGNAL(sig_InitComparedTextView(CString &,CString &)),m_pSCLComparedTextWidget,SLOT(ShowText(CString&, CString&)));

}

QSCLFileComparedWidget::~QSCLFileComparedWidget()
{

}

void QSCLFileComparedWidget::InitUI()
{
	m_pRightComparedSplitter = new QSplitter(Qt::Vertical);
	m_pSCLXmlComparedTree = new QSCLXmlComparedTree(this);
	m_pSCLComparedTextWidget = new QSCLComparedTextWidget();
	m_pRightComparedSplitter->addWidget(m_pSCLXmlComparedTree);
	m_pRightComparedSplitter->addWidget(m_pSCLComparedTextWidget);
	m_pRightComparedSplitter->setStretchFactor(0,6);
	m_pRightComparedSplitter->setStretchFactor(1,4);

	m_pMainFileComparedSplitter = new QSplitter(Qt::Horizontal);
	m_pSCLComparedTreeCtrl = new QSCLComparedTreeCtrl(this, m_strSCLFilePath, m_strCompareFilePath);
	m_pMainFileComparedSplitter->addWidget(m_pSCLComparedTreeCtrl);
	m_pMainFileComparedSplitter->addWidget(m_pRightComparedSplitter);
	m_pMainFileComparedSplitter->setStretchFactor(0,4);
	m_pMainFileComparedSplitter->setStretchFactor(1,6);


	m_pFileComparedLayout = new QVBoxLayout(this);
	m_pFileComparedLayout->addWidget(m_pMainFileComparedSplitter);
	setLayout(m_pFileComparedLayout);

}