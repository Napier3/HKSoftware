#include "SttLineEdit.h"

QSttLineEdit::QSttLineEdit(QWidget *parent):QLineEdit(parent)
{

}

void QSttLineEdit::mousePressEvent(QMouseEvent *event)
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

void QSttLineEdit::UpdateText(const QString &strText)
{
	setText(strText);
	SetEditFinished();
}