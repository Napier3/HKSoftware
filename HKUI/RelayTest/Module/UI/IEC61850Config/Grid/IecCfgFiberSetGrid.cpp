#include "IecCfgFiberSetGrid.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "IecCfgChsGridBase.h"
#include "../../Module/XLangResource_Native.h"
#include <QApplication>

CIecCfgFiberSetGrid::CIecCfgFiberSetGrid(QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_nMaxFiberNum = 6;
	m_bRunning = FALSE;
	m_nLeftWidth=200;
	installEventFilter(this);
}

CIecCfgFiberSetGrid::~CIecCfgFiberSetGrid()
{
	m_oFiberSetList.RemoveAll();

}

void CIecCfgFiberSetGrid::InitGrid()
{
	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	m_pFiberSel_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pFiberSel_DelegBase);

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgFiberSetGrid::InitGridTitle()
{
	CString strFiberDesc,strFiberSet;
	//strFiberDesc = _T("光口描述");
	//strFiberSet = _T("光口设置");

	CString astrGridTitle[IECCFG_FIBERSET_GRID_COLS] = {g_sLangTxt_IEC_OPDES,g_sLangTxt_IEC_Opticalport};
	
	//20240103 gongyiping 默认strFiberDesc宽度为200
	//由于输出光口设置有两个该表格和接收光口设置有一个表格，需要重新设置光口描述的宽度
	int iGridWidth[IECCFG_FIBERSET_GRID_COLS]={m_nLeftWidth,100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFG_FIBERSET_GRID_COLS);
}

void CIecCfgFiberSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGFIBERPARA)
	{
		return;
	}

	if (nRow>=m_nMaxFiberNum)
	{
		return;
	}

	CIecCfgFiberPara *pIecCfgFiberPara = (CIecCfgFiberPara*)pData;
	Show_StaticString(pData,nRow,0,&pIecCfgFiberPara->m_strName/*strType*/);

	if(pData->GetParent()->GetClassID() == CFGCLASSID_CIECCFGFIBERPARAIN)
	{
		if (pIecCfgFiberPara->m_strID.Find(_T("ST")) == -1)  // 只显示ST类型  lcq 2023-9-18
		{
			return;
		}

		Show_DataType_Val(pData, nRow, 1,iecfg_ST_FiberInDataType, &pIecCfgFiberPara->m_ntype,EndEditCell_FiberSetChangged);
		m_oFiberSetList.AddTail(pIecCfgFiberPara);
		UpdateData_ByDataType(pIecCfgFiberPara);
		UpdateDataFiberType();

	}
	else
	{
	if (pIecCfgFiberPara->m_strID.Find(_T("ST")) != -1)
	{
		Show_DataType_Val(pData, nRow, 1,iecfg_ST_FiberDataType, &pIecCfgFiberPara->m_ntype);
	} 
	else
	{
		Show_DataType_Val(pData, nRow, 1,iecfg_LC_FiberDataType, &pIecCfgFiberPara->m_ntype);
	}
	}
	

	nRow++;

}


void CIecCfgFiberSetGrid::UpdateData_ByDataType(CIecCfgFiberPara *pIecCfgFiberPara)
{
	if ((pIecCfgFiberPara->m_ntype == 1)|| (pIecCfgFiberPara->m_ntype == 2))
	{
		return;
	}

	POS pos = m_oFiberSetList.GetHeadPosition();
	CIecCfgFiberPara *pFiberPara = NULL;

	while (pos != NULL)
	{
		pFiberPara = (CIecCfgFiberPara *)m_oFiberSetList. GetNext(pos);
		
		if (pIecCfgFiberPara->m_strID == pFiberPara->m_strID)
		{
			continue;
		}
		
		if (pFiberPara->m_ntype == 0 )//20231103chenling ST1设置PPS不生效问题
		{
			pFiberPara->m_ntype = 1;
		}
	}
}


void CIecCfgFiberSetGrid::EndEditCell_FiberSetChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgFiberPara *pIecCfgFiberPara = (CIecCfgFiberPara *)pVCellData->pObj; 

	if (nCol == 1)
	{
		((CIecCfgFiberSetGrid*)pGrid)->UpdateData_ByDataType(pIecCfgFiberPara);
		((CIecCfgFiberSetGrid*)pGrid)->UpdateDataFiberType();
	}
}

void CIecCfgFiberSetGrid::UpdateDataFiberType()
{
	POS pos = m_oFiberSetList.GetHeadPosition();
	CIecCfgFiberPara *pFiberPara = NULL;
	int nRows = 0;
	
	while (pos != NULL)
	{
		pFiberPara = (CIecCfgFiberPara *)m_oFiberSetList. GetNext(pos);		
		Show_DataType_Val(pFiberPara, nRows, 1,iecfg_ST_FiberInDataType, &pFiberPara->m_ntype,EndEditCell_FiberSetChangged);
		nRows++;
	}
	

}

CDataType* CIecCfgFiberSetGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgFiberSetGrid::slot_doubleClicked( int nRow,int nCol )
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
}

void CIecCfgFiberSetGrid::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol != 0)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
	pItem->setText(strValue);

}


bool CIecCfgFiberSetGrid::eventFilter(QObject *obj, QEvent *event)
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

void CIecCfgFiberSetGrid::mousePressEvent(QMouseEvent * event)
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

