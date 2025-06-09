//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_VtestSvOut.cpp  CXScdDrawCtrl_VtestSvOut


#include "stdafx.h"
#include "XScdDrawCtrl_VtestSvOut.h"

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridTitleSvOut
CXScdDrawCtrl_VtestGridTitleSvOut::CXScdDrawCtrl_VtestGridTitleSvOut()
{

}

CXScdDrawCtrl_VtestGridTitleSvOut::~CXScdDrawCtrl_VtestGridTitleSvOut()
{

}

void CXScdDrawCtrl_VtestGridTitleSvOut::ShowTitle(CExBaseObject *pData)
{
	CIecVtest92Data *p92Data = (CIecVtest92Data*)pData;
	Show_Check(pData, 0, 0, &p92Data->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("SVOUT"));
	Show_Hex(pData, 0, 2, &p92Data->m_dwAppID, 2);
	Show_Fiber(pData, 0, 3,    &p92Data->m_nFiberIndex);




}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridChsSvOut
CXScdDrawCtrl_VtestGridChsSvOut::CXScdDrawCtrl_VtestGridChsSvOut()
{

}

CXScdDrawCtrl_VtestGridChsSvOut::~CXScdDrawCtrl_VtestGridChsSvOut()
{

}


void CXScdDrawCtrl_VtestGridChsSvOut::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecVtest92Ch *p92Ch = (CIecVtest92Ch*)pData;

	if (CXScdDrawConstGlobal::OnlyShowUsedSvOutChs())
	{
		if (p92Ch->m_nIndexExternal == -1)
		{
			return;
		}
	}

	Show_Index(pData, nRow, 0);
	Show_String(pData, nRow, 1, &p92Ch->m_strName, EndEditCell_String_NameAndID );
	ShowVtestCh_AppCh(pData, nRow, 2, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);

	//编号改变
	if (CXScdDrawConstGlobal::OnlyShowUsedSvOutChs())
	{
		if (p92Ch->m_nIndexExternal != 65535)
		{
			CString strIndex;
			long nIndex=m_pDatas->FindIndex(pData);
			strIndex.Format(_T("%d / %d"), p92Ch->m_nIndexExternal+1, nIndex+1);
			SetItemText(nRow, 0, strIndex);
		}
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestSvOut
CXScdDrawCtrl_VtestSvOut::CXScdDrawCtrl_VtestSvOut()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VtestSvOut::~CXScdDrawCtrl_VtestSvOut()
{
}

void CXScdDrawCtrl_VtestSvOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset);
}


// DWORD CXScdDrawCtrl_VtestSvOut::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
// {
// 	UINT nClassID = pData->GetClassID();
// 
// 	if (nClassID != CFGCLASSID_CIECCFG92DATA || nClassID != CFGCLASSID_CIECCFG91DATA || nClassID != CFGCLASSID_CIECCFG6044DATA)
// 	{
// 		return XCREATE_FAIL;
// 	}
// 
// 	return XCREATE_SUCC;
// }


DWORD CXScdDrawCtrl_VtestSvOut::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_VtestGridTitleSvOut();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_VtestSvOut::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_VtestGridChsSvOut();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecVtestDataBase *pIecVtestData = (CIecVtestDataBase*)pData;
	m_pGridCtrlChs->ShowDatas(pIecVtestData->m_pVtestChs);

	return XCREATE_SUCC;
}

