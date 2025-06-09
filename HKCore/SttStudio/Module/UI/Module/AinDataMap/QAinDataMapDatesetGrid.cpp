#include "QAinDataMapDateSetGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>
#include "../../SttTestCntrFrameBase.h"

QAinDataMapDataSetGrid::QAinDataMapDataSetGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{

}

QAinDataMapDataSetGrid::~QAinDataMapDataSetGrid()
{

}


void QAinDataMapDataSetGrid::InitDataSetGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QAinDataMapDataSetGrid::InitGridTitle()
{
	CString astrGridTitle[2];
	astrGridTitle[0]= _T("Name");
	astrGridTitle[1]= _T("ID");

	int iGridWidth[2]={100, 50};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 2);
}

void QAinDataMapDataSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_StaticString(pData,nRow, 0, pDvmData->m_strName);
	Show_StaticString(pData,nRow, 1, pDvmData->m_strID);
	
	//Show_StaticString(pData,nRow, 2,  pDvmData->m_strValue);
	nRow++;
}


