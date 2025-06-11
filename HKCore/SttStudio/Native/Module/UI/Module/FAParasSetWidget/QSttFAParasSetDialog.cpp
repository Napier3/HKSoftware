#include "QSttFAParasSetDialog.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttFAParasSetDialog::QSttFAParasSetDialog( QWidget *parent /*= 0*/ )	: QDialog(parent)
{
	m_pSttFAParasSetWidget = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;

	InitUI();
}

QSttFAParasSetDialog::~QSttFAParasSetDialog()
{

}

void QSttFAParasSetDialog::InitUI()
{
	CString strTemp;
	strTemp = QString::fromLocal8Bit("FA参数设置");
	setWindowTitle(strTemp);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	resize(830, 500);
	setFixedSize(QSize(830, 500));
	m_pSttFAParasSetWidget = new QSttFAParasSetWidget;
	m_pOK_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sOK");
	m_pOK_PushButton->setText(strTemp);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sCancel");
	m_pCancel_PushButton->setText(strTemp);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);


	QHBoxLayout *pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pOK_PushButton);
	pHBoxLayout->addSpacing(20);
	pHBoxLayout->addWidget(m_pCancel_PushButton);
	pHBoxLayout->addStretch();
	pHBoxLayout->setDirection(QBoxLayout::LeftToRight);
	
	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pSttFAParasSetWidget);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	

	setFocusPolicy(Qt::StrongFocus);

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));

	CString strFilePath;
	strFilePath = _P_GetConfigPath();
	strFilePath += _T("BinBoutCommMapConfig.xml");
	OpenFAParasFile(strFilePath);
	m_pSttFAParasSetWidget->InitData(&m_pFAParasData);
}

BOOL QSttFAParasSetDialog::OpenFAParasFile( const CString& strParasFile )
{
	if (!IsFileExist(strParasFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("FA参数文件【%s】不存在"),strParasFile.GetString()); 
		return FALSE;
	}
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pFAParasData.OpenXmlFile(strParasFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	m_pFAParasCopyData = (CDataGroup*)(&m_pFAParasData)->Clone();
	return TRUE;
}


 void QSttFAParasSetDialog::slot_OKClicked()
 {		
	 m_pSttFAParasSetWidget->SaveData();

	if (!m_pFAParasCopyData->IsEqual(&m_pFAParasData))
	{
		emit sig_UpdatepFAParasData(&m_pFAParasData);

		CString strFilePath;
		strFilePath = _P_GetConfigPath();
		strFilePath += _T("BinBoutCommMapConfig.xml");
		m_pFAParasData.SaveXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

	accept();
}

void QSttFAParasSetDialog::slot_CancelClicked()
{
	close();
}
