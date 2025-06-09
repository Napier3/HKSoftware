// XrioFileParameterGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioFileParameterGrid.h"
#include "..\..\XrioRead\XrioCustomParameter.h"
#include "..\..\XrioRead\XrioObjectCfg.h"
#include "..\..\XrioRead\XrioListCfg.h"
#include "..\XrioReadTool\XrioReadTool.h"

#define XRIO_PARAMETER_TABLE_COLS       12

#define XRIO_PARAMETER_COL_INDEX        0
#define XRIO_PARAMETER_COL_STATE        1
#define XRIO_PARAMETER_COL_NAME         2
#define XRIO_PARAMETER_COL_ID           3
#define XRIO_PARAMETER_COL_DESCRIPTION  4
#define XRIO_PARAMETER_COL_DATATYPE     5
#define XRIO_PARAMETER_COL_REFVALUE     6
#define XRIO_PARAMETER_COL_VALUE        7
#define XRIO_PARAMETER_COL_UNIT         8
#define XRIO_PARAMETER_COL_MIN          9
#define XRIO_PARAMETER_COL_MAX          10

// CXrioFileParameterGrid

CXrioFileParameterGrid::CXrioFileParameterGrid()
{
	m_nAdjustBeginCol = 1;
}

CXrioFileParameterGrid::~CXrioFileParameterGrid()
{
}

// CXrioFileParameterGrid 成员函数
void CXrioFileParameterGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXrioFileParameterGrid::InitGridTitle()
{
	CString astrGridTitle[XRIO_PARAMETER_TABLE_COLS] = {_T("编号"),_T("状态"),_T("名称"),_T("ID"),_T("描述"),_T("数据类型"),_T("参考值"),
		_T("值"),_T("单位"),_T("最小值"),_T("最大值"),_T("公式")};
	int iGridWidth[XRIO_PARAMETER_TABLE_COLS]={50, 50, 150, 50, 300, 80, 80, 80, 50, 80, 80, 150};
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, XRIO_PARAMETER_TABLE_COLS);
}

void CXrioFileParameterGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	//CXrioCustomParameter *pCustomParameter = ((CXrioTplMapObj *)pData)->m_pXrioParas;
	CXrioCustomParameter *pCustomParameter = ((CXrioCustomParameter *)pData);

	if (pCustomParameter == NULL)
	{
		Show_Index(pCustomParameter, nRow, XRIO_PARAMETER_COL_INDEX);//编号
		nRow++;
		return;
	}
//	_T("编号"),_T("状态"),_T("名称"),_T("Id"),_T("描述"),_T("数据类型"),_T("参考值"),_T("值"),_T("单位"),_T("最小值"),_T("最大值"),_T("公式")

	Show_Index(pCustomParameter, nRow, XRIO_PARAMETER_COL_INDEX);//编号
	long lEnabled;
	if (pCustomParameter->m_strEnabled == _T("true"))
	{
		lEnabled = 1;
	}
	else
	{
		lEnabled = 0;
	}
	Show_Check(pCustomParameter, nRow, XRIO_PARAMETER_COL_STATE, &lEnabled);//状态
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_NAME, pCustomParameter->m_strName);   //名称
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_ID, pCustomParameter->m_strID);	//Id
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_DESCRIPTION, pCustomParameter->m_strDescription);	//描述
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_DATATYPE, pCustomParameter->m_strDataType);	//数据类型

	Show_String(pCustomParameter, nRow, XRIO_PARAMETER_COL_VALUE, &pCustomParameter->m_strValue);					//值
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_UNIT, pCustomParameter->m_strUnit);  //单位
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_MIN, pCustomParameter->m_strMinValue);		//最小值
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_MAX, pCustomParameter->m_strMaxValue);		//最大值

//	POS pos = pCustomParameter->GetHeadPosition();
//	UINT nClassID = XRIOCLASSID_BASECLASS;
//	CExBaseObject* pDataObject = NULL;
//
//	while(pos)
//	{
//		pDataObject = pCustomParameter->GetNext(pos);
//		nClassID = pDataObject->GetClassID();
//        switch(nClassID)
//		{
//		case XRIOCLASSID_UNIT:
//			Show_StaticString(pCustomParameter, nRow, 8, ((CXrioUnit*)pDataObject)->m_strUnit);				//单位
//			break;
//		case XRIOCLASSID_ENABLEDREFLIST:
//			break;
//		case XRIOCLASSID_VALUEREFLIST:
//			break;
//		case XRIOCLASSID_ENUMLIST:
////			Show_ComboBox((CXrioEnumList*)pDataObject, nRow, 6, _T(""));
//			break;
//		default:
//			break;
//		}
//	}

	nRow++;
}
