#include "QCharactWidgetForTest.h"
#include <QResizeEvent>

#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../SttTestCntrCmdDefine.h"

#include <QCoreApplication>
//#include <qwt_symbol.h>
#include <QDir>
#include <QMessageBox>
#include "../../SttTestCntrFrameBase.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../XLangResource_Native.h"

QCharactWidgetForTest::QCharactWidgetForTest(QWidget *parent,  BOOL bUseMouseMoveChar) :
    QWidget(parent)
{
	m_strXAxis = _T("R");
	m_strYAxis = _T("X");
	m_strTitle = _T("R-X(omg)");
	m_pCharacteristics = g_theTestCntrFrame->m_pCharacteristics;
	m_pCharacteristics->CalCharElement(NULL);
	m_pCharacterDrawView = new CPsuCharDrawView();
	m_pCharacterDrawView->UI_SetActiveElement(NULL);
	//第三个和第四个参数，都传递为FALSE，表示不显示特性曲线默认的测试线
	m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, FALSE, FALSE);
	CRect rcClient(0,0,width(),height());
	CDC oDC(this);
	m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);
	initPlot();
	m_bUseMouseMoveChar = bUseMouseMoveChar;
	m_pCurrCharacteristic = NULL;
	m_bCharHasChanged = TRUE;
	connect(this, SIGNAL(sig_UpdateCurrTestPoint(QString,QString,double ,double)),
		this, SLOT(slot_UpdateCurrTestPoint(QString,QString,double ,double)),Qt::QueuedConnection);
}

QCharactWidgetForTest::~QCharactWidgetForTest()
{
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

	return TRUE;
}

void QCharactWidgetForTest::InitCharacteristic(const CString &strMacroID)
{
	ClearSearchPoints();
	m_pCurrCharacteristic = NULL;
	CXDrawMngr* pXDrawMngr = m_pCharacterDrawView->GetXDrawMngr_Axis();
	CString strAxis;
	strAxis = _T("cartes");
	m_bCharHasChanged = TRUE;
	BOOL bLockXY = TRUE;

	if ((strMacroID == STT_ORG_MACRO_CurrInverseTimeTest)
		||(strMacroID == STT_ORG_MACRO_VolInverseTimeTest)
		||(strMacroID == STT_ORG_MACRO_UFInverseTimeTest))
	{
		strAxis = _T("logarithm");
	}
	else if ((strMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_ElecRailwayDiffTest)
		||(strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)||(strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest))
	{
		bLockXY = FALSE;
	}

	if (pXDrawMngr->m_strAxis != strAxis)
	{
		m_pCharacterDrawView->UpdateAxisType(strAxis,bLockXY);
		initPlot();
	}


	UpdateCharDesc(strMacroID,_T(""));
	m_strCurrMacroID = strMacroID;
	UpdateDrawCharacters();
}

void QCharactWidgetForTest::UpdateCharDesc(const CString &strMacroID, const CString &strCharID)
{
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

	CDC oDC(this);
	int nWidth = rc.width();
	int nHeigh = rc.height();

	if(rc.height() > 600)
	{
		CRect rcClient(0, 0, rc.width(), nHeigh/*rc.height() - STT_Charact_ToolBtn_Width*/);
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}
	else
	{
		CRect rcClient(0, 0, nWidth/*rc.width() - STT_Charact_ToolBtn_Width*/, rc.height());
		m_pCharacterDrawView->SetBorder(rcClient, &oDC);
	}
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

//			emit sig_LeftButtonDown();
			UpdateDrawCharacters();
		}	
	}

	QWidget::mousePressEvent(event);
}

void QCharactWidgetForTest::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}

void QCharactWidgetForTest::wheelEvent(QWheelEvent *event)
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

	m_pCharacteristics->CalCharElement(NULL);
	m_pCharacterDrawView->UI_SetActiveElement(NULL);

	m_pCharacterDrawView->XCreateElement(m_pCharacteristics, NULL, IsViewTestLines(), FALSE);
	int nWidth = width();

	CRect rcClient(0,0,nWidth,height());
	CDC oDC(this);
	m_pCharacterDrawView->SetBorder(rcClient, &oDC);

	m_pCharacterDrawView->SetAxisName(m_strXAxis,m_strYAxis,m_strTitle);	//上面有代码会将坐标改为x-y 故在此调用修改坐标 20211013 sf

	initPlot();	//sf 20211027 重新设置坐标格式

	UpdateDrawCharacters();
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

			if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
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

			if ((pX != NULL)&&(pX->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
			{
				bHasAct = TRUE;
			}
			else
			{
				pX = pX_set;
			}
		}
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest)
	{
		pX = (CDvmValue*)pValues->FindByID("FaultCurrent");
		pY = (CDvmValue*)pValues->FindByID("TripTime");
		pX_set = pX;
		pY_set = (CDvmValue*)pValues->FindByID("SettingTime");

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
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

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = pY_set;
		}
	}
	else if (m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest)
	{
		pX = (CDvmValue*)pValues->FindByID("FaultVolt");
		pY = (CDvmValue*)pValues->FindByID("TripTime");
		pX_set = pX;
		pY_set = (CDvmValue*)pValues->FindByID("MaxFaultTime");

		if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
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

		if ((pX != NULL)&&(pX->m_strValue != /*_T("未动作")*//*g_sLangTxt_State_NoActioned*/g_sLangTxt_Unact))//lcq
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

		QCharTestPointsGrid *pCharTestPointsGrid = g_theTestCntrFrame->GetCharTestPointsGrid();

		if (pCharTestPointsGrid)
		{
			pCharTestPointsGrid->AddTestResultPoint(dX, dY,bHasAct,dX_set,dY_set);
		}
		g_theTestCntrFrame->AddTestPoints(dX, dY,bHasAct);
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














