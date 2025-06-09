//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CmdExecGlobal.h

#pragma once

#include "../../../Module/DataMngr/DataMngrGlobal.h"

//#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00060000)
#define CmdMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00060000)

#define MNGRCLASSID_CCMDEXECRSLT       (CmdMngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CEXECRESULT       (CmdMngrCLASSID_EXLISTCLASS + 0X00000001)

class CCmdExecXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CCmdExecXmlRWKeys();
	virtual ~CCmdExecXmlRWKeys();
	static long g_nMngrRef;

public:
	static CCmdExecXmlRWKeys* g_pXmlKeys;
	static CCmdExecXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCExecResultKey; //rslt
	BSTR m_strCCmdExecRsltKey; //cmd-exec-rslt

public:
	static BSTR CExecResultKey()  {   return g_pXmlKeys->m_strCExecResultKey;  }
	static BSTR CCmdExecRsltKey()  {   return g_pXmlKeys->m_strCCmdExecRsltKey;  }
};



class CCmdExecConstGlobal
{
private:
	CCmdExecConstGlobal();
	virtual ~CCmdExecConstGlobal();

public:
	static CCmdExecConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCmdExecConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
