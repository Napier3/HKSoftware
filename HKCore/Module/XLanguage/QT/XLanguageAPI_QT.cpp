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

//����QT����������Ӧ��ͬʱ�����ؼ���λ��
//pWidget��QT�ؼ�
BOOL AdjustSize(QWidget* pWidget)
{
    if(pWidget == NULL)
    {
        return FALSE;
    }
    long nOldWidth = pWidget->width();
    long nHeight = pWidget->height();
    pWidget->adjustSize();
    //��֤Y�᲻��
    pWidget->resize(pWidget->width(), nHeight);
    return TRUE;
}

//����ID��Ӧ�Ŀؼ����ı�
//pWidget��QT�ؼ��Ļ�����
//strID���ؼ���Ӧ��ID
bool xlang_SetLangStrToWidget(QWidget* pWidget, const CString& strID, long nCtrlsType)
{
    if(pWidget == NULL)
    {
        return FALSE;
    }

    QString strLanguageString;
    //����Դ�ļ�����Դ���л�ȡID��Ӧ���ַ���
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


//����ID��Ӧ�Ŀؼ���Ա���ı�
//pAction���ؼ���Ա
//strID�����ؼ���Ա��Ӧ��ID
bool xlang_SetLangStrToAction(QAction* pAction, const CString& strID)
{
    if(pAction == NULL)
    {
        return FALSE;
    }

    CString strLanguageString;
    //����Դ�ļ�����Դ���л�ȡID��Ӧ���ַ���
    strLanguageString = xlang_GetLgugStr(strID);
    pAction->setText(strLanguageString);
    //�ؼ���Ա�Ĳ���������Ӧ��
    return TRUE;
}
#endif

void xlang_GetLangStrByFile(CString& strTrans, const CString& strID)
{
	//����Դ�ļ�����Դ���л�ȡID��Ӧ���ַ���
	strTrans = xlang_GetLgugStr(strID);
}

