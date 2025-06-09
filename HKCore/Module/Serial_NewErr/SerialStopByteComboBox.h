#pragma once

#include "SerialBaseComboBox.h"

// CSerialStopByteComboBox

class CSerialStopByteComboBox : public CSerialBaseComboBox
{
	DECLARE_DYNAMIC(CSerialStopByteComboBox)

public:
	CSerialStopByteComboBox();
	virtual ~CSerialStopByteComboBox();
	void InitStopByteByteString();
	
	virtual void SetSelect(float fStopBit);
	virtual BOOL GetSelect(float &fData);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
};


