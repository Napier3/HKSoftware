#include "SttCmdWzdDsEditGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/DataMngr/Value.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

#include "../../XLangResource_Native.h"

QSttCmdWzdDsEditGrid_CheckBoxDelegate::QSttCmdWzdDsEditGrid_CheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{
	CString strEmptyPath;
	strEmptyPath =  _P_GetResourcePath();
	strEmptyPath += _T("Empty.png");
	m_oEmptyPixmap.load(strEmptyPath);
	m_oEmptyPixmap.scaled(20,20);
}

QSttCmdWzdDsEditGrid_CheckBoxDelegate::~QSttCmdWzdDsEditGrid_CheckBoxDelegate()
{

}

// 移动到CDvmData类  shaolei 2023-7-28
// CDvmValue* QSttCmdWzdDsEditGrid_CheckBoxDelegate::GetDataValue(CDvmData *pData) const
// {
// 	if (pData->GetCount() == 0)
// 	{
// 		return (CDvmValue*)pData->GetHead();
// 	}
// 
// 	POS pos = pData->GetHeadPosition();
// 	CDvmValue *p = NULL;
// 	CString strRight;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmValue *)pData->GetNext(pos);
// 		strRight = p->m_strID.right(2);
// 
// 		if (strRight == "$t" || strRight == "$q")
// 		{
// 			continue;
// 		}
// 
// 		return p;
// 	}
// 
// 	return (CDvmValue*)pData->GetHead();
// }

//鼠标单击单元格的时候，重绘事件触发
void QSttCmdWzdDsEditGrid_CheckBoxDelegate::paint(QPainter * painter,
													 const QStyleOptionViewItem & option,
													 const QModelIndex & index) const
{
	CDvmData *pDvmData = NULL;
	QGV_ITEM* pCurItem = GetCurrItem(index);
	BOOL bTypeBool = FALSE;

	if ((pCurItem != NULL)&&(pCurItem->lParam != 0))
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		pDvmData = (CDvmData *)pVCellData->pObj;
		CDvmValue *pFind = pDvmData->GetDataValue();   //返回除$t  $q之外的第一个pDvmData子对象

		if (pFind == NULL)
		{
			if (pDvmData->m_strDataType == _T("BOOL"))
			{
				bTypeBool = TRUE;
			}
		}
		else if (pFind->m_strDataType == _T("BOOL"))
		{
			bTypeBool = TRUE;
		}
	}

	if (!bTypeBool)
	{
		return;
	}

	bool bChecked = index.model()->data(index, Qt::CheckStateRole).toBool();//绘制图片
	QRect rect = option.rect;
	QPoint pt = rect.center();

	if(bChecked)
	{
		pt -= QPoint(m_oSelectedPixmap.width()/2,m_oSelectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oSelectedPixmap);
	}
	else
	{
		pt -= QPoint(m_oUnselectedPixmap.width()/2,m_oUnselectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oUnselectedPixmap);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttCmdWzdDsShowGrid::CSttCmdWzdDsShowGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pDataset = NULL;
}

CSttCmdWzdDsShowGrid::~CSttCmdWzdDsShowGrid()
{

}

void CSttCmdWzdDsShowGrid::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
}

void CSttCmdWzdDsShowGrid::InitGridTitle()
{
	CString astrGridTitle[4] = {/*"名称"*/g_sLangTxt_Name, "ID", /*"数值"*/g_sLangTxt_Value, ""};
	int iGridWidth[4]={300, 150, 120, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

//该表格显示数据集
void CSttCmdWzdDsShowGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);
	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strValue);

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//
CSttCmdWzdDsEditGrid::CSttCmdWzdDsEditGrid(QWidget* pparent):CSttCmdWzdDsShowGrid(pparent)
{
	m_nTypeRwOptr = COMMCMD_RWOPTR_READ_INT;
	m_pValues = NULL;
	m_pDataGroupBK = NULL;
}

CSttCmdWzdDsEditGrid::~CSttCmdWzdDsEditGrid()
{

}

// 移动到CDvmData类  shaolei  2023-7-28
// CDvmValue* CSttCmdWzdDsEditGrid::GetDataValue(CDvmData *pData)
// {
// 	if (pData->GetCount() == 0)
// 	{
// 		return (CDvmValue*)pData->GetHead();
// 	}
// 
// 	POS pos = pData->GetHeadPosition();
// 	CDvmValue *p = NULL;
// 	CString strRight;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmValue *)pData->GetNext(pos);
// 		strRight = p->m_strID.right(2);
// 
// 		if (strRight == "$t" || strRight == "$q")
// 		{
// 			continue;
// 		}
// 
// 		return p;
// 	}
// 
// 	return (CDvmValue*)pData->GetHead();
// }


void CSttCmdWzdDsEditGrid::InitTypeRwOptr(const CString &strRwOptr)
{
	if (strRwOptr == COMMCMD_RWOPTR_READ)
	{
		m_nTypeRwOptr = COMMCMD_RWOPTR_READ_INT;
	}
	else if (strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		m_nTypeRwOptr = COMMCMD_RWOPTR_WRITE_INT;
	}
	else if (strRwOptr == COMMCMD_RWOPTR_REGISTER)
	{
		m_nTypeRwOptr = COMMCMD_RWOPTR_REGISTER_INT;
	}
	else
	{
		m_nTypeRwOptr = COMMCMD_RWOPTR_READ_INT;
	}
}

CValue* CSttCmdWzdDsEditGrid::AddDataToSttCommCmd(CDvmData *pData)
{
	if (m_pValues == NULL)
	{
		return NULL;
	}

	CValue *pValue = (CValue*)m_pValues->FindByID(pData->m_strID);

	if (pValue == NULL)
	{
		pValue = m_pValues->AddValue(pData->m_strID, pData->m_strValue);
	}
	else
	{
		pValue->m_strValue = pData->m_strValue;
	}

	return pValue;
}

void CSttCmdWzdDsEditGrid::FillCmdValues()
{
	if(!m_pDatas)
	{
		return;
	}

	POS pos = m_pDatas->GetHeadPosition();
	while (pos)
	{
		CDvmData* pDvmData = (CDvmData*)m_pDatas->GetNext(pos);
		CDvmValue* pDvmValue = pDvmData->GetDataValue();
		if(pDvmValue->m_strDataType == "BOOL")
		{
			CValue* pValue = (CValue*)m_pValues->FindByID(pDvmData->m_strID);
			if (!pValue)
			{
				pValue = m_pValues->AddValue(pDvmData->m_strID, pDvmValue->m_strValue);
			}

			pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		}
	}
}

void CSttCmdWzdDsEditGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
// 	m_pValue_Bool = new QSttCmdWzdDsEditGrid_CheckBoxDelegate(this);
// 	setItemDelegateForColumn(1,m_pValue_Bool);
}

void CSttCmdWzdDsEditGrid::InitGridTitle()
{
	if (m_nTypeRwOptr == COMMCMD_RWOPTR_WRITE_INT)
	{
		CString astrGridTitle[8] = {/*"名称"*/g_sLangTxt_Name, /*"标识",*/ /*"数值"*/g_sLangTxt_Value, /*"修改为"*/g_sLangTxt_Native_modifyto, /*"单位"*/g_sLangTxt_Unit, /*"最小值"*/g_sLangTxt_MinValue, /*"最大值"*/g_sLangTxt_MaxValue, /*"步长"*/g_sLangTxt_Step, ""};
		int iGridWidth[8]={200, 120, 120, 40, 100, 100, 100, 10};
		QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 8);
	}
	else
	{
		CString astrGridTitle[7] = {/*"名称"*/g_sLangTxt_Name, /*"标识",*/ /*"数值"*/g_sLangTxt_Value, /*"单位"*/g_sLangTxt_Unit, /*"最小值"*/g_sLangTxt_MinValue, /*"最大值"*/g_sLangTxt_MaxValue, /*"步长"*/g_sLangTxt_Step, ""};
		int iGridWidth[7]={200, 120, 40, 100, 100, 100, 10};
		QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 7);
	}
}

//对于读指令
void CSttCmdWzdDsEditGrid::ShowData_Read(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);   //名称
	//Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);

	CDvmValue *pFind = pDvmData->GetDataValue();   //返回除$t  $q之外的第一个pDvmData子对象

	if (pFind == NULL)
	{
		pDvmData->m_dwItemData = (unsigned long)pData;
		if (pDvmData->m_strDataType == "BOOL")
		{
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);

			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), NULL, FALSE);   //数值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMax);   //最大值
			Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strMin);   //最小值
		}
		else
		{
			//跳闸矩阵，只能通过ID判断。跳闸矩阵最大65535，因此最大长度2个字节。
			if (pDvmData->m_strID.Find("OUTMATR") > 0)
			{
				pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
				DWORD dwMax = CString_To_long(pDvmData->m_strMax);
				DWORD dwMin = CString_To_long(pDvmData->m_strMin);

				Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, FALSE);   //数值
				Show_Hex(pDvmData, nRow, 4, &dwMax, 2, FALSE);   //最大值
				Show_Hex(pDvmData, nRow, 3, &dwMin, 2, FALSE);   //最小值	
			}
			else
			{
				Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strValue);//数值
				Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMax);   //最大值
				Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strMin);   //最小值
			}
		}
	}
	else
	{
		pDvmData->m_dwItemData = (unsigned long)pFind;

		if (pFind->m_strDataType == "BOOL")
		{
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);

			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), NULL, FALSE);//数值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMax);//最大值
			Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strMin);//最小值
		}
		else if (pFind->m_strID.Find("OUTMATR") > 0)
		{
			//跳闸矩阵，只能通过ID判断。跳闸矩阵最大65535，因此最大长度2个字节。
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
			DWORD dwMax = CString_To_long(pDvmData->m_strMax);
			DWORD dwMin = CString_To_long(pDvmData->m_strMin);

			Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, FALSE);//数值
			Show_Hex(pDvmData, nRow, 4, &dwMax, 2, FALSE);//最大值
			Show_Hex(pDvmData, nRow, 3, &dwMin, 2, FALSE);//最小值	
		}
		else
		{
			Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strValue);//数值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMax);//最大值
			Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strMin);//最小值
		}
	}

	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strUnit);   //单位
	Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strStep);   //步长
	nRow++;
}

void CSttCmdWzdDsEditGrid::ShowData_Write(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;
	CDvmData* pDvmDataBK = pDvmData;

	if (m_pDataGroupBK != NULL)
	{
		CDataGroup* pDataGroupBK = (CDataGroup*)m_pDataGroupBK->GetHead();
		pDvmDataBK = (CDvmData*)pDataGroupBK->FindByID(pDvmData->m_strID);
	}
	
	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);   //名称
	//Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);

	CDvmValue *pFind = pDvmData->GetDataValue();   //返回除$t  $q之外的第一个pDvmData子对象

	if (pFind == NULL)
	{
		pDvmData->m_dwItemData = (unsigned long)pData;
		if (pDvmData->m_strDataType == "BOOL")
		{
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
			//Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), EndEditCell_CmdDataValue_BOOL);  //数值
			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmDataBK->m_dwReserved), NULL, FALSE);   //数值
			ShowData_CmdValue_BOOL(pDvmData, nRow);   //修改为

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);   //最大值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);   //最小值
		}
		else
		{
			//跳闸矩阵，只能通过ID判断。跳闸矩阵最大65535，因此最大长度2个字节。
			if (pDvmData->m_strID.Find("OUTMATR") > 0)
			{
				pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
				DWORD dwMax = CString_To_long(pDvmData->m_strMax);
				DWORD dwMin = CString_To_long(pDvmData->m_strMin);

				//Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, TRUE, TRUE, EndEditCell_CmdDataValue_Hex);//数值
				Show_Hex(pDvmData, nRow, 1, &pDvmDataBK->m_dwReserved, 2, FALSE);   //数值
				ShowData_CmdValue_Hex(pDvmData, nRow);   //修改为

				Show_Hex(pDvmData, nRow, 5, &dwMax, 2, FALSE);   //最大值
				Show_Hex(pDvmData, nRow, 4, &dwMin, 2, FALSE);   //最小值
			}
			else
			{
				//Show_String(pDvmData, nRow, 1, &pDvmData->m_strValue, EndEditCell_CmdDataValue);   //数值
				Show_StaticString(pDvmData, nRow, 1, &pDvmDataBK->m_strValue);//数值
				ShowData_CmdValue_String(pDvmData, nRow);  //修改为

				Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);   //最大值
				Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);   //最小值
			}
		}
	}
	else
	{
		pDvmData->m_dwItemData = (unsigned long)pFind;

		if (pFind->m_strDataType == "BOOL")
		{
			pDvmDataBK->m_dwReserved = pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);

			//Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), EndEditCell_CmdDataValue_BOOL);//数值
			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmDataBK->m_dwReserved), NULL, FALSE);//数值
			ShowData_CmdValue_BOOL(pDvmData, nRow);   //修改为

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);//最大值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);//最小值

			pDvmData->m_nChange = 1;
		}
		else if (pFind->m_strID.Find("OUTMATR") > 0)
		{
			//跳闸矩阵，只能通过ID判断。跳闸矩阵最大65535，因此最大长度2个字节。
			pDvmDataBK->m_dwReserved = pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
			DWORD dwMax = CString_To_long(pDvmData->m_strMax);
			DWORD dwMin = CString_To_long(pDvmData->m_strMin);

			//Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, TRUE, TRUE, EndEditCell_CmdDataValue_Hex);//数值
			Show_Hex(pDvmData, nRow, 1, &pDvmDataBK->m_dwReserved, 2, FALSE);//数值
			ShowData_CmdValue_Hex(pDvmData, nRow);   //修改为

			Show_Hex(pDvmData, nRow, 5, &dwMax, 2, FALSE);//最大值
			Show_Hex(pDvmData, nRow, 4, &dwMin, 2, FALSE);//最小值
		}
		else
		{
			//Show_String(pDvmData, nRow, 1, &pDvmData->m_strValue, EndEditCell_CmdDataValue);//数值
			Show_StaticString(pDvmData, nRow, 1, &pDvmDataBK->m_strValue);//数值
			ShowData_CmdValue_String(pDvmData, nRow);  //修改为

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);//最大值
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);//最小值
		}
	}

	Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strUnit);   //单位
	Show_StaticString(pDvmData, nRow, 6, &pDvmData->m_strStep);   //步长

	nRow++;
}

void CSttCmdWzdDsEditGrid::ShowData_CmdValue_String(CDvmData *pData, int& nRow)
{
	if (m_pValues != NULL)
	{
		CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

		if (pValue != NULL)
		{
			//Show_StaticString(pValue, nRow, 2, &pValue->m_strValue);  //修改为
			Show_String(pValue, nRow, 2, &pValue->m_strValue, EndEditCell_CmdDataValue_CmdValue);   //修改为
		}
		else
		{
			CString strValue;
			Show_String(NULL, nRow, 2, &strValue, EndEditCell_CmdDataValue_CmdValue);
		}
	}
	else
	{
		if (pData->m_nChange == 1)
		{
			Show_String(pData, nRow, 2, &pData->m_strValue, EndEditCell_Init_String);
		}
		else
		{
			CString strValue;
			Show_String(pData, nRow, 2, &strValue, EndEditCell_Init_String);
		}
		//Show_String(pData, nRow, 2, &pData->m_strValue);
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_Init_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CString strCurValue = pCell->text();

	if (pVCellData->pObj != NULL)
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;
		
		if (! strCurValue.IsEmpty())
		{
			pData->m_strValue = strCurValue;
			pData->m_nChange = 1;
		}	
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_Init_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);

	if (pVCellData->pObj != NULL)
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;
		bool bUnchecked = pCell->checkState() == Qt::Unchecked;
		if((bUnchecked && pData->m_strValue == "0")
			|| (!bUnchecked && pData->m_strValue == "1"))
		{
			//初始化
			return;
		}

		QGV_ITEM *pItem = pGrid->GetCell(nRow, nCol);

		if (bUnchecked)
		{
			*pVCellData->pnValue = 0;
			pData->m_strValue = _T("0");
		}
		else
		{
			*pVCellData->pnValue = 1;
			pData->m_strValue = _T("1");
		}

// 		pData->m_dwReserved = pItem->checkState();
// 		pData->m_strValue = QString::number(pData->m_dwReserved);
		pData->m_nChange = 1;
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_Init_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);

	if (pVCellData->pObj != NULL)
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;
		pData->m_dwReserved = pCell->text().toULong(0, 10);
		pData->m_strValue = QString::number(pData->m_dwReserved, 16);
	}
}

void CSttCmdWzdDsEditGrid::ShowData_CmdValue_BOOL(CDvmData *pData, int& nRow)
{
	if (m_pValues != NULL)
	{
		CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

		if (pValue != NULL)
		{
			pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
			Show_Check(pValue, nRow, 2, (long*)(&pValue->m_dwReserved), EndEditCell_CmdDataValue_CmdValue_BOOL); //修改为
		}
		else
		{
			DWORD dwValue = CString_To_long(pData->m_strValue);
			Show_Check(NULL, nRow, 2, (long*)(&dwValue), EndEditCell_CmdDataValue_CmdValue_BOOL);   //修改为
		}
	}
	else
	{
		pData->m_dwReserved = CString_To_long(pData->m_strValue);
		Show_Check(pData, nRow, 2, (long*)(&pData->m_dwReserved), EndEditCell_Init_BOOL);
	}
}

void CSttCmdWzdDsEditGrid::ShowData_CmdValue_Hex(CDvmData *pData, int& nRow)
{
	if (m_pValues != NULL)
	{
		CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

		if (pValue != NULL)
		{
			pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
			Show_Hex(pValue, nRow, 2, &pValue->m_dwReserved, 2, TRUE, TRUE, EndEditCell_CmdDataValue_CmdValue_Hex); //修改为
		}
		else
		{
			DWORD dwValue = CString_To_long(pData->m_strValue);
			Show_Hex(NULL, nRow, 2, &dwValue, 2, TRUE, TRUE, EndEditCell_CmdDataValue_CmdValue_Hex); //修改为
		}
	}
	else
	{
		pData->m_dwReserved = pData->m_strValue.toULong(0, 10);
		Show_Hex(pData, nRow, 2, &pData->m_dwReserved, 4, TRUE, TRUE, EndEditCell_Init_Hex);
	}
}

void CSttCmdWzdDsEditGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);

		if (m_nTypeRwOptr == COMMCMD_RWOPTR_WRITE_INT)
		{
			ShowData_Write(pObj, nRowIndex, FALSE);
		}
		else
		{
			ShowData_Read(pObj, nRowIndex, FALSE);
		}
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();

		emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData((CDvmData *)pVCellData->pObj);
		CValue* pValue = ((CSttCmdWzdDsEditGrid* )pGrid)->AddDataToSttCommCmd((CDvmData *)pVCellData->pObj);

		//pGrid->Show_StaticString(pValue, nRow, 2, &pValue->m_strValue);  //修改为
		//pGrid->Show_String(pValue, nRow, 2, &pValue->m_strValue, EndEditCell_CmdDataValue_CmdValue); 
	}
}

/*
enum CheckState {
   Unchecked,
   PartiallyChecked,
   Checked
};
*/
void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pnValue != pCell->checkState())
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (pCell->checkState() == Qt::Unchecked)
		{
			*pVCellData->pnValue = 0;
			pData->m_strValue = _T("0");
		}
		else
		{
			*pVCellData->pnValue = 1;
			pData->m_strValue = _T("1");
		}

		emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData(pData);
		CValue* pValue = ((CSttCmdWzdDsEditGrid* )pGrid)->AddDataToSttCommCmd(pData);

		//pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		//pGrid->Show_Check(pValue, nRow, 2, (long*)(&pValue->m_dwReserved), NULL, FALSE);   //修改为
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strCurValue = pCell->text();

	DWORD dwCurValue = 0;

	if ((strCurValue.Find("0X")== -1)&&(strCurValue.Find("0x")== -1))
	{
		dwCurValue = strCurValue.toULong(0,10);
	}
	else
	{
		dwCurValue = strCurValue.toULong(0,16);
	}

	if (*pVCellData->pdwValue != dwCurValue)
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;
		*pVCellData->pdwValue = dwCurValue;

		pData->m_strValue.Format(_T("%d"), dwCurValue);
		emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData(pData);
		CValue* pValue = ((CSttCmdWzdDsEditGrid* )pGrid)->AddDataToSttCommCmd(pData);

		//pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		//pGrid->Show_Hex(pValue, nRow, 2, &pValue->m_dwReserved, 2, FALSE);   //修改为
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue_CmdValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	//ASSERT(pVCellData->pObj != NULL);
	CValue* pValue = NULL;
	CString strCurValue = pCell->text();
	CValues *pValues = ((CSttCmdWzdDsEditGrid* )pGrid)->m_pValues;

	QGV_ITEM *pItem = NULL;
	if (pVCellData->pObj == NULL)
	{
		//说明是第一次编辑，还没有添加对象到m_pValues
		pItem = pGrid->GetCell(nRow, 1);
		pVCellData = (PEXBASECELLDATA)pItem->lParam;
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (pValues->FindByID(pData->m_strID) == NULL)
		{
			pValue = pValues->AddValue(pData->m_strID, strCurValue);
		}
		
		pGrid->Show_String(pValue, nRow, 2, &pValue->m_strValue, EndEditCell_CmdDataValue_CmdValue); 
	}
	else
	{
		pValue = (CValue*)pVCellData->pObj;
	}

	pItem = pGrid->GetCell(nRow, nCol);
	pVCellData = (PEXBASECELLDATA)pItem->lParam;
	if (*pVCellData->pString != strCurValue)
	{
		*pVCellData->pString = strCurValue;

		emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData_Value(pValue);

		if (strCurValue.IsEmpty())
		{
			pValues->Delete(pValue);
			pGrid->Show_String(NULL, nRow, 2, &strCurValue, EndEditCell_CmdDataValue_CmdValue);
		}
	}
}

void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue_CmdValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	//ASSERT(pVCellData->pObj != NULL);
	CValue* pValue = NULL;
	CString strCurValue = pCell->text();
	CValues *pValues = ((CSttCmdWzdDsEditGrid* )pGrid)->m_pValues;

	if (pVCellData->pObj == NULL)
	{
		//说明是第一次编辑，还没有添加对象到m_pValues
		QGV_ITEM *pItem = pGrid->GetCell(nRow, 1);
		pVCellData = (PEXBASECELLDATA)pItem->lParam;
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (pValues->FindByID(pData->m_strID) == NULL)
		{
			pValue = pValues->AddValue(pData->m_strID, strCurValue);
		}

		pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		pGrid->Show_Check(pValue, nRow, 2, (long*)(&pValue->m_dwReserved), EndEditCell_CmdDataValue_CmdValue_BOOL); 
	}
	else
	{
		pValue = (CValue*)pVCellData->pObj;
	}

	if (pCell->checkState() == Qt::Unchecked)
	{
		*pVCellData->pnValue = 0;
		pValue->m_strValue = _T("0");
	}
	else
	{
		*pVCellData->pnValue = 1;
		pValue->m_strValue = _T("1");
	}

	emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData_Value(pValue);
}

void CSttCmdWzdDsEditGrid::EndEditCell_CmdDataValue_CmdValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	//ASSERT(pVCellData->pObj != NULL);
	CValue* pValue = NULL;
	CString strCurValue = pCell->text();
	CValues *pValues = ((CSttCmdWzdDsEditGrid* )pGrid)->m_pValues;

	DWORD dwCurValue = 0;

	if ((strCurValue.Find("0X")== -1)&&(strCurValue.Find("0x")== -1))
	{
		dwCurValue = strCurValue.toULong(0,10);
	}
	else
	{
		dwCurValue = strCurValue.toULong(0,16);
	}

	if (pVCellData->pObj == NULL)
	{
		//说明是第一次编辑，还没有添加对象到m_pValues
		QGV_ITEM *pItem = pGrid->GetCell(nRow, 1);
		pVCellData = (PEXBASECELLDATA)pItem->lParam;
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (pValues->FindByID(pData->m_strID) == NULL)
		{
			pValue = pValues->AddValue(pData->m_strID, strCurValue);
		}

		pValue->m_strValue.Format(_T("%d"), dwCurValue);
		pValue->m_dwReserved = dwCurValue;
		pGrid->Show_Hex(pValue, nRow, 2, &pValue->m_dwReserved, 2, TRUE, TRUE, EndEditCell_CmdDataValue_CmdValue_Hex);
	}
	else
	{
		pValue = (CValue*)pVCellData->pObj;
		pValue->m_strValue.Format(_T("%d"), dwCurValue);
	}

	if (*pVCellData->pdwValue != dwCurValue)
	{
		emit ((CSttCmdWzdDsEditGrid* )pGrid)->sig_CmdWzd_UpdateData_Value(pValue);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttCmdWzdDsEditGrid_Register::CSttCmdWzdDsEditGrid_Register(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttCmdWzdDsEditGrid_Register::~CSttCmdWzdDsEditGrid_Register()
{

}

void CSttCmdWzdDsEditGrid_Register::InitGrid()
{
	QExBaseListGridBase::InitGrid();
}

void CSttCmdWzdDsEditGrid_Register::InitGridTitle()
{
	CString astrGridTitle[4] = {/*"名称"*/g_sLangTxt_Name, "ID", /*"数值"*/g_sLangTxt_Value, ""};
	int iGridWidth[4]={300, 150, 120, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

//该表格显示数据集
void CSttCmdWzdDsEditGrid_Register::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CValue *pValue = (CValue *)pData;
	CString strName = GetValueName(pValue);

	Show_StaticString(pValue, nRow, 0, &strName);
	Show_StaticString(pValue, nRow, 1, &pValue->m_strID);

	if (!IsValue_Bool(pValue))
	{
		Show_String(pValue, nRow, 2, &pValue->m_strValue, EndEditCell_CmdDataValue);
	}
	else
	{
		pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		Show_Check(pValue, nRow, 2, (long*)(&pValue->m_dwReserved), EndEditCell_CmdDataValue_BOOL);
	}

	nRow++;
}

CString CSttCmdWzdDsEditGrid_Register::GetValueName(CValue* pValue)
{
	CString strName;

	if (pValue->m_strID == STT_CMD_PARA_TrgOps_4)
	{
		return /*_T("是否周期上送")*/g_sLangTxt_period;
	}

	if (pValue->m_strID == STT_CMD_PARA_TrgOps_2)
	{
		return /*_T("是否品质上送")*/g_sLangTxt_quality;
	}

	if (pValue->m_strID == STT_CMD_PARA_TrgOps_1)
	{
		return /*_T("是否突变上送")*/g_sLangTxt_mutate;
	}

	if (pValue->m_strID == STT_CMD_PARA_IntgPd)
	{
		return /*_T("周期上送时间(ms)")*/g_sLangTxt_leadtime;
	}

	return strName;
}

BOOL CSttCmdWzdDsEditGrid_Register::IsValue_Bool(CValue *pValue)
{
	if (pValue->m_strID == STT_CMD_PARA_TrgOps_4)
	{
		return TRUE;
	}

	if (pValue->m_strID == STT_CMD_PARA_TrgOps_2)
	{
		return TRUE;
	}

	if (pValue->m_strID == STT_CMD_PARA_TrgOps_1)
	{
		return TRUE;
	}

	if (pValue->m_strID == STT_CMD_PARA_IntgPd)
	{
		return FALSE;
	}

	return FALSE;
}

void CSttCmdWzdDsEditGrid_Register::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();

		emit ((CSttCmdWzdDsEditGrid_Register* )pGrid)->sig_CmdWzd_UpdateData_Value((CValue *)pVCellData->pObj);
	}
}

/*
enum CheckState {
   Unchecked,
   PartiallyChecked,
   Checked
};
*/
void CSttCmdWzdDsEditGrid_Register::EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pnValue != pCell->checkState())
	{
		CValue *pValue = (CValue *)pVCellData->pObj;

		if (pCell->checkState() == Qt::Unchecked)
		{
			*pVCellData->pnValue = 0;
			pValue->m_strValue = _T("0");
		}
		else
		{
			*pVCellData->pnValue = 1;
			pValue->m_strValue = _T("1");
		}

		emit ((CSttCmdWzdDsEditGrid_Register* )pGrid)->sig_CmdWzd_UpdateData_Value(pValue);
	}
}