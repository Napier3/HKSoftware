#include "SttCommCfgPkgMonitorLeftGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>

extern CFont *g_pSttGlobalFont;

SttCCommCfgPkgMonitorLeftGrid::SttCCommCfgPkgMonitorLeftGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	setFont(*g_pSttGlobalFont);
	m_bRunning = FALSE;
}

SttCCommCfgPkgMonitorLeftGrid::~SttCCommCfgPkgMonitorLeftGrid()
{

}

void SttCCommCfgPkgMonitorLeftGrid::InitGrid()
{
 	InitGridTitle();
	setSelectionMode(QAbstractItemView::SingleSelection);
	setFocusPolicy(Qt::NoFocus);

	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
	connect(this,SIGNAL(currentCellChanged(int , int , int , int )),this,SLOT(slot_CurrentCellChanged(int , int , int , int )));
	connect(this,SIGNAL(sig_ScrollFinished()),this,SLOT(slot_ScrollGridFinished()));
	//SetEditable(FALSE);
}

void SttCCommCfgPkgMonitorLeftGrid::InitGridTitle()
{
	CString astrGridTitle[STTCCOMMCFGPKGMONITORLEFTGRID_COLS] = { CString("时标") , CString("帧简析"),CString("帧数据")};
	int  iColType[STTCCOMMCFGPKGMONITORLEFTGRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[STTCCOMMCFGPKGMONITORLEFTGRID_COLS]={230,70,100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCCOMMCFGPKGMONITORLEFTGRID_COLS);
}

void SttCCommCfgPkgMonitorLeftGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	 /*	ASSERT(pData);
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

void SttCCommCfgPkgMonitorLeftGrid::SelectRow(int nRow)
{
// 	QGV_ITEM* pitem = (QGV_ITEM*)item(nRow,1);
// 
// 	if(pitem == NULL)
// 	{
// 		return;
// 	}
// 
// 	pitem->setSelected(true);

	//setCurrentCell(nRow,QItemSelectionModel::Select);
}

void SttCCommCfgPkgMonitorLeftGrid::ShowData(CSttParas *pData, int nRow)
{
	ASSERT(pData);
	CDvmData *pTimeData = (CDvmData *)pData->FindByID("Time");
	Show_StaticString(pTimeData,nRow,0,&pTimeData->m_strValue);

	CDvmData *pDirData = (CDvmData *)pData->FindByID("Dir");
	long nDir  = CString_To_long (pDirData->m_strValue);
	CString strDir = "";
	if(nDir)
	{
		strDir = _T("接收");
	}
	else
	{
		strDir = _T("发送");
}
	//Show_StaticString(pDirData,nRow,1,&pDirData->m_strValue); 
	Show_StaticString(pDirData,nRow,1,&strDir); 

	CDvmData *pPkgData = (CDvmData *)pData->FindByID("Pkg");
	Show_StaticString(pPkgData,nRow,2,&pPkgData->m_strValue); 
}

bool SttCCommCfgPkgMonitorLeftGrid::eventFilter(QObject *obj, QEvent *event)
{
#ifdef _PSX_QT_LINUX_
	return QScrollTableWidget::eventFilter(obj,event);
#else
	return QTableWidget::eventFilter(obj,event);
#endif
	//return  true;
}

void SttCCommCfgPkgMonitorLeftGrid::mousePressEvent(QMouseEvent * event)
{
#ifdef _PSX_QT_LINUX_
	QScrollTableWidget::mousePressEvent(event);
#else
	QTableWidget::mousePressEvent(event);
#endif

}

