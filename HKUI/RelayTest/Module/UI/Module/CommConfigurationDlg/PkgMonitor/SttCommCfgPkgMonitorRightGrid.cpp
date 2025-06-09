#include "SttCommCfgPkgMonitorRightGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>
#include <QHeaderView>

extern CFont *g_pSttGlobalFont;

SttCCommCfgPkgMonitorRightGrid::SttCCommCfgPkgMonitorRightGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	setFont(*g_pSttGlobalFont);
}

SttCCommCfgPkgMonitorRightGrid::~SttCCommCfgPkgMonitorRightGrid()
{

}

void SttCCommCfgPkgMonitorRightGrid::InitGrid()
{
 	InitGridTitle();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
	verticalHeader()->setVisible(false);
	resizeColumnToContents(0);
	//SetEditable(FALSE);
	SetRowCount(1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections  Section
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
#else
    verticalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);
#endif
}

void SttCCommCfgPkgMonitorRightGrid::InitGridTitle()
{
	CString astrGridTitle[STTCCOMMCFGPKGMONITORRIGHTGRID_COLS] = { CString("帧解析")};
	int  iColType[STTCCOMMCFGPKGMONITORRIGHTGRID_COLS]={QT_GVET_NOEDIT};
	int iGridWidth[STTCCOMMCFGPKGMONITORRIGHTGRID_COLS]={180};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCCOMMCFGPKGMONITORRIGHTGRID_COLS);
}

void SttCCommCfgPkgMonitorRightGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	/*ASSERT(pData);
 	CDvmData *pDvmData = (CDvmData *)pData;
	CString strValue,strDataType;
 	Show_StaticString(pData,nRow,0,&pDvmData->m_strName); 
	strDataType = pDvmData->m_strDataType;
	strDataType.MakeUpper();

	if (strDataType == "FLOAT")
	{
		double dValue = CString_To_double(pDvmData->m_strValue);
		strValue.Format(_T("%.03lf"),dValue);
	}
	else
	{
		strValue = pDvmData->m_strValue;
	}

	Show_StaticString(pData,nRow,1,strValue); 
 	nRow++;*/
}

void SttCCommCfgPkgMonitorRightGrid::SelectRow(int nRow)
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

void SttCCommCfgPkgMonitorRightGrid::ShowData(CSttParas *pData, int nRow)
{
	ASSERT(pData);

	CDvmData *pPkgData = (CDvmData *)pData->FindByID("Pkg");
	//CString str = "ASSERT(pData); CDvmData *pDvmData = (CDvmData *)pData;CString strValue,strDataType;strDataType.MakeUpper();";
	//Show_StaticString(pPkgData,nRow,0,&str); 
	Show_StaticString(pPkgData,nRow,0,&pPkgData->m_strValue); 
}
