// CommCmdParaEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommCmdParaEditDlg.h"

#include "..\..\..\..\Module\XLanguage\XLanguageResource.h"
#include "..\..\..\..\Module\XLanguage\XLangWndAdjust.h"
#include "..\..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\TestControl/TestControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////

// CCommCmdEditGrid

CCommCmdEditGrid::CCommCmdEditGrid()
{
	
}

CCommCmdEditGrid::~CCommCmdEditGrid()
{
}

BOOL CCommCmdEditGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData/*=0*/)
{
	if (nCol == 3)
	{
		return EndEditCell_Value(nRow, dwItemData);
	}

	return TRUE;
}

BOOL CCommCmdEditGrid::EndEditCell_Value(int nRow, DWORD dwItemData/*=0*/)
{
	CGridCell *pCell = GetCell(nRow, 3);
	CExBaseObject* pObj = (CExBaseObject*)pCell->lParam;

	ASSERT(pObj != NULL);
	if (pObj != NULL)
	{
		if (pObj->GetClassID() == DTMCLASSID_CVALUE)
		{
			CValue *pValue = (CValue *)pObj;
			CCommCmd *pCommCmd = (CCommCmd*)pValue->GetParent()->GetParent();
			pValue->m_strValue = pCell->szText;

#ifdef GUIDEBOOK_DEV_MODE
#else
			CTestControl *pTestControl = (CTestControl*)pValue->GetAncestor(GBCLASSID_TESTCONTROL);
			pTestControl->EditItemPara(pCommCmd, pValue);
#endif

			if (!IsStringNumber(pValue->m_strValue))
			{
				ASSERT (pCommCmd->GetClassID() == GBCLASSID_COMMCMD);
				CString strValue = pCommCmd->CalValue(pValue);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s ==>> %s"), pValue->m_strValue, strValue);
			}

			return TRUE;
		}
	}

	return FALSE;
}

// CCommCmdEditGrid 消息处理程序

void CCommCmdEditGrid::ShowColumnTitle()
{	
	SetRowCount(1);
	SetFixedRowCount(1);

	int iNum = 4;
	//char cTempStr[4][24] = {"编号","名称","标识","数值"};
	CString cTempStr[5]={
		g_sLangTxt_Index/*"编号"*/
		,g_sLangTxt_Name/*"名称"*/
		,g_sLangTxt_Id/*"ID"*/
		,g_sLangTxt_Value/*"数值"*/
	};

	int  iColType[4] = {GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT};
	int iWidth[4] = {50,250,160, 80};
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,iColType[iCol]);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	SetRowHeight(0, 20);
}

void CCommCmdEditGrid::InitGrid(CCommCmd* pCommCmd)
{
	m_pCommCmd = pCommCmd;
	SetListMode(TRUE);
	SetColumnCount(4);
	ShowColumnTitle();
	InitData();
}

void CCommCmdEditGrid::InitData()
{
	CValue *pValue = NULL;
	CValues *pValues = m_pCommCmd->GetCmd()->GetValues();
	long nCount = pValues->GetCount();
	CCmd *pCmd = m_pCommCmd->GetCmd();

	m_pCpuDataList = m_pCommCmd->GetDataset(pCmd->m_nUseDeviceEx);
	SetRowCount(nCount+1);
	int nRow = 1;
	POS pos = pValues->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		InsertValuetoItem(pValue, nRow);
		nRow++;
	}
}

void CCommCmdEditGrid::InsertValuetoItem(CExBaseObject *pData,int &nRowIndex)
{
	UINT nClassID = pData->GetClassID();
	ASSERT(nClassID == DTMCLASSID_CVALUE);

	if(nClassID != DTMCLASSID_CVALUE)
	{
		return;
	}

	CValue* pValue = (CValue*)pData;

	GV_ITEM Item;
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT  | GVIF_DATATYPE |GVIF_VALUE|GVIS_FOCUSED;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;
	Item.dwValue = 0;
	Item.row = nRowIndex;

	Item.col = 0;
	Item.lParam = (LPARAM)pData;
	Item.nDataType = GVET_NOEDIT;
	Item.szText.Format(_T("%d"),nRowIndex);
	SetItem(&Item);

	Item.col = 1;
	Item.szText = pValue->m_strID;

	if (m_pCpuDataList != NULL)
	{
		CExBaseObject *pFind = m_pCpuDataList->FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			Item.szText = pFind->m_strName;
		}
		else
		{
			CDataObj *pDataObj = m_pCommCmd->FindDataObj(pValue->m_strID, m_pCommCmd->GetCpusIndex());

			if (pDataObj != NULL)
			{
				Item.szText = pDataObj->m_strName;
			}
			else
			{
				CString strText;
				strText = m_pCommCmd->FindDataObjValue_Name(pValue->m_strID, m_pCommCmd->GetCpusIndex());

				if (strText.GetLength() > 0)
				{
					Item.szText = strText;
				}
				else
				{
				Item.crFgClr = RGB(255, 0, 0);
			}
		}
	}
	}

	SetItem(&Item);

	Item.col = 2;
	Item.szText = pValue->m_strID;
	SetItem(&Item);

	Item.col = 3;
	Item.nDataType = GVET_EDITBOX;

	Item.szText = pValue->m_strValue;
	SetItem(&Item);

	SetRowHeight(nRowIndex, 20);
}



// CCommCmdParaEditDlg 对话框

CCommCmdParaEditDlg::CCommCmdParaEditDlg(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent, TRUE)
{
	m_pCommCmd = NULL;
}

CCommCmdParaEditDlg::~CCommCmdParaEditDlg()
{
}

void CCommCmdParaEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}

void CCommCmdParaEditDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_btnCommcmdOk.SetLanguageID(g_sLangID_OK);
	m_btnCommcmdCancel.SetLanguageID(g_sLangID_Cancel);


	CXLangWndAdjMngr oWndAdjMngr;         
	oWndAdjMngr.RegisterCols();  
	oWndAdjMngr.RegisterXCol(&m_btnCommcmdOk);  
	oWndAdjMngr.RegisterXCol(&m_btnCommcmdCancel); 


	oWndAdjMngr.Adjust(this, TRUE);
	xlang_InitByLgugStr(g_sLangID_TestItemParEdit, this);
}


BEGIN_MESSAGE_MAP(CCommCmdParaEditDlg, CDynDialogEx)
END_MESSAGE_MAP()


// CCommCmdParaEditDlg 消息处理程序

BOOL CCommCmdParaEditDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateButton(m_btnCommcmdOk, g_sLangTxt_OK, CRect(177, 490, 267, 515), IDOK, this);
	CreateButton(m_btnCommcmdCancel, g_sLangTxt_Cancel, CRect(277, 490, 367, 515), IDCANCEL, this);

	CreateEdit(m_edtCmdInfor, CRect(5, 5, 570, 27), 6002, this);
	CCmd *pCmd = m_pCommCmd->GetCmd();
	CString strInfor;
	strInfor.Format(_T("%s(%s)"), m_pCommCmd->m_strCommCmdID, pCmd->m_strDatasetPath);
	m_edtCmdInfor.SetWindowText(strInfor);
	m_edtCmdInfor.SetReadOnly(TRUE);

	m_gridPara.Create(CRect(5, 30, 570, 485),this,6001);
	m_gridPara.InitGrid(m_pCommCmd);

	m_btnCommcmdOk.SetFont(g_pGlobalFont11);
	m_btnCommcmdCancel.SetFont(g_pGlobalFont11);
	m_gridPara.SetFont(g_pGlobalFont11);
	m_edtCmdInfor.SetFont(g_pGlobalFont11);

	CRect rcDlg;
	GetWindowRect(rcDlg);
	rcDlg.right = rcDlg.left + 580;
	rcDlg.bottom = rcDlg.top + 550;
	MoveWindow(rcDlg);
	CenterWindow();
	
    xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
