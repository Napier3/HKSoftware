//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbSmartGenWzdGlobal.h

#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"

//2021-10-9  LIJUNQING
#define DVMCLASSID_GBMACROGENWZD       (DVMCLASSID_EXLISTCLASS + 0X000000F1)
#define DVMCLASSID_GBSMARTGENWZD       (DVMCLASSID_EXLISTCLASS + 0X000000F2)
#define DTMCLASSID_CCONTENTS       (DVMCLASSID_EXLISTCLASS + 0X000000F3)
#define DVMCLASSID_GBWZDCOMMCMDADD       (DVMCLASSID_EXLISTCLASS + 0X000000F4)
#define DVMCLASSID_GBWZDMACROTESTADD       (DVMCLASSID_EXLISTCLASS + 0X000000F5)
#define DVMCLASSID_GBWZDITEMSADD       (DVMCLASSID_EXLISTCLASS + 0X000000F6)
#define DVMCLASSID_GBWZDITEMEDIT       (DVMCLASSID_EXLISTCLASS + 0X000000F7)
#define DVMCLASSID_GBWZDITEMMOVE       (DVMCLASSID_EXLISTCLASS + 0X000000F8)
#define DVMCLASSID_GBWZDITEMCOPY       (DVMCLASSID_EXLISTCLASS + 0X000000F9)
#define DVMCLASSID_GBWZDITEMPASTE       (DVMCLASSID_EXLISTCLASS + 0X000000FA)

#define GBCLASSID_GbWzdAiDATAKEY       (DVMCLASSID_BASECLASS + 0X000000FB)
#define GBCLASSID_GbWzdAiDATASCPTOPTR       (DVMCLASSID_EXLISTCLASS + 0X000000FC)
#define GBCLASSID_GbWzdAiDATASCPTOPTR_AND       (DVMCLASSID_EXLISTCLASS + 0X000000FD)
#define GBCLASSID_GbWzdAiDATASCPTOPTR_OR       (DVMCLASSID_EXLISTCLASS + 0X000000FE)
#define GBCLASSID_GbWzdAiDATASCPTOPTR_NOT       (DVMCLASSID_EXLISTCLASS + 0X000000FF)
#define GBCLASSID_GbWzdAiDATASCPTFUNC       (DVMCLASSID_EXLISTCLASS + 0X00000100)
#define GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTHAVE       (DVMCLASSID_EXLISTCLASS + 0X00000101)
#define GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTNOTHAVE       (DVMCLASSID_EXLISTCLASS + 0X00000102)
#define GBCLASSID_GbWzdAiScript       (DVMCLASSID_EXLISTCLASS + 0X00000103)
#define GBCLASSID_GbWzdAiCase       (DVMCLASSID_EXLISTCLASS + 0X00000104)
#define GBCLASSID_GbWzdAiSwitch       (DVMCLASSID_EXLISTCLASS + 0X00000105)
#define GBCLASSID_GbWzdAiMacroPara       (DVMCLASSID_EXLISTCLASS + 0X00000106)
#define GBCLASSID_GbWzdAiDOAttr       (DVMCLASSID_BASECLASS + 0X00000106)
#define GBCLASSID_GbWzdAiDO       (DVMCLASSID_EXLISTCLASS + 0X00000107)
#define GBCLASSID_GbWzdAiParas       (DVMCLASSID_EXLISTCLASS + 0X00000108)
#define GBCLASSID_GbWzdAiValSet       (DVMCLASSID_EXLISTCLASS + 0X00000109)
#define GBCLASSID_GbWzdAiTool       (DVMCLASSID_BASECLASS + 0X0000010A)


#define DVMCLASSID_GBWZDITEMRSLTEXPREDIT       (DVMCLASSID_EXLISTCLASS + 0X0000010B)
#define DVMCLASSID_GBWZDITEMSETSTATE       (DVMCLASSID_EXLISTCLASS + 0X0000010C)
#define DVMCLASSID_GBWZDSAFETYADD       (DVMCLASSID_EXLISTCLASS + 0X0000010D)
#define DVMCLASSID_GBWZDCOMMCMDUPDATE       (DVMCLASSID_EXLISTCLASS + 0X0000010E)
#define DVMCLASSID_GBWZDCOMMCMDADDGRP       (DVMCLASSID_EXLISTCLASS + 0X0000010F)
#define DVMCLASSID_GBWZDITEMSDELETE       (DVMCLASSID_EXLISTCLASS + 0X00000110)


#define GbSmartGenWzd_File_Postfix   _T("wzdxml")

class CGbSmartGenWzdXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CGbSmartGenWzdXmlRWKeys();
	virtual ~CGbSmartGenWzdXmlRWKeys();
	static long g_nGbSmartGenWzdRef;

public:
	static CGbSmartGenWzdXmlRWKeys* g_pGbSmartGenWzdKeys;
	static CGbSmartGenWzdXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCGbWzdMacroTestAddKey; //macro-test-add
	BSTR m_strCGbWzdCommCmdAddKey; //comm-cmd-add
	BSTR m_strCGbMacroGenWzdKey; //macro-gen
	BSTR m_strCGbSmartGenWzdKey; //smart-wzd
	BSTR m_strContentsKey; //contents
	BSTR m_strCGbWzdItemsAddKey;  //items-add
	BSTR m_strCGbWzdItemEditKey;  //item-edit
	BSTR m_strCGbWzdItemMoveKey;  //item-move
	BSTR m_strCGbWzdItemCopyKey;  //item-copy
	BSTR m_strCGbWzdItemPasteKey;  //item-paste
	BSTR m_strCGbWzdItemRsltExprEditKey;  //item-rsltexpr-edit
	BSTR m_strCGbWzdItemSetStateKey;  //item-setstate
	BSTR m_strCGbWzdSafetyAddKey;  //safety-add
	BSTR m_strCGbWzdCommCmdUpdateKey; //comm-cmd-update
	BSTR m_strCGbWzdCommCmdAddGrpKey; //comm-cmd-add-grp
	BSTR m_strCGbWzdItemsDeleteKey;  //items-delete

	BSTR m_strTestClassKey;
	BSTR m_strItemsNameKey;
	BSTR m_strItemsIDKey;
	BSTR m_strTestMacroUIKey;
	BSTR m_strParentItemsIDKey;

	BSTR m_strDvmFileKey;
	BSTR m_strEngineProgIDKey;
	BSTR m_strPpFileKey;
	BSTR m_strDevIPKey;
	BSTR m_strDevPortKey;
	BSTR m_strCommCmdIDKey;
	BSTR m_strItemsID_OldKey;
	BSTR m_strRepeatTimesKey;
	BSTR m_strLocalIPKey;
	BSTR m_strMoveTypeKey;
	BSTR m_strMoveTimesKey;
	BSTR m_strItemTypeKey;

	BSTR m_strSrcParentItemsIDKey;
	BSTR m_strDestParentItemsIDKey;
	BSTR m_strSrcItemsNameKey;
	BSTR m_strDestItemsNameKey;
	BSTR m_strSrcItemsIDKey;
	BSTR m_strDestItemsIDKey;
	BSTR m_strSelectKey;
	BSTR m_strShowKey;
	BSTR m_strEnableKey;

	//GbWzdAiScript
	BSTR m_strGbWzdAiKey;
	BSTR m_strGbWzdAiScriptKey;
	BSTR m_strGbWzdAiDataScptFuncMustNotHaveKey;
	BSTR m_strGbWzdAiDataScptFuncMustHaveKey;
	BSTR m_strGbWzdAiDataScptOptrNotKey;
	BSTR m_strGbWzdAiDataScptOptrOrKey;
	BSTR m_strGbWzdAiDataScptOptrAndKey;
	BSTR m_strGbWzdAiDataOptrtKey;
	BSTR m_strGbWzdAiDataKeyKey;
	BSTR m_strStandNameKey;	
	BSTR m_strGbWzdAiCaseKey;	
	BSTR m_strGbWzdAiSwitchKey;	
	BSTR m_strGbWzdAiMacroParatKey;	
	BSTR m_strExprKey;	
	BSTR m_strAttrIDKey;	
	BSTR m_strGbWzdAiDoAttrKey;	
	BSTR m_strGbWzdAiDoKey;	
	BSTR m_strIsTimeSetsUnit_ms_Key;
	BSTR m_strIsAddDevResetKey;
	BSTR m_strGbWzdAiParasKey;
	BSTR m_strGbWzdAiValSetKey;

	//shaolei 2023-6-21  是否作为标题、标题等级
	BSTR m_strRptTitleKey;
	BSTR m_strTitleLevelKey;

	BSTR m_strAftUseResetKey;
	BSTR m_strAddCommCmdKey;

public:
	static BSTR CGbWzdMacroTestAddKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdMacroTestAddKey;  }
	static BSTR CGbWzdCommCmdAddKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdCommCmdAddKey;  }
	static BSTR CGbMacroGenWzdKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbMacroGenWzdKey;  }
	static BSTR CGbSmartGenWzdKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbSmartGenWzdKey;  }
	static BSTR CDvmContentsKey()  {   return g_pGbSmartGenWzdKeys->m_strContentsKey;  }
	static BSTR CGbWzdItemsAddKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemsAddKey;  }
	static BSTR CGbWzdItemEditKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemEditKey;  }
	static BSTR CGbWzdItemMoveKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemMoveKey;  }
	static BSTR CGbWzdItemCopyKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemCopyKey;  }
	static BSTR CGbWzdItemPasteKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemPasteKey;  }
	static BSTR CGbWzdItemRsltExprEditKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemRsltExprEditKey;  }
	static BSTR CGbWzdItemSetStateKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemSetStateKey;  }
	static BSTR CGbWzdSafetyAddKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdSafetyAddKey;  }
	static BSTR CGbWzdCommCmdUpdateKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdCommCmdUpdateKey;  }
	static BSTR CGbWzdCommCmdAddGrpKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdCommCmdAddGrpKey;  }
	static BSTR CGbWzdItemsDeleteKey()  {   return g_pGbSmartGenWzdKeys->m_strCGbWzdItemsDeleteKey;  }
};

//2022-10-4 lijunqing
long GbGenWzd_GetSelCount(CDataGroup *pGroup);



inline BOOL GbWzdAiDataScript_IsFunc(UINT nClassID)
{
	return ((nClassID == GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTNOTHAVE)
		|| (nClassID == GBCLASSID_GbWzdAiDATASCPTFUNC_MUSTHAVE));
}

inline BOOL GbWzdAiDataScript_IsOptr(UINT nClassID)
{
	return ((nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_AND)
		|| (nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_OR)
		|| (nClassID == GBCLASSID_GbWzdAiDATASCPTOPTR_NOT) );
}

