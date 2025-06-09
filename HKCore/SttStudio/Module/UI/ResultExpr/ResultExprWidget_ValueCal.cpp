#include "ResultExprWidget_ValueCal.h"
#include "ui_ResultExprWidget_ValueCal.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


QResultExprWidget_ValueCal::QResultExprWidget_ValueCal(QWidget *parent) :
    QResultExprWidget(parent),
    ui(new Ui::QResultExprWidget_ValueCal)
{
    ui->setupUi(this);
    InitUI();
    InitConnect();
	InitLanguage();
}

QResultExprWidget_ValueCal::~QResultExprWidget_ValueCal()
{
    delete ui;
}

void QResultExprWidget_ValueCal::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label,g_sLangTxt_Native_paramone,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_2,g_sLangTxt_Native_paramtwo,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_3,g_sLangTxt_Native_operationresult,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_4,g_sLangTxt_Native_ReferenceValue,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_5,g_sLangTxt_Native_errorlimit,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_6,g_sLangTxt_Native_errorresult,XLang_Ctrls_QLabel);
}

void QResultExprWidget_ValueCal::InitUI()
{
    setBackgroundColor(QColor(35, 168, 242));
	ui->m_cbbCalType->setShowType(QResultExprWidgetExprComboBox::Cal);
	ui->m_cbbExpr->setShowType(QResultExprWidgetExprComboBox::LittleExpr);
}

void QResultExprWidget_ValueCal::InitConnect()
{
 	connect(ui->m_editValue1, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
 	connect(ui->m_editValue2, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
 	connect(ui->m_editCalResult, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editStdValue, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editErrorValue, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editErrorResult, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));

 	connect(ui->m_btnValue1Del, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
 	connect(ui->m_btnValue2Del, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
 	connect(ui->m_btnCalResultDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnStdValueDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnErrorValueDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnErrorResultDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));

 	connect(ui->m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
}

void QResultExprWidget_ValueCal::OnSelectExpr()
{
	long nResult = FALSE;
	if(sender()->objectName() == "m_editValue1")
	{
		nResult = OnSelectExpr_Data(ui->m_editValue1);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValue1(), ui->m_editValue1, nResult);
	}
	else if(sender()->objectName() == "m_editValue2")
	{
		nResult = OnSelectExpr_Data(ui->m_editValue2);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValue2(), ui->m_editValue2, nResult);
	}
	else if(sender()->objectName() == "m_editCalResult")
	{
		nResult = OnSelectExpr_Report(ui->m_editCalResult);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueCalRslt(), ui->m_editCalResult, nResult);
	}
	else if(sender()->objectName() == "m_editStdValue")
	{
		nResult = OnSelectExpr_Data(ui->m_editStdValue);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueStd(), ui->m_editStdValue, nResult);
	}
	else if(sender()->objectName() == "m_editErrorResult")
	{
		nResult = OnSelectExpr_Report(ui->m_editErrorResult);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueErrorRslt(), ui->m_editErrorResult, nResult);
	}
	else if(sender()->objectName() == "m_editErrorValue")
	{
		nResult = OnSelectExpr_Data(ui->m_editErrorValue);
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueError(), ui->m_editErrorValue, nResult);
	}
}

void QResultExprWidget_ValueCal::OnDelectExpr()
{
	if(sender()->objectName() == "m_btnValue1Del")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValue1(), NULL);
	}
	else if(sender()->objectName() == "m_btnValue2Del")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValue2(), NULL);
	}
	else if(sender()->objectName() == "m_btnCalResultDel")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueCalRslt(), NULL);
	}
	else if(sender()->objectName() == "m_btnStdValueDel")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueStd(), NULL);
	}
	else if(sender()->objectName() == "m_btnErrorResultDel")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueErrorRslt(), NULL);
	}
	else if(sender()->objectName() == "m_btnErrorValueDel")
	{
		UpdateExprValue(((CXExprValueCal*)m_pExprBase)->GetExprValueError(), NULL);
	}
}

void QResultExprWidget_ValueCal::SaveExprBase()
{	
	((CXExprValueCal*)m_pExprBase)->m_strCalOptr = ui->m_cbbCalType->currentText();

	if(ui->m_cbbExprType->currentIndex() == 0)
	{
		((CXExprValueCal*)m_pExprBase)->m_strMode = EXPRTYPE_ABS;
	}
	else
	{
		((CXExprValueCal*)m_pExprBase)->m_strMode = EXPRTYPE_REAL;
	}

	((CXExprValueCal*)m_pExprBase)->m_strOptr = ui->m_cbbExpr->currentText();
}

void QResultExprWidget_ValueCal::LoadExprBase(CXExprBase* pExprBase)
{
	CXExprValue1* m_pValue1 = ((CXExprValueCal*)m_pExprBase)->GetExprValue1();
	CXExprValue2* m_pValue2 = ((CXExprValueCal*)m_pExprBase)->GetExprValue2();
	CXExprValueCalRslt *m_pCalResult = ((CXExprValueCal*)m_pExprBase)->GetExprValueCalRslt();
	CXExprValueStd *m_pValueStd = ((CXExprValueCal*)m_pExprBase)->GetExprValueStd();
	CXExprValueError *m_pValueError = ((CXExprValueCal*)m_pExprBase)->GetExprValueError();
	CXExprValueErrorRslt *m_pValueErrorRslt = ((CXExprValueCal*)m_pExprBase)->GetExprValueErrorRslt();
	LoadExprBase_ComboBox(ui->m_cbbCalType, ((CXExprValueCal*)pExprBase)->m_strCalOptr);
	LoadExprBase_ComboBox(ui->m_cbbExpr, ((CXExprValueCal*)pExprBase)->m_strOptr);
	if(((CXExprValueCal*)m_pExprBase)->m_strMode == "abs")
	{
		LoadExprBase_ComboBox(ui->m_cbbExprType, 0);
	}
	else
	{
		LoadExprBase_ComboBox(ui->m_cbbExprType, 1);
	}
	LoadExprBase_Edit(ui->m_editValue1, m_pValue1);
	LoadExprBase_Edit(ui->m_editValue2, m_pValue2);
	LoadExprBase_Edit(ui->m_editCalResult, m_pCalResult);
	LoadExprBase_Edit(ui->m_editStdValue, m_pValueStd);
	LoadExprBase_Edit(ui->m_editErrorValue, m_pValueError);
	LoadExprBase_Edit(ui->m_editErrorResult, m_pValueErrorRslt);

	CXExprValueRslt* pRslt = ((CXExprValueCal*)m_pExprBase)->GetExprValueRslt();
	if(pRslt->m_strValue == "0")
	{
		setBackgroundColor(QColor(255, 0, 0));
	}
}