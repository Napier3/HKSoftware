#pragma once
#include "XmlRWBase.h"

class CXmlRWFactory
{
public:
	CXmlRWFactory(void);
	virtual ~CXmlRWFactory(void);

public:
	static CXmlRWDocBase* CreateXmlRWDoc(long nType);
	static CXmlRWDocBase* CreateXmlRWDoc(const CString &strFile, long nType);
};
