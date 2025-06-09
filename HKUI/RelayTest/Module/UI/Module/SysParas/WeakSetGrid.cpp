#include "WeakSetGrid.h"
#include <QMenu>
#include <QAction>
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../XLangResource_Native.h"
#include <QApplication>


#define WEAKSET_GRID_COL_INDEX_NAME                    0
//#define WEAKSET_GRID_COL_INDEX_ID                      1
#define WEAKSET_GRID_COL_INDEX_WEAK                    1
#define WEAKSET_GRID_COL_INDEX_PRIM                    2
#define WEAKSET_GRID_COL_INDEX_SECOND                  3
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif


CWeakSetGrid::CWeakSetGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pPrimaryValue_DelegBase = NULL;
	m_pSecondaryValue_DelegBase = NULL;

	m_bRunning = FALSE;
	installEventFilter(this);
}

CWeakSetGrid::~CWeakSetGrid()
{
}

void CWeakSetGrid::InitGrid()
{
 	InitGridTitle();
	m_pPrimaryValue_DelegBase = new QExBaseListFloatEditDelegBase(this);
	m_pPrimaryValue_DelegBase->InitCoverage(1,100000,3);
	setItemDelegateForColumn(WEAKSET_GRID_COL_INDEX_PRIM,m_pPrimaryValue_DelegBase);

	m_pSecondaryValue_DelegBase = new QExBaseListFloatEditDelegBase(this);
	m_pSecondaryValue_DelegBase->InitCoverage(0.00,10,3);
	setItemDelegateForColumn(WEAKSET_GRID_COL_INDEX_SECOND,m_pSecondaryValue_DelegBase);
	SetEditable(TRUE);
	CreateGridMenu();

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_OnItemClicked(int,int)),Qt::UniqueConnection);

}

void CWeakSetGrid::InitGridTitle()
{
//	CString astrGridTitle[WEAKSET_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name,/*_T("软件资源标识"),*//*_T("弱信号通道")*/g_sLangTxt_ChMaps_WeekCh,/*_T("一次值(V/A)")*/g_sLangTxt_Gradient_VAOnceValue,/*_T("二次值(V/A)")*/g_sLangTxt_Gradient_VATwiceValue}; //lcq

//2024-8-22 wuxinyi 按需求弱信号设置二次值单位修改为（v）
	CString astrGridTitle[WEAKSET_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name,/*_T("软件资源标识"),*//*_T("弱信号通道")*/g_sLangTxt_ChMaps_WeekCh,/*_T("一次值(V/A)")*/g_sLangTxt_Gradient_VAOnceValue}; //lcq
	CString strTwiceTital = g_sLangTxt_IEC_TwiceValue.GetString();
	strTwiceTital.AppendFormat(_T("(V)"));
	astrGridTitle[3] = strTwiceTital;
	int  iColType[WEAKSET_GRID_COLS]={QT_GVET_NOEDIT, /*QT_GVET_NOEDIT,*/QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[WEAKSET_GRID_COLS]={130,/* 100,*/ 130, 130, 130};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, WEAKSET_GRID_COLS);
//	SetFont(g_pGlobalFont11);
}

void CWeakSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->m_strID.Find("Bin")>=0)
	{
		return;
	}
	else if (pData->m_strID.Find("Bout") >= 0)
	{
		return;
	}

	ASSERT(pData);
	CSttChMap *pChMap = (CSttChMap *)pData;
	Show_StaticString(pData,nRow,0,&pChMap->m_strName); 
//	Show_StaticString(pData,nRow,1,&pChMap->m_strID); 
	CString strWeakString;
	CDvmData *pDvmData = NULL;
	CSttHdChs *pHdChs = NULL;
	strWeakString = pChMap->GetHdChsString(STT_MODULETYPE_ID_WEEK);
	Show_StaticString(pData,nRow,1,&strWeakString);
	pHdChs = pChMap->GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
		return;
	}

	if (pHdChs->GetCount() <= 0)
	{
		return;
	}

	CSttHdCh *pHdCh = (CSttHdCh*)pHdChs->GetHead();
	pDvmData = pHdCh->GetPrimaryValue_DvmData();
	Show_String(pData,nRow,2,&pDvmData->m_strValue,EndEditCell_WeakRateSetString);
	pDvmData = pHdCh->GetSecondaryValue_DvmData();
	Show_String(pData,nRow,3,&pDvmData->m_strValue,EndEditCell_WeakRateSetString);
 	nRow++;
}

void CWeakSetGrid::EndEditCell_WeakRateSetString (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CSttChMap *pChMap = (CSttChMap*)pVCellData->pObj;

	CSttHdChs *pHdChs = pChMap->GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
		return;
	}

	if (pHdChs->GetCount() <= 0)
	{
		return;
	}

	if (*pVCellData->pString != pCell->text())
	{
		CString strTmp;
		strTmp = pCell->text();
		double dValue = CString_To_double(strTmp);
		(*pVCellData->pString).Format(_T("%.03lf"),dValue);

		if (strTmp != (*pVCellData->pString))
		{
			pCell->setText(*pVCellData->pString);
		}
		//		((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

	CSttHdCh *pHdCh = (CSttHdCh*)pHdChs->GetHead();
	float fPrimaryValue = pHdCh->GetPrimaryValue_Float();
	float fSecondaryValue = pHdCh->GetSecondaryValue_Float();
	
	POS pos = pHdChs->GetHeadPosition();

	while(pos)
	{
		pHdCh = (CSttHdCh *)pHdChs->GetNext(pos);
		pHdCh->SetTransRate_Weak(fPrimaryValue,fSecondaryValue);
	}
}

void CWeakSetGrid::CreateGridMenu()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);
	m_pWeakSetMenu = new QMenu(this);

	m_pThreePhaseEqualAction = new QAction(/*tr("三相相同")*/g_sLangTxt_Gradient_SameThreep,this); //lcq
	m_pThreePhaseEqualAction->setCheckable(true);
	m_pThreePhaseEqualAction->setCheckable(false);
	m_pAllEqualAction = new QAction(/*tr("全部相同")*/g_sLangTxt_Gradient_AllSamep,this); //lcq

	m_pWeakSetMenu->addAction(m_pThreePhaseEqualAction);
	m_pWeakSetMenu->addAction(m_pAllEqualAction);

	connect (m_pThreePhaseEqualAction,SIGNAL(triggered()),this,SLOT(slot_ThreePhaseEqualActlicked())); 
	connect (m_pAllEqualAction,SIGNAL(triggered()),this,SLOT(slot_AllEqualActlicked())); 
	QExBaseListGridBase::CreateGridMenu();
}

void CWeakSetGrid::slot_GridShowMenu(QPoint pos)
{
	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();//获得QTableWidget列表点击的行数 

	switch(col)
	{
//	case WEAKSET_GRID_COL_INDEX_WEAK:
	case WEAKSET_GRID_COL_INDEX_PRIM:
	case WEAKSET_GRID_COL_INDEX_SECOND:
		{
			m_pWeakSetMenu->move(cursor().pos()); 
			m_pWeakSetMenu->show(); 
		}
		break;
	default:
		break;
	}
}

BOOL CWeakSetGrid::GetCurSelChMapObj(CSttChMaps **ppChMaps,CSttChMap **ppChMap,CSttHdCh **ppHdCh,float &fValue,BOOL &bPrimaryValue)
{
	QGV_ITEM *pItem = GetCurrSelItem();

	if (pItem == NULL)
	{
		return FALSE;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;

	if (pVCellData == NULL)
	{
		return FALSE;
	}

	*ppChMap = (CSttChMap*)pVCellData->pObj;

	if (*ppChMap == NULL)
	{
		return FALSE;
	}

	*ppChMaps = (CSttChMaps*)(*ppChMap)->GetParent();

	if (*ppChMaps == NULL)
	{
		return FALSE;
	}

	CSttHdChs *pHdChs = (*ppChMap)->GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
		return FALSE;
	}

	if (pHdChs->GetCount() <= 0)
	{
		return FALSE;
	}

	*ppHdCh = (CSttHdCh*)pHdChs->GetHead();
	long nCol = pItem->column();

	if (nCol == WEAKSET_GRID_COL_INDEX_PRIM)
	{
		bPrimaryValue = TRUE;
		fValue = (*ppHdCh)->GetPrimaryValue_Float();
	}
	else if (nCol == WEAKSET_GRID_COL_INDEX_SECOND)
	{
		bPrimaryValue = FALSE;
		fValue = (*ppHdCh)->GetSecondaryValue_Float();
	}
	else 
		return FALSE;

	return TRUE;
}

void CWeakSetGrid::slot_ThreePhaseEqualActlicked()
{
	CSttChMaps *pChMaps = NULL;
	CSttChMap *pChMap = NULL;
	CSttHdCh *pHdCh = NULL;
	long nCol = 0;
	BOOL bPrimaryValue = FALSE;
	float fValue = 0.0f;

	if (!GetCurSelChMapObj(&pChMaps,&pChMap,&pHdCh,fValue,bPrimaryValue))
	{
		return;
	}

	long nRsIndex = pChMap->GetRsIndexFromID();
	BOOL bHasUpdate = FALSE;
	CString strSoftRs1,strSoftRs2;

	if (nRsIndex%3 == 0)
	{
		strSoftRs1.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex-1);
		strSoftRs2.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex-2);
	}
	else if (nRsIndex%3 == 1)
	{
		strSoftRs1.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex+1);
		strSoftRs2.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex+2);
	}
	else if (nRsIndex%3 == 2)
	{
		strSoftRs1.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex-1);
		strSoftRs2.Format(_T("%c%ld"),pChMap->m_strID.GetAt(0),nRsIndex+1);
	}

	pChMap = (CSttChMap*)pChMaps->FindByID(strSoftRs1);

	if (pChMap != NULL)
	{
		bHasUpdate = TRUE;
		pChMap->SetWeakRateValue(fValue,bPrimaryValue);
	}

	pChMap = (CSttChMap*)pChMaps->FindByID(strSoftRs2);

	if (pChMap != NULL)
	{
		bHasUpdate = TRUE;
		pChMap->SetWeakRateValue(fValue,bPrimaryValue);
	}

	if (bHasUpdate)
	{
		ShowDatas(m_pDatas);
	}
}

void CWeakSetGrid::slot_AllEqualActlicked()
{
	CSttChMaps *pChMaps = NULL;
	CSttChMap *pChMap = NULL;
	CSttHdCh *pHdCh = NULL;
	long nCol = 0;
	BOOL bPrimaryValue = FALSE;
	float fValue = 0.0f;

	if (!GetCurSelChMapObj(&pChMaps,&pChMap,&pHdCh,fValue,bPrimaryValue))
	{
		return;
	}

	POS pos = pChMaps->GetHeadPosition();
	CSttChMap *pCurChMap = NULL;

	while(pos)
	{
		pCurChMap = (CSttChMap *)pChMaps->GetNext(pos);

		if (pCurChMap->m_strID.GetAt(0) != pChMap->m_strID.GetAt(0))
		{
			continue;
		}

		if (pCurChMap == pChMap)
		{
			continue;
		}

		pCurChMap->SetWeakRateValue(fValue,bPrimaryValue);
	}

	ShowDatas(m_pDatas);
}


void CWeakSetGrid::slot_OnItemClicked(int nRow,int nCol )
{
	
// 	QTableWidgetItem *pItem = this->item(nRow,nCol);
	QGV_ITEM *pItem = GetCell(nRow,nCol);
	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetWidgetBoard_DigitData(4,strValue,pItem,this);
	//QSoftKeyBoard::DisableUserFunc();
// 	pItem->setText(strValue);


//#ifdef _USE_SoftKeyBoard_
//	//QSoftKeyBoard::Attach330Channel(this, 4);
//	QSoftKeyBoard::AttachObj(this);
//	QSoftKeyBoard::ReAttachObj();
//#endif

}



bool CWeakSetGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void CWeakSetGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}

