#ifndef ScrollDef_H
#define ScrollDef_H

#include <QScrollBar>
#include <QMouseEvent>

enum tagSliderDir
{ 
	DEFAULT = 0, 
	VERI = 0, 
	HORI 
};

struct tagSliderAttri
{
	QPoint  m_oPressedAxis;
	QScrollBar *m_pCurScrollBar;
	tagSliderDir m_tagSliderDir;
	bool m_bIsMoving;
	bool m_bIsPressed;
	long m_nScrollVal;
	long m_nPreOffset;
	long m_nScrollLastMaxVal;
	long m_nCellIndex;
	long m_nPreValSaved;

	tagSliderAttri() : m_oPressedAxis(0, 0)
	{
		m_pCurScrollBar = NULL;
		m_tagSliderDir = DEFAULT;
		m_bIsMoving = false;
		m_bIsPressed = false;
		m_nScrollVal = 0;
		m_nPreOffset = 0;
		m_nCellIndex = 0;
		m_nPreValSaved = 0;
	}
};

#endif//!ScrollDef_H