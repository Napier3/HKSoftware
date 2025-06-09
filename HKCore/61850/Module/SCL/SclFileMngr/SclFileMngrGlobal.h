//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SclFileMngrGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CXSCLFILEMNGR       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CXSCLFILEOBJ       (MngrCLASSID_BASECLASS + 0X00000001)

class CSclFileMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSclFileMngrXmlRWKeys();
	virtual ~CSclFileMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSclFileMngrXmlRWKeys* g_pXmlKeys;
	static CSclFileMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXSclFileObjKey; //scl-file
	BSTR m_strCXSclFileMngrKey; //scl-file-mngr
	BSTR m_strCurr_Sel_IedKey; //curr-sel-ied
	BSTR m_strSizeKey; //size
	BSTR m_strSscl_PathKey; //sscl-path
	BSTR m_strScl_PathKey; //scl-path
	BSTR m_strUseKey; //use

public:
	static BSTR CXSclFileObjKey()  {   return g_pXmlKeys->m_strCXSclFileObjKey;  }
	static BSTR CXSclFileMngrKey()  {   return g_pXmlKeys->m_strCXSclFileMngrKey;  }
	static BSTR Curr_Sel_IedKey()  {   return g_pXmlKeys->m_strCurr_Sel_IedKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR Sscl_PathKey()  {   return g_pXmlKeys->m_strSscl_PathKey;  }
	static BSTR Scl_PathKey()  {   return g_pXmlKeys->m_strScl_PathKey;  }
	static BSTR UseKey()  {   return g_pXmlKeys->m_strUseKey;  }
};



class CSclFileMngrConstGlobal
{
private:
	CSclFileMngrConstGlobal();
	virtual ~CSclFileMngrConstGlobal();

public:
	static CSclFileMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSclFileMngrConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
