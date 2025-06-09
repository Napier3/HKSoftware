#include "ResultExprWidget_Cmp.h"
#include "ui_ResultExprWidget_Cmp.h"
#include "ResultExprDlg_Data.h"
#include "ResultExprDlg_Reports.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QResultExprWidget_Cmp::QResultExprWidget_Cmp(QWidget *parent) :
    QResultExprWidget(parent),
    ui(new Ui::QResultExprWidget_Cmp)
{
    ui->setupUi(this);

    InitUI();
    InitConnect();
	InitLanguage();
}

QResultExprWidget_Cmp::~QResultExprWidget_Cmp()
{
    delete ui;
}

void QResultExprWidget_Cmp::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label,g_sLangTxt_Native_paramone,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_2,g_sLangTxt_Native_paramtwo,XLang_Ctrls_QLabel);
}

void QResultExprWidget_Cmp::InitUI()
{
    setBackgroundColor(QColor(35, 168, 242));
    ui->m_cbbExpr->setShowType(QResultExprWidgetExprComboBox::AllExpr);
}

void QResultExprWidget_Cmp::InitConnect()
{
	connect(ui->m_btnDel1, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnDel2, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_editValue1, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editValue2, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
}

void QResultExprWidget_Cmp::OnSelectExpr()
{
	QResultExprWidgetButtonLine* pEdit = (QResultExprWidgetButtonLine*)sender();
	long nResult = OnSelectExpr_Data(pEdit);
	if(sender()->objectName() == "m_editValue1")
	{
		UpdateExprValue(((CXExprCmp*)m_pExprBase)->GetExprValue1(), ui->m_editValue1, nResult);
	}
	else if(sender()->objectName() == "m_editValue2")
	{
		UpdateExprValue(((CXExprCmp*)m_pExprBase)->GetExprValue2(), ui->m_editValue2, nResult);
	}
}

void QResultExprWidget_Cmp::OnDelectExpr()
{
	if(sender()->objectName() == "m_btnDel1")
	{
		ui->m_editValue1->Clear();
		UpdateExprValue(((CXExprCmp*)m_pExprBase)->GetExprValue1(), NULL); 
	}
	else
	{
		ui->m_editValue2->Clear();
		UpdateExprValue(((CXExprCmp*)m_pExprBase)->GetExprValue2(), NULL); 
	}
}

void QResultExprWidget_Cmp::SaveExprBase()
{
	((CXExprCmp*)m_pExprBase)->m_strOptr = ui->m_cbbExpr->currentText();
}

void QResultExprWidget_Cmp::LoadExprBase(CXExprBase* pExprBase)
{
	CXExprValue1* pValue1 = ((CXExprCmp*)m_pExprBase)->GetExprValue1();
	CXExprValue2* pValue2 = ((CXExprCmp*)m_pExprBase)->GetExprValue2();
	LoadExprBase_ComboBox(ui->m_cbbExpr, ((CXExprCmp*)pExprBase)->m_strOptr);
	LoadExprBase_Edit(ui->m_editValue1, pValue1);
	LoadExprBase_Edit(ui->m_editValue2, pValue2);

	CXExprValueRslt* pRslt = ((CXExprCmp*)m_pExprBase)->GetValueRslt();
	if(pRslt->m_strValue == "0")
	{
		setBackgroundColor(QColor(255, 0, 0));
	}
}