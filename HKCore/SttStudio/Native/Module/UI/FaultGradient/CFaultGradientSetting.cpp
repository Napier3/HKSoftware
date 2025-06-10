#include "CFaultGradientSetting.h"
#include "../Controls/SttLineEdit.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"

CFaultGradientSetting::CFaultGradientSetting(tmt_fault_gradient_test *pFGParas,QWidget *parent)
	: QDialog(parent),ui(new Ui::CFaultGradientSetting)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pFGParas = pFGParas;
	InitLanguage();
	ui->tabWidget->removeTab(0);
	SetUIFont(ui->m_tabBOut);
	SetStyleValue(ui->m_gbNormal);
	SetStyleValue(ui->m_gbError);
	SetStyleValue(ui->m_gbNormal,0);
	SetStyleValue(ui->m_gbError,1);

	((QSttTabWidget*)ui->tabWidget)->InitStyleSheet();
	connect(ui->btnGrpError,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(on_GrpOutError_ButtonClick(QAbstractButton*)));
	connect(ui->btnGrpNormal,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(on_GrpOutNormal_ButtonClick(QAbstractButton*)));
	connect(ui->m_btnOK,SIGNAL(clicked()),this,SLOT(on_OkButtonClick()));
	connect(ui->m_btnCancel,SIGNAL(clicked()),this,SLOT(on_CancelButtonClick()));
}

CFaultGradientSetting::~CFaultGradientSetting()
{
	delete ui;
}

void CFaultGradientSetting::InitLanguage()
{

}

void CFaultGradientSetting::SetUIFont(QWidget* pWidget)
{
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);
	ui->m_btnOK->setFont(*g_pSttGlobalFont);	
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);
	ui->tabWidget->setFont(*g_pSttGlobalFont);

	if(pWidget == NULL) return;
	pWidget->setFont(*g_pSttGlobalFont);

	QWidget *pChildWig = NULL;
	foreach(QObject* pObj,pWidget->children())
	{
		if(pObj == NULL) continue;

		QAbstractButton* pBt = NULL;
		pBt = dynamic_cast<QAbstractButton*>(pObj);
		if(pBt)
		{
			pBt->setFont(*g_pSttGlobalFont);
		}
		else
		{
			pChildWig = dynamic_cast<QWidget*>(pObj);
			if(pChildWig)
			{
				SetUIFont(pChildWig);
			}
		}
	}
}

void CFaultGradientSetting::SetStyleValue(QGroupBox* pGroup,int nVFlag)
{
	if(pGroup == NULL) return;
	foreach(QObject* pObj,pGroup->children())
	{
		if(pObj == NULL) continue;
		QSttCheckBox* pCheck = NULL;
		pCheck = dynamic_cast<QSttCheckBox*>(pObj);
		if(pCheck)
		{
			if(nVFlag < 0)
			{
				pCheck->InitStyleSheet();
			}
			else if(nVFlag >= 0)
			{
				QString strBtn = pCheck->objectName();
				int nIndex = strBtn.right(1).toInt();
				GlobalSetQcheckState_BinaryOut(pCheck,m_pFGParas->m_oFaultGradientParas.m_binOut[nVFlag],nIndex);
				m_binOutTemp[nVFlag][nIndex] = m_pFGParas->m_oFaultGradientParas.m_binOut[nVFlag][nIndex];
			}
			
		}
	}
}

void CFaultGradientSetting::on_GrpOutNormal_ButtonClick(QAbstractButton * pCurrBtn)
{
	QString strBtn = pCurrBtn->objectName();
	int nIndex = strBtn.right(1).toInt();
	if (pCurrBtn->isChecked())
	{
		m_binOutTemp[0][nIndex].nState = 1;
	}
	else
	{
		m_binOutTemp[0][nIndex].nState = 0;
	}
}

void CFaultGradientSetting::on_GrpOutError_ButtonClick(QAbstractButton * pCurrBtn)
{
	QString strBtn = pCurrBtn->objectName();
	int nIndex = strBtn.right(1).toInt();
	if (pCurrBtn->isChecked())
	{
		m_binOutTemp[1][nIndex].nState = 1;
	}
	else
	{
		m_binOutTemp[1][nIndex].nState = 0;
	}
}

void CFaultGradientSetting::on_OkButtonClick()
{
	accept();
}

void CFaultGradientSetting::on_CancelButtonClick()
{
	reject();
}