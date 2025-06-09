//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_VtestGsOut.cpp  CXScdDrawCtrl_VtestGsOut


#include "stdafx.h"
#include "XScdDrawCtrl_VtestGsOut.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridTitleGsOut
CXScdDrawCtrl_VtestGridTitleGsOut::CXScdDrawCtrl_VtestGridTitleGsOut()
{

}

CXScdDrawCtrl_VtestGridTitleGsOut::~CXScdDrawCtrl_VtestGridTitleGsOut()
{

}

void CXScdDrawCtrl_VtestGridTitleGsOut::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecVtestGoutData *pGoutData=(CIecVtestGoutData *)pData;
	//CIecVtest92Data *p92Data = (CIecVtest92Data*)pData;
	Show_Check(pData, 0, 0, &pGoutData->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("GSOUT"));
	Show_Hex(pData, 0, 2, &pGoutData->m_dwAppID, 2);

	Show_Fiber(pData, 0, 3, &pGoutData->m_nFiberIndex);

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridChsGsOut
CXScdDrawCtrl_VtestGridChsGsOut::CXScdDrawCtrl_VtestGridChsGsOut()
{

}

CXScdDrawCtrl_VtestGridChsGsOut::~CXScdDrawCtrl_VtestGridChsGsOut()
{

}


void CXScdDrawCtrl_VtestGridChsGsOut::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecVtest92Ch *p92Ch = (CIecVtest92Ch*)pData;

	if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
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
	if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
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
//CXScdDrawCtrl_VtestGsOut
CXScdDrawCtrl_VtestGsOut::CXScdDrawCtrl_VtestGsOut()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VtestGsOut::~CXScdDrawCtrl_VtestGsOut()
{
}

void CXScdDrawCtrl_VtestGsOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset);
}


DWORD CXScdDrawCtrl_VtestGsOut::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_VtestGridTitleGsOut();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_VtestGsOut::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_VtestGridChsGsOut();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecVtestDataBase *pIecVtestData = (CIecVtestDataBase*)pData;
	m_pGridCtrlChs->ShowDatas(pIecVtestData->m_pVtestChs);

	return XCREATE_SUCC;
}

