#pragma once

#include "SerialBaseComboBox.h"

// CSerialDataByteComboBox

class CSerialDataByteComboBox : public CSerialBaseComboBox
{
	DECLARE_DYNAMIC(CSerialDataByteComboBox)

public:
	CSerialDataByteComboBox();
	virtual ~CSerialDataByteComboBox();
	void InitDataByteByteString();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
};


