//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpPrjGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

//#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CPPPRJDEVICES       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CPPPRJDEVICE       (MngrCLASSID_EXLISTCLASS + 0X00000001)

class CPpPrjXmlRWKeys : public CXmlRWKeys
{
protected:
	CPpPrjXmlRWKeys();
	virtual ~CPpPrjXmlRWKeys();
	static long g_nMngrRef;

public:
	static CPpPrjXmlRWKeys* g_pXmlKeys;
	static CPpPrjXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPpPrjDeviceKey; //device
	BSTR m_strCPpPrjDevicesKey; //devices
	BSTR m_strTemplate_FileKey; //template-file
	BSTR m_strDdvm_FileKey; //ddvm-file

public:
	static BSTR CPpPrjDeviceKey()  {   return g_pXmlKeys->m_strCPpPrjDeviceKey;  }
	static BSTR CPpPrjDevicesKey()  {   return g_pXmlKeys->m_strCPpPrjDevicesKey;  }
	static BSTR Template_FileKey()  {   return g_pXmlKeys->m_strTemplate_FileKey;  }
	static BSTR Ddvm_FileKey()  {   return g_pXmlKeys->m_strDdvm_FileKey;  }
};



class CPpPrjConstGlobal
{
private:
	CPpPrjConstGlobal();
	virtual ~CPpPrjConstGlobal();

public:
	static CPpPrjConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CPpPrjConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
