// MyCoboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestGridVs2008.h"
#include "MyCoboBox.h"


// CMyCoboBox

IMPLEMENT_DYNAMIC(CMyCoboBox, CComboBox)

CMyCoboBox::CMyCoboBox()
{

}

CMyCoboBox::~CMyCoboBox()
{
}


BEGIN_MESSAGE_MAP(CMyCoboBox, CComboBox)
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CMyCoboBox::OnCbnKillfocus)
END_MESSAGE_MAP()



// CMyCoboBox ��Ϣ�������



void CMyCoboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
}

void CMyCoboBox::OnCbnKillfocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
