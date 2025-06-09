#include "SttDvmEdit.h"

QSttDvmEdit::QSttDvmEdit(CDvmData *pData,QWidget *parent):QLineEdit(parent)
{
	m_Parent = parent;
	m_pData = pData;
	connect(this,SIGNAL(editingFinished()),this,SLOT(slot_OnEdited()));
}

void QSttDvmEdit::slot_OnEdited()
{
	CString str = text();
	setText(str);
	m_pData->m_strValue = str;
}
