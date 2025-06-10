#include "QSttAntiShakeTimeTestItemsGroupGrid.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../Module/SttGlobalDef.h"
#include"../Module/XLangResource_Native.h"
#include "../../Module/XLanguage/XLanguageResource.h"
#include "../../../UI/AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#include <QComboBox>

QSttAntiShakeTimeTestItemsGroupGrid::QSttAntiShakeTimeTestItemsGroupGrid(QWidget *parent )
:QExBaseListGridBase(parent)
{
	m_pFileSelectDelegate = NULL;
	m_nRow = 0 ;
	connect(this,SIGNAL(sig_UpdateCheckState(CDataGroup*,int)),this,SLOT(slot_UpdateCheckState(CDataGroup*, int)));
}

QSttAntiShakeTimeTestItemsGroupGrid::~QSttAntiShakeTimeTestItemsGroupGrid()
{
	m_ObjectIdList.clear();
	m_oBoutSetList.clear();
}

void QSttAntiShakeTimeTestItemsGroupGrid::InitGrid()
{
	InitGridTitle();
// 	setFont(*g_pSttGlobalFont);
 	verticalHeader()->setVisible(false);
// 	horizontalHeader()->setFont(*g_pSttGlobalFont);
 	SetEditable(FALSE);

	m_pFileSelectDelegate = new /*QExBaseListCheckBoxDelegate*/QSttAntiShakeTimeCheckBoxDelegate(this);
	setItemDelegateForColumn(1,m_pFileSelectDelegate);

}

void QSttAntiShakeTimeTestItemsGroupGrid::InitGridTitle()
{
// 	// ��ֹ��ͷ���
// 	horizontalHeader()->setSectionsClickable(false);
// 	// ��ֹ��ͷ��С�޸�
// 	horizontalHeader()->setSectionsMovable(false);
// 	horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
 //	horizontalHeader()->setFont(*g_pSttGlobalFont);

	CString astrGridTitle[QSTTTESTITEMGRIDCOL] = {_T("���"),_T("ѡ��"),_T("���"),_T("YXͨ��"),
	_T("����ͨ��"),_T("��ʼ״̬"),_T("������(ms)"),_T("Ԥ�Ʊ�λ����"),_T("ʵ�ʱ�λ����"),_T("���Խ��")};
	int iGridWidth[QSTTTESTITEMGRIDCOL]={60, 60, 80, 140, 90, 90, 125, 125, 125, 80};
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
				Show_StaticString(pDvmData, nRow, 0, &strValue);   //���

				if (pDvmData->m_strID == STT_ANTISHAKE_TIME_INTERVAL_SELECT )
				{
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(g_pAntiShakeTime->m_pCmbIntervalSelect);
					QString strIndex = pComboBox->itemText(nIndex);
					CString strText(strIndex.toStdString().c_str()); 
					Show_StaticString(pDvmData, nRow, 2, &strText);
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_TEST_OBJECT )
				{
// 					int nIndex = pDvmData->m_strValue.toInt();
// 					QComboBox* pComboBox = static_cast<QComboBox*>(g_pAntiShakeTime->m_pCmbTestObject);
// 					QString strIndex = pComboBox->itemText(nIndex);
// 					CString strText(strIndex.toStdString().c_str()); 
					CDvmData *pCurrData = (CDvmData *)(g_pAntiShakeTime->m_oTestObjectList).FindByID(pDvmData->m_strValue);
					if(pCurrData != NULL)
					{
					Show_StaticString(pDvmData, nRow, 3, &/*strText*/pCurrData->m_strName);
					}
					if(!pDvmData->m_strValue.isEmpty())
					{
						m_ObjectIdList.append(pDvmData->m_strValue);
					}
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_BOUT_SET)
				{
					CDvmData* pBoutSet = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_BOUT_SET);
					if (pBoutSet != NULL) 
					{
						CString strBoutSet = pBoutSet->m_strValue;
						int nIndex = strBoutSet.toInt();
						//g_pAntiShakeTime->m_pCmbBoutSet->setItemData(nIndex, QVariant(0), Qt::UserRole - 1);	
					}
// 					int nIndex = pDvmData->m_strValue.toInt();
// 					QComboBox* pComboBox = static_cast<QComboBox*>(g_pAntiShakeTime->m_pCmbBoutSet);
// 					QString strIndex = pComboBox->itemText(nIndex);
// 					CString strText(strIndex.toStdString().c_str()); 

					CString strValue = pDvmData->m_strValue;
					CString strName,strID;
					strName.Format(_T("����%d"),strValue.toInt());
					strID.Format(_T("Bout%d"),strValue.toInt());

					if (!strID.isEmpty())
					{
						m_oBoutSetList.append(strID);
					}
// 					strValue = strValue.right(1);
// 					strValue.Format(_T("����%d"),strValue.toInt());
					Show_StaticString(pDvmData, nRow, 4, &strName);	
				}
				else if (pDvmData->m_strID == STT_ANTISHAKE_TIME_INIT_STATE)
				{
					int nIndex = pDvmData->m_strValue.toInt();
					QComboBox* pComboBox = static_cast<QComboBox*>(g_pAntiShakeTime->m_pCmbInitState);
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
	g_pAntiShakeTime->UpDateButtonState();
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
		g_pAntiShakeTime->m_pBtnDeleteTestItem->setEnabled(true);
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
	g_pAntiShakeTime->UpDateButtonState();
	//g_pAntiShakeTime->SaveXmlParas();
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

int QSttAntiShakeTimeTestItemsGroupGrid::GetGridRow( int nIndex )
{
	int nRowIndex = 0;

	for (int nRow = 0;nRow <= rowCount();nRow++)
	{
		QGV_ITEM *pItem = GetCell(nRow,1); 

		if (pItem == NULL)
		{
			continue;
		}

		if (pItem->checkState() != Qt::Unchecked)
		{	
			nRowIndex ++;

			if (nRowIndex == nIndex)
			{
				return nRow;
			}
		}
	}
	return -1;
}


void QSttAntiShakeTimeTestItemsGroupGrid::UpdateDatas( CDvmValues *pValues,CExBaseList *pResultList,CString strItemID)
{
	if (pResultList == NULL || pValues == NULL)
	{
		return;
	}

	int nRowIndex = (strItemID == _T("AntiShakeTimeTest$ReadCount")) ? 1 : strItemID.right(1).toInt() + 1;

	int nRow = GetGridRow(nRowIndex);	
	if (nRow == -1)
		return;

	CString strID = m_ObjectIdList.at(nRow);

	CDvmData *pDvmData = NULL;
	POS pos = pResultList->GetHeadPosition();
	while (pos != NULL)
	{
		pDvmData = (CDvmData*)pResultList->GetNext(pos);
		if (pDvmData == NULL )
		{
			continue;
		}

		if (strID == pDvmData->m_strID)
		{
			Show_StaticString(pDvmData, nRow, 8, &pDvmData->m_strValue);
			break;
		}
	}

	CDvmValue *pDvmValue = (CDvmValue*)pValues->FindByID(_T("RsltDsc"));
	if (pDvmValue)
	{
		Show_StaticString(pDvmData, nRow, 9, &pDvmValue->m_strValue);
	}
}

QSttAntiShakeTimeCheckBoxDelegate::QSttAntiShakeTimeCheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{

}

QSttAntiShakeTimeCheckBoxDelegate::~QSttAntiShakeTimeCheckBoxDelegate()
{

}

//�����¼�������ֵ��ת
bool QSttAntiShakeTimeCheckBoxDelegate::editorEvent(QEvent * event,
											  QAbstractItemModel * model,
											  const QStyleOptionViewItem &/* option*/,
											  const QModelIndex & index)
{
	if(event->type() == QEvent::MouseButtonPress)
	{
		QVariant varValue = model->data(index,Qt::CheckStateRole);

		bool bValue = varValue.toBool();

		if(varValue.isValid())//�����ǰֵ��Ч,�򽫵�ǰ״̬ȡ��
		{
			bValue = bValue?false:true;
		}
		else//���򽫵�ǰֵ��Ϊ1,����Ϊѡ��״̬
		{
			bValue = true;
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
			*(pVCellData->pString)  = _T("1");
		} 
		else
		{ 
			*(pVCellData->pString)  = _T("0");
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
