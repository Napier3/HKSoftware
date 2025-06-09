#include "SttModuleAttrsGrid.h"

#include "../../../../Module/SttTest/Common/tmt_adjust_sys_para_module_def.h"

#include "..\ReportView\XLangResource_PowerTestWin.h"

CSttModuleAttrsGrid::CSttModuleAttrsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttModuleAttrsGrid::~CSttModuleAttrsGrid()
{

}

void CSttModuleAttrsGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(FALSE);
}

void CSttModuleAttrsGrid::InitGridTitle()
{
	CString astrGridTitle[CDEVICE_MODULE_ATTRS_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name.GetString(),/*_T("数据值")*/g_sLangTxt_State_Datavalue.GetString()};
	int  iColType[CDEVICE_MODULE_ATTRS_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CDEVICE_MODULE_ATTRS_GRID_COLS]={200,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CDEVICE_MODULE_ATTRS_GRID_COLS);
}

void CSttModuleAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);	
	
	if (pData->GetClassID() == DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData *)pData;
	Show_String(pData,nRow,0,&pDvmData->m_strName); 
	Show_String(pData,nRow,1,&pDvmData->m_strValue); 


 	nRow++;
}


