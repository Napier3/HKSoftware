#include "SttSclIedViewWidget.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

QSttSclIedViewWidget::QSttSclIedViewWidget(QWidget *parent)
	: QWidget(parent),m_zoomCount(0),m_canvasWidth(920),m_canvasHeight(520),m_minCanvasWidth(920),m_pRoot(parent)
{
	m_scdView = new QSttSclIedChildViewWidget(this,parent);
	//m_scdView->m_pRoot=m_pRoot;
	connect(m_scdView, SIGNAL(IEDClickedSignal(int )), this, SIGNAL(IEDClickedSignal(int )));

	scrollArea = new QScrollArea;
	//scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(m_scdView);

	//QPushButton *button = new QPushButton(tr("导出"));
	//connect(button, SIGNAL(clicked()),SLOT(OnExportBtnClicked()));
	//button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	QPushButton *zoomInButton = new QPushButton(/*tr("放大")*/g_sLangTxt_State_Magnify);
	connect(zoomInButton, SIGNAL(clicked()), SLOT(OnZoomInBtnClicked()));
	QPushButton *zoomOutButton = new QPushButton(/*tr("缩小")*/g_sLangTxt_State_Shrink);
	connect(zoomOutButton, SIGNAL(clicked()), SLOT(OnZoomOutBtnClicked()));

	QHBoxLayout *hBoxLayout = new QHBoxLayout;
	hBoxLayout->setMargin(0);
	hBoxLayout->addStretch();
	hBoxLayout->addWidget(zoomInButton);
	hBoxLayout->addWidget(zoomOutButton);

	QVBoxLayout *vBoxLayout = new QVBoxLayout;
	vBoxLayout->setMargin(0);
	//hBoxLayout->addWidget(button, Qt::AlignRight);
	vBoxLayout->addLayout(hBoxLayout);
	vBoxLayout->addWidget(scrollArea);
	setLayout(vBoxLayout);

	m_size.setHeight(g_canvas_heigh);
	m_size.setWidth(g_canvas_width);
}

QSttSclIedViewWidget::~QSttSclIedViewWidget()
{

}

void QSttSclIedViewWidget::ShowIED(CSclIed *pSclIed)
{

	//将缩放还原
	m_factor = 1.0;

	//Fix放大问题，该处移除
	//while(m_zoomCount >0)
	//{
	//	zoomOut();
	//	m_zoomCount--;
	//}

	m_scdView->InitData(pSclIed, m_minCanvasHeight);
	m_canvasHeight = m_minCanvasHeight;
	m_scdView->resize(m_canvasWidth, m_canvasHeight);
}

void QSttSclIedViewWidget::zoomIn()
//! [9] //! [10]
{
	scaleImage(1.25);
}

void QSttSclIedViewWidget::zoomOut()
{
	scaleImage(0.8);
}

void QSttSclIedViewWidget::scaleImage(double factor)
//! [23] //! [24]
{
	m_factor *= factor;
	m_scdView->resize(m_factor * QSize(m_canvasWidth, m_canvasHeight));
	m_scdView->ZoomIn(factor);

	adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void QSttSclIedViewWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
	scrollBar->setValue(int(factor * scrollBar->value()
		+ ((factor - 1) * scrollBar->pageStep()/2)));
}

// 滚轮事件
void QSttSclIedViewWidget::wheelEvent(QWheelEvent *event)
{
	return;

	// 当滚轮远离使用者时进行放大，当滚轮向使用者方向旋转时进行缩小
	if(event->delta() > 0)
	{
		if (m_zoomCount >= 3)
			return ;

		zoomIn();
		m_zoomCount++;
	}
	else
	{
		if(m_zoomCount == 0)
			return;

		zoomOut();
		m_zoomCount--;
	}
}

void QSttSclIedViewWidget::resizeEvent ( QResizeEvent * /*event*/ )
{
	//获取窗口宽度
 	QSize size = scrollArea->maximumViewportSize();
	m_canvasHeight = size.height() > m_minCanvasHeight ? size.height() : m_minCanvasHeight;
	m_canvasWidth = size.width() > m_minCanvasWidth ? size.width() : m_minCanvasWidth;

	scaleImage(1.0);

	m_scdView->InitScrollData(scrollArea->verticalScrollBar());
}

void QSttSclIedViewWidget::OnIEDClicked(int index)
{
	emit IEDClickedSignal(index);
}

void QSttSclIedViewWidget::OnExportBtnClicked()
{
	m_scdView->ExportPicture(300, 200*m_canvasHeight/520);
}

void QSttSclIedViewWidget::OnZoomInBtnClicked()
{
	//Fix放大问题
//	if (m_zoomCount >= 3)
//		return ;

	zoomIn();

//	m_zoomCount++;
}

void QSttSclIedViewWidget::OnZoomOutBtnClicked()
{
	//Fix放大问题
//	if(m_zoomCount == 0)
//		return;

	zoomOut();

//	m_zoomCount--;
}