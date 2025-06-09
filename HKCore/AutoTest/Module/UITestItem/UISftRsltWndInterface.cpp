#include "stdafx.h"
#include "UISftRsltWndInterface.h"

#include "UISftRsltWndEdit.h"
#include "UISftRsltWndDateTimeCtrl.h"
#include "UISftRsltWndComboBox.h"
#include "UISftRsltWndPassword.h"
#include "UISftRsltWndMultiSel.h"
#include "UISftRsltWndIpEdit.h"
#include "UISftRsltWndMacEdit.h"
#include "UISftRsltWndDsGrid.h"

#include <locale.h>
#include "../GuideBook/GbDataTypeMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const long CUISftRsltWndInterface::g_nResultTitleWidth = 150;
const long CUISftRsltWndInterface::g_nResultEditWidth  = 150;
const long CUISftRsltWndInterface::g_nResultUnitWidth  = 30;
const long CUISftRsltWndInterface::g_nResultWndGap = 5;
const long CUISftRsltWndInterface::g_nResultColGapWidth = 8;
const long CUISftRsltWndInterface::g_nResultWndMinHeight  = 25;

const long CUISftRsltWndInterface::g_nResultWndHeightEdit = 20;
const long CUISftRsltWndInterface::g_nResultWndHeightComboBox = 25;
const long CUISftRsltWndInterface::g_nResultWndHeightMultiComboBox = 60;
const long CUISftRsltWndInterface::g_nResultDlgMaxHeight = 400;

// const char* CUISftRsltWndInterface::g_pszDataType_combobox = "combobox";
// const char* CUISftRsltWndInterface::g_pszDataType_multicombobox = "multicombobox";
// const char* CUISftRsltWndInterface::g_pszDataType_datetime = "datetime";
// const char* CUISftRsltWndInterface::g_pszDataType_password = "password";
// const char* CUISftRsltWndInterface::g_pszDataType_number = "number";
// const char* CUISftRsltWndInterface::g_pszDataType_string = "string";

long UI_GetOneResultWndMaxWidth()
{
	long nWidth = CUISftRsltWndInterface::g_nResultTitleWidth 
		+ CUISftRsltWndInterface::g_nResultEditWidth
		+ CUISftRsltWndInterface::g_nResultUnitWidth;

	return nWidth;
}

long UI_GetSftWndMaxWidth()
{
	long nWidth = CUISftRsltWndInterface::g_nResultTitleWidth 
		+ CUISftRsltWndInterface::g_nResultEditWidth
		+ CUISftRsltWndInterface::g_nResultUnitWidth;

	nWidth *= 2;
	nWidth += CUISftRsltWndInterface::g_nResultWndGap * 3;

	return nWidth;
}

long UI_GetSftInforWndMaxWidth()
{
	long nWidth = CUISftRsltWndInterface::g_nResultTitleWidth 
		+ CUISftRsltWndInterface::g_nResultEditWidth
		+ CUISftRsltWndInterface::g_nResultUnitWidth;

	nWidth *= 2;
	nWidth += CUISftRsltWndInterface::g_nResultWndGap ;

	return nWidth;
}

CUISftRsltWndInterface::CUISftRsltWndInterface()
{
	m_oRsltData = NULL;
	m_rectRsltWnd = CRect(0,0,0,0);
	m_pTitle = NULL;
	m_pRsltEditWnd = NULL;
	m_nHeight = 20;
	m_nRsltEditWndHeight = 20;
	m_nRsltEditWndType = RSLTEDITWNDTYPE_None;
	m_pParentWnd = NULL;
	m_pUnit = NULL;

	m_nTitleWidth = g_nResultTitleWidth;
	m_nHeight     = g_nResultWndMinHeight;
	m_nWidth      = -1;
	m_nLeft       = 5;
	m_nTop        = 5;
}

CUISftRsltWndInterface::~CUISftRsltWndInterface()
{
	EndIt();
}

void CUISftRsltWndInterface::EndIt()
{
	if(m_pTitle != NULL)
	{
		delete m_pTitle;
		m_pTitle = NULL;
	}
	if(m_pRsltEditWnd != NULL)
	{
		delete m_pRsltEditWnd;
		m_pRsltEditWnd = NULL;
	}
	if(m_pUnit != NULL)
	{
		delete m_pUnit;
		m_pUnit = NULL;
	}
}


void CUISftRsltWndInterface::CreateRsltEditWnd(CShortData * oRsltData,CWnd* pParentWnd,long &nID,long nLeft/* =0 */,long nTop/* =0 */,long nWidth/* =400 */)
{
	if(oRsltData == NULL)
		return;

	m_oRsltData = oRsltData;
	CString strName = oRsltData->m_strName;
	CString strDataType = oRsltData->m_strDataTypeID;
	CString strFormat = oRsltData->m_strFormat;

	CreateRsltEditWnd(strDataType,strFormat,pParentWnd,nID);
}

void CUISftRsltWndInterface::CreateRsltEditWnd(const CString& strDataType,const CString& strDomain,CWnd* pParentWnd,long &nID)
{
	m_pParentWnd = pParentWnd;

	long nGap = m_rectRsltWnd.Width()/2;
	CRect rcWnd = m_rectRsltWnd;
	rcWnd.right = rcWnd.left + nGap;

	if(strDataType == g_strGbDataTypeCombobox)
	{
		m_nHeight = g_nResultWndHeightComboBox;
	}
	else if (strDataType == g_strGbDataTypeMulticombobox)
	{
		m_nHeight = g_nResultWndHeightMultiComboBox;
	}
	else if(strDataType == g_strGbDataTypePassword)
	{
		m_nHeight = g_nResultWndHeightComboBox;
	}
	else if(strDataType == g_strGbDataTypeDvmDataset)
	{
		m_nHeight = 200;
	}
	else
	{
		m_nHeight = g_nResultWndHeightEdit;
	}

	m_nRsltEditWndHeight = m_nHeight;
	m_rectTitle.left = m_nLeft;
	m_rectTitle.top = m_nTop;
	m_rectTitle.right = m_rectTitle.left + g_nResultTitleWidth;
	m_rectTitle.bottom = m_rectTitle.top + m_nHeight;

	m_rectEdit.left = m_rectTitle.right + g_nResultWndGap;
	m_rectEdit.top = m_nTop;
	m_rectEdit.right = m_rectEdit.left + g_nResultEditWidth;
	m_rectEdit.bottom = m_rectEdit.top + m_nHeight;

	if(strDataType == g_strGbDataTypeDvmDataset)
	{
		m_rectEdit.right += g_nResultEditWidth;
	}

	m_rectUnit.left = m_rectEdit.right + g_nResultWndGap;
	m_rectUnit.top = m_nTop;
	m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
	m_rectUnit.bottom = m_rectUnit.top + m_nHeight;

	m_pTitle = new CUISftRsltWndStatic();
	m_pUnit = new CUISftRsltWndStatic();
// 	m_pTitle->Create(m_oRsltData->m_strName,WS_CHILD/*|WS_VISIBLE*/|SS_LEFT
// 		,m_rectTitle,pParentWnd,nID++);
// 	m_pUnit->Create(m_oRsltData->m_strUnit,WS_CHILD/*|WS_VISIBLE*/|SS_LEFT
// 		,m_rectUnit,pParentWnd,nID++);
	m_pTitle->CreateUIStatic(m_oRsltData->m_strName,m_rectTitle,pParentWnd,nID++);
	m_pUnit->CreateUIStatic(m_oRsltData->m_strUnit,m_rectUnit,pParentWnd,nID++);

	CString strFormat = m_oRsltData->m_strFormat;

	if(strDataType == g_strGbDataTypeCombobox)
	{
		m_nRsltEditWndType = RSLTEDITWNDTYPE_ComboBox;
		m_rectEdit.bottom += 200;
		
		CUISftRsltWndComboBox *pBox = new CUISftRsltWndComboBox(m_oRsltData);
		pBox->m_pResultWndInterface = this;
		pBox->Create(WS_CHILD/*|WS_VISIBLE*/|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL|WS_VSCROLL|WS_TABSTOP , m_rectEdit, pParentWnd, nID++);
		m_pRsltEditWnd = pBox;
	}
	else if(strDataType == g_strGbDataTypeMulticombobox)
	{	
		//MultiComboBox
		m_nRsltEditWndType = RSLTEDITWNDTYPE_MultiSel;
		CUISftRsltWndMultiSel* pBox = new CUISftRsltWndMultiSel(strFormat);
		pBox->m_pResultWndInterface = this;
		DWORD dwStyle = WS_BORDER | WS_CHILD | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS /*| WS_VISIBLE */| WS_VSCROLL;
		pBox->Create(dwStyle,m_rectEdit,pParentWnd,nID++);
		m_pRsltEditWnd = pBox;
		CString strData = m_oRsltData->m_strValue;
		pBox->InitMultiSel(strFormat,strData);
	}
	else if(strDataType == g_strGbDataTypeDatetime)
	{
		m_nRsltEditWndType = RSLTEDITWNDTYPE_DateTimeCtrl;
		CUISftRsltWndDateTimeCtrl* pTimeCtrl = new CUISftRsltWndDateTimeCtrl(strFormat);
		pTimeCtrl->m_pResultWndInterface = this;
		pTimeCtrl->Create(WS_CHILD | WS_TABSTOP,m_rectEdit,pParentWnd,nID++);
		m_pRsltEditWnd = pTimeCtrl;
		CString strValue = m_oRsltData->m_strValue;
		if(strValue == _T(""))
		{
			//设置初值
			SYSTEMTIME sysTime;   // Win32 time information
			GetLocalTime(&sysTime);
			COleDateTime tm(sysTime);
			tm.GetCurrentTime();
#ifdef _UNICODE
			_wsetlocale(LC_ALL,_T("chs"));
#else
			setlocale(LC_ALL,_T("chs"));
#endif
			CString strDateTime = tm.Format(strFormat);
			m_oRsltData->PutValue(strDateTime);
#ifdef _UNICODE
			_wsetlocale(LC_ALL,_T("eng"));
#else
			setlocale(LC_ALL,_T("eng"));
#endif
		}
		pTimeCtrl->InitResultDateTimeCtrl(strFormat,strValue);
	}
	else if(strDataType == g_strGbDataTypePassword)
	{
		m_nRsltEditWndType = RSLTEDITWNDTYPE_Password;
		CUISftRsltWndPassword *pPswWnd = new CUISftRsltWndPassword();
		pPswWnd->m_pResultWndInterface = this;
		DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE;

		pPswWnd->Create(_T(""), WS_CHILD/*|WS_VISIBLE*/|SS_LEFT | WS_BORDER |WS_TABSTOP
			, /*rcWnd*/m_rectTitle, pParentWnd, nID++);

		m_pRsltEditWnd = pPswWnd;
		CString strData = m_oRsltData->m_strValue;
		//TrimValueString(strData);
		pPswWnd->InitPassWord(_T("")/*m_oRsltData.GetMessage()*/, strData, nID);
	}
	else if(strDataType == g_strGbDataTypeMacAddr)
	{
		m_nRsltEditWndType = RSLTEDITWNDTYPE_MacEdit;
		CUISftRsltWndMacEdit *pMacWnd = new CUISftRsltWndMacEdit();

		pMacWnd->Create(WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT|ES_AUTOHSCROLL |WS_TABSTOP
			,m_rectEdit,pParentWnd,nID++);
		pMacWnd->EnableWindow(TRUE);
		pMacWnd->Init();

		m_pRsltEditWnd = pMacWnd;

		if (m_oRsltData->m_strValue.GetLength() == 17 || m_oRsltData->m_strValue.GetLength()== 12)
		{
			pMacWnd->SetWindowText(m_oRsltData->m_strValue);
		}
		else
		{
			pMacWnd->SetWindowText(_T("FF-FF-FF-FF-FF-FF"));
		}

		pMacWnd->m_pResultWndInterface = this;
	}
	else if(strDataType == g_strGbDataTypeIPAddr)
	{
		m_nRsltEditWndType = RSLTEDITWNDTYPE_IPEdit;
		CUISftRsltWndIpEdit *pIPWnd = new CUISftRsltWndIpEdit();
		pIPWnd->m_pResultWndInterface = this;

		pIPWnd->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP
			,m_rectEdit,pParentWnd,nID++);
		pIPWnd->EnableWindow(TRUE);

		m_pRsltEditWnd = pIPWnd;
		CString strData = m_oRsltData->m_strValue;
		pIPWnd->SetWindowText(strData);
	}
	else if(strDataType == g_strGbDataTypeDvmDataset)
	{
		m_rectEdit.bottom += 200;
		m_nRsltEditWndType = RSLTEDITWNDTYPE_DvmDsDataset;
		CUISftRsltWndDsGrid *pDsGrid = new CUISftRsltWndDsGrid();
		pDsGrid->m_pResultWndInterface = this;
		pDsGrid->CreateGsGrid(m_oRsltData, nID++, pParentWnd);
		pDsGrid->EnableWindow(TRUE);
		m_pRsltEditWnd = pDsGrid;
	}
	else
	{
		//创建Edit控件，可能的类型为number 或string
		m_nRsltEditWndType = RSLTEDITWNDTYPE_Edit;
		CUISftRsltWndEdit* pEdit = new CUISftRsltWndEdit(strDataType);
		pEdit->m_pResultWndInterface = this;
		m_pRsltEditWnd = pEdit;
		pEdit->CreateEx(WS_EX_CLIENTEDGE,_T("Edit"),_T(""),WS_CHILD/*|WS_VISIBLE*/|ES_LEFT|ES_AUTOHSCROLL |WS_TABSTOP
			,m_rectEdit,pParentWnd,nID++);
		pEdit->EnableWindow(TRUE);
		CString strValue = m_oRsltData->m_strValue;
		
		pEdit->SetWindowText(strValue);
	}
}

void CUISftRsltWndInterface::OnResultDataChanged(const CString &strData)
{
	m_oRsltData->PutValue(strData);
	
	if(m_pParentWnd != NULL)
	{
		m_pParentWnd->PostMessage(WM_USER+1000, 0, 0);
	}
}

void CUISftRsltWndInterface::CalResultWndSize()
{
	long nTitleHeight = 0, nTitleWidth = 0;
	long nHeightGap = 0;
	m_pTitle->CalWndSize(nTitleWidth, nTitleHeight);	

	/*if (g_nResultTitleWidth < m_nTitleWidth && m_nTitleWidth <= g_nResultTitleWidth*2)
	{
		nTitleHeight += nTitleHeight * 2;
		m_nTitleWidth = g_nResultTitleWidth;
	}
	else */if ( nTitleWidth > g_nResultTitleWidth*2)
	{
		long nMax = UI_GetOneResultWndMaxWidth() + g_nResultWndGap + g_nResultTitleWidth;
		m_nTitleWidth = nMax;//min(nTitleWidth, nMax);
		long nRows = nTitleWidth / nMax + 2;

// 		if (nRows > 1)
// 		{
// 			nRows++;
// 		}

		nTitleHeight *= nRows;
	}
	else
	{
		m_nTitleWidth = nTitleWidth;
	}

	if (m_oRsltData->m_strDataTypeID == g_strGbDataTypeDvmDataset)
	{
		m_nWidth = UI_GetSftInforWndMaxWidth();
	}
	else
	{
		m_nWidth = m_nTitleWidth + g_nResultEditWidth + g_nResultUnitWidth;
	}

	m_nHeight = max(m_nHeight, nTitleHeight);
}

long CUISftRsltWndInterface::AdjustResultWndPosition(long xOffset,long yOffset,long nMaxTitleWidth)
{
	m_rectTitle.OffsetRect(xOffset, yOffset);
	m_rectEdit.OffsetRect(xOffset, yOffset);
	m_rectUnit.OffsetRect(xOffset, yOffset);
	m_rectTitle.left = m_rectTitle.right - nMaxTitleWidth;

	long nTitleHeight = m_rectTitle.Height();
	long nHeightGap = m_rectTitle.top - m_rectEdit.top;
	m_rectEdit.OffsetRect(0, nHeightGap);
	m_rectUnit.OffsetRect(0, nHeightGap);
	if (nTitleHeight > m_nRsltEditWndHeight)
	{
		nHeightGap = (nTitleHeight - m_nRsltEditWndHeight) / 2;
		m_rectEdit.OffsetRect(0, nHeightGap);
		m_rectUnit.OffsetRect(0, nHeightGap);
	}

	m_rectTitle.bottom = m_rectTitle.top + nTitleHeight;

	m_pTitle->MoveWindow(m_rectTitle);

	if (m_nRsltEditWndType == RSLTEDITWNDTYPE_Password)
	{
		m_pRsltEditWnd->MoveWindow(m_rectEdit);
		((CUISftRsltWndPassword*)m_pRsltEditWnd)->AdjustWnd();
	}
	else
	{
		m_pRsltEditWnd->MoveWindow(m_rectEdit);
	}

	m_pUnit->MoveWindow(m_rectUnit);
//	m_pTitle->BringWindowToTop();
// 	m_pTitle->ShowWindow(SW_HIDE);
// 	m_pTitle->ShowWindow(SW_SHOW);

	ShowWindow();

	return m_nHeight;
}

void CUISftRsltWndInterface::AdjustLeft(long xPos, long nWidth)
{
	if (m_oRsltData->m_strDataTypeID == g_strGbDataTypeDvmDataset)
	{
		m_rectTitle.right = m_nTitleWidth + m_rectTitle.left;
		m_rectEdit.left = m_rectTitle.right + g_nResultWndGap;
		m_rectEdit.right = UI_GetSftInforWndMaxWidth() - g_nResultUnitWidth - g_nResultWndGap;
		m_rectUnit.left = m_rectEdit.right + g_nResultWndGap;
		m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
		return;
	}

	m_nLeft = xPos;
	m_nWidth = nWidth;

	m_rectTitle.left = xPos;
	m_rectTitle.right = xPos + nWidth - g_nResultEditWidth - g_nResultUnitWidth;

	m_rectEdit.left = m_rectTitle.right;
	m_rectEdit.right = m_rectEdit.left + g_nResultEditWidth;

	m_rectUnit.left = m_rectEdit.right;
	m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
}

void CUISftRsltWndInterface::AdjustRight(long xPosRight, long nWidth)
{
	if (m_oRsltData->m_strDataTypeID == g_strGbDataTypeDvmDataset)
	{
		m_rectTitle.right = m_nTitleWidth + m_rectTitle.left;
		m_rectEdit.left = m_rectTitle.right + g_nResultWndGap;
		m_rectEdit.right = UI_GetSftInforWndMaxWidth() - g_nResultUnitWidth - g_nResultWndGap;
		m_rectUnit.left = m_rectEdit.right + g_nResultWndGap;
		m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
		return;
	}

	//long nRight = UI_GetSftWndMaxWidth();
	m_nWidth = nWidth;
	m_nLeft = xPosRight - nWidth;
	
	m_rectTitle.left = m_nLeft;
	m_rectTitle.right = m_nLeft + nWidth - g_nResultEditWidth - g_nResultUnitWidth;

	m_rectEdit.left = m_rectTitle.right;
	m_rectEdit.right = m_rectEdit.left + g_nResultEditWidth;

	m_rectUnit.left = m_rectEdit.right;
	m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
}

void CUISftRsltWndInterface::AdjustLeftRight(long xPosRight, long nWidth)
{
	if (m_oRsltData->m_strDataTypeID == g_strGbDataTypeDvmDataset)
	{
		AdjustRight(xPosRight, nWidth);
		return;
	}

	m_nWidth = xPosRight - g_nResultWndGap;
	m_nLeft = g_nResultWndGap;
	
	m_rectTitle.left = m_nLeft;
	m_rectTitle.right = m_nLeft + (xPosRight - g_nResultEditWidth - g_nResultUnitWidth - g_nResultWndGap);

	m_rectEdit.left = m_rectTitle.right;
	m_rectEdit.right = m_rectEdit.left + g_nResultEditWidth;

	m_rectUnit.left = m_rectEdit.right;
	m_rectUnit.right = m_rectUnit.left + g_nResultUnitWidth;
}

void CUISftRsltWndInterface::AdjustY(long &yPos, long nHeight)
{
	m_nHeight = nHeight;
	long yCenter = yPos + m_nHeight / 2;

	//2021-4-3  lijunqing
// 	m_rectTitle.top = yCenter - m_pTitle->m_nHeight / 2;
// 	m_rectTitle.bottom = m_rectTitle.top + m_pTitle->m_nHeight;
	m_rectTitle.top = yCenter - m_nHeight / 2;
	m_rectTitle.bottom = m_rectTitle.top + m_nHeight;

	long nTopGap = m_nRsltEditWndHeight / 2;
	long nBottomGap = m_nRsltEditWndHeight - nTopGap;

	m_rectEdit.top = yCenter - nTopGap;
	m_rectEdit.bottom = yCenter + nBottomGap;

	if (m_nRsltEditWndType == RSLTEDITWNDTYPE_ComboBox)
	{
		m_rectEdit.bottom += 200;
	}

	m_rectUnit.top = yCenter - m_pUnit->m_nHeight / 2;
	m_rectUnit.bottom = m_rectUnit.top +  m_pUnit->m_nHeight;

	m_pTitle->MoveWindow(m_rectTitle, TRUE);
	m_pTitle->ShowWindow(SW_SHOW);

	m_pRsltEditWnd->MoveWindow(m_rectEdit, TRUE);
	m_pRsltEditWnd->ShowWindow(SW_SHOW);

	m_pUnit->MoveWindow(m_rectUnit, TRUE);
	m_pUnit->ShowWindow(SW_SHOW);

	//yPos += m_nHeight;
}

BOOL CUISftRsltWndInterface::IsSingle()
{
	if (m_oRsltData->m_strDataTypeID == g_strGbDataTypeDvmDataset)
	{
		return TRUE;
	}

	if (m_nTitleWidth > g_nResultTitleWidth * 2)
	{
		return TRUE;
	}

	return FALSE;
}

void CUISftRsltWndInterface::SetFont(CFont* pFont)
{
	if (m_pTitle != NULL)
	{
		m_pTitle->SetFont(pFont);
		m_pTitle->m_pFont = pFont;
	}
	if (m_pUnit != NULL)
	{
		m_pUnit->SetFont(pFont);
		m_pUnit->m_pFont = pFont;
	}

	if (m_pRsltEditWnd)
	{
		m_pRsltEditWnd->SetFont(pFont);
	}
}

void CUISftRsltWndInterface::ShowWindow()
{
	m_pTitle->ShowWindow(SW_SHOW);
	m_pRsltEditWnd->ShowWindow(SW_SHOW);
	m_pUnit->ShowWindow(SW_SHOW);
}
