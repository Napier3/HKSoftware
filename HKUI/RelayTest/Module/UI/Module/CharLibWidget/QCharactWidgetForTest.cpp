#include "QCharactWidgetForTest.h"
#include <QResizeEvent>

#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../SttTestCntrCmdDefine.h"

#include <QCoreApplication>
//#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>
#include "../../SttTestCntrFrameAPI.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../XLangResource_Native.h"

#include "QCharTestPointsGrid.h"
#include "../../SttTestCntrFrameBase.h"

QCharactWidgetForTest::QCharactWidgetForTest(QWidget *parent, BOOL bUseMouseMoveChar, BOOL bUseOptrButtons) :
    QWidget(parent)
{
	m_strXAxis = _T("R");
	m_strYAxis = _T("X");
	m_strTitle = _T("R-X(omg)");
	//m_strCurrShowCharaID = "";
    m_pCharacteristics = stt_Frame_Characteristics();
	m_pCharacteristics->CalCharElement(NULL);
    m_pCharacteristics->CalCharErrBandLen();
	m_pCharacterDrawView = new CInternationalCharDrawView();
	m_pCharacterDrawView->UI_SetActiveElement(NULL);
	//第三个和第四个参数，都传递为FALSE，表示不显示特性曲线默认的测试线
	m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);
	CRect rcClient(0,0,width(),height());
	CDC oDC(this);
	m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);

     m_bUseOptrButtons = bUseOptrButtons;
    if (m_bUseOptrButtons)
    {
        AddDrawOptrBtns();
    }
	initPlot();
	m_bUseMouseMoveChar = bUseMouseMoveChar;
	m_pCurrCharacteristic = NULL;
	m_bCharHasChanged = TRUE;
	connect(this, SIGNAL(sig_UpdateCurrTestPoint(QString,QString,double ,double)),
		this, SLOT(slot_UpdateCurrTestPoint(QString,QString,double ,double)),Qt::QueuedConnection);

	m_TestMenu = NULL;
	m_TestAddAction = NULL;
	m_ZoomInAction = NULL;
	m_ZoomOutAction = NULL;
	m_ResetAction = NULL;
	m_pCircleWidget =NULL;

	m_TestMenu = new QMenu(this);
	m_fx = 0;
	m_fy = 0;
	m_bCharHasSynChanged = FALSE;
    m_bAddTestLineFromChar= FALSE;
    m_bKeepAxisZoom = FALSE;

}

QCharactWidgetForTest::~QCharactWidgetForTest()
{
    qDeleteAll(m_listDrawOptrBtn);
    m_listDrawOptrBtn.clear();
}

BOOL QCharactWidgetForTest::IsViewTestLines()
{
	if (m_strCurrMacroID == STT_ORG_MACRO_DistanceTest)
	{
		return FALSE;
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_DistanceTest_I)
	{
		return FALSE;
	}
    else if (m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        return FALSE;
    }
else if (m_strCurrMacroID == STT_ORG_MACRO_SynTest_I)
    {
        return FALSE;
    }
	//20240816 zhangyq 曲线编辑不显示测试点
	if (m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I || m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest_I)
	{
		return FALSE;
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_DiffTest_I)//add wangtao 20240923 
	{
		return FALSE;
	}

	return TRUE;
}

void QCharactWidgetForTest::InitCharacteristic(const CString &strMacroID, BOOL bClearTestData)
{
	ClearSearchPoints();
	m_pCurrCharacteristic = NULL;
	CString strAxis;
	strAxis = GetAxisType(strMacroID);  //20240806 zhangyq 获取各个模块的坐标类型
	BOOL bLockXY = IsLockXY(strMacroID);
	BOOL bIsInternationalMode = IsInternationalMode(strMacroID);
	m_bCharHasChanged = TRUE;
	m_pCharacterDrawView->UpdateAxisType(strAxis, bLockXY);

    //20240822 wanmj 清空测试点/线
    if(bClearTestData && m_pCharacteristics != NULL)
    {
        m_pCharacteristics->ClearTestData();
    }
	UpdateCharDesc(strMacroID, _T(""));//20240924 luozibing 在坐标轴显示曲线前 更新坐标轴
	//20240806 zhangyq 如果为国际版，则统一处理有关坐标信息，其中，自动准同期需要加圆形图案

	if (bIsInternationalMode)
	{
        //m_bUseMouseMoveChar = TRUE;       //20240927 wanmj 移到UpdateCharDesc，否则国际版会全部设为可移动
		//1)该逻辑应该是针对所有测试功能的,不应该在此处增加; zhouhj 2024.9.21
		//2)改逻辑是在曲线编辑时，显示全部，曲线显示时显示选择的曲线；
		//3)此处逻辑影响内容较多，需要讨论确认方案后，才可修改
		//if (strMacroID == STT_ORG_MACRO_DistanceTest_I)
		//{
		//	m_pCharacterDrawView->m_bShowAllCharacts = FALSE;//20240919 luozibing 距离模块右侧特性曲线显示部分曲线
		//}
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		m_pCharacteristics->CalCharElement(NULL);//add wangtao 20241011
        m_pCharacteristics->CalCharErrBandLen();
		m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);
		InitTestMenu();
		initInternationalPlot();

		this->resize(this->size() - QSize(1, 1));
		this->resize(this->size() + QSize(1, 1));
	}
	else
	{
		initPlot();
	}

	UpdateCircleWidget_Syn(strMacroID);//更新同期右下角,角度圆
	SetUseOptrButtons(bIsInternationalMode);
	m_strCurrMacroID = strMacroID;
	UpdateDrawCharacters();
}

CString QCharactWidgetForTest::GetAxisType(const CString &strMacroID)
{
	CString strAxis;
	strAxis = _T("cartes");

	if ((strMacroID == STT_ORG_MACRO_CurrInverseTimeTest)
		|| (strMacroID == STT_ORG_MACRO_VolInverseTimeTest)
		|| (strMacroID == STT_ORG_MACRO_UFInverseTimeTest)
		|| (strMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I) 
		|| (strMacroID == STT_ORG_MACRO_VolInverseTimeTest_I))
	{
		strAxis = _T("logarithm");
	}

	return strAxis;
}

BOOL QCharactWidgetForTest::IsLockXY(const CString &strMacroID)
{
	BOOL bLockXY = TRUE;

	if ((strMacroID == STT_ORG_MACRO_DiffCurr6ITest) || (strMacroID == STT_ORG_MACRO_ElecRailwayDiffTest)
		|| (strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest) || (strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)
		|| (strMacroID == STT_ORG_MACRO_DiffTest_I))
	{
		bLockXY = FALSE;
	}

	return bLockXY;
}

BOOL QCharactWidgetForTest::IsInternationalMode(const CString &strMacroID)
{
	BOOL bIsInternationalMode = FALSE;
	//CXDrawMngr* pXDrawMngr = m_pCharacterDrawView->GetXDrawMngr_Axis();

	if ((strMacroID == STT_ORG_MACRO_DistanceTest_I) || (strMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I)
		|| (strMacroID == STT_ORG_MACRO_VolInverseTimeTest_I)
		|| (strMacroID == STT_ORG_MACRO_DistanceSearchTest_I) 
		|| (strMacroID == STT_ORG_MACRO_DiffTest_I)
		|| (strMacroID == STT_ORG_MACRO_SynTest_I))
	{
		bIsInternationalMode = TRUE;
	}

	return bIsInternationalMode;
}

void QCharactWidgetForTest::UpdateCircleWidget_Syn(const CString &strMacroID)
{
	//20240731 gongyp 自动准同期(国际版)
	if (strMacroID == STT_ORG_MACRO_SynTest_I)
	{
		if (m_pCircleWidget == NULL)
		{
			int nWidthLength = this->width() / 4;
			int nHeightLength = this->height() / 4;
			//设置圆形图案放置在特性图界面的右下角
			m_pCircleWidget = new QCharCircleWidget_Syn(this);
			m_pCircleWidget->SetAngle(-20, +20);//设置圆形图案的角度为-20°和20°
			m_pCircleWidget->SetArrowhead(0);//设置圆形图案的指向线段的角度
			m_pCircleWidget->setGeometry(this->width() - nWidthLength, this->height() - nHeightLength - 85, nWidthLength, nWidthLength);  // 放置在右下角  
			connect(this, SIGNAL(sizeChanged()), this, SLOT(updateButtonPosition()));
		}
	}
	else
	{
		if (m_pCircleWidget != NULL)
		{
			disconnect(this, SIGNAL(sizeChanged()), this, SLOT(updateButtonPosition()));
			delete m_pCircleWidget;
			m_pCircleWidget = NULL;
		}
	}
}

//根据界面的大小，圆形图案也随之改变
void QCharactWidgetForTest::updateButtonPosition(/*const QSize &newSize*/) 
{  
	int nWidthLength=this->width()/4;
	int nHeightLength=this->height()/4;

	//m_pCircleWidget->setGeometry(nWidthLength*3,nHeightLength*3-40,nWidthLength, nHeightLength);  // 放置在右下角 
	//根据按钮位置的进行设置进行显示
	if (this->height() > 600)
	{
		m_pCircleWidget->setGeometry(nWidthLength* 3 - 10, nHeightLength * 3 - 85, nWidthLength, nHeightLength );  // 放置在右下角 
	}
	else
	{
		m_pCircleWidget->setGeometry(nWidthLength* 3 - 45, nHeightLength * 3 - 40, nWidthLength, nHeightLength);  // 放置在右下角 
	}
}

void QCharactWidgetForTest::InitTestMenu()
{
	if(!m_TestMenu->isEmpty())//已经添加过，不再添加
	{
		return;
	}

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
void QCharactWidgetForTest::UpdateCharDesc(const CString &strMacroID, const CString &strCharID)
{
    BOOL bIsInternationalMode = IsInternationalMode(strMacroID);
    if(bIsInternationalMode)
        m_bUseMouseMoveChar = TRUE;

	if (strMacroID == STT_ORG_MACRO_CurrInverseTimeTest)
	{
		setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pCharacterDrawView->SetIsShowText(false);
	}
	else if (strMacroID == STT_ORG_MACRO_VolInverseTimeTest)
	{
		setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		SetAxisName(_T("U(V)"),_T("t(s)"),_T("U - t"));
		m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pCharacterDrawView->SetIsShowText(false);
	}
	else if (strMacroID == STT_ORG_MACRO_UFInverseTimeTest)
	{
		setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		SetAxisName(_T("U*/F*"),_T("t(s)"),_T("U*/F* - t"));
		m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pCharacterDrawView->SetIsShowText(false);
	}
	else if ((strMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
		||(strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_ElecRailwayDiffTest))
	{
		if ((strCharID != _T("PsuDiffHarmTest"))&&(strCharID != _T("ElecRailwayDiffHarmTest")))
		{
			setObjectName(QString::fromUtf8("QLineDiffCurr6ICharactWidget"));
			SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
			m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
			m_pCharacterDrawView->SetIsShowText(false);
			m_pCharacterDrawView->SetIsShowAng(false);
		} 
		else
		{
			setObjectName(QString::fromUtf8("QLineDiffCurr6ICharactWidget"));
			SetAxisName(_T("(%)"),_T("Id(A)"),_T(" "));
			m_pCharacterDrawView->SetXYUnitShow(_T("%"),_T("A"));
			m_pCharacterDrawView->SetIsShowText(false);
			m_pCharacterDrawView->SetIsShowAng(false);
		}
	}
	else if (strMacroID == STT_ORG_MACRO_DiffTest_I)
	{
		if ((strCharID != _T("PsuDiffHarmTest")))
		{
			m_pCharacterDrawView->m_bShowAllCharacts = FALSE;
			setObjectName(QString::fromUtf8("QLineDiffCurr6ICharactWidget"));
			SetAxisName(_T("Ir(A)"), _T("Id(A)"), CString("比例制动边界搜索"));
			m_pCharacterDrawView->SetXYUnitShow(_T("A"), _T("A"));
			m_pCharacterDrawView->SetIsShowText(false);
			m_pCharacterDrawView->SetIsShowAng(false);
		}
		else
		{
			m_pCharacterDrawView->m_bShowAllCharacts = FALSE;
			setObjectName(QString::fromUtf8("QLineDiffCurr6ICharactWidget"));
			SetAxisName(_T("(%)"), _T("Id(A)"), CString("比例制动边界搜索"));
			m_pCharacterDrawView->SetXYUnitShow(_T("%"), _T("A"));
			m_pCharacterDrawView->SetIsShowText(false);
			m_pCharacterDrawView->SetIsShowAng(false);
		}
		m_bUseMouseMoveChar = FALSE;
	}
    else if (strMacroID == STT_ORG_MACRO_DistanceTest_I)
	{
		m_pCharacterDrawView->m_bShowAllCharacts = FALSE;
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		setObjectName(QString::fromUtf8("QDistanceICharactWidget"));
		m_pCharacterDrawView->SetIsShowAng(true);
        m_pCharacterDrawView->SetAxisName(_T("R/Ω "),_T("X/Ω "),g_sLangTxt_Distance_ImpSetCheck/*("阻抗定值校验")*/);
        SetUseOptrButtons(TRUE);      
	}
    else if(strMacroID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        m_pCharacterDrawView->m_bShowAllCharacts = FALSE;
        m_pCharacterDrawView->UI_SetActiveElement(NULL);
        setObjectName(QString::fromUtf8("QDistanceSearchICharactWidget"));
        m_pCharacterDrawView->SetIsShowAng(true);
        m_pCharacterDrawView->SetAxisName(_T("R/Ω "),_T("X/Ω "),g_sLangTxt_Distance_ImpSetCheck/*("阻抗定值校验")*/);
        SetUseOptrButtons(TRUE);
        m_bUseMouseMoveChar = FALSE;
        m_bAddTestLineFromChar = TRUE;
        m_bKeepAxisZoom = TRUE;
	}
	else if (strMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I)
	{
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		setObjectName(QString::fromUtf8("QCurrInverseTimeICharactWidget"));
		SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pCharacterDrawView->SetIsShowText(false);
		m_bUseMouseMoveChar = false;
	}
	else if (strMacroID == STT_ORG_MACRO_VolInverseTimeTest_I)
	{
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		setObjectName(QString::fromUtf8("QVolInverseTimeICharactWidget"));
		SetAxisName(_T("U(V)"),_T("t(s)"),_T("U - t"));
		m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pCharacterDrawView->SetIsShowText(false);
		m_bUseMouseMoveChar = false;
	}
	else if (strMacroID == STT_ORG_MACRO_SynTest_I)
	{
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		setObjectName(QString::fromUtf8("QSynCharactWidget"));
		//SetAxisName(_T("△f(Hz)"),_T("△U(V)"),_T(" "));
		SetAxisName(_T("df/Hz"),_T("dV/V"),_T(" "));
		m_pCharacterDrawView->SetXYUnitShow(_T("Hz"),_T("V"));
		m_pCharacterDrawView->SetIsShowAng(true);
	}
	else
	{
		setObjectName(QString::fromUtf8("QImpCharactWidget"));
		SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
		m_pCharacterDrawView->SetIsShowAng(true);
	}
}

void QCharactWidgetForTest::paintEvent(QPaintEvent *event)
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

BOOL QCharactWidgetForTest::UpdateDrawCharacters()
{
	if (m_pCharacterDrawView == NULL)
	{
		return FALSE;
	}

	update();
	return TRUE;
}

void QCharactWidgetForTest::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = parentWidget()->rect();
    ResizeUI(rc.width(),rc.height());
	emit sizeChanged();
//	CDC oDC(this);
//	int nWidth = rc.width();
//	int nHeigh = rc.height();

//	if(rc.height() > 600)
//	{
//		CRect rcClient(0, 0, rc.width(), nHeigh/*rc.height() - STT_Charact_ToolBtn_Width*/);
//		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
//	}
//	else
//	{
//		CRect rcClient(0, 0, nWidth/*rc.width() - STT_Charact_ToolBtn_Width*/, rc.height());
//		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
//	}

}

void QCharactWidgetForTest::UpdateAxisType(const CString& strAxis, BOOL bLockXY)
{
	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	m_pCharacterDrawView->UpdateAxisType(strAxis, bLockXY);
}

void QCharactWidgetForTest::initPlot()
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

	ClearSearchPoints();
}
void QCharactWidgetForTest::initInternationalPlot()
{
	CAxisInterface *pAxisInterface = NULL;
	m_pCharacterDrawView->GetAxisInterface(&pAxisInterface);

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
	ClearSearchPoints();
}
void QCharactWidgetForTest::mouseDoubleClickEvent(QMouseEvent *event)
{
	UpdateDrawCharacters();
	mousePressEvent(event);   

//	emit sig_UpdatePointLocation(m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX,m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY);
}

void QCharactWidgetForTest::mouseMoveEvent(QMouseEvent *event)
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
            else if(m_bAddTestLineFromChar) //20240918 wanmj 鼠标拖拽在特性图画线
            {
                m_pCharacterDrawView->SetTestLineEnd(oPoint);
                UpdateDrawCharacters();
            }
		}
	}

	event->ignore();
}

void QCharactWidgetForTest::mousePressEvent(QMouseEvent *event)
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
            else if(m_bAddTestLineFromChar) //20240918 wanmj 鼠标拖拽在特性图画线
            {
                m_pCharacterDrawView->SetTestLineBegin(oPoint);
            }
//			emit sig_LeftButtonDown();
			UpdateDrawCharacters();
		}
		if (event->button() == Qt::RightButton)
		{
			m_fx = m_pCharacterDrawView->m_oAxisInstruct_Point.m_fX;	//记录右键点击的坐标
			m_fy = m_pCharacterDrawView->m_oAxisInstruct_Point.m_fY;

			m_TestMenu->exec(QCursor::pos());

		}	
	}

	QWidget::mousePressEvent(event);
}

void QCharactWidgetForTest::mouseReleaseEvent(QMouseEvent *event)
{
    //20240918 wanmj 鼠标拖拽在特性图画测试线
    CPoint oPoint(event->pos().x(),event->pos().y());
    CRect rc = m_pCharacterDrawView->GetBorder();
    if(event->pos().x() <= rc.Width())
    {
        m_pCharacterDrawView->SetAxisInstruct_Point(oPoint);

        if (event->button() == Qt::LeftButton && m_bAddTestLineFromChar)
        {
            m_pCharacterDrawView->SetTestLineEnd(oPoint);
            UpdateDrawCharacters();
        }

    }

	QWidget::mouseReleaseEvent(event);
}

void QCharactWidgetForTest::wheelEvent(QWheelEvent *event)
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

void QCharactWidgetForTest::SetAxisName( const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle )
{
	m_strXAxis = strXAxisName;
	m_strYAxis = strYAxisName;
	m_strTitle = strAxisTitle;

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
}

void QCharactWidgetForTest::UpdateCurrTestPoint(const CString &strCharaID,const CString &strIndex,
												double dX,double dY)
{
	emit sig_UpdateCurrTestPoint(strCharaID,strIndex,dX,dY);
}

void QCharactWidgetForTest::slot_UpdateDrawCharacters()
{
	if (NULL == m_pCharacterDrawView)
	{
		return;
	}

//	if (!m_strCurrShowCharaID.IsEmpty())//add wangtao 20240929 如果不为空说明该模块存在多条特性曲线
//	{
//		return;
//	}

    //20241011 wanmj 记录界面缩放大小
    double dAxisXmin, dAxisYmin, dAxisXmax, dAxisYmax;
    m_pCharacterDrawView->GetAxisMinMax(dAxisXmin, dAxisYmin, dAxisXmax, dAxisYmax);

	m_pCharacteristics->CalCharElement(NULL);
    m_pCharacteristics->SetIsShowErrorBand(TRUE);
    m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);	//20241017 wanmj 先创建m_listCharElement链表里的元素才可以获取和曲线的交点，计算相对误差
    m_pCharacteristics->CalCharErrBandLen();
	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, IsViewTestLines(), FALSE);
	int nWidth = width();

	CRect rcClient(0,0,nWidth,height());
	CDC oDC(this);
	m_pCharacterDrawView->SetBorder(rcClient, &oDC);

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);	//上面有代码会将坐标改为x-y 故在此调用修改坐标 20211013 sf

    if (m_strCurrMacroID == STT_ORG_MACRO_DistanceTest_I
            || m_strCurrMacroID == STT_ORG_MACRO_SynTest_I
            || m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest_I
            || m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I 
            || m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest_I
			|| m_strCurrMacroID == STT_ORG_MACRO_DiffTest_I)
	{
		initInternationalPlot();
	}
	else
	{
	initPlot();	//sf 20211027 重新设置坐标格式
	}

	ResizeUI(width(), height());
	UpdateDrawCharacters();

    //20241011 wanmj 保持特性曲线图界面原有缩放
    if(m_bKeepAxisZoom)
    {
        m_pCharacterDrawView->SetAxisMinMax(dAxisXmin, dAxisYmin, dAxisXmax, dAxisYmax);
    }

}

void QCharactWidgetForTest::UpdateCharacteristic(const CString &strCharID, int nTestObjDrawMode)
{
	//m_strCurrShowCharaID = strCharID;
	CCharacteristic *pCurrCharacteristic = NULL;

	if (strCharID.IsEmpty())
	{
		pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}
	else
	{
		POS pos = m_pCharacteristics->GetHeadPosition();
		BOOL bCharaExisted = FALSE;
		while (pos != NULL)
		{
			CExBaseList* pCharTemp = (CExBaseList*)m_pCharacteristics->GetNext(pos);
			if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
				continue;

			CCharacteristic *pChar = (CCharacteristic*)pCharTemp;
			if (pChar->m_strID != strCharID)//add wangtao 20240927 查找指定特性曲线并显示
			{
				pChar->m_nUse = 0;
			}
			else
			{
				pChar->m_nUse = 1;
				pCurrCharacteristic = pChar;
			}
		}
	}

	if (pCurrCharacteristic == NULL)
	{
		//2024-9-14 wuxinyi 修改%s但传入int型导致中断
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新曲线图")*/g_sLangTxt_Gradient_UnUpdateGraph.GetString(),
// 			strCharaIDNew.GetString(), -1); //lcq
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新曲线图")*/g_sLangTxt_Gradient_UnUpdateGraph.GetString(),
			strCharID.GetString(), _T("-1")); //lcq
		return;
	}

	if ((m_pCurrCharacteristic != pCurrCharacteristic) || m_bCharHasChanged || m_pCharacteristics->m_nTestObjDrawMode != nTestObjDrawMode)
	{
		m_pCharacterDrawView->ClearSearchPoints();
		m_bCharHasChanged = FALSE;
		m_pCharacteristics->m_nTestObjDrawMode = nTestObjDrawMode;
		m_pCurrCharacteristic = pCurrCharacteristic;
		UpdateCharDesc(m_strCurrMacroID, strCharID);

		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		m_pCurrCharacteristic->CalCharElement(NULL);//add wangtao 20240920 
		m_pCharacterDrawView->XCreateElement(pCurrCharacteristic, NULL, IsViewTestLines(), FALSE);
		int nWidth = width();

		CRect rcClient(0, 0, nWidth, height());
		CDC oDC(this);
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}
	ResizeUI(width(), height());
	update();
}

void QCharactWidgetForTest::slot_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY)
{
	CString strCharaIDNew,strIndexNew;
	strCharaIDNew = strCharaID;
	strIndexNew = strIndex;
	CCharacteristic *pCurrCharacteristic = NULL;

	if (strCharaIDNew.IsEmpty() && strIndexNew.IsEmpty())
	{
		pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}
	else
	{
		pCurrCharacteristic = m_pCharacteristics->FindCharByID_Index(strCharaIDNew,strIndexNew);
	}

	if (pCurrCharacteristic == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新曲线图")*/g_sLangTxt_Gradient_UnUpdateGraph.GetString(),
			strCharaIDNew.GetString(),strIndexNew.GetString()); //lcq
		return;
	}

	if ((m_pCurrCharacteristic != pCurrCharacteristic) || m_bCharHasChanged)
	{
		m_pCharacterDrawView->ClearSearchPoints();
		m_bCharHasChanged = FALSE;
		m_pCurrCharacteristic = pCurrCharacteristic;
		UpdateCharDesc(m_strCurrMacroID,strCharaID);

		m_pCharacterDrawView->UI_SetActiveElement(NULL);
		m_pCharacterDrawView->XCreateElement(pCurrCharacteristic, NULL, IsViewTestLines(), FALSE);
		int nWidth = width();

		CRect rcClient(0,0,nWidth,height());
		CDC oDC(this);
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}

	m_pCharacterDrawView->UpdateCurrTestPoint(dX, dY);
	update();
}

void QCharactWidgetForTest::AddTestResultPoint(CExBaseList* pValue)
{
	CDvmValues* pValues = (CDvmValues*)pValue;
	CDvmValue* pX = NULL;
	CDvmValue* pY = NULL;
	CDvmValue* pX_set = NULL;
	CDvmValue* pY_set = NULL;
	BOOL bHasAct = FALSE;
	double dX_set = 0.0f,dY_set = 0.0f;
	CString strCharID;

	if (m_pCurrCharacteristic != NULL)
	{
		strCharID = m_pCurrCharacteristic->m_strID;
	}

	if ((m_strCurrMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
		||(m_strCurrMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_ElecRailwayDiffTest))
	{
		if ((strCharID != _T("PsuDiffHarmTest"))&&(strCharID != _T("ElecRailwayDiffHarmTest")))
		{
			pX = (CDvmValue*)pValues->FindByID("TripIr");
			pY = (CDvmValue*)pValues->FindByID("TripId");
			pX_set = pX;
			pY_set = (CDvmValue*)pValues->FindByID("IdSetting");

			if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
			{
				bHasAct = TRUE;
			}
			else
			{
				pY = pY_set;
			}
		} 
		else
		{
			pX = (CDvmValue*)pValues->FindByID("TripRHarm");
			pY = (CDvmValue*)pValues->FindByID("Id");
			pX_set = (CDvmValue*)pValues->FindByID("RateHarmSet");
			pY_set = pY;

			if ((pX != NULL)&&(pX->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
			{
				bHasAct = TRUE;
			}
			else
			{
				pX = pX_set;
			}
		}
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest||(m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		pX = (CDvmValue*)pValues->FindByID("FaultCurrent");
		pY = (CDvmValue*)pValues->FindByID("TripTime");
		pX_set = pX;
		pY_set = (CDvmValue*)pValues->FindByID("SettingTime");

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = pY_set;
		}
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_UFInverseTimeTest)
	{
		pX = (CDvmValue*)pValues->FindByID("VolFreqRate");
		pY = (CDvmValue*)pValues->FindByID("TripTime");
		pX_set = pX;
		pY_set = (CDvmValue*)pValues->FindByID("SettingTime");

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = pY_set;
		}
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest||(m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest_I))
	{
		pX = (CDvmValue*)pValues->FindByID("FaultVolt");
		pY = (CDvmValue*)pValues->FindByID("TripTime");
		pX_set = pX;
		pY_set = (CDvmValue*)pValues->FindByID("MaxFaultTime");

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = pY_set;
		}

	}
	else if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)
		||(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
	{
		pX = (CDvmValue*)pValues->FindByID("TripZ");
		pY = (CDvmValue*)pValues->FindByID("TripZAngle");
		pX_set = (CDvmValue*)pValues->FindByID("ValSetting");;
		pY_set = (CDvmValue*)pValues->FindByID("ValSettingAngle");

		if ((pX != NULL)&&(pX->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pX = pX_set;
			pY = pY_set;
		}
	}
	else
	{
	}

	if (pX_set && pY_set)
	{
		dX_set = CString_To_double(pX_set->m_strValue);
		dY_set = CString_To_double(pY_set->m_strValue);
	}

	if(pX && pY)
	{
		double dX = CString_To_double(pX->m_strValue);
		double dY = CString_To_double(pY->m_strValue);

		if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)||
			(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
		{
			double dX_New = dX*cos(dY*3.1415926/180.0);
			double dY_New = dX*sin(dY*3.1415926/180.0);
			dX = dX_New;
			dY = dY_New;

			dX_New = dX_set*cos(dY_set*3.1415926/180.0);
			dY_New = dX_set*sin(dY_set*3.1415926/180.0);
			dX_set = dX_New;
			dY_set = dY_New;
		}
		else if ((strCharID == _T("PsuDiffHarmTest"))||(strCharID == _T("ElecRailwayDiffHarmTest")))
		{
			dX *= 100;
			dX_set *= 100;
		}

// 		if (fabs(dY)<0.0001)
// 		{
// 			dY = 122;
// 		}
		m_pCharacterDrawView->AddTestResultPoint(dX, dY,bHasAct);

        QCharTestPointsGrid *pCharTestPointsGrid = (QCharTestPointsGrid*)stt_Frame_CharTestPointsGrid();

		if (pCharTestPointsGrid)
		{
			pCharTestPointsGrid->AddTestResultPoint(dX, dY,bHasAct,dX_set,dY_set);
		}
        stt_Frame_AddTestPoints(dX, dY,bHasAct);
	}
}

void QCharactWidgetForTest::ClearSearchPoints()
{
	if (m_pCharacterDrawView)
	{
		m_pCharacterDrawView->ClearSearchPoints();
	}

	m_pCurrCharacteristic = NULL;
}

void QCharactWidgetForTest::ClearSearchPoint(long nPtIndex)
{
	if(m_pCharacterDrawView)
	{
		m_pCharacterDrawView->ClearSearchPoints(nPtIndex);
	}
}

void QCharactWidgetForTest::ClearSearchPointsFrom(long nPtIndex)
{
	long nCount = m_pCharacterDrawView->GetSearchPointsCount();
	for (int i = nCount - 1; i >= nPtIndex; i--)
	{
		ClearSearchPoint(i);
	}
}

void QCharactWidgetForTest::slotDrawOptr_ZoomIn()
{
	m_pCharacterDrawView->ZoomIn();
	UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_ZoomOut()
{
	m_pCharacterDrawView->ZoomOut();
	UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_Reset()
{
	m_pCharacterDrawView->ZoomReset();
	UpdateDrawCharacters();
	slotDrawOptr_SynReset();
	
}

void QCharactWidgetForTest::slot_ActionTestAddClicked()
{
    if(m_bAddTestLineFromChar)
    {
        double dBegX, dBegY, dEndX, dEndY;
        BOOL bAdd = m_pCharacterDrawView->GetTestLineBegEndPos(dBegX, dBegY, dEndX, dEndY);
        if(bAdd)
        {
            BOOL bSucc = g_theTestCntrFrame->AddItem_From_Charact(dBegX, dBegY, dEndX, dEndY);
            if(bSucc)
                m_pCharacterDrawView->ClearTestLine();  //测试项添加成功，测试线清空，否则会影响当前测试线颜色显示
        }
    }
    else
    {
	g_theTestCntrFrame->AddItem_From_Charact(m_fx,m_fy);
    }

}
void QCharactWidgetForTest::DeleteTestData(const CString &strIDPath)
{
	((CInternationalCharDrawView *)m_pCharacterDrawView)->DeleteTestData(strIDPath);
	/*if (m_strCurrShowCharaID.IsEmpty())
	{*/
		slot_UpdateDrawCharacters();    //20240822 wanmj
		update();
	//}
	//else//add wangtao 20240923 如果当前模块存在多个曲线，则刷新记录中的曲线
	//{
	//	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	//	if (m_pCurrCharacteristic == NULL)
	//	{
	//		return;
	//	}

	//	m_pCurrCharacteristic->CalCharElement(NULL);
	//	m_pCharacterDrawView->XCreateElement(m_pCurrCharacteristic, NULL, IsViewTestLines(), FALSE);
	//	ResizeUI(width(), height());
	//	update();
	//}
}

void QCharactWidgetForTest::AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState)
{
	((CInternationalCharDrawView *)m_pCharacterDrawView)->AddUpdateTestPoint_Imp(strIDPath, dX, dY, nFaultType, nZoneType, nState);
	slot_UpdateDrawCharacters();
	update();
}

void QCharactWidgetForTest::UpdateTestCharParas_Syn(double dX, double dY)
{
	((CInternationalCharDrawView *)m_pCharacterDrawView)->UpdateTestUI_Syn(m_pCharacteristics,dX, dY);
	slot_UpdateDrawCharacters();
	update();

	m_bCharHasSynChanged = m_pCharacterDrawView->SetAxisAdjust(dX);//?????????未定义
	UpdateDrawCharacters();
}

void QCharactWidgetForTest::AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState)
{
    ((CInternationalCharDrawView *)m_pCharacterDrawView)->AddUpdateTestLine_Imp(strIDPath, dBegX, dBegY, dEndX, dEndY, nFaultType, nZoneType, nState);
    slot_UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_SynReset()
{
	if (m_bCharHasSynChanged)
	{
		slotDrawOptr_ZoomOut();
	}
}
void QCharactWidgetForTest::AddDrawOptrBtns()
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

QPushButton* QCharactWidgetForTest::AddDrawOptrBtn(const CString &strImg, long nIndex)
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
void QCharactWidgetForTest::UpdateDrawOptrBtns()
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
void QCharactWidgetForTest::ResizeUI(int nWidth,int nHeight)
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

void QCharactWidgetForTest::SetUseOptrButtons(BOOL bUseOptrButtons)
{
    if(m_bUseOptrButtons == bUseOptrButtons)
    {
        return;
    }
    m_bUseOptrButtons = bUseOptrButtons;

    if(m_listDrawOptrBtn.count() == 0&&m_bUseOptrButtons)
    {
        AddDrawOptrBtns();
    }
}
void QCharactWidgetForTest::slotDrawOptr_MoveUp()
{
    m_pCharacterDrawView->MoveUp();
    UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_MoveDown()
{
    m_pCharacterDrawView->MoveDown();
    UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_MoveLeft()
{
    m_pCharacterDrawView->MoveLeft();
    UpdateDrawCharacters();
}

void QCharactWidgetForTest::slotDrawOptr_MoveRight()
{
    m_pCharacterDrawView->MoveRight();
    UpdateDrawCharacters();
}

void QCharactWidgetForTest::AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState)
{
	((CInternationalCharDrawView *)m_pCharacterDrawView)->AddUpdateTestLine(strIDPath, dBegX, dBegY, dEndX, dEndY, nFaultType, nState);
	slot_UpdateDrawCharacters();
	//m_pCharacterDrawView->UI_SetActiveElement(NULL);
	////if (m_pCurrCharacteristic == NULL)
	////{
	////	m_pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	////}
	//m_pCurrCharacteristic->CalCharElement(NULL);
	//m_pCharacterDrawView->XCreateElement(m_pCurrCharacteristic, NULL, IsViewTestLines(), FALSE);
	//ResizeUI(width(), height());
	//update();
}
void QCharactWidgetForTest::AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState)
{
	((CInternationalCharDrawView *)m_pCharacterDrawView)->AddUpdateTestPoint(strIDPath, dX, dY, nFaultType, nState);
	slot_UpdateDrawCharacters();
	//m_pCharacterDrawView->UI_SetActiveElement(NULL);
	//m_pCurrCharacteristic->CalCharElement(NULL);
	//if (m_pCurrCharacteristic == NULL)
	//{
	//	m_pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	//}
	//m_pCharacterDrawView->XCreateElement(m_pCurrCharacteristic, NULL, IsViewTestLines(), FALSE);
	//ResizeUI(width(), height());
	//update();
}
void QCharactWidgetForTest::UpdateCharacterisByFaultType(int nFaultType)
{////20241012 luozibing 未添加测试点时更新界面显示曲线故障类型 曲线故障类型改变刷新界面

	CString strFaultOld = Global_GetCharFaultTypeStringByFaultType(m_pCharacterDrawView->m_nFaultType);
	CString strFaultNew = Global_GetCharFaultTypeStringByFaultType(nFaultType);
	m_pCharacterDrawView->m_nFaultType = nFaultType;
	if (strFaultOld != strFaultNew)
	{
		slot_UpdateDrawCharacters();
	}
}