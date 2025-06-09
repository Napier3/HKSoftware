//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
