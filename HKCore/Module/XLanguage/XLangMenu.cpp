//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangRibbonCtrls.cpp


#include "stdafx.h"
#include "XLangMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CXLangMenu::CXLangMenu()
{
	
}

CXLangMenu::~CXLangMenu()
{

}


BOOL CXLangMenu::LoadMenu(UINT nIDResource)
{
	BOOL b = CMenu::LoadMenu(nIDResource);

	if (!b)
	{
		return b;
	}

	long nNewXLangStrCount = 0;
	InitMenuXLang(this, nNewXLangStrCount);

	if (nNewXLangStrCount > 0)
	{
		xlang_Save();
	}

	return b;

}

void CXLangMenu::InitMenuXLang(CMenu *pMenu, long &nNewXLangStrCount)
{
	long nCount = pMenu->GetMenuItemCount();
	long nPos = 0;
	UINT nMenuItemID = 0;
	CString strXLangID, strText;
	CMenu *pSubMenu = NULL;

	for (nPos=0; nPos<nCount; nPos++)
	{
		nMenuItemID = pMenu->GetMenuItemID(nPos);

		if (nMenuItemID == 0xFFFFFFFF)
		{
			pSubMenu = pMenu->GetSubMenu(nPos);

			if (pSubMenu != NULL)
			{
				InitMenuXLang(pSubMenu, nNewXLangStrCount);
			}
		}
		else if (nMenuItemID > 0)
		{
			strXLangID.Format(_T("sMenu_%d"), nMenuItemID);

			if (xlang_GetLgugStr(strXLangID, strText))
			{
				pMenu->ModifyMenu(nPos, MF_BYPOSITION, nMenuItemID, strText);
			}
			else
			{
				if (pMenu->GetMenuString(nPos, strText, MF_BYPOSITION) > 0)
				{
					xlang_AddString(strXLangID, strText);
					nNewXLangStrCount++;
				}
			}
		}
	}
}

