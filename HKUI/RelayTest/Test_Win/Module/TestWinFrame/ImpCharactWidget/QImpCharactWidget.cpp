#include "QImpCharactWidget.h"
#include <QResizeEvent>
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../../../../Module/API/GlobalConfigApi.h"

#include <QCoreApplication>
//#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>

QImpCharactWidget::QImpCharactWidget(QWidget *parent, bool bUseOptrButtons, BOOL bUseMouseMoveChar) :
    QWidget(parent)
{
	m_bStart = false;
//	m_bUpdatePaint = TRUE;

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
		m_ZoomInAction = new QAction(/*tr("放大")*/g_sLangTxt_State_Magnify,this);
		m_ZoomInAction->setIcon (QPixmap( "./images/ZoomIn.png"));
		m_TestMenu->addAction(m_ZoomInAction);
		connect(m_ZoomInAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomIn()));

		m_ZoomOutAction = new QAction(/*tr("缩小")*/g_sLangTxt_State_Shrink,this);
		m_ZoomOutAction->setIcon (QPixmap( "./images/ZoomOut.png"));
		m_TestMenu->addAction(m_ZoomOutAction);
		connect(m_ZoomOutAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_ZoomOut()));

		m_ResetAction = new QAction(/*tr("复位")*/g_sLangTxt_State_Reposition,this);
		m_ResetAction->setIcon (QPixmap( "./images/ZoomReset.png"));
		m_TestMenu->addAction(m_ResetAction);
		connect(m_ResetAction, SIGNAL(triggered()), this, SLOT(slotDrawOptr_Reset()));
	}

	m_pCharacteristics = g_theSttXTestMngrBaseApp->m_pCharacteristics;

	m_strXAxis = _T("R");
	m_strYAxis = _T("X");
	m_strTitle = _T("R-X(Ω)");

 //   if (pFind != NULL)
    {
        m_pCharacteristics->CalCharElement(NULL);
        m_pCharacterDrawView = new CPsuCharDrawView();
        m_pCharacterDrawView->UI_SetActiveElement(NULL);

		//第三个和第四个参数，都传递为FALSE，表示不显示特性曲线默认的测试线
        m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);

        CRect rcClient(0,0,width(),height());
        m_pDC = new CDC(this);
        m_pCharacterDrawView->SetBorder(rcClient, m_pDC);
    }

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
//	m_pCharacterDrawView->SetTestPointLine(10,10);
	initPlot();

	if (bUseOptrButtons)
	{
		AddDrawOptrBtns();
	}
	
	m_bUseMouseMoveChar = bUseMouseMoveChar;
}

void QImpCharactWidget::AddDrawOptrBtns()
{
	long nIndex = 0;
	QPushButton *pBtn = AddDrawOptrBtn("ZoomIn", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomIn()));

	pBtn = AddDrawOptrBtn("ZoomOut", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_ZoomOut()));

// 	pBtn = AddDrawOptrBtn("ZoomMouse", nIndex++);
// 	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MouseZoom()));

	pBtn = AddDrawOptrBtn("ZoomReset", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_Reset()));

	pBtn = AddDrawOptrBtn("MoveUp", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveUp()));

	pBtn = AddDrawOptrBtn("MoveDown", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveDown()));

	pBtn = AddDrawOptrBtn("MoveLeft", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveLeft()));

	pBtn = AddDrawOptrBtn("MoveRight", nIndex++);
	connect(pBtn,SIGNAL(clicked()),this,SLOT(slotDrawOptr_MoveRight()));
}

QPushButton* QImpCharactWidget::AddDrawOptrBtn(const CString &strID, long nIndex)
{
	QPushButton *pBtn = new QPushButton(this);
	CString strIcon, strPath;
	strPath = _P_GetBinPath();
	strIcon.Format("images/%s.png", strID.GetString());
	strIcon = strPath + strIcon;
	QIcon icon(strIcon);
	pBtn->setIcon(icon);
	pBtn->setIconSize(QSize(60, 60));
// 	pBtn->setFlat(true);
// 	pBtn->setGeometry(4+nIndex * 17,4,45,45);
	m_listDrawOptrBtn.append(pBtn);

	return pBtn;
}

QImpCharactWidget::~QImpCharactWidget()
{
	qDeleteAll(m_listDrawOptrBtn);
	m_listDrawOptrBtn.clear();

 //   delete m_pDC;
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

//	if (!m_bUpdatePaint)
// 	{
// 		return;
// 	}

	CDC oDC(this);
	oDC.begin(this);
	m_pCharacterDrawView->Draw(&oDC, 1, CPoint(0, 0));
	oDC.end();
}

BOOL QImpCharactWidget::UpdateDrawCharacters()
{
	if (m_pCharacterDrawView == NULL)
	{
		return FALSE;
	}

// 	//if (m_pCharacterDrawView->HasDefChar())
// 	{
// 		CDC oDC(this);
// 		oDC.begin(this);
// 		m_pCharacterDrawView->Draw(&oDC, 1, CPoint(0, 0));
// 		oDC.end();
// 		updateGeometry();
// 		return TRUE;
// 	}

	update();
	return FALSE;
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

void QImpCharactWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = parentWidget()->rect();
	CDC *pDC = new CDC(this);
	int nWidth = rc.width();
	int nHeigh = rc.height();

	if (m_bUseOptrButtons)
	{
		nWidth -= STT_Charact_ToolBtn_Width;
		nHeigh -= STT_Charact_ToolBtn_Width;
	}

	if(rc.height() > 600)
	{
		CRect rcClient(0, 0, rc.width(), nHeigh/*rc.height() - STT_Charact_ToolBtn_Width*/);
		m_pCharacterDrawView->SetBorder(rcClient, pDC);
	}
	else
	{
		CRect rcClient(0, 0, nWidth/*rc.width() - STT_Charact_ToolBtn_Width*/, rc.height());
		m_pCharacterDrawView->SetBorder(rcClient, pDC);
	}

	if (m_bUseOptrButtons)
	{
		UpdateDrawOptrBtns();
	}
}

void QImpCharactWidget::updateButtonPos()
{
	QRect rc = parentWidget()->rect();
	CDC *pDC = new CDC(this);
	int nWidth = rc.width();
	int nHeigh = rc.height();

	if (m_bUseOptrButtons)
	{
		nWidth -= STT_Charact_ToolBtn_Width;
		nHeigh -= STT_Charact_ToolBtn_Width;
	}

	if(rc.height() > 600)
	{
		CRect rcClient(0, 0, rc.width(), nHeigh/*rc.height() - STT_Charact_ToolBtn_Width*/);
		m_pCharacterDrawView->SetBorder(rcClient, pDC);
	}
	else
	{
		CRect rcClient(0, 0, nWidth/*rc.width() - STT_Charact_ToolBtn_Width*/, rc.height());
		m_pCharacterDrawView->SetBorder(rcClient, pDC);
	}
	
	if (m_bUseOptrButtons)
	{
		UpdateDrawOptrBtns();
	}

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

void QImpCharactWidget::clearResultAll()
{
	UpdateDrawCharacters();
//	replot();
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
			QMessageBox::warning(this,/*tr("创建文件夹")*/g_sLangTxt_Gradient_CreateFolder,/*tr("文件夹创建失败！")*/g_sLangTxt_Gradient_FolderCreationFailed);
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
	m_pCharacterDrawView->UI_OnMouseMove(0,oPoint);

	if (event->buttons() & Qt::LeftButton)
	{
		if (m_bUseMouseMoveChar)
		{
			m_pCharacterDrawView->MouseMove_MoveTo(oPoint);
		}
	}

	event->ignore();
}

void QImpCharactWidget::mousePressEvent(QMouseEvent *event)
{
	CPoint oPoint(event->pos().x(),event->pos().y());
	m_pCharacterDrawView->SetAxisInstruct_Point(oPoint);

	if (event->button() == Qt::LeftButton)
	{
		if (m_bUseMouseMoveChar)
		{
			m_pCharacterDrawView->MouseMove_SetBegin(oPoint);
		}
		
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

	m_TestAddAction = new QAction(/*tr("添加试验")*/g_sLangTxt_Gradient_AddExperiment,this);
	m_TestAddAction->setIcon (QPixmap( "./images/Add.png"));
	if (m_TestMenu == NULL)
	{
		return;
	}
	m_TestMenu->insertAction(0,m_TestAddAction);
	connect(m_TestAddAction, SIGNAL(triggered()), this, SLOT(slot_ActionTestAddClicked()));
}

void QImpCharactWidget::slot_UpdateDrawCharacters()
{
	if (NULL == m_pCharacterDrawView)
	{
		return;
	}

	m_pCharacteristics->CalCharElement(NULL);
	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);
// 	CRect rcClient(0,0,width(),height());
// 	m_pCharacterDrawView->SetBorder(rcClient, m_pDC);

	//2023-12-11 suyang 添加、删除阻抗特性时 特性图范围会往下移动一点，被放大缩小按钮遮挡,重新调整范围  
	updateButtonPos();

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);	//上面有代码会将坐标改为x-y 故在此调用修改坐标 20211013 sf

	initPlot();	//sf 20211027 重新设置坐标格式

	UpdateDrawCharacters();
}

void QImpCharactWidget::GetSearchingPng(CString& strBase64)
{
	CRect rc = m_pCharacterDrawView->GetBorder();
	int nCurrWidth = rc.Width();
	int nCurrHeight = rc.Height();

	CDC *pDC = new CDC(this);
	int nWidth = 600;
	int nHeigh = 600;
	if (m_bUseOptrButtons)
	{
		nWidth += STT_Charact_ToolBtn_Width;
		nHeigh += STT_Charact_ToolBtn_Width;
	}
	CRect rcClient(0, 0, nWidth, nHeigh);
	m_pCharacterDrawView->SetBorder(rcClient, pDC);

	QByteArray ba;
	QBuffer* buffer = new QBuffer(&ba);
	buffer->open(QIODevice::WriteOnly);
	QPixmap pixmap (nWidth, nHeigh);  
	this->render(&pixmap);
	QImage image = pixmap.toImage();
	image.save(buffer, "png", -1);
	QString strPngBase64 = ba.toBase64();
	strBase64 = strPngBase64;

	CRect rect(0, 0, nCurrWidth, nCurrHeight);
	m_pCharacterDrawView->SetBorder(rect, pDC);
	delete buffer;
}















