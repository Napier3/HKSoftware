#include "SttCheckBox.h"
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/API/GlobalConfigApi.h"
//#include "../SttTestCntrFrameBase.h"

QSttCheckBox::QSttCheckBox(QWidget *parent)
	: QCheckBox(parent)
{
	InitStyleSheet();
}

QSttCheckBox::QSttCheckBox(const QString &text,QWidget *parent)
: QCheckBox(text,parent)
{
	InitStyleSheet();
}

QSttCheckBox::~QSttCheckBox()
{

}

void QSttCheckBox::InitStyleSheet()
{
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QCheckBox::indicator:checked {image: url(:/ctrls/images/checked.png);} QCheckBox::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
	setStyleSheet(strStyleSheet);
#endif

	if (g_pSttGlobalFont != NULL)
	{
		setFont(*g_pSttGlobalFont);
	}
}