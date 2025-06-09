#include "QSttAntiShakeTimeTestItemsGroupGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../../../Module/SttGlobalDef.h"
#include"../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/XLanguageResource.h"
#include "../../../UI/AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#include <QComboBox>

QSttAntiShakeTimeTestItemsGroupGrid::QSttAntiShakeTimeTestItemsGroupGrid(QSttMacroParaEditViewAntiShakeTime *pShakeTime,QWidget *parent )
:QExBaseListGridBase(parent)
{
	m_pShakeTime = pShakeTime;
	connect(this,SIGNAL(sig_UpdateCheckState(CDataGroup*,int)),this,SLOT(slot_UpdateCheckState(CDataGroup*, int)));
}

QSttAntiShakeTimeTestItemsGroupGrid::~QSttAntiShakeTimeTestItemsGroupGrid()
{
	
}

void QSttAntiShakeTimeTestItemsGroupGrid::InitGrid()
{
	InitGridTitle();
	setFont(*g_pSttGlobalFont);
	verticalHeader()->setVisible(false);
	SetEditable(FALSE);

	m_pFileSelectDelegate = new /*QExBaseListCheckBoxDelegate*/QSttAntiShakeTimeCheckBoxDelegate(this);
	setItemDelegateForColumn(1,m_pFileSelectDelegate);

}

void QSttAntiShakeTimeTestItemsGroupGrid::InitGridTitle()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    // 禁止表头点击
    horizontalHeader()->setSectionsClickable(false);
    // 禁止表头大小修改
    horizontalHeader()->setSectionsMovable(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    // 禁止表头点击
    horizontalHeader()->setClickable(false);
    // 禁止表头大小修改
    horizontalHeader()->setMovable(false);
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif
	horizontalHeader()->setFont(*g_pSttGlobalFont);

	CString astrGridTitle[QSTTTESTITEMGRIDCOL] = {_T("编号"),_T("选择"),_T("间隔"),_T("YX通道"),
	_T("开出通道"),_T("初始状态"),_T("脉冲宽度(ms)"),_T("预计变位次数"),_T("实际变位次数"),_T("测试结果")};
	int iGridWidth[QSTTTESTITEMGRIDCOL]={60, 60, 70, 85, 95, 95, 125, 120, 120, 80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTTESTITEMGRIDCOL);
}

void QSttAntiShakeTimeTestItemsGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
	CDataGroup *pDataGroup = (CDataGroup*)pData;
	if (pDataGroup->GetHeadPosition() != NULL)
	{
		ShowChildren(pDataGroup, nRow);
		nRow++;
	}
}

void QSttAntiShakeTimeTestItemsGroupGrid::ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pDataGroup);
	POS pos = pDataGroup->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	long nIndex = 1;
	long nZero = 0;
	long nOne = 1;
	while (pos)
	{
		pDvmData = (CDvmData *)pDataGroup->GetNext(pos);
		CString str_ID[] = { STT_ANTISHAKE_TIME_INTERVAL_SELECT, STT_ANTISHAKE_TIME_TEST_OBJECT, STT_ANTISHAKE_TIME_BOUT_SET,
			STT_ANTISHAKE_TIME_INIT_STATE, STT_ANTISHAKE_TIME_PULSE_WIDTH, STT_ANTISHAKE_TIME_ESTIMATE_TIMES, 
			STT_ANTISHAKE_TIME_ACTUAL_TIMES, STT_ANTISHAKE_TIME_TEST_RESUL };
		if (pDvmData->m_strValue.IsEmpty())
		{
			nRow--;
			return;
		}

 		for(int i = 0; i < 8; ++i)
 		{
			if (pDvmData->m_strID == STT_ANTISHAKE_TIME_SELECT)
			{
				pDvmData = (CDvmData *)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);
				Show_Check(pDvmData, nRow, 1,&pDvmData->m_strValue, EndEditCell_CheckChanged);
			}
			else if (pDvmData->m_strID == str_ID[i])
			{
				CString strValue;
				strValue.Format(_T("%d"), nRow + 1); 
				Show_StaticString(pDvmData, nRow, 0, &strValue);   //编号

				if (pDvmData->m_strID == STT_ANTISHAKE_TIME_INTERVAL_SELECT )
				{
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(m_pShakeTime->m_pCmbIntervalSelect);
					QString strIndex = pComboBox->itemText(nIndex);
					CString strText(strIndex.toStdString().c_str()); 
					Show_StaticString(pDvmData, nRow, 2, &strText);
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_TEST_OBJECT )
				{
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(m_pShakeTime->m_pCmbTestObject);
					QString strIndex = pComboBox->itemText(nIndex);
					CString strText(strIndex.toStdString().c_str()); 
					Show_StaticString(pDvmData, nRow, 3, &strText);
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_BOUT_SET)
				{
				CDvmData* pBoutSet = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_BOUT_SET);
				if (pBoutSet != NULL) 
				{
						CString strBoutSet = pBoutSet->m_strValue;
						int nIndex = strBoutSet.toInt();
					m_pShakeTime->m_pCmbBoutSet->setItemData(nIndex, QVariant(0), Qt::UserRole - 1);
				}
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(m_pShakeTime->m_pCmbBoutSet);
					QString strIndex = pComboBox->itemText(nIndex);
					CString strText(strIndex.toStdString().c_str()); 
					Show_StaticString(pDvmData, nRow, 4, &strText);
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_INIT_STATE)
				{
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(m_pShakeTime->m_pCmbInitState);
					QString strIndex = pComboBox->itemText(nIndex);
					CString strText(strIndex.toStdString().c_str()); 
					Show_StaticString(pDvmData, nRow, 5, &strText);
				}
				else
				{
					Show_StaticString(pDvmData, nRow, nIndex, &pDvmData->m_strValue);
			}
		}
		}
		nIndex++;
	}
	m_pShakeTime->UpDateButtonState();
}


void QSttAntiShakeTimeTestItemsGroupGrid::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc/*, BOOL bEnable*/)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrCheck, pData,NULL, NULL);
	pVCellData->nVt = VCD_STRING;
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_CHECKBOX;
	pItem->m_pEditFunc = NULL;
	int nOne = 1;
	int nValue = pstrCheck->toInt();
	if (nValue == nOne)
	{
		pItem->setCheckState(Qt::Checked);
		m_pShakeTime->m_pBtnDeleteTestItem->setEnabled(true);
	} 
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}

	pItem->m_pEditFunc = pFunc;
	pVCellData->pFunc = pFunc;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QSttAntiShakeTimeTestItemsGroupGrid::slot_UpdateCheckState(CDataGroup *pDataGroup,int nRow)
{
	m_pShakeTime->UpDateButtonState();
	m_pShakeTime->SaveXmlParas();
}

void QSttAntiShakeTimeTestItemsGroupGrid::EndEditCell_CheckChanged(int nRow, int nCol, QGV_ITEM* pCell, QExBaseListGridBase* pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QSttAntiShakeTimeTestItemsGroupGrid *pOwnGrid = (QSttAntiShakeTimeTestItemsGroupGrid*)pGrid;

	if ((pVCellData->pString != NULL))
	{
		CDataGroup *pDataGroup = (CDataGroup*)pVCellData->pString;
		emit pOwnGrid->sig_UpdateCheckState(pDataGroup,nRow);
	}
}

QSttAntiShakeTimeCheckBoxDelegate::QSttAntiShakeTimeCheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{

}

QSttAntiShakeTimeCheckBoxDelegate::~QSttAntiShakeTimeCheckBoxDelegate()
{

}

//单击事件发生，值翻转
bool QSttAntiShakeTimeCheckBoxDelegate::editorEvent(QEvent * event,
											  QAbstractItemModel * model,
											  const QStyleOptionViewItem &/* option*/,
											  const QModelIndex & index)
{
	if(event->type()==QEvent::MouseButtonPress)
	{
		QVariant varValue = model->data(index,Qt::CheckStateRole);

		bool bValue=varValue.toBool();

		if(varValue.isValid())//如果当前值有效,则将当前状态取反
		{
			bValue=bValue?false:true;
		}
		else//否则将当前值置为1,即置为选择状态
		{
			bValue=true;
		}

		model->setData(index,bValue,Qt::CheckStateRole);
		//		index.setData();

		QGV_ITEM* pCurItem = GetCurrItem(index);

		if (pCurItem == NULL)
		{
			return true;
		}

		pCurItem->dwValue = bValue;

		if (pCurItem->lParam == 0)
		{
			return true;
		}

		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		ASSERT(pVCellData->pString);

		long nValue = CString_To_long(*(pVCellData->pString));
		if(nValue == 0)
		{
			*(pVCellData->pString)  = "1";
		} 
		else
		{ 
			*(pVCellData->pString)  = "0";
		}

		if (pCurItem->m_pEditFunc != NULL)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
			pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
			pExBaseListGridBase->OnDataSelChanged(index.row(),index.column());
		}

		return true;//I have handled the event
	}

	return false;


}
