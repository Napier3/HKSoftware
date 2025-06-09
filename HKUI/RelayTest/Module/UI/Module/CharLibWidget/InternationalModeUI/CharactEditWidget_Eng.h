#pragma once
#include"../QImpCharactWidget.h"
#include "../../../../XLangResource_Native.h"

class QCharactEditWidget_Eng :
	public QImpCharactWidget
{
public:
	explicit QCharactEditWidget_Eng(CCharacteristics *pCharacteristics, QWidget *parent = 0, bool bUseOptrButtons = FALSE, BOOL bUseMouseMoveChar = FALSE, BOOL bChangePlot = FALSE);
	virtual ~QCharactEditWidget_Eng(void);
	void SetChangePlot(BOOL bChangePlot);
protected:
	BOOL m_bChangePlot;
	virtual void initPlot();
};
