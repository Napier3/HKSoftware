//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBGeneratorGlobal.h

#pragma once

#include "../../BaseClass/ExBaseList.h"

#define UIBGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define UIBGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define UIBGCLASSID_CUIBGENHARM       (UIBGCLASSID_BASECLASS + 0X00000000)
#define UIBGCLASSID_CUIBGENANALOG       (UIBGCLASSID_EXLISTCLASS + 0X00000001)
#define UIBGCLASSID_CUIBGENSTATE       (UIBGCLASSID_EXLISTCLASS + 0X00000002)
#define UIBGCLASSID_CUIBGENERATOR       (UIBGCLASSID_EXLISTCLASS + 0X00000003)
#define UIBGCLASSID_CUIBGENBINARY       (UIBGCLASSID_BASECLASS + 0X00000004)

class CUIBGeneratorXmlRWKeys : public CXmlRWKeys
{
protected:
	CUIBGeneratorXmlRWKeys();
	virtual ~CUIBGeneratorXmlRWKeys();
	static long g_nUIBGRef;

public:
	static CUIBGeneratorXmlRWKeys* g_pXmlKeys;
	static CUIBGeneratorXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCUibGenBinaryKey; //binary
	BSTR m_strCUibGeneratorKey; //UIB_Gen
	BSTR m_strCUibGenStateKey; //state
	BSTR m_strCUibGenAnalogKey; //analog
	BSTR m_strCUibGenHarmKey; //hm
	BSTR m_strUseKey; //use
	BSTR m_strIndexKey; //index
	BSTR m_strValueKey; //value
	BSTR m_strAngleKey; //angle
	BSTR m_strZeroKey; //zero
	BSTR m_strCoefKey; //coef
	BSTR m_strChIDKey; //ch-id
	BSTR m_strRandKey; //rand
	BSTR m_strUnitKey; //unit
	BSTR m_strPrimaryKey; //primary
	BSTR m_strSecondaryKey; //secondary
	BSTR m_strTimeLongKey; //time-long
	BSTR m_strModeKey; //mode
	BSTR m_strFreqKey; //freq
	BSTR m_strSampRateKey; //samp-rate
	BSTR m_strUchCountKey; //u-chs
	BSTR m_strIchCountKey; //i-chs
	BSTR m_strBchCountKey; //b-chs
	BSTR m_strTurnTimeKey; //turn-time
	BSTR m_strHoldTimeKey; //hold-time

public:
	static BSTR CUibGenBinaryKey()  {   return g_pXmlKeys->m_strCUibGenBinaryKey;  }
	static BSTR CUibGeneratorKey()  {   return g_pXmlKeys->m_strCUibGeneratorKey;  }
	static BSTR CUibGenStateKey()  {   return g_pXmlKeys->m_strCUibGenStateKey;  }
	static BSTR CUibGenAnalogKey()  {   return g_pXmlKeys->m_strCUibGenAnalogKey;  }
	static BSTR CUibGenHarmKey()  {   return g_pXmlKeys->m_strCUibGenHarmKey;  }
	static BSTR UseKey()  {   return g_pXmlKeys->m_strUseKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR AngleKey()  {   return g_pXmlKeys->m_strAngleKey;  }
	static BSTR ZeroKey()  {   return g_pXmlKeys->m_strZeroKey;  }
	static BSTR CoefKey()  {   return g_pXmlKeys->m_strCoefKey;  }
	static BSTR ChIDKey()  {   return g_pXmlKeys->m_strChIDKey;  }
	static BSTR RandKey()  {   return g_pXmlKeys->m_strRandKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR PrimaryKey()  {   return g_pXmlKeys->m_strPrimaryKey;  }
	static BSTR SecondaryKey()  {   return g_pXmlKeys->m_strSecondaryKey;  }
	static BSTR TimeLongKey()  {   return g_pXmlKeys->m_strTimeLongKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
	static BSTR FreqKey()  {   return g_pXmlKeys->m_strFreqKey;  }
	static BSTR SampRateKey()  {   return g_pXmlKeys->m_strSampRateKey;  }
	static BSTR UchCountKey()  {   return g_pXmlKeys->m_strUchCountKey;  }
	static BSTR IchCountKey()  {   return g_pXmlKeys->m_strIchCountKey;  }
	static BSTR BchCountKey()  {   return g_pXmlKeys->m_strBchCountKey;  }
	static BSTR TurnTimeKey()  {   return g_pXmlKeys->m_strTurnTimeKey;  }
	static BSTR HoldTimeKey()  {   return g_pXmlKeys->m_strHoldTimeKey;  }
};



class CUIBGeneratorConstGlobal
{
private:
	CUIBGeneratorConstGlobal();
	virtual ~CUIBGeneratorConstGlobal();

public:
	static CUIBGeneratorConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CUIBGeneratorConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
