// NetDeviceComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "NetDeviceComboBox.h"


// CNetDeviceComboBox

IMPLEMENT_DYNAMIC(CNetDeviceComboBox, CComboBox)

CNetDeviceComboBox::CNetDeviceComboBox()
{
	m_pNetCardList = CStNetCardInforList::Create();
}

CNetDeviceComboBox::~CNetDeviceComboBox()
{
	m_pNetCardList->Release();
}


BEGIN_MESSAGE_MAP(CNetDeviceComboBox, CComboBox)
END_MESSAGE_MAP()



// CNetDeviceComboBox 消息处理程序

void CNetDeviceComboBox::InitNetDevice(BOOL bOnllyShowDesc)
{
	POS pos = m_pNetCardList->GetHeadPosition();
	CStNetCardInfor *pCard = NULL;
	ResetContent();
	CString strText;

	while (pos != NULL)
	{
		pCard = m_pNetCardList->GetNext(pos);

		if (bOnllyShowDesc)
		{
			strText= pCard->m_strInfor;;
		}
		else
		{
			strText.Format(_T("%s(%s)"), CString(pCard->m_strInfor), CString(pCard->m_strIP));
		}

		long nIndex = AddString(strText);
		SetItemDataPtr(nIndex, pCard);
	}

	SetCurSel(0);
}
