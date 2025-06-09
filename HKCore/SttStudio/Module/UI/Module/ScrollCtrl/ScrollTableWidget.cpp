#include "ScrollTableWidget.h"
#include <QApplication>
#include <QLineEdit>
#include "../../../../../Module/OSInterface/OSInterface.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern long g_nTableVertScrollWidth;
extern long g_nTableHorizontalScrollHeight;

QCheckBoxDelegateBase::QCheckBoxDelegateBase(QObject *parent)
: QItemDelegate(parent)
{
	// 	m_oSelectedPixmap = QPixmap(":/pic/images/checked-20.png");
	// 	m_oUnselectedPixmap=QPixmap(":/pic/images/unchecked-20.png");
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
										const QStyleOptionViewItem & option,
										const QModelIndex & index)
{
	//表格单击事件,会转换为双击
	if(event->type()==QEvent::MouseButtonDblClick/*MouseButtonPress*/)
	{
// 		if ((index.column() == 0)&&(index.row() == 0))
// 		{
// 			return true;
// 		}

		QVariant varValue = model->data(index,Qt::CheckStateRole);

		int nValue = varValue.toInt();

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
	else if (event->type()==QEvent::MouseButtonPress)
	{
		return false;
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("editorEvent[MouseButtonDblClick][row=%d,cow=%d]"),index.row(),index.column());
	}
	else
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("editorEvent[event->type()=%d][row=%d,cow=%d]"),event->type(),index.row(),index.column());
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QScrollTableWidget::QScrollTableWidget(QWidget* pParent) : QTableWidget(pParent)
{
	m_oAttri.m_pCurScrollBar = this->verticalScrollBar();
	m_oAttri.m_tagSliderDir = DEFAULT;
	m_oAttri.m_bIsMoving = false;
	m_oAttri.m_bIsPressed = false;
	m_oAttri.m_nScrollVal = 0;
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_nCellIndex = 0;
	m_oAttri.m_nPreValSaved = 0;

	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	SetSliderDir(VERI);
	
	
	SetVertScrollWidth(g_nTableVertScrollWidth);
	SetHorizontalScrollHeight(g_nTableHorizontalScrollHeight);
}

QScrollTableWidget::~QScrollTableWidget()
{
	
}

void QScrollTableWidget::SetSliderDir(tagSliderDir tagDir)
{
	m_oAttri.m_tagSliderDir = tagDir;
	// 区分横向或纵向，不同时支持横向纵向
	if (m_oAttri.m_tagSliderDir == VERI)
	{
		m_oAttri.m_pCurScrollBar = this->verticalScrollBar();
	}
	else
	{
		m_oAttri.m_pCurScrollBar = this->horizontalScrollBar();
	}
}

bool QScrollTableWidget::IsScrollMoving()
{
	return m_oAttri.m_bIsMoving;
}

void QScrollTableWidget::SetVertScrollWidth(long nVertScrollWidth) //竖直滑块宽度
{
	CString strSheetStyle;

#ifdef _PSX_QT_LINUX_
	strSheetStyle.Format(_T("QScrollBar{ width:%ldpx ;margin-top:2px;margin-bottom:2px }"
		"QScrollBar::handle:vertical{  width:%ldpx }"
		"QScrollBar::sub-line:vertical{height:2px;subcontrol-position:top;subcontrol-origin:margin;}"
        "QScrollBar::add-line:vertical{height:2px;subcontrol-position:bottom;subcontrol-origin:margin;}"),nVertScrollWidth,nVertScrollWidth);
/*
#else
    strSheetStyle.Format(_T("QScrollBar{width:%ldpx  ;margin-top:16px;margin-bottom:16px}"),nVertScrollWidth);
*/
#endif
	verticalScrollBar()->setStyleSheet(strSheetStyle);
}

void QScrollTableWidget::SetHorizontalScrollHeight(long nLevelScrollHeight) //水平滑块宽度
{
	CString strSheetStyle;
#ifdef _PSX_QT_LINUX_
	strSheetStyle.Format(_T("QScrollBar{ height:%ldpx ;margin-top:2px;margin-bottom:2px }"
		"QScrollBar::handle:horizontal{  height:%ldpx }"
		"QScrollBar::sub-line:horizontal{width:2px;subcontrol-position:top;subcontrol-origin:margin;}"
		"QScrollBar::add-line:horizontal{width:2px;subcontrol-position:bottom;subcontrol-origin:margin;}"),nLevelScrollHeight,nLevelScrollHeight);
/*
#else
	strSheetStyle.Format(_T("QScrollBar{ height:%ldpx ;margin-top:2px;margin-bottom:2px }"
		"QScrollBar::handle:horizontal{ height:%ldpx }"
		"QScrollBar::sub-line:horizontal{width:2px;subcontrol-position:top;subcontrol-origin:margin;}"
		"QScrollBar::add-line:horizontal{width:2px;subcontrol-position:bottom;subcontrol-origin:margin;}"),nLevelScrollHeight);
*/
#endif
	horizontalScrollBar()->setStyleSheet(strSheetStyle);

}



void QScrollTableWidget::mousePressEvent(QMouseEvent *ev)
{
#ifndef _PSX_QT_LINUX_   //shaolei 2023-1-13 屏蔽鼠标右键点击进入编辑状态
	if (ev->button() == Qt::RightButton)
	{
		return;
	}
#endif
	m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	m_oAttri.m_oPressedAxis = ev->pos();
	m_oAttri.m_nPreOffset = 0;
	m_oAttri.m_bIsPressed = true;
	m_oAttri.m_nScrollLastMaxVal = 0;
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::HideSmoothKeyboard();
#endif
	QTableWidget::mousePressEvent( ev );
}


void QScrollTableWidget::mouseMoveEvent(QMouseEvent *ev)
{
	if (!m_oAttri.m_bIsPressed)
	{
		// 未经过按下事件，不应到这里来
		QTableWidget::mouseMoveEvent( ev );
		return;
	}

	int nCurXPos = ev->x(), nCurYPos = ev->y();
	int nMax = 0, nOffset = 0;

#ifdef _PSX_QT_LINUX_
	//根据鼠标开始移动的方向确定滑动方向
	if(!m_oAttri.m_bIsMoving)
	{
		long nDx = nCurXPos - m_oAttri.m_oPressedAxis.x();
		long nDy = nCurYPos - m_oAttri.m_oPressedAxis.y();
		if(qAbs(nDx) > qAbs(nDy))
		{
			SetSliderDir(HORI);
			//如果没有横向滚动条则重新设置回纵向
			if(!m_oAttri.m_pCurScrollBar->maximum())
			{
				SetSliderDir(VERI);
			}
		}
		else
		{
			SetSliderDir(VERI);
		}
		m_oAttri.m_nScrollVal = m_oAttri.m_pCurScrollBar->value();
	}
#endif

	if (m_oAttri.m_tagSliderDir == VERI)
	{
		nOffset = nCurYPos - m_oAttri.m_oPressedAxis.y();
	}
	else
	{
		nOffset = nCurXPos - m_oAttri.m_oPressedAxis.x();
	}
	nMax = m_oAttri.m_pCurScrollBar->maximum();


	if ( m_oAttri.m_nPreOffset != nOffset )
	{
		int  curScrollBarVal = m_oAttri.m_nScrollVal-nOffset;
		if ( curScrollBarVal < 0 )
		{
			curScrollBarVal = 0;
		}
		else if ( curScrollBarVal > nMax )
		{
			curScrollBarVal = m_oAttri.m_pCurScrollBar->maximum();
		}

		m_oAttri.m_pCurScrollBar->setValue(curScrollBarVal);
		m_oAttri.m_nPreOffset = nOffset;
	}

	//滑动超过10个像素才视为已经滑动
	int tmpDiffPosX = nCurXPos-m_oAttri.m_oPressedAxis.x();
	int tmpDiffPosY = nCurYPos-m_oAttri.m_oPressedAxis.y();
	tmpDiffPosX = (tmpDiffPosX>0) ? tmpDiffPosX : (0-tmpDiffPosX);
	tmpDiffPosY = (tmpDiffPosY>0) ? tmpDiffPosY : (0-tmpDiffPosY);
	if ( tmpDiffPosX > 10 || tmpDiffPosY > 10 )
	{
		m_oAttri.m_bIsMoving = true;
	}
}

void QScrollTableWidget::mouseReleaseEvent(QMouseEvent *ev)
{
#ifndef _PSX_QT_LINUX_
	QList<QLineEdit*> oList = findChildren<QLineEdit*>();
	for (int i = 0; i < oList.size(); i++)
	{
		oList[i]->setContextMenuPolicy(Qt::NoContextMenu);
		oList[i]->installEventFilter(this);
	}
#endif

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	if ( m_oAttri.m_bIsMoving == true )
	{
		setCurrentItem(NULL);
		m_oAttri.m_oPressedAxis = QPoint(0, 0);
		m_oAttri.m_nPreOffset = 0;
		m_oAttri.m_bIsPressed = false;
		m_oAttri.m_bIsMoving = false;
		emit sig_ScrollFinished();
		return;
	}

	QTableWidget::mouseReleaseEvent( ev );
}
