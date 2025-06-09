#pragma once

#include "XKeyDB.h"

class CXMatchVirTerminal
{
public:
	CXMatchVirTerminal();
	virtual ~CXMatchVirTerminal();

	CXKeyMatchRefList m_listMatchInputKeys;	//引用对象匹配的关键字
	CXKeyMatchRefList m_listMatchOutputKeys;	//引用对象匹配的关键字

	bool Match(CString strInDesc ,CString strOutDesc ,CXKeyDB *pKeyDb ,CString &strKeysDesc);

private:
	bool Match(CXKeyMatchRefList *pInputXKeys, CXKeyMatchRefList *pOutputXKeys ,CString &strKeysDesc);
};

