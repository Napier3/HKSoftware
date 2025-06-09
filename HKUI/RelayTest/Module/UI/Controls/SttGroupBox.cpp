#include "SttGroupBox.h"
#include "../../../../Module/OSInterface/OSInterface.h"


QSttGroupBox::QSttGroupBox(QWidget *parent)
	: QGroupBox(parent)
{
	InitStyleSheet();
}

QSttGroupBox::QSttGroupBox(const QString &text,QWidget *parent)
: QGroupBox(text,parent)
{
	InitStyleSheet();
}

QSttGroupBox::~QSttGroupBox()
{

}

void QSttGroupBox::InitStyleSheet()
{
	CString strStyleSheet;

#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QGroupBox::title { padding-top: 10px; }");
	setStyleSheet(strStyleSheet);
#endif
	if (g_pSttGlobalFont != NULL)
	{
	     setFont(*g_pSttGlobalFont);
	}
}
