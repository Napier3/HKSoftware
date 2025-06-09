#include "SttGbRptGrid_Dataset.h"
#include "../../../XLangResource_Native.h"

CSttGbRptGrid_Dataset::CSttGbRptGrid_Dataset(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttGbRptGrid_Dataset::~CSttGbRptGrid_Dataset()
{

}

void CSttGbRptGrid_Dataset::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
}

void CSttGbRptGrid_Dataset::InitGridTitle()
{
	CString astrGridTitle[4] = {/*"名称"*/g_sLangTxt_Name, "ID", /*"数值"*/g_sLangTxt_Value, /*"数据类型"*/g_sLangTxt_DataType};
	int iGridWidth[4]={300, 150, 120, 120};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

//该表格显示数据集
void CSttGbRptGrid_Dataset::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);
	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strValue);
	Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strDataType);

	nRow++;
}