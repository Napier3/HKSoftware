// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// CharLibDevView.cpp : CCharLibDevView 类的实现
//

#include "stdafx.h"
#include "CharLibDev.h"

#include "CharLibDevDoc.h"
#include "CharLibDevView.h"
#include "DlgCharElement.h"
#include "XLanguageResourceAts_CharLibDev.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Index_gridCharInterface    0
#define Index_btnNewVariable       1
#define Index_btnDeleteVariable    2

#define Index_gridCharElement      3
#define Index_btnNewElement        4
#define Index_btnDeleteElement     5
#define Index_btnMoveUp            6
#define Index_btnMoveDown          7

#define Index_gridTestLine        8

#define Index_stcCharDraw          9

// CCharLibDevView

IMPLEMENT_DYNCREATE(CCharLibDevView, CFormView)

BEGIN_MESSAGE_MAP(CCharLibDevView, CFormView)
	
	ON_BN_CLICKED(IDC_BTN_NEW_VARIABLE, &CCharLibDevView::OnBnClickedBtnNewVariable)
	ON_BN_CLICKED(IDC_BTN_DELETE_VARIABLE, &CCharLibDevView::OnBnClickedBtnDeleteVariable)
	ON_BN_CLICKED(IDC_BTN_NEW_ELEMENT, &CCharLibDevView::OnBnClickedBtnNewElement)
	ON_BN_CLICKED(IDC_BTN_DELETE__ELEMENT, &CCharLibDevView::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_MOVEUP, &CCharLibDevView::OnBnClickedBtnMoveup)
	ON_BN_CLICKED(IDC_BTN_MOVE_DOWN, &CCharLibDevView::OnBnClickedBtnMoveDown)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCharLibDevView 构造/析构

CCharLibDevView::CCharLibDevView()
	: CFormView(CCharLibDevView::IDD)
{
	m_pCharacteristic = NULL;

	m_pCharInterface   = NULL;
	m_pCharacterArea   = NULL;
}

CCharLibDevView::~CCharLibDevView()
{
	m_pCharacteristic = NULL;
}

void CCharLibDevView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW_CHARTEMP, m_stcCharDraw);
	DDX_Control(pDX, IDC_GRID_CHARINTERFACE, m_gridCharInterface);
	DDX_Control(pDX, IDC_GRID_CHARELEMENT, m_gridCharElement);
	DDX_Control(pDX, IDC_GRID_MACROTEST, m_gridCharElementTestLine);
	DDX_Control(pDX, IDC_BTN_NEW_VARIABLE, m_btnNewVariable);
	DDX_Control(pDX, IDC_BTN_DELETE_VARIABLE, m_btnDeleteVariable);
	DDX_Control(pDX, IDC_BTN_NEW_ELEMENT, m_btnNewElement);
	DDX_Control(pDX, IDC_BTN_DELETE__ELEMENT, m_btnDeleteElement);
	DDX_Control(pDX, IDC_BTN_MOVEUP, m_btnMoveUp);
	DDX_Control(pDX, IDC_BTN_MOVE_DOWN, m_btnMoveDown);
}

BOOL CCharLibDevView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CCharLibDevView::EnableCharInterfaceButtons()
{
	CExBaseObject *pVariable = m_gridCharInterface.GetCurrCellData();

	m_btnDeleteVariable.EnableWindow(pVariable != NULL);
}

void CCharLibDevView::EnableCharElementButtons()
{

}

void CCharLibDevView::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_btnNewVariable.SetLanguageID(g_sLangID_NewVarious);
	m_btnDeleteVariable.SetLanguageID(g_sLangID_DeleteVarious);
	m_btnNewElement.SetLanguageID(g_sLangID_InportElement);
	m_btnDeleteElement.SetLanguageID(g_sLangID_DeleteElement);
	m_btnMoveUp.SetLanguageID(g_sLangID_UpMove);
	m_btnMoveDown.SetLanguageID(g_sLangID_DownMove);


	CXLangWndAdjMngr oWndAdjMngr;
	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_btnNewVariable);
	oWndAdjMngr.RegisterXCol(&m_btnDeleteVariable);

	oWndAdjMngr.RegisterCols();
	oWndAdjMngr.RegisterXCol(&m_btnNewElement);
	oWndAdjMngr.RegisterXCol(&m_btnDeleteElement);
	oWndAdjMngr.RegisterXCol(&m_btnMoveUp);
	oWndAdjMngr.RegisterXCol(&m_btnMoveDown);
	oWndAdjMngr.Adjust(this, TRUE);

}


void CCharLibDevView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();
	xlang_InitAndAdjust();

	m_gridCharInterface.InitGrid();
	m_gridCharElement.InitGrid();
	m_gridCharElementTestLine.InitGrid();

	m_gridCharInterface.AttachDataViewOptrInterface(this);
	m_gridCharElement.AttachDataViewOptrInterface(this);
	m_gridCharElementTestLine.AttachDataViewOptrInterface(this);

	m_gridCharInterface.SetFont(g_pGlobalFont12);
	m_gridCharElement.SetFont(g_pGlobalFont12);
	m_gridCharElementTestLine.SetFont(g_pGlobalFont12);

	InitCtrlsPos();

	CRect rcClient;
	GetClientRect(&rcClient);
	AdjustCtrlsPos(rcClient.Width(), rcClient.Height());
}

void CCharLibDevView::ShowCharacteristicTmplate()
{
	ASSERT (m_pCharacteristic != NULL);

	if (m_pCharacteristic == NULL)
	{
		return;
	}

	//变量
	m_pCharInterface = m_pCharacteristic->GetCharInterface();
	m_gridCharInterface.ShowDatas(m_pCharInterface);

	CCharacteristic *pCharacteristic = m_pCharacteristic;
	m_pCharacterArea = pCharacteristic->GetCharacterArea();
	m_gridCharElement.ShowDatas(m_pCharacterArea);
	m_gridCharElementTestLine.ShowDatas(NULL);

	//曲线图
	m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);

	EnableCharInterfaceButtons();
	EnableCharElementButtons();
}

void CCharLibDevView::InitCtrlsPos()
{
	m_gridCharInterface.GetWindowRect(&m_rcCtrls[Index_gridCharInterface]);
	m_btnNewVariable.GetWindowRect(&m_rcCtrls[Index_btnNewVariable]);
	m_btnDeleteVariable.GetWindowRect(&m_rcCtrls[Index_btnDeleteVariable]);

	m_gridCharElement.GetWindowRect(&m_rcCtrls[Index_gridCharElement]);
	m_btnNewElement.GetWindowRect(&m_rcCtrls[Index_btnNewElement]);
	m_btnDeleteElement.GetWindowRect(&m_rcCtrls[Index_btnDeleteElement]);
	m_btnMoveUp.GetWindowRect(&m_rcCtrls[Index_btnMoveUp]);
	m_btnMoveDown.GetWindowRect(&m_rcCtrls[Index_btnMoveDown]);

	m_gridCharElementTestLine.GetWindowRect(&m_rcCtrls[Index_gridTestLine]);

	m_stcCharDraw.GetWindowRect(&m_rcCtrls[Index_stcCharDraw]);

	for (long nIndex=0; nIndex<12; nIndex++)
	{
		ScreenToClient(&m_rcCtrls[nIndex]);
	}
}

void CCharLibDevView::AdjustCtrlsPos(long cx, long cy)
{
	if (!::IsWindow(m_btnNewElement.m_hWnd))
	{
		return;
	}

	long nYGap = cy - m_rcCtrls[Index_gridTestLine].bottom - 5;
	long nXGap = cx - m_rcCtrls[Index_stcCharDraw].right - 5;
	long nOffset = 0;
	CRect rcWnd[12];
	memcpy(rcWnd, m_rcCtrls, 12*sizeof(CRect));

	if (nYGap > 5)
	{
		nOffset = nYGap / 3;
		rcWnd[Index_gridCharInterface].bottom += nOffset;
		rcWnd[Index_btnNewVariable].OffsetRect(0, nOffset);
		rcWnd[Index_btnDeleteVariable].OffsetRect(0, nOffset);

		long nTemp = nOffset * 2;
		rcWnd[Index_gridCharElement].top += nOffset;
		rcWnd[Index_gridCharElement].bottom += nTemp;
		rcWnd[Index_btnNewElement].OffsetRect(0, nTemp);
		rcWnd[Index_btnDeleteElement].OffsetRect(0, nTemp);
		rcWnd[Index_btnMoveUp].OffsetRect(0, nTemp);
		rcWnd[Index_btnMoveDown].OffsetRect(0, nTemp);

		rcWnd[Index_gridTestLine].top += nOffset*2;
		rcWnd[Index_gridTestLine].bottom = cy - 5;

		rcWnd[Index_stcCharDraw].bottom = cy - 5;
	}

	if (nXGap > 5)
	{
		nOffset = nXGap / 2;
		rcWnd[Index_gridCharInterface].right += nOffset;
		rcWnd[Index_btnNewVariable].OffsetRect(nOffset, 0);
		rcWnd[Index_btnDeleteVariable].OffsetRect(nOffset, 0);

		rcWnd[Index_gridCharElement].right += nOffset;
		rcWnd[Index_btnNewElement].OffsetRect(nOffset, 0);
		rcWnd[Index_btnDeleteElement].OffsetRect(nOffset, 0);
		rcWnd[Index_btnMoveUp].OffsetRect(nOffset, 0);
		rcWnd[Index_btnMoveDown].OffsetRect(nOffset, 0);

		rcWnd[Index_gridTestLine].right = rcWnd[Index_gridCharElement].right;

		rcWnd[Index_stcCharDraw].left += nOffset;
		rcWnd[Index_stcCharDraw].right += nXGap;
	}

	m_gridCharInterface.MoveWindow(rcWnd[Index_gridCharInterface]);
	m_btnNewVariable.CButton::MoveWindow(rcWnd[Index_btnNewVariable]);
	m_btnDeleteVariable.CButton::MoveWindow(rcWnd[Index_btnDeleteVariable]);

	m_gridCharElement.MoveWindow(rcWnd[Index_gridCharElement]);
	m_btnNewElement.CButton::MoveWindow(rcWnd[Index_btnNewElement]);
	m_btnDeleteElement.CButton::MoveWindow(rcWnd[Index_btnDeleteElement]);
	m_btnMoveUp.CButton::MoveWindow(rcWnd[Index_btnMoveUp]);
	m_btnMoveDown.CButton::MoveWindow(rcWnd[Index_btnMoveDown]);

	m_gridCharElementTestLine.MoveWindow(rcWnd[Index_gridTestLine]);

	m_stcCharDraw.MoveWindow(rcWnd[Index_stcCharDraw]);
	Invalidate(FALSE);
}

void CCharLibDevView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCharLibDevView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCharLibDevView 诊断

#ifdef _DEBUG
void CCharLibDevView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCharLibDevView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCharLibDevDoc* CCharLibDevView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCharLibDevDoc)));
	return (CCharLibDevDoc*)m_pDocument;
}
#endif //_DEBUG


// CCharLibDevView 消息处理程序
void CCharLibDevView::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (pGridCtrl == &m_gridCharInterface)
	{
		EnableCharInterfaceButtons();
	}
	else if (pGridCtrl == &m_gridCharElement)
	{
		EnableCharElementButtons();
		CCharElement *pCharElement = (CCharElement*)m_gridCharElement.GetCurrCellData();
		m_stcCharDraw.SetActiveElement(pCharElement);

		ShowCharElementTestLines();
	}
	else if (pGridCtrl == &m_gridCharElementTestLine)
	{
	}
}


void CCharLibDevView::ShowCharElementTestLines()
{
	CCharElement *pCharElement = (CCharElement*)m_gridCharElement.GetCurrCellData();
	m_gridCharElementTestLine.ShowDatas(pCharElement);
}

BOOL CCharLibDevView::OnEditCellLBDblClk_CharElement(int nRow, int nCol, UINT nChar)
{
	CCharElement *pCharElement = (CCharElement*)m_gridCharElement.GetDataRow(nRow, nCol);
	ASSERT (pCharElement != NULL);

	CDlgCharElement dlg;
	dlg.m_pCharElementEdit = pCharElement;

	if (dlg.DoModal() == IDCANCEL)
	{
		return TRUE;
	}

	if (dlg.m_pCharElementSrcSel->m_strID == pCharElement->m_strID)
	{
		dlg.m_pCharElementSrcSel->Copy(pCharElement);
		m_gridCharElement.UpdateData(pCharElement);
	}
	else
	{

	}

	m_stcCharDraw.SetActiveElement(NULL, FALSE);
	m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);
	m_stcCharDraw.SetActiveElement(pCharElement);

	return TRUE;
}

BOOL CCharLibDevView::OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	if (pGridCtrl == &m_gridCharElement)
	{
		return OnEditCellLBDblClk_CharElement(nRow, nCol, nChar);
	}

	return FALSE;
}

void CCharLibDevView::OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (pGridCtrl == &m_gridCharInterface)
	{
		m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);
	}
	else if (pGridCtrl == &m_gridCharElement)
	{
		CCharElement *pCharElement = (CCharElement*)m_gridCharElement.GetCurrCellData();
		m_stcCharDraw.SetActiveElement(NULL, FALSE);
		m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);
		m_stcCharDraw.SetActiveElement(pCharElement);
		m_gridCharElementTestLine.ShowDatas(pCharElement);
	}
}

void CCharLibDevView::OnBnClickedBtnNewVariable()
{
	if (m_pCharInterface == NULL)
	{
		return;
	}

	CCharInterfaceVariable *pNew = new CCharInterfaceVariable();
	m_pCharInterface->AddNewChild(pNew, TRUE);
	m_gridCharInterface.InsertData(pNew);
	char_dev_SetModifiedFlag(m_pCharInterface, TRUE);
}

void CCharLibDevView::OnBnClickedBtnDeleteVariable()
{
	CExBaseObject *pVariable = m_gridCharInterface.GetCurrCellData();

	if (pVariable == NULL)
	{
		return;
	}

	CString strMsg;
	strMsg.Format(g_sLangTxt_SureDelElement/*_T("是否删除变量“%s”？")*/, pVariable->m_strID);
	UINT nRet = MessageBox(strMsg,g_sLangTxt_Message1 /*_T("提示")*/, MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		return;
	}

	long nRow = m_gridCharInterface.GetDataRow(pVariable);
	m_gridCharInterface.DeleteRow(nRow);
	m_pCharInterface->Delete(pVariable);
	char_dev_SetModifiedFlag(m_pCharInterface, TRUE);
	EnableCharInterfaceButtons();
}

void CCharLibDevView::OnBnClickedBtnNewElement()
{
	CCharacterArea *pArea = m_pCharacteristic->GetCharacterArea();
	CDlgCharElement dlg;
	dlg.m_pPrevCharElement = (CCharElement*)pArea->GetTail();

	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	CCharElement *pNew = (CCharElement*)dlg.m_pCharElementSrcSel->Clone();
	pArea->AddNewChild(pNew);
	m_gridCharElement.InsertData(pNew);

	//曲线图
	m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);
}

void CCharLibDevView::OnBnClickedBtnDelete()
{
	CCharElement *pSel = (CCharElement*)m_gridCharElement.GetCurrCellData();

	if (pSel == NULL)
	{
		return;
	}

	CString strMsg;
	strMsg.Format(g_sLangTxt_SureDelVarious/*_T("你确实要删除元素“%s”吗？")*/, pSel->m_strName);
	
	if (MessageBox(strMsg, g_sLangTxt_Message1/*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) != IDYES)
	{
		return;
	}

	long nRow = m_gridCharElement.GetDataRow(pSel);
	m_gridCharElement.DeleteRow(nRow);
	m_pCharacterArea->Delete(pSel);
	m_gridCharElementTestLine.ShowDatas(NULL);
	char_dev_SetModifiedFlag(m_pCharacterArea, TRUE);
	m_gridCharElement.Invalidate(FALSE);

	//曲线图
	m_stcCharDraw.InitCharacterDrawView(m_pCharacteristic);
}

void CCharLibDevView::OnBnClickedBtnMoveup()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCharLibDevView::OnBnClickedBtnMoveDown()
{
// 	CString strFile;
// 	strFile = _P_GetBinPath();
// 	strFile += _T("CharGraph.bmp");
// 	
// 	char_view_WriteBitmapFile(m_pCharacteristic, 800, 800, strFile);
}


void CCharLibDevView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	AdjustCtrlsPos(cx, cy);
}

void CCharLibDevView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
{
	if (lHint == 0)
	{
		return;
	}

	CExBaseObject *p = (CExBaseObject *)lHint;
	ASSERT (p->GetClassID() == CHARCLASSID_CCHARACTERISTIC);

	m_pCharacteristic = (CCharacteristic*)lHint;
	ShowCharacteristicTmplate();
}
