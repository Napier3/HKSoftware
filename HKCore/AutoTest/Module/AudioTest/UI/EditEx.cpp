// EditEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "AudioTest.h"
#include "EditEx.h"


// CEditEx

IMPLEMENT_DYNAMIC(CEditEx, CEdit)

CEditEx::CEditEx()
{
	m_nState = 1;
}

CEditEx::~CEditEx()
{
}


BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CEditEx ��Ϣ�������
void CEditEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_nState == 1)
	{
		if((nChar >= '0' && nChar <= '9') || (nChar == 0x08) || (nChar == 0x2E))
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if(m_nState == 2)
	{
		if((nChar >= 'A' && nChar <= 'Z') || (nChar >= 'a' && nChar <= 'z') || (nChar == 0x08) || (nChar == 0x2E))
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if(m_nState == 3)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	//CEdit::OnChar(nChar, nRepCnt, nFlags);
}


void CEditEx::SetState(int nState)
{
	m_nState = nState;
}