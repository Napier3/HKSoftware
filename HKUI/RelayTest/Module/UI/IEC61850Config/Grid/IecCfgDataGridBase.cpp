#include "IecCfgDataGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDatasBase.h"

#include <QApplication>


#include "../../Module/XLangResource_Native.h"
#include "IecCfgChsGridBase.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "XMessageBox.h"

QFiberSelectedComBoxDelegBase::QFiberSelectedComBoxDelegBase(QObject *parent): QExBaseListComBoxDelegBase(parent)
{

}

QFiberSelectedComBoxDelegBase::~QFiberSelectedComBoxDelegBase()
{

}

void QFiberSelectedComBoxDelegBase::setEditorData(QWidget * editor, const QModelIndex &index)const
{
	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return;
	}

	if (pCurItem->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	ASSERT(pVCellData->pExBaseList != NULL);
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;


	CIecCfg6044CommonData *pCommonData = (CIecCfg6044CommonData *)pVCellData->pObj;
	CExBaseList* pIecCfgDatasBase = (CExBaseList*)pCommonData->GetParent();
	CExBaseObject *pObj = NULL;
	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	long nFiberIndex;
	QVector<long> oFiberVector; 

	POS pos = pIecCfgDatasBase->GetHeadPosition();
	while(pos)
	{
		pObj = pIecCfgDatasBase->GetNext(pos);

		if ((pObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)||
			(pObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA))
		{
			pIecCfg6044CommonData=(CIecCfg6044CommonData*)pObj;	
			if((pIecCfg6044CommonData != pCommonData)&& (pIecCfg6044CommonData->m_nUseFlag == 1))
			{
				nFiberIndex = pIecCfg6044CommonData->m_nFiberIndex;
				oFiberVector.push_back(nFiberIndex);
			}		
			}
		}

	bool bSel = false;//没有可选择
	CIecCfgDatasBase * ptemp = (CIecCfgDatasBase *)pIecCfgDatasBase;
	long nUseCount = ptemp->GetUseDatasCount(pCommonData->GetClassID());
	long nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST();
	if (nUseCount<nFiberCount)
	{
		bSel = true;
	}

	if (pDataType != NULL)
	{
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();

		long nIndex = 0,nCurrIndex = 0,nCurrIndex2 = 0;
		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);

			if (pDataTypeValue->m_strName == strItem)
			{
				nCurrIndex2 = nCurrIndex;
			}

			nIndex =CString_To_long(pDataTypeValue->m_strIndex);
			bool b = oFiberVector.contains(nIndex);

			if(pCommonData->m_nUseFlag == 0 && !bSel)
			{
				pComboBox->addItem(pDataTypeValue->m_strName);
				break;
			}
			if (b == false)
			{
				pComboBox->addItem(pDataTypeValue->m_strName);
				nCurrIndex++;
			}
		}

		if (nCurrIndex2 >= 0)
		{
			pComboBox->setCurrentIndex(nCurrIndex2);
		}	
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CIecCfgDataGridBase::CIecCfgDataGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pRefChsGrid = NULL;
	m_pCtrlBlockSelectDelegate = NULL;
	m_pDesMacAddrDelegate = NULL;
	m_pFiberSelected_DelegBase = NULL;
	m_pAppIDDelegate = NULL;
	m_pVersionNODelegate = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgDataGridBase::~CIecCfgDataGridBase()
{

}

void CIecCfgDataGridBase::InitGrid()
{
	InitGridTitle();
	m_pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pCtrlBlockSelectDelegate);
	//20230915 suyang 根据表格顺序，位置不一致
// 	m_pDesMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
// 	setItemDelegateForColumn(1,m_pDesMacAddrDelegate);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
//	SetAdjustBeginCol(0);
//	AutoAdjColWidth();
//	QExBaseListGridBase::InitGrid();
	connect(this,SIGNAL(cellDoubleClicked/*cellClicked*//*itemDoubleClicked*/(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_UpdateCheckState(CIecCfgDataBase*,int)),this,SLOT(slot_UpdateCheckState(CIecCfgDataBase*,int)));
}

void CIecCfgDataGridBase::InitGridTitle()
{
//	QExBaseListGridBase::InitGridTitle();
}

void CIecCfgDataGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
//	QExBaseListGridBase::ShowData(pData,nRow,bInsertRow);
}


CDataType* CIecCfgDataGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgDataGridBase::UpdateSelectedState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CIecCfgDataBase *pIecCfgDataBase = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行

	while (pos != NULL)
	{
		pIecCfgDataBase = (CIecCfgDataBase*)m_pDatas->GetNext(pos);

		if (IsCfgData(pIecCfgDataBase))
		{
			Show_Check(pIecCfgDataBase,nRowIndex,0,&pIecCfgDataBase->m_nUseFlag,EndEditCell_CheckChanged);
			nRowIndex++;
		}
	}
}

void CIecCfgDataGridBase::OnDataSelChanged(int nRow, int nCol)
{
	QExBaseListGridBase::OnDataSelChanged(nRow,nCol);
}

long iecfg_ValidateChsMiMax_GOOSE(long nGooseChs)
{
	if (nGooseChs < 1)
	{
		return 1;
	}

	if (nGooseChs > 256)		//程序中不做限制，解析后VM中再做限制
	{
		return 100;
	}

	return nGooseChs;
}

void CIecCfgDataGridBase::EndEditCell_ChNum (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVellData = (EXBASECELLDATA*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pnValue != NULL);
	ASSERT (pVellData->nVt == VCD_LONG);
	ASSERT (pVellData->pObj != NULL);
	CString strTmp = pCell->text();
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;

	long nChNum = CString_To_long(strTmp);
	long nNewChNUm = 1;

	if ((pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)||(pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGINDATA))
	{
		nNewChNUm = iecfg_ValidateChsMiMax_GOOSE(nChNum);
	}
	else
	{
		nNewChNUm = iecfg_ValidateChsMiMax(nChNum);
	}

	if (nChNum != nNewChNUm)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_rangenumber .GetString(), nChNum, nNewChNUm);
	}

	if (nNewChNUm == pIecCfgData->m_nChannelNum)
	{
		strTmp.Format(_T("%d"), pIecCfgData->m_nChannelNum);
		pCell->setText(strTmp);
		return;
	}

	//在此对通道数量进行有效性验证
	pIecCfgData->m_nChannelNum = nNewChNUm;
	strTmp.Format(_T("%d"), nNewChNUm);
	pCell->setText(strTmp);

	pIecCfgData->SetChannelNum(nNewChNUm);
	CIecCfgDataGridBase *pSelfObj = (CIecCfgDataGridBase *)pGrid;
	QExBaseListGridBase* pRefChsGrid = pSelfObj->GetRefChsGrid();

	if (pRefChsGrid != NULL)
	{
		pRefChsGrid->ShowDatas(pIecCfgData->m_pCfgChs);
	}

	//  	CIecCfgGinDataGrid *pIecCfgDataGrid = (CIecCfgGinDataGrid*)pGrid;
	//   	ASSERT (pIecCfgDataGrid->m_pRefChsGrid != NULL);
	//   	pIecCfgDataGrid->m_pRefChsGrid->ShowDatas(pIecCfgData->m_pCfgChs);
	//   	iecfg_SetModified(pIecCfgData);
}

void CIecCfgDataGridBase::EndEditCell_SampleDelay (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->nVt == VCD_LONG)
	{
		long nValue =  CString_To_long(pCell->text());

		if (nValue != *(pVCellData->pnValue))
		{
			if (nValue > 99999)
			{
				nValue = 99999;
				pCell->setText(_T("99999"));
			}

			if (nValue < 0)
			{
				nValue = 0;
				pCell->setText(_T("0"));
			}

			*(pVCellData->pnValue) = nValue;
			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		}
	}
}

void CIecCfgDataGridBase::slot_doubleClicked( int nRow,int nCol )
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
}

void CIecCfgDataGridBase::EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CIecCfgDataGridBase *pOwnGrid = (CIecCfgDataGridBase*)pGrid;

	if ((pVCellData->pObj != NULL))
	{
		CIecCfgDataBase *pIecCfgDataBase = (CIecCfgDataBase*)pVCellData->pObj;
		CIecCfgDatasBase *pIecCfgDatasBase = (CIecCfgDatasBase*)pIecCfgDataBase->GetParent();

		if (pIecCfgDatasBase != NULL)
		{
			if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
			{
				if(pIecCfgDataBase->m_nUseFlag)
				{
					long nUseCount = pIecCfgDatasBase->GetUseDatasCount(pIecCfgDataBase->GetClassID());
					long nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST();
					if (nUseCount>nFiberCount)
					{
						pIecCfgDataBase->m_nUseFlag = 0;
						emit pOwnGrid->sig_UpdateCheckState(pIecCfgDataBase,nRow);
						CString strTitle,strText;
						strTitle =  ("提示");
						strText = ("光口已全部占用，当前无可选择的光口！");
						CXMessageBox::information(NULL, strTitle,strText);	
					}
					else
					{
						emit pOwnGrid->sig_FiberSelUpdate(pIecCfgDataBase,nRow);
					}
				}
			}
			else
		{
			long nUseCount = pIecCfgDatasBase->GetUseDatasCount(pIecCfgDataBase->GetClassID());
			long nMaxCfgDataCount = pIecCfgDatasBase->GetMaxCfgDataCount(pIecCfgDataBase->GetClassID());

			if (nUseCount>nMaxCfgDataCount)
			{
				pIecCfgDataBase->m_nUseFlag = 0;
				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_maxblocks.GetString(),nUseCount,nMaxCfgDataCount);
				emit pOwnGrid->sig_UpdateCheckState(pIecCfgDataBase,nRow);
			}
		}

		}
	}
}



void CIecCfgDataGridBase::EndEditCell_ChLenthChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CIecCfgDataBase *pIecCfgDataBase = (CIecCfgDataBase*)pVCellData->pObj;
	CIecCfg6044CommonData *pIecCfg6044CommonData = (CIecCfg6044CommonData*)pIecCfgDataBase;//2024-1-19 zhouyangyong 先修改数据再刷新表格
	CExBaseObject *pObj = NULL;
	if (pIecCfgDataBase->m_pCfgChs != NULL)
	{
		POS pos = pIecCfgDataBase->m_pCfgChs->GetHeadPosition();
		while(pos != NULL)
		{
			pObj = pIecCfgDataBase->m_pCfgChs->GetNext(pos);
			CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pObj;
			if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue||pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
			{
				continue;
			}
			else
			{
				pIecCfg6044CommonCh->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
			}
		}
	}

	CIecCfgDataGridBase *pSelfObj = (CIecCfgDataGridBase*)pGrid;
	CIecCfgChsGridBase *pRefChsGrid = (CIecCfgChsGridBase*)pSelfObj->GetRefChsGrid();
	if (pRefChsGrid != NULL)
	{
		pRefChsGrid->UpdateChLengths(pIecCfgDataBase->m_pCfgChs, pIecCfg6044CommonData->m_nSmpDataLen);
	}
}

void CIecCfgDataGridBase::EndEditCell_TextChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);

	CString strText = pCell->text();

	if(strText == _T("-----"))
	{
		//20230111 suyang 针对MAC地址类型为空情况
		pCell->setText(*pVCellData->pString);
		return;
	}
	if (strText.IsEmpty())
	{
		pCell->setText(*pVCellData->pString);
		return;
	}

	if (*pVCellData->pString !=  pCell->text())
	{
		*pVCellData->pString =  pCell->text();

	}

}
void CIecCfgDataGridBase::slot_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow)
{
	Show_Check(pIecCfgDataBase,nRow,0,&pIecCfgDataBase->m_nUseFlag,EndEditCell_CheckChanged);
}

void CIecCfgDataGridBase::slot_FiberSelUpdate(CIecCfgDataBase *pIecCfgDataBase,int nRow){};

bool CIecCfgDataGridBase::eventFilter(QObject *obj, QEvent *event)
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

void CIecCfgDataGridBase::mousePressEvent(QMouseEvent * event)
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

