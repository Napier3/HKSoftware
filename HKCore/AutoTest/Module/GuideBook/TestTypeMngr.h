#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/DataMngr/DataTypes.h"
#include "../../../Module/API/GlobalConfigApi.h"

static const CString g_strTestTypeXMLFile = _T("TestType.xml");

typedef CDataType CTestType;


class CTestTypes : public CDataTypes
{
public:
	CTestTypes();
	virtual ~CTestTypes();

public:
	long Open();
	long Open(const CString& strFile);

};

class CTestTypeMngr : public CXmlRWKeys
{
private:
	CTestTypeMngr();
	virtual ~CTestTypeMngr()	{}

	static long g_nTestTypeXMLKeysRef;

public:
	//static CTestTypeMngr* g_pTestTypeXMLKeys;
	static CTestTypes* g_pTestTypes;
	static CTestTypes* Create();
	static void Release();

public:
	BSTR m_strTestTypesKey;
	BSTR m_strTestTypeKey;
};

