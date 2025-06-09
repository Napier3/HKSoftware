#include "QExBaseListComBoxDelegBase.h"
#include <QLineEdit>
#include <QApplication>
#include "../ScrollCtrl/ScrollComboBox.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include <QPainter>
#include <math.h>

//////////////////////////////////////////////////////////////////////////

QExBaseListItemDelegateBase::QExBaseListItemDelegateBase(QObject *parent)
: QItemDelegate(parent)
{
}

QExBaseListItemDelegateBase::~QExBaseListItemDelegateBase()
{

}

QGV_ITEM* QExBaseListItemDelegateBase::GetCurrItem(const QModelIndex &oQModelIndex) const
{
	QObject *pParent = parent();

	if (pParent == NULL)
	{
		return NULL;
	}

	QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(pParent);

	if (pExBaseListGridBase == NULL)
	{
		return NULL;
	}

	return pExBaseListGridBase->GetCell(oQModelIndex.row(),oQModelIndex.column());
}


//////////////////////////////////////////////////////////////////////////

QExBaseListCheckBoxDelegate::QExBaseListCheckBoxDelegate(QObject *parent)
: QExBaseListItemDelegateBase(parent)
{
	InitStyleSheet();
// 	m_oSelectedPixmap = QPixmap(":/pic/images/checked-20.png");
// 	m_oUnselectedPixmap=QPixmap(":/pic/images/unchecked-20.png");

}

QExBaseListCheckBoxDelegate::~QExBaseListCheckBoxDelegate()
{

}


//鼠标单击单元格的时候，重绘事件触发
void QExBaseListCheckBoxDelegate::paint(QPainter * painter,
							  const QStyleOptionViewItem & option,
							  const QModelIndex & index) const
{
// 	//获取值    原生态绘制
// 	bool checked = index.model()->data(index, Qt::CheckStateRole).toBool();
// 	//按钮的风格选项  
// 	QStyleOptionButton *checkBoxOption = new QStyleOptionButton();  
// 	checkBoxOption->state |= QStyle::State_Enabled;  
// 	//根据值判断是否选中  
// 	if(checked)  
// 	{  
// 		checkBoxOption->state |= QStyle::State_On;  
// 	}  
// 	else  
// 	{  
// 		checkBoxOption->state |= QStyle::State_Off;  
// 	}  
// 	//返回QCheckBox几何形状  
// 	checkBoxOption->rect = CheckBoxRect(option);  
// 	//绘制QCheckBox  
// 	QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter); 


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

void QExBaseListCheckBoxDelegate::InitStyleSheet()
{
	CString strSelectPath,strUnSelectPath;
#ifdef _PSX_QT_WINDOWS_
	strSelectPath =  _P_GetResourcePath();
	strSelectPath += _T("checked.png");
	strUnSelectPath =  _P_GetResourcePath();
	strUnSelectPath += _T("unchecked.png");
#else
	strSelectPath =  ":/ctrls/images/checked.png";
	strUnSelectPath += ":/ctrls/images/unchecked.png";
#endif
	m_oSelectedPixmap.load(strSelectPath);
	m_oSelectedPixmap.scaled(20,20);
	m_oUnselectedPixmap.load(strUnSelectPath);
	m_oUnselectedPixmap.scaled(20,20);
}

QRect QExBaseListCheckBoxDelegate::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const  
{  
	//绘制按钮所需要的参数  
	QStyleOptionButton checkBoxStyleOption;  
	//按照给定的风格参数 返回元素子区域  
	QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);  
	//返回QCheckBox坐标  
	QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,  
		viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);  
	//返回QCheckBox几何形状  
	return QRect(checkBoxPoint, checkBoxRect.size());  
}  

//单击事件发生，值翻转
bool QExBaseListCheckBoxDelegate::editorEvent(QEvent * event,
									QAbstractItemModel * model,
									const QStyleOptionViewItem &/* option*/,
									const QModelIndex & index)
{
	if(event->type()==QEvent::MouseButtonPress)
	{
#ifndef _PSX_QT_LINUX_
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);  

		if (mouseEvent->button() == Qt::RightButton)
		{
			return false;
		}
#endif

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
		BOOL bHasChanged = FALSE;

		if (pVCellData->nVt == VCD_STRING)
		{
			ASSERT(pVCellData->pString);
			long nCheckValue = CString_To_long(*pVCellData->pString);

			if(nCheckValue != bValue )
			{
				pVCellData->pString->Format("%d",(int)bValue);
				bHasChanged = TRUE;
			}
		} 
		else
		{
			ASSERT(pVCellData->pnValue);

			if( *(pVCellData->pnValue) != bValue )
			{
				*(pVCellData->pnValue)  = bValue;
				bHasChanged = TRUE;
			}
		}

		if (pCurItem->m_pEditFunc != NULL)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
			pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
			pExBaseListGridBase->OnDataSelChanged(index.row(),index.column());
		}
		else if (bHasChanged)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
			pExBaseListGridBase->SetModifiedFlag(pVCellData->pObj);
		}

		return true;//I have handled the event
	}

	return false;


}
//////////////////////////////////////////////////////////////////////////

QExBaseListComBoxDelegBase::QExBaseListComBoxDelegBase(QObject *parent)
: QExBaseListItemDelegateBase(parent)
{
	m_bEditable= TRUE;
	m_bFirstClicked = TRUE;
}

QExBaseListComBoxDelegBase::~QExBaseListComBoxDelegBase()
{

}

QWidget *QExBaseListComBoxDelegBase::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
										 const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return NULL;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return NULL;
	}

	if (pCurItem->lParam == 0)
	{
		return NULL;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

	if (pDataType != NULL)
	{
        QScrollComboBox *pComboBox = new QScrollComboBox(parent);
#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
		pComboBox->SetIgnoreFirstHidePopup(true);
#endif
		return pComboBox;
	} 
	else
	{
		return new QLineEdit(parent);
	}
}

// 单击事件发生
bool QExBaseListComBoxDelegBase::editorEvent(QEvent * event,
											  QAbstractItemModel * model,
											  const QStyleOptionViewItem & option,
											  const QModelIndex & index)
{
// #ifdef  _PSX_QT_LINUX_
// 	long nType = event->type();
// 
// 	if(event->type()==QEvent::MouseButtonDblClick)
// 	{
// 		if (m_bFirstClicked)
// 		{
// 			m_bFirstClicked = FALSE;
// 			return true;
// 		}
// 	}
// #endif

	return QExBaseListItemDelegateBase::editorEvent(event,model,option,index);
}
// 
// 鼠标单击单元格的时候，重绘事件触发
 void QExBaseListComBoxDelegBase::paint(QPainter * painter,
 										const QStyleOptionViewItem & option,
 										const QModelIndex & index) const
 {  
	 if (!m_bEditable)
	 {
		 QItemDelegate::paint(painter,option,index);
		 return;
	 }

	 QGV_ITEM* pCurItem = GetCurrItem(index);

	 if ((pCurItem == NULL) || (pCurItem->lParam == 0))
	 {
		 QItemDelegate::paint(painter,option,index);
		 return;
	 }

	 PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;

	 if (pVCellData->pExBaseList == NULL)
	 {
		 QItemDelegate::paint(painter,option,index);
		 return;
	 }

  	QProxyStyle oProxyStyle;
  	QStyleOptionComboBox oStyleOptionComboBox;
 	oStyleOptionComboBox.state = QStyle::State_On;
 	oStyleOptionComboBox.rect = option.rect;
	QPalette oPalette;

	if (pCurItem != NULL)
	{
		oStyleOptionComboBox.editable = true;
		oStyleOptionComboBox.frame = false;
		oStyleOptionComboBox.currentText = pCurItem->text();
	}

	oProxyStyle.drawComplexControl(QStyle::CC_ComboBox,&oStyleOptionComboBox, painter);
	oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);

//	bool bBackColorValid = false;
//
//  	if (pCurItem != NULL)
//  	{
//  		oStyleOptionComboBox.editable = true;
//  		oStyleOptionComboBox.frame = false;
//  		oStyleOptionComboBox.currentText = pCurItem->text();
// 		QColor oColor = pCurItem->backgroundColor();
// 
// 		if (oColor.isValid())
// 		{
// 			painter->setBackground(oColor);
// //			oPalette.setColor(QPalette::Background,oColor);
// 			bBackColorValid = true;
// 		}
// 		else
// 		{
// 			painter->setBackground(QColor(0,0,0));
// //			oPalette.setColor(QPalette::Background,QColor(0,0,0));
// 		}
// 	}
//  
//  	oProxyStyle.drawComplexControl(QStyle::CC_ComboBox,&oStyleOptionComboBox, painter// 	if (bBackColorValid)
// 	{
// 		oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText,QPalette::Background);//	} 
//	else
//	{
//		oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);//	}
//	QItemDelegate::paint(painter,option,index);
 
//  	Q_UNUSED(index);
//  	QStyleOptionComboBox btnStyle;
//  //	btnStyle.text = "我是按钮";             //设置按钮文本
//  	btnStyle.rect = option.rect;            //设置按钮区域为当前item的rect
//  //	btnStyle.state = QStyle::State_Enabled; //设置按钮状态
//  
//  	QComboBox btn;
//  	btn.addItem("00000");
//  	btn.addItem("11111");
//  	btn.style()->drawControl(QStyle::CE_ItemViewItem, &btnStyle, painter,&btn);   //将按钮绘制出来
//  
//  	QStyleOptionComboBox *checkBoxOption = new QStyleOptionComboBox();  
//   
//  	//返回QCheckBox几何形状  
//  	checkBoxOption->rect = ComboBoxRect(option);  
//  	//绘制QCheckBox  
//  	QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel,checkBoxOption,painter); 
 
 }
 
// QRect QExBaseListComBoxDelegBase::ComboBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const  
// {  
// 	//绘制按钮所需要的参数  
// 	QStyleOptionComboBox checkBoxStyleOption;  
// 	//按照给定的风格参数 返回元素子区域  
// 	QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_ComboBoxLayoutItem, &checkBoxStyleOption);  
// 	//返回QCheckBox坐标  
// 	QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,  
// 		viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);  
// 	//返回QCheckBox几何形状  
// 	return QRect(checkBoxPoint, checkBoxRect.size());  
// } 

void QExBaseListComBoxDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

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
	
	if (pDataType != NULL)
	{
        QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
		pComboBox->clear();
		int nCurIndex = -1,nIndex = 0;
        CString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);

			if (pDataTypeValue->m_strName == strItem)
			{
				nCurIndex = nIndex;
			}

			pComboBox->addItem(pDataTypeValue->m_strName);
			nIndex++;
		}

		if (nCurIndex>=0)
		{
			pComboBox->setCurrentIndex(nCurIndex);

			if (pComboBox->isHidden())
			{
                pComboBox->showPopup();
			}
		}
	}
	else
	{
		QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
		lineEdit->setText(index.model()->data(index, Qt::EditRole).toString()); 
	}
}

void QExBaseListComBoxDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model, 
									 const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

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

	if (pVCellData->pExBaseList != NULL)
	{
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		model->setData(index,comboBox->currentText(),Qt::EditRole);
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = (CDataTypeValue*)pDataType->GetAtIndex(comboBox->currentIndex());

		if (pDataTypeValue == NULL)
		{
			return;
		}

		ASSERT(pDataTypeValue);
		BOOL bHasChanged = FALSE;

		if (pVCellData->nVt == VCD_STRING)
		{
			if (pCurItem->nReserved == QT_GRID_COMBOBOX_StringType_DataTypeIndex)
			{
				long nIndex1 = CString_To_long(*pVCellData->pString);
				long nIndex2 = CString_To_long(pDataTypeValue->m_strIndex);
				//*(pVCellData->pString) = pDataTypeValue->m_strIndex;
				if (nIndex1 != nIndex2)
				{
					*(pVCellData->pString) = pDataTypeValue->m_strIndex;
					bHasChanged = TRUE;
				}
			}
			else
			{
				if (*(pVCellData->pString) != pDataTypeValue->m_strID)
				{
					*(pVCellData->pString) = pDataTypeValue->m_strID;
					bHasChanged = TRUE;
				}
			}	
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			long nDataTypeIndex = pDataTypeValue->GetIndex();

			if (*(pVCellData->pnValue) != nDataTypeIndex)
			{
				*(pVCellData->pnValue) = nDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			double dDataTypeIndex = pDataTypeValue->GetIndex();

			if (fabs(dDataTypeIndex - *(pVCellData->pdValue))>0.001f)
			{
				*(pVCellData->pdValue) = dDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			double dDataTypeIndex = pDataTypeValue->GetIndex();

			if (fabs(dDataTypeIndex - *(pVCellData->pfValue))>0.001f)
			{
				*(pVCellData->pfValue) = dDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			DWORD nDataTypeIndex = pDataTypeValue->GetIndex();

			if (*(pVCellData->pdwValue) != nDataTypeIndex)
			{
				*(pVCellData->pdwValue) = nDataTypeIndex;
				bHasChanged = TRUE;
			}
		}

		if (bHasChanged)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());

			if (pExBaseListGridBase != NULL)
			{
				pExBaseListGridBase->SetModifiedFlag(pVCellData->pObj);
			}
		}

//		*pVCellData->pString = pDataTypeValue->m_strID;
	}
	else
	{
		QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(editor);
		QString text = pLineEdit->text();  
		model->setData(index, text, Qt::EditRole);
		*pVCellData->pString = text;
	}

	if (pCurItem->m_pEditFunc != NULL)
	{
		QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
		pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
	}
}

void QExBaseListComBoxDelegBase::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											 const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////
//20240913 huangliang 添加可编辑下拉框
QExBaseListEditComBoxDelegBase::QExBaseListEditComBoxDelegBase(QObject *parent)
	: QExBaseListComBoxDelegBase(parent)
{
	m_bEditable = TRUE;
	m_bFirstClicked = TRUE;
}

QExBaseListEditComBoxDelegBase::~QExBaseListEditComBoxDelegBase()
{
}

QWidget *QExBaseListEditComBoxDelegBase::createEditor(QWidget *parent, const QStyleOptionViewItem &,
	const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return NULL;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return NULL;
	}

	if (pCurItem->lParam == 0)
	{
		return NULL;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

	if (pDataType != NULL)
	{
		QScrollComboBox *pComboBox = new QScrollComboBox(parent);
#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
		pComboBox->SetIgnoreFirstHidePopup(true);
#endif
		pComboBox->setEditable(true);
		return pComboBox;
	}
	else
	{
		return new QLineEdit(parent);
	}
}

void QExBaseListEditComBoxDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

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

	if (pDataType != NULL)
	{
		QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
		pComboBox->clear();
		int nCurIndex = -1, nIndex = 0;
		CString strItem = index.model()->data(index, Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);

			if (pDataTypeValue->m_strName == strItem)
			{
				nCurIndex = nIndex;
			}

			pComboBox->addItem(pDataTypeValue->m_strName);
			nIndex++;
		}

		//20241009 huangliang 没找到什么时候默认选择了第一项，这里把没找到的文本添加到第一项里
		if (nCurIndex < 0 && strItem != _T(""))
		{
			pComboBox->insertItem(0, strItem);
			nCurIndex = 0;
		}

		if (nCurIndex >= 0)
		{
			pComboBox->setCurrentIndex(nCurIndex);

			if (pComboBox->isHidden())
			{
				pComboBox->showPopup();
			}
		}
	}
	else
	{
		QLineEdit *lineEdit = static_cast <QLineEdit*>(editor);
		lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
	}
}

void QExBaseListEditComBoxDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

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

	if (pVCellData->pExBaseList != NULL)
	{		
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		QString sCurrentText = comboBox->currentText();
		model->setData(index, comboBox->currentText(), Qt::EditRole);
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
		QString strItem = index.model()->data(index, Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = (CDataTypeValue*)pDataType->GetAtIndex(comboBox->currentIndex());

		if (pDataTypeValue == NULL)
		{
			return;
		}

		ASSERT(pDataTypeValue);
		BOOL bHasChanged = FALSE;

		if (pVCellData->nVt == VCD_STRING)
		{
			if (pCurItem->nReserved == QT_GRID_COMBOBOX_StringType_DataTypeIndex)
			{
				long nIndex1 = CString_To_long(*pVCellData->pString);
				long nIndex2 = CString_To_long(pDataTypeValue->m_strIndex);
				//*(pVCellData->pString) = pDataTypeValue->m_strIndex;
				if (nIndex1 != nIndex2)
				{
					*(pVCellData->pString) = pDataTypeValue->m_strIndex;
					bHasChanged = TRUE;
				}
			}
			else
			{
				if (*(pVCellData->pString) != pDataTypeValue->m_strID)
				{
					*(pVCellData->pString) = pDataTypeValue->m_strID;
					bHasChanged = TRUE;
				}
			}
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			long nDataTypeIndex = pDataTypeValue->GetIndex();

			if (*(pVCellData->pnValue) != nDataTypeIndex)
			{
				*(pVCellData->pnValue) = nDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			double dDataTypeIndex = pDataTypeValue->GetIndex();

			if (fabs(dDataTypeIndex - *(pVCellData->pdValue))>0.001f)
			{
				*(pVCellData->pdValue) = dDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			double dDataTypeIndex = pDataTypeValue->GetIndex();

			if (fabs(dDataTypeIndex - *(pVCellData->pfValue))>0.001f)
			{
				*(pVCellData->pfValue) = dDataTypeIndex;
				bHasChanged = TRUE;
			}
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			DWORD nDataTypeIndex = pDataTypeValue->GetIndex();

			if (*(pVCellData->pdwValue) != nDataTypeIndex)
			{
				*(pVCellData->pdwValue) = nDataTypeIndex;
				bHasChanged = TRUE;
			}
		}

		if (bHasChanged)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());

			if (pExBaseListGridBase != NULL)
			{
				pExBaseListGridBase->SetModifiedFlag(pVCellData->pObj);
			}
		}

		//		*pVCellData->pString = pDataTypeValue->m_strID;   
	}
	else
	{
		QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(editor);
		QString text = pLineEdit->text();
		model->setData(index, text, Qt::EditRole);
		*pVCellData->pString = text;
	}

	if (pCurItem->m_pEditFunc != NULL)
	{
		QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
		pCurItem->m_pEditFunc(index.row(), index.column(), pCurItem, pExBaseListGridBase);
	}
}

//////////////////////////////////////////////////////////////////////////
