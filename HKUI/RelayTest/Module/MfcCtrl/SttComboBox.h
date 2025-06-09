#pragma once

#include "SttWndCtrlInterface.h"
#include "..\..\..\Module\BaseClass\ExBaseListComboBox.h"
#include "..\..\..\Module\MfcCtrlEx\NumberComboBox.h"

// CSttComboBox

#define STT_CMB_DATA_MODE_ID        0
#define STT_CMB_DATA_MODE_INDEX  1

class CSttComboBox : public CExBaseListComboBox, public CSttWndCtrlInterface
{
public:
	CSttComboBox();
	virtual ~CSttComboBox();

	UINT m_nValueDataMode;
public:
	virtual void ShowData();
	virtual void SaveData();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchange();
};



class CSttNumberComboBox : public CNumberComboBox, public CSttWndCtrlInterface
{
public:
	CSttNumberComboBox();
	virtual ~CSttNumberComboBox();

public:
	virtual void ShowData();
	virtual void SaveData();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchange();
};


