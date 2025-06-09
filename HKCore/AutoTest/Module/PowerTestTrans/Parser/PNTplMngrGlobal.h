//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplMngrGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CPNTPLROOT       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CPNTPLELEMENT       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CPNTPLEQUATION       (MngrCLASSID_BASECLASS + 0X00000002)
#define MNGRCLASSID_CPNTPLTEXT       (MngrCLASSID_BASECLASS + 0X00000003)
#define MNGRCLASSID_CPNTPLGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000004)

class CPNTplMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CPNTplMngrXmlRWKeys();
	virtual ~CPNTplMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CPNTplMngrXmlRWKeys* g_pXmlKeys;
	static CPNTplMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPNTplGroupKey; //pntplgroup
	BSTR m_strCPNTplTextKey; //pntpltext
	BSTR m_strCPNTplEquationKey; //pntplequation
	BSTR m_strCPNTplElementKey; //pntplelement
	BSTR m_strCPNTplRootKey; //pntplroot
	BSTR m_strValueKey; //value

public:
	static BSTR CPNTplGroupKey()  {   return g_pXmlKeys->m_strCPNTplGroupKey;  }
	static BSTR CPNTplTextKey()  {   return g_pXmlKeys->m_strCPNTplTextKey;  }
	static BSTR CPNTplEquationKey()  {   return g_pXmlKeys->m_strCPNTplEquationKey;  }
	static BSTR CPNTplElementKey()  {   return g_pXmlKeys->m_strCPNTplElementKey;  }
	static BSTR CPNTplRootKey()  {   return g_pXmlKeys->m_strCPNTplRootKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CPNTplMngrConstGlobal
{
private:
	CPNTplMngrConstGlobal();
	virtual ~CPNTplMngrConstGlobal();

public:
	static CPNTplMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CPNTplMngrConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
