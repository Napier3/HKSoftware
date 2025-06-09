#include "ZTViewWidget.h"
#include "../../../../../Module/API/GlobalConfigApi.h"

QZTViewWidget::QZTViewWidget(QWidget *parent):
	QWidget(parent)
{
	m_bStart = false;

	m_TestMenu = NULL;
	m_TestAddAction = NULL;
	m_ZoomInAction = NULL;
	m_ZoomOutAction = NULL;
	m_ResetAction = NULL;

	m_TestMenu = new QMenu(this);
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
	
	m_pZTDrawView = new CZTCharDrawView();
    m_pZTDrawView->SetAxisName(g_sLangTxt_Distance_ZTYAxis,_T("t(s)"),_T("  "));
 	initPlot();
// 	IsHaveAddAct();
	m_dYMax = 0;

	CRect rcClient(0,0,width(),height());
	CDC oDC(this);
	m_pZTDrawView->SetBorder(rcClient, &oDC);

    AddDrawOptrBtns();
}

QZTViewWidget::~QZTViewWidget(void)
{
    qDeleteAll(m_listDrawOptrBtn);
    m_listDrawOptrBtn.clear();

	if (m_pZTDrawView != NULL)
	{
		delete m_pZTDrawView;
		m_pZTDrawView = NULL;
	}
}
void QZTViewWidget::initPlot()
{
	CAxisInterface *pAxisInterface = NULL;
	m_pZTDrawView->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		CDataGroup oAxisConfig;
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisGridLineColor,(long)RGB(0, 0, 0));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisGridLineColor,(long)RGB(0, 0, 0));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterLineWidth,(long)1);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterColor,(long)RGB(0, 0, 0));
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

QPushButton* QZTViewWidget::AddDrawOptrBtn(const CString &strImg, long nIndex)
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

void QZTViewWidget::UpdateDrawOptrBtns()
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

void QZTViewWidget::AddDrawOptrBtns()
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

    return;
}

void QZTViewWidget::slotDrawOptr_ZoomIn()
{
	m_pZTDrawView->ZoomIn();
	UpdateDrawCharacters();
}

void QZTViewWidget::slotDrawOptr_ZoomOut()
{
	m_pZTDrawView->ZoomOut();
	UpdateDrawCharacters();
}
void QZTViewWidget::slotDrawOptr_MoveUp()
{
	m_pZTDrawView->MoveUp();
	UpdateDrawCharacters();
}

void QZTViewWidget::slotDrawOptr_MoveDown()
{
	m_pZTDrawView->MoveDown();
	UpdateDrawCharacters();
}

void QZTViewWidget::slotDrawOptr_MoveLeft()
{
	m_pZTDrawView->MoveLeft();
	UpdateDrawCharacters();
}

void QZTViewWidget::slotDrawOptr_MoveRight()
{
	m_pZTDrawView->MoveRight();
	UpdateDrawCharacters();
}
void QZTViewWidget::slotDrawOptr_Reset()
{
    m_pZTDrawView->ZoomReset();
	UpdateDrawCharacters();
}
void QZTViewWidget::paintEvent(QPaintEvent *event)
{
	if (m_pZTDrawView == NULL)
	{
		return;
	}

	CDC oDC(this);
	oDC.begin(this);
	m_pZTDrawView->Draw(&oDC, 1, CPoint(0, 0));
	oDC.end();
}

BOOL QZTViewWidget::UpdateDrawCharacters()
{
	if (m_pZTDrawView == NULL)
	{
		return FALSE;
	}

	update();
	return TRUE;
}

void QZTViewWidget::ResizeUI(int nWidth,int nHeight)
{
	if ((nWidth<=STT_Charact_ToolBtn_Width) || (nHeight <= STT_Charact_ToolBtn_Width))
	{
		return;
	}

	CDC oDC(this);
	int nCharWidth = nWidth;
	int nCharHeigh = nHeight;

    nCharWidth -= STT_Charact_ToolBtn_Width;
    nCharHeigh -= STT_Charact_ToolBtn_Width;

	if(nHeight > 600)
	{
		CRect rcClient(0, 0, nWidth, nCharHeigh);
		m_pZTDrawView->SetBorder(rcClient, &oDC);
	}
	else
	{
		CRect rcClient(0, 0, nCharWidth, nHeight);
		m_pZTDrawView->SetBorder(rcClient, &oDC);
	}

    m_pZTDrawView->ZoomAxisReset(m_dYMax);

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

void QZTViewWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = parentWidget()->rect();
	ResizeUI(rc.width(),rc.height());
}
void QZTViewWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	UpdateDrawCharacters();
	mousePressEvent(event);   
}
void QZTViewWidget::mouseMoveEvent(QMouseEvent *event)
{
	CPoint oPoint,oPoint_x;
	oPoint.SetPoint(event->pos().x(),event->pos().y());
	oPoint_x.SetPoint(event->pos().x(),0);
	CRect rc = m_pZTDrawView->GetBorder();
	if(event->pos().x() <= rc.Width())
	{
		m_pZTDrawView->UI_OnMouseMove(0,oPoint);

		if (event->buttons() & Qt::LeftButton)
		{
			m_pZTDrawView->MouseMove_MoveTo(oPoint_x);
			UpdateDrawCharacters();

		}
	}
	event->ignore();
}
void QZTViewWidget::mousePressEvent(QMouseEvent *event)
{
	CPoint oPoint,oPoint_x;
	oPoint.SetPoint(event->pos().x(),event->pos().y());
	oPoint_x.SetPoint(event->pos().x(),0);
	CRect rc = m_pZTDrawView->GetBorder();
	if(event->pos().x() <= rc.Width())
	{
		m_pZTDrawView->SetAxisInstruct_Point(oPoint);

		if (event->button() == Qt::LeftButton)
		{
			m_pZTDrawView->LeftButtonDown();
			m_pZTDrawView->MouseMove_SetBegin(oPoint_x);

			emit sig_LeftButtonDown();
			UpdateDrawCharacters();
		}
		if (event->button() == Qt::RightButton)
		{
			if(m_bUseAddButtons)
			{
				m_fx = m_pZTDrawView->m_oAxisInstruct_Point.m_fX;	//记录右键点击的坐标
				m_fy = m_pZTDrawView->m_oAxisInstruct_Point.m_fY;

				m_TestMenu->exec(QCursor::pos());

			}
		}	
	}

	QWidget::mousePressEvent(event);
}
void QZTViewWidget::slot_ActionTestAddClicked()
{
	//emit sig_AddPointLocation(m_fx,m_fy);
	m_pZTDrawView->AddOneTestPoint(m_fx,m_fy);
}

void QZTViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}

void QZTViewWidget::wheelEvent(QWheelEvent *event)//滚轮事件
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

void QZTViewWidget::IsHaveAddAct()
{
	m_bUseAddButtons = true;

	m_TestAddAction = new QAction(g_sLangTxt_Gradient_AddExperiment,this); // 添加试验 lcq 3.14
	//m_TestAddAction = new QAction(tr("添加试验"),this);
#ifdef _PSX_QT_WINDOWS_
	m_TestAddAction->setIcon (QPixmap( "./images/Add.png"));
#else
	m_TestAddAction->setIcon (QPixmap( ":/ctrls/images/Add.png"));
#endif
	if (m_TestMenu == NULL)
	{
		return;
	}
	m_TestMenu->insertAction(0,m_TestAddAction);
	connect(m_TestAddAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestAddClicked()));
}
void QZTViewWidget::UpdateZTViewDraw(CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[])
{
	if (m_pZTDrawView == NULL)
	{
		return;
	}

	m_pZTDrawView->ClearTestLines();
	//m_pZTDrawView->ClearSearchPoints(-1);

	//20241009 luozibing 排除中间存在的无效区段数据 
	CString strName_Temp[10];
	double dZSeting_Temp[10] = { 0 };
	double dTSeting_Temp[10] = { 0 };
	double dPlus_Temp[10] = { 0 };
	double dMinus_Temp[10] = { 0 };
	int ZoneNum = 0;
	for (int i = 0; i < 10; i++)
	{
		if (dTSeting[i] == 0 && dZSeting[i] == 0)
		{
			continue;
		}
		strName_Temp[ZoneNum] = strName[i];
		dZSeting_Temp[ZoneNum] = dZSeting[i];
		dTSeting_Temp[ZoneNum] = dTSeting[i];
		dPlus_Temp[ZoneNum] = dPlus[i];
		dMinus_Temp[ZoneNum] = dMinus[i];
		ZoneNum++;
	}
	UpdateZTViewDraw(ZoneNum, strName_Temp, dZSeting_Temp, dTSeting_Temp, dPlus_Temp, dMinus_Temp);
}
void QZTViewWidget::UpdateZTViewDraw(int nNum,CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[])
{
	BOOL bFirstPositive = FALSE;
	BOOL bFirstNegative = FALSE;
	BOOL bDrawV = FALSE;
	int nMaxX, nMinX;

	nMaxX = -1;//20240925 luozibing 记录最后存在数据的数组下标
	nMinX = -1;

	//20240709 luozibing 绘制线段
	for (int i = 0; i<nNum; i++)
	{
		if (dTSeting[i] == 0 && dZSeting[i] == 0)
		{
			continue;
		}
		bDrawV = TRUE;
		//if (dZSeting[i]>nMaxLine_X)//记录最大X数据
		//{
		//	nMaxX = i;
		//	nMaxLine_X = dZSeting[i];
		//}
		//if (dZSeting[i] < nMinLine_X)
		//{
		//	nMinX = i;
		//	nMinLine_X = dZSeting[i];
		//}
		if (dTSeting[i]>m_dYMax)
		{
			m_dYMax = dTSeting[i];
		}

		nMaxX = i;
		if (dTSeting[i] > 0 && !bFirstPositive)
		{// 第一次画正数横线从x= 0 开始
			bFirstPositive = TRUE;
			m_pZTDrawView->AddOneTestLine(strName[i], 0, dTSeting[i], dZSeting[i], dTSeting[i], dPlus[i], dMinus[i]);
		}
		else if (dZSeting[i] < 0 && !bFirstNegative)
		{// 第一次画负数横线从x= 0 开始
			bFirstNegative = TRUE;
			m_pZTDrawView->AddOneTestLine(strName[i], 0, dTSeting[i], dZSeting[i], dTSeting[i], dPlus[i], dMinus[i]);
		}
		else
		{
			double dPrevZSeting;
			if (i == 0)
			{
				bFirstPositive = TRUE;
				dPrevZSeting = 0;
			}
			else
			{
				dPrevZSeting = dZSeting[i - 1];
			}
			m_pZTDrawView->AddOneTestLine(strName[i], dPrevZSeting, dTSeting[i], dZSeting[i], dTSeting[i], dPlus[i], dMinus[i]);
		}
		//画中间竖线 
		//20240925 luozibing 测试修改 下一节点无数据时不显示竖线
		if (!(dTSeting[i + 1] == 0 && dZSeting[i + 1] == 0) && bDrawV)
		{
			double dNextTSeting;
			dNextTSeting = dTSeting[i + 1];
			m_pZTDrawView->AddOneTestLine(strName[i], dZSeting[i], dTSeting[i], dZSeting[i], dNextTSeting, dPlus[i], dMinus[i]);
		}
	}
	// 画边缘竖线
	/*if (bDrawV)
	{
	if (nMaxLine_X != 0 & nMinX != -1)
	{
	m_pZTDrawView->AddOneTestLine(ZTVIEW_MINIMUM_VERTICAL_LINE, dZSeting[nMinX], dTSeting[nMinX], dZSeting[nMinX], 99, dPlus[nMinX], dMinus[nMinX]);
	}
	if (nMinLine_X != 0 & nMaxX != -1)
	{
	m_pZTDrawView->AddOneTestLine(ZTVIEW_MAXIMUM_VERTICAL_LINE, dZSeting[nMaxX], dTSeting[nMaxX], dZSeting[nMaxX], 99, dPlus[nMaxX], dMinus[nMaxX]);
	}
	}*/
	//20240925 luozibing 不考虑阻抗值为负的情况下，绘制最后一条横线对应的竖线
	if (bDrawV)
	{
		m_pZTDrawView->AddOneTestLine(ZTVIEW_MAXIMUM_VERTICAL_LINE, dZSeting[nMaxX], dTSeting[nMaxX], dZSeting[nMaxX], 99, dPlus[nMaxX], dMinus[nMaxX]);
	}


	ResizeUI(width(), height());
	UpdateDrawCharacters();
}
void QZTViewWidget::SetImpTestLines(BOOL b)
{
	m_ImpSearch = b;
	m_pZTDrawView->m_ImpSearch = b;
}
void QZTViewWidget::SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype)
{
	m_pZTDrawView->SetAngleAndFaultype(strAngle,strFaultype);
}
void QZTViewWidget::AddOneTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY)
{
	m_pZTDrawView->AddOneTestPoint(strIDPath, strFaultType, dX, dY);
	update();
}
void QZTViewWidget::DeleteTestPoint(const CString &strIDPath)
{
	m_pZTDrawView->DeleteTestPoint(strIDPath);
	update();
}
void QZTViewWidget::UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, bool bSelPonit)
{
	if (!m_pZTDrawView->UpdateTestPoint(strIDPath, strFaultType, dX, dY, bSelPonit))
	{
		m_pZTDrawView->AddOneTestPoint(strIDPath, strFaultType, dX, dY);
	}
	update();
}