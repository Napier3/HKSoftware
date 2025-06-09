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
#ifdef _PSX_QT_LINUX_
	CString strStyleSheet;
	strStyleSheet.Format("QCheckBox::indicator:checked {image: url(%schecked.png);} QCheckBox::indicator:unchecked {image: url(%sunchecked.png);}",
		_P_GetResourcePath(),_P_GetResourcePath());
	setStyleSheet(strStyleSheet);

#endif
}