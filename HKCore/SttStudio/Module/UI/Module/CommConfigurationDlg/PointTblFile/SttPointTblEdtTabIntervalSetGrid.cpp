#include "SttPointTblEdtTabIntervalSetGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../../Module/DataMngr/DvmLogicDevice.h"
#include <QDebug>
extern void Global_SetComCfgTableHeight(QTableWidget *pGrid);
extern QFont *g_pSttGlobalFont;


SttCPointTblEdtTabIntervalSetGrid::SttCPointTblEdtTabIntervalSetGrid (QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	//m_pColsList = NULL;
	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);

		
}

SttCPointTblEdtTabIntervalSetGrid::~SttCPointTblEdtTabIntervalSetGrid ()
{

}

void SttCPointTblEdtTabIntervalSetGrid::SetColumns(QStringList* strIDsList, QStringList* strNmsList)
{
	if (strIDsList == NULL)
	{
		return;
	}
	m_oColIDsList.clear();
	for (int i=0; i<strIDsList->size(); i++)
	{
		m_oColIDsList.append(strIDsList->at(i));
	}

	m_oColNamesList.clear();
	for (int i=0; i<strNmsList->size(); i++)
	{
		m_oColNamesList.append(strNmsList->at(i));
	}

	//m_pColsList = stringList;
	int iSize = strIDsList->size();
	CString *strGridTitles = new CString[iSize + 1];
	int *iColTypes = new int[iSize];
	int *iWidths = new int[iSize + 1];

	strGridTitles[0] = CString("�����");
	iWidths[0] = 200;
	for (int i=0; i<iSize; i++)
	{
		strGridTitles[i + 1] = strNmsList->at(i);
	//iColTypes[i]=QT_GVET_NOEDIT;
		iWidths[i + 1] = 150;
	}

	QExBaseListGridBase::InitGridTitle(strGridTitles, iWidths, iSize+1);

	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}

} 

void SttCPointTblEdtTabIntervalSetGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(FALSE);
}

void SttCPointTblEdtTabIntervalSetGrid::InitGridTitle()
{
	//�������ң���׵�ַ��ң���׵�ַ��ң���׵�ַ��ң���׵�ַ
	//���в����׵�ַ�����в����׵�ַ����ֵ�����׵�ַ����ѹ���׵�ַ
	 
	CString astrGridTitle[STTCPOINTTBLEDTTABINTERVALSETGRID_COLS] = { _T("�����"), _T("ң���׵�ַ"), _T("ң���׵�ַ"), _T("ң���׵�ַ"), _T("ң���׵�ַ"), _T("���в����׵�ַ"), _T("���в����׵�ַ"), _T("��ֵ�����׵�ַ"),_T("��ѹ���׵�ַ")};

	int  iColType[STTCPOINTTBLEDTTABINTERVALSETGRID_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[STTCPOINTTBLEDTTABINTERVALSETGRID_COLS]={100,100,100,100,100,100,100,100,100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCPOINTTBLEDTTABINTERVALSETGRID_COLS);
}

void SttCPointTblEdtTabIntervalSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	CDvmLogicDevice *pLogicDev = (CDvmLogicDevice *)pData;
	if(pLogicDev->m_strID == "report")
	{
		return;
	}
	CString strDatasetName = pLogicDev->m_strName;
	if (strDatasetName.IsEmpty())
	{
		strDatasetName = pLogicDev->m_strID;
	}
 	Show_StaticString(pData, nRow, 0, &strDatasetName); 

	for (int i=0; i<m_oColIDsList.size(); i++)
	{
		CExBaseObject* pFind = pLogicDev->FindChildByID(m_oColIDsList.at(i));
		if (pFind != NULL)
		{
			CDvmDataset *pdataSet = (CDvmDataset*)pFind;
			////Show_Hex(pData,nRow,i+1,(DWORD*)(&pdataSet->m_nAddr),2); 
			Show_Hex(pData,nRow,i+1,(DWORD*)(&pdataSet->m_nAddr),2,TRUE,TRUE,EndSttCommCfgEditCell_AddrValue); 

			////Show_Long(pData, nRow, i+1, &pdataSet->m_nAddr);
			//Show_Long(pData, nRow, i+1, &pdataSet->m_nAddr, EndSttCommCfgEditCell_String);
			//Show_Long(pData,nRow,i+1,&pdataSet->m_nAddr,TRUE,_T(""),EndEditCell_ChNum);
		}
	}

 	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCPointTblEdtTabIntervalSetGrid::SelectRow(int nRow)
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

void SttCPointTblEdtTabIntervalSetGrid::EndSttCommCfgEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
//	qDebug()<<"SttCPointTblEdtTabIntervalSetGrid END  nrow:"<<nRow<<" ncol:"<<nCol;
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if(*(pVCellData->pString) != pCell->text())
	{
		*(pVCellData->pString) = pCell->text();
	}
}

void SttCPointTblEdtTabIntervalSetGrid::EndSttCommCfgEditCell_AddrValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
//	qDebug()<<"EndSttCommCfgEditCell_AddrValue END test nrow:"<<nRow<<" ncol:"<<nCol;
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT(pVellData->pObj != NULL);
	
	CString crtVl=pCell->text();

	CDvmLogicDevice *pDevice = (CDvmLogicDevice*)(pVellData->pObj);
	if (pDevice->GetCount() <= 0)
	{
		return;
	}


	//QStringList *pStrList = (QStringList *)(m_pIED_Hash.value(pDevice->m_strID));
	SttCPointTblEdtTabIntervalSetGrid *pGridCrt =	(SttCPointTblEdtTabIntervalSetGrid*)pGrid;
	//QTableWidgetItem *pHeadTitle = pGridCrt->horizontalHeaderItem(nCol);
	//CString strHeadTitle = pHeadTitle->text();
	//CString findDasetID = strHeadTitle;
	//if (pStrList->contains(strHeadTitle))
	//{
	//	findDasetID=strHeadTitle;
	//}

	CString findDasetID = pGridCrt->m_oColIDsList.at(nCol - 1);

	if (findDasetID.IsEmpty())
	{
		return;
	}
	CDvmDataset *pDasetFind = (CDvmDataset*)(pDevice->FindByID(findDasetID));
	if (pDasetFind == NULL)
	{
		return;
	}

	CString strCellText = pCell->text();
	strCellText.MakeUpper();
	int nPos = strCellText.Find(CString("0X"));
	CString strTableAddr;
	long lLastRes = 0;
	if (nPos < 0) //��ʮ������
	{	
		long lValue = CString_To_long(pCell->text());
		strTableAddr.Format(_T("0X%04X"), lValue);
		lLastRes = lValue;
		pDasetFind->m_nAddr = lValue;
		

	}else{ //ʮ������
		strTableAddr = pCell->text();
		CString strTmp = pCell->text();
		long nValue = 0;
		char *pzfTmp = NULL;
		CString_to_char(strTmp,&pzfTmp);
		HexToLong(pzfTmp, nValue);
		delete pzfTmp;
		lLastRes = nValue;

		//===========
		CString strValueMdy;
		strValueMdy.Format("%ld", nValue);
		//pDvmValue->m_strValue = strValueMdy;

		pDasetFind->m_nAddr = nValue;
	}
	//emit ((SttCPointTblEdtTabIntervalSetGrid*)pGrid)->sig_ChangedAdress(nRow,nCol,pCell->text());//chenling20240301
	emit ((SttCPointTblEdtTabIntervalSetGrid*)pGrid)->sig_ChangedIntervSetDevAddr();
	
	emit ((SttCPointTblEdtTabIntervalSetGrid*)pGrid)->sig_ApplyAll(false);
}

/*
void IecCfgFT3OutGrid::EndEditCell_AppCh_FT3Value(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfg6044CommonCh *pCommonCh = (CIecCfg6044CommonCh*)pVellData->pObj;
	ASSERT (pCommonCh != NULL);

	long nValue =  CString_To_long(pCell->text());

	if (nValue != *(pVellData->pnValue))
	{
		*(pVellData->pnValue) = nValue;
		emit ((IecCfgFT3OutGrid*)pGrid)->sig_Ft3Value_Changed();
		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVellData->pObj);
	}
}*/


bool SttCPointTblEdtTabIntervalSetGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}
#ifdef _PSX_QT_LINUX_
	return QScrollTableWidget::eventFilter(obj,event);
#else
	return QTableWidget::eventFilter(obj,event);
#endif
	return  true;

}

void SttCPointTblEdtTabIntervalSetGrid::mousePressEvent(QMouseEvent * event)
{

	if (m_bRunning)
	{
#ifdef _PSX_QT_LINUX_
		QScrollTableWidget::mousePressEvent(event);
#else
		QTableWidget::mousePressEvent(event);
#endif
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);

#ifdef _PSX_QT_LINUX_
	QScrollTableWidget::mousePressEvent(event);
#else
	QTableWidget::mousePressEvent(event);
#endif

}
