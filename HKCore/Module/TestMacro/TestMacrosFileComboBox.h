#pragma once

#include "../BaseClass/ExBaseListComboBox.h"

class CTestMacrosFileComboBox : public CExBaseListComboBox
{
public:
	CTestMacrosFileComboBox();
	virtual ~CTestMacrosFileComboBox();

	void ShowTestMacrosFiles();

protected:
	virtual void ShowBaseList();
};


