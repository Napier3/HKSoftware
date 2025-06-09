//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangRibbonCtrls.cpp


#include "stdafx.h"
#include "XLangToolBar.h"
#include <afxtoolbar.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CXLangToolBar::CXLangToolBar()
{
	
}

CXLangToolBar::~CXLangToolBar()
{

}


void CXLangToolBar::AdjustLocations()
{
	CMFCToolBar::AdjustLocations();

	UpdateTooltipsEx();
	RedrawCustomizeButton();
}

void CXLangToolBar::UpdateTooltipsEx()
{
	if (m_pToolTip->GetSafeHwnd() == NULL)
	{
		return;
	}

	while (m_nTooltipsCount-- >= 0)
	{
		m_pToolTip->DelTool(this, m_nTooltipsCount);
	}

	CString strXLangID, strText, strTrans;
	BOOL bNeedSave = FALSE;

	m_nTooltipsCount = 0;
	for (int i = 0; i < m_Buttons.GetCount(); i++)
	{
		CMFCToolBarButton* pButton = GetButton(i);
		ASSERT_VALID(pButton);

		if (pButton->m_nStyle != TBBS_SEPARATOR)
		{
			CString strTipText;

			//���ȸ���ID�����ı���������ڣ������Tip
			strXLangID.Format(_T("sToolTip_%d"), pButton->m_nID);

			if (xlang_GetLgugStr(strXLangID, strText))
			{
				AfxExtractSubString(strTipText, strText, 0, '\n');

				if (!pButton->OnUpdateToolTip(this, i, *m_pToolTip, strTipText))
				{
					m_pToolTip->AddTool(this, strTipText, pButton->Rect(), i + 1);
				}
			}
			else
			{
				//������Դ����
				TCHAR szFullText [256];
				AfxLoadString(pButton->m_nID, szFullText);

				//�ڶ�������Դ�����в������ݣ�������ڣ��򲻴�������
				strTrans = xlang_FindLandTransByLangTxt(szFullText);

				if (strTrans.GetLength() > 1)
				{
					AfxExtractSubString(strTipText, strTrans, 1, '\n');
					//strTipText = strTrans;
				}
				else
				{
					//�����Դ�ַ��������ڣ�����ӵ���������Դ�ļ�
					AfxExtractSubString(strTipText, szFullText, 1, '\n');

					if (szFullText[0] != 0)
					{
						strText = szFullText;
						xlang_AddString(strXLangID, strText);
						bNeedSave = TRUE;
					}
				}

				if (!pButton->OnUpdateToolTip(this, i, *m_pToolTip, strTipText))
				{
					m_pToolTip->AddTool(this, LPSTR_TEXTCALLBACK, pButton->Rect(), i + 1);
				}
			}

			m_nTooltipsCount ++;
		}
	}

	if (bNeedSave)
	{
		xlang_Save();
	}
}
