#include "stdafx.h"
#include "GbItemVariableIDReplaceEx.h"
#include "..\..\Module\System\StringVariableReplace.h"


CGbItemVariableIDReplaceEx::CGbItemVariableIDReplaceEx()
{
	
}

CGbItemVariableIDReplaceEx::~CGbItemVariableIDReplaceEx()
{
	
}

void CGbItemVariableIDReplaceEx::Replace(CCommCmd *pGbObj)
{
	ShowReplaceItemPath(pGbObj);
	CGbItemVariableIDReplace::Replace((CGbItemBase*)pGbObj);

	CCmd *pCmd = pGbObj->GetCmd();

	//CPUID
	CGbItemVariableIDReplace::Replace(pCmd->m_strDatasetPath);

	//Values
	POS pos = pCmd->GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);
		CGbItemVariableIDReplace::Replace(pValue->m_strID);
	}

	CDevice *pDevice = (CDevice*)pGbObj->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice != NULL)
	{
		CGbCommCmdSplit oSplit;
		oSplit.InitCommCmdItemDatasetPath(pDevice, pGbObj);
	}
}
