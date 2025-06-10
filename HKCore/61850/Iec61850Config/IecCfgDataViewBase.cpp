// IecCfgDataViewBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgDataViewBase.h"

//////////////////////////////////////////////////////////////////////////
//
long CIecCfgDataCopyPasteTool::g_nGlobalRef = 0;
CIecCfgDataCopyPasteTool* CIecCfgDataCopyPasteTool::g_pGlobal = NULL;

CIecCfgDataCopyPasteTool::CIecCfgDataCopyPasteTool()
{

}

CIecCfgDataCopyPasteTool::~CIecCfgDataCopyPasteTool()
{
	RemoveAll();
}

CIecCfgDataCopyPasteTool* CIecCfgDataCopyPasteTool::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIecCfgDataCopyPasteTool();
	}

	return g_pGlobal;
}

void CIecCfgDataCopyPasteTool::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

void CIecCfgDataCopyPasteTool::SetIecCfgDataClassID(UINT nIecCfgDataClassID)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->m_nIecCfgDataClassID = nIecCfgDataClassID;
}

void CIecCfgDataCopyPasteTool::AddPasteButton(UINT nClassID, CButton *pBtnPaste)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_AddPasteButton(nClassID, pBtnPaste);
}

void CIecCfgDataCopyPasteTool::SetPasteButton(CButton *pBtnPaste, UINT nClassID)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_SetPasteButton(pBtnPaste, nClassID);
}

void CIecCfgDataCopyPasteTool::RemovePasteButton(CButton *pBtnPaste)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_RemovePasteButton(pBtnPaste);
}

void CIecCfgDataCopyPasteTool::RestCopySrcList()
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_RestCopySrcList();
}

void CIecCfgDataCopyPasteTool::AddCopySrcData(CIecCfgDataBase *pIecCfgData)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_AddCopySrcData(pIecCfgData);
}

void CIecCfgDataCopyPasteTool::AddCopySrcData(CExBaseList *pListIecCfgDatas)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	if (pListIecCfgDatas->GetCount() > 0)
	{
		CExBaseObject *p = pListIecCfgDatas->GetHead();
		ASSERT (g_pGlobal->m_nIecCfgDataClassID == p->GetClassID());

		if (g_pGlobal->m_nIecCfgDataClassID != p->GetClassID())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ǰ��������ID��%08X != %08X���쳣")
				, g_pGlobal->m_nIecCfgDataClassID , p->GetClassID());
		}
	}

	g_pGlobal->In_AddCopySrcData(pListIecCfgDatas);
}

void CIecCfgDataCopyPasteTool::EnableAllPasteButtons()
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_EnableAllPasteButtons();
}

void CIecCfgDataCopyPasteTool:: EnableAllPasteButton(CButton *pBtnPaste)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_EnablePasteButton(pBtnPaste);
}

void CIecCfgDataCopyPasteTool::OnCfgDatasDelete(CExBaseList *pListDatas)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_OnCfgDatasDelete(pListDatas);
}

void CIecCfgDataCopyPasteTool::OnCfgDatasDelete(CIecCfgDataBase *pIecCfgData)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_OnCfgDatasDelete(pIecCfgData);
}


void CIecCfgDataCopyPasteTool::GetNewDatas(CExBaseList *pListDatas)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return;
	}

	g_pGlobal->In_GetNewDatas(pListDatas);
}

//�ڲ�ʵ�ֺ���
void CIecCfgDataCopyPasteTool::In_AddPasteButton(UINT nClassID, CButton *pBtnPaste)
{
	m_oBtnAndDatasRefObjMngr.AddBtnAndDatasRefObj(nClassID, pBtnPaste);
}

void CIecCfgDataCopyPasteTool::In_SetPasteButton(CButton *pBtnPaste, UINT nClassID)
{
	m_oBtnAndDatasRefObjMngr.SetPasteButton(pBtnPaste, nClassID);
}

void CIecCfgDataCopyPasteTool::In_RemovePasteButton(CButton *pBtnPaste)
{
	m_oBtnAndDatasRefObjMngr.RemovePasteButton(pBtnPaste);
}

void CIecCfgDataCopyPasteTool::In_RestCopySrcList()
{
	RemoveAll();
}

void CIecCfgDataCopyPasteTool::In_AddCopySrcData(CIecCfgDataBase *pIecCfgData)
{
	AddTail(pIecCfgData);
}

void CIecCfgDataCopyPasteTool::In_AddCopySrcData(CExBaseList *pListIecCfgDatas)
{
	Append(pListIecCfgDatas);
}

void CIecCfgDataCopyPasteTool::In_EnableAllPasteButtons()
{
	m_oBtnAndDatasRefObjMngr.EnableButtons(m_nIecCfgDataClassID, GetCount());
}

void CIecCfgDataCopyPasteTool::In_EnablePasteButton(CButton *pBtnPaste)
{
	m_oBtnAndDatasRefObjMngr.EnableButton(pBtnPaste, m_nIecCfgDataClassID, GetCount());
}

void CIecCfgDataCopyPasteTool::In_OnCfgDatasDelete(CExBaseList *pListDatas)
{
	POS pos = pListDatas->GetHeadPosition();
	CIecCfgDataBase *pIecCfgData = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pIecCfgData = (CIecCfgDataBase *)pListDatas->GetNext(pos);

		if (Find(pIecCfgData) != NULL)
		{
			Remove(pIecCfgData);
			bTrue = TRUE;
		}
	}

	if (bTrue)
	{
		In_EnableAllPasteButtons();
	}
}

void CIecCfgDataCopyPasteTool::In_GetNewDatas(CExBaseList *pListDatas)
{
	pListDatas->AppendClone(this);
}

BOOL CIecCfgDataCopyPasteTool::In_OnCfgDatasDelete(CIecCfgDataBase *pIecCfgData)
{
	POS pos = Find(pIecCfgData);

	if (pos != NULL)
	{
		Remove(pIecCfgData);
		In_EnableAllPasteButtons();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
//
CIecCfgDataCopyPasteTool::CBtnAndDatasRefObj::CBtnAndDatasRefObj(UINT nClassID, CButton *pBtnPaste)	
{
	m_nClassID = nClassID;
	m_pBtnPaste = pBtnPaste;
}


void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObj::EnablePasteButton(UINT nClassID, long nSrcDataCount)
{
	ASSERT( m_pBtnPaste != NULL);

	if (m_pBtnPaste != NULL)
	{
		m_pBtnPaste->EnableWindow((nClassID == m_nClassID) && (nSrcDataCount > 0));
	}
}

//////////////////////////////////////////////////////////////////////////
//

void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::AddBtnAndDatasRefObj(UINT nClassID, CButton *pBtnPaste)
{
	CBtnAndDatasRefObj *pNew = new CBtnAndDatasRefObj(nClassID, pBtnPaste);
	AddNewChild(pNew);
}

void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::EnableButtons(UINT nClassID, long nSrcDataCount)
{
	POS pos = GetHeadPosition();
	CBtnAndDatasRefObj *pBtn = NULL;

	while (pos != NULL)
	{
		pBtn = (CBtnAndDatasRefObj *)GetNext(pos);
		pBtn->EnablePasteButton(nClassID, nSrcDataCount);
	}
}

void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::EnableButton(CButton *pBtnPaste, UINT nClassID, long nSrcDataCount)
{
	CBtnAndDatasRefObj *pBtn = FindButton(pBtnPaste);

	if (pBtn != NULL)
	{
		pBtn->EnablePasteButton(nClassID, nSrcDataCount);
	}
}

void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::SetPasteButton(CButton *pBtnPaste, UINT nClassID)
{
	CIecCfgDataCopyPasteTool::CBtnAndDatasRefObj *pFind = FindButton(pBtnPaste);

	if (pFind != NULL)
	{
		pFind->m_nClassID = nClassID;
	}
}

void CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::RemovePasteButton(CButton *pBtnPaste)
{
	CIecCfgDataCopyPasteTool::CBtnAndDatasRefObj *pFind = FindButton(pBtnPaste);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}

CIecCfgDataCopyPasteTool::CBtnAndDatasRefObj* CIecCfgDataCopyPasteTool::CBtnAndDatasRefObjMngr::FindButton(CButton *pBtnPaste)
{
	CBtnAndDatasRefObj *p = NULL;
	CBtnAndDatasRefObj *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CBtnAndDatasRefObj *)GetNext(pos);

		if (p->m_pBtnPaste == pBtnPaste)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
// CIecCfgDataViewBase

const UINT    CIecCfgDataViewBase::g_nIecCfgDataOptrID[IDC_BTN_IECCFG_DATA_OPTR_COUNT] = 
{
	IDC_BTN_IECCFG_DATA_OPTR_ADD,
	IDC_BTN_IECCFG_DATA_OPTR_DELETE ,
// 	IDC_BTN_IECCFG_DATA_OPTR_DELETEALL,
	IDC_BTN_IECCFG_DATA_OPTR_MOVEUP,
	IDC_BTN_IECCFG_DATA_OPTR_MOVEDOWN,
	IDC_BTN_IECCFG_DATA_OPTR_COPY,
	IDC_BTN_IECCFG_DATA_OPTR_PASTE,
	IDC_BTN_IECCFG_DATA_OPTR_EXPORTTO,
	IDC_BTN_IECCFG_DATA_OPTR_INCREASE,
	IDC_BTN_IECCFG_DATA_OPTR_DECREASE,
	IDC_BTN_IECCFG_DATA_OPTR_SELALL

};

CString CIecCfgDataViewBase::g_strIecCfgDataOptrText[IDC_BTN_IECCFG_DATA_OPTR_COUNT] = 
{
	_T(""),  //CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecAdd  //_T("���"),
	_T("ɾ��") ,
// 	_T("ɾ��ȫ��"),
	_T("����"),
	_T("����"),
	_T("����"),
	_T("ճ��"),
	CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecOutputTo,//_T("�����"),
	_T("����"),
	_T("�ݼ�"),
	_T("ȫ��ѡ")
};


CIecCfgDataViewBase::CIecCfgDataViewBase(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

	if (g_strIecCfgDataOptrText[0].GetLength() == 0)
	{
		long nIndex = 0;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_Add;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_Delete;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_UpMove;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_DownMove;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_Copy;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceBase::g_sLangTxt_Paste;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecOutputTo;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceIec_61850Cfg::g_sLangTxt_Increase;
		g_strIecCfgDataOptrText[nIndex++] = CXLanguageResourceIec_61850Cfg::g_sLangTxt_Decrease;
		g_strIecCfgDataOptrText[nIndex++] =  CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecUnselectAll;
	}

	m_pChsView = NULL;
	m_pIecCfgFile = NULL;
	m_pIecCfgDataGrid = NULL;
	m_nGridTop = 0;
	m_pLastSelIecCfgData = NULL;
	m_pIecCfgDatas = NULL;
	m_bSelAllState = FALSE;
}

CIecCfgDataViewBase::~CIecCfgDataViewBase()
{
	FreeGrid();

	//��ȥPaste��ť
	CIecCfgDataCopyPasteTool::RemovePasteButton(&m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_PASTE]);
	CExBaseList listDatas;
	m_pIecCfgDatas->GetIecCfgDatas(listDatas);
	CIecCfgDataCopyPasteTool::OnCfgDatasDelete(&listDatas);
	listDatas.RemoveAll();

	CIecCfgDataCopyPasteTool::Release();
}


void CIecCfgDataViewBase::FreeGrid(CRect &rcGrid)
{
	if (m_pIecCfgDataGrid != NULL)
	{
		m_pIecCfgDataGrid->GetWindowRect(&rcGrid);
		ScreenToClient(&rcGrid);
	}

	FreeGrid();
}

void CIecCfgDataViewBase::FreeGrid()
{
	if (m_pIecCfgDataGrid != NULL)
	{
		m_pIecCfgDataGrid->DestroyWindow();
		delete m_pIecCfgDataGrid;
		m_pIecCfgDataGrid = NULL;
	}
}

void CIecCfgDataViewBase::InitView(CIecCfgDataGridBase *pIecCfgDataGrid)
{

}

void CIecCfgDataViewBase::AdjustSize(int cx, int cy)
{
	if (cy < IDC_IECCFG_DATAVIEW_CY_MIN)
	{
		cy = IDC_IECCFG_DATAVIEW_CY_MIN;
	}

	CRect rc;

	if (m_pIecCfgDataGrid != NULL)
	{
		if (::IsWindow(m_pIecCfgDataGrid->m_hWnd))
		{
			rc.left = 5;
			rc.right = cx - 5;
			rc.top = m_nGridTop;
			rc.bottom = cy - 4 - IDC_BTN_IECCFG_DATA_OPTR_HEIGHT;
			m_pIecCfgDataGrid->MoveWindow(rc, TRUE);
		}
	}

	if (::IsWindow(m_btnIecCfgDataOptr[0].m_hWnd))
	{
		//��ť
		GetAddButtonRect(rc, cy);

		long nIndex = 0;

		for (nIndex=0; nIndex<IDC_BTN_IECCFG_DATA_OPTR_COUNT; nIndex++)
		{
			m_btnIecCfgDataOptr[nIndex].MoveWindow(rc, TRUE);
			rc.OffsetRect(IDC_BTN_IECCFG_DATA_OPTR_WIDTH+5, 0);
		}
	}
}

void CIecCfgDataViewBase::GetAddButtonRect(CRect &rc, long cy)
{
	rc.left = 5;
	rc.top = cy-IDC_BTN_IECCFG_DATA_OPTR_HEIGHT-2;
	rc.right = rc.left + IDC_BTN_IECCFG_DATA_OPTR_WIDTH;
	rc.bottom = rc.top + IDC_BTN_IECCFG_DATA_OPTR_HEIGHT;
}

void CIecCfgDataViewBase::CreateAllButtons(int cx, int cy)
{
	CIecCfgDataCopyPasteTool::Create();

	CRect rc;
	GetAddButtonRect(rc, cy);
	DWORD dwStyle = (WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON) ;

	long nIndex = 0;

	for (nIndex=0; nIndex<IDC_BTN_IECCFG_DATA_OPTR_COUNT; nIndex++)
	{
		m_btnIecCfgDataOptr[nIndex].CreateEx(0, _T("BUTTON"), g_strIecCfgDataOptrText[nIndex]
		, dwStyle, rc, this, g_nIecCfgDataOptrID[nIndex]); 
		m_btnIecCfgDataOptr[nIndex].SetFont(g_pGlobalFont11);
		rc.OffsetRect(IDC_BTN_IECCFG_DATA_OPTR_WIDTH+5, 0);
	}

	CIecCfgDataCopyPasteTool::AddPasteButton(0, &m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_PASTE]);
}

void CIecCfgDataViewBase::EnableAllButtons()
{
	long nDatasCount = m_pIecCfgDatas->GetCfgDataCount();

	m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_DELETE].EnableWindow(m_pLastSelIecCfgData != NULL);
// 	m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_DELETEALL].EnableWindow(nDatasCount > 0);
	
	if (m_pLastSelIecCfgData == NULL)
	{
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_MOVEDOWN].EnableWindow(FALSE);
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_MOVEUP].EnableWindow(FALSE);
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_COPY].EnableWindow(FALSE);
	}
	else
	{
		long nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(m_pLastSelIecCfgData);
		long nCount = m_pIecCfgDatas->GetCfgDataCount();

		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_MOVEDOWN].EnableWindow(nIndex+1 < nCount);
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_MOVEUP].EnableWindow(nIndex > 0);
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_COPY].EnableWindow(TRUE);
	}

	m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_EXPORTTO].EnableWindow(FALSE);
	m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_INCREASE].EnableWindow(nDatasCount > 0);
	m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_DECREASE].EnableWindow(nDatasCount > 0);

}

void CIecCfgDataViewBase::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CIecCfgFile *pFile = (CIecCfgFile*)lHint;
	m_pIecCfgFile = pFile;

	if (m_pChsView != NULL)
	{
		m_pChsView->m_pIecCfgFile = pFile;
		m_pChsView->CreateChsGrid();
	}

	CreateIecCfgDataGrid();
	ShowIecCfgData();	

	if (m_pIecCfgDataGrid != NULL && m_pChsView != NULL)
	{
		m_pIecCfgDataGrid->AttachRefChsGrid(m_pChsView->m_pIecCfgDataChsGrid);
	}

	if ((m_pIecCfgDatas != NULL) && (m_pIecCfgDataGrid != NULL))
	{
		CIecCfgDataCopyPasteTool::EnableAllPasteButton(&m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_PASTE]);
	}
}

void CIecCfgDataViewBase::ShowIecCfgData()
{
	//��õ�ǰ������ͼ��Ӧ�����ݹ������
	m_pIecCfgDatas = GetIecCfgDatas();

	if (m_pIecCfgDatas == NULL)
	{
		return;
	}

	if (m_pIecCfgDataGrid == NULL)
	{
		return;
	}

	//��ʾ���ݵ���񣬲�ѡ�е�һ������
	m_pIecCfgDataGrid->ShowDatas(m_pIecCfgDatas);
	m_pIecCfgDataGrid->SelectRow(1);
	
	//��ȡ��һ���������ݶ��󣬼�¼Ϊ���һ��ѡ�еĶ���
	m_pLastSelIecCfgData = m_pIecCfgDatas->GetIecCfgData(0);
	
	if (m_pChsView != NULL)
	{//��ͨ���������ʾ
		m_pChsView->ShowIecCfgDataChs(m_pLastSelIecCfgData);
	}

	//����Paste��ť��Ӧ��������ID
	CIecCfgDataCopyPasteTool::SetPasteButton(&m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_PASTE]
		, m_pIecCfgDatas->GetIecCfgDataClassID());

	//���°�ť״̬
	EnableAllButtons();
}

//////////////////////////////////////////////////////////////////////////
//��ť��Ӧ����
void CIecCfgDataViewBase::OnBnClickedBtnAdd()
{
	ASSERT (m_pIecCfgDataGrid != NULL);
	ASSERT (m_pIecCfgFile != NULL);
	ASSERT (m_pChsView != NULL);
	ASSERT (m_pIecCfgDatas != NULL);

	if (m_pIecCfgDatas == NULL)
	{
		return;
	}


	CIecCfgDataBase *pCfgData = m_pIecCfgDatas->AddNewIecCfgData();
	
	if (!m_pIecCfgDatas->CanAddCfgData())
	{
		pCfgData->m_nUseFlag = 0;
	}
	else
	{
		pCfgData->m_nUseFlag = 1;
	}

// 	VARIANT vValue;
// 
// 	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_FIBER, vValue);
// 	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_APPID, vValue);
// 	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_SRCMAC, vValue);
// 	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_DESTMAC, vValue);
	AutoSetCfgDataValue(pCfgData, 1);

	//�����SMV�������ͨ��
	if(m_pIecCfgDatas->GetClassID() == CFGCLASSID_CIECCFGDATASSMV)
	{
		CIecCfgSmvDataBase *pSmvCfgData = (CIecCfgSmvDataBase*)pCfgData;
		//pSmvCfgData->UpdateChsIndex();
	}

	int nRow = m_pIecCfgDataGrid->GetRowCount();
	m_pIecCfgDataGrid->ShowData(pCfgData, nRow, TRUE);	
	m_pIecCfgDataGrid->SelectRow(nRow-1);
	m_pIecCfgDataGrid->SetRowHeight(nRow-1, EXBASEGRID_ROWHEIGHT);
	m_pIecCfgDataGrid->Invalidate(FALSE);
	m_pChsView->ShowIecCfgDataChs(pCfgData);
	m_pLastSelIecCfgData = pCfgData;

	m_pIecCfgDataGrid->ResetScrollBars();
	iecfg_SetModified(pCfgData);
	EnableAllButtons();
}

//��β����ʼ������oListIecCfgData����ȡһ��CIecCfgDataBase������m_pIecCfgDatas�в��Һ���һ������ǰ��һ�����ݶ���
//ֻҪ�����ݶ�����oListIecCfgData�У����ҵ�����һ�����ݶ���
CIecCfgDataBase* CIecCfgDataViewBase::GetNextIecCfgData(CExBaseList &oListIecCfgData)
{
	POS pos = oListIecCfgData.GetTailPosition();
	CIecCfgDataBase *p = NULL;
	long nIndex = 0;
	CIecCfgDataBase *pNext = NULL;
	CIecCfgDataBase *pFind = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)oListIecCfgData.GetPrev(pos);
		nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(p);

		//��һ�����ݶ���
		pNext = m_pIecCfgDatas->GetIecCfgData(nIndex+1);

		if(pNext != NULL)
		{
			if (oListIecCfgData.Find(pNext) == NULL)
			{
				pFind = pNext;
				break;
			}
		}

		//��һ�����ݶ���
		pNext = m_pIecCfgDatas->GetIecCfgData(nIndex-1);

		if(pNext != NULL)
		{
			if (oListIecCfgData.Find(pNext) == NULL)
			{
				pFind = pNext;
				break;
			}
		}
	}

	return pFind;
}

void CIecCfgDataViewBase::OnBnClickedBtnDelete()
{
	if (m_pLastSelIecCfgData == NULL)
	{
		return;
	}

	CExBaseList oListItems;
	m_pIecCfgDataGrid->GetAllSelectDatas(&oListItems);

	if (oListItems.GetCount() == 0)
	{
		return;
	}

	//�Ƚ��Ƿ񼴽���ȫ��ɾ��
	CExBaseList oListDatas;
	m_pIecCfgDatas->GetIecCfgDatas(oListDatas);

	if (oListDatas.GetCount() == oListItems.GetCount())
	{
		MessageBox(_T("���ٱ���һ���������ݶ���"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		oListDatas.RemoveAll();
		oListItems.RemoveAll();
		return;
	}

	oListDatas.RemoveAll();
	CIecCfgDataBase *pNextIecCfgData = GetNextIecCfgData(oListItems);
	POS pos = oListItems.GetHeadPosition();
	CIecCfgDataBase *pIecCfgData = NULL;
	CString strName;
	CString strMsg;
	long nIndex = 0;

	//��ȡ�����б���ʾ��ʾ��Ϣ
	while (pos != NULL)
	{
		pIecCfgData = (CIecCfgDataBase *)oListItems.GetNext(pos);
		strName.AppendFormat(_T("��%s��"), pIecCfgData->GetCfgDataShortName());
	}

	strMsg.Format(_T("��ȷʵҪɾ��%s��"), strName);
	UINT nRet = MessageBox(strMsg, _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		oListItems.RemoveAll(); //������Ҫ������б�
		return;
	}

	m_pIecCfgDataGrid->ClearSelect();
	m_pChsView->ShowIecCfgDataChs(NULL);  //�����ͨ�����

	//�������ĩβ��ʼ������ɾ�����������У�ɾ�����ݼ����е����ݶ���
	pos = oListItems.GetTailPosition();

	while (pos != NULL)
	{
		pIecCfgData = (CIecCfgDataBase *)oListItems.GetPrev(pos);
		nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(pIecCfgData);
		m_pIecCfgDataGrid->DeleteRow(nIndex+1);	
		m_pIecCfgDatas->DeleteCfgData(pIecCfgData);
	}

	//���û��ѡ�е���Ŀ����ѡ�е�һ�����ݶ���
	if (m_pIecCfgDatas->GetUseDatasCount() == 0)
	{
		pIecCfgData = m_pIecCfgDatas->GetIecCfgData(0);
		pIecCfgData->m_nUseFlag = 1;
		int nRow = 1;
		m_pIecCfgDataGrid->FreeExBaseCellData(1);
		m_pIecCfgDataGrid->ShowData(pIecCfgData, nRow, FALSE);
	}

	//������ճ�����ߵ�����Դ
	CIecCfgDataCopyPasteTool::OnCfgDatasDelete(&oListItems);
	oListItems.RemoveAll();//������Ҫ������б�

	//��ʾ������������
	m_pLastSelIecCfgData = pNextIecCfgData;

	if (m_pLastSelIecCfgData != NULL)
	{
		nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(m_pLastSelIecCfgData);
		m_pChsView->ShowIecCfgDataChs(m_pLastSelIecCfgData);

		m_pIecCfgDataGrid->SelectRow(nIndex+1);
		m_pChsView->ShowIecCfgDataChs(pNextIecCfgData);
	}

	iecfg_SetModified(m_pIecCfgDatas);
	m_pIecCfgDataGrid->ResetScrollBars();
	m_pIecCfgDataGrid->Invalidate(FALSE);
	EnableAllButtons();
}

void CIecCfgDataViewBase::OnBnClickedBtnDeleteAll()
{
	UINT nRet = MessageBox(_T("��ȷʵҪɾ��ȫ�����ݶ�����"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		return;
	}

	//��ձ��
	m_pLastSelIecCfgData = NULL;
	m_pChsView->ShowIecCfgDataChs(NULL);
	m_pIecCfgDataGrid->ShowDatas(NULL);

	//�������ݹ�����������
	CExBaseList listTemp;
	m_pIecCfgDatas->SetCount(0, listTemp);

	//������ճ�����ߵ�����Դ
	CIecCfgDataCopyPasteTool::OnCfgDatasDelete(&listTemp);

	//ɾ�����ж���
	listTemp.DeleteAll();

	iecfg_SetModified(m_pIecCfgDatas);
	EnableAllButtons();
}

void CIecCfgDataViewBase::OnBnClickedBtnMoveUp()
{
	long nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(m_pLastSelIecCfgData);
	ASSERT( nIndex > 0 );

	if (nIndex <= 0)
	{
		return;
	}

	m_pIecCfgDataGrid->ClearSelect();
	m_pIecCfgDatas->ChangePosition(nIndex, nIndex-1);
	m_pIecCfgDataGrid->ChangeRowPosition(nIndex+1, nIndex);
	m_pIecCfgDataGrid->SelectRow(nIndex);

	iecfg_SetModified(m_pIecCfgDatas);
	EnableAllButtons();
}

void CIecCfgDataViewBase::OnBnClickedBtnMoveDown()
{
	long nIndex = m_pIecCfgDatas->GetIecCfgDataIndex(m_pLastSelIecCfgData);
	long nCount = m_pIecCfgDatas->GetCfgDataCount();

	ASSERT( nIndex < nCount - 1 );

	if (nIndex >= nCount - 1)
	{
		return;
	}

	m_pIecCfgDataGrid->ClearSelect();
	m_pIecCfgDatas->ChangePosition(nIndex, nIndex+1);
	m_pIecCfgDataGrid->ChangeRowPosition(nIndex+1, nIndex+2);
	m_pIecCfgDataGrid->SelectRow(nIndex+2);

	iecfg_SetModified(m_pIecCfgDatas);
	EnableAllButtons();
}

void CIecCfgDataViewBase::OnBnClickedBtnCopy()
{
	CExBaseList oListIecCfgDatas;

	//�ӱ���л��ѡ�е�ȫ�����ݶ���
	m_pIecCfgDataGrid->GetAllSelectDatas(&oListIecCfgDatas);

	//���¿���ճ�����߶��������Դ����
	CIecCfgDataCopyPasteTool::RestCopySrcList();
	CIecCfgDataCopyPasteTool::SetIecCfgDataClassID(m_pIecCfgDatas->GetIecCfgDataClassID());
	CIecCfgDataCopyPasteTool::AddCopySrcData(&oListIecCfgDatas);
	oListIecCfgDatas.RemoveAll();

	//ʹ��ճ����ť
	CIecCfgDataCopyPasteTool::EnableAllPasteButtons();

	EnableAllButtons();
}

void CIecCfgDataViewBase::OnBnClickedBtnPaste()
{
	//�ӹ�������л�ȡ�µ����ݶ���
	CExBaseList oListNewDatas;
	CIecCfgDataCopyPasteTool::GetNewDatas(&oListNewDatas);
	
	POS pos = oListNewDatas.GetHeadPosition();
	CIecCfgDataBase *pIecCfgData = NULL;
	int nRow = m_pIecCfgDataGrid->GetRowCount();
	long nMaxCount = m_pIecCfgDatas->GetMaxCfgDataCount();

	while (pos != NULL)
	{
		pIecCfgData = (CIecCfgDataBase *)oListNewDatas.GetNext(pos);

		if (m_pIecCfgDatas->GetUseDatasCount() >= nMaxCount)
		{
			pIecCfgData->m_nUseFlag = 0;
		}

		//��������ӵ����ݼ�����
		m_pIecCfgDatas->AddNewChild(pIecCfgData);

		//��ճ����������ʾ�������
		m_pIecCfgDataGrid->ShowData(pIecCfgData, nRow, TRUE);
		m_pIecCfgDataGrid->SetRowHeight(nRow-1, EXBASEGRID_ROWHEIGHT);
	}

	//ѡ�б����
	m_pIecCfgDataGrid->SelectRow(nRow-1);

	//��ʾͨ������
	if (pIecCfgData != NULL)
	{
		m_pChsView->ShowIecCfgDataChs(pIecCfgData);
		m_pIecCfgDataGrid->Invalidate(FALSE);
	}

	m_pIecCfgDataGrid->ResetScrollBars();
	iecfg_SetModified(m_pIecCfgDatas);
	oListNewDatas.RemoveAll();
}

void CIecCfgDataViewBase::OnBnClickedBtnExportTo()
{

}

void CIecCfgDataViewBase::AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nOffset)
{
	VARIANT vFiberMin, vFiberMax;
	vFiberMin.vt = vFiberMax.vt = VT_I4;
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(m_pIecCfgDataGrid->GetAppPortDataType());
	vFiberMin.ulVal = 0;
	vFiberMax.ulVal = -1;

	if (pDataType != NULL)
	{
		vFiberMax.ulVal = pDataType->GetCount() - 1;
	}

	if (vFiberMax.ulVal < 0)
	{
		vFiberMax.ulVal = 7;
	}

	VARIANT vAppIDMin, vAppIDMax;
	vAppIDMin.vt = vAppIDMax.vt = VT_UI4;
	vAppIDMin.ulVal = 0;
	vAppIDMax.ulVal = 0x0FFFF;
	VARIANT vMacMin, vMacMax;
	vMacMin.vt = vMacMax.vt = VT_UI8;
	vMacMin.ullVal = 0;
	vMacMax.ullVal = 0x0FFFFFFFFFFFF;

	VARIANT vValue;

	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_FIBER, vValue, nOffset, &vFiberMin, &vFiberMax);
	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_APPID, vValue, nOffset, &vAppIDMin, &vAppIDMax);
	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_SRCMAC, vValue, nOffset, &vMacMin, &vMacMax);
	m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_DESTMAC, vValue, nOffset, &vMacMin, &vMacMax);
}

void CIecCfgDataViewBase::AutoSetCfgDataValue(long nOffset)
{
	CExBaseList oList;
	m_pIecCfgDatas->GetIecCfgDatas(oList);

	CIecCfgDataBase *pCfgData = NULL;
//	VARIANT vValue;
	POS pos = oList.GetHeadPosition();
	m_pIecCfgDataGrid->ClearSelect();

// 	VARIANT vFiberMin, vFiberMax;
// 	vFiberMin.vt = vFiberMax.vt = VT_I4;
// 	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(m_pIecCfgDataGrid->GetAppPortDataType());
// 	vFiberMin.ulVal = 0;
// 	vFiberMax.ulVal = -1;
// 
// 	if (pDataType != NULL)
// 	{
// 		vFiberMax.ulVal = pDataType->GetCount() - 1;
// 	}
// 	
// 	if (vFiberMax.ulVal < 0)
// 	{
// 		vFiberMax.ulVal = 7;
// 	}
// 
// 	VARIANT vAppIDMin, vAppIDMax;
// 	vAppIDMin.vt = vAppIDMax.vt = VT_UI4;
// 	vAppIDMin.ulVal = 0;
// 	vAppIDMax.ulVal = 0x0FFFF;
// 	VARIANT vMacMin, vMacMax;
// 	vMacMin.vt = vMacMax.vt = VT_UI8;
// 	vMacMin.ulVal = 0;
// 	vMacMax.ulVal = 0x0FFFF;

	while (pos != NULL)
	{
		pCfgData = (CIecCfgDataBase *)oList.GetNext(pos);
// 		m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_FIBER, vValue, nOffset, &vFiberMin, &vFiberMax);
// 		m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_APPID, vValue, nOffset, &vAppIDMin, &vAppIDMax);
// 		m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_SRCMAC, vValue, nOffset, &vMacMin, &vMacMax);
// 		m_pIecCfgDatas->AutoSetCfgDataValue(pCfgData, CFGDATAID_DESTMAC, vValue, nOffset, &vMacMin, &vMacMax);
		AutoSetCfgDataValue(pCfgData, nOffset);
	}

	//���±��
	int nRow = m_pIecCfgDataGrid->GetRowCount();
	m_pIecCfgDataGrid->UpdateDatas();
	m_pIecCfgDataGrid->SelectRow(nRow-1);

	//ѡ�����һ��
	long nCount = m_pIecCfgDatas->GetCfgDataCount();
	m_pLastSelIecCfgData = m_pIecCfgDatas->GetIecCfgData(nCount-1);
	m_pChsView->ShowIecCfgDataChs(m_pLastSelIecCfgData);

	iecfg_SetModified(m_pIecCfgDatas);
	//�����ʱ����
	oList.RemoveAll();
}

void CIecCfgDataViewBase::OnBnClickedBtnIncrease()
{
	AutoSetCfgDataValue(1);
}

void CIecCfgDataViewBase::OnBnClickedBtnDecrease()
{
	AutoSetCfgDataValue(-1);
}

void CIecCfgDataViewBase::OnBnClickedBtnSelAll()
{
	CExBaseList oList;
	m_pIecCfgDatas->GetIecCfgDatas(oList);
	CIecCfgDataBase *pCfgData = NULL;
	POS pos = oList.GetHeadPosition();
	m_pIecCfgDataGrid->ClearSelect();

	while (pos != NULL)
	{
		pCfgData = (CIecCfgDataBase *)oList.GetNext(pos);
		pCfgData->m_nUseFlag = m_bSelAllState;
	}

	m_pIecCfgDataGrid->UpdateDatas();
	
	if (m_pLastSelIecCfgData != NULL)
	{
		long nRow = oList.FindIndex(m_pLastSelIecCfgData);
		if (nRow >= 0)
		{
			nRow++;
			m_pIecCfgDataGrid->SelectRow(nRow);
		}
	}

	oList.RemoveAll();
	iecfg_SetModified(m_pIecCfgDatas);
	m_bSelAllState = !m_bSelAllState;

	if (m_bSelAllState)
	{
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_SELALL].SetWindowText(CXLanguageResourceBase::g_sLangTxt_SelAll);
	}
	else
	{
		m_btnIecCfgDataOptr[INDEX_BTN_IECCFG_DATA_OPTR_SELALL].SetWindowText(CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecUnselectAll);
	}
}

//////////////////////////////////////////////////////////////////////////
//�ⲿ����
void CIecCfgDataViewBase::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (nRow <= 0 || nCol <= 0)
	{
		return;
	}

	PEXBASECELLDATA pVellData = (EXBASECELLDATA*)pGridCtrl->GetItemData(nRow, nCol);

	if (pVellData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  ���û�й������ݶ���"), nRow, nCol);
		return;
	}

	ASSERT (pVellData->pObj != NULL);
	ASSERT (m_pChsView != NULL);

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;

	if (pIecCfgData == NULL || m_pChsView == NULL)
	{
		return;
	}

	if (m_pLastSelIecCfgData == pIecCfgData)
	{
		return;
	}

	m_pChsView->ShowIecCfgDataChs(pIecCfgData);
	m_pLastSelIecCfgData = pIecCfgData;

	EnableAllButtons();
}
