//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXMainConfigGlobal.h

#pragma once

#include "ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTTXUIDATAMAINCONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTTXUIDATAGLOBAL       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CSTTXUIDATAFONT       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CSTTXUIDATATAB       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CSTTXUIDATATEXT       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CSTTXUIDATABTNSGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CSTTXUIDATABUTTON       (MngrCLASSID_EXLISTCLASS + 0X00000007)
#define MNGRCLASSID_CSTTXUIDATACMD       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CSTTXUIDATAFILETYPES       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CSTTXUIDATAFILETYPE       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CSTTXUIDATATABS       (MngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CSTTXUIDATABASE       (MngrCLASSID_EXLISTCLASS + 0X0000000D)

class CSttXMainConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttXMainConfigXmlRWKeys();
	virtual ~CSttXMainConfigXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSttXMainConfigXmlRWKeys* g_pXmlKeys;
	static CSttXMainConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttXuiDataBaseKey; //
	BSTR m_strCSttXuiDataTabsKey; //tabs
	BSTR m_strCSttXuiDataFileTypeKey; //file-type
	BSTR m_strCSttXuiDataFileTypesKey; //file-types
	BSTR m_strCSttXuiDataFileMngrGridKey; //file-mngr-grid
	BSTR m_strCSttXuiDataCmdKey; //cmd
	BSTR m_strCSttXuiDataButtonKey; //button
	BSTR m_strCSttXuiDataBtnsGroupKey; //btns-group
	BSTR m_strCSttXuiDataTestBtnsGroupKey; //test-btns-group
	BSTR m_strCSttXuiDataTextKey; //text
	BSTR m_strCSttXuiDataTabKey; //tab
	BSTR m_strCSttXuiDataFontKey; //font
	BSTR m_strCSttXuiDataGlobalKey; //global
	BSTR m_strCSttXuiDataMainConfigKey; //main
	BSTR m_strVersionKey; //version
	BSTR m_strTitleKey; //title
	BSTR m_strPicKey; //pic
	BSTR m_strCxKey; //cx
	BSTR m_strCyKey; //cy
	BSTR m_StrShowBatteryBtnKey; //showBatteryBtn
	BSTR m_strStartupDelayTimeKey; //startup-delaytime
	BSTR m_strCr_BackKey; //cr-back
	BSTR m_strCr_TextKey; //cr_text
	BSTR m_strSizeKey; //size
	BSTR m_strFontKey; //font
	BSTR m_strTextKey; //text
	BSTR m_strXKey; //x
	BSTR m_strYKey; //y
	BSTR m_strInsetKey; //inset
	BSTR m_strFromKey; //from
	BSTR m_strTypeKey; //type
	BSTR m_strData_SrcKey; //data-src
	BSTR m_strEmit_ModeKey; //emit-mode
	BSTR m_strRootKey; //root
	BSTR m_strArgvKey; //argv

public:
	static BSTR CSttXuiDataBaseKey()  {   return g_pXmlKeys->m_strCSttXuiDataBaseKey;  }
	static BSTR CSttXuiDataTabsKey()  {   return g_pXmlKeys->m_strCSttXuiDataTabsKey;  }
	static BSTR CSttXuiDataFileTypeKey()  {   return g_pXmlKeys->m_strCSttXuiDataFileTypeKey;  }
	static BSTR CSttXuiDataFileTypesKey()  {   return g_pXmlKeys->m_strCSttXuiDataFileTypesKey;  }
	static BSTR CSttXuiDataFileMngrGridKey()  {   return g_pXmlKeys->m_strCSttXuiDataFileMngrGridKey;  }
	static BSTR CSttXuiDataCmdKey()  {   return g_pXmlKeys->m_strCSttXuiDataCmdKey;  }
	static BSTR CSttXuiDataButtonKey()  {   return g_pXmlKeys->m_strCSttXuiDataButtonKey;  }
	static BSTR CSttXuiDataBtnsGroupKey()  {   return g_pXmlKeys->m_strCSttXuiDataBtnsGroupKey;  }
	static BSTR CSttXuiDataTestBtnsGroupKey()  {   return g_pXmlKeys->m_strCSttXuiDataTestBtnsGroupKey;  }
	static BSTR CSttXuiDataTextKey()  {   return g_pXmlKeys->m_strCSttXuiDataTextKey;  }
	static BSTR CSttXuiDataTabKey()  {   return g_pXmlKeys->m_strCSttXuiDataTabKey;  }
	static BSTR CSttXuiDataFontKey()  {   return g_pXmlKeys->m_strCSttXuiDataFontKey;  }
	static BSTR CSttXuiDataGlobalKey()  {   return g_pXmlKeys->m_strCSttXuiDataGlobalKey;  }
	static BSTR CSttXuiDataMainConfigKey()  {   return g_pXmlKeys->m_strCSttXuiDataMainConfigKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR TitleKey()  {   return g_pXmlKeys->m_strTitleKey;  }
	static BSTR PicKey()  {   return g_pXmlKeys->m_strPicKey;  }
	static BSTR CxKey()  {   return g_pXmlKeys->m_strCxKey;  }
	static BSTR CyKey()  {   return g_pXmlKeys->m_strCyKey;  }
	static BSTR ShowBatteryBtn()  {   return g_pXmlKeys->m_StrShowBatteryBtnKey;  }
	static BSTR Cr_BackKey()  {   return g_pXmlKeys->m_strCr_BackKey;  }
	static BSTR Cr_TextKey()  {   return g_pXmlKeys->m_strCr_TextKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR FontKey()  {   return g_pXmlKeys->m_strFontKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
	static BSTR XKey()  {   return g_pXmlKeys->m_strXKey;  }
	static BSTR YKey()  {   return g_pXmlKeys->m_strYKey;  }
	static BSTR InsetKey()  {   return g_pXmlKeys->m_strInsetKey;  }
	static BSTR FromKey()  {   return g_pXmlKeys->m_strFromKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Data_SrcKey()  {   return g_pXmlKeys->m_strData_SrcKey;  }
	static BSTR Emit_ModeKey()  {   return g_pXmlKeys->m_strEmit_ModeKey;  }
	static BSTR RootKey()  {   return g_pXmlKeys->m_strRootKey;  }
};



class CSttXMainConfigConstGlobal
{
private:
	CSttXMainConfigConstGlobal();
	virtual ~CSttXMainConfigConstGlobal();

public:
	static CSttXMainConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttXMainConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

extern double g_dUIShowCoef;