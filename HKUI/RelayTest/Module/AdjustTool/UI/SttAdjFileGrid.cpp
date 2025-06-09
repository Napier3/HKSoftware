//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "SttAdjFileGrid.h"

#define STT_ADJFILE_COLS	5

CSttAdjFileGrid::CSttAdjFileGrid()
{
	//初始化属性

	//初始化成员变量
}

CSttAdjFileGrid::~CSttAdjFileGrid()
{

}


void CSttAdjFileGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(STT_ADJFILE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjFileGrid::InitGridTitle()
{
	CString astrTitle[STT_ADJFILE_COLS] = {_T("编号"),_T("型号"),_T("序列号"),_T("上传时间"),_T("上传人员")};
	CString astrAttrs[STT_ADJFILE_COLS] = {_T(""),_T("Model"),_T("SN"),_T("UpdateTime"),_T("Name_User")};
	int nWidth[STT_ADJFILE_COLS]={40,250,150,250,150};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, STT_ADJFILE_COLS);
	InitGridColAttrs(astrAttrs, STT_ADJFILE_COLS);
}

