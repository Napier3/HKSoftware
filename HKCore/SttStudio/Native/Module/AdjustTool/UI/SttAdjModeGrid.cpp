//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "SttAdjModeGrid.h"

CSttAdjModeGrid::CSttAdjModeGrid()
{
	//初始化属性
	//m_strChildDataTypeID = CommDBData_ID_Record;		//STT_ADJ_DATA_TYPE_SttModel;

	//m_strChildDataTypeID = CommDBData_ID_Record;  //STT_ADJ_DATA_TYPE_SttModel;

	m_strChildDataTypeID = CommDBData_ID_Record;
}

CSttAdjModeGrid::~CSttAdjModeGrid()
{

}


void CSttAdjModeGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModeGrid::InitGridTitle()
{
	CString astrTitle[5] = {_T("编号"),  _T("名称"),  _T("类型"),  _T("型号"),   _T("模块数")};//模块ID
	CString astrAttrs[5] = {_T(""),  _T("name"),  _T("id"),  _T("value"),  _T("value")};
	int nWidth[5]  =  {40,  120,  100,  100,  100};


	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 5);
	InitGridColAttrs(astrAttrs, 5);
}

// 2020-11-23 mym add
// 写给自己的：这函数是基类中调用的函数，在ShowDatas函数中，每一条数据调用一次，然后nRow加加，换到下一行；
void CSttAdjModeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{		
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)//DTMCLASSID_CDATAGROUP
	{
		return;
	}

	CDvmData * pDvmData_Value= NULL;
	CString   strModel, strType;

	POS posValue = NULL;

	CDvmData *pDvmData  = (CDvmData*)pData;
	Show_Index(pDvmData, nRow, 0);
	Show_StaticString(pDvmData, nRow, 1, &pData->m_strName);

	posValue = pDvmData->GetHeadPosition();
	while(posValue != NULL)
	{
		pDvmData_Value  = (CDvmData *)pDvmData->GetNext(posValue);
		if (pDvmData_Value->m_strID=="Model")//此时获取ID=="Model" 此时的VALUE值；
		{
			strModel  = pDvmData_Value->m_strValue;
		}
		else if (pDvmData_Value->m_strID=="Type")//此时获取ID=="Model" 此时的VALUE值；
		{
			if (pDvmData_Value->m_strValue=="0")
				strType  = "装置";
			if (pDvmData_Value->m_strValue=="1")
				strType  = "模块";
		}
		
	}
	Show_StaticString(pDvmData, nRow, 2, strType);//pData->m_strID);

	Show_StaticString(pDvmData, nRow, 3, &strModel);

	//for (long nCol=2; nCol<m_nCols; nCol++)
	//{
	// 	ShowAttrCol(pChDrvPos, nRow, nCol);
	//}

	nRow++;
}
