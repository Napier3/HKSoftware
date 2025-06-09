// MyCoboBox.cpp : 实现文件
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



// CMyCoboBox 消息处理程序



void CMyCoboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
}

void CMyCoboBox::OnCbnKillfocus()
{
	// TODO: 在此添加控件通知处理程序代码
}
