#ifndef ScrollTreeWidget_H
#define ScrollTreeWidget_H

#include "ScrollDef.h"
#include <QTreeWidget>

class QScrollTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	explicit QScrollTreeWidget(QWidget* pParent = NULL);
	virtual ~QScrollTreeWidget();

	bool IsMoving() { return m_oAttri.m_bIsMoving; }
	bool IsPressed() { return m_oAttri.m_bIsPressed; }
	void SetMoving(bool bIsMoving) { m_oAttri.m_bIsMoving = bIsMoving; }
	void SetPressed(bool bIsPressed) { m_oAttri.m_bIsPressed = bIsPressed; }
	bool IsScrollMoving();

protected:
	virtual void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	virtual void mouseReleaseEvent(QMouseEvent *ev);

private:
	tagSliderAttri m_oAttri;
};

#endif//!ScrollTreeWidget_H