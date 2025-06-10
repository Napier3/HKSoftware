#include "ResultExprWidget_Range.h"
#include "ui_ResultExprWidget_Range.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


QResultExprWidget_Range::QResultExprWidget_Range(QWidget *parent) :
    QResultExprWidget(parent),
    ui(new Ui::QResultExprWidget_Range)
{
    ui->setupUi(this);
    InitUI();
    InitConnect();
	InitLanguage();
}

QResultExprWidget_Range::~QResultExprWidget_Range()
{
    delete ui;
}

void QResultExprWidget_Range::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label,g_sLangTxt_ResultParameter,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_2,g_sLangTxt_Native_baseline_min,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_3,g_sLangTxt_Native_baseline_max,XLang_Ctrls_QLabel);
}

void QResultExprWidget_Range::InitUI()
{
    setBackgroundColor(QColor(35, 168, 242));
    ui->m_cbbMaxExpr->setShowType(QResultExprWidgetExprComboBox::LittleExpr);
    ui->m_cbbMinExpr->setShowType(QResultExprWidgetExprComboBox::BigExpr);
}

void QResultExprWidget_Range::InitConnect()
{
	connect(ui->m_editResultParas, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editMinValue, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editMaxValue, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_btnResultParasDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnMinValueDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnMaxValueDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
}

void QResultExprWidget_Range::OnSelectExpr()
{
	long nResult = FALSE;
	if(sender()->objectName() == "m_editResultParas")
	{
		nResult = OnSelectExpr_Report(ui->m_editResultParas);
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValue(), ui->m_editResultParas, nResult);
	}
	else if(sender()->objectName() == "m_editMinValue")
	{
		nResult = OnSelectExpr_Data(ui->m_editMinValue);
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValueMin(), ui->m_editMinValue, nResult);
	}
	else if(sender()->objectName() == "m_editMaxValue")
	{
		nResult = OnSelectExpr_Data(ui->m_editMaxValue);
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValueMax(), ui->m_editMaxValue, nResult);
	}
}

void QResultExprWidget_Range::OnDelectExpr()
{
	if(sender()->objectName() == "m_btnResultParasDel")
	{
		ui->m_editResultParas->Clear();
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValue(), NULL);
	}
	else if(sender()->objectName() == "m_btnMinValueDel")
	{
		ui->m_editMinValue->Clear();
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValueMin(), NULL);
	}
	else if(sender()->objectName() == "m_btnMaxValueDel")
	{
		ui->m_editMaxValue->Clear();
		UpdateExprValue(((CXExprRange*)m_pExprBase)->GetExprValueMax(), NULL);
	}
}

void QResultExprWidget_Range::SaveExprBase()
{
	((CXExprRange*)m_pExprBase)->m_strMinOptr = ui->m_cbbMinExpr->currentText();
	((CXExprRange*)m_pExprBase)->m_strMaxOptr = ui->m_cbbMaxExpr->currentText();
}

void QResultExprWidget_Range::LoadExprBase(CXExprBase* pExprBase)
{
	CXExprValue* pValue = ((CXExprRange*)m_pExprBase)->GetExprValue();
	CXExprValueMin* pValueMin = ((CXExprRange*)m_pExprBase)->GetExprValueMin();
	CXExprValueMax* pValueMax = ((CXExprRange*)m_pExprBase)->GetExprValueMax();
	LoadExprBase_ComboBox(ui->m_cbbMinExpr, ((CXExprRange*)m_pExprBase)->m_strMinOptr);
	LoadExprBase_ComboBox(ui->m_cbbMaxExpr, ((CXExprRange*)m_pExprBase)->m_strMaxOptr);
	LoadExprBase_Edit(ui->m_editResultParas, pValue);
	LoadExprBase_Edit(ui->m_editMinValue, pValueMin);
	LoadExprBase_Edit(ui->m_editMaxValue, pValueMax);

	CXExprValueRslt* pRslt = ((CXExprRange*)m_pExprBase)->GetExprValueRslt();
	if(pRslt->m_strValue == "0")
	{
		setBackgroundColor(QColor(255, 0, 0));
	}
}