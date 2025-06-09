#pragma once

#include "SerialBaseComboBox.h"

// CSerialBaudRateComboBox

class CSerialBaudRateComboBox : public CSerialBaseComboBox
{
	DECLARE_DYNAMIC(CSerialBaudRateComboBox)

public:
	CSerialBaudRateComboBox();
	virtual ~CSerialBaudRateComboBox();
	void InitBaudRateString();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
};


