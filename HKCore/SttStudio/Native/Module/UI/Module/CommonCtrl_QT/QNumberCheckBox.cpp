#include "QNumberCheckBox.h"
#include "../../../Module/API/GlobalConfigApi.h"

QNumberCheckBox::QNumberCheckBox(QWidget *parent)
	: QCheckBox(parent)
{
	InitStyleSheet();
}

QNumberCheckBox::QNumberCheckBox(const QString &text,QWidget *parent)
: QCheckBox(text,parent)
{
	InitStyleSheet();
}

QNumberCheckBox::~QNumberCheckBox()
{

}

void QNumberCheckBox::SetValue(int nValue)
{
	if (nValue)
	{
		setCheckState(Qt::Checked);
	} 
	else
	{
		setCheckState(Qt::Unchecked);
	}
}

int QNumberCheckBox::GetValue()
{
	if (checkState() == Qt::Checked)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}

void QNumberCheckBox::InitStyleSheet()
{
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QCheckBox::indicator:checked {image: url(:/ctrls/images/checked.png);} QCheckBox::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	setStyleSheet(strStyleSheet);
}