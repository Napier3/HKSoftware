#include "QSttBinRecordModuleGrid.h"

#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "../../SmartCap/61850Cap/CapDevice/CapDeviceRcdCh.h"
#include "../QSttBinRecordDlg.h"
#include "../SttBinRecordDefine.h"
QSttBinRecordModuleGrid::QSttBinRecordModuleGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{
}

QSttBinRecordModuleGrid::~QSttBinRecordModuleGrid()
{

}

void QSttBinRecordModuleGrid::InitGrid(CCapDeviceMngr *pCapDeviceAll)
{
	m_pCapDeviceAll = pCapDeviceAll;
	InitGridTitle();
	setFont(*g_pSttGlobalFont);
	verticalHeader()->setVisible(false);
	SetEditable(FALSE);
	m_pFileSelectDelegate = new QSttBinRecordModuleCheckBoxDelegate(this);
	setItemDelegateForColumn(STT_BINRECORD_ID_NONE, m_pFileSelectDelegate);
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slot_CellChanged(int, int)));
}

void QSttBinRecordModuleGrid::InitGridTitle()
{
	CString astrGridTitle[QSTTBINRECORDMODULEGRIDCOL] = { /*_T("���")*/g_sLtxt_SICDGSerial, /*_T("ѡ��")*/g_sLtxt_SICDSelect, /*_T("�������")*/g_sLangTxt_BinRecord_PlugName, /*_T("���λ��")*/g_sLangTxt_BinRecord_PlugPOS, /*_T("ͨ������")*/g_sLangTxt_BinRecord_ChannelNum,
	_T("")};
	int iGridWidth[QSTTBINRECORDMODULEGRIDCOL] = { 50, 50, 200, 200, 200, 150 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTBINRECORDMODULEGRIDCOL);
}

void QSttBinRecordModuleGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
	CCapDeviceRecord *pDev = (CCapDeviceRecord*)pData;

	CString strModulePos, strChannelNum, strValue, strUseFlag;
	strModulePos.Format("%d", pDev->m_nModulePos);
	strChannelNum.Format("%d", pDev->m_nChannelNum);
	strUseFlag.Format(_T("%d"), pDev->m_nUseFlag);
	strValue.Format(_T("%d"), nRow + STT_BINRECORD_ID_NONE);
	
	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NZERO, &strValue);   //���
	Show_Check(pData, nRow, STT_BINRECORD_ID_NONE, &pDev->m_nUseFlag, EndEditCell_CheckChanged);
	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, &pData->m_strName);

	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTHREE, strModulePos);
	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NFOUR, strChannelNum);
	nRow++;
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slot_BinRecordModuleGrid(int, int)));
}


void QSttBinRecordModuleGrid::EndEditCell_CheckChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QSttBinRecordModuleGrid *pOwnGrid = (QSttBinRecordModuleGrid*)pGrid;

	if (pVCellData->pnValue != NULL)
	{
		int nState = *pVCellData->pnValue;
		emit pOwnGrid->sig_CheckBoxValue(nRow, nState);  //��ȡcheckbox״̬
	}
}

void QSttBinRecordModuleGrid::slot_BinRecordModuleGrid(int nRow, int nCol)
{
	CCapDeviceRecord *pDevice = (CCapDeviceRecord *)m_pCapDeviceAll->GetAtIndex(nRow);

	if (pDevice != NULL && m_pBinRecordChsGrid != NULL)
	{
		g_pBinRecord->m_pSttBinRecordChsGrid->ShowDatas(pDevice);
	}
}

void QSttBinRecordModuleGrid::slot_CellChanged(int nRow, int nCol)
{

}


QSttBinRecordModuleCheckBoxDelegate::QSttBinRecordModuleCheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{

}

QSttBinRecordModuleCheckBoxDelegate::~QSttBinRecordModuleCheckBoxDelegate()
{

}

//�����¼�������ֵ��ת
bool QSttBinRecordModuleCheckBoxDelegate::editorEvent(QEvent * event,
	QAbstractItemModel * model,
	const QStyleOptionViewItem &/* option*/,
	const QModelIndex & index)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QVariant varValue = model->data(index, Qt::CheckStateRole);

		bool bValue = varValue.toBool();

		if (varValue.isValid())//�����ǰֵ��Ч,�򽫵�ǰ״̬ȡ��
		{
			bValue = bValue ? false : true;
		}
		else//���򽫵�ǰֵ��Ϊ1,����Ϊѡ��״̬
		{
			bValue = true;
		}

		model->setData(index, bValue, Qt::CheckStateRole);
		QGV_ITEM* pCurItem = GetCurrItem(index);

		if (pCurItem == NULL)
		{
			return true;
		}

		pCurItem->dwValue = bValue;

		if (pCurItem->lParam == STT_BINRECORD_ID_NZERO)
		{
			return true;
		}

		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		ASSERT(pVCellData->pnValue);

		if (*(pVCellData->pnValue) == STT_BINRECORD_ID_NONE)
		{
			*(pVCellData->pnValue) = STT_BINRECORD_ID_NZERO;
		}
		else if (*(pVCellData->pnValue) == STT_BINRECORD_ID_NZERO)
		{
			*(pVCellData->pnValue) = STT_BINRECORD_ID_NONE;
		}

		if (pCurItem->m_pEditFunc != NULL || pCurItem->nDataType == QT_GVET_CHECKBOX)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
			pCurItem->m_pEditFunc(index.row(), index.column(), pCurItem, pExBaseListGridBase);
		}
		//long nValue = CString_To_long(*(pVCellData->pString));

		return true;
	}
	return false;
}
