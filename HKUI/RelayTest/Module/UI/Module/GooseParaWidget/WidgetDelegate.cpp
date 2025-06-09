#include "WidgetDelegate.h"
#include <QApplication>
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../ScrollCtrl/ScrollComboBox.h"
#include <QSpinBox>

#pragma execution_character_set("utf-8")

CCheckBoxDelegate::CCheckBoxDelegate(QObject *parent)
	: QItemDelegate(parent)
{
	favouritePixmap=QPixmap(":/pic/images/checked-20.png");
	notFavouritePixmap=QPixmap(":/pic/images/unchecked-20.png");
}

CCheckBoxDelegate::~CCheckBoxDelegate()
{

}


//鼠标单击单元格的时候，重绘事件触发
void CCheckBoxDelegate::paint(QPainter * painter,
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

QRect CCheckBoxDelegate::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const  
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
bool CCheckBoxDelegate::editorEvent(QEvent * event,
								 QAbstractItemModel * model,
								 const QStyleOptionViewItem & /*option*/,
								 const QModelIndex & index)
{
	if(event->type()==QEvent::MouseButtonPress)
	{
		QVariant var=model->data(index,Qt::CheckStateRole);
		bool isFavourite=var.toBool();
		if(var.isValid())
			isFavourite=isFavourite?false:true;
		else
			isFavourite=true;
		model->setData(index,isFavourite,Qt::CheckStateRole);

		return true;//I have handled the event
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
CSpinBoxDelegate::CSpinBoxDelegate(int _iMin, int _iMax, QObject *parent)
:QItemDelegate(parent),m_iMin(_iMin),m_iMax(_iMax)
{

}

CSpinBoxDelegate::~CSpinBoxDelegate()
{

}

QWidget *CSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, 
										const QModelIndex &/*index*/) const
{
	QSpinBox *spinBox = new QSpinBox(parent);
	spinBox->setMinimum(m_iMin);
	spinBox->setMaximum(m_iMax);
	return spinBox;
}

void CSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int iValue = index.model()->data(index,Qt::EditRole).toInt();

	QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
	spinBox->setValue(iValue);
}

void CSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									const QModelIndex &index) const
{
	QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
	model->setData(index,spinBox->value(),Qt::EditRole);
}

void CSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////

CComboBoxDelegate::CComboBoxDelegate(PAGE_TYPE _type, QObject *parent)
: QItemDelegate(parent),m_type(_type)
{
	
}

CComboBoxDelegate::~CComboBoxDelegate()
{

}

QWidget *CComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
										 const QModelIndex &index) const
{
	QVariant variant = index.data();

	QScrollComboBox *comboBox = new QScrollComboBox(parent);
	return comboBox;
}

void CComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	CString strSingle, strDouble;
	xlang_GetLangStrByFile(strSingle, "GOOSE_Single");
	xlang_GetLangStrByFile(strDouble, "GOOSE_Double");

	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;

	switch(m_type)
	{
	case SMV91_CHAN:
		{
			if (index.column() == 1)
			{
/*
				pugi::xml_node Type_node = CSingleTon::GetInstance().m_root.select_node(PUGIXML_TEXT("./SMV/IEC61850-9-1/Channel/Type")).node();
				for (pugi::xml_node Option_node = Type_node.child(PUGIXML_TEXT("Option")); Option_node; 
					Option_node = Option_node.next_sibling(PUGIXML_TEXT("Option")))
				{
					strItemList<<(CString)Option_node.attribute(PUGIXML_TEXT("name")).value();
				}
*/
			}
			else if (index.column() == 2)
			{
/*
				pugi::xml_node Map_node = CSingleTon::GetInstance().m_root.select_node(PUGIXML_TEXT("./SMV/IEC61850-9-1/Channel/Map")).node();
				for (pugi::xml_attribute attri = Map_node.first_attribute(); attri; 
					attri = attri.next_attribute())
				{
					strItemList<<(CString)attri.value();
				}
*/
			}

			break;
		}
	
	case SMV92_CHAN:
		{
			if (index.column() == 1)
			{
/*
				pugi::xml_node Map_node = CSingleTon::GetInstance().m_root.child(PUGIXML_TEXT("SMV")).child(PUGIXML_TEXT("IEC61850-9-2")).child(PUGIXML_TEXT("Map"));
				for(pugi::xml_node Type_node = Map_node.child(PUGIXML_TEXT("Type")); Type_node; 
					Type_node = Type_node.next_sibling(PUGIXML_TEXT("Type")))
				{
					strItemList<<(CString)Type_node.attribute(PUGIXML_TEXT("name")).value();
				}
*/
			}
			else if (index.column() == 2)
			{
				QModelIndex chanTypeIndex = index.sibling(index.row(), 1);
				QString strType = index.model()->data(chanTypeIndex,Qt::EditRole).toString();
/*
				pugi::xml_node Map_node = CSingleTon::GetInstance().m_root.child(PUGIXML_TEXT("SMV")).child(PUGIXML_TEXT("IEC61850-9-2")).child(PUGIXML_TEXT("Map"));
				pugi::xml_node Type_node = Map_node.find_child_by_attribute(PUGIXML_TEXT("name"), (const pugi::char_t*)strType.data());
				for (pugi::xml_attribute attri = Type_node.child(PUGIXML_TEXT("Val")).first_attribute(); attri; attri = attri.next_attribute())
				{
					strItemList<<(CString)attri.value();
				}
*/
			}

			break;
		}
	
	case GOPUB_CHAN:
		{
			if (index.column() == 1)
			{
				CDataType* pGooseChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("GooseChDataType"));
				if (pGooseChDataType)
				{
					CDataTypeValue* pDataTypeValue = NULL;
					POS pos = pGooseChDataType->GetHeadPosition();
					while (pos)
					{
						pDataTypeValue = (CDataTypeValue*)pGooseChDataType->GetNext(pos);
						strItemList<<pDataTypeValue->m_strName;
					}
				}
			}
			else if (index.column() == 2)
			{
				QModelIndex chanTypeIndex = index.sibling(index.row(), 1);
				QString strType = index.model()->data(chanTypeIndex,Qt::EditRole).toString();
				CDataType* pDataType = NULL;
				CDataTypeValue* pDataTypeValue = NULL;
				POS pos = NULL;

				if (strType == strSingle)
				{
					pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_single);
					if (pDataType)
					{
						pos = pDataType->GetHeadPosition();
						while (pos)
						{
							pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
							strItemList<<pDataTypeValue->m_strName;
						}
					}
				}
				else if (strType == strDouble)
				{
					pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_double);
					if (pDataType)
					{
						pos = pDataType->GetHeadPosition();
						while (pos)
						{
							pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
							strItemList<<pDataTypeValue->m_strName;
						}
					}
				}
			}
			
			break;
		}
	
	default:
		break;
	}

	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	comboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		comboBox->addItem(strValue);
	}
	comboBox->setCurrentIndex(id);
}

void CComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,comboBox->currentText(),Qt::EditRole);
}

void CComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											 const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////
CNumberEditDelegate::CNumberEditDelegate(CLineEdit::TEXT_TYPE _type, QObject *parent)
: QItemDelegate(parent),m_textType(_type)
{

}

CNumberEditDelegate::~CNumberEditDelegate()
{

}

QWidget *CNumberEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, 
										   const QModelIndex &index) const
{
	QString str = index.model()->data(index,Qt::EditRole).toString();
	CLineEdit *lineEdit = new CLineEdit(m_textType, str, parent);

	return lineEdit;
}

void CNumberEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString str = index.model()->data(index,Qt::EditRole).toString();

	CLineEdit *lineEdit = dynamic_cast<CLineEdit *>(editor);
	if(lineEdit != NULL)
		lineEdit->setText(str);
	lineEdit->setCursorPosition(2);
}

void CNumberEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									   const QModelIndex &index) const
{
	CLineEdit *lineEdit = dynamic_cast<CLineEdit *>(editor);
	QString str = lineEdit->text();
	model->setData(index,str,Qt::EditRole);
}

void CNumberEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											   const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////
CComplexDelegate::CComplexDelegate(PAGE_TYPE _type, QObject *parent)
	: QItemDelegate(parent), m_type(_type)
{
	InitLanguage();
}

CComplexDelegate::~CComplexDelegate()
{

}

void CComplexDelegate::InitLanguage()
{
	CString strSingle, strDouble, strString, strQuality, strFloat;
	xlang_GetLangStrByFile(m_strSingle, "GOOSE_Single");
	xlang_GetLangStrByFile(m_strDouble, "GOOSE_Double");
	xlang_GetLangStrByFile(m_strString, "sCharacterString");
	xlang_GetLangStrByFile(m_strQuality, "IEC_Quality");
	xlang_GetLangStrByFile(m_strFloat, "GOOSE_Float");
}

QWidget *CComplexDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
	const QModelIndex &index) const
{
	if(m_type == GOPUB_CHAN)
	{
		if (index.column() == 3)
		{
			QString strType = index.sibling(index.row(), 1).data().toString();

			if(strType == m_strSingle || strType == m_strDouble)
			{
				QComboBox *comboBox = new QScrollComboBox(parent);
				return comboBox;
			}
			else if(strType == m_strString)
			{
				QLineEdit *lineEdit = new QLineEdit(parent);
				return lineEdit;
			}
			else if(strType == m_strQuality)
			{
				QString str = index.model()->data(index, Qt::EditRole).toString();
				CLineEdit *lineEdit = new CLineEdit(CLineEdit::APPID_TEXT, str, parent);
				return lineEdit;
			}
			else if(strType == m_strFloat)
			{
				QLineEdit *lineEdit = new QLineEdit(parent);
				QDoubleValidator* aIntValidator = new QDoubleValidator;
				lineEdit->setValidator(aIntValidator);
				return lineEdit;
			}
			else if(strType == "INT32")
			{
				QLineEdit *lineEdit = new QLineEdit(parent);
				QIntValidator* aIntValidator = new QIntValidator;
				lineEdit->setValidator(aIntValidator);
				return lineEdit;
			}
			else if(strType == "INT32U")
			{
				QLineEdit *lineEdit = new QLineEdit(parent);
				QIntValidator* aIntValidator = new QIntValidator;
				aIntValidator->setBottom(0);
				lineEdit->setValidator(aIntValidator);
				return lineEdit;
			}
		}
	}

	return NULL;
}

void CComplexDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString strItem = index.model()->data(index, Qt::EditRole).toString();

	if (m_type == GOPUB_CHAN)
	{
		if (index.column() == 3)
		{
			QString strType = index.sibling(index.row(), 1).data().toString();
			QStringList strItemList;
			CDataType* pDataType = NULL;
			CDataTypeValue* pDataTypeValue = NULL;
			POS pos = NULL;
			if (strType == m_strSingle || strType == m_strDouble)
			{
				if (strType == m_strSingle)
				{
					pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_single_def_value);
					if (pDataType)
					{
						pos = pDataType->GetHeadPosition();
						while (pos)
						{
							pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
							strItemList<<pDataTypeValue->m_strID;
						}
					}
				}
				else if (strType == m_strDouble)
				{
					pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_double_def_value);
					if (pDataType)
					{
						pos = pDataType->GetHeadPosition();
						while (pos)
						{
							pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
							strItemList<<pDataTypeValue->m_strID;
						}
					}
				}
				QComboBox *comboBox =  dynamic_cast<QComboBox *>(editor);
				int id = 0;
				for (int i = 0; i < strItemList.size(); i++)
				{
					QString strValue = strItemList.at(i);
					if (strValue == strItem)
					{
						id = i;
					}
					comboBox->addItem(strValue);
				}
				comboBox->setCurrentIndex(id);
			}
			else if(strType == m_strString)
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				lineEdit->setText(strItem);
			}
			else if(strType == m_strQuality)
			{
				CLineEdit *lineEdit = dynamic_cast<CLineEdit *>(editor);
				lineEdit->setText(strItem);
				lineEdit->setCursorPosition(2);
			}
			else if(strType == m_strFloat)
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				lineEdit->setText(strItem);
			}
			else if(strType == "INT32" || strType == "INT32U")
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				lineEdit->setText(strItem);
			}
		}
	}
}

void CComplexDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	if (m_type == GOPUB_CHAN)
	{
		if (index.column() == 3)
		{
			QString strType = index.sibling(index.row(), 1).data().toString();

			if(strType == m_strSingle || strType == m_strDouble)
			{
				QComboBox *comboBox = dynamic_cast<QComboBox *>(editor);
				if(comboBox != NULL){
					model->setData(index, comboBox->currentText(), Qt::EditRole);
				}
			}
			else if(strType == m_strSingle)
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				model->setData(index, lineEdit->text(), Qt::EditRole);
			}
			else if(strType == m_strQuality)
			{
				CLineEdit *lineEdit = dynamic_cast<CLineEdit *>(editor);
				QString str = lineEdit->text();
				model->setData(index, str, Qt::EditRole);
			}
			else if(strType == m_strFloat)
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				model->setData(index, lineEdit->text(), Qt::EditRole);
			}
			else if(strType == "INT32" || strType == "INT32U")
			{
				QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(editor);
				model->setData(index, lineEdit->text(), Qt::EditRole);
			}
		}
	}
}

void CComplexDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
	const QModelIndex &) const
{
	editor->setGeometry(option.rect);
}
