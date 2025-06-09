#include "QCharEditRadioHarmWidget.h"
//#include "ui_QCharEditRadioHarmWidget.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QCharEditRadioHarmWidget::QCharEditRadioHarmWidget( QWidget *parent /*= 0*/,CDiffCharCal *pDiffCharCal )
{
    ui.setupUi(this);

	m_pGridCharLine = new QCharEditGrid_DiffLine(this);
	m_pGridCharLine->InitGrid();
	ui.verticalLayout->addWidget(m_pGridCharLine);
	m_pGridCharLine->AttachDataViewOptrInterface(this);
	m_nTranSort = 0;

	
	if(pDiffCharCal == NULL)
	{
		return;
	}
	m_pDiffCharCal = pDiffCharCal;

	InitUI();
	InitChar();
	InitConnect();
        InitLanguage();
	SetDiffFont();


}

QCharEditRadioHarmWidget::~QCharEditRadioHarmWidget()
{
    
}

void QCharEditRadioHarmWidget::InitUI()
{
	ui.m_cbSettingMinAxis->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DifferMarkType")));
	ui.m_cbHarmIndex->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DiffHarmIndex")));

	this->setFixedSize(450, 540); 
	//this->setFixedSize(ui.m_mainVerticalLayout->sizeHint());
	ui.m_label_Func->setMinimumSize(400, 90);
	if(m_astrTranSortList.length() > 0)
	{
		m_astrTranSortList.clear();
	}	

	m_astrTranSortList<</*tr("Y/V接线平衡变压器")*/g_sLangTxt_Gradient_YNWirBlancer<</*tr("Y/△-11接线(无转角)")*/g_sLangTxt_Gradient_YNoCorners<</*tr("单相变压器")*/g_sLangTxt_Gradient_Sphase<</*tr("Y/△/△接线")*/g_sLangTxt_Gradient_YDSCornect<<tr("Scott(1)")<<tr("V/V(1)")\
		<<tr("V/X")<</*tr("Y/A 接线阻抗匹配平衡变压器")*/g_sLangTxt_Gradient_ImpedanceMB<</*tr("三相V/V接线变压器")*/g_sLangTxt_Gradient_ThrVWirceTF<<tr("Scott(2)")<<tr("Scott(3)")<<tr("V/V(2)")<<tr("Scott(4)")\
		<</*tr("三相V/V接线变压器2")*/g_sLangTxt_Gradient_SecThrVWirceTF<</*tr("三相V/V")*/g_sLangTxt_Gradient_VThrPhase<<tr("Y/V(2)")<<tr("Scott(5)")<</*tr("Y/△-11接线(Y侧转角)")*/g_sLangTxt_Gradient_YSideCorner; //lcq

	ui.m_cmb_TranSort->addItems(m_astrTranSortList);

	initMaxPositiveEdit(ui.m_edtSet_Istart);
	initMaxPositiveEdit(ui.m_edtSet_Isd);
	initMaxPositiveEdit(ui.m_editInSet);
	initMaxPositiveEdit(ui.m_editHarmCoef);
	initMaxPositiveEdit(ui.m_editSet_IdValue);
	ui.m_editSet_IdValue->setText("1.5");

	slot_btnUserClear(true);
	ui.gridLayout_4->setContentsMargins(0,0,0,0);

	ui.gridLayout_4->setMargin(0);//设置外边距



}

void QCharEditRadioHarmWidget::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.m_lbSettingMinAxis, g_sLangTxt_Native_DevSetMethod, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbHarmIndex, g_sLangTxt_Native_harmonicOrder, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbHarmCoef, g_sLangTxt_State_HarmonicBrakingcoefficient, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbTranSort, g_sLangTxt_Native_TransConnForm, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleStart, g_sLangTxt_Native_Threshold, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleLineSd, g_sLangTxt_Native_QuickBreak, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_btnUserAdd, g_sLangTxt_Gradient_AddCusp, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.m_btnUserClear, g_sLangTxt_Gradient_Emptycusp, XLang_Ctrls_QPushButton);
}


void QCharEditRadioHarmWidget::SetDiffFont()
{
	m_pGridCharLine->setFont(*g_pSttGlobalFont);
	m_pGridCharLine->horizontalHeader()->setFont(*g_pSttGlobalFont);

	ui.m_edtSet_Istart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleStart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLineSd->setFont(*g_pSttGlobalFont);

	ui.m_lbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_cbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_lbInSet->setFont(*g_pSttGlobalFont);
	ui.m_editInSet->setFont(*g_pSttGlobalFont);
	ui.m_lbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_cbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_lbHarmCoef->setFont(*g_pSttGlobalFont);
	ui.m_editHarmCoef->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Isd->setFont(*g_pSttGlobalFont);

	ui.m_btnUserClear->setFont(*g_pSttGlobalFont);
	ui.m_btnUserAdd->setFont(*g_pSttGlobalFont);
	ui.m_lbIdValue->setFont(*g_pSttGlobalFont);
	ui.m_editSet_IdValue->setFont(*g_pSttGlobalFont);

	ui.m_lbTranSort->setFont(*g_pSttGlobalFont);
	ui.m_cmb_TranSort->setFont(*g_pSttGlobalFont);
}

void QCharEditRadioHarmWidget::InitConnect()
{

	connect(m_pGridCharLine, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_pGridCharLine, SIGNAL(sig_DiffCharChanged()), this,SLOT(slot_DiffCharChanged()));

	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));
	connect(ui.m_editHarmCoef, SIGNAL(editingFinished()), this, SLOT(slot_HarmCoef_editingFinished()));
	connect(ui.m_editInSet, SIGNAL(editingFinished()), this, SLOT(slot_InSet_editingFinished()));
	connect(ui.m_btnUserAdd, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));
	connect(ui.m_btnUserClear, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	connect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));

#ifdef _PSX_QT_LINUX_

	connect(ui.m_edtSet_Istart,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Isd,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));

#endif

}

void QCharEditRadioHarmWidget::InitChar()
{
	CCharacteristic* pChar =  GetCurrentCharacter();
	if(!pChar)
	{
		//没有配置文件,则初始化
        stt_Frame_Characteristics()->InitEmptyCharacter(AXIS_TYPE_ID_CARTES);
		pChar = GetCurrentCharacter();
		pChar->InitAfterRead();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_HORZ;
	}
	else
	{
		CCharacterArea* pArea = pChar->GetCharacterArea();
		//设置门槛值
		CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
		m_pDiffCharCal->m_fIcdqd = CString_To_double(pLine->m_strYb);
		m_pDiffCharCal->m_fKid0 = CalLineK(pLine);

		//设置拐点
		switch(pArea->GetCount())
		{
		case 5:
			pLine = (CCharElementLined*)pArea->GetAt((long)3);
			m_pDiffCharCal->m_fKid3 = CalLineK(pLine);
			m_pDiffCharCal->m_fIp3 = CString_To_double(pLine->m_strXb);
		case 4:
			pLine = (CCharElementLined*)pArea->GetAt((long)2);
			m_pDiffCharCal->m_fKid2 = CalLineK(pLine);
			m_pDiffCharCal->m_fIp2 = CString_To_double(pLine->m_strXb);
		case 3:
			pLine = (CCharElementLined*)pArea->GetAt((long)1);
			m_pDiffCharCal->m_fKid1 = CalLineK(pLine);
			m_pDiffCharCal->m_fIp1 = CString_To_double(pLine->m_strXb);
			break;
		default:
			break;
		}

		m_pDiffCharCal->m_nKneePoints = pArea->GetCount() - 2;

		//设置速断
		pLine = (CCharElementLined*)pArea->GetTail();
		m_pDiffCharCal->m_fIsd = CString_To_double(pLine->m_strYb);
	}
	InitDiffData();
}

void QCharEditRadioHarmWidget::InitDiffData()
{
	disconnect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	disconnect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));
	disconnect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));

	ui.m_cbSettingMinAxis->SetSelByIndex(m_pDiffCharCal->m_nMinAxis);
	ui.m_cbHarmIndex->SetSelByIndex(m_pDiffCharCal->m_nHarmIndex);
	ui.m_cmb_TranSort->SetSelByIndex(m_nTranSort);

	CString strText;

	strText.Format("%.3f", m_pDiffCharCal->m_fInSet);
	ui.m_editInSet->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fHarmCoef);
	ui.m_editHarmCoef->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fIcdqd);
	ui.m_edtSet_Istart->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fIsd);
	ui.m_edtSet_Isd->setText(strText);	

	strText.Format("%.3f", m_pDiffCharCal->m_fIp2);
	strText.Format("%.3f", m_pDiffCharCal->m_fIp3);

	strText.Format("%.3f", m_pDiffCharCal->m_fKid0);
	strText.Format("%.3f", m_pDiffCharCal->m_fKid1);
	strText.Format("%.3f", m_pDiffCharCal->m_fKid2);
	strText.Format("%.3f", m_pDiffCharCal->m_fKid3);
	strText.Format("%.3f", m_pDiffCharCal->m_fIp1);

	emit sig_ChangeCTPoint(m_bAmbo);
	InitUI_Unit();
	UpdateTranSortIndex(m_nTranSort);


	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));
	connect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));

}

void QCharEditRadioHarmWidget::slot_CmbSettingMinAxisIndexChanged( int nIndex )
{
	m_pDiffCharCal->m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();	
	UpdateEditsDisEnable();
	InitUI_Unit();
	emit sig_ChangeICMAxisName();
	emit sig_ChangeSettingMinAxisIndex(nIndex);
}

void QCharEditRadioHarmWidget::slot_CmbHarmIndexChanged( int nIndex )
{
	m_pDiffCharCal->m_nHarmIndex = ui.m_cbHarmIndex->GetSelectIndex2();
}

void QCharEditRadioHarmWidget::UpdateEditsDisEnable()
{

	if (m_pDiffCharCal->m_nMinAxis == 0)//有名值
	{
		ui.m_editInSet->setEnabled(false);
	}
	else
	{
		ui.m_editInSet->setEnabled(true);
	}
}

void QCharEditRadioHarmWidget::InitUI_Unit()
{
	CString strText,strText_IrAxis,strText_IdAxis,strCustomText,strText_cbInsel,strText_AxisTitle;
	
	if (m_pDiffCharCal->m_nMinAxis)
	{
		strCustomText = /*_T("制动电流(Ie)")*/g_sLangTxt_Native_Iecurrent;
		strText_cbInsel =/* _T("基准电流(Ie)")*/g_sLangTxt_Gradient_IRCurrent;  //lcq
	} 
	else
	{
		strCustomText = /*_T("制动电流(A)")*/g_sLangTxt_Native_Acurrent;
		strText_cbInsel = /*_T("基准电流(A)")*/g_sLangTxt_Gradient_ARCurrent;   //lcq
	}

	ui.m_lbInSet->setText(strText_cbInsel);
	ui.m_lbIdValue->setText(strCustomText);
	ui.m_cmb_TranSort->setCurrentIndex(m_nTranSort);
}

float QCharEditRadioHarmWidget::CalLineK( CCharElementLined* pLine )
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditRadioHarmWidget::slot_InSet_editingFinished()
{
	SetParaI(ui.m_editInSet, m_pDiffCharCal->m_fInSet);
	emit sig_MainWidgetCharChange();
	emit sig_ChangeInset(m_pDiffCharCal->m_fInSet);
}

float QCharEditRadioHarmWidget::SetParaI( QLineEdit* pEdit, float& fv )
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

float QCharEditRadioHarmWidget::SetLimit( float min,float max,float val )
{
	if (val<min)
	{
		val = min;
	}
	else if (val>max)
	{
		val = max;
	}
	return val;
}

void QCharEditRadioHarmWidget::UpdateEdit_IrValueUserPoint()
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();

	if(!pPoint)
	{
		return;
	}

	CString strValue;
	
	strValue.Format(_T("%.03f"),pPoint->m_fY);
	
	disconnect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	ui.m_editSet_IdValue->setText(strValue);
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));

}

//void QCharEditRadioHarmWidget::UpdateChar( BOOL bUpdateTable /*= FALSE*/,BOOL bCharTypeChanged /*= FALSE*/,BOOL bParasChanged /*= TRUE*/ )
//{
//	long bChanged = m_pDiffCharCal->m_oPoints.GetCount();
//
//	m_pDiffCharCal->CalHarm();
//	
//	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->GetTail();
//
//	if (pChar == NULL)
//	{
//		return;
//	}
//
//	pChar->m_bXMin = TRUE;
//	pChar->m_bXMax = TRUE;
//	pChar->m_bYMin = TRUE;
//	pChar->m_bYMax = TRUE;
//	pChar->m_fXMin = 0.0f;
//	pChar->m_fYMin = 0.0f;
//	pChar->m_fXMax = m_pDiffCharCal->m_fXMax;
//	pChar->m_fYMax = m_pDiffCharCal->m_fYMax;
//	pChar->m_strXMin = _T("0.0");
//	pChar->m_strYMin = _T("0.0");
//	pChar->m_strXMax.Format(_T("%lf"),pChar->m_fXMax);
//	pChar->m_strYMax.Format(_T("%lf"),pChar->m_fYMax);
//	CCharacterArea* pArea = pChar->GetCharacterArea();
//
//	if((!bCharTypeChanged) && (bChanged != m_pDiffCharCal->m_oPoints.GetCount()))
//	{
//		//段数改变
//		pArea->DeleteAll();
//		CCharElement *pCharElement = pArea->GetCharBisector();
//
//		if (pCharElement != NULL)//20230206 zhouhj  拐点等线段也删除
//		{
//			pCharElement->DeleteAll();
//		}
//
//		POS pos = m_pDiffCharCal->m_oPoints.GetHeadPosition();
//		CXDrawData_Point* pLast = NULL;
//		CString strFX, strFY;
//		long nLineIndex = 0;
//
//		while (pos)
//		{
//			CXDrawData_Point* pt = (CXDrawData_Point*)m_pDiffCharCal->m_oPoints.GetNext(pos);
//
//			if(pLast)
//			{
//				CCharElementLined* pLine = new CCharElementLined;
//				strFX.Format("%.3f", pLast->m_fX);
//				strFY.Format("%.3f", pLast->m_fY);
//				pLine->SetBeginPoint(strFX, strFY);
//				strFX.Format("%.3f", pt->m_fX);
//				strFY.Format("%.3f", pt->m_fY);
//				pLine->SetEndPoint(strFX, strFY);
//				pArea->AddNewChild(pLine);
//				nLineIndex++;
//			}
//
//			pLast = pt;
//		}
//
//		ShowDatas_Table();
//	}
//	else
//	{
//		POS pos = m_pDiffCharCal->m_oPoints.GetHeadPosition();
//		CXDrawData_Point* pLast = NULL;
//		CString strFX, strFY;
//		long nIndex = 0;
//		while (pos)
//		{
//			CXDrawData_Point* pt = (CXDrawData_Point*)m_pDiffCharCal->m_oPoints.GetNext(pos);
//			if(pLast)
//			{
//				CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
//				strFX.Format("%.3f", pLast->m_fX);
//				strFY.Format("%.3f", pLast->m_fY);
//				pLine->SetBeginPoint(strFX, strFY);
//				strFX.Format("%.3f", pt->m_fX);
//				strFY.Format("%.3f", pt->m_fY);
//				pLine->SetEndPoint(strFX, strFY);
//				nIndex++;
//			}
//			pLast = pt;
//		}
//
//		if (bUpdateTable)
//		{
//			ShowDatas_Table();
//		}
//	}
//
//	emit sig_CharChanged(GetCurrentCharacter(),bParasChanged);	
//
//
//
//}

//void QCharEditRadioHarmWidget::GroupDatasToChar( CDataGroup *pDatas )
//{
//	stt_GetDataValueByID(pDatas,CharDiff_ID_IDoor,m_pDiffCharCal->m_fIcdqd);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_IQuickSetting,m_pDiffCharCal->m_fIsd);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_CTPoint,m_pDiffCharCal->m_nCTPoint);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp1,m_pDiffCharCal->m_fIp1);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp2,m_pDiffCharCal->m_fIp2);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp3,m_pDiffCharCal->m_fIp3);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Kid,m_pDiffCharCal->m_fKid0);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid1,m_pDiffCharCal->m_fKid1);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid2,m_pDiffCharCal->m_fKid2);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid3,m_pDiffCharCal->m_fKid3);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateHarm,m_pDiffCharCal->m_fHarmCoef);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_MinAxis,m_pDiffCharCal->m_nMinAxis);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Insel,m_pDiffCharCal->m_nInsel);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_In,m_pDiffCharCal->m_fInSet);
//
//	stt_GetDataValueByID(pDatas,CharDiff_ID_HarmIndex,m_pDiffCharCal->m_nHarmIndex);
//
//	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrPointNum,m_pDiffCharCal->m_nPointNum[0]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1PointNum,m_pDiffCharCal->m_nPointNum[1]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2PointNum,m_pDiffCharCal->m_nPointNum[2]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3PointNum,m_pDiffCharCal->m_nPointNum[3]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrPointNum,m_pDiffCharCal->m_nPointNum[4]);
//
//	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrErrorBand,m_pDiffCharCal->m_fErrorBand[0]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1ErrorBand,m_pDiffCharCal->m_fErrorBand[1]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2ErrorBand,m_pDiffCharCal->m_fErrorBand[2]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3ErrorBand,m_pDiffCharCal->m_fErrorBand[3]);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrErrorBand,m_pDiffCharCal->m_fErrorBand[4]);
//
//	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = 1;
//	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Check,nStartCurrCheck);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1_Check,nRateCoef1Check);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2_Check,nRateCoef2Check);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3_Check,nRateCoef3Check);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurr_Check,m_pDiffCharCal->m_nSelectSd);
//	m_pDiffCharCal->m_nKneePoints = nRateCoef1Check + nRateCoef2Check + nRateCoef3Check;
//
//	InitDiffData();
//	UpdateEditsDisEnable();
//	UpdateChar(TRUE,FALSE,FALSE);
//}

CCharacteristic* QCharEditRadioHarmWidget::GetCurrentCharacter()
{
	return stt_Frame_Characteristics()->GetTail_Char();
}

long QCharEditRadioHarmWidget::GetSettingMinAxisIndex()
{
	return ui.m_cbSettingMinAxis->GetSelectIndex2();
}

void QCharEditRadioHarmWidget::slot_btnUserAdd( bool bState )
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
	if(!pPoint)
	{
		return;
	}

    CCharacteristic* pChar = stt_Frame_Characteristics()->GetTail_Char();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();

	pCharLine = (CCharElementLined*)pArea->GetAt(1);
	double dXb = 0, dYb = 0, dXe = 0, dYe = 0;
	pCharLine->GetLine(dXb, dYb, dXe, dYe);

	CCharTestLine* pTestLine = new CCharTestLine();
	pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
	pTestLine->m_nTestLineID = char_GetTestLineID(pCharLine, pCharLine->GetUserTestPoints());
	pTestLine->m_fPos = pPoint->m_fY;
	pTestLine->m_fXset = pPoint->m_fX;
	pTestLine->m_fYset = pPoint->m_fY;
	pTestLine->m_fXb = pPoint->m_fX + pCharLine->GetErrorLength();
	pTestLine->m_fXe = pPoint->m_fX - pCharLine->GetErrorLength();
	pTestLine->m_fYb = pPoint->m_fY;
	pTestLine->m_fYe = pPoint->m_fY;
	pCharLine->AddNewChild(pTestLine);
	pCharLine->SetUserTestPoint(pCharLine->GetUserTestPoints() + 1);

	emit sig_UpdateChar(TRUE,FALSE,TRUE);

}

void QCharEditRadioHarmWidget::slot_btnUserClear( bool bState )
{
    CCharacteristic* pChar = stt_Frame_Characteristics()->GetTail_Char();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();
	long nIndex = 0;
	while (pos)
	{
		pCharLine = (CCharElementLined*)pArea->GetNext(pos);
		for (int i = pCharLine->GetCount() - 1; i >= 0; i-- )
		{
			CCharTestLine* pTestLine = (CCharTestLine*)pCharLine->GetAt(i);
			if(pTestLine->m_strType == CHAR_TEST_LINE_TYPE_USER)
			{
				pCharLine->DeleteAt(i);
			}
		}
		pCharLine->SetUserTestPoint(0);
	}
	emit sig_UpdateChar(TRUE,FALSE,TRUE);
}

void QCharEditRadioHarmWidget::slot_TestPointsErrorBandChanged()
{
	emit sig_TestPointsErrorBandChanged();
}

void QCharEditRadioHarmWidget::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditRadioHarmWidget::slot_IdValue_editingFinished()
{
	CString strIdValue = ui.m_editSet_IdValue->text();
	emit sig_IdValue_editingFinished(strIdValue);
}

void QCharEditRadioHarmWidget::slot_HarmCoef_editingFinished()
{
	SetParaK(ui.m_editHarmCoef, m_pDiffCharCal->m_fHarmCoef);
	emit sig_MainWidgetCharChange();
}

float QCharEditRadioHarmWidget::SetParaK( QLineEdit* pEdit, float& fv )
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

void QCharEditRadioHarmWidget::on_m_onlineEdit_Changed()
{
	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
}

void QCharEditRadioHarmWidget::on_m_edtSet_Istart_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Istart, m_pDiffCharCal->m_fIcdqd);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
	emit sig_ChangeIstart(fv);
}

void QCharEditRadioHarmWidget::on_m_edtSet_Isd_editingFinished()
{
	if(ui.m_edtSet_Isd->text().toDouble()<ui.m_edtSet_Istart->text().toDouble())
	{
		ui.m_edtSet_Isd->setText("error");
		return;
	}
	float fv = SetParaI(ui.m_edtSet_Isd, m_pDiffCharCal->m_fIsd);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
	emit sig_ChangeIsd(fv);

}

void QCharEditRadioHarmWidget::UpdateTranSortIndex(int index )
{

#ifdef _PSX_QT_WINDOWS_ 
	CString strName;
	CString strPicPath = _P_GetResourcePath();

	if(ElecRailway_TransType_0_YV <0 || index > ElecRailway_TransType_17_YD11_YT)
		return;

	QString strPic;
	switch(index)
	{
	case ElecRailway_TransType_0_YV:
		if (m_bAmbo)  //一侧指向变压器
		{
			strPic = QString("/images/Y-V_2.png");
		}
		else
		{
			strPic = QString("/images/Y-V.png");
		}
		break;
	case ElecRailway_TransType_1_YD11:
		if (m_bAmbo)
		{
			strPic = QString("/images/Y-Angle-11_2.png");
		}
		else
		{
			strPic = QString("/images/Y-Angle-11.png");
		}
		break;
	case ElecRailway_TransType_2_Single:
		if (m_bAmbo)
		{
			strPic = QString("/images/SinglePh_2.png");
		}
		else
		{
			strPic = QString("/images/SinglePh.png");
		}
		break;
	case ElecRailway_TransType_3_YDD:
		if (m_bAmbo)
		{
			strPic = QString("/images/Y-Angle-Angle_2.png");
		}
		else
		{
			strPic = QString("/images/Y-Angle-Angle.png");
		}
		break;
	case ElecRailway_TransType_4_Scott1:
		if (m_bAmbo)
		{
			strPic = QString("/images/Scott(1)_2.png");
		}
		else
		{
			strPic = QString("/images/Scott(1).png");
		}
		break;
	case ElecRailway_TransType_5_VV1:
		if (m_bAmbo)
		{
			strPic = QString("/images/V-V(1)_2.png");
		}
		else
		{
			strPic = QString("/images/V-V(1).png");
		}
		break;
	case ElecRailway_TransType_6_VX:
		if (m_bAmbo)
		{
			strPic = QString("/images/V-X_2.png");
		}
		else
		{
			strPic = QString("/images/V-X.png");
		}
		break;
	case ElecRailway_TransType_7_YA:
		if (m_bAmbo)
		{
			strPic = QString("/images/Y-A_2.png");
		}
		else
		{
			strPic = QString("/images/Y-A.png");
		}
		break;
	case ElecRailway_TransType_8_ThreeVV:
		if (m_bAmbo)
		{
			strPic = QString("/images/ThreePhV-V_2.png");
		}
		else
		{
			strPic = QString("/images/ThreePhV-V.png");
		}
		break;
	case ElecRailway_TransType_9_Scott2:
		if (m_bAmbo)
		{
			strPic = QString("/images/Scott(2)_2.png");
		}
		else
		{
			strPic = QString("/images/Scott(2).png");
		}
		break;
	case ElecRailway_TransType_10_Scott3:
		if (m_bAmbo)
		{
			strPic = QString("/images/Scott(3)_2.png");
		}
		else
		{
			strPic = QString("/images/Scott(3).png");
		}
		break;
	case ElecRailway_TransType_11_VV2:
		if (m_bAmbo)
		{
			strPic = QString("/images/V-V(2)_2.png");
		}
		else
		{
			strPic = QString("/images/V-V(2).png");
		}
		break;
	case ElecRailway_TransType_12_Scott4:
		if (m_bAmbo)
		{
			strPic = QString("/images/Scott(4)_2.png");
		}
		else
		{
			strPic = QString("/images/Scott(4).png");
		}
		break;
	case ElecRailway_TransType_13_ThreeVV2:
		if (m_bAmbo)
		{
			strPic = QString("/images/ThreePhV-V2_2.png");
		}
		else
		{
			strPic = QString("/images/ThreePhV-V2.png");
		}
		break;
	case ElecRailway_TransType_14_ThreeVV3:
		if (m_bAmbo)
		{
			strPic = QString("/images/ThreePhV-V3_2.png");
		}
		else
		{
			strPic = QString("/images/ThreePhV-V3.png");
		}
		break;
	case ElecRailway_TransType_15_ThreeYV2:
		if (m_bAmbo)
		{
			strPic = QString("/images/Y-V(2)_2.png");
		}
		else
		{
			strPic = QString("/images/Y-V(2).png");
		}
		break;
	case ElecRailway_TransType_16_Scott5:
		if (m_bAmbo)
		{
			strPic = QString("/images/Scott(5)_2.png");
		}
		else
		{
			strPic = QString("/images/Scott(5).png");
		}
		break;
	case ElecRailway_TransType_17_YD11_YT:
		if (m_bAmbo)
		{
			strPic = QString("/images/Y-Angle-11YT_2.png");
		}
		else
		{
			strPic = QString("/images/Y-Angle-11YT.png");
		}
		break;
	}

	strName = strPicPath + strPic;
#else
	CString strName;
	//CString strPicPath = _P_GetResourcePath();

	if(ElecRailway_TransType_0_YV <0 || index > ElecRailway_TransType_17_YD11_YT)
		return;

	QString strPic;
	switch(index)
	{
	case ElecRailway_TransType_0_YV:
		if (m_bAmbo)  //一侧指向变压器
		{
			strPic = QString(":/ctrls/images/Y-V_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-V.png");
		}
		break;
	case ElecRailway_TransType_1_YD11:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Y-Angle-11_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-Angle-11.png");
		}
		break;
	case ElecRailway_TransType_2_Single:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/SinglePh_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/SinglePh.png");
		}
		break;
	case ElecRailway_TransType_3_YDD:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Y-Angle-Angle_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-Angle-Angle.png");
		}
		break;
	case ElecRailway_TransType_4_Scott1:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Scott(1)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Scott(1).png");
		}
		break;
	case ElecRailway_TransType_5_VV1:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/V-V(1)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/V-V(1).png");
		}
		break;
	case ElecRailway_TransType_6_VX:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/V-X_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/V-X.png");
		}
		break;
	case ElecRailway_TransType_7_YA:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Y-A_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-A.png");
		}
		break;
	case ElecRailway_TransType_8_ThreeVV:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/ThreePhV-V_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/ThreePhV-V.png");
		}
		break;
	case ElecRailway_TransType_9_Scott2:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Scott(2)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Scott(2).png");
		}
		break;
	case ElecRailway_TransType_10_Scott3:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Scott(3)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Scott(3).png");
		}
		break;
	case ElecRailway_TransType_11_VV2:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/V-V(2)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/V-V(2).png");
		}
		break;
	case ElecRailway_TransType_12_Scott4:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Scott(4)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Scott(4).png");
		}
		break;
	case ElecRailway_TransType_13_ThreeVV2:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/ThreePhV-V2_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/ThreePhV-V2.png");
		}
		break;
	case ElecRailway_TransType_14_ThreeVV3:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/ThreePhV-V3_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/ThreePhV-V3.png");
		}
		break;
	case ElecRailway_TransType_15_ThreeYV2:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Y-V(2)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-V(2).png");
		}
		break;
	case ElecRailway_TransType_16_Scott5:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Scott(5)_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Scott(5).png");
		}
		break;
	case ElecRailway_TransType_17_YD11_YT:
		if (m_bAmbo)
		{
			strPic = QString(":/ctrls/images/Y-Angle-11YT_2.png");
		}
		else
		{
			strPic = QString(":/ctrls/images/Y-Angle-11YT.png");
		}
		break;
	}

	strName = strPic;
#endif

	QPixmap pix(strName);

	pix = pix.scaled(ui.m_label_Func->width(),ui.m_label_Func->height(),Qt::KeepAspectRatio);

	ui.m_label_Func->setPixmap(pix);
	ui.m_label_Func->setAlignment(Qt::AlignCenter);

}

void QCharEditRadioHarmWidget::slot_normalChangeTransSort( int index )
{
	ui.m_cmb_TranSort->setCurrentIndex(index);
	m_nTranSort = index;
	UpdateTranSortIndex(index);
}

void QCharEditRadioHarmWidget::slot_cmb_TranSortIndexChanged( int index )
{
	UpdateTranSortIndex(index);
	emit sig_ChangeTranSortIndex(index);
}

void QCharEditRadioHarmWidget::slot_normalChangeSettingMinAxis( int index )
{
	ui.m_cbSettingMinAxis->setCurrentIndex(index);
	//m_pDiffCharCal->m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();	
	UpdateEditsDisEnable();
	InitUI_Unit();
}



void QCharEditRadioHarmWidget::slot_normalChangeInSet( float InSet )
{
	QString nInSet=QString::number(InSet,'f',3);
	ui.m_editInSet->setText(nInSet);
	SetParaI(ui.m_editInSet, m_pDiffCharCal->m_fInSet);
}


void QCharEditRadioHarmWidget::slot_normalChangeCTPoint( bool bAmbo )
{
	if(bAmbo == true)
	{
		m_bAmbo = true;
	}
	else if(bAmbo == false)
	{
		m_bAmbo = false;
	}
	UpdateTranSortIndex(m_nTranSort);

}

void QCharEditRadioHarmWidget::InitDataToChar()
{
	InitDiffData();
	UpdateEditsDisEnable();
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditRadioHarmWidget::slot_normalChangeIstart(float Istart)
{
	QString nIstart=QString::number(Istart,'f',3);
	ui.m_edtSet_Istart->setText(nIstart);
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditRadioHarmWidget::slot_normalChangeIsd( float Isd )
{
	QString nIsd=QString::number(Isd,'f',3);
	ui.m_edtSet_Isd->setText(nIsd);
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}



void QCharEditRadioHarmWidget::SetCDiffCharCal( CDiffCharCal *pDiffCharCal )
{
	if(pDiffCharCal == NULL)
	{
		return;
	}
	m_pDiffCharCal = pDiffCharCal;
}

void QCharEditRadioHarmWidget::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{

	CCharElement *pCurrSelElement = (CCharElement*)m_pGridCharLine->GetCurrSelData();

	if (pCurrSelElement == NULL)
	{
		return;
	}

	emit sig_ActiveSegment(pCurrSelElement);
}


