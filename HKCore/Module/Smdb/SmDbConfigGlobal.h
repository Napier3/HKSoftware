//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbConfigGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CEPCAPDBCONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CEPCAPDBFILECFG       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CEPCAPDBFILEAREA       (MngrCLASSID_BASECLASS + 0X00000002)

class CSmDbConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CSmDbConfigXmlRWKeys();
	virtual ~CSmDbConfigXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSmDbConfigXmlRWKeys* g_pXmlKeys;
	static CSmDbConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpCapDbFileAreaKey; //db-area
	BSTR m_strCSmDbFileCfgKey; //sm-db-file
	BSTR m_strCSmDbConfigKey; //ep-cap-db-config
	BSTR m_strSizeKey; //size
	BSTR m_strViewKey; //view
	BSTR m_strFileKey; //file
	BSTR m_strBeginPosKey; //view

public:
	static BSTR CEpCapDbFileAreaKey()  {   return g_pXmlKeys->m_strCEpCapDbFileAreaKey;  }
	static BSTR CSmDbFileCfgKey()  {   return g_pXmlKeys->m_strCSmDbFileCfgKey;  }
	static BSTR CSmDbConfigKey()  {   return g_pXmlKeys->m_strCSmDbConfigKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR ViewKey()  {   return g_pXmlKeys->m_strViewKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR BeginPosKey()  {   return g_pXmlKeys->m_strBeginPosKey;  }
};



class CSmDbConfigConstGlobal
{
private:
	CSmDbConfigConstGlobal();
	virtual ~CSmDbConfigConstGlobal();

public:
	static CSmDbConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSmDbConfigConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
