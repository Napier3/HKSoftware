//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
		//��ͬ���ı���Ҫ�ظ����
		strXLangID = xlang_FindLandidByLangTxt(pButton->m_strText);

		//û���ҵ���ص��ı�����Ϊ�µ��ı�
		if (strXLangID.GetLength() == 0)
		{
			//���Menu��XLangID
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

	//���һ�ȡ���ԣ����û���ҵ���������µ����Զ���
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

