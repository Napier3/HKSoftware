#pragma once
#include "..\baseclass\baseobject.h"

class CXmlDbKeys :
	public CXmlRWKeys
{
private:
	CXmlDbKeys(void);
	virtual ~CXmlDbKeys(void);
	static long g_nXmlDbKeysRef;

public:
	static CXmlDbKeys* g_pXmlDbKeys;
	static CXmlDbKeys* CreateXmlDbKeys();
	static void Release();

public:
	//Ԫ������
	BSTR m_strDbKey;
	BSTR m_strDbTableKey;
	BSTR m_strTagsKey;
	BSTR m_strTagKey;
	BSTR m_strDataKey;

	//��������
	BSTR m_strDbIDKey;
	BSTR m_strDbNameKey;
	BSTR m_strUserIDKey;
	BSTR m_strUserNameKey;
	BSTR m_strDataTypeKey;
	BSTR m_strIsKeyKey;
};
