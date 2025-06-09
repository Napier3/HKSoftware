#pragma once
#include "..\..\..\module\mfcctrlex\numbercombobox.h"

class CRepeatComboBox :	public CNumberComboBox
{
public:
	CRepeatComboBox(void);
	~CRepeatComboBox(void);

	long m_nRepeatCount;
	;
public:
	void InitComboBox(CExBaseObject *pGbItem);
	void InitComboBox(long nRepeatCount, const CString &strCalMode);
	long GetRepeatIndex();
};
