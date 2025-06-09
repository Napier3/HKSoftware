//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CommExprGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CCOMMEXPR       (MngrCLASSID_EXLISTCLASS + 0X00000000)

class CCommExprXmlRWKeys : public CXmlRWKeys
{
protected:
	CCommExprXmlRWKeys();
	virtual ~CCommExprXmlRWKeys();
	static long g_nMngrRef;

public:
	static CCommExprXmlRWKeys* g_pXmlKeys;
	static CCommExprXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCCommExprKey; //expr
	BSTR m_strValueKey; //value
	BSTR m_strOptrKey; //optr

public:
	static BSTR CCommExprKey()  {   return g_pXmlKeys->m_strCCommExprKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR OptrKey()  {   return g_pXmlKeys->m_strOptrKey;  }
};



class CCommExprConstGlobal
{
private:
	CCommExprConstGlobal();
	virtual ~CCommExprConstGlobal();

public:
	static CCommExprConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCommExprConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
