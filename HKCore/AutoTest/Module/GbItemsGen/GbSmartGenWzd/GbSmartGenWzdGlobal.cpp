//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbSmartGenWzdGlobal.cpp

#include "stdafx.h"
#include "GbSmartGenWzdGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CGbSmartGenWzdXmlRWKeys

CGbSmartGenWzdXmlRWKeys* CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys = NULL;
long CGbSmartGenWzdXmlRWKeys::g_nGbSmartGenWzdRef = 0;


CGbSmartGenWzdXmlRWKeys::CGbSmartGenWzdXmlRWKeys()
{
	m_strCGbWzdMacroTestAddKey = L"macro-test-add";
	m_strCGbWzdCommCmdAddKey = L"comm-cmd-add";
	m_strCGbMacroGenWzdKey = L"macro-gen";
	m_strCGbSmartGenWzdKey = L"smart-wzd";
	m_strContentsKey = L"contents";
	m_strCGbWzdItemsAddKey = L"items-add";
	m_strCGbWzdItemEditKey = L"item-edit";
	m_strCGbWzdItemMoveKey = L"item-move";
	m_strCGbWzdItemCopyKey = L"item-copy";
	m_strCGbWzdItemPasteKey = L"item-paste";
	m_strCGbWzdItemRsltExprEditKey = L"item-rsltexpr-edit";
	m_strCGbWzdItemSetStateKey = L"item-setstate";
	m_strCGbWzdSafetyAddKey = L"safety-add";
	m_strCGbWzdCommCmdUpdateKey = L"comm-cmd-update";
	m_strCGbWzdCommCmdAddGrpKey = L"comm-cmd-add-grp";
	m_strCGbWzdItemsDeleteKey = L"items-delete";

	m_strTestClassKey = L"test-class";
	m_strItemsNameKey = L"items-name";
	m_strItemsIDKey = L"items-id";
	m_strTestMacroUIKey = L"test-macro-ui-id";
	m_strParentItemsIDKey = L"parent-items-id";

	m_strDvmFileKey = L"dvm-file";
	m_strEngineProgIDKey = L"engine-prog-id";
	m_strPpFileKey = L"pp-file";
	m_strDevIPKey = L"dev-ip";
	m_strDevPortKey = L"dev-port";
	m_strCommCmdIDKey = L"comm-cmd-id";
	m_strItemsID_OldKey = L"items-id-old";
	m_strRepeatTimesKey = L"repeat-times";
	m_strLocalIPKey = L"local-ip";
	m_strMoveTypeKey = L"move-type";
	m_strMoveTimesKey = L"move-times";
	m_strItemTypeKey = L"item-type";

	m_strSrcParentItemsIDKey = L"src-parent-items-id";
	m_strDestParentItemsIDKey = L"dest-parent-items-id";
	m_strSrcItemsNameKey = L"src-items-name";
	m_strDestItemsNameKey = L"dest-items-name";
	m_strSrcItemsIDKey = L"src-items-id";
	m_strDestItemsIDKey = L"dest-items-id";
	m_strSelectKey = L"select";
	m_strShowKey = L"show";
	m_strEnableKey = L"enable";

	m_strGbWzdAiKey  = L"gb-wzd-ai";
	m_strGbWzdAiScriptKey  = L"script";
	m_strGbWzdAiDataScptFuncMustNotHaveKey  = L"must-not-have";
	m_strGbWzdAiDataScptFuncMustHaveKey  = L"must-have";
	m_strGbWzdAiDataScptOptrNotKey  = L"not";
	m_strGbWzdAiDataScptOptrOrKey  = L"or";
	m_strGbWzdAiDataScptOptrAndKey  = L"and";
	m_strGbWzdAiDataOptrtKey  = L"optr";
	m_strGbWzdAiDataKeyKey  = L"key";
	m_strStandNameKey  = L"stand";
	m_strGbWzdAiCaseKey = L"case";	
	m_strGbWzdAiSwitchKey = L"switch";	
	m_strGbWzdAiMacroParatKey = L"macro-para";	
	m_strExprKey = L"expr";
	m_strAttrIDKey = L"attr";
	m_strGbWzdAiDoAttrKey = L"attr";
	m_strGbWzdAiDoKey = L"do";
	m_strIsTimeSetsUnit_ms_Key = L"time-unit-ms";
	m_strIsAddDevResetKey = L"add-devreset";
	m_strGbWzdAiParasKey = L"macro-paras";
	m_strGbWzdAiValSetKey = L"val-set";

	//shaolei 2023-6-21  是否作为标题、标题等级
	m_strRptTitleKey = L"rpt-title";
	m_strTitleLevelKey = L"title-level";

	m_strAftUseResetKey = L"aft-use-devreset";
	m_strAddCommCmdKey = L"add-commcmd";
}

CGbSmartGenWzdXmlRWKeys::~CGbSmartGenWzdXmlRWKeys()
{
}

CGbSmartGenWzdXmlRWKeys* CGbSmartGenWzdXmlRWKeys::Create()
{
	g_nGbSmartGenWzdRef++;

	if (g_nGbSmartGenWzdRef == 1)
	{
		g_pGbSmartGenWzdKeys = new CGbSmartGenWzdXmlRWKeys();
	}

	return g_pGbSmartGenWzdKeys;
}

void CGbSmartGenWzdXmlRWKeys::Release()
{
	g_nGbSmartGenWzdRef--;

	if (g_nGbSmartGenWzdRef == 0)
	{
		delete g_pGbSmartGenWzdKeys;
		g_pGbSmartGenWzdKeys = NULL;
	}
}


long GbGenWzd_GetSelCount(CDataGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nSelCount = 0;

	while (pos != NULL)
	{
		p = pGroup->GetNext(pos);

		if (dvm_GetDvmX_Value_long(p) == 1)
		{
			nSelCount++;
		}
	}

	return nSelCount;
}
