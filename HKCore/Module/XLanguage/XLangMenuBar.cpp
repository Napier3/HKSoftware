//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangRibbonCtrls.cpp


#include "stdafx.h"
#include "XLangMenuBar.h"
#include <afxmenubar.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 long CXLangMenuBar::g_nMenuRootIndex = 0;

CXLangMenuBar::CXLangMenuBar()
{
	
}

CXLangMenuBar::~CXLangMenuBar()
{

}


void CXLangMenuBar::CreateFromMenu(HMENU hMenu, BOOL bDefaultMenu, BOOL bForceUpdate)
{
	CMFCMenuBar::CreateFromMenu(hMenu, bDefaultMenu, bForceUpdate);

	InitXLangButtons();

}

void CXLangMenuBar::InitXLangByButton(CMFCToolBarMenuButton *pMenuButton)
{
	InitXLangText(pMenuButton);
	const CObList &listCmds = pMenuButton->GetCommands();

	POSITION pos = listCmds.GetHeadPosition();
	CMFCToolBarMenuButton *pButton = NULL;

	while (pos != NULL)
	{
		pButton = (CMFCToolBarMenuButton *)m_Buttons.GetNext(pos);
		InitXLangByButton(pButton);
	}
}

void CXLangMenuBar::InitXLangText(CMFCToolBarMenuButton *pButton)
{
	if (pButton->m_nID == 0 && pButton->m_strText.GetLength() == 0)
	{
		return;
	}

	CString strXLangID, strText;

	if ((pButton->m_nID == 0xFFFFFFFF) || (pButton->m_nID==0)) //-1
	{
		//相同的文本不要重复多次
		strXLangID = xlang_FindLandidByLangTxt(pButton->m_strText);

		//没有找到相关的文本，则为新的文本
		if (strXLangID.GetLength() == 0)
		{
			//获得Menu的XLangID
			while (TRUE)
			{
				g_nMenuRootIndex++;
				strXLangID.Format(_T("sMenuPop_%d"), g_nMenuRootIndex);

				if (!xlang_IsLandidExist(strXLangID))
				{
					break;
				}
			}
		}
	}
	else
	{
		strXLangID.Format(_T("sMenuItem_%d"), pButton->m_nID);
	}

	//查找获取语言，如果没有找到，则添加新的语言对象
	if (!xlang_GetLgugStr(strXLangID, strText))
	{
		if (pButton->m_strText.GetLength() > 0)
		{
			xlang_AddString(strXLangID, pButton->m_strText);
		}
		else
		{
			int i = 0;
		}
	}
	else
	{
		pButton->m_strText = strText;
	}
}

void CXLangMenuBar::InitXLangButtons()
{
	POSITION pos = m_Buttons.GetHeadPosition();
	CMFCToolBarMenuButton *pButton = NULL;

	while (pos != NULL)
	{
		pButton = (CMFCToolBarMenuButton *)m_Buttons.GetNext(pos);
		InitXLangByButton(pButton);
	}
}

