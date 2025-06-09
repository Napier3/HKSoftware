#pragma once


//class id定义
#define GBWZDCLASSID_BASECLASS             (CLASSID_BASECLASS + 0X00090000)
#define GBWZDCLASSID_EXLISTCLASS           (CLASSID_EXLISTCLASS + 0X00090000)

#define GBWZDCLASSID_COMMCMD               (GBWZDCLASSID_BASECLASS +  0x00000001)
#define GBWZDCLASSID_DEVICEMODEL           (GBWZDCLASSID_BASECLASS +  0x00000002)
#define GBWZDCLASSID_FOLDER                (GBWZDCLASSID_EXLISTCLASS +  0x00000003)
#define GBWZDCLASSID_GBTDATAINTERFACE      (GBWZDCLASSID_BASECLASS +  0x00000004)
#define GBWZDCLASSID_INITGBBYSTXML         (GBWZDCLASSID_EXLISTCLASS +  0x00000005)
#define GBWZDCLASSID_SELECTSTXML           (GBWZDCLASSID_BASECLASS +  0x00000006)
#define GBWZDCLASSID_GBWIZARD              (GBWZDCLASSID_EXLISTCLASS +  0x00000007)
#define GBWZDCLASSID_SAVE                  (GBWZDCLASSID_BASECLASS +  0x00000008)
#define GBWZDCLASSID_GBATTR                (GBWZDCLASSID_BASECLASS +  0x00000009)

#define GBWZDCLASSID_STXML_SELROOT                (GBWZDCLASSID_BASECLASS +  0x0000000A)
#define GBWZDCLASSID_STXML_EDITMAP                (GBWZDCLASSID_BASECLASS +  0x0000000B)
#define GBWZDCLASSID_STXML_EDITGBITEM             (GBWZDCLASSID_BASECLASS +  0x0000000C)

#define GBWZDCLASSID_CDINWZDFROMSCLGINCH       (GBWZDCLASSID_BASECLASS + 0x0000000D)
#define GBWZDCLASSID_CDINWZDFROMSCLGINCHS       (GBWZDCLASSID_EXLISTCLASS + 0x0000000E)

#include "..\GuideBook\GbXMLKeys.h"

class CGbWzdToolXmlRWKeys : public CGbXMLKeys
{
protected:
	CGbWzdToolXmlRWKeys();
	virtual ~CGbWzdToolXmlRWKeys();
	static long g_nKDBRef;

public:
	static CGbWzdToolXmlRWKeys* g_pGbWzdToolXmlKeys;
	static CGbWzdToolXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCGbtBatchItemRefKey;
	BSTR m_strCGbtBatchGbtDataRefKey;
	BSTR m_strCGbtBatchItemGroupKey;
	BSTR m_strCGbtBatchGbtDataGroupKey;
	BSTR m_strCGbtBatchItemGroupsKey;
	BSTR m_strCGbtDataScriptMapKey;
	BSTR m_strCGbtDataInterfaceMapKey;
	BSTR m_strCGbInsertStxmlFileKey;
	BSTR m_strCGbInsertStxmlFileMngrKey;
	BSTR m_strCGbInsertStxmlFileToolKey;
	BSTR m_strCGbWzdDatasetRefKey;
	BSTR m_strCGbWzdDatasetRefsKey;
	
	BSTR m_strCBatchItemRefValueKey;
	BSTR m_strValueKey;
	BSTR m_strDatasetPathKey;
	BSTR m_strBatchVariableModeKey;
	BSTR m_strBatchItemsModeKey;
	BSTR m_strDataValueKey;
	BSTR m_strRefObjNameKey;
	BSTR m_strRefObjPathKey;
	BSTR m_strStxmlFileFilterKey;
	BSTR m_strStxmlFileKey;
	BSTR m_strIec61850ConfigFileKey;
	BSTR m_strAddRptGroupTitleKey;
	BSTR m_strInsertRootItemsKey;
	BSTR m_strRootItemsNameKey;
	BSTR m_strRootItemsIDKey;
	BSTR m_strUseKey;

	//向导关键字
	BSTR m_strCGbWzdCmdGbAttrKey;
	BSTR m_strCGbWzdCmdDeviceModelKey;
	BSTR m_strCGbWzdCmdSelectStxmlFileKey;

	BSTR m_strCGbWzdCmdInitGbByStxmlFileKey;
	BSTR m_strCGbWzdCmdEditGbtDataMapKey;
	BSTR m_strCGbWzdCmdSelectRootItemsKey;
	BSTR m_strCGbWzdCmdSaveKey;
	BSTR m_strCGuideBookWizardKey;
	BSTR m_strCGbWzdCmdKey;

	BSTR m_strCDinWzdFromSclGinChsKey; //din-wzd-ch
	BSTR m_strCDinWzdFromSclGinChKey; //din-wzd-ch
	BSTR m_strAppIDKey; //app-id
	BSTR m_strGsChIndexKey; //ch-index
	BSTR m_strItemPathKey;

public:
	static BSTR CGbtCommCmdItemEditExpandKey()    {      return g_pGbWzdToolXmlKeys->m_strDataSetKey;   } 
	static BSTR CGbtCommCmdItemEditKey()    {      return g_pGbWzdToolXmlKeys->m_strItemsKey;   } 
	static BSTR CGbtCommCmdItemEditMngrKey()    {      return g_pGbWzdToolXmlKeys->m_strCommCmdKey;   } 
	static BSTR CGbtBatchItemRefKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtBatchItemRefKey;   } 
	static BSTR CGbtBatchGbtDataRefKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtBatchGbtDataRefKey;   } 
	static BSTR CGbtBatchItemGroupKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtBatchItemGroupKey;   } 
	static BSTR CGbtBatchGbtDataGroupKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtBatchGbtDataGroupKey;   } 
	static BSTR CGbtBatchItemGroupsKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtBatchItemGroupsKey;   } 
	static BSTR CGbtDataScriptMapKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtDataScriptMapKey;   } 
	static BSTR CGbtDataInterfaceMapKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbtDataInterfaceMapKey;   } 
	static BSTR CGbInsertStxmlFileKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbInsertStxmlFileKey;   } 
	static BSTR CGbInsertStxmlFileMngrKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbInsertStxmlFileMngrKey;   } 
	static BSTR CGbInsertStxmlFileToolKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbInsertStxmlFileToolKey;   } 
	static BSTR CGbWzdDatasetRefKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdDatasetRefKey;   } 
	static BSTR CGbWzdDatasetRefsKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdDatasetRefsKey;   } 

	static BSTR CBatchItemRefValueKey()    {      return g_pGbWzdToolXmlKeys->m_strCBatchItemRefValueKey;   } 
	static BSTR ValueKey()    {      return g_pGbWzdToolXmlKeys->m_strValueKey;   } 
	static BSTR DatasetPathKey()    {      return g_pGbWzdToolXmlKeys->m_strDatasetPathKey;   } 
	static BSTR BatchVariableModeKey()    {      return g_pGbWzdToolXmlKeys->m_strBatchVariableModeKey;   } 
	static BSTR BatchItemsModeKey()    {      return g_pGbWzdToolXmlKeys->m_strBatchItemsModeKey;   } 
	static BSTR DataValueKey()    {      return g_pGbWzdToolXmlKeys->m_strDataValueKey;   } 
	static BSTR RefObjNameKey()    {      return g_pGbWzdToolXmlKeys->m_strRefObjNameKey;   } 
	static BSTR RefObjPathKey()    {      return g_pGbWzdToolXmlKeys->m_strRefObjPathKey;   } 
	static BSTR StxmlFileFilterKey()    {      return g_pGbWzdToolXmlKeys->m_strStxmlFileFilterKey;   } 
	static BSTR StxmlFileKey()    {      return g_pGbWzdToolXmlKeys->m_strStxmlFileKey;   } 
	static BSTR Iec61850ConfigFileKey()    {      return g_pGbWzdToolXmlKeys->m_strIec61850ConfigFileKey;   } 
	static BSTR InsertRootItemsKey()    {      return g_pGbWzdToolXmlKeys->m_strInsertRootItemsKey;   } 
	static BSTR RootItemsNameKey()    {      return g_pGbWzdToolXmlKeys->m_strRootItemsNameKey;   } 
	static BSTR RootItemsIDKey()    {      return g_pGbWzdToolXmlKeys->m_strRootItemsIDKey;   } 

	static BSTR CGbWzdCmdGbAttrKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdGbAttrKey;			}
	static BSTR CGbWzdCmdDeviceModelKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdDeviceModelKey;			}
	static BSTR CGbWzdCmdSelectStxmlFileKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdSelectStxmlFileKey;			}

	static BSTR CGbWzdCmdInitGbByStxmlFileKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdInitGbByStxmlFileKey;			}
	static BSTR CGbWzdCmdEditGbtDataMapKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdEditGbtDataMapKey;			}
	static BSTR CGbWzdCmdSelectRootItemsKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdSelectRootItemsKey;			}
	static BSTR CGbWzdCmdSaveKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdSaveKey;			}
	static BSTR CGuideBookWizardKey()    {      return g_pGbWzdToolXmlKeys->m_strCGuideBookWizardKey;			}
	static BSTR CGbWzdCmdKey()    {      return g_pGbWzdToolXmlKeys->m_strCGbWzdCmdKey;			}

	static BSTR CDinWzdFromSclGinChsKey()  {   return g_pGbWzdToolXmlKeys->m_strCDinWzdFromSclGinChsKey;  }
	static BSTR CDinWzdFromSclGinChKey()  {   return g_pGbWzdToolXmlKeys->m_strCDinWzdFromSclGinChKey;  }
	static BSTR AppIDKey()  {   return g_pGbWzdToolXmlKeys->m_strAppIDKey;  }
	static BSTR GsChIndexKey()  {   return g_pGbWzdToolXmlKeys->m_strGsChIndexKey;  }
	static BSTR ItemPathKey()  {   return g_pGbWzdToolXmlKeys->m_strItemPathKey;  }
};

static const CString g_strGbWzdFilePostFix = _T("gbwzd");
static const CString g_strGbWzdFileName = _T("作业指导书向导文件");
static const CString g_strGbWzdAutoFilePostFix = _T("gawzd");
//static const CString g_strGbWzdAutoFileName = _T("作业指导书自动向导文件");//g_sLangTxt_GuideAutoWizardFile


CString wzd_GetWzdFilePath();
CString wzd_GetWzdFileDlgFilter();
