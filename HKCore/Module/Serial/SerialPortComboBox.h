#pragma once

#include "SerialBaseComboBox.h"

// CSerialPortComboBox

class CSerialPortComboBox : public CSerialBaseComboBox
{
	DECLARE_DYNAMIC(CSerialPortComboBox)

public:
	CSerialPortComboBox();
	virtual ~CSerialPortComboBox();
	void InitPortByteString();
	void SetSelectByIDString(const CString &strPortByteID);

	void SetPortCount(long nCount);
	
private:
	long m_nPortCount;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
};


