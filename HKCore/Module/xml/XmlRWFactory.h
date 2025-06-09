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

//2024-11-22 lijunqing �ⲿ�Ĵ�������
public:
	static void CreateXmlRWFactory(CXmlRWFactory *pXmlRWFactory);

protected:
	virtual CXmlRWDocBase* I_CreateXmlRWDoc(long nType);

	static CXmlRWFactory *g_pXmlRWFactory;
};
