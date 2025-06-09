#include "SwingImpChartWidget.h"
#include <QResizeEvent>

#include "../../../../Module/API/GlobalConfigApi.h"

#include <QCoreApplication>
//#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>
#include "../SttTestCntrFrameBase.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../XLangResource_Native.h"
#include "../SttTestCntrFrameAPI.h"

QSwingImpChartWidget::QSwingImpChartWidget(QWidget *parent, bool bUseOptrButtons, BOOL bUseMouseMoveChar) :
    QWidget(parent)
{
	m_bViewTestLines = FALSE;
	m_bHasResize = FALSE;

	m_TestMenu = NULL;
	m_TestAddAction = NULL;
	m_ZoomInAction = NULL;
	m_ZoomOutAction = NULL;
	m_ResetAction = NULL;
	m_bUseOptrButtons = bUseOptrButtons;
	m_bUseAddButtons = m_bUseOptrButtons;

	m_TestMenu = new QMenu(this);

	if (bUseOptrButtons)
	{
#ifdef _PSX_QT_WINDOWS_
		//m_ZoomInAction = new QAction(tr("放大"),this);
		m_ZoomInAction = new QAction(g_sLangTxt_State_Magnify,this);  //放大 lcq 3.14
		m_ZoomInAction->setIcon (QPixmap( "../Resource/ZoomIn.png"));
		m_TestMenu->addAction(m_ZoomInAction);
		connect(m_ZoomInAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomIn()));

		//m_ZoomOutAction = new QAction(tr("缩小"),this);
		m_ZoomOutAction = new QAction(g_sLangTxt_State_Shrink,this); //缩小 lcq 3.14
		m_ZoomOutAction->setIcon (QPixmap( "../Resource/ZoomOut.png"));
		m_TestMenu->addAction(m_ZoomOutAction);
		connect(m_ZoomOutAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomOut()));

		//m_ResetAction = new QAction(tr("复位"),this);
		m_ResetAction = new QAction(g_sLangTxt_State_Reposition,this); //复位 lcq 3.14
		m_ResetAction->setIcon (QPixmap( "../Resource/ZoomReset.png"));
		m_TestMenu->addAction(m_ResetAction);
		connect(m_ResetAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_Reset()));
#else
		m_ZoomInAction = new QAction(g_sLangTxt_State_Magnify,this);  //放大 lcq 3.14
		m_ZoomInAction->setIcon (QPixmap( ":/ctrls/images/ZoomIn.png"));
		m_TestMenu->addAction(m_ZoomInAction);
		connect(m_ZoomInAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomIn()));

		m_ZoomOutAction = new QAction(g_sLangTxt_State_Shrink,this); //缩小 lcq 3.14
		m_ZoomOutAction->setIcon (QPixmap( ":/ctrls/images/ZoomOut.png"));
		m_TestMenu->addAction(m_ZoomOutAction);
		connect(m_ZoomOutAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomOut()));

		m_ResetAction = new QAction(g_sLangTxt_State_Reposition,this); //复位 lcq 3.14
		m_ResetAction->setIcon (QPixmap( ":/ctrls/images/ZoomReset.png"));
		m_TestMenu->addAction(m_ResetAction);
		connect(m_ResetAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_Reset()));
#endif
	}

	m_strXAxis = _T("R");
	m_strYAxis = _T("X");
	m_strTitle = _T(" ");

	m_pCharacterDrawView = new CSwingImpChartDrawView();
	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	//第三个和第四个参数，都传递为FALSE，表示不显示特性曲线默认的测试线
    m_pCharacteristics = stt_Frame_Characteristics();
    m_pCharacteristics->CalCharElement(NULL);
    m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);
	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
	initPlot();

	if (bUseOptrButtons)
	{
		AddDrawOptrBtns();
	}

 	CRect rcClient(0,0,width(),height());
 	CDC oDC(this);
 	m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	//	ResizeUI(487,651/*width(),height()*/);
	
	m_bUseMouseMoveChar = bUseMouseMoveChar;
}

void QSwingImpChartWidget::SetImpDatas()
{
	m_pCharacterDrawView->SetCharacterDatas();
	update();

	return;
}

void QSwingImpChartWidget::SetTestPoint(double dX, double dY)
{
	m_pCharacterDrawView->SetTestPoint(dX, dY);
	update();

	return;
}

void QSwingImpChartWidget::AddDrawOptrBtns()
{
	long nIndex = 0;
	QPushButton *pBtn = AddDrawOptrBtn("zoomin.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomIn()));

	pBtn = AddDrawOptrBtn("zoomout.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomOut()));

	pBtn = AddDrawOptrBtn("zoomreset.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_Reset()));

	pBtn = AddDrawOptrBtn("moveup.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveUp()));

	pBtn = AddDrawOptrBtn("movedown.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveDown()));

	pBtn = AddDrawOptrBtn("moveleft.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveLeft()));

	pBtn = AddDrawOptrBtn("moveright.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveRight()));
}

QPushButton* QSwingImpChartWidget::AddDrawOptrBtn(const CString &strImg, long nIndex)
{
	QPushButton *pBtn = new QPushButton(this);
	CString strIcon, strPath;
#ifdef _PSX_QT_WINDOWS_
	strPath = _P_GetResourcePath();
#else
	strPath = ":/ctrls/images/";
#endif
	strIcon = strPath + strImg;
	QIcon icon(strIcon);
	pBtn->setIcon(icon);
	pBtn->setIconSize(QSize(STT_Charact_ToolBtn_Width, STT_Charact_ToolBtn_Width));
	//pBtn->setFlat(true);
	m_listDrawOptrBtn.append(pBtn);
	return pBtn;
}

QSwingImpChartWidget::~QSwingImpChartWidget()
{
	qDeleteAll(m_listDrawOptrBtn);
	m_listDrawOptrBtn.clear();
//	if(NULL != m_pCharacteristics)
//		delete m_pCharacteristics;
	if(NULL != m_pCharacterDrawView)
		delete m_pCharacterDrawView;
}

void QSwingImpChartWidget::slotDrawOptr_ZoomIn()
{
	m_pCharacterDrawView->ZoomIn();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_ZoomOut()
{
	m_pCharacterDrawView->ZoomOut();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_Reset()
{
	m_pCharacterDrawView->ZoomReset();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_MouseZoom()
{
	//m_pCharacterDrawView->zoomm();
}

void QSwingImpChartWidget::slotDrawOptr_MoveUp()
{
	m_pCharacterDrawView->MoveUp();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_MoveDown()
{
	m_pCharacterDrawView->MoveDown();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_MoveLeft()	
{
	m_pCharacterDrawView->MoveLeft();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::slotDrawOptr_MoveRight()
{
	m_pCharacterDrawView->MoveRight();
	UpdateDrawCharacters();
}

void QSwingImpChartWidget::paintEvent(QPaintEvent *event)
{
	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	CDC oDC(this);
	oDC.begin(this);
	m_pCharacterDrawView->Draw(&oDC, 1, CPoint(0, 0));
	oDC.end();
}

void QSwingImpChartWidget::wheelEvent(QWheelEvent *event)
{
    double dData = event->delta();

    if (dData>0)
    {
        slotDrawOptr_ZoomIn();
    }
    else
    {
        slotDrawOptr_ZoomOut();
    }
}

BOOL QSwingImpChartWidget::UpdateDrawCharacters()
{
	if (m_pCharacterDrawView == NULL)
	{
		return FALSE;
	}

	update();
	return TRUE;
}

void QSwingImpChartWidget::UpdateDrawOptrBtns()
{
	QRect rc = parentWidget()->rect();
	long nHeight = rc.height();
	if(nHeight > 600)
	{
		long nWidth = rc.width();
		nWidth = (nWidth - 7 * 50) / 6;

		for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
		{
			m_listDrawOptrBtn[i]->setGeometry(i * (50 + nWidth), rc.height() - STT_Charact_ToolBtn_Width , 50, 50);
		}
	}
	else
	{
		nHeight = (nHeight - 7 * 50 - 60) / 6;

		for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
		{
			m_listDrawOptrBtn[i]->setGeometry(rc.right() - STT_Charact_ToolBtn_Width, 30 + i * (50 + nHeight), 50, 50);
		}
	}
}

void QSwingImpChartWidget::ResizeUI(int nWidth,int nHeight)
{
	if ((nWidth<=STT_Charact_ToolBtn_Width) || (nHeight <= STT_Charact_ToolBtn_Width))
	{
		return;
	}

	CDC oDC(this);
    nWidth -= 30;
    nHeight -= 30;
	int nCharWidth = nWidth;
	int nCharHeigh = nHeight;

	if (m_bUseOptrButtons)
	{
		nCharWidth -= STT_Charact_ToolBtn_Width;
		nCharHeigh -= STT_Charact_ToolBtn_Width;
	}

	if(nHeight > 600)
	{
		CRect rcClient(0, 0, nWidth, nCharHeigh);
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}
	else
	{
		CRect rcClient(0, 0, nCharWidth, nHeight);
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}

	if (m_bUseOptrButtons)
	{
		if(nHeight > 600)
		{
			nWidth = (nWidth - 7 * STT_Charact_ToolBtn_Width) / 6;

			for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
			{
				m_listDrawOptrBtn[i]->setGeometry(i * (STT_Charact_ToolBtn_Width + nWidth), nHeight - STT_Charact_ToolBtn_Width, STT_Charact_ToolBtn_Width, STT_Charact_ToolBtn_Width);
			}
		}
		else
		{
			nHeight = (nHeight - 7 * STT_Charact_ToolBtn_Width - 60) / 6;

			for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
			{
				m_listDrawOptrBtn[i]->setGeometry(nWidth - STT_Charact_ToolBtn_Width, 30 + i * (STT_Charact_ToolBtn_Width + nHeight), STT_Charact_ToolBtn_Width, STT_Charact_ToolBtn_Width);
			}
		}
	}

//	update();
}

void QSwingImpChartWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = parentWidget()->rect();
	ResizeUI(rc.width(),rc.height());

// 	CDC oDC(this);
// 	int nWidth = rc.width();
// 	int nHeigh = rc.height();
// 
// 	if (m_bUseOptrButtons)
// 	{
// 		nWidth -= STT_Charact_ToolBtn_Width;
// 		nHeigh -= STT_Charact_ToolBtn_Width;
// 	}
// 
// 	if(rc.height() > 600)
// 	{
// 		CRect rcClient(0, 0, rc.width(), nHeigh/*rc.height() - STT_Charact_ToolBtn_Width*/);
// 		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
// 	}
// 	else
// 	{
// 		CRect rcClient(0, 0, nWidth/*rc.width() - STT_Charact_ToolBtn_Width*/, rc.height());
// 		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
// 	}
// 
// 	if (m_bUseOptrButtons)
// 	{
// 		UpdateDrawOptrBtns();
// 	}
}

void QSwingImpChartWidget::initPlot()
{
	CAxisInterface *pAxisInterface = NULL;
	m_pCharacterDrawView->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		CDataGroup oAxisConfig;
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterLineWidth,(long)2);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterColor,(long)RGB(172, 172, 172));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisScaleFont,(long)12);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisNameFont,(long)14);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisTopGap,(long)26);
		pAxisInterface->SetAxisConfig(&oAxisConfig);
	}
}

void QSwingImpChartWidget::slot_ZKDel( int key)
{
	UpdateDrawCharacters();
}


void QSwingImpChartWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	UpdateDrawCharacters();
	mousePressEvent(event);   

	emit sig_UpdatePointLocation(m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX,m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY);
}

void QSwingImpChartWidget::mouseMoveEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	CRect rc = m_pCharacterDrawView->GetBorder();
	if(event->pos().x() <= rc.Width())
	{
		m_pCharacterDrawView->UI_OnMouseMove(0,oPoint);

		if (event->buttons() & Qt::LeftButton)
		{
			if (m_bUseMouseMoveChar)
			{
				m_pCharacterDrawView->MouseMove_MoveTo(oPoint);
				UpdateDrawCharacters();
			}
		}
	}

	event->ignore();
}

void QSwingImpChartWidget::mousePressEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	CRect rc = m_pCharacterDrawView->GetBorder();
	if(event->pos().x() <= rc.Width())
	{
		m_pCharacterDrawView->SetAxisInstruct_Point(oPoint);

		if (event->button() == Qt::LeftButton)
		{
			if (m_bUseMouseMoveChar)
			{
				m_pCharacterDrawView->MouseMove_SetBegin(oPoint);
			}

			emit sig_LeftButtonDown();
			UpdateDrawCharacters();
		}
		if (event->button() == Qt::RightButton)
		{
			if(m_bUseAddButtons)
			{
				m_fx = m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX;	//记录右键点击的坐标
				m_fy = m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY;

				m_TestMenu->exec(QCursor::pos());

			}
		}	
	}

	QWidget::mousePressEvent(event);
}

void QSwingImpChartWidget::slot_ActionTestAddClicked()
{
	emit sig_AddPointLocation(m_fx,m_fy);
}

void QSwingImpChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}

void QSwingImpChartWidget::SetAxisName( const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle )
{
	m_strXAxis = strXAxisName;
	m_strYAxis = strYAxisName;
	m_strTitle = strAxisTitle;

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
}

void QSwingImpChartWidget::EnableSetting(BOOL bUseMouseMoveChar)
{
	m_bUseMouseMoveChar = bUseMouseMoveChar;
}

void QSwingImpChartWidget::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic)
{
	

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);	//上面有代码会将坐标改为x-y 故在此调用修改坐标 20211013 sf

	initPlot();	//sf 20211027 重新设置坐标格式

	ResizeUI(width(),height());
	UpdateDrawCharacters();
}
















