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


//��굥����Ԫ���ʱ���ػ��¼�����
void QCheckBoxDelegateBase::paint(QPainter * painter,
								  const QStyleOptionViewItem & option,
								  const QModelIndex & index) const
{
	//��ȡֵ  
	bool checked = index.model()->data(index, Qt::CheckStateRole).toBool();
	//��ť�ķ��ѡ��  
	QStyleOptionButton *checkBoxOption = new QStyleOptionButton();  
	checkBoxOption->state |= QStyle::State_Enabled;  
	//����ֵ�ж��Ƿ�ѡ��  
	if(checked)  
	{  
		checkBoxOption->state |= QStyle::State_On;  
	}  
	else  
	{  
		checkBoxOption->state |= QStyle::State_Off;  
	}  
	//����QCheckBox������״  
	checkBoxOption->rect = CheckBoxRect(option);  
	//����QCheckBox  
	QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter); 
}


QRect QCheckBoxDelegateBase::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const  
{  
	//���ư�ť����Ҫ�Ĳ���  
	QStyleOptionButton checkBoxStyleOption;  
	//���ո����ķ����� ����Ԫ��������  
	QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);  
	//����QCheckBox����  
	QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,  
		viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);  
	//����QCheckBox������״  
	return QRect(checkBoxPoint, checkBoxRect.size());  
}  

//�����¼�������ֵ��ת
bool QCheckBoxDelegateBase::editorEvent(QEvent * event,
										QAbstractItemModel * model,
										const QStyleOptionViewItem & option,
										const QModelIndex & index)
{
	//��񵥻��¼�,��ת��Ϊ˫��
	if(event->type()==QEvent::MouseButtonDblClick/*MouseButtonPress*/)
	{
// 		if ((index.column() == 0)&&(index.row() == 0))
// 		{
// 			return true;
// 		}

		QVariant varValue = model->data(index,Qt::CheckStateRole);

		int nValue = varValue.toInt();

		if(varValue.isValid())//�����ǰֵ��Ч,�򽫵�ǰ״̬ȡ��
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
		else//���򽫵�ǰֵ��Ϊ1,����Ϊѡ��״̬
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
	// ���ֺ�������򣬲�ͬʱ֧�ֺ�������
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

void QScrollTableWidget::SetVertScrollWidth(long nVertScrollWidth) //��ֱ������
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

void QScrollTableWidget::SetHorizontalScrollHeight(long nLevelScrollHeight) //ˮƽ������
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
#ifndef _PSX_QT_LINUX_   //shaolei 2023-1-13 ��������Ҽ��������༭״̬
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
		// δ���������¼�����Ӧ��������
		QTableWidget::mouseMoveEvent( ev );
		return;
	}

	int nCurXPos = ev->x(), nCurYPos = ev->y();
	int nMax = 0, nOffset = 0;

#ifdef _PSX_QT_LINUX_
	//������꿪ʼ�ƶ��ķ���ȷ����������
	if(!m_oAttri.m_bIsMoving)
	{
		long nDx = nCurXPos - m_oAttri.m_oPressedAxis.x();
		long nDy = nCurYPos - m_oAttri.m_oPressedAxis.y();
		if(qAbs(nDx) > qAbs(nDy))
		{
			SetSliderDir(HORI);
			//���û�к�����������������û�����
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

	//��������10�����ز���Ϊ�Ѿ�����
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
