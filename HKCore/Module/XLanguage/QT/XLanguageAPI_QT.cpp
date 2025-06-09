#include "stdafx.h"
#include "XLanguageAPI_QT.h"

#ifndef _USE_NO_GUI_
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QToolButton>
#include <QRadioButton>
#include <QLineEdit>

//调用QT的字体自适应，同时调整控件的位置
//pWidget：QT控件
BOOL AdjustSize(QWidget* pWidget)
{
    if(pWidget == NULL)
    {
        return FALSE;
    }
    long nOldWidth = pWidget->width();
    long nHeight = pWidget->height();
    pWidget->adjustSize();
    //保证Y轴不变
    pWidget->resize(pWidget->width(), nHeight);
    return TRUE;
}

//设置ID对应的控件的文本
//pWidget：QT控件的基础类
//strID：控件对应的ID
bool xlang_SetLangStrToWidget(QWidget* pWidget, const CString& strID, long nCtrlsType)
{
    if(pWidget == NULL)
    {
        return FALSE;
    }

    QString strLanguageString;
    //从资源文件、资源类中获取ID对应的字符串
    strLanguageString = xlang_GetLgugStr(strID);
	
	return xlang_SetLangStrToWidget_Txt(pWidget, xlang_GetLgugStr(strID), nCtrlsType);
}

bool xlang_SetLangStrToWidget_Txt(QWidget* pWidget, const CString &strText,long nCtrlsType)
{
	if(pWidget == NULL)
	{
		return FALSE;
	}

	QString strClassName;
	switch (nCtrlsType)
	{
		case XLang_Ctrls_QPushButton:((QPushButton*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QToolButton:((QToolButton*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QMenu:((QMenu*)pWidget)->setTitle(strText);break;
		case XLang_Ctrls_QLabel:((QLabel*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QCheckBox:((QCheckBox*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QGroupBox:((QGroupBox*)pWidget)->setTitle(strText);break;
		case XLang_Ctrls_QRadioButton:((QRadioButton*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QLineEdit:((QLineEdit*)pWidget)->setText(strText);break;
		case XLang_Ctrls_QTabWidget:
		strClassName = pWidget->parentWidget()->parentWidget()->metaObject()->className();
		if(strClassName == "QTabWidget")
		{
			QTabWidget* pTabWidget = (QTabWidget*)pWidget->parentWidget()->parentWidget();
			pTabWidget->setTabText(pTabWidget->indexOf(pWidget), strText);
		}
		break;
	default:
		break;
	}

	return AdjustSize(pWidget);
}


//设置ID对应的控件成员的文本
//pAction：控件成员
//strID：：控件成员对应的ID
bool xlang_SetLangStrToAction(QAction* pAction, const CString& strID)
{
    if(pAction == NULL)
    {
        return FALSE;
    }

    CString strLanguageString;
    //从资源文件、资源类中获取ID对应的字符串
    strLanguageString = xlang_GetLgugStr(strID);
    pAction->setText(strLanguageString);
    //控件成员的布局是自适应的
    return TRUE;
}
#endif

void xlang_GetLangStrByFile(CString& strTrans, const CString& strID)
{
	//从资源文件、资源类中获取ID对应的字符串
	strTrans = xlang_GetLgugStr(strID);
}

