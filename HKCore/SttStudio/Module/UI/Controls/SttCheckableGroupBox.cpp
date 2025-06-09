#include "SttCheckableGroupBox.h"
#include "../../../../Module/OSInterface/OSInterface.h"


QSttCheckableGroupBox::QSttCheckableGroupBox(QWidget *parent)
: QGroupBox(parent)
{
	InitStyleSheet();
}


QSttCheckableGroupBox::~QSttCheckableGroupBox()
{

}

void QSttCheckableGroupBox::InitStyleSheet()
{
	CString strStyleSheet;

#ifndef _PSX_QT_WINDOWS_
	strStyleSheet = "QGroupBox::indicator { width: 20px; height: 20px; }"
		            "QGroupBox::title { padding-left: 10px; }"
                    "QGroupBox::indicator:checked { image: url(:/ctrls/images/checked.png); } "
                    "QGroupBox::indicator:unchecked { image: url(:/ctrls/images/unchecked.png); }";
    setStyleSheet(strStyleSheet);
#endif
	if (g_pSttGlobalFont != NULL)
	{
	    setFont(*g_pSttGlobalFont);
	}
}

