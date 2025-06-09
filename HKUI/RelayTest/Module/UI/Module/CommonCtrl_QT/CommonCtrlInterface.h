#pragma once

class CCommonCtrlInterface
{
public:
	CCommonCtrlInterface(){}
	virtual ~CCommonCtrlInterface(){}

	virtual void UpdateText(const QString &strText) = 0;
};
