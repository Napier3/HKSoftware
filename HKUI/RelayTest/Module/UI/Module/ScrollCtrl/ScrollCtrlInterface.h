#ifndef ScrollCtrlInterface_H
#define ScrollCtrlInterface_H

#include "ScrollDef.h"
#include <QMouseEvent>

class CScrollCtrlInterface
{
public:
	CScrollCtrlInterface();
	virtual ~CScrollCtrlInterface();

	bool IsMoving() { return m_oAttri.m_bIsMoving; }
	bool IsPressed() { return m_oAttri.m_bIsPressed; }
	void SetMoving(bool bIsMoving) { m_oAttri.m_bIsMoving = bIsMoving; }
	void SetPressed(bool bIsPressed) { m_oAttri.m_bIsPressed = bIsPressed; }

protected:
	void InitScrollCtrl(QScrollBar *pCurScrollBar);
	virtual void mousePressEvent_ScrollBase(QMouseEvent *ev);
	virtual bool mouseMoveEvent_ScrollBase(QMouseEvent *ev);
	virtual bool mouseReleaseEvent_ScrollBase(QMouseEvent *ev);

private:
	tagSliderAttri m_oAttri;
};

#endif//!ScrollCtrlInterface_H