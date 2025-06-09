#include "ResultExprWidget_Error.h"
#include "ui_ResultExprWidget_Error.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


QResultExprWidget_Error::QResultExprWidget_Error(QWidget *parent) :
    QResultExprWidget(parent),
    ui(new Ui::QResultExprWidget_Error)
{
    ui->setupUi(this);
	InitUI();
	InitConnect();
	InitLanguage();
	ui->m_cbbExprType->clear();

	m_cbbExprTypeList<</*tr("???????")*/g_sLangTxt_StateEstimate_AbsError<</*tr("??????")*/g_sLangTxt_StateEstimate_RelError;
	ui->m_cbbExprType->addItems(m_cbbExprTypeList);
}

QResultExprWidget_Error::~QResultExprWidget_Error()
{
    delete ui;
}

void QResultExprWidget_Error::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label,g_sLangTxt_ResultParameter,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_2,g_sLangTxt_Native_baselineparams,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_3,g_sLangTxt_Native_errorresult,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_5,g_sLangTxt_Native_errorlimit,XLang_Ctrls_QLabel);

}

void QResultExprWidget_Error::InitUI()
{
	setBackgroundColor(QColor(35, 168, 242));
	ui->m_cbbExpr->setShowType(QResultExprWidgetExprComboBox::LittleExpr);
}

void QResultExprWidget_Error::InitConnect()
{
	connect(ui->m_editResultParas, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editStdParas, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editErrorResult, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_editErrorValue, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_btnResultParasDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnStdParasDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnErrorResultDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnErrorValueDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
}

void QResultExprWidget_Error::OnSelectExpr()
{
	long nResult = FALSE;
	if(sender()->objectName() == "m_editResultParas")
	{
		nResult = OnSelectExpr_Report(ui->m_editResultParas);
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValue(), ui->m_editResultParas, nResult);
	}
	else if(sender()->objectName() == "m_editStdParas")
	{
		nResult = OnSelectExpr_Data(ui->m_editStdParas);
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueStd(), ui->m_editStdParas, nResult);
	}
	else if(sender()->objectName() == "m_editErrorResult")
	{
		nResult = OnSelectExpr_Report(ui->m_editErrorResult);
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueErrorRslt(), ui->m_editErrorResult, nResult);
	}
	else if(sender()->objectName() == "m_editErrorValue")
	{
		nResult = OnSelectExpr_Data(ui->m_editErrorValue);
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueError(), ui->m_editErrorValue, nResult);
	}
}

void QResultExprWidget_Error::OnDelectExpr()
{
	if(sender()->objectName() == "m_btnResultParasDel")
	{
		ui->m_editResultParas->Clear();
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValue(), NULL); 
	}
	else if(sender()->objectName() == "m_btnStdParasDel")
	{
		ui->m_editStdParas->Clear();
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueStd(), NULL); 
	}
	else if(sender()->objectName() == "m_btnErrorResultDel")
	{
		ui->m_editErrorResult->Clear();
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueErrorRslt(), NULL); 
	}
	else if(sender()->objectName() == "m_btnErrorValueDel")
	{
		ui->m_editErrorValue->Clear();
		UpdateExprValue(((CXExprError*)m_pExprBase)->GetExprValueError(), NULL); 
	}
}

void QResultExprWidget_Error::SaveExprBase()
{
	if(ui->m_cbbExprType->currentIndex() == 0)
	{
		((CXExprError*)m_pExprBase)->m_strMode = EXPRTYPE_ABS;
	}
	else
	{
		((CXExprError*)m_pExprBase)->m_strMode = EXPRTYPE_REAL;
	}

	((CXExprError*)m_pExprBase)->m_strOptr = ui->m_cbbExpr->currentText();
}

void QResultExprWidget_Error::LoadExprBase(CXExprBase* pExprBase)
{
	CXExprValue *m_pValue = ((CXExprError*)m_pExprBase)->GetExprValue();
	CXExprValueStd *m_pValueStd = ((CXExprError*)m_pExprBase)->GetExprValueStd();
	CXExprValueError *m_pValueError = ((CXExprError*)m_pExprBase)->GetExprValueError();
	CXExprValueErrorRslt *m_pValueErrorRslt = ((CXExprError*)m_pExprBase)->GetExprValueErrorRslt();
	LoadExprBase_ComboBox(ui->m_cbbExpr, ((CXExprError*)pExprBase)->m_strOptr);
	if(((CXExprError*)m_pExprBase)->m_strMode == EXPRTYPE_ABS)
	{
		LoadExprBase_ComboBox(ui->m_cbbExprType, 0);
	}
	else
	{
		LoadExprBase_ComboBox(ui->m_cbbExprType, 1);
	}
	LoadExprBase_Edit(ui->m_editResultParas, m_pValue);
	LoadExprBase_Edit(ui->m_editStdParas, m_pValueStd);
	LoadExprBase_Edit(ui->m_editErrorValue, m_pValueError);
	LoadExprBase_Edit(ui->m_editErrorResult, m_pValueErrorRslt);

	CXExprValueRslt* pRslt = ((CXExprError*)m_pExprBase)->GetExprValueRslt();
	if(pRslt->m_strValue == "0")
	{
		setBackgroundColor(QColor(255, 0, 0));
	}
}