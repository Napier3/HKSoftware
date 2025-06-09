#include "SttLanguageCfgDialog.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include <QMessageBox>
#include "../Module/ScrollCtrl/ScrollComboBox.h"
//#include "../SttTestCntrFrameBase.h"


QSttLanguageCfgDialog::QSttLanguageCfgDialog(QWidget *parent) : QDialog(parent)
{
// 	Qt::WindowFlags flags = Qt::Dialog;
// 	flags |= Qt::WindowCloseButtonHint;
// 	this->setWindowFlags(flags);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    CXLanguageMngr *pXLang = CXLanguageMngr::g_pXLanguageMngr;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle, "Native_LangSetting");
	this->setWindowTitle(strTitle);

    m_pMainLayout = new QVBoxLayout(this);
    this->setLayout(m_pMainLayout);

    m_pCenterLayout = new QHBoxLayout();
    m_pBottomLayout = new QHBoxLayout();

    m_pBtnOK = new QPushButton();
    m_pBtnCancel = new QPushButton();
    CString strOK;
    CString strCancel;
    xlang_GetLangStrByFile(strOK, "sOK");
    xlang_GetLangStrByFile(strCancel, "sCancel");

    QFont font = m_pBtnOK->font();
    font.setPixelSize(20);
    m_pBtnOK->setFont(font);
    m_pBtnOK->setText(strOK);
    m_pBtnCancel->setFont(font);
    m_pBtnCancel->setText(strCancel);

	m_pComboBox = new QScrollComboBox();

    POS pos = pXLang->GetHeadPosition();
	int i = 0;
    while (pos != NULL)
    {
        CXLanguage *pObj = (CXLanguage*)pXLang->GetNext(pos);
        if(pObj != NULL)
        {
			m_pComboBox->insertItem(i++,pObj->m_strName);
			m_pComboBox->setFont(font);
        }
    }

	m_pComboBox->setCurrentIndex(pXLang->FindIndexByID(xlang_GetCurrLanguageID()));
	m_pComboBox->setFixedWidth(180);

	m_pCenterLayout->addWidget(m_pComboBox);
	m_pCenterLayout->addWidget(m_pBtnOK);
	m_pCenterLayout->addWidget(m_pBtnCancel);

	CString strTipContext;
	xlang_GetLangStrByFile(strTipContext, "Native_LangTipContext");
	m_pLabelText = new QLabel();
	m_pLabelText->setText(strTipContext);
	font.setPixelSize(18);
	m_pLabelText->setFont(font);

	m_pBottomLayout->addWidget(m_pLabelText);

	m_pMainLayout->addLayout(m_pCenterLayout);
	m_pMainLayout->addSpacing(20);
	m_pMainLayout->addLayout(m_pBottomLayout);
    connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
	
	SetLanguageCfgFont();
}

void QSttLanguageCfgDialog::SetLanguageCfgFont()
{
	m_pLabelText->setFont(*g_pSttGlobalFont);
	m_pBtnCancel->setFont(*g_pSttGlobalFont);
	m_pBtnOK->setFont(*g_pSttGlobalFont);
	m_pComboBox->setFont(*g_pSttGlobalFont);

}

void QSttLanguageCfgDialog::slot_OKClick()
{
	CXLanguageMngr *pXLang = CXLanguageMngr::g_pXLanguageMngr;

	CXLanguage *pObj = (CXLanguage*)pXLang->GetAt(m_pComboBox->currentIndex());

	pXLang->xlang_SetCurrLanguageID(pObj->m_strID);//这个函数里面自带保存，就不用调用保存了

    close();
}

void QSttLanguageCfgDialog::slot_CancelClick()
{
    close();
}


