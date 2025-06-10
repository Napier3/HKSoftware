#include "SclCtrlsGridBase.h"
#include <QApplication>

CSclCtrlsGridBase::CSclCtrlsGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pSelectedSclCtrlsRef = NULL;
	m_pTypeSel_DelegBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

CSclCtrlsGridBase::~CSclCtrlsGridBase()
{
}

void CSclCtrlsGridBase::InitGrid()
{
	InitGridTitle();
	QExBaseListCheckBoxDelegate *pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,pCtrlBlockSelectDelegate);
	m_pTypeSel_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pTypeSel_DelegBase);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
//	AutoAdjColWidth();
	SetEditable(TRUE);

	//2023/9/24 wjs 添加对表格SclSelectCtrlsGrid的初始化
	//InitSclSelectCtrlsGrid();
}

CDataType* CSclCtrlsGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CSclCtrlsGridBase::InitGridTitle()
{
}

void CSclCtrlsGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
}

void CSclCtrlsGridBase::UpdateSelectedState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CSclCtrlBase *pSclCtrlBase = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行

	while (pos != NULL)
	{
		pSclCtrlBase = (CSclCtrlBase*)m_pDatas->GetNext(pos);
		Show_Check(pSclCtrlBase,nRowIndex,0,&pSclCtrlBase->m_nSelect,EndEditCell_CheckChanged);
		UpdatePubSubCfg(pSclCtrlBase,nRowIndex);
		nRowIndex++;
	}
}

void CSclCtrlsGridBase::EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CSclCtrlsGridBase *pOwnGrid = (CSclCtrlsGridBase*)pGrid;

// 	if (pCell->dwValue == *(pVCellData->pnValue))
// 	{
// 		return;
// 	}

//	*(pVCellData->pnValue) = pCell->dwValue;

	if ((pVCellData->pObj != NULL))
	{
		CSclCtrlBase *pSclCtrlBase = (CSclCtrlBase*)pVCellData->pObj;

		if (pSclCtrlBase->m_nSelect)
		{
			if ((pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)||(pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT))
			{
				pSclCtrlBase->m_dwItemData = 0;//用于测试仪Goose订阅
			}
			else  if ((pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)||(pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN))
			{
				pSclCtrlBase->m_dwItemData = 1;//用于测试仪Goose发布
			}
		}

		if (pOwnGrid->m_pSelectedSclCtrlsRef != NULL)
		{
			if (pSclCtrlBase->m_nSelect)
			{
				pOwnGrid->m_pSelectedSclCtrlsRef->AddTail(pSclCtrlBase);
			} 
			else
			{
				pOwnGrid->m_pSelectedSclCtrlsRef->Remove(pSclCtrlBase);
			}
		}

		pOwnGrid->UpdatePubSubCfg(pSclCtrlBase,nRow,TRUE);

	}

}


void CSclCtrlsGridBase::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow,BOOL UpdateCtrlSelectGrid)
{
	//if (pSclCtrlBase->m_nSelect)
	//{
	//	//2023/10/17 wjs 监视该combox被点击事件
	//	Show_DataType_Val(pSclCtrlBase, nRow, 1,iecfg_TesterSubPubDataType, (long *)&pSclCtrlBase->m_dwItemData,EndEditCell_ComBoxChanged);
	//} 
	//else
	//{
	//	Show_StaticString(pSclCtrlBase,nRow,1,_T("--")); 
	//}

	if(UpdateCtrlSelectGrid)
	{
		emit sig_UpdateSelectCtrlsGrid();
	}
}

bool CSclCtrlsGridBase::eventFilter(QObject *obj, QEvent *event)
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

void CSclCtrlsGridBase::mousePressEvent(QMouseEvent * event)
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

void CSclCtrlsGridBase::OnDataSelChanged(int nRow, int nCol)
{
	QExBaseListGridBase::OnDataSelChanged(nRow,nCol);
}
