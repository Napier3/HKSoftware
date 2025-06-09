#include "QImpCharactWidget.h"
#include <QResizeEvent>

#include "../../../../Module/API/GlobalConfigApi.h"

#include <QCoreApplication>
//#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>
#include "../../SttTestCntrFrameBase.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../XLangResource_Native.h"

QImpCharactWidget::QImpCharactWidget(QWidget *parent, bool bUseOptrButtons, BOOL bUseMouseMoveChar) :
    QWidget(parent)
{
	m_bStart = false;
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
	m_strTitle = _T("R-X(omg)");

	m_pCharacteristic = NULL;
	m_pCharacteristics = g_theTestCntrFrame->m_pCharacteristics;

	m_pCharacteristics->CalCharElement(NULL);
	m_pCharacterDrawView = new CPsuCharDrawView();
	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	//第三个和第四个参数，都传递为FALSE，表示不显示特性曲线默认的测试线
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

void QImpCharactWidget::AddDrawOptrBtns()
{
	long nIndex = 0;
	QPushButton *pBtn = AddDrawOptrBtn("zoomin.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomIn()));

	pBtn = AddDrawOptrBtn("zoomout.png", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomOut()));

// 	pBtn = AddDrawOptrBtn("zoommouse", nIndex++);
// 	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MouseZoom()));

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

QPushButton* QImpCharactWidget::AddDrawOptrBtn(const CString &strImg, long nIndex)
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
	pBtn->setIconSize(QSize(50, 50));
	//pBtn->setFlat(true);
	m_listDrawOptrBtn.append(pBtn);
	return pBtn;
}

QImpCharactWidget::~QImpCharactWidget()
{
	qDeleteAll(m_listDrawOptrBtn);
	m_listDrawOptrBtn.clear();
}

void QImpCharactWidget::slotDrawOptr_ZoomIn()
{
	m_pCharacterDrawView->ZoomIn();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_ZoomOut()
{
	m_pCharacterDrawView->ZoomOut();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_Reset()
{
	m_pCharacterDrawView->ZoomReset();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_MouseZoom()
{
	//m_pCharacterDrawView->zoomm();
}

void QImpCharactWidget::slotDrawOptr_MoveUp()
{
	m_pCharacterDrawView->MoveUp();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_MoveDown()
{
	m_pCharacterDrawView->MoveDown();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_MoveLeft()	
{
	m_pCharacterDrawView->MoveLeft();
	UpdateDrawCharacters();
}

void QImpCharactWidget::slotDrawOptr_MoveRight()
{
	m_pCharacterDrawView->MoveRight();
	UpdateDrawCharacters();
}

void QImpCharactWidget::paintEvent(QPaintEvent *event)
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

void QImpCharactWidget::UI_SetActiveElement(CXDrawElement *pElement)
{
	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	m_pCharacterDrawView->UI_SetActiveElement(pElement);
	update();
}

BOOL QImpCharactWidget::UpdateDrawCharacters()
{
	if (m_pCharacterDrawView == NULL)
	{
		return FALSE;
	}

	update();
	return TRUE;
}

void QImpCharactWidget::UpdateDrawOptrBtns()
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

void QImpCharactWidget::ResizeUI(int nWidth,int nHeight)
{
	if ((nWidth<=STT_Charact_ToolBtn_Width) || (nHeight <= STT_Charact_ToolBtn_Width))
	{
		return;
	}

	CDC oDC(this);
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
			nWidth = (nWidth - 7 * 50) / 6;

			for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
			{
				m_listDrawOptrBtn[i]->setGeometry(i * (50 + nWidth), nHeight - STT_Charact_ToolBtn_Width , 50, 50);
			}
		}
		else
		{
			nHeight = (nHeight - 7 * 50 - 60) / 6;

			for (int i = 0; i < m_listDrawOptrBtn.size(); i++)
			{
				m_listDrawOptrBtn[i]->setGeometry(nWidth - STT_Charact_ToolBtn_Width, 30 + i * (50 + nHeight), 50, 50);
			}
		}
	}

//	update();
}

void QImpCharactWidget::resizeEvent(QResizeEvent *pReSizeEvent)
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

CXDrawPoint* QImpCharactWidget::CreateNewDrawPoint(const double &dR,const double &dX)
{
	return m_pCharacterDrawView->CreateNewTestPoint(dR,dX);
}

void QImpCharactWidget::initPlot()
{
	CAxisInterface *pAxisInterface = NULL;
	m_pCharacterDrawView->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		CDataGroup oAxisConfig;
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(0, 0, 128));
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

void QImpCharactWidget::slot_ZKDel( int key)
{
	UpdateDrawCharacters();
}

void QImpCharactWidget::ClearSearchPoints()
{
	if (m_pCharacterDrawView)
	{
		m_pCharacterDrawView->ClearSearchPoints();
	}
}

QString QImpCharactWidget::exportPlot( QString name )
{
	QString strDir = QDir::currentPath()+"/testPic/";
	QString strPath = strDir+name;
	QDir *pDir = new QDir;
	bool exist = pDir->exists(strDir);
	if(exist)
	{

	}
	else
	{
		bool ok = pDir->mkdir(strDir);
		if( !ok )
		{
			//CXMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建失败！"));
			CXMessageBox::warning(this,g_sLangTxt_Gradient_CreateFolder.GetString(),g_sLangTxt_Gradient_FolderCreationFailed.GetString());    //创建文件夹  文件夹创建失败 lcq 3.14
		}
	}

	return strPath;
}

void QImpCharactWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	UpdateDrawCharacters();
	mousePressEvent(event);   

	emit sig_UpdatePointLocation(m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX,m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY);
}

void QImpCharactWidget::mouseMoveEvent(QMouseEvent *event)
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

void QImpCharactWidget::CalPointVertHorzLine(long nIndex, CString strType)
{
	m_pCharacterDrawView->CalVertHorzLine(nIndex, strType);
}

void QImpCharactWidget::UpdateVertLine(double dXValue)
{
	m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX = dXValue;
	CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_VERT);
	UpdateDrawCharacters();
}

void QImpCharactWidget::UpdateHorzLine(double dYValue)
{
	m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY = dYValue;
	CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_HORZ);
	UpdateDrawCharacters();
}

CXDrawLine* QImpCharactWidget::GetLeftButtonLine()
{
	return m_pCharacterDrawView->GetLeftButtonLine();
}

void QImpCharactWidget::mousePressEvent(QMouseEvent *event)
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

void QImpCharactWidget::slot_ActionTestAddClicked()
{
	emit sig_AddPointLocation(m_fx,m_fy);
}

void QImpCharactWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}

void QImpCharactWidget::wheelEvent(QWheelEvent *event)
{
	double dData = event->delta();

	if (dData>0)
	{
		m_pCharacterDrawView->UI_ZoomIn();
	} 
	else
	{
		m_pCharacterDrawView->UI_ZoomOut();
	}

	event->ignore();
}

void QImpCharactWidget::SetAxisName( const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle )
{
	m_strXAxis = strXAxisName;
	m_strYAxis = strYAxisName;
	m_strTitle = strAxisTitle;

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
}
void QImpCharactWidget::IsHaveAddAct()
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

void QImpCharactWidget::EnableSetting(BOOL bUseMouseMoveChar)
{
	m_bUseMouseMoveChar = bUseMouseMoveChar;
}

void QImpCharactWidget::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic)
{
	m_pCharacteristic = NULL;

	if (pCharacteristic != NULL)
	{
		if (pCharacteristic->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
		{
			m_pCharacteristic = (CCharacteristic*)pCharacteristic;
		}
	}

	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	if (m_pCharacteristic != NULL)
	{
		m_pCharacteristic->CalCharElement(NULL);
		m_pCharacterDrawView->XCreateElement(m_pCharacteristic, NULL, m_bViewTestLines, FALSE);
	} 
	else
	{
		m_pCharacteristics->CalCharElement(NULL);
		m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, m_bViewTestLines, FALSE);
	}

// 	int nWidth = width();
// 
// 	if (m_bUseOptrButtons)
// 	{
// 		nWidth = width()-STT_Charact_ToolBtn_Width;
// 	} 
// 
// 	CRect rcClient(0,0,nWidth,height());
// 	CDC oDC(this);
// 	m_pCharacterDrawView->SetBorder(rcClient, &oDC);

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);	//上面有代码会将坐标改为x-y 故在此调用修改坐标 20211013 sf

	initPlot();	//sf 20211027 重新设置坐标格式

	ResizeUI(width(),height());
	UpdateDrawCharacters();
}
















