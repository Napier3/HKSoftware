#include "SttDvmEdit.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../SttTestCntrFrameBase.h"

QSttDvmEdit::QSttDvmEdit(CDvmData *pData,QWidget *parent):QSttLineEdit(parent)
{
	m_Parent = parent;
	m_pData = pData;
#ifdef _PSX_QT_LINUX_
	connect(this,SIGNAL(clicked()),this,SLOT(slot_OnClick()));
#endif
	connect(this,SIGNAL(editingFinished()),this,SLOT(slot_DataEditingFinished()));

#ifndef _PSX_QT_LINUX_
//	connect(this,SIGNAL(textChanged(const QString&)),this,SLOT(slot_TextChanged(const QString&)));
#endif
}

void QSttDvmEdit::mousePressEvent(QMouseEvent *event)
{
	//如果单击了就触发clicked信号
	if (event->button() == Qt::LeftButton)
	{
		//触发clicked信号
		emit clicked();
	}

	//将该事件传给父类处理
	QLineEdit::mousePressEvent(event);
}

void QSttDvmEdit::slot_TextChanged(const QString &text)
{
	m_pData->m_strValue = text;
}

void QSttDvmEdit::slot_OnClick()
{
	CString str = text();
	GetEngWidgetBoard_DigitData(str,this);

//  	GetEngWidgetBoard_DigitData(str, m_Parent);
//  	setText(str);
//  	m_pData->m_strValue = str;
}

void QSttDvmEdit::slot_DataEditingFinished()
{
	m_pData->m_strValue = text();
}
