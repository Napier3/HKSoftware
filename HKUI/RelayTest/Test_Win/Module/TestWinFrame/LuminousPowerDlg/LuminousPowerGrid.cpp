#include "LuminousPowerGrid.h"
#include "../testwinbase.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

QLuminousPowerGrid::QLuminousPowerGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{
	m_strPicPath_Green = _P_GetResourcePath();
	m_strPicPath_Green +="circle_green.png";
	
	m_strPicPath_Black = _P_GetResourcePath();
	m_strPicPath_Black +="circle_black.png";
}

QLuminousPowerGrid::~QLuminousPowerGrid()
{

}


void QLuminousPowerGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QLuminousPowerGrid::InitGridTitle()
{
	CString astrGridTitle[3];
	astrGridTitle[0]= /*_T("状态")*/g_sLangTxt_State;
	astrGridTitle[1]= /*_T("光口")*/g_sLangTxt_IEC_FI;
	astrGridTitle[2]= /*_T("光功率(-dbm)")*/g_sLangTxt_Gradient_FOpticalPower;

	int iGridWidth[3]={60, 100, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void QLuminousPowerGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CDvmData *pDvmData = (CDvmData *)pData;
	double dValue=CString_To_double(pDvmData->m_strValue);

// 	QLabel *pLabelWidget = (QLabel*)cellWidget(nRow,0);
// 
// 	if (pLabelWidget == NULL)
// 	{
// 		pLabelWidget = new QLabel(this);
// 	}

	CString strValue;
	strValue.Format(_T("%.2f"), dValue);

	if ((dValue > -53.0f)&&(dValue <0.001f))
	{
		Show_StaticString(pData,nRow, 0, /*_T("连接")*/g_sLangTxt_Native_BtnConnectDevice);
		QGV_ITEM *pPicItem = GetCell(nRow,0);
		pPicItem->setIcon(QPixmap(m_strPicPath_Green));
//		pLabelWidget->setPixmap(QPixmap(m_strPicPath_Green));
	Show_StaticString(pData,nRow, 2, strValue);
	}
	else
	{		
		Show_StaticString(pData,nRow, 0, /* _T("断开")*/g_sLangTxt_SOE_Break);
		QGV_ITEM *pPicItem = GetCell(nRow,0);
		pPicItem->setIcon(QPixmap(m_strPicPath_Black));
//		pLabelWidget->setPixmap(QPixmap(m_strPicPath_Black));
		Show_StaticString(pData,nRow, 2, _T("--"));
	}

//	pLabelWidget->setAlignment(Qt::AlignCenter); 
//	setCellWidget(nRow,0,pLabelWidget);
	Show_StaticString(pData,nRow, 1, pDvmData->m_strName);
	nRow++;
}


