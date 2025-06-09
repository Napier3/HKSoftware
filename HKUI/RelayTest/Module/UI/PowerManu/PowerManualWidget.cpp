#include "stdafx.h"
#include "PowerManualWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewPowerManu.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"

QPowerManualWidget::QPowerManualWidget(QWidget *pParent): QWidget(pParent)
{
    m_pStepValue_LineEdit = NULL;
    m_pStartValue_LineEdit = NULL;
	m_pEndValue_LineEdit = NULL;
    m_pStepTime_LineEdit = NULL;
    m_pChSelect_ComboBox = NULL;
    //m_pChGradientType_ComboBox = NULL;
    m_pChangedType_ComboBox = NULL;
    m_pBout_CheckBox[0] = NULL;
    m_pBout_CheckBox[1] = NULL;
    m_pBout_CheckBox[2] = NULL;
    m_pBout_CheckBox[3] = NULL;

    m_pAuto_CheckBox = NULL;
	m_nChanneType = 0;
	m_nUnitType = 0;

	m_pFirstRowWidget = NULL;
	m_pFirstRowLayout = NULL;
	m_pSecondRowWidget = NULL;
	m_pSecondRowLayout = NULL;
	m_pThirdRowWidget = NULL;
	m_pThirdRowLayout = NULL;
}

QPowerManualWidget::~QPowerManualWidget()
{

}

void QPowerManualWidget::InitUI()
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pPowerManuTab = new QSttTabWidget(this);
	m_pMainGridLayout->addWidget(m_pPowerManuTab, 0, 0, 1, 10);

	m_pVolCurr_Widget = new QWidget();
	m_pVolCurr_Widget->setObjectName(QString::fromUtf8("m_layoutIV"));
	CString strText;
	m_pPowerManuTab->addTab(m_pVolCurr_Widget,g_sLangTxt_sequence);

	//strText = _T("通道选择:");
	m_pChSelect_Label = new QLabel(/*_T("变量选择:")*/(g_sLangTxt_Impedance_VarChoose+ ":"),this);
	m_pChSelect_ComboBox = new QScrollComboBox(this);
	//strText = _T("步长时间:");
	m_pStepTime_Label = new QLabel(g_sLangTxt_steplength,this);
	m_pStepTime_LineEdit = new QSettingLineEdit(this);
	//strText = _T("自动");
	m_pAuto_CheckBox = new QSttCheckBox(g_sLangTxt_Manual_Auto,this);

	//strText = _T("始值(VA):");
	m_pStartValue_Label = new QLabel(/*_T("始值(VA):")*/(g_sLangTxt_State_BeginVal + "(VA):"),this);
	m_pStartValue_LineEdit = new QSettingLineEdit(this);

	//strText = _T("终值(VA):");
	m_pEndValue_Label = new QLabel(/*_T("终值(VA):")*/(g_sLangTxt_State_EndVal + "(VA):"),this);
	m_pEndValue_LineEdit = new QSettingLineEdit(this);

	//strText = _T("变化步长(VA):");
	m_pStepValue_Label = new QLabel(/*_T("变化步长(VA):")*/g_sLangTxt_Gradient_Step + "(VA):"  ,this);
	m_pStepValue_LineEdit = new QSettingLineEdit(this);

	//strText = _T("变化方式:");
	m_pChangedType_Label = new QLabel(g_sLangTxt_Manual_ChangeType,this);
	m_pChangedType_ComboBox = new QScrollComboBox(this);

	//strText = _T("开出量");
	m_pBoutGroupBox = new QGroupBox(g_sLangTxt_Native_Bout,this);
	//2023/10/9 - wjs 开出量宽度改小，使其他按钮内容可以显示全
	//m_pBoutGroupBox->setFixedWidth(110);
	//2023/10/9 - wjs 设置为可动态调整
	QSizePolicy sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Preferred);
	m_pStartValue_Label->setSizePolicy(sizePolicy);
	m_pStartValue_LineEdit->setSizePolicy(sizePolicy);
	m_pEndValue_Label->setSizePolicy(sizePolicy);
	m_pEndValue_LineEdit->setSizePolicy(sizePolicy);
	m_pStepValue_Label->setSizePolicy(sizePolicy);
	m_pStepValue_LineEdit->setSizePolicy(sizePolicy);
	m_pChangedType_Label->setSizePolicy(sizePolicy);
	m_pChangedType_ComboBox->setSizePolicy(sizePolicy);
	m_pBoutGroupBox->setSizePolicy(sizePolicy);

	m_pBout_GridLayout = new QGridLayout(m_pBoutGroupBox);
	strText = _T("1");
	m_pBout_CheckBox[0] = new QSttCheckBox(strText,m_pBoutGroupBox);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[0], 0, 0, 1, 1);

	strText = _T("2");
	m_pBout_CheckBox[1] = new QSttCheckBox(strText,m_pBoutGroupBox);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[1], 0, 1, 1, 1);

	strText = _T("3");
	m_pBout_CheckBox[2] = new QSttCheckBox(strText,m_pBoutGroupBox);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[2], 1, 0, 1, 1);

	strText = _T("4");
	m_pBout_CheckBox[3] = new QSttCheckBox(strText,m_pBoutGroupBox);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[3], 1, 1, 1, 1);

	//strText = _T("频率(Hz):");
	//m_pFreq_Label = new QLabel(g_sLangTxt_Frequency + ":",this);
	//m_pFreq_LineEdit = new QSttLineEdit(this);
	//m_pFreq_LineEdit->setText("50.0");
	//m_pFreq_LineEdit->setFixedWidth(100); //20240508 xueyangfan 频率缩短

	//strText = _T("锁");
	m_pLock_PushButton = new QPushButton(g_sLangTxt_Manual_Lock,this);
	m_pLock_PushButton->setFixedWidth(150);

	strText = _T("+");
	m_pAdd_PushButton = new QPushButton(strText,this);
	m_pAdd_PushButton->setFixedWidth(150);

	strText = _T("-");
	m_pMinus_PushButton = new QPushButton(strText,this);
	m_pMinus_PushButton->setFixedWidth(150);

	//strText = _T("开关量设置");
	m_pBinarySet_PushButton = new QPushButton(g_sLangTxt_Native_Switch,this);
	m_pBinarySet_PushButton->setFixedWidth(150);

	m_pEstimate_PushButton =new QPushButton(g_sLangTxt_State_Estimate,this);
	m_pEstimate_PushButton->setFixedWidth(150);

	m_pFirstRowWidget = new QWidget(this);
	m_pMainGridLayout->addWidget(m_pFirstRowWidget, 1, 0, 1, 8);
	m_pFirstRowLayout =new QHBoxLayout(m_pFirstRowWidget);
	m_pFirstRowLayout->addWidget(m_pChSelect_Label);
	m_pFirstRowLayout->addWidget(m_pChSelect_ComboBox);
	m_pFirstRowLayout->addSpacing(30);
	m_pFirstRowLayout->addWidget(m_pStepTime_Label);
	m_pFirstRowLayout->addWidget(m_pStepTime_LineEdit);
	//m_pFirstRowLayout->addSpacing(10);
	m_pFirstRowLayout->addWidget(m_pChangedType_Label);
	m_pFirstRowLayout->addWidget(m_pChangedType_ComboBox);
	m_pFirstRowLayout->addWidget(m_pAuto_CheckBox);
   

	m_pChSelect_Label->setFixedWidth(100);
	m_pChSelect_ComboBox->setMinimumWidth(130);
	m_pStepTime_LineEdit->setMaximumWidth(170);
	//m_pFirstRowLayout->setSpacing(15);     //dxy 20240204 将通道选择下拉框加宽

	/*m_pMainGridLayout->addWidget(m_pStartValue_Label, 2, 0, 1, 1);
	m_pMainGridLayout->addWidget(m_pStartValue_LineEdit, 2, 1, 1, 1);
	m_pMainGridLayout->addWidget(m_pEndValue_Label, 2, 2, 1, 1);
	m_pMainGridLayout->addWidget(m_pEndValue_LineEdit, 2, 3, 1, 1);
	m_pMainGridLayout->addWidget(m_pStepValue_Label, 2, 4, 1, 1);
	m_pMainGridLayout->addWidget(m_pStepValue_LineEdit, 2, 5, 1, 1);
	m_pMainGridLayout->addWidget(m_pChangedType_Label, 2, 6, 1, 1);
	m_pMainGridLayout->addWidget(m_pChangedType_ComboBox, 2, 7, 1, 1);*/
	m_pSecondRowWidget = new QWidget(this);
	m_pMainGridLayout->addWidget(m_pSecondRowWidget, 2, 0, 1, 8);
	m_pSecondRowLayout =new QHBoxLayout(m_pSecondRowWidget);
	m_pSecondRowLayout->addWidget(m_pStartValue_Label);
	m_pSecondRowLayout->addWidget(m_pStartValue_LineEdit);
	m_pSecondRowLayout->addWidget(m_pEndValue_Label);
	m_pSecondRowLayout->addWidget(m_pEndValue_LineEdit);
	m_pSecondRowLayout->addWidget(m_pStepValue_Label);
	m_pSecondRowLayout->addWidget(m_pStepValue_LineEdit);
	//m_pSecondRowLayout->addWidget(m_pChangedType_Label);
	//m_pSecondRowLayout->addWidget(m_pChangedType_ComboBox);

	//m_pSecondRowLayout->setAlignment(Qt::AlignLeft);
	//m_pSecondRowWidget->addLayout(m_pSecondRowLayout);

	m_pMainGridLayout->addWidget(m_pBoutGroupBox, 1, 8, 2, 2);

	/*m_pMainGridLayout->addWidget(m_pFreq_Label, 3, 0, 1, 1);
	m_pMainGridLayout->addWidget(m_pFreq_LineEdit, 3, 1, 1, 1);
	m_pMainGridLayout->addWidget(m_pLock_PushButton, 3, 3, 1, 1);
	m_pMainGridLayout->addWidget(m_pAdd_PushButton, 3, 4, 1, 1);
	m_pMainGridLayout->addWidget(m_pMinus_PushButton, 3, 5, 1, 1);
	m_pMainGridLayout->addWidget(m_pBinarySet_PushButton, 3, 6, 1, 2);
	m_pMainGridLayout->addWidget(m_pEstimate_PushButton, 3, 8, 1, 2);*/
	m_pThirdRowWidget = new QWidget(this);
	m_pMainGridLayout->addWidget(m_pThirdRowWidget, 3, 0, 1, 10);
	m_pThirdRowLayout =new QHBoxLayout(m_pThirdRowWidget);
	m_pThirdRowLayout->setAlignment(Qt::AlignRight);
	//m_pThirdRowLayout->addWidget(m_pFreq_Label);
	//m_pThirdRowLayout->addWidget(m_pFreq_LineEdit);
	m_pThirdRowLayout->addWidget(m_pLock_PushButton);
	QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_pThirdRowLayout->addSpacerItem(spacer);
	m_pThirdRowLayout->addWidget(m_pAdd_PushButton);
	spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_pThirdRowLayout->addSpacerItem(spacer);
	m_pThirdRowLayout->addWidget(m_pMinus_PushButton);
	spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_pThirdRowLayout->addSpacerItem(spacer);
	//m_pThirdRowLayout->addSpacing(70);
	m_pThirdRowLayout->addWidget(m_pBinarySet_PushButton);
	m_pThirdRowLayout->addWidget(m_pEstimate_PushButton);


	m_bControlLock = false;
	m_pManualParas = NULL;
	m_nVChNums = m_nIChNums = 0;
	m_pEvent = NULL;

	xlang_GetLangStrByFile(strText, "Manual_S_E");
	m_pChangedType_ComboBox->addItem(strText);
	xlang_GetLangStrByFile(strText, "Manual_S_E_S");
	m_pChangedType_ComboBox->addItem(strText);

	m_pAdd_PushButton->setDisabled(true);
	m_pMinus_PushButton->setDisabled(true);
	m_pLock_PushButton->setDisabled(true);

#ifdef _PSX_QT_WINDOWS_
	CString strImagePath = _P_GetResourcePath();
	m_imgLock.addFile(strImagePath + "Lock.png");
	m_imgUnlock.addFile(strImagePath + "Unlock.png");
#else
	CString strImagePath ;
	strImagePath = ":/ctrls/images/Lock.png";
	m_imgLock.addFile(strImagePath);
	strImagePath = ":/ctrls/images/Unlock.png";
	m_imgUnlock.addFile(strImagePath);
#endif
	m_pLock_PushButton->setIcon(m_imgUnlock);
	m_pLock_PushButton->setIconSize(QSize(m_pAdd_PushButton->height(), m_pAdd_PushButton->height()));
	//2023/10/9 wjs 取消对按钮“锁”的固定
	//m_pLock_PushButton->setFixedWidth(m_pAdd_PushButton->width());
	m_pLock_PushButton->setText("");
}

void QPowerManualWidget::InitConnect()
{
	connect(m_pPowerManuTab, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
}

void QPowerManualWidget::SetData(CSttTestResourceBase *pSttTestResource,tmt_PowerManuParas* pManualParas,CEventResult* pEvent)
{
	m_pTestResource = pSttTestResource;
	m_pManualParas = pManualParas;
	m_pEvent = pEvent;

	UpdateData();
}

void QPowerManualWidget::SetUnitType (int index)
{
	QString strText;
	switch(index)
	{
	case 0: 
		strText = "VA"; 
		break;
	case 1:	
		strText = "W"; 
		break;
	case 2:	
		strText = "Var"; 
		break;
	default:
		break;
	}

    CString strTemp; 
	//xlang_GetLangStrByFile(strTemp, "Manual_Step");
	strTemp = /*_T("变化步长(VA):")*/g_sLangTxt_Gradient_Step + "(VA):";
	m_pStepValue_Label->setText(strTemp.mid(0, m_pStepValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
	//xlang_GetLangStrByFile(strTemp, "Manual_InitVal");
    strTemp = /*_T("始值(VA):")*/g_sLangTxt_State_BeginVal + "(VA):";
	m_pStartValue_Label->setText(strTemp.mid(0, m_pStartValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
	//xlang_GetLangStrByFile(strTemp, "Manual_FinishVal");
    strTemp = /*_T("终值(VA):")*/g_sLangTxt_State_EndVal + "(VA):";
	m_pEndValue_Label->setText(strTemp.mid(0, m_pEndValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
};

void QPowerManualWidget::UpdateData()
{
	if(m_pManualParas == NULL || m_pTestResource == NULL)
	{
		return;
	}

	m_nVChNums = m_pTestResource->m_oVolChRsListRef.GetCount();
	m_nIChNums = m_pTestResource->m_oCurChRsListRef.GetCount();

	bool bAuto = m_pManualParas->m_bAuto;
	m_pStartValue_LineEdit->setDisabled(!bAuto);
	m_pEndValue_LineEdit->setDisabled(!bAuto);
	m_pStepTime_LineEdit->setDisabled(!bAuto);

	g_theTestCntrFrame->SetVectorGradient(m_pManualParas->m_bAuto);

	//递变参数
	InitGradientData();
	slot_lne_startChanged();
	slot_lne_endChanged();
	slot_lne_stepChanged();
	//slot_Freq_LineEdit_Changed();

	m_pAdd_PushButton->setDisabled(bAuto);
	m_pMinus_PushButton->setDisabled(bAuto);

	GlobalSetQcheckState_BinaryOut(m_pBout_CheckBox[0],m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pBout_CheckBox[1],m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pBout_CheckBox[2],m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pBout_CheckBox[3],m_pManualParas->m_binOut,3);

	//开入量设置
	Global_CheckBinSelect(m_pManualParas->m_binIn,g_nBinCount, m_pManualParas->m_nBinLogic);

	//老化、直流、自动
	m_pAuto_CheckBox->setChecked(m_pManualParas->m_bAuto);
}

void QPowerManualWidget::InitGradientData()
{
	/*if (m_pManualParas->m_nGradientTpSelect == phasor_type)功率只有幅值
	{
		m_pStartValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fStart,'f',1));
		m_pEndValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fEnd,'f',1));
		m_pStepValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fStep,'f',1));
	}
	else
	{*/
		//20240801 gongyiping 
		//m_pStartValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fStart,'f',3));  //有效位数改为三位 20210912 sf
		((QSettingLineEdit*)m_pStartValue_LineEdit)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_oPowerGradient.fStart), 3);
		//m_pEndValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fEnd,'f',3));
		((QSettingLineEdit*)m_pEndValue_LineEdit)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_oPowerGradient.fEnd), 3);
		//m_pStepValue_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fStep,'f',3));
		((QSettingLineEdit*)m_pStepValue_LineEdit)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_oPowerGradient.fStep), 3);
	//}

	//20240801 gongyiping 
	m_pStepTime_LineEdit->setText(QString::number(m_pManualParas->m_oPowerGradient.fStepTime,'f',3));
	((QSettingLineEdit*)m_pStepTime_LineEdit)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_oPowerGradient.fStepTime), 3);

	m_pChangedType_ComboBox->setCurrentIndex(m_pManualParas->m_oPowerGradient.nMode);

	Sequence_type var = getParaTypeByIndex(m_pManualParas->m_nGradientChSelect);
	InitGradientVarList();
	InitGradientVar(var);

	/*switch (m_pManualParas->m_nGradientTpSelect)
	{
	case amplitude_type:
		m_pChGradientType_ComboBox->setCurrentIndex(0);
		break;
	case phasor_type:
		m_pChGradientType_ComboBox->setCurrentIndex(1);
		break;
	case fre_type:
		m_pChGradientType_ComboBox->setCurrentIndex(2);
		break;
	default:
		break;
	}*/
}

void QPowerManualWidget::InitGradientVarList()
{
	m_pChSelect_ComboBox->clear();

	if (m_pTestResource == NULL)
	{
		return;
	}

	m_pTestResource->AddGradientPower(m_oGradientChs);

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oGradientChs.GetNext(pos);
		m_pChSelect_ComboBox->addItem(pCurTypeValue->m_strID.GetString());
	}
}

void QPowerManualWidget::InitGradientVar(Sequence_type vartype)
{
	CDataTypeValue *pCurSelData = m_oGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_selectchannel.GetString(),vartype);
		return;
	}
	else
	{
		long nIndex = m_oGradientChs.FindIndex(pCurSelData);
		ASSERT(nIndex>=0);
		m_pChSelect_ComboBox->setCurrentIndex(nIndex);
	}
}

float QPowerManualWidget::slot_lne_Changed(QLineEdit* pLineEdit)
{
	//20240801 gongyiping 
	if (pLineEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)pLineEdit)->IsSetting())
		{
			float fv = ((QSettingLineEdit*)pLineEdit)->GetValue().toFloat();
			return fv;
		}
	}

	float fv = pLineEdit->text().toFloat();
    fv = setLimit(0,660000000.000,fv); //最大限值
//	QString strvar = m_pChSelect_ComboBox->currentText();
//	//int index = m_pChGradientType_ComboBox->currentIndex();
//	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
//	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
//	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
//	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;

//			if (strvar.contains("U"))
//			{
//				if (fv>fAcVMax)
//				{
//					fv = fAcVMax;
//				}

//				if (fv<0)
//				{
//					fv = 0;
//				}
//			}
//			else if (strvar.contains("I"))
//			{
//				if (fv>fAcIMax)
//				{
//					fv = fAcIMax;
//				}

//				if (fv<0)
//				{
//					fv = 0;
//				}
//			}
		pLineEdit->setText(QString::number(fv,'f',3));
	

	return fv;
}

void QPowerManualWidget::slot_lne_startChanged()
{
	m_pManualParas->m_oPowerGradient.fStart = slot_lne_Changed(m_pStartValue_LineEdit);

	if(m_pChSelect_ComboBox->currentText().contains("U"))
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualParas->m_oPowerGradient.fStart,
			m_pManualParas->m_oPowerGradient.fEnd, 0, 0);
	}
	else
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualParas->m_oPowerGradient.fStart,
			m_pManualParas->m_oPowerGradient.fEnd);
	}
}

void QPowerManualWidget::slot_lne_endChanged()
{
	m_pManualParas->m_oPowerGradient.fEnd = slot_lne_Changed(m_pEndValue_LineEdit);

	if(m_pChSelect_ComboBox->currentText().contains("U"))
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualParas->m_oPowerGradient.fStart,
			m_pManualParas->m_oPowerGradient.fEnd, 0, 0);
	}
	else
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualParas->m_oPowerGradient.fStart,
			m_pManualParas->m_oPowerGradient.fEnd);
	}
}

//void QPowerManualWidget::slot_Freq_LineEdit_Changed()
//{
//	//float fv = m_pFreq_LineEdit->text().toFloat();
//
//	if (qAbs(fv)<=EPSINON)
//	{
//		fv = 0.001;
//	}
//
//	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
//	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
//	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
//	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;
//
//	fv = setLimit(0.001,Global_GetMaxFreq(),fv);
//
//	if (fv < 0.001)
//	{
//		fv = 0.001;
//	}
//
//	m_pManualParas->m_fFreq = fv;
//	//m_pFreq_LineEdit->setText(QString::number(fv,'f',3));
//}

void QPowerManualWidget::slot_lne_stepChanged()
{
	float fv = m_pStepValue_LineEdit->text().toFloat();
    float fMinValue = 0;
    float fMaxValue = 660000000;
	if (qAbs(fv)<=EPSINON)
	{
        fMinValue = 0.001;
	}

    fv = setLimit(fMinValue,fMaxValue,fv); //最大限值


//	QString strvar = m_pChSelect_ComboBox->currentText();
//	//int index = m_pChGradientType_ComboBox->currentIndex();
//	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
//	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
//	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
//	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;


//			if (strvar.contains("U"))
//			{
//				if (fv>fAcVMax)
//				{
//					fv = fAcVMax;
//				}

//				if (fv<0)
//				{
//					fv = 0.001;
//				}
//			}
//			else if (strvar.contains("I"))
//			{
//				if (fv>fAcIMax)
//				{
//					fv = fAcIMax;
//				}

//				if (fv<0)
//				{
//					fv = 0.001;
//				}
//			}


	m_pManualParas->m_oPowerGradient.fStep = fv;
	m_pStepValue_LineEdit->setText(QString::number(fv,'f',3));
}

void QPowerManualWidget::slot_lne_steptimeChanged()
{
	//20240801 gongyiping 
	if (m_pStepTime_LineEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pStepTime_LineEdit)->IsSetting())
		{
			return;
		}
	}


	float fv = m_pStepTime_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_pManualParas->m_oPowerGradient.fStepTime != fv)
	{
		m_pManualParas->m_oPowerGradient.fStepTime = fv;
	}

	m_pStepTime_LineEdit->setText(QString::number(fv,'f',3));
}


void QPowerManualWidget::slot_btn_LockClicked()
{
	if (m_pManualParas->m_bLockChanged)
	{
		m_bControlLock = true;
		m_pManualParas->m_bLockChanged = false;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
		m_pLock_PushButton->setIcon(m_imgUnlock);
	}
	else
	{
		m_bControlLock = false;
		m_pManualParas->m_bLockChanged = true;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		m_pLock_PushButton->setIcon(m_imgLock);
	}

	m_pManualParas->m_bBinStop = TRUE;
}

void QPowerManualWidget::ChannelTableItemValue_AllFreq(float fstep,int AddOrMinus,bool bDC)
{
	if (m_pTestResource != NULL)
	{
		CString strChID;
		CExBaseObject *pChObj = NULL;

		for (int nChIndex = 0;nChIndex<6;nChIndex++ )
		{
			strChID.Format(_T("U%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oVolChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(pChObj->m_strName,fstep,fre_type,AddOrMinus,bDC);
			}

			strChID.Format(_T("I%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oCurChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(pChObj->m_strName,fstep,fre_type,AddOrMinus,bDC);
			}
		}
	}
}

void QPowerManualWidget::slot_btn_AddClicked()
{
	QString str = m_pChSelect_ComboBox->currentText();
	float fstep = m_pManualParas->m_oPowerGradient.fStep;

	if (str.length()<=3)
	{
		emit sig_ChannelTableItemValue(str,fstep,amplitude_type,1,false);
	}
	else
	{
		QStringList chanelist;
		QRegExp rx("\\(([^()]+)\\)");  
		int pos = 0;  
		while ((pos = rx.indexIn(str, pos)) != -1) 
		{  
			// 提取括号内的字符串  
			QString captured = rx.cap(1);  
			// 按逗号分割括号内的字符串  
			QStringList innerList = captured.split(",");  
			// 添加到结果列表中  
			chanelist.append(innerList);  
			// 移动位置以继续搜索  
			pos += rx.matchedLength();  
		}  
		
		if (chanelist.size() ==0 )//如果没有括号且list长度为空，就再次分割逗号寻找一次
		{
			chanelist = str.split(",");
		}
		for (int i=0;i<chanelist.size();i++)
		{
			QString ch = chanelist.at(i);
			emit sig_ChannelTableItemValue(ch,fstep,amplitude_type,1,false);
		}
	}
}

void QPowerManualWidget::slot_btn_MinusClicked()
{
	QString str = m_pChSelect_ComboBox->currentText();
	float fstep = m_pManualParas->m_oPowerGradient.fStep;

	if (str.length()<=3)
	{
		emit sig_ChannelTableItemValue(str,fstep,amplitude_type,-1,false);
	}
	else
	{
		QStringList chanelist;
		QRegExp rx("\\(([^()]+)\\)");  
		int pos = 0;  
		while ((pos = rx.indexIn(str, pos)) != -1) 
		{  
			// 提取括号内的字符串  
			QString captured = rx.cap(1);  
			// 按逗号分割括号内的字符串  
			QStringList innerList = captured.split(",");  
			// 添加到结果列表中  
			chanelist.append(innerList);  
			// 移动位置以继续搜索  
			pos += rx.matchedLength();  
		}  

		if (chanelist.size() ==0 )//如果没有括号且list长度为空，就再次分割逗号寻找一次
		{
			chanelist = str.split(",");
		}
		for (int i=0;i<chanelist.size();i++)
		{
			QString ch = chanelist.at(i);
			emit sig_ChannelTableItemValue(ch,fstep,amplitude_type,-1,false);
		}
	}
}

void QPowerManualWidget::slot_cb_AutoClicked()
{
	bool bIsChecked = false;
	if (m_pAuto_CheckBox->isChecked())
	{
		m_bControlLock = false;
		bIsChecked = true;
		m_pAdd_PushButton->setDisabled(true);
		m_pMinus_PushButton->setDisabled(true);	}
	else
	{
		m_bControlLock = false;
		bIsChecked = false;	
		m_pAdd_PushButton->setDisabled(false);
		m_pMinus_PushButton->setDisabled(false);	}

	if(m_pManualParas->m_bAuto != bIsChecked)
	{
		m_pManualParas->m_bAuto = bIsChecked;
	}

	m_pStartValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pEndValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pStepTime_LineEdit->setDisabled(!m_pManualParas->m_bAuto);

	g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualParas->m_bAuto);
}

void QPowerManualWidget::slot_cbb_SelectChanged(int index)
{
//	m_pManualParas->m_nGradientTpSelect = index;
	SetUnitType(index);
	UpdateData();
}

void QPowerManualWidget::slot_cbb_ChannelChanged(int index)
{
	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(index);

	if(!pCurDataTypeValue)
	{
		return;
	}

	m_pManualParas->m_nGradientChSelect = pCurDataTypeValue->GetIndex();

	if(m_pChSelect_ComboBox->currentText().indexOf("S") != -1)
	{
		m_nChanneType = 0;
	}
	else if (m_pChSelect_ComboBox->currentText().indexOf("P") != -1)
	{
		m_nChanneType = 1;
	} 
	else
	{
		m_nChanneType = 2;
	}


	SetUnitType(m_nChanneType);
};

void QPowerManualWidget::slot_cbb_ChangeTypeChanged(int index)
{
	m_pManualParas->m_oPowerGradient.nMode = index;
}

void QPowerManualWidget::slot_ck_Out1StateChanged()
{
	if (m_pBout_CheckBox[0]->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[0].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[0].nState = 0;
	}
}

void QPowerManualWidget::slot_ck_Out2StateChanged()
{
	if (m_pBout_CheckBox[1]->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[1].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[1].nState = 0;
	}
}

void QPowerManualWidget::slot_ck_Out3StateChanged()
{
	if (m_pBout_CheckBox[2]->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[2].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[2].nState = 0;
	}
}

void QPowerManualWidget::slot_ck_Out4StateChanged()
{
	if (m_pBout_CheckBox[3]->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[3].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[3].nState = 0;
	}
}

void QPowerManualWidget::StartInit()
{
	m_bControlLock = false;
	m_pManualParas->m_bLockChanged = m_bControlLock;

	bool bAuto = m_pManualParas->m_bAuto;

	m_pAdd_PushButton->setDisabled(bAuto);
	m_pMinus_PushButton->setDisabled(bAuto);
	m_pLock_PushButton->setDisabled(bAuto);

	m_pChangedType_ComboBox->setDisabled(bAuto);
	m_pChSelect_ComboBox->setDisabled(bAuto);
//	m_pChGradientType_ComboBox->setDisabled(bAuto);
	m_pStepValue_LineEdit->setDisabled(bAuto);
	//m_pFreq_LineEdit->setDisabled(bAuto);
	m_pBoutGroupBox->setDisabled(bAuto);
	m_pBinarySet_PushButton->setDisabled(bAuto);
	m_pEstimate_PushButton->setDisabled(bAuto);

	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[0],0,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[1],1,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[2],2,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[3],3,g_nBoutCount,!bAuto);

	m_pStepTime_LineEdit->setDisabled(true);
	m_pStartValue_LineEdit->setDisabled(true);
	m_pEndValue_LineEdit->setDisabled(true);

	m_pAuto_CheckBox->setDisabled(true);
}

void QPowerManualWidget::StopInit()
{
	m_bControlLock = true;
	m_pManualParas->m_bLockChanged = false;
	m_pLock_PushButton->setIcon(m_imgUnlock);
	m_pLock_PushButton->setDisabled(true);

	m_pAdd_PushButton->setDisabled(m_pManualParas->m_bAuto);
	m_pMinus_PushButton->setDisabled(m_pManualParas->m_bAuto);

	m_pChSelect_ComboBox->setDisabled(false);
//	m_pChGradientType_ComboBox->setDisabled(false);
	m_pChangedType_ComboBox->setDisabled(false);
	m_pStepValue_LineEdit->setDisabled(false);
	//m_pFreq_LineEdit->setDisabled(false);

	m_pStepTime_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pStartValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pEndValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);

	m_pAuto_CheckBox->setDisabled(false);

	m_pManualParas->m_bLockChanged = false;		
	m_pBoutGroupBox->setDisabled(false);
	m_pBinarySet_PushButton->setDisabled(false);
	m_pEstimate_PushButton->setDisabled(false);

	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[0],0,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[1],1,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[2],2,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[3],3,g_nBoutCount,true);
}

void QPowerManualWidget::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (g_pPowerManuTest == NULL)
	{
		return;
	}

	BOOL bVisibleBottomCtrlsGoose = (g_pPowerManuTest->m_pGooseParaWidget == m_pPowerManuTab->currentWidget());
	BOOL bVisibleBottomCtrlsFT3 = (g_pPowerManuTest->m_pFT3OutParaWidget == m_pPowerManuTab->currentWidget());
	BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);

//	m_frmOtherPara->setVisible(bVisibleBottomCtrls);
	m_pBoutGroupBox->setVisible(bVisibleBottomCtrls);
	m_pLock_PushButton->setVisible(bVisibleBottomCtrls);
	m_pAdd_PushButton->setVisible(bVisibleBottomCtrls);
	m_pMinus_PushButton->setVisible(bVisibleBottomCtrls);
	m_pBinarySet_PushButton->setVisible(bVisibleBottomCtrls);
	m_pEstimate_PushButton->setVisible(bVisibleBottomCtrls);

    m_pChSelect_Label->setVisible(bVisibleBottomCtrls);
    m_pChSelect_ComboBox->setVisible(bVisibleBottomCtrls);
    m_pStepTime_Label->setVisible(bVisibleBottomCtrls);
    m_pStepTime_LineEdit->setVisible(bVisibleBottomCtrls);
    m_pAuto_CheckBox->setVisible(bVisibleBottomCtrls);
    m_pStartValue_Label->setVisible(bVisibleBottomCtrls);
    m_pStartValue_LineEdit->setVisible(bVisibleBottomCtrls);
    m_pEndValue_Label->setVisible(bVisibleBottomCtrls);
    m_pEndValue_LineEdit->setVisible(bVisibleBottomCtrls);
    m_pStepValue_Label->setVisible(bVisibleBottomCtrls);
    m_pStepValue_LineEdit->setVisible(bVisibleBottomCtrls);
    m_pChangedType_Label->setVisible(bVisibleBottomCtrls);
    m_pChangedType_ComboBox->setVisible(bVisibleBottomCtrls);
    m_pFirstRowWidget->setVisible(bVisibleBottomCtrls);
    m_pSecondRowWidget->setVisible(bVisibleBottomCtrls);
    m_pThirdRowWidget->setVisible(bVisibleBottomCtrls);

}
