//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MmsRcdFilesMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CMMSDEVICES       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CMMSDEVICE       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CRCDDIR       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CRCDFILE       (MngrCLASSID_BASECLASS + 0X00000003)

class CMmsRcdFilesMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CMmsRcdFilesMngrXmlRWKeys();
	virtual ~CMmsRcdFilesMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CMmsRcdFilesMngrXmlRWKeys* g_pXmlKeys;
	static CMmsRcdFilesMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCRcdFileKey; //rcd-file
	BSTR m_strCRcdDirKey; //rcd-dir
	BSTR m_strCMmsDeviceKey; //mms-device
	BSTR m_strCMmsDevicesKey; //mms-devices
	BSTR m_strDirsizeKey; //dirsize
	BSTR m_strDirtimeKey; //dirtime
	BSTR m_strFilesizeKey; //filesize
	BSTR m_strFiletimeKey; //filetime

public:
	static BSTR CRcdFileKey()  {   return g_pXmlKeys->m_strCRcdFileKey;  }
	static BSTR CRcdDirKey()  {   return g_pXmlKeys->m_strCRcdDirKey;  }
	static BSTR CMmsDeviceKey()  {   return g_pXmlKeys->m_strCMmsDeviceKey;  }
	static BSTR CMmsDevicesKey()  {   return g_pXmlKeys->m_strCMmsDevicesKey;  }
	static BSTR DirsizeKey()  {   return g_pXmlKeys->m_strDirsizeKey;  }
	static BSTR DirtimeKey()  {   return g_pXmlKeys->m_strDirtimeKey;  }
	static BSTR FilesizeKey()  {   return g_pXmlKeys->m_strFilesizeKey;  }
	static BSTR FiletimeKey()  {   return g_pXmlKeys->m_strFiletimeKey;  }
};



class CMmsRcdFilesMngrConstGlobal
{
private:
	CMmsRcdFilesMngrConstGlobal();
	virtual ~CMmsRcdFilesMngrConstGlobal();

public:
	static CMmsRcdFilesMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMmsRcdFilesMngrConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
