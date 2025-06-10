#include "SttCmdWzdGrid_DsData.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/DataMngr/DvmData.h"

#include "../../XLangResource_Native.h"

#define CMDWZD_GRID_DADATA_COLS	2

#define CMDWZD_GRID_DSDATA_NAME    0
#define CMDWZD_GRID_DSDATA_VALUE   1

CSttCmdWzdGrid_DsData::CSttCmdWzdGrid_DsData(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_nGridType = DSDATA_GRID_TYPE_SRC;
}

CSttCmdWzdGrid_DsData::~CSttCmdWzdGrid_DsData()
{

}

void CSttCmdWzdGrid_DsData::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
}

void CSttCmdWzdGrid_DsData::InitGridTitle()
{
	CString astrGridTitle[CMDWZD_GRID_DADATA_COLS] = {/*"名称"*/g_sLangTxt_Name, /*"数值"*/g_sLangTxt_Value};
	int iGridWidth[CMDWZD_GRID_DADATA_COLS]={120, 20};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CMDWZD_GRID_DADATA_COLS);
}

//该表格显示数据集
void CSttCmdWzdGrid_DsData::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_StaticString(pDvmData, nRow, CMDWZD_GRID_DSDATA_NAME, &pDvmData->m_strName);

	if (m_nGridType == DSDATA_GRID_TYPE_SRC)
	{
		Show_StaticString(pDvmData, nRow, CMDWZD_GRID_DSDATA_VALUE, &pDvmData->m_strValue);
	}
	else
	{
		Show_String(pDvmData, nRow, CMDWZD_GRID_DSDATA_VALUE, &pDvmData->m_strValue);
	}

	nRow++;
}

