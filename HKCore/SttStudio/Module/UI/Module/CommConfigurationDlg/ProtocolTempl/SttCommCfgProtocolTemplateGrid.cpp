#include "SttCommCfgProtocolTemplateGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../Module/XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
extern void Global_SetComCfgTableHeight(QTableWidget *pGrid);
extern QFont *g_pSttGlobalFont;

SttCCommCfgProtocolTemplateGrid::SttCCommCfgProtocolTemplateGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

SttCCommCfgProtocolTemplateGrid::~SttCCommCfgProtocolTemplateGrid()
{

}

void SttCCommCfgProtocolTemplateGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(FALSE);
	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
}

void SttCCommCfgProtocolTemplateGrid::InitGridTitle()
{
	CString astrGridTitle[STTCCOMMCFGPROTOCOLTEMPLATE_COLS] = { /*_T("�ļ���")*/g_sLangTxt_FileName, CString("�ļ���С"), CString("����ʱ��")};
	int  iColType[STTCCOMMCFGPROTOCOLTEMPLATE_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[STTCCOMMCFGPROTOCOLTEMPLATE_COLS]={200, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCCOMMCFGPROTOCOLTEMPLATE_COLS);
}

void SttCCommCfgProtocolTemplateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
 	CDvmData *pDvmData = (CDvmData *)pData;
	CString strValue, strDataType;
 	Show_StaticString(pData, nRow, 0, &pDvmData->m_strName); 
	Show_StaticString(pData, nRow, 1, &pDvmData->m_strMin);
	Show_StaticString(pData, nRow, 2, &pDvmData->m_strMax); 

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

	//Show_StaticString(pData,nRow,1,strValue); 
 	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCCommCfgProtocolTemplateGrid::SelectRow(int nRow)
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


