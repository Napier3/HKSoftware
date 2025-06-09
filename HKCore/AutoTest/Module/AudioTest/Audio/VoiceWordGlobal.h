//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VoiceWordGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define VWCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define VWCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define VWCLASSID_CAUDIOREPLYKEYWORD       (VWCLASSID_EXLISTCLASS + 0X00000000)
#define VWCLASSID_CAUDIOTIPWORD       (VWCLASSID_EXLISTCLASS + 0X00000001)
#define VWCLASSID_CAUDIOTIPWORDS       (VWCLASSID_EXLISTCLASS + 0X00000002)
#define VWCLASSID_CAUDIOORDERWORD       (VWCLASSID_EXLISTCLASS + 0X00000003)
#define VWCLASSID_CAUDIOORDERWORDS       (VWCLASSID_EXLISTCLASS + 0X00000004)
#define VWCLASSID_CAUDIOWORD       (VWCLASSID_EXLISTCLASS + 0X00000005)
#define VWCLASSID_CAUDIOFLOWWORD       (VWCLASSID_EXLISTCLASS + 0X00000006)
#define VWCLASSID_CAUDIOFLOWWORDS       (VWCLASSID_EXLISTCLASS + 0X00000007)
#define VWCLASSID_CAUDIOKEYWORD       (VWCLASSID_EXLISTCLASS + 0X00000008)
#define VWCLASSID_CAUDIOKEYWORDS       (VWCLASSID_EXLISTCLASS + 0X00000009)
#define VWCLASSID_CAUDIOTESTWORDS       (VWCLASSID_EXLISTCLASS + 0X0000000A)
#define VWCLASSID_CAUDIODATA       (VWCLASSID_EXLISTCLASS + 0X0000000B)

class CVoiceWordXmlRWKeys : public CXmlRWKeys
{
protected:
	CVoiceWordXmlRWKeys();
	virtual ~CVoiceWordXmlRWKeys();
	static long g_nVWRef;

public:
	static CVoiceWordXmlRWKeys* g_pXmlKeys;
	static CVoiceWordXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCAudioDataKey; //data
	BSTR m_strCAudioTestWordsKey; //test-words
	BSTR m_strCAudioKeyWordsKey; //key-words
	BSTR m_strCAudioKeyWordKey; //key-word
	BSTR m_strCAudioFlowWordsKey; //flow-words
	BSTR m_strCAudioFlowWordKey; //flow-word
	BSTR m_strCAudioWordKey; //word
	BSTR m_strCAudioOrderWordsKey; //order-words
	BSTR m_strCAudioOrderWordKey; //order-word
	BSTR m_strCAudioTipWordsKey; //tip-words
	BSTR m_strCAudioTipWordKey; //tip-word
	BSTR m_strCAudioReplyKeyWordKey; //reply-key-word
	BSTR m_strValueKey; //value
	BSTR m_strTip_Word_IdKey; //tip-word-id
	BSTR m_strOrder_Word_IdKey; //order-word-id
	BSTR m_strLevelKey; //level
	BSTR m_strFlagKey; //flag
	BSTR m_strTipWordKey; //tip-word
	BSTR m_strData_TypeKey; //data-type

public:
	static BSTR CAudioDataKey()  {   return g_pXmlKeys->m_strCAudioDataKey;  }
	static BSTR CAudioTestWordsKey()  {   return g_pXmlKeys->m_strCAudioTestWordsKey;  }
	static BSTR CAudioKeyWordsKey()  {   return g_pXmlKeys->m_strCAudioKeyWordsKey;  }
	static BSTR CAudioKeyWordKey()  {   return g_pXmlKeys->m_strCAudioKeyWordKey;  }
	static BSTR CAudioFlowWordsKey()  {   return g_pXmlKeys->m_strCAudioFlowWordsKey;  }
	static BSTR CAudioFlowWordKey()  {   return g_pXmlKeys->m_strCAudioFlowWordKey;  }
	static BSTR CAudioWordKey()  {   return g_pXmlKeys->m_strCAudioWordKey;  }
	static BSTR CAudioOrderWordsKey()  {   return g_pXmlKeys->m_strCAudioOrderWordsKey;  }
	static BSTR CAudioOrderWordKey()  {   return g_pXmlKeys->m_strCAudioOrderWordKey;  }
	static BSTR CAudioTipWordsKey()  {   return g_pXmlKeys->m_strCAudioTipWordsKey;  }
	static BSTR CAudioTipWordKey()  {   return g_pXmlKeys->m_strCAudioTipWordKey;  }
	static BSTR CAudioReplyKeyWordKey()  {   return g_pXmlKeys->m_strCAudioReplyKeyWordKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR Tip_Word_IdKey()  {   return g_pXmlKeys->m_strTip_Word_IdKey;  }
	static BSTR Order_Word_IdKey()  {   return g_pXmlKeys->m_strOrder_Word_IdKey;  }
	static BSTR LevelKey()  {   return g_pXmlKeys->m_strLevelKey;  }
	static BSTR FlagKey()  {   return g_pXmlKeys->m_strFlagKey;  }
	static BSTR TipWordKey()  {   return g_pXmlKeys->m_strTipWordKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
};



class CVoiceWord3ConstGlobal
{
private:
	CVoiceWord3ConstGlobal();
	virtual ~CVoiceWord3ConstGlobal();

public:
	static CVoiceWord3ConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CVoiceWord3ConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
