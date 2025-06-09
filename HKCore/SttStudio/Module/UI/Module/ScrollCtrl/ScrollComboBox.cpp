#include "ScrollComboBox.h"

#include <QAbstractItemView>

#include "../../../../../Module/Log/LogPrint.h"
//#include "../../SttTestCntrFrameBase.h"

extern long g_nComBoxItemHeight;// = 50
extern long g_nComBoxVertScrollWidth;// = 50
long Global_GetComBoxItemHeight()
{
    return g_nComBoxItemHeight;
}


#define CBB_LIST_WIDTH	300

QScrollComboBox::QScrollComboBox(QWidget* pParent,bool bwidthflag) : QComboBox(pParent)
{
	m_bIsScrolling = false;
	m_nLastIndex = 0;
	m_bFirstHidePopup = 1;
	m_bIgnoreFirstHidePopup = 0;
	m_pListView = new QScrollListView(this);
	m_pModel = NULL;
	setView(m_pListView);
	setMaxVisibleItems(5);

#ifdef _PSX_QT_LINUX_
	QFont Font = this->font();
	Font.setPixelSize(20);
	setFont(Font);
#endif

	//2024-4-29 wuxinyi 下拉框滑动条宽度需加宽故改为45
	g_nComBoxVertScrollWidth = 50;
	long nHeight = Global_GetComBoxItemHeight();
	SetCoboboxVertScrollWidth(g_nComBoxVertScrollWidth,nHeight);
#ifdef _PSX_QT_LINUX_
	/*long nHeight = Global_GetComBoxItemHeight();
	CString strStyle;
	strStyle.Format("QComboBox { min-height: 24px;}"
		"QComboBox QAbstractItemView::item { min-height: %dpx;}",nHeight);
	setStyleSheet(strStyle);*/
	if (bwidthflag)
	{
	view()->setFixedWidth(CBB_LIST_WIDTH);
	}
	else
	{
		view()->setMinimumSize(0, 0);
		view()->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
	}

#endif

	if (g_pSttGlobalFont)
	{
		m_pListView->setFont(*g_pSttGlobalFont);
	}

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_IndexChanged(int)));
	connect(this, SIGNAL(activated(int)), this, SLOT(slot_IndexChanged(int)));

	QScrollBar *scrollBar = m_pListView->verticalScrollBar();
        scrollBar->setSingleStep(1); // 设置滑动条的步长
}

QScrollComboBox::~QScrollComboBox()
{
	if(m_pListView)
	{
		delete m_pListView;
		m_pListView = NULL;
	}
}

void QScrollComboBox::SetDefaultVisibleItems()
{
	setMaxVisibleItems(10);
}

//如果后期需要用到tip来显示项的全部字符串,则启用该函数
// void QScrollComboBox::addItem(const QString &text, const QVariant &userData)
// {
// #ifndef _PSX_QT_LINUX_
// 	if(m_pModel == NULL)
// 	{
// 		m_pModel = new QStandardItemModel(this);
// 		setModel(m_pModel);
// 	}
// 
// 	QStandardItem* pItem = new QStandardItem(text);
// 	pItem->setToolTip(text);
// 	pItem->setData(userData);
// 	m_pModel->appendRow(pItem);
// #else
// 	QComboBox::addItem(text, userData);
// #endif
// }

void QScrollComboBox::SetBoxSize(long nFontSize, long nItemSize)
{
	ComboBox_SetSize(nFontSize, nItemSize, this);
}

void QScrollComboBox::hidePopup()
{
	if(!m_pListView->IsMoving())
	{
		if (isHidden())
		{
			return;
		}

		if (m_bIgnoreFirstHidePopup && m_bFirstHidePopup)
		{
			m_bFirstHidePopup = 0;
			return;
		}

		QComboBox::hidePopup();
	}
}

//如果有用户自定义的currentIndexChanged或者activated信号,则需要判断IsScrolling
void QScrollComboBox::slot_IndexChanged(int index)
{
	if(m_pListView->IsMoving())
	{
		m_bIsScrolling = true;
		setCurrentIndex(m_nLastIndex);
	}
	else
	{
		m_bIsScrolling = false;
	}
	m_pListView->SetPressed(false);
	m_pListView->SetMoving(false);
}

void QScrollComboBox::mousePressEvent(QMouseEvent *ev)
{
	m_nLastIndex = currentIndex();

	long nMaxLen = 0;
	for (int i = 0; i < count(); i++)
	{
		CString strText = itemText(i);
		nMaxLen = strText.GetLength() > nMaxLen ? strText.GetLength() : nMaxLen;
	}

	if(nMaxLen * 20 * 2 / 3 > CBB_LIST_WIDTH)
	{
		view()->setFixedWidth(nMaxLen * 16);
	}
	QComboBox::mousePressEvent( ev );

	
}
/*
void QScrollComboBox::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) 
	{
		// 如果左键被按下，则记录当前的鼠标位置
		lastPos = event->pos();
	}

	QComboBox::mousePressEvent(event);
}

void QScrollComboBox::mouseMoveEvent(QMouseEvent *event)
{   
	
	// 计算鼠标在ComBobox中移动的位移量
	int dy = event->pos().y() - lastPos.y();

	// 获取当前ComBobox上的item数量
	int counts = count();

	// 获取当前选中的item index
	int currentIndexs = currentIndex();

	// 根据鼠标是否向上或者向下移动，来决定要设置的新的index
	int newIndex = dy > 0 ? (currentIndexs + 1) : (currentIndexs - 1);

	// 如果新index大于item数量或者小于0，则不做任何处理
	if (newIndex < 0 || newIndex > (counts - 1)) 
		return;

	// 更新lastPos的位置，以便下一次计算位移量时使用
	lastPos = event->pos();

	// 调用setCurrentIndex来更新ComBobox中选中的item index
	setCurrentIndex(newIndex);

	QComboBox::mouseMoveEvent(event);
}

void QScrollComboBox::mouseReleaseEvent(QMouseEvent *event) 
{  
	lastPos = QPoint(-1, -1);  

	QComboBox::mouseReleaseEvent(event);  
} 
*/

void ComboBox_SetSize(long nFontSize, long nItemSize, QComboBox *pComboBox)
{
	if(nFontSize)
	{
		QFont Font = pComboBox->font();
		Font.setPixelSize(nFontSize);
		pComboBox->setFont(Font);
	}

	if(nItemSize)
	{
		CString strHeight;
		strHeight.Format("QComboBox { min-height: %dpx;}"
			"QComboBox QAbstractItemView::item { min-height: %dpx;}", nItemSize, nItemSize);
		pComboBox->setStyleSheet(strHeight);
	}
	
}

void QScrollComboBox::setFixedWidth_All(long nComboxWidth,long nListView)
{
	setFixedWidth(nComboxWidth);

	if (m_pListView == NULL)
	{
		return;
	}

	m_pListView->setFixedWidth(nListView);
}

void QScrollComboBox::SetCoboboxVertScrollWidth(long nComBoxVertWidth,long nHeights)
{
	CString strSheetStyle;

#ifdef _PSX_QT_LINUX_
	strSheetStyle.Format(_T("QScrollBar:vertical{border: 2px;width:%ldpx;}"
						"QScrollBar::add-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
							"QScrollBar::sub-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
							"QComboBox { min-height: 24px;}"
							"QScrollBar::handle:vertical {min-height: 120px;}"
                        "QComboBox QAbstractItemView::item { min-height: %ldpx;}"),nComBoxVertWidth,nHeights);

/*
#else
	strSheetStyle.Format(_T("QScrollBar:vertical{margin:30px 0px 30px 0px;background-color:#F0F1EF;border: 0px;width:30px;}"
		"QScrollBar::handle:vertical{background-color:#bbbbbb;width:%ldpx;border-radius:7px;}"
		"QScrollBar::handle:vertical:hover{background-color:#9B9B9B;width:30px;border-radius:7px;}"
		"QScrollBar::add-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
		"QScrollBar::sub-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
		"QScrollBar::add-page:vertical{background-color:rgb(240,241,239);}"
		"QScrollBar::sub-page:vertical {background-color:rgb(240,241,239);}"
		"QScrollBar::up-arrow:vertical{border:0px;width:30px;height:30px;}"
		"QScrollBar::up-arrow:vertical:pressed{border:0px;width:30px;height:30px;}"
		"QScrollBar::down-arrow:vertical{border:0px;width:30px;height:30px;}"
		"QScrollBar::down-arrow:vertical:pressed {border:0px;width:30px;height:30px;}"),nComBoxVertWidth,nHeights);
		

	"QScrollBar:vertical {border: 2px solid grey;width: 80px;}"
 		"QScrollBar::handle:vertical {background: lightgrey;min-height: 20px;}"
 		"QScrollBar::add-line:vertical {background: lightgrey;}"
 		"QScrollBar::sub-line:vertical {background: lightgrey;}")
 
 	QScrollBar:vertical {border: 2px solid grey;width: %ldpx;}"
 	"QComboBox QAbstractItemView:vertical {width: %ldpx;}"
							"QComboBox { min-height: 24px;}"
 	"QComboBox QAbstractItemView::item { min-height: %ldpx;}"
 	*/

#endif
//	QString str;
//	str = styleSheet();
	setStyleSheet(strSheetStyle);
	
}


/*"QScrollBar:vertical{margin:30px 0px 30px 0px;background-color:#F0F1EF;border: 0px;width:30px;}"
"QScrollBar::handle:vertical{background-color:#bbbbbb;width:%ldpx;border-radius:7px;}"
"QScrollBar::handle:vertical:hover{background-color:#9B9B9B;width:30px;border-radius:7px;}"
"QScrollBar::add-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
"QScrollBar::sub-line:vertical{subcontrol-origin: margin;border:1px solid rgb(240,241,239);height:30px;}"
"QScrollBar::add-page:vertical{background-color:rgb(240,241,239);}"
"QScrollBar::sub-page:vertical {background-color:rgb(240,241,239);}"
"QScrollBar::up-arrow:vertical{border:0px;width:30px;height:30px;}"
"QScrollBar::up-arrow:vertical:pressed{border:0px;width:30px;height:30px;}"
"QScrollBar::down-arrow:vertical{border:0px;width:30px;height:30px;}"
"QScrollBar::down-arrow:vertical:pressed {border:0px;width:30px;height:30px;}"
*/
/*

"QScrollBar:vertical {width: 10px;background-color: #f1ee04; }"

*/

/*
QComboBox {border :  1px  solid  gray ;border-radius:  3px ;padding :  1px  2px  1px  2px ;min-width :  9em ; }
*/


/*

"QScrollBar:vertical {border: 2px solid grey; min-width: 80px;}"


*/

/*
"QScrollBar:vertical {border: 2px solid grey;width: 80px;}"
"QComboBox QAbstractItemView:vertical {width: 80px;}");"
*/

/*

*/
