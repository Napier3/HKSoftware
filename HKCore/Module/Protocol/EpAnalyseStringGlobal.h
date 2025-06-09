//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseStringGlobal.h

#pragma once

#include "ExBaseList.h"

#define EPASCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define EPASCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define EPASCLASSID_CEPANALYSESTRING       (EPASCLASSID_EXLISTCLASS + 0X00000000)
#define EPASCLASSID_CEPANALYSEMNGR       (EPASCLASSID_EXLISTCLASS + 0X00000001)
#define EPASCLASSID_CEPANALYSESTRINGVAL       (EPASCLASSID_BASECLASS + 0X00000002)

class CEpAnalyseStringXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpAnalyseStringXmlRWKeys();
	virtual ~CEpAnalyseStringXmlRWKeys();
	static long g_nEPASRef;

public:
	static CEpAnalyseStringXmlRWKeys* g_pXmlKeys;
	static CEpAnalyseStringXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpAnalyseStringValKey; //ep-string-val
	BSTR m_strCEpAnalyseMngrKey; //ep-analyse-string
	BSTR m_strCEpAnalyseStringKey; //ep-string
	BSTR m_strStringKey; //string
	BSTR m_strValueKey; //value
	BSTR m_strValue2Key; //value2

public:
	static BSTR CEpAnalyseStringValKey()  {   return g_pXmlKeys->m_strCEpAnalyseStringValKey;  }
	static BSTR CEpAnalyseMngrKey()  {   return g_pXmlKeys->m_strCEpAnalyseMngrKey;  }
	static BSTR CEpAnalyseStringKey()  {   return g_pXmlKeys->m_strCEpAnalyseStringKey;  }
	static BSTR StringKey()  {   return g_pXmlKeys->m_strStringKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR Value2Key()  {   return g_pXmlKeys->m_strValue2Key;  }
};



class CEpAnalyseStringConstGlobal
{
private:
	CEpAnalyseStringConstGlobal();
	virtual ~CEpAnalyseStringConstGlobal();

public:
	static CEpAnalyseStringConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpAnalyseStringConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
