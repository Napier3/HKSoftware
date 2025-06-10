#include "CharEditWidget_Syn.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"

QCharEditWidget_Syn::QCharEditWidget_Syn(QWidget *parent)
	: QWidget(parent)
{
	m_pCharEditWidget = this;
	ui.setupUi(this);
        InitLanguage();
}

void QCharEditWidget_Syn::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.label_26, g_sLangTxt_Native_actionSetting, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.label_27, g_sLangTxt_Gradient_ActionTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_chkDoor, g_sLangTxt_Native_ActionThres, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.checkBox_Set2, g_sLangTxt_Native_DoubleTimeLimit, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.checkBox_Set3, g_sLangTxt_Native_TripleTimeLimit, XLang_Ctrls_QCheckBox);
}

QCharEditWidget_Syn::~QCharEditWidget_Syn()
{

}
