//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDevice_101Global.h

#pragma once

#include "..\..\Device\EpDeviceGlobal.h"

#define EPDCLASSID_CEPDEVICE101       (EPDCLASSID_EXLISTCLASS + 0X00000000)
#define EPDCLASSID_CEPDEVICEDATA101YC       (EPDCLASSID_EXLISTCLASS + 0X00000001)
#define EPDCLASSID_CEPDEVICEDATA101YK       (EPDCLASSID_EXLISTCLASS + 0X00000002)
#define EPDCLASSID_CEPDEVICEDATA101YT       (EPDCLASSID_EXLISTCLASS + 0X00000003)
#define EPDCLASSID_CEPDEVICEDATA101YX       (EPDCLASSID_EXLISTCLASS + 0X00000004)
#define EPDCLASSID_CEPDEVICENODE101YC       (EPDCLASSID_EXLISTCLASS + 0X00000005)
#define EPDCLASSID_CEPDEVICENODE101YK       (EPDCLASSID_EXLISTCLASS + 0X00000006)
#define EPDCLASSID_CEPDEVICENODE101YT       (EPDCLASSID_EXLISTCLASS + 0X00000007)
#define EPDCLASSID_CEPDEVICENODE101YX       (EPDCLASSID_EXLISTCLASS + 0X00000008)

class CEpDevice_101XmlRWKeys : public CEpDeviceXmlRWKeys
{
protected:
	CEpDevice_101XmlRWKeys();
	virtual ~CEpDevice_101XmlRWKeys();
	static long g_nEPDRef;

public:
	static CEpDevice_101XmlRWKeys* g_pXmlKeys;
	static CEpDevice_101XmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpDeviceNode101YxKey; //yx-node
	BSTR m_strCEpDeviceNode101YtKey; //yt-node
	BSTR m_strCEpDeviceNode101YkKey; //yk-node
	BSTR m_strCEpDeviceNode101YcKey; //yc-node
	BSTR m_strCEpDeviceData101YxKey; //yx
	BSTR m_strCEpDeviceData101YtKey; //yt
	BSTR m_strCEpDeviceData101YkKey; //yk
	BSTR m_strCEpDeviceData101YcKey; //yc
	BSTR m_strCEpDevice101Key; //device
	BSTR m_strValueKey; //value
	BSTR m_strMaxKey; //max
	BSTR m_strMinKey; //min
	BSTR m_strUnitKey; //unit

public:
	static BSTR CEpDeviceNode101YxKey()  {   return g_pXmlKeys->m_strCEpDeviceNode101YxKey;  }
	static BSTR CEpDeviceNode101YtKey()  {   return g_pXmlKeys->m_strCEpDeviceNode101YtKey;  }
	static BSTR CEpDeviceNode101YkKey()  {   return g_pXmlKeys->m_strCEpDeviceNode101YkKey;  }
	static BSTR CEpDeviceNode101YcKey()  {   return g_pXmlKeys->m_strCEpDeviceNode101YcKey;  }
	static BSTR CEpDeviceData101YxKey()  {   return g_pXmlKeys->m_strCEpDeviceData101YxKey;  }
	static BSTR CEpDeviceData101YtKey()  {   return g_pXmlKeys->m_strCEpDeviceData101YtKey;  }
	static BSTR CEpDeviceData101YkKey()  {   return g_pXmlKeys->m_strCEpDeviceData101YkKey;  }
	static BSTR CEpDeviceData101YcKey()  {   return g_pXmlKeys->m_strCEpDeviceData101YcKey;  }
	static BSTR CEpDevice101Key()  {   return g_pXmlKeys->m_strCEpDevice101Key;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
};



class CEpDevice_101ConstGlobal
{
private:
	CEpDevice_101ConstGlobal();
	virtual ~CEpDevice_101ConstGlobal();

public:
	static CEpDevice_101ConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpDevice_101ConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
