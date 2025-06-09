//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgToolGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define IFTCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define IFTCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define IFTCLASSID_CIECCFGFILE       (IFTCLASSID_BASECLASS + 0X00000000)
#define IFTCLASSID_CIECCFGFILES       (IFTCLASSID_EXLISTCLASS + 0X00000001)
#define IFTCLASSID_CSCLFILE       (IFTCLASSID_BASECLASS + 0X00000002)
#define IFTCLASSID_CSCLFILES       (IFTCLASSID_EXLISTCLASS + 0X00000003)
#define IFTCLASSID_CIECCFGTOOL       (IFTCLASSID_EXLISTCLASS + 0X00000004)
#define IFTCLASSID_CIECCFGFILE_DEVICE       (IFTCLASSID_EXLISTCLASS + 0X00000005)

class CIecCfgToolXmlRWKeys : public CXmlRWKeys
{
protected:
	CIecCfgToolXmlRWKeys();
	virtual ~CIecCfgToolXmlRWKeys();
	static long g_nIFTRef;

public:
	static CIecCfgToolXmlRWKeys* g_pXmlKeys;
	static CIecCfgToolXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIecCfgToolKey; //iecfg-tool
	BSTR m_strCSclFilesKey; //scl-files
	BSTR m_strCSclFileKey; //scl-file
	BSTR m_strCIecCfgFilesKey; //iecfg-files
	BSTR m_strCIecCfgFileKey; //iecfg-file
	BSTR m_strCIecCfgFileDeviceKey; //iecfg-file-device

	BSTR m_strUseDebugKey; 
	BSTR m_strAutoSetUIChIndexKey; //
	BSTR m_strIecCfgDownDllFileKey; //
	BSTR m_strViewOnlyUsedInChsKey; //view-only-used-inch
	BSTR m_strViewChsPathKey; //"view-chs-path"

	BSTR m_strTscdNameKey; //tscd-name
	BSTR m_strAT02D_UseHarmKey; //"use-harm"    �ܺ��  20200615 ��������ģ��ʱ�Ƿ�����г��
	BSTR m_strAT02D_VerifyVolCurChannelKey; //"verify-volcur" �ܺ�� 20201128  AT02D���������ļ�ʱ��У����붼������ѹ����ͨ����������PNI302�������ļ�������ֻ������ѹͨ������ʱ����Ҫ��У�鹦��
	BSTR m_strLinkGoutKey; //"link-gout"    �ܺ��  20200615 ����Gout�����
	BSTR m_strAutoOpenLastKey; //"auto-open-last"    �ܺ��  20200914 �Ƿ��Զ����ϴδ򿪹��������ļ�

public:
	static BSTR CIecCfgToolKey()  {   return g_pXmlKeys->m_strCIecCfgToolKey;  }
	static BSTR CSclFilesKey()  {   return g_pXmlKeys->m_strCSclFilesKey;  }
	static BSTR CSclFileKey()  {   return g_pXmlKeys->m_strCSclFileKey;  }
	static BSTR CIecCfgFilesKey()  {   return g_pXmlKeys->m_strCIecCfgFilesKey;  }
	static BSTR CIecCfgFileKey()  {   return g_pXmlKeys->m_strCIecCfgFileKey;  }
	static BSTR CIecCfgFileDeviceKey()  {   return g_pXmlKeys->m_strCIecCfgFileDeviceKey;  }
};



class CIecCfgToolConstGlobal
{
private:
	CIecCfgToolConstGlobal();
	virtual ~CIecCfgToolConstGlobal();

public:
	static CIecCfgToolConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIecCfgToolConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
