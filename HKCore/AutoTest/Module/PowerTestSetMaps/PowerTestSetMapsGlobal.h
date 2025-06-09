//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PowerTestSetMapsGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define SetMapMngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define SetMapMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define SETMAPMNGRCLASSID_CPOWERTESTSETMAPS       (SetMapMngrCLASSID_EXLISTCLASS + 0X00000000)
#define SETMAPMNGRCLASSID_CSETMAP       (SetMapMngrCLASSID_BASECLASS + 0X00000001)
#define SETMAPMNGRCLASSID_CPARAMAP       (SetMapMngrCLASSID_BASECLASS + 0X00000002)

class CPowerTestSetMapsXmlRWKeys : public CXmlRWKeys
{
protected:
	CPowerTestSetMapsXmlRWKeys();
	virtual ~CPowerTestSetMapsXmlRWKeys();
	static long g_nSetMapMngrRef;

public:
	static CPowerTestSetMapsXmlRWKeys* g_pXmlKeys;
	static CPowerTestSetMapsXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSetMapKey; //set-map
	BSTR m_strCParaMapKey; //para-map
	BSTR m_strCPowerTestSetMapsKey; //powertest-set-maps
	BSTR m_strMapKey; //map

public:
	static BSTR CSetMapKey()  {   return g_pXmlKeys->m_strCSetMapKey;  }
	static BSTR CParaMapKey()  {   return g_pXmlKeys->m_strCParaMapKey;  }	
	static BSTR CPowerTestSetMapsKey()  {   return g_pXmlKeys->m_strCPowerTestSetMapsKey;  }
	static BSTR MapKey()  {   return g_pXmlKeys->m_strMapKey;  }
};



class CPowerTestSetMapsConstGlobal
{
private:
	CPowerTestSetMapsConstGlobal();
	virtual ~CPowerTestSetMapsConstGlobal();

public:
	static CPowerTestSetMapsConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CPowerTestSetMapsConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
