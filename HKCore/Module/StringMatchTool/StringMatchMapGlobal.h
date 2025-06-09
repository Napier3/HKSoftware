//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StringMatchMapGlobal.h

#pragma once

#include "ExBaseList.h"

#define SMMCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define SMMCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define SMMCLASSID_CSMMKEY       (SMMCLASSID_BASECLASS + 0X00000000)
#define SMMCLASSID_CSMMGROUPKEY       (SMMCLASSID_EXLISTCLASS + 0X00000001)
#define SMMCLASSID_CSMMMULTIKEY       (SMMCLASSID_EXLISTCLASS + 0X00000002)
#define SMMCLASSID_CSMMGROUPKEYS       (SMMCLASSID_EXLISTCLASS + 0X00000003)
#define SMMCLASSID_CSMMKEYMNGR       (SMMCLASSID_EXLISTCLASS + 0X00000004)
#define SMMCLASSID_CSMMREFKEY       (SMMCLASSID_BASECLASS + 0X00000005)
#define SMMCLASSID_CSMMREFGROUPKEY       (SMMCLASSID_BASECLASS + 0X00000006)
#define SMMCLASSID_CSMMMACTHTOOL       (SMMCLASSID_EXLISTCLASS + 0X00000007)
#define SMMCLASSID_CSMMREFGROUPKEYS       (SMMCLASSID_BASECLASS + 0X00000008)

class CStringMatchMapXmlRWKeys : public CXmlRWKeys
{
protected:
	CStringMatchMapXmlRWKeys();
	virtual ~CStringMatchMapXmlRWKeys();
	static long g_nSMMRef;

public:
	static CStringMatchMapXmlRWKeys* g_pXmlKeys;
	static CStringMatchMapXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSmmRefGroupKeysKey; //ref-group-keys
	BSTR m_strCSmmGroupKeysKey; //group-keys
	BSTR m_strCSmmMacthToolKey; //
	BSTR m_strCSmmRefGroupKeyKey; //ref-group-key
	BSTR m_strCSmmRefKeyKey; //ref-key
	BSTR m_strCSmmKeyMngrKey; //key-mngr
	BSTR m_strCSmmMultiKeyKey; //multi-key
	BSTR m_strCSmmGroupKeyKey; //group-key
	BSTR m_strCSmmKeyKey; //key
	BSTR m_strIndexKey; //index
	BSTR m_strTypeKey; //type

public:
	static BSTR CSmmRefGroupKeysKey()  {   return g_pXmlKeys->m_strCSmmRefGroupKeysKey;  }
	static BSTR CSmmGroupKeysKey()  {   return g_pXmlKeys->m_strCSmmGroupKeysKey;  }
	static BSTR CSmmMacthToolKey()  {   return g_pXmlKeys->m_strCSmmMacthToolKey;  }
	static BSTR CSmmRefGroupKeyKey()  {   return g_pXmlKeys->m_strCSmmRefGroupKeyKey;  }
	static BSTR CSmmRefKeyKey()  {   return g_pXmlKeys->m_strCSmmRefKeyKey;  }
	static BSTR CSmmKeyMngrKey()  {   return g_pXmlKeys->m_strCSmmKeyMngrKey;  }
	static BSTR CSmmMultiKeyKey()  {   return g_pXmlKeys->m_strCSmmMultiKeyKey;  }
	static BSTR CSmmGroupKeyKey()  {   return g_pXmlKeys->m_strCSmmGroupKeyKey;  }
	static BSTR CSmmKeyKey()  {   return g_pXmlKeys->m_strCSmmKeyKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
};



class CStringMatchMapConstGlobal
{
private:
	CStringMatchMapConstGlobal();
	virtual ~CStringMatchMapConstGlobal();

public:
	static CStringMatchMapConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CStringMatchMapConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
