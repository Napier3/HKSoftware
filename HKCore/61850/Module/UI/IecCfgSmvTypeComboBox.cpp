// IecCfgSmvTypeComboBox.cpp : 实现文件
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



// CIecCfgSmvTypeComboBox 消息处理程序


void CIecCfgSmvTypeComboBox::InitIt()
{
	long index = AddString(_T("IEC61850-9-2"));
	SetItemData(index, SMVTYPE_92);
// 	index = AddString(_T("IEC61850-9-1"));  zhouhj 20211009 9-1报文方式已经淘汰m暂时不显示
// 	SetItemData(index, SMVTYPE_91);
	index = AddString(_T("常规FT3"));
	SetItemData(index, SMVTYPE_6044);
	index = AddString(_T("柔直FT3"));
	SetItemData(index, SMVTYPE_6044_COMMON);
	index = AddString(_T("2M"));
	SetItemData(index, SMVTYPE_2M);
}

void CIecCfgSmvTypeComboBox::InitIt_SmvIn()
{
	long index = 0;
// 	index = AddString(_T("IEC61850-9-2"));
// 	SetItemData(index, SMVTYPE_92);
// 	index = AddString(_T("IEC61850-9-1"));  zhouhj 20211009 9-1报文方式已经淘汰m暂时不显示
// 	SetItemData(index, SMVTYPE_91);
// 	index = AddString(_T("常规FT3"));
// 	SetItemData(index, SMVTYPE_6044);
	index = AddString(_T("柔直FT3"));
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

