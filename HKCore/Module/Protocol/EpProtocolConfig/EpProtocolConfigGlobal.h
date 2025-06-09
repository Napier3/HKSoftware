//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpProtocolConfigGlobal.h

#pragma once

#include "ExBaseList.h"

#define EPCCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define EPCCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define EPCCLASSID_CEP101CONFIG       (EPCCLASSID_BASECLASS + 0X00000000)
#define EPCCLASSID_CEP104CONFIG       (EPCCLASSID_BASECLASS + 0X00000001)
#define EPCCLASSID_CEPPROTOCOLCONFIG       (EPCCLASSID_EXLISTCLASS + 0X00000002)

class CEpProtocolConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpProtocolConfigXmlRWKeys();
	virtual ~CEpProtocolConfigXmlRWKeys();
	static long g_nEPCRef;

public:
	static CEpProtocolConfigXmlRWKeys* g_pXmlKeys;
	static CEpProtocolConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpProtocolConfigKey; //ep-protocol-config
	BSTR m_strCEp104ConfigKey; //IEC60870-5-104
	BSTR m_strCEp101ConfigKey; //IEC60870-5-101
	BSTR m_strOddrKey; //oddr
	BSTR m_strYxAddrKey; //yx-addr
	BSTR m_strYcAddrKey; //yc-addr
	BSTR m_strYtAddrKey; //yt-addr

public:
	static BSTR CEpProtocolConfigKey()  {   return g_pXmlKeys->m_strCEpProtocolConfigKey;  }
	static BSTR CEp104ConfigKey()  {   return g_pXmlKeys->m_strCEp104ConfigKey;  }
	static BSTR CEp101ConfigKey()  {   return g_pXmlKeys->m_strCEp101ConfigKey;  }
	static BSTR OddrKey()  {   return g_pXmlKeys->m_strOddrKey;  }
	static BSTR YxAddrKey()  {   return g_pXmlKeys->m_strYxAddrKey;  }
	static BSTR YcAddrKey()  {   return g_pXmlKeys->m_strYcAddrKey;  }
	static BSTR YtAddrKey()  {   return g_pXmlKeys->m_strYtAddrKey;  }
};



class CEpProtocolConfigConstGlobal
{
private:
	CEpProtocolConfigConstGlobal();
	virtual ~CEpProtocolConfigConstGlobal();

public:
	static CEpProtocolConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpProtocolConfigConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
