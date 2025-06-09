#include "StateSettingValueDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>

StateSettingValueDlg::StateSettingValueDlg(tmt_StateParas* pParas, QWidget* parent) : QDialog(parent)
{
	m_pEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

StateSettingValueDlg::~StateSettingValueDlg()
{

}

void StateSettingValueDlg::InitUI()
{
	CString strTitle = /*"整定值"*/g_sLangTxt_State_SettingValue; //lcq
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);
	
	CString strText;
	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	QLabel* pLabel = new QLabel(this);
	xlang_GetLangStrByFile(strText, "Native_ActionTime");
	pLabel->setText(strText);
	pHLayout->addWidget(pLabel);
	m_pEdit = new QLineEdit(this);
	//m_pEdit->setText(QString::number(m_pParas->m_fTset));
	pHLayout->addWidget(m_pEdit);
	pVLayout->addLayout(pHLayout);

	pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);
}

void StateSettingValueDlg::slot_btnOK_Clicked()
{
	//float fTset = CString_To_double(m_pEdit->text());
	//m_pParas->m_fTset = fTset;
	accept();
}

void StateSettingValueDlg::slot_btnCancel_Clicked()
{
	reject();
}