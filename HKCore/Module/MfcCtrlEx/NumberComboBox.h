#pragma once


// CNumberComboBox

class CNumberComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CNumberComboBox)

public:
	CNumberComboBox();
	virtual ~CNumberComboBox();

	long GetNumber();
	long GetNumber(long &nNumber);
	void SelNumber(long nNumber);
	void InitNumbers(long nBegin, long nEnd, long nDefault=0);

private:
	long m_nDefault;

protected:
	DECLARE_MESSAGE_MAP()
};


