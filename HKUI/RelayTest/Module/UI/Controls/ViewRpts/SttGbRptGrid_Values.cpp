#include "SttGbRptGrid_Values.h"
#include "../../../../../Module/DataMngr/Value.h"
#include "../../../../../Module/DataMngr/DvmValue.h"
#include "../../../XLangResource_Native.h"
#define STTGBRPT_GRID_VLAUES_COLS	3

#define CMDWZD_GRID_DSDATA_NAME    0
#define CMDWZD_GRID_DSDATA_VALUE   1

CSttGbRptGrid_Values::CSttGbRptGrid_Values(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttGbRptGrid_Values::~CSttGbRptGrid_Values()
{

}

void CSttGbRptGrid_Values::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
}

void CSttGbRptGrid_Values::InitGridTitle()
{
	CString astrGridTitle[STTGBRPT_GRID_VLAUES_COLS] = {/*"名称"*/g_sLangTxt_Name, /*"数值"*/g_sLangTxt_Value, ""};
	int iGridWidth[STTGBRPT_GRID_VLAUES_COLS]={400, 300, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTGBRPT_GRID_VLAUES_COLS);
}

//该表格显示数据集
void CSttGbRptGrid_Values::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmValue *pValue = (CDvmValue *)pData;
	CString strName = pValue->m_strName;

	if (strName.IsEmpty())
	{
		strName = pValue->m_strID;
	}

	Show_StaticString(pValue, nRow, CMDWZD_GRID_DSDATA_NAME, &strName);
	Show_StaticString(pValue, nRow, CMDWZD_GRID_DSDATA_VALUE, &pValue->m_strValue);
	nRow++;
}