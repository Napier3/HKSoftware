#pragma once

#include "XKeyDB.h"

class CXMatchVirTerminal
{
public:
	CXMatchVirTerminal();
	virtual ~CXMatchVirTerminal();

	CXKeyMatchRefList m_listMatchInputKeys;	//���ö���ƥ��Ĺؼ���
	CXKeyMatchRefList m_listMatchOutputKeys;	//���ö���ƥ��Ĺؼ���

	bool Match(CString strInDesc ,CString strOutDesc ,CXKeyDB *pKeyDb ,CString &strKeysDesc);

private:
	bool Match(CXKeyMatchRefList *pInputXKeys, CXKeyMatchRefList *pOutputXKeys ,CString &strKeysDesc);
};

