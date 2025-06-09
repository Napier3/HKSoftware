#include "SttPxEngineDsEditGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/DataMngr/Value.h"


//////////////////////////////////////////////////////////////////////////
//
CSttPxEngineDsEditGrid::CSttPxEngineDsEditGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttPxEngineDsEditGrid::~CSttPxEngineDsEditGrid()
{

}

CDvmValue* CSttPxEngineDsEditGrid::GetDataValue(CDvmData *pData)
{
	if (pData->GetCount() == 0)
	{
		return (CDvmValue*)pData->GetHead();
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *p = NULL;
	CString strRight;

	while (pos != NULL)
	{
		p = (CDvmValue *)pData->GetNext(pos);
		strRight = p->m_strID.right(2);

		if (strRight == "$t" || strRight == "$q")
		{
			continue;
		}

		return p;
	}

	return (CDvmValue*)pData->GetHead();
}


void CSttPxEngineDsEditGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
}

void CSttPxEngineDsEditGrid::InitGridTitle()
{
    CString astrGridTitle[4];
    astrGridTitle[0] = "数据名称";
    astrGridTitle[1] = "数据标识";
    astrGridTitle[2] = "数据值";
    astrGridTitle[3] = "";
	int iGridWidth[4]={300, 150, 120, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

//该表格显示数据集
void CSttPxEngineDsEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData*)pData;

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);

	if (pDvmData->m_strDataType.Find("OutMatr") > 0)
	{
		pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
		Show_Hex(pDvmData, nRow, 2, &pDvmData->m_dwReserved, 8);
	}
	else
	{
		Show_String(pDvmData, nRow, 2, &pDvmData->m_strValue, EndEditCell_CmdDataValue);
	}

	if (pDvmData->m_nChange == 1)
	{
		SetItemFgColour(nRow, 2, 255, 0, 0);
	}
	else
	{
		SetItemFgColour(nRow, 2, 0, 0, 0);
	}

	nRow++;
}

void CSttPxEngineDsEditGrid::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (pVCellData->pString == NULL)
	{
		return;
	}

    CString strText = pCell->text();
    if (*pVCellData->pString != strText)
	{
		*pVCellData->pString = pCell->text();
		CDvmData *pData = (CDvmData*)pVCellData->pObj;
		pData->m_nChange = 1;
		pGrid->SetItemFgColour(nRow, 2, 255, 0, 0);
	}
}

void CSttPxEngineDsEditGrid::EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();

		//emit ((CSttPxEngineDsEditGrid* )pGrid)->sig_PxEngine_UpdateData((CValue *)pVCellData->pObj);
	}
}

void CSttPxEngineDsEditGrid::EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

    CString strText = pCell->text();

    if (*pVCellData->pString != strText)
	{
        *pVCellData->pString = strText;

		//emit ((CSttPxEngineDsEditGrid* )pGrid)->sig_PxEngine_UpdateData((CValue *)pVCellData->pObj);
	}
}

void CSttPxEngineDsEditGrid::UpdateChangeState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	long nRow = 0;
	POS pos = m_pDatas->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pDatas->GetNext(pos);
	
		if (pData->m_nChange == 1)
		{
			SetItemFgColour(nRow, 2, 255, 0, 0);
		}
		else
		{
			SetItemFgColour(nRow, 2, 0, 0, 0);
		}
	}
}

