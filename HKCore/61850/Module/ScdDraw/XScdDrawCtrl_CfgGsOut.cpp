//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_CfgGsOut.cpp  CXScdDrawCtrl_CfgGsOut


#include "stdafx.h"
#include "XScdDrawCtrl_CfgGsOut.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridTitleGsOut
CXScdDrawCtrl_CfgGridTitleGsOut::CXScdDrawCtrl_CfgGridTitleGsOut()
{

}

CXScdDrawCtrl_CfgGridTitleGsOut::~CXScdDrawCtrl_CfgGridTitleGsOut()
{

}

void CXScdDrawCtrl_CfgGridTitleGsOut::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecCfgGoutData *pGoutData=(CIecCfgGoutData *)pData;
	//CIecCfg92Data *p92Data = (CIecCfg92Data*)pData;
	Show_Check(pData, 0, 0, &pGoutData->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("GSOUT"));
	Show_Hex(pData, 0, 2, &pGoutData->m_dwAppID, 2);

	Show_Fiber(pData, 0, 3, &pGoutData->m_nFiberIndex);

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridChsGsOut
CXScdDrawCtrl_CfgGridChsGsOut::CXScdDrawCtrl_CfgGridChsGsOut()
{

}

CXScdDrawCtrl_CfgGridChsGsOut::~CXScdDrawCtrl_CfgGridChsGsOut()
{

}


void CXScdDrawCtrl_CfgGridChsGsOut::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGOUTCH);

	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;

	if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
	{
		if (pGoutCh->m_nIndexExternal == -1)
		{
			return;
		}
	}

	Show_Index(pData, nRow, 0);
	Show_String(pData, nRow, 1, &pGoutCh->m_strName, EndEditCell_String_NameAndID );
	ShowCfgCh_AppCh(pData, nRow, 2, &pGoutCh->m_strAppChID, iecfg_SmvAppChDataType);

	//编号改变
	if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
	{
		if (pGoutCh->m_nIndexExternal != 65535)
		{
			CString strIndex;
			long nIndex=m_pDatas->FindIndex(pData);
			strIndex.Format(_T("%d / %d"), pGoutCh->m_nIndexExternal+1, nIndex+1);
			SetItemText(nRow, 0, strIndex);
		}
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGsOut
CXScdDrawCtrl_CfgGsOut::CXScdDrawCtrl_CfgGsOut()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_CfgGsOut::~CXScdDrawCtrl_CfgGsOut()
{
}

void CXScdDrawCtrl_CfgGsOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_CfgGsOut::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_CfgGridTitleGsOut();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_CfgGsOut::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_CfgGridChsGsOut();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	m_pGridCtrlChs->ShowDatas(pIecCfgData->m_pCfgChs);


	return XCREATE_SUCC;
}
