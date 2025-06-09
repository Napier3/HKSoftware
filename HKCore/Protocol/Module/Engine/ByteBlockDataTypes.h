#pragma once
#include "../../../module/baseclass/exbaselist.h"


class CByteBlockDataTypes :	public CExBaseList
{
public:
	CByteBlockDataTypes(void);
	virtual ~CByteBlockDataTypes(void);

public:
	void InitByTemplate(const CString &strEncodeMode);

};


class CPpTemplateEncodeModes :	public CExBaseList
{
public:
	CPpTemplateEncodeModes(void);
	virtual ~CPpTemplateEncodeModes(void);
};
