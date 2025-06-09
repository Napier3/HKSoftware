#include "DeviceAttrsGrid.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

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
// 	xlang_GetLangStrByFile(astrGridTitle[0],"Smv_Name"); //名称
// 	xlang_GetLangStrByFile(astrGridTitle[1],"State_Datavalue");  //数据值
	int  iColType[CDEVICE_ATTRS_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CDEVICE_ATTRS_GRID_COLS]={300,300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CDEVICE_ATTRS_GRID_COLS);;
}

void CDeviceAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
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


