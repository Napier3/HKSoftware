//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.cpp  CXUserListCtrl


#include "stdafx.h"
#include "XUserListCtrl.h"

CXUserListCtrl::CXUserListCtrl()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXUserListCtrl::~CXUserListCtrl()
{

}

void CXUserListCtrl::InitCollumns()
{
	InsertColumn(XUSER_COL_INDEX,     _T("���"),          LVCFMT_CENTER,40);
	InsertColumn(XUSER_COL_NAME,      _T("����"),          LVCFMT_CENTER,180);
	InsertColumn(XUSER_COL_ID,        _T("ID"),            LVCFMT_CENTER,200);
	InsertColumn(XUSER_COL_CURRTOOL,  _T("��ǰʹ�õĹ���"),LVCFMT_CENTER,80);

}

void CXUserListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CXUser *pUser = (CXUser*)pObj;

	SetItemData(nIndex, (DWORD)pObj);
}
