#pragma once

#include "SttWndCtrlInterface.h"
#include "..\..\..\Module\BaseClass\ExBaseListComboBox.h"
#include "..\AdjustTool\UI\SttAdjTRangeGrid.h"

// CSttTrangeComboBox

class CSttTrangeComboBox : public CExBaseListComboBox
{
public:
	CSttTrangeComboBox();
	virtual ~CSttTrangeComboBox();

public:
	virtual BOOL CanAdd(CExBaseObject *pObj);

};

