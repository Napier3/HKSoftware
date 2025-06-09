#include "DeviceAttrsGrid.h"
#include <QDesktopWidget>
#include <QApplication>
#include "../../../../../Module/DataMngr/DvmData.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

CDeviceAttrsGrid::CDeviceAttrsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CDeviceAttrsGrid::~CDeviceAttrsGrid()
{

}

void CDeviceAttrsGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(FALSE);
}

void CDeviceAttrsGrid::InitGridTitle()
{
	CString astrGridTitle[CDEVICE_ATTRS_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name,/*_T("数据值")*/g_sLangTxt_State_Datavalue};

	int  iColType[CDEVICE_ATTRS_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CDEVICE_ATTRS_GRID_COLS]={130,300};

	//2023-11-17 wuxinyi 2880X1800分辨率处理
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
 	if (rect.height() == 1800)
	{
		iGridWidth[0]=400;
		iGridWidth[1]=400;
	}
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CDEVICE_ATTRS_GRID_COLS);


}

void CDeviceAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
 	CDvmData *pDvmData = (CDvmData *)pData;
 	Show_String(pData,nRow,0,&pDvmData->m_strName); 
	Show_String(pData,nRow,1,&pDvmData->m_strValue); 
 	nRow++;
}

void CDeviceAttrsGrid::SelectRow(int nRow)
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


