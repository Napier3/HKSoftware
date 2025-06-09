// D:\WorkPM\Source\PMTest\GuideBookDev\UI\DataGroupListView.cpp : 实现文件
//

#include "stdafx.h"
#include "DataGroupListView.h"

// CDataGroupListView

IMPLEMENT_DYNAMIC(CDataGroupListView, CExBaseListListCtrl)

CDataGroupListView::CDataGroupListView()
{
	m_bFirstShow = TRUE;
	m_nCurrSelIndex = 0;
}

CDataGroupListView::~CDataGroupListView()
{
}


CString CDataGroupListView::GetDataPath(CShortData *pData, CExBaseObject *pRoot, const CString &strFlag)
{
	CString strPath;
	CDataGroup *pParent = (CDataGroup*)pData->GetParent();
	CString strTemp;

	strPath = pData->m_strRemark;

	while (pParent != NULL)
	{
		if (pParent == pRoot)
		{
			break;
		}

		strTemp.Format(_T("%s%s"), ((CDataGroup*)pParent)->m_strValue, strFlag);
		strPath = strTemp + strPath;
		pParent = (CDataGroup *)pParent->GetParent();
	}

	return strPath;
}

void CDataGroupListView::OnDataSelChanged(CShortData *pData)
{
	if (pData->m_dwReserved == 0)
	{
		this->DeleteObject(pData);
		m_pList->Remove(pData);
		UpdateIndex();
	}
	else
	{
		pData->m_strValue.Format(_T("%d"), pData->m_dwItemData);
		m_pList->AddTail(pData);
		this->InsertObj(m_pList->GetCount()-1, pData);
	}
}

void CDataGroupListView::OnDataValueChanged(CShortData *pData)
{
	pData->m_strValue.Format(_T("%d"), pData->m_dwItemData);
	CExBaseListListCtrl::UpdateListCtrl(pData);
}

BEGIN_MESSAGE_MAP(CDataGroupListView, CExBaseListListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CDataGroupListView::OnNMDblclk)
END_MESSAGE_MAP()


// CDataGroupListView 消息处理程序

int CDataGroupListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CExBaseListListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CDataGroupListView::InitCollumns()
{
	InsertColumn(0,/*_T("编号")*/g_sLangTxt_Index,LVCFMT_LEFT,50);
	InsertColumn(1,/*_T("名称")*/g_sLangTxt_Name,LVCFMT_LEFT,150);
	InsertColumn(2,/*_T("路径")*/g_sLangTxt_Path,LVCFMT_LEFT,150);
	InsertColumn(3,/*_T("数值")*/g_sLangTxt_Value,LVCFMT_LEFT,50);
}

void CDataGroupListView::UpdateListCtrl(CExBaseObject* pObj, long nItem)
{
	CShortData *pData = (CShortData *)pObj;

	CString strTemp;
	strTemp.Format(_T("%d"), nItem+1);
	SetItemText(nItem, 0, strTemp);
	SetItemText(nItem, 1, pData->m_strName);
	strTemp = GetDataPath(pData, m_pRoot, m_strFlag);
	SetItemText(nItem, 2, strTemp);
	SetItemText(nItem, 3, pData->m_strValue);
}

void CDataGroupListView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	long nCount = GetSelectedCount();

	if(nCount == 1)
	{
		int nItem = -1;
		nItem = GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)GetItemData(nItem);
	}

	*pResult = 0;
}
