#include "QGridDefine.h"

QGV_ITEM::QGV_ITEM(const QString &text): QTableWidgetItem(text)
{
	lParam = 0;
	m_pEditFunc = NULL;
}

QGV_ITEM::~QGV_ITEM()
{

}
