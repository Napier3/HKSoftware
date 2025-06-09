#include "StdAfx.h"
#include "GridiSmartTestBluetWzd.h"
#include "../StepDlg/WzdFile.h"

CGridiSmartTestBluetWzd::CGridiSmartTestBluetWzd(void)
{
}

CGridiSmartTestBluetWzd::~CGridiSmartTestBluetWzd(void)
{
}

void CGridiSmartTestBluetWzd::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(BluetWzd_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGridiSmartTestBluetWzd::InitGridTitle()
{
	CString astrSclIedsGirdTitle[BluetWzd_TABLE_COLS] = {_T("编号"),_T("变电站名称"),_T("装置型号"),_T("检验/接收日期"),_T("检验/接收人"),\
									_T("审核人"),_T("检验仪器"),_T("报告生成日期"),_T("检验类型"),_T("线路名称"),\
									_T("保护套别"),_T("任务ID")};
	const int nSclIedsWidth[BluetWzd_TABLE_COLS]={50, 150 ,150 ,150, 100 ,\
								150 ,200 ,150, 150 , 150 ,\
								150 ,330};
	SetColumnCount(BluetWzd_TABLE_COLS);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, BluetWzd_TABLE_COLS);
}

void CGridiSmartTestBluetWzd::ShowData(COrderInfo0x92 *pData, BOOL bInsertRow)
{
	SetRowCount(2, bInsertRow);

	int nRowIndex = 1;	
	ShowData(pData, nRowIndex, FALSE);

	SetRowCount(nRowIndex, bInsertRow);
	AfterShowDatas(1, bInsertRow);
}
void CGridiSmartTestBluetWzd::ShowDatas(CExBaseList *pDataList, BOOL bInsertRow)
{
	if (pDataList == NULL)
	{
		SetRowCount(1);
		return;
	}

	POS pos = pDataList->GetHeadPosition();
	int nRowIndex = 1;
	CExBaseObject *pObj = NULL;
	long nCalRows = pDataList->GetCount() + 1;
	SetRowCount(nCalRows, bInsertRow);

	while (pos != NULL)
	{
		pObj = pDataList->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bInsertRow);
	AfterShowDatas(1, bInsertRow);
	
	//SortTextItems(BluetWzd_SORT_TABLE_COLS, false);
}
void CGridiSmartTestBluetWzd::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
 	if (pData == NULL)
 	{
 		return;
 	}

	COrderInfo0x92 *pData92 = (COrderInfo0x92 *)pData;

	CString sJYLX = _T("未知类型");
	CDataType *pTestDataType = CCfgDataMngrConstGlobal::FindDataTypeAndAdd(g_strAppSendTestDataTypeID);
	if(pTestDataType != NULL)
	{
		CDataTypeValue *pValue = pTestDataType->FindByIndex(pData92->m_nstrJYLX);
		if(pValue != NULL)
		{
			sJYLX = pValue->m_strName;
		}
	}
 
 	Show_Index(pData92, nRow, 0);	 //序号
 	Show_StaticString(pData92, nRow, 1, &pData92->m_strstrBDZ);	  //变电站名称
	Show_StaticString(pData92, nRow, 2, &pData92->m_strstrSBXH);	  //装置型号
	Show_StaticString(pData92, nRow, 3, &pData92->m_strstrJYRQ);	//检验/接收日期
	Show_StaticString(pData92, nRow, 4, &pData92->m_strstrGZFZR);	//工作负责人
	Show_StaticString(pData92, nRow, 5, _T(""));					//审核人
	Show_StaticString(pData92, nRow, 6, &pData92->m_strstrSBMC);	//设备名称
	Show_StaticString(pData92, nRow, 7, _T(""));					//报告生成日期
	Show_StaticString(pData92, nRow, 8, sJYLX);					//检验类型
	Show_StaticString(pData92, nRow, 9, _T(""));					//线路名称
	Show_StaticString(pData92, nRow, 10, _T(""));				//保护套别
	Show_StaticString(pData92, nRow, 11, &pData92->m_strstrRWID);	//任务ID

	nRow++;
}