//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceGlobal.h

#pragma once

#include "ExBaseList.h"
#include "..\EpGlobalClassIDBaseDefine.h"

#define EPDCLASSID_CEPDEVICE       (EPDCLASSID_EXLISTCLASS + 0X00000000)
#define EPDCLASSID_CEPDEVICENODE       (EPDCLASSID_EXLISTCLASS + 0X00000001)
#define EPDCLASSID_CEPDEVICEDATA       (EPDCLASSID_BASECLASS + 0X00000002)
#define EPDCLASSID_CEPTAG            (EPDCLASSID_BASECLASS + 0X00000003)
#define EPDCLASSID_CEPTAGS            (EPDCLASSID_EXLISTCLASS + 0X00000004)

class CEpDeviceXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpDeviceXmlRWKeys();
	virtual ~CEpDeviceXmlRWKeys();
	static long g_nEPDRef;

public:
	static CEpDeviceXmlRWKeys* g_pXmlKeys;
	static CEpDeviceXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpDeviceDataKey; //data
	BSTR m_strCEpDeviceNodeKey; //node
	BSTR m_strCEpDeviceKey; //device
	BSTR m_strUsedKey; //use

public:
	static BSTR CEpDeviceDataKey()  {   return g_pXmlKeys->m_strCEpDeviceDataKey;  }
	static BSTR CEpDeviceNodeKey()  {   return g_pXmlKeys->m_strCEpDeviceNodeKey;  }
	static BSTR CEpDeviceKey()  {   return g_pXmlKeys->m_strCEpDeviceKey;  }
	static BSTR UsedKey()  {   return g_pXmlKeys->m_strUsedKey;  }
};



class CEpDeviceConstGlobal
{
private:
	CEpDeviceConstGlobal();
	virtual ~CEpDeviceConstGlobal();

public:
	static CEpDeviceConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpDeviceConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
