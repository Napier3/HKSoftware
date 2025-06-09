
#pragma once

#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"

// CPxiValue 

class CPxiValue
{
public:
	CPxiValue();
	virtual ~CPxiValue();


public:
	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(const CString &newVal);
	CString GetDataType(void);
	void SetDataType(const CString &newVal);
	CString GetValue(void);
	void SetValue(const CString &newVal);
	CString GetUnit(void);
	void SetUnit(const CString &newVal);
};


