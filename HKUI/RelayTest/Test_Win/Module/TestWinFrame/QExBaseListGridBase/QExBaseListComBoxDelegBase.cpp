﻿#include "QExBaseListComBoxDelegBase.h"
#include <QLineEdit>
#include <QApplication>
#include <QComboBox>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCheckBoxDelegateBase::QCheckBoxDelegateBase(QObject *parent)
: QItemDelegate(parent)
{
	m_bEditable= TRUE;
}

QCheckBoxDelegateBase::~QCheckBoxDelegateBase()
{
}

//鼠标单击单元格的时候，重绘事件触发
void QCheckBoxDelegateBase::paint(QPainter * painter,
										const QStyleOptionViewItem & option,
										const QModelIndex & index) const
{
	//获取值  
	bool checked = index.model()->data(index, Qt::CheckStateRole).toBool();
	//按钮的风格选项  
	QStyleOptionButton *checkBoxOption = new QStyleOptionButton(); 
	if(m_bEditable)
	{
		checkBoxOption->state |= QStyle::State_Enabled;  
	//根据值判断是否选中  
		if(checked)  
		{  
			checkBoxOption->state |= QStyle::State_On; 
		}  
		else  
		{  
			checkBoxOption->state |= QStyle::State_Off;  
		} 
	}
	else//不被修改默认勾选
	{
		checkBoxOption->state = QStyle::State_On;
	}
	 
	//返回QCheckBox几何形状  
	checkBoxOption->rect = CheckBoxRect(option);  
	//绘制QCheckBox  
	QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter); 

}


QRect QCheckBoxDelegateBase::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const  
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
 bool QCheckBoxDelegateBase::editorEvent(QEvent * event,
 											  QAbstractItemModel * model,
 											  const QStyleOptionViewItem & /*option*/,
 											  const QModelIndex & index)
 {
 	if(event->type()==QEvent::MouseButtonPress)
 	{
 		QVariant varValue = model->data(index,Qt::CheckStateRole);
 
 		int nValue=varValue.toInt();
 
 		if(varValue.isValid())//如果当前值有效,则将当前状态取反
 		{
			if (nValue == Qt::Unchecked)
			{
				nValue=Qt::Checked;
			} 
			else
			{
				nValue=Qt::Unchecked;
			}
 //			bValue=bValue?false:true;
 		}
 		else//否则将当前值置为1,即置为选择状态
 		{
			nValue=Qt::Checked;
 		}
 
 		model->setData(index,nValue,Qt::CheckStateRole);
 		return true;//I have handled the event
 	}
 
 	return false;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QExBaseListCheckBoxDelegate::QExBaseListCheckBoxDelegate(QObject *parent)
: QExBaseListItemDelegateBase(parent)
{
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
	//获取值  
	bool checked = index.model()->data(index, Qt::CheckStateRole).toBool();
	//按钮的风格选项  
	QStyleOptionButton *checkBoxOption = new QStyleOptionButton();  
	checkBoxOption->state |= QStyle::State_Enabled;  
	//根据值判断是否选中  
	if(checked)  
	{  
		checkBoxOption->state |= QStyle::State_On;  
	}  
	else  
	{  
		checkBoxOption->state |= QStyle::State_Off;  
	}  
	//返回QCheckBox几何形状  
	checkBoxOption->rect = CheckBoxRect(option);  
	//绘制QCheckBox  
	QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter); 

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
									const QStyleOptionViewItem & /*option*/,
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
		ASSERT(pVCellData->pnValue);

		if( *(pVCellData->pnValue) != bValue )
		{
			 *(pVCellData->pnValue)  = bValue;
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        QComboBox *pComboBox = new QComboBox(parent);
//		pComboBox->SetIgnoreFirstHidePopup(true);
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
        QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		int nCurIndex = -1,nIndex = 0;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
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

		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = pDataTypeValue->m_strID;
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			*(pVCellData->pnValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			*(pVCellData->pdValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			*(pVCellData->pfValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			*(pVCellData->pdwValue) = pDataTypeValue->GetIndex();
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
