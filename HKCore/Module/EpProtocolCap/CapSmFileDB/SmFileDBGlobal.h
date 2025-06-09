//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmFileDBGlobal.h

#pragma once

#include "ExBaseList.h"

#define SMDBCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define SMDBCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define SMDBCLASSID_CSMDBDATA       (SMDBCLASSID_BASECLASS + 0X00000000)
#define SMDBCLASSID_CSMDBTABLE       (SMDBCLASSID_EXLISTCLASS + 0X00000001)
#define SMDBCLASSID_CSMDBDATAEX       (SMDBCLASSID_EXLISTCLASS + 0X00000002)
#define SMDBCLASSID_CSMDBBUFFER       (SMDBCLASSID_BASECLASS + 0X00000003)
#define SMDBCLASSID_CSMDBFILE       (SMDBCLASSID_EXLISTCLASS + 0X00000004)

class CSmFileDBXmlRWKeys : public CXmlRWKeys
{
protected:
	CSmFileDBXmlRWKeys();
	virtual ~CSmFileDBXmlRWKeys();
	static long g_nSMDBRef;

public:
	static CSmFileDBXmlRWKeys* g_pXmlKeys;
	static CSmFileDBXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSmDbFileKey; //sm-file
	BSTR m_strCSmDbDataExKey; //sm-data-ex
	BSTR m_strCSmDbTableKey; //sm-table
	BSTR m_strCSmDbDataKey; //sm-data

public:
	static BSTR CSmDbFileKey()  {   return g_pXmlKeys->m_strCSmDbFileKey;  }
	static BSTR CSmDbDataExKey()  {   return g_pXmlKeys->m_strCSmDbDataExKey;  }
	static BSTR CSmDbTableKey()  {   return g_pXmlKeys->m_strCSmDbTableKey;  }
	static BSTR CSmDbDataKey()  {   return g_pXmlKeys->m_strCSmDbDataKey;  }
};



class CSmFileDBConstGlobal
{
private:
	CSmFileDBConstGlobal();
	virtual ~CSmFileDBConstGlobal();

public:
	static CSmFileDBConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSmFileDBConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
