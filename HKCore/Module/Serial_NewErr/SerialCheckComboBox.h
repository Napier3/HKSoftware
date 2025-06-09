#pragma once

#include "SerialBaseComboBox.h"

// CSerialCheckComboBox

class CSerialCheckComboBox : public CSerialBaseComboBox
{
	DECLARE_DYNAMIC(CSerialCheckComboBox)

public:
	CSerialCheckComboBox();
	virtual ~CSerialCheckComboBox();
	void InitCheckByteString();
	void SetSelectByIDString(const CString &strCheckByteID);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
};


