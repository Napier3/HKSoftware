//SttXDeviceMngrGrid.cpp  CSttXDeviceMngrGrid


#include "stdafx.h"
#include "SttXDeviceMngrGrid.h"
#include "SttXDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXDeviceMngrGrid::CSttXDeviceMngrGrid()
{
	m_nAdjustBeginCol = 2;
	m_dwChildClassID = DTMCLASSID_CDATAGROUP;
}

CSttXDeviceMngrGrid::~CSttXDeviceMngrGrid()
{

}

void CSttXDeviceMngrGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(7);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttXDeviceMngrGrid::InitGridTitle()
{
	CString astrTitle[7] = {_T("编号"),_T("选择"),_T("SN")  ,_T("型号")  ,_T("实验名称")  ,_T("位置")   ,_T("说明")};
	CString astrAttrs[7] = {_T("")       ,_T("")      ,_T("SN")   ,_T("Model") ,_T("TestName")  ,_T("Location") ,_T("Remark")};
	int nWidth[7]= {60,60,100,100, 300, 200, 200};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 7);
	InitGridColAttrs(astrAttrs, 7);
}

void CSttXDeviceMngrGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CSttXDevice *pDevice = (CSttXDevice*)pData;
	CString strTestName;

	pDevice->GetDataValue(_T("TestName"), strTestName);

	Show_Index(pDevice , nRow, 0);

	if (strTestName.GetLength() < 1)
	{
		Show_Check(pDevice, nRow, 1, &pDevice->m_nSelect);
	}
	else
	{
		Show_StaticString(pDevice, nRow, 1, _T("--"));
	}

	long nCol = 1;
	for (nCol=2; nCol < m_nCols; nCol++)
	{
		ShowAttrCol(pDevice, nRow, nCol);
	}

	nRow++;
}

