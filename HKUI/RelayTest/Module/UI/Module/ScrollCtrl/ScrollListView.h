#ifndef ScrollListView_H
#define ScrollListView_H

#include "ScrollDef.h"
#include <QListView>

class QScrollListView : public QListView
{
	Q_OBJECT
public:
	explicit QScrollListView(QWidget* pParent = NULL);
	virtual ~QScrollListView();

	bool IsMoving() { return m_oAttri.m_bIsMoving; }
	bool IsPressed() { return m_oAttri.m_bIsPressed; }
	void SetMoving(bool bIsMoving) { m_oAttri.m_bIsMoving = bIsMoving; }
	void SetPressed(bool bIsPressed) { m_oAttri.m_bIsPressed = bIsPressed; }

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

private:
	tagSliderAttri m_oAttri;
};

#endif//!ScrollListView_H