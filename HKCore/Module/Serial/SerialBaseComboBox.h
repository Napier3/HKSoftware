#pragma once


// CSerialCheckComboBox

class CSerialBaseComboBox : public CComboBox
{
public:
	CSerialBaseComboBox();
	virtual ~CSerialBaseComboBox();
	
public:
	virtual void SetSelect(const CString &strValue);
	virtual void SetSelect(long nValue);
	virtual BOOL GetSelect(CString &strText);
	virtual BOOL GetSelect(long &nData);
};


