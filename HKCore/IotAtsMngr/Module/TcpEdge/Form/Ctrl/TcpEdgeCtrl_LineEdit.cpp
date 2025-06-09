#include "stdafx.h"
#include "TcpEdgeCtrl_LineEdit.h"

CTcpEdgeCtrl_LineEdit::CTcpEdgeCtrl_LineEdit(QWidget *parent)
{

}

CTcpEdgeCtrl_LineEdit::~CTcpEdgeCtrl_LineEdit()
{

}

void CTcpEdgeCtrl_LineEdit::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}