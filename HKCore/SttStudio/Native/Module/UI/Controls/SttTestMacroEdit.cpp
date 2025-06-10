#include "SttTestMacroEdit.h"
#include "ui_SttTestMacroEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSttTestMacroEdit::QSttTestMacroEdit(CExBaseObject *pObj,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttTestMacroEdit)
{
    ui->setupUi(this);


	xlang_SetLangStrToWidget_Txt(ui->label_Name,g_sLangTxt_Name,XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	
	m_pSttTestData = pObj;

	ui->lineEdit_ID->setText(m_pSttTestData->m_strID);
	ui->lineEdit_Name->setText(m_pSttTestData->m_strName);

	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
}

QSttTestMacroEdit::~QSttTestMacroEdit()
{
    delete ui;
}

void QSttTestMacroEdit::slot_OKClick()
{
	m_pSttTestData->m_strID = ui->lineEdit_ID->text();
	m_pSttTestData->m_strName = ui->lineEdit_Name->text();

	close();
}

void QSttTestMacroEdit::slot_CancelClick()
{
	close();
}
