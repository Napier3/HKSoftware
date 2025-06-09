//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclGsOut.cpp  CXScdDrawCtrl_SclGsOut


#include "stdafx.h"
#include "XScdDrawCtrl_SclGsOut.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGridTitleGsOut
CXScdDrawCtrl_SclGridTitleGsOut::CXScdDrawCtrl_SclGridTitleGsOut()
{

}

CXScdDrawCtrl_SclGridTitleGsOut::~CXScdDrawCtrl_SclGridTitleGsOut()
{

}

void CXScdDrawCtrl_SclGridTitleGsOut::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);
	Show_StaticString(pData, 0, 1, _T("GSOUT"));

	if (nClassID == SCLIECCLASSID_CTRL_GS_OUT)
	{
		CSclCtrlGsOut *pSclCtrlGsOut = (CSclCtrlGsOut*)pData;
		Show_StaticString(pData, 0, 1, pSclCtrlGsOut->m_strID);
		Show_Hex(pData, 0, 2, &pSclCtrlGsOut->m_dwAppID, 2);
		Show_StaticString(pData, 0, 3, pSclCtrlGsOut->m_strMac);
	}
	else
	{
		CIecCfgGoutData *pGoutData=(CIecCfgGoutData *)pData;
		Show_Check(pData, 0, 0, &pGoutData->m_nUseFlag);
		Show_Fiber(pData, 0, 3, &pGoutData->m_nFiberIndex);
	}

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGridChsGsOut
CXScdDrawCtrl_SclGridChsGsOut::CXScdDrawCtrl_SclGridChsGsOut()
{

}

CXScdDrawCtrl_SclGridChsGsOut::~CXScdDrawCtrl_SclGridChsGsOut()
{

}


void CXScdDrawCtrl_SclGridChsGsOut::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	long nIndexExternal = 65535;

	if (nClassID == SCLIECCLASSID_CH_GS_OUT)
	{
		CSclChGsOut *pChGout = (CSclChGsOut*)pData;

		if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
		{
			if (!ChIsUsed_BeginObj(pData))
			{
				return;
			}
		}

		Show_Index(pData, nRow, 0, 1);
		Show_StaticString(pData, nRow, 1, &pChGout->m_strName );
		Show_StaticString(pData, nRow, 2, &pChGout->fcda_type);
		nIndexExternal = nRow ;
	}
	else
	{
		CIecCfgGoutCh *p92Ch = (CIecCfgGoutCh*)pData;

		if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
		{
			if (p92Ch->m_nIndexExternal == -1)
			{
				return;
			}
		}

		Show_Index(pData, nRow, 0);
		Show_String(pData, nRow, 1, &p92Ch->m_strName, EndEditCell_String_NameAndID );
		ShowCfgCh_AppCh(pData, nRow, 2, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);
		nIndexExternal = p92Ch->m_nIndexExternal ;
	}
	
	//编号改变
	if (CXScdDrawConstGlobal::OnlyShowUsedGsOutChs())
	{
		if (nIndexExternal != 65535)
		{
			CString strIndex;
			long nIndex=m_pDatas->FindIndex(pData);
			strIndex.Format(_T("%d/%d"), nIndexExternal+1, nIndex+1);
			SetItemText(nRow, 0, strIndex);
		}
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGsOut
CXScdDrawCtrl_SclGsOut::CXScdDrawCtrl_SclGsOut()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_SclGsOut::~CXScdDrawCtrl_SclGsOut()
{
}

void CXScdDrawCtrl_SclGsOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_SclGsOut::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_SclGridTitleGsOut();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);
	m_pGridCtrlTitle->AdjustAllCols();

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_SclGsOut::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_SclGridChsGsOut();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	if (pData->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		m_pGridCtrlChs->ShowDatas((CExBaseList*)pData);
	}
	else
	{
		CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
		m_pGridCtrlChs->ShowDatas(pIecCfgData->m_pCfgChs);
	}

	return XCREATE_SUCC;
}

