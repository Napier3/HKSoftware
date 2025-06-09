// IecCfgSmvTypeComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IecCfgSmvTypeComboBox.h"


// CIecCfgSmvTypeComboBox

IMPLEMENT_DYNAMIC(CIecCfgSmvTypeComboBox, CComboBox)

CIecCfgSmvTypeComboBox::CIecCfgSmvTypeComboBox()
{

}

CIecCfgSmvTypeComboBox::~CIecCfgSmvTypeComboBox()
{
}


BEGIN_MESSAGE_MAP(CIecCfgSmvTypeComboBox, CComboBox)
END_MESSAGE_MAP()



// CIecCfgSmvTypeComboBox ��Ϣ�������


void CIecCfgSmvTypeComboBox::InitIt()
{
	long index = AddString(_T("IEC61850-9-2"));
	SetItemData(index, SMVTYPE_92);
// 	index = AddString(_T("IEC61850-9-1"));  zhouhj 20211009 9-1���ķ�ʽ�Ѿ���̭m��ʱ����ʾ
// 	SetItemData(index, SMVTYPE_91);
	index = AddString(_T("����FT3"));
	SetItemData(index, SMVTYPE_6044);
	index = AddString(_T("��ֱFT3"));
	SetItemData(index, SMVTYPE_6044_COMMON);
	index = AddString(_T("2M"));
	SetItemData(index, SMVTYPE_2M);
}

void CIecCfgSmvTypeComboBox::InitIt_SmvIn()
{
	long index = 0;
// 	index = AddString(_T("IEC61850-9-2"));
// 	SetItemData(index, SMVTYPE_92);
// 	index = AddString(_T("IEC61850-9-1"));  zhouhj 20211009 9-1���ķ�ʽ�Ѿ���̭m��ʱ����ʾ
// 	SetItemData(index, SMVTYPE_91);
// 	index = AddString(_T("����FT3"));
// 	SetItemData(index, SMVTYPE_6044);
	index = AddString(_T("��ֱFT3"));
	SetItemData(index, SMVTYPE_6044_COMMON);
	index = AddString(_T("2M"));
	SetItemData(index, SMVTYPE_2M);
}

long CIecCfgSmvTypeComboBox::GetSmvType()
{
	long nSel = GetCurSel();
	return GetItemData(nSel);
}

void CIecCfgSmvTypeComboBox::SetSmvType(long nSmvType)
{
	long nIndexFind = 0;
	long nIndex = 0;
	long nCount = GetCount();

	for (nIndex = 0; nIndex<nCount; nIndex++)
	{
		if (nSmvType == GetItemData(nIndex))
		{
			nIndexFind = nIndex;
			break;
		}
	}

	SetCurSel(nIndexFind);
}

