#include "QCharEditRadioNormalWidget.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//////////////QCharEditRadioNormalWidget////////////////


QCharEditRadioNormalWidget::QCharEditRadioNormalWidget( QWidget *parent /*= 0*/,CDiffCharCal *pDiffCharCal )
{
	ui.setupUi(this);

	m_pGridCharLine = new QCharEditGrid_DiffLine(this);
	m_pGridCharLine->InitGrid();
	ui.m_mainVerticalLayout->insertWidget(2,m_pGridCharLine);
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

QCharEditRadioNormalWidget::~QCharEditRadioNormalWidget()
{

}
void QCharEditRadioNormalWidget::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.m_lbSettingMinAxis, g_sLangTxt_Native_DevSetMethod, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbTranSort, g_sLangTxt_Native_TransConnForm, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbName, g_sLangTxt_Name, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lbSetting, g_sLangTxt_FixedValue, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleK, g_sLangTxt_Native_RatioBrakeCoefficient, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_chkStart, g_sLangTxt_Gradient_StartTs, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleStart, g_sLangTxt_Gradient_StartCur, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_chkLine1, g_sLangTxt_Native_FirstPart, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleLine1, g_sLangTxt_Native_Inflection1, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_chkLine2, g_sLangTxt_Native_SecondPart, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleLine2, g_sLangTxt_Native_InflectionPoint2, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_chkLineSd, g_sLangTxt_Native_InstCurr, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.m_lblTitleLineSd, g_sLangTxt_Native_DiffSpdBrk, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui.m_btnUserAdd, g_sLangTxt_Gradient_AddCusp, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.m_btnUserClear, g_sLangTxt_Gradient_Emptycusp, XLang_Ctrls_QPushButton);
}

void QCharEditRadioNormalWidget::InitUI()
{
	ui.m_cbSettingMinAxis->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DifferMarkType")));

	if(m_astrTranSortList.length() > 0)
	{
		m_astrTranSortList.clear();
	}	
// 	m_astrTranSortList<<tr("Y/V接线平衡变压器")<<tr("Y/△-11接线(无转角)")<<tr("单相变压器")<<tr("Y/△/△接线")<<tr("Scott(1)")<<tr("V/V(1)")\
// 		<<tr("V/X")<<tr("Y/A 接线阻抗匹配平衡变压器")<<tr("三相V/V接线变压器")<<tr("Scott(2)")<<tr("Scott(3)")<<tr("V/V(2)")<<tr("Scott(4)")\
// 		<<tr("三相V/V接线变压器2")<<tr("三相V/V")<<tr("Y/V(2)")<<tr("Scott(5)")<<tr("Y/△-11接线(Y侧转角)");

	m_astrTranSortList<</*tr("Y/V接线平衡变压器")*/g_sLangTxt_Gradient_YNWirBlancer<</*tr("Y/△-11接线(无转角)")*/g_sLangTxt_Gradient_YNoCorners<</*tr("单相变压器")*/g_sLangTxt_Gradient_Sphase<</*tr("Y/△/△接线")*/g_sLangTxt_Gradient_YDSCornect<<tr("Scott(1)")<<tr("V/V(1)")\
		<<tr("V/X")<</*tr("Y/A 接线阻抗匹配平衡变压器")*/g_sLangTxt_Gradient_ImpedanceMB<</*tr("三相V/V接线变压器")*/g_sLangTxt_Gradient_ThrVWirceTF<<tr("Scott(2)")<<tr("Scott(3)")<<tr("V/V(2)")<<tr("Scott(4)")\
		<</*tr("三相V/V接线变压器2")*/g_sLangTxt_Gradient_SecThrVWirceTF<</*tr("三相V/V")*/g_sLangTxt_Gradient_VThrPhase<<tr("Y/V(2)")<<tr("Scott(5)")<</*tr("Y/△-11接线(Y侧转角)")*/g_sLangTxt_Gradient_YSideCorner; //lcq
	ui.m_cmb_TranSort->addItems(m_astrTranSortList);

	initMaxPositiveEdit(ui.m_edtSet_Istart);
	initMaxPositiveEdit(ui.m_edtSet_Ip1);
	initMaxPositiveEdit(ui.m_edtSet_Ip2);
	initMaxPositiveEdit(ui.m_edtSet_Isd);
	initMaxPositiveEdit(ui.m_edtSet_K1);
	initMaxPositiveEdit(ui.m_edtSet_K2);
	initMaxPositiveEdit(ui.m_editSet_IdValue);
	initMaxPositiveEdit(ui.m_editInSet);
	initMaxPositiveEdit(ui.m_edtSet_Kstart);
	ui.m_editSet_IdValue->setText("1.5");
	
	
	ui.m_chkStart->setEnabled(false);
	ui.m_chkLine1->setEnabled(false);

	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QCheckBox::indicator:checked {image: url(:/ctrls/images/checked.png);} QCheckBox::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	ui.m_chkStart->setStyleSheet(strStyleSheet);
	ui.m_chkLine1->setStyleSheet(strStyleSheet);
	ui.m_chkLineSd->setStyleSheet(strStyleSheet);
	ui.m_chkLine2->setStyleSheet(strStyleSheet);

	ui.m_chkStart->setChecked(true);
	ui.m_chkLine1->setChecked(true);
	ui.m_chkLineSd->setChecked(true);
	ui.m_chkLine2->setChecked(true);

	ui.m_edtSet_Ip2->setEnabled(false);
	ui.m_edtSet_K2->setEnabled(false);
	ui.m_edtSet_Kstart->setEnabled(false);

	ui.m_mainVerticalLayout->setSpacing(5);
	ui.gridLayout->setSpacing(5);
	ui.gridLayout_2->setSpacing(5);
	ui.m_label_Func->setMinimumSize(400, 90);
	this->setFixedSize(450, 540); 
}

void QCharEditRadioNormalWidget::InitConnect()
{
	connect(m_pGridCharLine, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_pGridCharLine, SIGNAL(sig_DiffCharChanged()), this,SLOT(slot_DiffCharChanged()));
	connect(ui.m_btnUserAdd, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));
	connect(ui.m_btnUserClear, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_editInSet, SIGNAL(editingFinished()), this, SLOT(slot_InSet_editingFinished()));
	connect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));

#ifdef _PSX_QT_LINUX_

	connect(ui.m_edtSet_Istart,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip1,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip2,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Isd,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Kstart,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K1,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K2,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));

#endif
}


CCharacteristic* QCharEditRadioNormalWidget::GetCurrentCharacter()
{
	return (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
}



void QCharEditRadioNormalWidget::on_m_chkStart_clicked()
{
	if(!ui.m_chkStart->isChecked())
	{
		ui.m_chkStart->setChecked(true);
	}
}

void QCharEditRadioNormalWidget::on_m_chkLine1_clicked()
{
	if(!ui.m_chkLine1->isChecked())
	{
		ui.m_chkLine1->setChecked(true);
	}
}

void QCharEditRadioNormalWidget::on_m_chkLine2_clicked()
{
	if(ui.m_chkLine2->isChecked())
	{
		EnableEdit(CharDiff_RateCoef2_Index);
	}
	else
	{
		DisableEdit(CharDiff_RateCoef2_Index);
	}
}


void QCharEditRadioNormalWidget::on_m_chkLineSd_clicked()
{
	if(ui.m_chkLineSd->isChecked())
	{
		EnableEdit(CharDiff_QuickCurr_Index);
	}
	else
	{
		DisableEdit(CharDiff_QuickCurr_Index);
	}
}

void QCharEditRadioNormalWidget::EnableEdit( long nIndex )
{
	switch(nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);

		if(!ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(true);
		}

		m_pDiffCharCal->m_nKneePoints = nIndex;
		break;

	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(true);
		m_pDiffCharCal->m_nSelectSd = 1;
		break;

	default:
		break;
	}

	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::DisableEdit( long nIndex )
{
	switch(nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);

		if(ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(false);
		}
		m_pDiffCharCal->m_nKneePoints = nIndex - 1;
		break;

	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(false);
		m_pDiffCharCal->m_nSelectSd = 0;
		break;

	default:
		break;
	}

	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::SetDiffFont()
{
	m_pGridCharLine->setFont(*g_pSttGlobalFont);
	m_pGridCharLine->horizontalHeader()->setFont(*g_pSttGlobalFont);

	ui.m_edtSet_Istart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleStart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleCurr->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleK->setFont(*g_pSttGlobalFont);
	ui.m_chkLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip1->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K1->setFont(*g_pSttGlobalFont);
	ui.m_chkStart->setFont(*g_pSttGlobalFont);
	ui.m_chkLine2->setFont(*g_pSttGlobalFont);
	ui.m_chkLineSd->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine2->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLineSd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip2->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Isd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Kstart->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K2->setFont(*g_pSttGlobalFont);
	ui.m_btnUserClear->setFont(*g_pSttGlobalFont);
	ui.m_btnUserAdd->setFont(*g_pSttGlobalFont);
	ui.m_lbIdValue->setFont(*g_pSttGlobalFont);
	ui.m_editSet_IdValue->setFont(*g_pSttGlobalFont);

	ui.m_lbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_cbSettingMinAxis->setFont(*g_pSttGlobalFont);
	
	ui.m_lbInSet->setFont(*g_pSttGlobalFont);
	ui.m_editInSet->setFont(*g_pSttGlobalFont);

	ui.m_lbName->setFont(*g_pSttGlobalFont);
	ui.m_lbSetting->setFont(*g_pSttGlobalFont);

	ui.m_lbTranSort->setFont(*g_pSttGlobalFont);
	ui.m_cmb_TranSort->setFont(*g_pSttGlobalFont);
	ui.m_lblSet_K->setFont(*g_pSttGlobalFont);
}

void QCharEditRadioNormalWidget::slot_CmbSettingMinAxisIndexChanged( int nIndex )
{
	m_pDiffCharCal->m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();
	UpdateEditsDisEnable();//更新控件使能状态
	InitUI_Unit();
	emit sig_ChangeICMAxisName();
	emit sig_ChangeSettingMinAxisIndex(nIndex);
}


void QCharEditRadioNormalWidget::UpdateEditsDisEnable()
{
	switch(m_pDiffCharCal->m_nKneePoints)
	{
	case 3:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		break;
	case 2:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		break;
	case 1:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		break;
	default:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		break;
	}

	if (m_pDiffCharCal->m_nMinAxis == 0)//有名值
	{
		ui.m_editInSet->setEnabled(false);
	}
	else
	{
		ui.m_editInSet->setEnabled(true);
	}
}

void QCharEditRadioNormalWidget::InitUI_Unit()
{
	
	CString strText,strText_IrAxis,strText_IdAxis,strCustomText,strText_cbInsel,strText_AxisTitle;
	//UpdateTransSortPicture()
	if (m_pDiffCharCal->m_nMinAxis)
	{
		strText = /*_T("电流(Ie)")*/g_sLangTxt_State_Iecurrent;
		strCustomText = /*_T("制动电流(Ie)")*/g_sLangTxt_Native_Iecurrent;
		strText_cbInsel = /*_T("基准电流(Ie)")*/g_sLangTxt_Gradient_IRCurrent; //lcq
	} 
	else
	{
		strText = /*_T("电流(A )")*/g_sLangTxt_State_Acurrent;
		strCustomText = /*_T("制动电流(A )")*/g_sLangTxt_Native_Acurrent;
		strText_cbInsel = /*_T("基准电流(A)")*/g_sLangTxt_Gradient_ARCurrent; //lcq
		ui.m_editInSet->setEnabled(false);
	}
	ui.m_lblTitleCurr->setText(strText);
	ui.m_lbIdValue->setText(strCustomText);
	ui.m_lbInSet->setText(strText_cbInsel);
	ui.m_cmb_TranSort->setCurrentIndex(m_nTranSort);

}


void QCharEditRadioNormalWidget::InitChar()
{
	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	if(pChar==NULL)
	{
		return;
	}
	CCharacterArea* pArea = pChar->GetCharacterArea();
	//设置门槛值
	CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
	m_pDiffCharCal->m_fIcdqd = CString_To_double(pLine->m_strYb);
	m_pDiffCharCal->m_fKid0 = 0/*CalLineK(pLine)*/;

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
		ui.m_chkLine2->setChecked(true);
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
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

	InitDiffData();
}

void QCharEditRadioNormalWidget::InitDiffData()
{
	disconnect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	disconnect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));

	ui.m_cbSettingMinAxis->SetSelByIndex(m_pDiffCharCal->m_nMinAxis);
	ui.m_cmb_TranSort->SetSelByIndex(m_nTranSort);
	
	CString strText;

	strText.Format("%.3f", m_pDiffCharCal->m_fInSet);
	ui.m_editInSet->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fIcdqd);
	ui.m_edtSet_Istart->setText(strText);
	strText.Format("%.3f", m_pDiffCharCal->m_fIsd);
	ui.m_edtSet_Isd->setText(strText);	

	strText.Format("%.3f", m_pDiffCharCal->m_fIp2);
	ui.m_edtSet_Ip2->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fKid0);
	ui.m_edtSet_Kstart->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fKid1);
	ui.m_edtSet_K1->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fKid2);
	ui.m_edtSet_K2->setText(strText);

	strText.Format("%.3f", m_pDiffCharCal->m_fIp1);
	ui.m_edtSet_Ip1->setText(strText);
	
	emit sig_ChangeCTPoint(m_bAmbo);

	InitUI_Unit();
	UpdateTransSortPicture(m_nTranSort);

	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cmb_TranSort,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TranSortIndexChanged(int)));
	
}

float QCharEditRadioNormalWidget::CalLineK( CCharElementLined* pLine )
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditRadioNormalWidget::slot_btnUserAdd( bool bState )
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
	if(!pPoint)
	{
		return;
	}

	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
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
		double dXb = 0, dYb = 0, dXe = 0, dYe = 0;
		pCharLine->GetLine(dXb, dYb, dXe, dYe);
		if(dXb < pPoint->m_fX && pPoint->m_fX < dXe)
		{
			break;
		}
		nIndex++;
	}

	CCharTestLine* pTestLine = new CCharTestLine();
	pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
	pTestLine->m_nTestLineID = char_GetTestLineID(pCharLine, nIndex);
	pTestLine->m_fPos = pPoint->m_fX;
	pTestLine->m_fXset = pPoint->m_fX;
	pTestLine->m_fYset = pPoint->m_fY;
	pTestLine->m_fXb = pPoint->m_fX;
	pTestLine->m_fXe = pPoint->m_fX;
	pTestLine->m_fYb = pPoint->m_fY + pCharLine->GetErrorLength();
	pTestLine->m_fYe = pPoint->m_fY - pCharLine->GetErrorLength();
	pCharLine->AddNewChild(pTestLine);
	pCharLine->SetUserTestPoint(pCharLine->GetUserTestPoints() + 1);

	emit sig_UpdateChar(TRUE,FALSE,TRUE);

}

void QCharEditRadioNormalWidget::slot_btnUserClear( bool bState )
{
	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);

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


void QCharEditRadioNormalWidget::on_m_edtSet_Istart_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Istart, m_pDiffCharCal->m_fIcdqd);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
	emit sig_ChangeIstart(fv);
}

void QCharEditRadioNormalWidget::slot_InSet_editingFinished()
{
	SetParaI(ui.m_editInSet, m_pDiffCharCal->m_fInSet);
	emit sig_MainWidgetCharChange();
	emit sig_ChangeInset(m_pDiffCharCal->m_fInSet);
	
}

float QCharEditRadioNormalWidget::SetParaI( QLineEdit* pEdit, float& fv )
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

float QCharEditRadioNormalWidget::SetLimit( float min,float max,float val )
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

void QCharEditRadioNormalWidget::on_m_edtSet_Ip1_editingFinished()
{
	SetParaI(ui.m_edtSet_Ip1, m_pDiffCharCal->m_fIp1);

	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::on_m_edtSet_K1_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_K1, m_pDiffCharCal->m_fKid1);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::on_m_edtSet_Ip2_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Ip2, m_pDiffCharCal->m_fIp2);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::on_m_edtSet_K2_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_K2, m_pDiffCharCal->m_fKid2);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::on_m_edtSet_Isd_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Isd, m_pDiffCharCal->m_fIsd);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
	emit sig_ChangeIsd(fv);
}

float QCharEditRadioNormalWidget::SetParaK( QLineEdit* pEdit, float& fv )
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

void QCharEditRadioNormalWidget::slot_IdValue_editingFinished()
{
	CString strIdValue = ui.m_editSet_IdValue->text();
	emit sig_IdValue_editingFinished(strIdValue);
	
}

void QCharEditRadioNormalWidget::UpdateEdit_IrValueUserPoint()
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();

	if(!pPoint)
	{
		return;
	}

	CString strValue;

	strValue.Format(_T("%.03f"),pPoint->m_fX);

	disconnect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	
	ui.m_editSet_IdValue->setText(strValue);
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));


}

void QCharEditRadioNormalWidget::slot_cmb_TranSortIndexChanged( int index )
{
	m_nTranSort = index;
	emit sig_ChangeTranSortIndex(index);
}

void QCharEditRadioNormalWidget::on_m_onlineEdit_Changed()
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

void QCharEditRadioNormalWidget::slot_TestPointsErrorBandChanged()
{
	emit sig_TestPointsErrorBandChanged();
}

void QCharEditRadioNormalWidget::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditRadioNormalWidget::UpdateTransSortPicture( int index )
{
	CString strName;
	CString strPicPath = _P_GetResourcePath();

	//lable控件显示公式图片；
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

	QPixmap pix(strName);
	pix = pix.scaled(ui.m_label_Func->width(),ui.m_label_Func->height(),Qt::KeepAspectRatio);
	ui.m_label_Func->setPixmap(pix);
	ui.m_label_Func->setAlignment(Qt::AlignCenter);

}

void QCharEditRadioNormalWidget::on_m_edtSet_Kstart_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_Kstart, m_pDiffCharCal->m_fKid0);
	emit sig_UpdateChar(FALSE,FALSE,TRUE);
}

void QCharEditRadioNormalWidget::slot_HarmChangeTransSort( int index )
{
	ui.m_cmb_TranSort->setCurrentIndex(index);
	m_nTranSort = index;
	UpdateTransSortPicture(index);
}

void QCharEditRadioNormalWidget::slot_HarmChangeSettingMinAxis( int index )
{
	ui.m_cbSettingMinAxis->setCurrentIndex(index);
	m_pDiffCharCal->m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();	
	UpdateEditsDisEnable();
	InitUI_Unit();
}

void QCharEditRadioNormalWidget::slot_HarmChangeInSet( float InSet )
{
	QString nIstart=QString::number(InSet,'f',3);
	ui.m_editInSet->setText(nIstart);
	SetParaI(ui.m_editInSet, m_pDiffCharCal->m_fInSet);
}


void QCharEditRadioNormalWidget::slot_HarmChangeCTPoint( bool bAmbo )
{
	if(bAmbo == true)
	{
		m_bAmbo = true;
	}
	else if(bAmbo == false)
	{
		m_bAmbo = false;
	}
	UpdateTransSortPicture(m_nTranSort);
	
}

void QCharEditRadioNormalWidget::InitDataToChar( long nRateCoef2Check )
{
	ui.m_chkLine2->setChecked(nRateCoef2Check);
	ui.m_chkLineSd->setChecked(m_pDiffCharCal->m_nSelectSd);

	InitDiffData();
	UpdateEditsDisEnable();
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditRadioNormalWidget::slot_HarmChangeIstart( float Istart )
{
	QString nIstart=QString::number(Istart,'f',3);
	ui.m_edtSet_Istart->setText(nIstart);
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditRadioNormalWidget::slot_HarmChangeIsd( float Isd )
{
	QString nIsd=QString::number(Isd,'f',3);
	ui.m_edtSet_Isd->setText(nIsd);
	emit sig_UpdateChar(TRUE,FALSE,FALSE);
}


void QCharEditRadioNormalWidget::SetCDiffCharCal( CDiffCharCal *pDiffCharCal )
{
	if(pDiffCharCal == NULL)
	{
		return;
	}
	m_pDiffCharCal = pDiffCharCal;


}

void QCharEditRadioNormalWidget::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridCharLine->GetCurrSelData();

	if (pCurrSelElement == NULL)
	{
		return;
	}

	emit sig_ActiveSegment(pCurrSelElement);
}


