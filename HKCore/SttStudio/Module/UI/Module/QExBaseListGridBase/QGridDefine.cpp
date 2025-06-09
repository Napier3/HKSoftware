#include "QGridDefine.h"

QGV_ITEM::QGV_ITEM(const QString &text): QTableWidgetItem(text)
{
	lParam = 0;
	m_pEditFunc = NULL;
	iMaxLen = 0;
	dwValue = 0;
}

QGV_ITEM::~QGV_ITEM()
{

}

void QGV_ITEM::UpdateText(const QString &strText)
{
	setText(strText);
}
