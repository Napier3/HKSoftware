#pragma once

#include "DataType.h"
#include "..\BaseClass\ExBaseListComboBox.h"
// CDataTypeComboBox

class CDataTypeComboBox : public CExBaseListComboBox
{
	DECLARE_DYNAMIC(CDataTypeComboBox)

public:
	CDataTypeComboBox();
	virtual ~CDataTypeComboBox();

public:
	void ShowDataType(CDataType *pDataType);

	CString GetSelectIndex();
	long GetSelectIndex2();
	
	BOOL SetSelByIndex(const CString &strIndex);
	BOOL SetSelByIndex(long nIndex);


protected:
	DECLARE_MESSAGE_MAP()
};


