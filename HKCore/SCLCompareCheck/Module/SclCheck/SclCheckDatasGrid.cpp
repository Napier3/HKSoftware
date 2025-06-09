#include "StdAfx.h"
#include "SclCheckDatasGrid.h"

#include "ResultsRec.h"


//////////////////////////////////////////////////////////////////////////
// CSclCheckCtrlGrid

const int g_nSclCheckCols = 8;
CString g_astrSclCheckTitle[g_nSclCheckCols] = {_T("序号"),_T("类型"),_T("描述信息"),_T("异常定位"),_T("提示数"),_T("告警数"),_T("错误数"),_T("严重错误")};
const int g_iSclCheckWidth[g_nSclCheckCols]={40 ,50 ,400 ,100 ,40 ,40 ,40 ,40 };

const int g_nSclCheckColsEmpty = 1;
const CString g_astrSclCheckTitleEmpty[g_nSclCheckColsEmpty] = {_T("无异常")};
const int g_iSclCheckWidthEmpty[g_nSclCheckColsEmpty]={60};

CSclCheckCtrlGrid::CSclCheckCtrlGrid()
{
	m_nAdjustBeginCol = 2;
	m_nOldSclIecCfgClassID = 0;
	m_nAdjustBeginCol = 1;
}

CSclCheckCtrlGrid::~CSclCheckCtrlGrid()
{
}

void CSclCheckCtrlGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(8);
	SetFixedRowCount(1);
	SetFixedColumnCount(8);
	InitGridTitle();
	//	SetPosTopLeft(0);
}

void CSclCheckCtrlGrid::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);
}

void CSclCheckCtrlGrid::InitGridTitle()
{

	if (m_pDatas == NULL)
	{
		SetColumnCount(1);
		SetRowCount(1);
		return;
	}

	if (m_nOldSclIecCfgClassID == m_pDatas->GetClassID())
	{
		return;
	}

	m_nOldSclIecCfgClassID = m_pDatas->GetClassID();
	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;

	switch (m_nOldSclIecCfgClassID)
	{

	case SCLCLASSID_CHECK_DATA:
		nCols = g_nSclCheckCols;
		pstrTitle = g_astrSclCheckTitle;
		pnWidth = g_iSclCheckWidth;
		break;


	default:
		nCols = g_nSclCheckColsEmpty;
		pstrTitle = g_astrSclCheckTitleEmpty;
		pnWidth = g_iSclCheckWidthEmpty;
		break;
	}

	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclCheckCtrlGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLCLASSID_CHECK_CHANNEL:
		ShowData_Check((CResultRec*)pData, nRow);
		break;
	}

	nRow++;
}


void CSclCheckCtrlGrid::ShowData_Check(CExBaseList *pGsOut,int nRow)
{
	//_T("序号")
	Show_Index(pGsOut, nRow, 0);

	//_T("类型")
	Show_StaticString(pGsOut, nRow, 1, &(((CResultRec*)pGsOut)->m_strErrorType));

	//_T("描述信息")
	Show_StaticString(pGsOut, nRow, 2, &(((CResultRec*)pGsOut)->m_strErrorText));

	// _T("出错位置")
	Show_StaticString(pGsOut, nRow, 3, &(((CResultRec*)pGsOut)->m_strErrorPos));

	// _T("提示数")
	Show_Long(pGsOut,nRow , 4 ,&(((CResultRec*)pGsOut)->m_nTipIndex));

	// _T("告警数")
	Show_Long(pGsOut,nRow , 5 ,&(((CResultRec*)pGsOut)->m_nWarningIndex));

	// _T("错误数")
	Show_Long(pGsOut,nRow , 6 ,&(((CResultRec*)pGsOut)->m_nErrorIndex));

	// _T("严重错误")
	Show_Long(pGsOut,nRow , 7 ,&(((CResultRec*)pGsOut)->m_nFatalErrorIndex));

}BEGIN_MESSAGE_MAP(CSclCheckCtrlGrid, CExBaseListGrid)
ON_WM_SIZE()
END_MESSAGE_MAP()

void CSclCheckCtrlGrid::OnSize(UINT nType, int cx, int cy)
{
	CExBaseListGrid::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
