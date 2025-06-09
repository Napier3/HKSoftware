#include "SttModulesGrid.h"
#include "../../../XLangResource_Native.h"
#include "../../../SttTest/Common/tmt_adjust_sys_para_module_def.h"


CSttModulesGrid::CSttModulesGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttModulesGrid::~CSttModulesGrid()
{

}

void CSttModulesGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(TRUE);
}

void CSttModulesGrid::InitGridTitle()
{
	CString astrGridTitle[CDEVICE_MODULES_GRID_COLS] = {/*_T("模块类型")*/g_sLangTxt_Gradient_ModuleType,/*_T("通道数")*/g_sLangTxt_IEC_ChannelNumber,/*_T("位置号")*/g_sLangTxt_Gradient_LocNumber,/*_T("型号")*/g_sLangTxt_Report_AppModel,/*_T("序列号")*/g_sLangTxt_Report_AppSN,/*_T("模块版本")*/g_sLangTxt_Gradient_ModuleVersion,/*_T("生产日期")*/g_sLangTxt_Gradient_ManufactDate};//lcq
	int  iColType[CDEVICE_MODULES_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CDEVICE_MODULES_GRID_COLS]={180,80,80,100,100,90,130};
	m_strModuleAttr[0] = _T("ModuleType");
	m_strModuleAttr[1] = _T("ChannelNum");
	m_strModuleAttr[2] = _T("ModulePos");
	m_strModuleAttr[3] = _T("Model");
	m_strModuleAttr[4] = _T("SN");
	m_strModuleAttr[5] = _T("Version");
	m_strModuleAttr[6] = _T("DateFac");
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CDEVICE_MODULES_GRID_COLS);
// 	setSelectionMode ( QAbstractItemView::SingleSelection);
// 	setStyleSheet("selection-background-color:lightblue;");
// 	setStyleSheet("selection-background-color: grey;selection-color: black");
// 	setEditTriggers(QAbstractItemView::CurrentChanged);
//	setStyleSheet("selection-background-color: grey;selection-color: black");
//	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void CSttModulesGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);	
	
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pDataGroup = (CDataGroup*)pData;

	if (pDataGroup->m_strDataType != STT_ADJ_DATA_TYPE_Module)
	{
		return;
	}

	CDataGroup *pModuleAttrs = (CDataGroup*)pDataGroup->FindByDataType(STT_ADJ_DATA_TYPE_ModuleAttrs);

	if (pModuleAttrs == NULL)
	{
		return;
	}

	for (int nColIndex = 0;nColIndex<CDEVICE_MODULES_GRID_COLS;nColIndex++)
	{
		ShowAttrCol(pModuleAttrs,m_strModuleAttr[nColIndex],nRow,nColIndex);
	}

 	nRow++;
}

void CSttModulesGrid::ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol)  	//显示DvmData子对象
{
	CExBaseObject *pFind = pDataGroup->FindByID(strDataID);

	if (pFind == NULL)
	{
		Show_StaticString(pDataGroup, nRow, nCol, _T("--"));
		return;
	}

	if (pFind->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		Show_StaticString(pDataGroup, nRow, nCol, _T("--"));
		return;
	}

	CDvmData *pData = (CDvmData*)pFind;

	if (pData->m_strValue.IsEmpty())
	{
		Show_StaticString(pDataGroup, nRow, nCol, _T("--"));
	}
	else
	{
		Show_StaticString(pDataGroup, nRow, nCol, &pData->m_strValue);
	}
}

void CSttModulesGrid::SelectRow(int nRow)
{
// 	QGV_ITEM* pitem = (QGV_ITEM*)item(nRow,1);
// 
// 	if(pitem == NULL)
// 	{
// 		return;
// 	}
// 
// 	pitem->setSelected(true);
}