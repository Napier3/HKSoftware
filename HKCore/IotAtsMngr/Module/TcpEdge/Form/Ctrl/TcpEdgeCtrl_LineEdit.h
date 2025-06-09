#ifndef _TCPEDGECTRL_LINEEDIT_H_
#define _TCPEDGECTRL_LINEEDIT_H_

#include <QLineEdit>
#include <QMouseEvent>

class CTcpEdgeCtrl_LineEdit : public QLineEdit
{
	Q_OBJECT
public:
	CTcpEdgeCtrl_LineEdit(QWidget *parent = 0);
	virtual ~CTcpEdgeCtrl_LineEdit();

	void mousePressEvent(QMouseEvent* event);

signals:
	void clicked();
};

#endif