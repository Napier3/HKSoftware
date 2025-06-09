//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//KeyDbGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"



#define KDBCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define KDBCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define KDBCLASSID_CXKEYBASE       (KDBCLASSID_BASECLASS + 0X00000000)
#define KDBCLASSID_CXMULTIKEYBASE       (KDBCLASSID_EXLISTCLASS + 0X00000001)
#define KDBCLASSID_CXKEYGROUPBASE       (KDBCLASSID_EXLISTCLASS + 0X00000002)
#define KDBCLASSID_CXKEYREF       (KDBCLASSID_BASECLASS + 0X00000003)
#define KDBCLASSID_CXMATCHTOOLBASE       (KDBCLASSID_EXLISTCLASS + 0X00000004)
#define KDBCLASSID_CXKEYDB       (KDBCLASSID_EXLISTCLASS + 0X00000005)
#define KDBCLASSID_CXMATCHOBJECT       (KDBCLASSID_EXLISTCLASS + 0X00000006)
#define KDBCLASSID_CXMATCHLIST       (KDBCLASSID_EXLISTCLASS + 0X00000007)
#define KDBCLASSID_CXKEYMNGR               (KDBCLASSID_EXLISTCLASS + 0X00000008)
#define KDBCLASSID_CXKEYMAPS                (KDBCLASSID_EXLISTCLASS + 0X00000009)

#define XMCFGCLASSID_CXMATCHDATAREF             (KDBCLASSID_BASECLASS + 0X0000000A)
#define XMCFGCLASSID_CXMATCHDATAREFS            (KDBCLASSID_EXLISTCLASS + 0X0000000B)
#define XMCFGCLASSID_CXMATCHDATASETREF         (KDBCLASSID_BASECLASS + 0X0000000C)
#define XMCFGCLASSID_CXMATCHDATASETREFS       (KDBCLASSID_EXLISTCLASS + 0X0000000D)
#define XMCFGCLASSID_CXMATCHCONFIG                (KDBCLASSID_EXLISTCLASS + 0X0000000E)

#define KDBCLASSID_CXMULTISUBKEY                   (KDBCLASSID_BASECLASS + 0X0000000F)

class CKeyDbXmlRWKeys : public CXmlRWKeys
{
protected:
	CKeyDbXmlRWKeys();
	virtual ~CKeyDbXmlRWKeys();
	static long g_nKDBRef;

public:
	static CKeyDbXmlRWKeys* g_pXmlKeys;
	static CKeyDbXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXKeyDBKey; //key-db
	BSTR m_strCXKeyRefKey; //key-ref
	BSTR m_strCXKeyGroupBaseKey; //key-group
	BSTR m_strCXMultiKeyBaseKey; //multi-key
	BSTR m_strCXMatchKeyBaseKey; //match-key
	BSTR m_strCXKeyBaseKey; //key
	BSTR m_strCXKeyMngrKey; //keys
	BSTR m_strCXKeyMapsKey; //key-maps
	BSTR m_strImportanceKey; //importance
	BSTR m_strArrayIndexKey;
	BSTR m_strIsArrayKey; //importance
	BSTR m_strCXMatchConfigKey; //
	BSTR m_strCXMatchDatasetRefsKey; //dataset-refs
	BSTR m_strCXMatchDatasetRefKey; //dataset-ref
	BSTR m_strCXMatchDatarefsKey; //data-refs
	BSTR m_strCXMatchDatarefKey; //data-ref
	BSTR m_strSrcPathKey; //src-path
	BSTR m_strDestPathKey; //dest-path
	BSTR m_strMmsDvmFileKey; //mms-dvm-file
	BSTR m_strSrcDatasetPathKey; //src-dataset-path
	BSTR m_strMinRateKey;  //min-rate   //最小匹配度：匹配度阈值

public:
	static BSTR CXKeyMngrKey()  {   return g_pXmlKeys->m_strCXKeyMngrKey;  }
	static BSTR CXKeyMapsKey()  {   return g_pXmlKeys->m_strCXKeyMapsKey;  }
	static BSTR CXKeyDBKey()  {   return g_pXmlKeys->m_strCXKeyDBKey;  }
	static BSTR CXKeyRefKey()  {   return g_pXmlKeys->m_strCXKeyRefKey;  }
	static BSTR CXKeyGroupBaseKey()  {   return g_pXmlKeys->m_strCXKeyGroupBaseKey;  }
	static BSTR CXMultiKeyBaseKey()  {   return g_pXmlKeys->m_strCXMultiKeyBaseKey;  }
    static BSTR CXMatchKeyBaseKey()  {   return g_pXmlKeys->m_strCXMatchKeyBaseKey;  }
	static BSTR CXKeyBaseKey()  {   return g_pXmlKeys->m_strCXKeyBaseKey;  }
	static BSTR ImportanceKey()  {   return g_pXmlKeys->m_strImportanceKey;  }
	static BSTR ArrayIndexKey()  {   return g_pXmlKeys->m_strArrayIndexKey;  }
	static BSTR IsArrayKey()  {   return g_pXmlKeys->m_strIsArrayKey;  }
	static BSTR MmsDvmFileKey()  {   return g_pXmlKeys->m_strMmsDvmFileKey;  }
	static BSTR CXMatchConfigKey()  {   return g_pXmlKeys->m_strCXMatchConfigKey;  }
	static BSTR CXMatchDatasetRefsKey()  {   return g_pXmlKeys->m_strCXMatchDatasetRefsKey;  }
	static BSTR CXMatchDatasetRefKey()  {   return g_pXmlKeys->m_strCXMatchDatasetRefKey;  }
	static BSTR CXMatchDatarefsKey()  {   return g_pXmlKeys->m_strCXMatchDatarefsKey;  }
	static BSTR CXMatchDatarefKey()  {   return g_pXmlKeys->m_strCXMatchDatarefKey;  }
	static BSTR SrcPathKey()  {   return g_pXmlKeys->m_strSrcPathKey;  }
	static BSTR DestPathKey()  {   return g_pXmlKeys->m_strDestPathKey;  }
	static BSTR SrcDatasetPathKey()  {   return g_pXmlKeys->m_strSrcDatasetPathKey;  }
	static BSTR MinRateKey()  {   return g_pXmlKeys->m_strMinRateKey;  }
};



class CKeyDbConstGlobal
{
private:
	CKeyDbConstGlobal();
	virtual ~CKeyDbConstGlobal();

public:
	static CKeyDbConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CKeyDbConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

//////////////////////////////////////////////////////////////////////////
//CXMatchRefObjectSelEdit
class CXMatchRefObjectSelEdit
{
public:
	virtual void SetMatchRefData(CExBaseObject *pRefObject) = 0;
};

#define WM_MAPEDIT_KEY_CHANGED  (WM_USER+1015)
#define WM_MAPEDIT_DATAVALUE_EXPR_EDIT  (WM_USER+1016)

#define WM_MAPEDIT_DATAVALUE_EXPR_NONE             0
#define WM_MAPEDIT_DATAVALUE_EXPR_RET_EDIT       1
#define WM_MAPEDIT_DATAVALUE_EXPR_RET_CANCEL   2


//////////////////////////////////////////////////////////////////////////
//xkeydb_IsXKey## functions
inline BOOL xkeydb_IsXKeyBase(CExBaseObject *p)
{
	return (p->GetClassID() == KDBCLASSID_CXKEYBASE);
}

inline BOOL xkeydb_IsXMultiKeyBase(CExBaseObject *p)
{
	return (p->GetParent()->GetClassID() == KDBCLASSID_CXMULTIKEYBASE);
}

inline BOOL xkeydb_IsXChildKeyBase(CExBaseObject *p)
{
	return (p->GetParent()->GetClassID() != KDBCLASSID_CXKEYDB);
}

