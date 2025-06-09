#include "HarmParaWidget.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "QHarmTable.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include"../../Module/XLangResource_Native.h"

QHarmParaWidget::QHarmParaWidget(QWidget *parent) : QWidget(parent)
{
	m_pTestResource = NULL;
	m_pHarmParas = NULL;
	m_nDispMode = V_Secondary;
	m_nHarmGradType = Amplitude_HarmGradType;
    InitUI();
	InitConnect();
	SetHarmParaFont();
}

QHarmParaWidget::~QHarmParaWidget()
{

}

bool QHarmParaWidget::IsChannelValid()
{
	long nVarIndex = m_pHarmParas->m_oHarmGradient.nHarmIndex;
	para_type type = va1_type;
	switch(m_pHarmParas->m_nGradientChSelect)
	{
	case 0:
		type = va1_type;
		return m_pHarmParas->m_uiVOL[0].Harm[nVarIndex].m_bSelect;
	case 1:
		type = vb1_type;
		return m_pHarmParas->m_uiVOL[1].Harm[nVarIndex].m_bSelect;
	case 2:
		type = vc1_type;
		return m_pHarmParas->m_uiVOL[2].Harm[nVarIndex].m_bSelect;
	case 4:
		type = vab1_type;
		return m_pHarmParas->m_uiVOL[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[1].Harm[nVarIndex].m_bSelect;
	case 5:
		type = vbc1_type;
		return m_pHarmParas->m_uiVOL[1].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[2].Harm[nVarIndex].m_bSelect;
	case 6:
		type = vca1_type;
		return m_pHarmParas->m_uiVOL[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[2].Harm[nVarIndex].m_bSelect;
	case 7:
		type = vabc1_type;
		return m_pHarmParas->m_uiVOL[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[1].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiVOL[2].Harm[nVarIndex].m_bSelect;
	case 8:
		type = va2_type;
		return m_pHarmParas->m_uiVOL[3].Harm[nVarIndex].m_bSelect;
	case 9:
		type = vb2_type;
		return m_pHarmParas->m_uiVOL[4].Harm[nVarIndex].m_bSelect;
	case 10:
		type = vc2_type;
		return m_pHarmParas->m_uiVOL[5].Harm[nVarIndex].m_bSelect;
	case 11:
		type = vabc2_type;
		return m_pHarmParas->m_uiVOL[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[4].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiVOL[5].Harm[nVarIndex].m_bSelect;
	case 12:
		type = ia1_type;
		return m_pHarmParas->m_uiCUR[0].Harm[nVarIndex].m_bSelect;
	case 13:
		type = ib1_type;
		return m_pHarmParas->m_uiCUR[1].Harm[nVarIndex].m_bSelect;
	case 14:
		type = ic1_type;
		return m_pHarmParas->m_uiCUR[2].Harm[nVarIndex].m_bSelect;
	case 15:
		type = iab1_type;
		return m_pHarmParas->m_uiCUR[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[1].Harm[nVarIndex].m_bSelect;
	case 16:
		type = ibc1_type;
		return m_pHarmParas->m_uiCUR[1].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[2].Harm[nVarIndex].m_bSelect;
	case 17:
		type = ica1_type;
		return m_pHarmParas->m_uiCUR[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[2].Harm[nVarIndex].m_bSelect;
	case 18:
		type = iabc1_type;
		return m_pHarmParas->m_uiCUR[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[1].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiCUR[2].Harm[nVarIndex].m_bSelect;
	case 19:
		type = ia2_type;
		return m_pHarmParas->m_uiCUR[3].Harm[nVarIndex].m_bSelect;
	case 20:
		type = ib2_type;
		return m_pHarmParas->m_uiCUR[4].Harm[nVarIndex].m_bSelect;
	case 21:
		type = ic2_type;
		return m_pHarmParas->m_uiCUR[5].Harm[nVarIndex].m_bSelect;
	case 22:
		type = iabc2_type;
		return m_pHarmParas->m_uiCUR[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[4].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiCUR[5].Harm[nVarIndex].m_bSelect;
	case 23:
		type = vall_type;
		return m_pHarmParas->m_uiVOL[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[1].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiVOL[2].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiVOL[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[4].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiVOL[5].Harm[nVarIndex].m_bSelect;
		break;
	case 24:
		type = iall_type;
		return m_pHarmParas->m_uiCUR[0].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[1].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiCUR[2].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiCUR[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[4].Harm[nVarIndex].m_bSelect
			&& m_pHarmParas->m_uiCUR[5].Harm[nVarIndex].m_bSelect;
		break;
	case 25:
		type = vdc_type;
		break;
	case 26:
		type = vz_type;
		break;
	case 27:
		type = vab2_type;
		return m_pHarmParas->m_uiVOL[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[4].Harm[nVarIndex].m_bSelect;
		break;
	case 28:
		type = vbc2_type;
		return m_pHarmParas->m_uiVOL[4].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[5].Harm[nVarIndex].m_bSelect;
		break;
	case 29:
		type = vca2_type;
		return m_pHarmParas->m_uiVOL[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiVOL[5].Harm[nVarIndex].m_bSelect;
		break;
	case 30:
		type = iab2_type;
		return m_pHarmParas->m_uiCUR[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[4].Harm[nVarIndex].m_bSelect;
		break;
	case 31:
		type = ibc2_type;
		return m_pHarmParas->m_uiCUR[4].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[5].Harm[nVarIndex].m_bSelect;
		break;
	case 32:
		type = ica2_type;
		return m_pHarmParas->m_uiCUR[3].Harm[nVarIndex].m_bSelect 
			&& m_pHarmParas->m_uiCUR[5].Harm[nVarIndex].m_bSelect;
		break;
	case 33:
		type = iabcAdd_type;
		break;
	case 34:
		type = ia2b2c2Add_type;
		break;
	case 35:
		type = vabcAdd_type;
		break;
	case 36:
		type = va2b2c2Add_type;
		break;
	case 37:
		type = freAll_type;
		break;
	case 38:
		type = iaia2Add_type;
		break;
	case 39:
		type = ibib2Add_type;
		break;
	case 40:
		type = icic2Add_type;
		break;
	case 41:
		type = iaia2Add_ibib2Add_icic2Add_type;
		break;
	case 42:
		type = iaia2ibib2icic2Add_type;
		break;
	default:
		break;
	}

	return true;
}

void QHarmParaWidget::SetHarmParaFont()//字体设置
{
	m_pGroupBox_Gradient->setFont(*g_pSttGlobalFont);	
	m_pLabel_ChannelChose->setFont(*g_pSttGlobalFont);
	m_pLabel_Start->setFont(*g_pSttGlobalFont);
	m_pCmb_Chanel->setFont(*g_pSttGlobalFont);
	m_pCmb_HarmNum->setFont(*g_pSttGlobalFont);
	m_pCheck_Auto->setFont(*g_pSttGlobalFont);
    m_pEdit_Start->setFont(*g_pSttGlobalFont);
    m_pLabel_End->setFont(*g_pSttGlobalFont);
    m_pLabel_Step->setFont(*g_pSttGlobalFont);
    m_pEdit_End->setFont(*g_pSttGlobalFont);
    m_pEdit_End->setFont(*g_pSttGlobalFont);
    m_pEdit_Steptime->setFont(*g_pSttGlobalFont);
    m_pLabel_StepTime->setFont(*g_pSttGlobalFont);
    m_pEdit_Step->setFont(*g_pSttGlobalFont);
 	m_pLogicOr->setFont(*g_pSttGlobalFont);//逻辑或
	m_pCheck_Input10->setFont(*g_pSttGlobalFont);
	m_pCheck_Input9->setFont(*g_pSttGlobalFont);
	m_pCheck_Input8->setFont(*g_pSttGlobalFont);
	m_pCheck_Input7->setFont(*g_pSttGlobalFont);
	m_pCheck_Input6->setFont(*g_pSttGlobalFont);
	m_pCheck_Input5->setFont(*g_pSttGlobalFont);
	m_pCheck_Input4->setFont(*g_pSttGlobalFont);
	m_pCheck_Input3->setFont(*g_pSttGlobalFont);
	m_pCheck_Input2->setFont(*g_pSttGlobalFont);
	m_pCheck_Input1->setFont(*g_pSttGlobalFont);
 	m_pGroupBox_PutInSet->setFont(*g_pSttGlobalFont);
 	m_pLogicAnd->setFont(*g_pSttGlobalFont);//逻辑与
	m_pCheck_Output10->setFont(*g_pSttGlobalFont);
	m_pCheck_Output9->setFont(*g_pSttGlobalFont);
    m_pCheck_Output8->setFont(*g_pSttGlobalFont);
    m_pCheck_Output7->setFont(*g_pSttGlobalFont);
    m_pCheck_Output6->setFont(*g_pSttGlobalFont);
    m_pCheck_Output5->setFont(*g_pSttGlobalFont);
    m_pCheck_Output4->setFont(*g_pSttGlobalFont);
    m_pCheck_Output3->setFont(*g_pSttGlobalFont);
    m_pCheck_Output2->setFont(*g_pSttGlobalFont);
    m_pCheck_Output1->setFont(*g_pSttGlobalFont);
    m_pGroupBox_PutOutSet->setFont(*g_pSttGlobalFont);
	m_RadioBtn_Amplitude->setFont(*g_pSttGlobalFont);
	m_RadioBtn_Percent->setFont(*g_pSttGlobalFont);

}

void QHarmParaWidget::InitUI()
{
    m_pVBoxLayout_Main = new QVBoxLayout();
    this->setLayout(m_pVBoxLayout_Main);
    CString strGradient,strOutPutSet,strInPutSet,strTmp;

    xlang_GetLangStrByFile(strGradient,"Manual_Changing");
    xlang_GetLangStrByFile(strOutPutSet,"Manual_OutSetting");
	xlang_GetLangStrByFile(strInPutSet,"Manual_InSetting");

    m_pGroupBox_Gradient = new QSttGroupBox();
//  QFont *font = m_pGroupBox_Gradient->font();
//  font.setPointSize(20);

    m_pGroupBox_Gradient->setTitle(strGradient);

    m_pVLayout_GadientMain = new QVBoxLayout;//垂直布局
    m_pGroupBox_Gradient->setLayout(m_pVLayout_GadientMain);

	m_pGridLayout_Gadient = new QGridLayout;//栅格布局
	m_pVLayout_GadientMain->addLayout(m_pGridLayout_Gadient);

	m_pHLayout_Gadient = new QHBoxLayout;
	m_pVLayout_GadientMain->addLayout(m_pHLayout_Gadient);

    m_pLabel_ChannelChose = new QLabel(tr("通道选择"),this);
    xlang_SetLangStrToWidget(m_pLabel_ChannelChose, "Manual_Channel", XLang_Ctrls_QLabel);
    m_pGridLayout_Gadient->addWidget(m_pLabel_ChannelChose,0,0);

    m_pLabel_Start = new QLabel(tr("始值"),this);
	CString strStart;
	xlang_GetLangStrByFile(strStart,"State_BeginVal");
	strStart += ":";
	m_pLabel_Start->setText(strStart);
    m_pGridLayout_Gadient->addWidget(m_pLabel_Start,1,0);

    m_pCmb_Chanel = new QScrollComboBox();//通道选择框
    m_pGridLayout_Gadient->addWidget(m_pCmb_Chanel,0,1);

    m_pEdit_Start = new QSettingLineEdit(this);//始值编辑框
    m_pGridLayout_Gadient->addWidget(m_pEdit_Start,1,1);

    m_pCmb_HarmNum = new QScrollComboBox();//谐波选择框
    m_pGridLayout_Gadient->addWidget(m_pCmb_HarmNum,0,2,1,2);

    m_pLabel_End = new QLabel(tr("终值"),this);
	CString strEnd;
	xlang_GetLangStrByFile(strEnd,"State_EndVal");
	strEnd += ":";
	m_pLabel_End->setText(strEnd);
    m_pGridLayout_Gadient->addWidget(m_pLabel_End,1,2);
    m_pEdit_End = new QSettingLineEdit(this);
    m_pGridLayout_Gadient->addWidget(m_pEdit_End,1,3);

    m_pLabel_Step = new QLabel(tr("步长"),this);
	CString strStep;
	xlang_GetLangStrByFile(strStep,"sStep");
	strStep += ":";
	m_pLabel_Step->setText(strStep);
    m_pGridLayout_Gadient->addWidget(m_pLabel_Step,0,4);

    m_pEdit_Step = new QSettingLineEdit(this);//步长编辑框
    m_pGridLayout_Gadient->addWidget(m_pEdit_Step,0,5);

    m_pLabel_StepTime = new QLabel(tr("时间"),this);
    xlang_SetLangStrToWidget(m_pLabel_StepTime, "Manual_Timer", XLang_Ctrls_QLabel);
    m_pGridLayout_Gadient->addWidget(m_pLabel_StepTime,1,4);

    m_pEdit_Steptime = new QSettingLineEdit(this);//时间编辑框
    m_pGridLayout_Gadient->addWidget(m_pEdit_Steptime,1,5);

    m_pCheck_Auto = new QSttCheckBox();
	m_pCheck_Auto->setObjectName("m_pCheck_Auto");//自动
// 	m_pCheck_Auto->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Auto, "Manual_Auto", XLang_Ctrls_QCheckBox);
//    m_pGridLayout_Gadient->addWidget(m_pCheck_Auto,0,6);


	//strTmp = "谐波按幅值递变";
//xlang_GetLangStrByFile(g_sLangTxt_State_HarmonicAmpInc,"State_HarmonicAmpInc");//谐波按幅值递变-LCQ
	m_RadioBtn_Amplitude = new QRadioButton(g_sLangTxt_State_HarmonicAmpInc,this);
	//strTmp = "谐波按百分比递变";
//xlang_GetLangStrByFile(g_sLangTxt_State_HarmonicAmpPer,"State_HarmonicAmpPer");//谐波按百分比递变-LCQ
	m_RadioBtn_Percent = new QRadioButton(g_sLangTxt_State_HarmonicAmpPer,this);
// 	m_pHLayout_Gadient->addWidget(m_pCheck_Auto);
//  m_pHLayout_Gadient->addWidget(m_RadioBtn_Amplitude);
//  m_pHLayout_Gadient->addWidget(m_RadioBtn_Percent);

	//2024-7-30 wuxinyi 界面优化
	m_pGridLayout_Gadient->addWidget(m_pCheck_Auto, 2, 0);
	m_pGridLayout_Gadient->addWidget(m_RadioBtn_Amplitude, 2, 2);
	m_pGridLayout_Gadient->addWidget(m_RadioBtn_Percent, 2, 4);

	m_pGridLayout_Gadient->setVerticalSpacing(20);
	m_pGridLayout_Gadient->setHorizontalSpacing(10);


	m_pGroupBox_PutInSet = new QSttGroupBox();
	m_pGroupBox_PutInSet->setTitle(strInPutSet);
	m_pGridLayout_PutInSet = new QGridLayout;
	m_pGroupBox_PutInSet->setLayout(m_pGridLayout_PutInSet);

	m_pCheck_Input1 = new QSttCheckBox();
// 	m_pCheck_Input1->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input1, "Manual_InA", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input1,0,0);

	m_pCheck_Input2 = new QSttCheckBox();
// 	m_pCheck_Input2->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input2, "Manual_InB", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input2,0,1);

	m_pCheck_Input3 = new QSttCheckBox();
// 	m_pCheck_Input3->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");

	xlang_SetLangStrToWidget(m_pCheck_Input3, "Manual_InC", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input3,0,2);

	m_pCheck_Input4 = new QSttCheckBox();
// 	m_pCheck_Input4->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input4, "Manual_InD", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input4,0,3);

	m_pLogicAnd = new QRadioButton();
// 	m_pLogicAnd->setStyleSheet("QRadioButton::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pLogicAnd, "Native_LogicAnd", XLang_Ctrls_QRadioButton);
	m_pGridLayout_PutInSet->addWidget(m_pLogicAnd,0,5);

	m_pCheck_Input5 = new QSttCheckBox();
// 	m_pCheck_Input5->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input5, "Manual_InE", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input5,0,4);

	m_pCheck_Input6 = new QSttCheckBox();
// 	m_pCheck_Input6->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input6, "Manual_InF", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input6,1,0);

	m_pCheck_Input7 = new QSttCheckBox();
// 	m_pCheck_Input7->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input7, "Manual_InG", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input7,1,1);

	m_pCheck_Input8 = new QSttCheckBox();
// 	m_pCheck_Input8->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pCheck_Input8, "Manual_InH", XLang_Ctrls_QCheckBox);
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input8,1,2);

	CString strText;
	xlang_GetLangStrByFile(strText, "Native_BinX");
	m_pCheck_Input9 = new QSttCheckBox();
// 	m_pCheck_Input9->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Input9->setText(strText + "I");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input9,1,3);

	m_pCheck_Input10 = new QSttCheckBox();
// 	m_pCheck_Input10->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Input10->setText(strText + "J");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input10,1,4);

	m_pLogicOr = new QRadioButton();
// 	m_pLogicOr->setStyleSheet("QRadioButton::indicator{width:18px; height:18px;}");
	xlang_SetLangStrToWidget(m_pLogicOr, "Native_LogicOr", XLang_Ctrls_QRadioButton);
	m_pGridLayout_PutInSet->addWidget(m_pLogicOr,1,5);

    m_pGroupBox_PutOutSet = new QSttGroupBox();
    m_pGroupBox_PutOutSet->setTitle(strOutPutSet);
    m_pGridLayout_PutOutSet = new QGridLayout;
    m_pGroupBox_PutOutSet->setLayout(m_pGridLayout_PutOutSet);

    m_pCheck_Output1 = new QSttCheckBox();
// 	m_pCheck_Output1->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output1, "Manual_Out1", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output1,0,0);

    m_pCheck_Output2 = new QSttCheckBox();
// 	m_pCheck_Output2->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output2, "Manual_Out2", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output2,0,1);

    m_pCheck_Output3 = new QSttCheckBox();
// 	m_pCheck_Output3->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output3, "Manual_Out3", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output3,0,2);

    m_pCheck_Output4 = new QSttCheckBox();
// 	m_pCheck_Output4->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output4, "Manual_Out4", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output4,0,3);

    m_pCheck_Output5 = new QSttCheckBox();
// 	m_pCheck_Output5->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output5, "Manual_Out5", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output5,0,4);

    m_pCheck_Output6 = new QSttCheckBox();
// 	m_pCheck_Output6->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output6, "Manual_Out6", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output6,1,0);

    m_pCheck_Output7 = new QSttCheckBox();
// 	m_pCheck_Output7->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output7, "Manual_Out7", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output7,1,1);

    m_pCheck_Output8 = new QSttCheckBox();
// 	m_pCheck_Output8->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
    xlang_SetLangStrToWidget(m_pCheck_Output8, "Manual_Out8", XLang_Ctrls_QCheckBox);
    m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output8,1,2);

	xlang_GetLangStrByFile(strText, "Native_BoutX");
	m_pCheck_Output9 = new QSttCheckBox();
// 	m_pCheck_Output9->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Output9->setText(strText + "9");
	m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output9,1,3);

	m_pCheck_Output10 = new QSttCheckBox();
// 	m_pCheck_Output10->setStyleSheet("QSttCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Output10->setText(strText + "10");
	m_pGridLayout_PutOutSet->addWidget(m_pCheck_Output10,1,4);

	//采用QSttCheckBox类，需要注销样式  2022-11-19 sy
// 	QString strStyle = "QSttCheckBox::indicator:unchecked{width: 20px;height: 20px;}"
// 		"QSttCheckBox::indicator:checked{width: 20px;height: 20px;}";
// 		/*"QSttCheckBox{font-size:18px;}";*/ // 2022-10-22 sy 采用g_pSttGlobalFont

// 	m_pCheck_Output1->setStyleSheet(strStyle);
// 	m_pCheck_Output2->setStyleSheet(strStyle);
// 	m_pCheck_Output3->setStyleSheet(strStyle);
// 	m_pCheck_Output4->setStyleSheet(strStyle);
// 	m_pCheck_Output5->setStyleSheet(strStyle);
// 	m_pCheck_Output6->setStyleSheet(strStyle);
// 	m_pCheck_Output7->setStyleSheet(strStyle);
// 	m_pCheck_Output8->setStyleSheet(strStyle);
// 	m_pCheck_Output9->setStyleSheet(strStyle);
// 	m_pCheck_Output10->setStyleSheet(strStyle);
// 	m_pCheck_Input1->setStyleSheet(strStyle);
// 	m_pCheck_Input2->setStyleSheet(strStyle);
// 	m_pCheck_Input3->setStyleSheet(strStyle);
// 	m_pCheck_Input4->setStyleSheet(strStyle);
// 	m_pCheck_Input5->setStyleSheet(strStyle);
// 	m_pCheck_Input6->setStyleSheet(strStyle);
// 	m_pCheck_Input7->setStyleSheet(strStyle);
// 	m_pCheck_Input8->setStyleSheet(strStyle);
// 	m_pCheck_Input9->setStyleSheet(strStyle);
// 	m_pCheck_Input10->setStyleSheet(strStyle);
	
    m_pVBoxLayout_Main->addWidget(m_pGroupBox_Gradient);
	m_pVBoxLayout_Main->addWidget(m_pGroupBox_PutInSet);
    m_pVBoxLayout_Main->addWidget(m_pGroupBox_PutOutSet);

// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input1,m_pHarmParas->m_oBinaryConfig.m_binIn,0);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input2,m_pHarmParas->m_oBinaryConfig.m_binIn,1);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input3,m_pHarmParas->m_oBinaryConfig.m_binIn,2);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input4,m_pHarmParas->m_oBinaryConfig.m_binIn,3);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input5,m_pHarmParas->m_oBinaryConfig.m_binIn,4);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input6,m_pHarmParas->m_oBinaryConfig.m_binIn,5);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input7,m_pHarmParas->m_oBinaryConfig.m_binIn,6);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input8,m_pHarmParas->m_oBinaryConfig.m_binIn,7);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input9,m_pHarmParas->m_oBinaryConfig.m_binIn,8);
// 	GlobalSetQcheckState_BinaryIn(m_pCheck_Input10,m_pHarmParas->m_oBinaryConfig.m_binIn,9);
// 
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output1,m_pHarmParas->m_oBinaryConfig.m_binOut,0);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output2,m_pHarmParas->m_oBinaryConfig.m_binOut,1);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output3,m_pHarmParas->m_oBinaryConfig.m_binOut,2);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output4,m_pHarmParas->m_oBinaryConfig.m_binOut,3);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output5,m_pHarmParas->m_oBinaryConfig.m_binOut,4);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output6,m_pHarmParas->m_oBinaryConfig.m_binOut,5);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output7,m_pHarmParas->m_oBinaryConfig.m_binOut,6);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output8,m_pHarmParas->m_oBinaryConfig.m_binOut,7);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output9,m_pHarmParas->m_oBinaryConfig.m_binOut,8);
// 	GlobalSetQcheckState_BinaryOut(m_pCheck_Output10,m_pHarmParas->m_oBinaryConfig.m_binOut,9);

// 	if(g_nBinCount == 8)
// 	{
// 		m_pCheck_Input9->setChecked(false);
// 		m_pCheck_Input10->setChecked(false);
// 		m_pCheck_Input9->setEnabled(false);
// 		m_pCheck_Input10->setEnabled(false);
// 	}

// 	if(g_nBoutCount == 8)
// 	{
// 		m_pCheck_Output9->setChecked(false);
// 		m_pCheck_Output10->setChecked(false);
// 		m_pCheck_Output9->setEnabled(false);
// 		m_pCheck_Output10->setEnabled(false);
// 	}
}

void QHarmParaWidget::paintEvent( QPaintEvent *e )
{
	QStyleOption opt;

	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void QHarmParaWidget::SetData( CSttTestResourceBase *pSttTestResource,tmt_HarmParas *pHarmParas )
{
	m_pTestResource = pSttTestResource;
	m_pHarmParas = pHarmParas;

	UpdataPara();
}

void QHarmParaWidget::UpdataPara()
{
	m_pTestResource->AddGradientChs(m_oGradientChs);

	m_pHarmParas->m_nGradientTpSelect = amplitude_type;

	//m_pEdit_Start->setText(QString::number(m_pHarmParas->m_oHarmGradient.fStart,'f',3));//始值
	//m_pEdit_End->setText(QString::number(m_pHarmParas->m_oHarmGradient.fEnd,'f',3));//终值
	//m_pEdit_Step->setText(QString::number(m_pHarmParas->m_oHarmGradient.fStep,'f',3));//步长
	//m_pEdit_Steptime->setText(QString::number(m_pHarmParas->m_oHarmGradient.fStepTime,'f',3));//时间
	m_pEdit_Start->UpdateStructText(CVariantDataAddress(&m_pHarmParas->m_oHarmGradient.fStart), 3);//始值
	m_pEdit_End->UpdateStructText(CVariantDataAddress(&m_pHarmParas->m_oHarmGradient.fEnd), 3);//终值
	m_pEdit_Step->UpdateStructText(CVariantDataAddress(&m_pHarmParas->m_oHarmGradient.fStep), 3);//步长
	m_pEdit_Steptime->UpdateStructText(CVariantDataAddress(&m_pHarmParas->m_oHarmGradient.fStepTime), 3);//时间


	SetGradientCurSelCh();
	SetHarmOrderCombox();

	UpdateBinaryInBinaryOutEnable();

	bool bAuto = m_pHarmParas->m_bAuto;
	m_pEdit_Start->setDisabled(!bAuto);
	m_pEdit_End->setDisabled(!bAuto);
	m_pEdit_Steptime->setDisabled(!bAuto);

	if(m_pHarmParas->m_oBinaryConfig.m_nBinLogic == 1)
	{
		m_pLogicAnd->setChecked(true);
		m_pLogicOr->setChecked(false);
	}
	else
	{
		m_pLogicAnd->setChecked(false);
		m_pLogicOr->setChecked(true);
	}

	if (m_nHarmGradType == Amplitude_HarmGradType)
	{
		m_RadioBtn_Amplitude->setChecked(true);
		m_RadioBtn_Percent->setChecked(false);
	} 
	else
	{
		m_RadioBtn_Amplitude->setChecked(false);
		m_RadioBtn_Percent->setChecked(true);
	}

	if (m_pHarmParas->m_bAuto)
		m_pCheck_Auto->setChecked(true);
	else
		m_pCheck_Auto->setChecked(false);

// 	slot_cmb_ChanelIndexChanged(0);  //20240327 suyang 不应设置0，应从结构体里面获取
	
}

void QHarmParaWidget::UpdateBinaryInBinaryOutEnable()
{
	disconnect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)));
	disconnect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)));
	disconnect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)));
	disconnect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)));
	disconnect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)));
	disconnect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)));
	disconnect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)));
	disconnect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)));
	disconnect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)));
	disconnect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)));

	Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic);

	GlobalSetQcheckState_BinaryIn(m_pCheck_Input1,m_pHarmParas->m_oBinaryConfig.m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input2,m_pHarmParas->m_oBinaryConfig.m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input3,m_pHarmParas->m_oBinaryConfig.m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input4,m_pHarmParas->m_oBinaryConfig.m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input5,m_pHarmParas->m_oBinaryConfig.m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input6,m_pHarmParas->m_oBinaryConfig.m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input7,m_pHarmParas->m_oBinaryConfig.m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input8,m_pHarmParas->m_oBinaryConfig.m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input9,m_pHarmParas->m_oBinaryConfig.m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input10,m_pHarmParas->m_oBinaryConfig.m_binIn,9);

	// 	m_pCheck_Input1->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect);
	// 	m_pCheck_Input2->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect);
	// 	m_pCheck_Input3->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[2].nSelect);
	// 	m_pCheck_Input4->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[3].nSelect);
	// 	m_pCheck_Input5->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[4].nSelect);
	// 	m_pCheck_Input6->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[5].nSelect);
	// 	m_pCheck_Input7->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[6].nSelect);
	// 	m_pCheck_Input8->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[7].nSelect);
	// 
	// 	if(g_nBinCount == 10)
	// 	{
	// 		m_pCheck_Input9->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[8].nSelect);
	// 		m_pCheck_Input10->setChecked(m_pHarmParas->m_oBinaryConfig.m_binIn[9].nSelect);
	// 	}

	connect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)));
	connect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)));
	connect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)));
	connect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)));
	connect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)));
	connect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)));
	connect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)));
	connect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)));
	connect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)));
	connect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)));

	// 	m_pCheck_Output1->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[0].nState);
	// 	m_pCheck_Output2->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[1].nState);
	// 	m_pCheck_Output3->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[2].nState);
	// 	m_pCheck_Output4->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[3].nState);
	// 	m_pCheck_Output5->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[4].nState);
	// 	m_pCheck_Output6->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[5].nState);
	// 	m_pCheck_Output7->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[6].nState);
	// 	m_pCheck_Output8->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[7].nState);
	// 	if(g_nBoutCount == 10)
	// 	{
	// 		m_pCheck_Output9->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[8].nState);
	// 		m_pCheck_Output10->setChecked(m_pHarmParas->m_oBinaryConfig.m_binOut[9].nState);
	// 	}

	disconnect(m_pCheck_Output1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out1StateChanged(int)));
	disconnect(m_pCheck_Output2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out2StateChanged(int)));
	disconnect(m_pCheck_Output3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out3StateChanged(int)));
	disconnect(m_pCheck_Output4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out4StateChanged(int)));
	disconnect(m_pCheck_Output5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out5StateChanged(int)));
	disconnect(m_pCheck_Output6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out6StateChanged(int)));
	disconnect(m_pCheck_Output7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out7StateChanged(int)));
	disconnect(m_pCheck_Output8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out8StateChanged(int)));
	disconnect(m_pCheck_Output9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out9StateChanged(int)));
	disconnect(m_pCheck_Output10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out10StateChanged(int)));

	GlobalSetQcheckState_BinaryOut(m_pCheck_Output1,m_pHarmParas->m_oBinaryConfig.m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output2,m_pHarmParas->m_oBinaryConfig.m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output3,m_pHarmParas->m_oBinaryConfig.m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output4,m_pHarmParas->m_oBinaryConfig.m_binOut,3);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output5,m_pHarmParas->m_oBinaryConfig.m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output6,m_pHarmParas->m_oBinaryConfig.m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output7,m_pHarmParas->m_oBinaryConfig.m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output8,m_pHarmParas->m_oBinaryConfig.m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output9,m_pHarmParas->m_oBinaryConfig.m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_pCheck_Output10,m_pHarmParas->m_oBinaryConfig.m_binOut,9);

	connect(m_pCheck_Output1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out1StateChanged(int)));
	connect(m_pCheck_Output2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out2StateChanged(int)));
	connect(m_pCheck_Output3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out3StateChanged(int)));
	connect(m_pCheck_Output4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out4StateChanged(int)));
	connect(m_pCheck_Output5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out5StateChanged(int)));
	connect(m_pCheck_Output6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out6StateChanged(int)));
	connect(m_pCheck_Output7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out7StateChanged(int)));
	connect(m_pCheck_Output8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out8StateChanged(int)));
	connect(m_pCheck_Output9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out9StateChanged(int)));
	connect(m_pCheck_Output10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out10StateChanged(int)));
}
void QHarmParaWidget::SetGradientCurSelCh()
{
	disconnect(m_pCmb_Chanel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_ChanelIndexChanged( int)));
	
	m_pCmb_Chanel->clear();
	CDataTypeValue *pCurData = NULL;
	POS pos = m_oGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurData = (CDataTypeValue *)m_oGradientChs.GetNext(pos);
		m_pCmb_Chanel->addItem(pCurData->m_strID);//mod wangtao 20241029 去掉.GetString(),解决乱码问题
		//m_pCmb_Chanel->addItem(pCurData->m_strID.GetString());
	}

	para_type var = getParaTypeByInt(m_pHarmParas->m_nGradientChSelect);

	SetGradientCurSelCh(var);

	connect(m_pCmb_Chanel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_ChanelIndexChanged( int)));

}
void QHarmParaWidget::SetGradientCurSelCh( para_type vartype )
{
	CDataTypeValue *pCurSelData = m_oGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的递变通道(Index=%d)未查找到."),vartype);
	    CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurselinNotFound.GetString(),vartype);//当前选择的递变通道(Index=%d)未查找到 lcq
		return;
	} 
	else
	{
		long nIndex = m_oGradientChs.FindIndex(pCurSelData);
		ASSERT(nIndex>=0);
		m_pCmb_Chanel->setCurrentIndex(nIndex);
	}
}

void QHarmParaWidget::SetHarmOrderCombox()//谐波序列
{
	disconnect(m_pCmb_HarmNum, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_HarmOrderIndexChanged( int)));

	m_strHarmList.clear();
	m_pCmb_HarmNum->clear();
	ASSERT(m_pHarmParas);

	CString strDC,strFun,strHarm;

	xlang_GetLangStrByFile(strDC,"Native_DC");//直流
	xlang_GetLangStrByFile(strFun,"Native_Fundamental");//基波

	CString strHarmCount;
	xlang_GetLangStrByFile(strHarmCount, "State_HarmCount");

	m_strHarmList<<strDC;
	m_strHarmList<<strFun;
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	for (int nIndex = 2;  nIndex  <  nMaxRowCount;  nIndex++)
	{
// 		if (m_pHarmParas->m_uiVOL[0].Harm[nIndex].m_bSelect)//固定加30次谐波
// 		if (m_pHarmParas->m_uiVOL[m_pHarmParas->m_nGradientChSelect].Harm[nIndex].m_bSelect)
		{
			strHarm.Format("%d",nIndex);
			strHarm += strHarmCount;
// 			if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())//20220525  zhouhj  此处不需要进行语言判断,根据实际语言进行谐波次数转换
// 			{
// 				
// 			}
// 			else
// 			{
// 				strHarm = QString("Harm %1").arg(nIndex);
// 			}
			m_strHarmList<<strHarm;
		}
	}

	for (int k = 0; k < m_strHarmList.size(); k++)
		m_pCmb_HarmNum->addItem(m_strHarmList[k]);

	m_pCmb_HarmNum->setCurrentIndex(GetHarmIndex());
	connect(m_pCmb_HarmNum, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_HarmOrderIndexChanged( int)));
}

void QHarmParaWidget::InitConnect()
{
	connect(m_pCmb_Chanel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_ChanelIndexChanged( int)));
	connect(m_pCmb_HarmNum, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_cmb_HarmOrderIndexChanged( int)));


#ifdef _PSX_QT_LINUX_
	connect(m_pEdit_Start, SIGNAL(clicked()), this, SLOT(slot_lne_StartClicked()));
	connect(m_pEdit_End, SIGNAL(clicked()), this, SLOT(slot_lne_EndClicked()));
	connect(m_pEdit_Step, SIGNAL(clicked()), this, SLOT(slot_lne_StepClicked()));
	connect(m_pEdit_Steptime, SIGNAL(clicked()), this, SLOT(slot_lne_StepTimeClicked()));
#endif
	connect(m_pEdit_Start, SIGNAL(editingFinished()), this, SLOT(slot_lne_StartChanged()));
	connect(m_pEdit_End, SIGNAL(editingFinished()), this, SLOT(slot_lne_EndChanged()));
	connect(m_pEdit_Step, SIGNAL(editingFinished()), this, SLOT(slot_lne_StepChanged()));
	connect(m_pEdit_Steptime, SIGNAL(editingFinished()), this, SLOT(slot_lne_StepTimeChanged()));


	connect(m_pCheck_Auto, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_AutoStateChanged(int)));

	connect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)));
	connect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)));
	connect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)));
	connect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)));
	connect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)));
	connect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)));
	connect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)));
	connect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)));
	connect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)));
	connect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)));

	connect(m_pCheck_Output1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out1StateChanged(int)));
	connect(m_pCheck_Output2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out2StateChanged(int)));
	connect(m_pCheck_Output3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out3StateChanged(int)));
	connect(m_pCheck_Output4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out4StateChanged(int)));
	connect(m_pCheck_Output5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out5StateChanged(int)));
	connect(m_pCheck_Output6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out6StateChanged(int)));
	connect(m_pCheck_Output7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out7StateChanged(int)));
	connect(m_pCheck_Output8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out8StateChanged(int)));
	connect(m_pCheck_Output9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out9StateChanged(int)));
	connect(m_pCheck_Output10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_Out10StateChanged(int)));

	connect(m_pLogicAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)));
	connect(m_pLogicOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)));

	connect(m_RadioBtn_Amplitude, SIGNAL(toggled(bool )), this, SLOT(slot_radio_HarmGradTypeStateChanged(bool)));
	connect(m_RadioBtn_Percent, SIGNAL(toggled(bool )), this, SLOT(slot_radio_HarmGradTypeStateChanged(bool)));
}

void QHarmParaWidget::slot_cmb_ChanelIndexChanged( int index )
{
	if(m_pCmb_Chanel->IsScrolling())
	{
		return;
	}

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(index);

	if (pCurDataTypeValue == NULL)
	{
		return;
	}

	m_pHarmParas->m_nGradientChSelect = pCurDataTypeValue->GetIndex();

	
	UpdateGradLabelUnit();

	slot_lne_StartChanged();
	slot_lne_EndChanged();
	slot_lne_StepChanged();

	m_strChanelText=m_pCmb_Chanel->currentText();

	if(CHANNAL_TYPE_I(m_pHarmParas->m_nGradientChSelect))
	{
		m_pHarmParas->m_nVarIndexType = 0;
	}
	else if (CHANNAL_TYPE_U(m_pHarmParas->m_nGradientChSelect))
	{
		m_pHarmParas->m_nVarIndexType = 1;
	}
	else if(CHANNAL_TYPE_F(m_pHarmParas->m_nGradientChSelect))
	{
		m_pHarmParas->m_nVarIndexType = 2;
	}

	if(!IsChannelValid())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("指定通道的谐波未被勾选!"));
	}
}

void QHarmParaWidget::UpdateGradLabelUnit()
{
	QString text = m_pCmb_Chanel->currentText();
	QString str;

	if (IsHarmGradPercentType())
	{
		str = tr("(%):");
	}
	else if (text.contains("U"))
	{
		if (m_nDispMode == V_Primary)//一次值
		{
			str = tr("(kV):");
		}
		else
		{
			str = tr("(V):");
		}
	}
	else
	{	
		str = tr("(A):");
	}

	CString strStart,strEnd,strStep;

	xlang_GetLangStrByFile(strStart,"State_BeginVal");
	xlang_GetLangStrByFile(strEnd,"State_EndVal");
	xlang_GetLangStrByFile(strStep,"sStep");

	m_pLabel_Start->setText(strStart + str);
	m_pLabel_End->setText(strEnd + str);
	m_pLabel_Step->setText(strStep + str);
}

bool QHarmParaWidget::IsHarmGradPercentType()
{
	return (m_nHarmGradType == Percent_HarmGradType)&&(m_pHarmParas->m_oHarmGradient.nHarmIndex != 1);
}

void QHarmParaWidget::slot_cmb_HarmOrderIndexChanged( int index )
{
	if (index < 0)
		return;

	if(m_pCmb_HarmNum->IsScrolling())
	{
		return;
	}

	m_pHarmParas->m_oHarmGradient.nHarmIndex = index;//20220525 谐波次数依次为直流、基波、2次谐波等等  无需再进行字符串匹配
	UpdateGradLabelUnit();

	if(!IsChannelValid())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("指定通道的谐波未被勾选!"));
	}

// 	CString strNO = tr("0");
// 	CString strDC,strFin,str2Harm;
// 
// 	xlang_GetLangStrByFile(strDC,"Native_DC");
// 	xlang_GetLangStrByFile(strFin,"Manual_Fundamental");
// 	str2Harm = tr("次谐波");
// 	CString strTemp = m_strHarmList[index];
// 
// 	if (strTemp == strDC)
// 	{
// 		m_pHarmParas->m_oHarmGradient.nHarmIndex  = 0;
// 	}
// 	else if (strTemp == strFin)
// 	{
// 		m_pHarmParas->m_oHarmGradient.nHarmIndex = 1;
// 	}
// 	else 
// 	{
// 		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
// 		{
// 			int pos = strTemp.Find(str2Harm);
// 			m_pHarmParas->m_oHarmGradient.nHarmIndex = strTemp.left(pos).toInt();
// 		}
// 		else
// 		{
// 			strNO = m_strHarmList[index].mid(5);
// 			m_pHarmParas->m_oHarmGradient.nHarmIndex = strNO.toInt();
// 		}
// 	}
}

void QHarmParaWidget::slot_lne_StartChanged()
{
	//20240705 huangliang 
	if (m_pEdit_Start->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEdit_Start)->IsSetting())
		{
			return ;
		}		
	}
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fv = m_pEdit_Start->text().toFloat();	  //变化始值

	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		fv = setLimit(0,fAcVMax,fv);
	}
	else
	{	
		fv = setLimit(0,fAcIMax,fv);
	}
	m_pEdit_Start->setText(QString::number(fv,'f',3));
	m_pHarmParas->m_oHarmGradient.fStart = fv;
	
}

void QHarmParaWidget::slot_lne_EndChanged()
{
	//20240705 huangliang 
	if (m_pEdit_End->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEdit_End)->IsSetting())
		{
			return ;
		}		
	}
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fv = m_pEdit_End->text().toFloat();

	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		fv = setLimit(0,fAcVMax,fv);
	}
	else
	{	
		fv = setLimit(0,fAcIMax,fv);
	}
	m_pEdit_End->setText(QString::number(fv,  'f', 3));
	m_pHarmParas->m_oHarmGradient.fEnd = fv;
}

void QHarmParaWidget::slot_lne_StepChanged()
{
	//20240705 huangliang 
	if (m_pEdit_Step->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEdit_Step)->IsSetting())
		{
			return ;
		}		
	}
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fv = m_pEdit_Step->text().toFloat();

	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		fv = setLimit(0,fAcVMax,fv);
	}
	else
	{	
		fv = setLimit(0,fAcIMax,fv);
	}
	m_pEdit_Step->setText(QString::number(fv,  'f', 3));
	m_pHarmParas->m_oHarmGradient.fStep = fv;
}
void QHarmParaWidget::slot_lne_StepTimeChanged()
{
	//20240705 huangliang 
	if (m_pEdit_Steptime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEdit_Steptime)->IsSetting())
		{
			return ;
		}		
	}
	float fv = m_pEdit_Steptime->text().toFloat();
	fv = setLimit(0,999.999,fv);

	m_pHarmParas->m_oHarmGradient.fStepTime = fv;

    m_pEdit_Steptime->setText(QString::number(fv,'f',3));
}

void QHarmParaWidget::slot_ck_AutoStateChanged(int)
{	
    if (m_pCheck_Auto->isChecked())
	{
		m_pHarmParas->m_bAuto = true;		
	}
	else
	{
		m_pHarmParas->m_bAuto = false;	
	}

	m_pEdit_Start->setDisabled(!m_pHarmParas->m_bAuto);
	m_pEdit_End->setDisabled(!m_pHarmParas->m_bAuto);
	m_pEdit_Steptime->setDisabled(!m_pHarmParas->m_bAuto);

	if (m_pHarmParas->m_bAuto)
	{
		if (m_nHarmGradType == Percent_HarmGradType)
		{
			m_nHarmGradType = Amplitude_HarmGradType;
			m_RadioBtn_Amplitude->setChecked(true);
			m_RadioBtn_Percent->setChecked(false);
		}
		
		m_RadioBtn_Amplitude->setEnabled(false);
		m_RadioBtn_Percent->setEnabled(false);
	} 
	else
	{
		m_RadioBtn_Amplitude->setEnabled(true);
		m_RadioBtn_Percent->setEnabled(true);
	}

	//勾选时改变m_strChanelText
	m_strChanelText = m_pCmb_Chanel->currentText();

	emit sig_AutoStateChanged(m_pHarmParas->m_bAuto);
}

void QHarmParaWidget::slot_ck_In1StateChanged(int)
{	
	if (m_pCheck_Input1->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In2StateChanged(int)
{	
	if (m_pCheck_Input2->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In3StateChanged(int)
{	
	if (m_pCheck_Input3->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[2].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In4StateChanged(int)
{	
	if (m_pCheck_Input4->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[3].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In5StateChanged(int)
{
	if (m_pCheck_Input5->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[4].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In6StateChanged(int)
{	
	if (m_pCheck_Input6->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[5].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In7StateChanged(int)
{	
	if (m_pCheck_Input7->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[6].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In8StateChanged(int)
{
	if (m_pCheck_Input8->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[7].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In9StateChanged(int)
{
	if (m_pCheck_Input9->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[8].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_In10StateChanged(int)
{
	if (m_pCheck_Input10->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binIn[9].nSelect = 0;
	}

	if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
	{
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	emit sig_InPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out1StateChanged(int)
{	
    if (m_pCheck_Output1->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[0].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[0].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out2StateChanged(int)
{	
    if (m_pCheck_Output2->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[1].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[1].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out3StateChanged(int)
{	
    if (m_pCheck_Output3->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[2].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[2].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out4StateChanged(int)
{	
    if (m_pCheck_Output4->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[3].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[3].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out5StateChanged(int)
{
    if (m_pCheck_Output5->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[4].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[4].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out6StateChanged(int)
{	
    if (m_pCheck_Output6->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[5].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[5].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out7StateChanged(int)
{	
    if (m_pCheck_Output7->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[6].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[6].nState = 0;
	}

	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out8StateChanged(int)
{
    if (m_pCheck_Output8->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[7].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[7].nState = 0;
	}
	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out9StateChanged(int)
{
	if (m_pCheck_Output9->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[8].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[8].nState = 0;
	}
	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::slot_ck_Out10StateChanged(int)
{
	if (m_pCheck_Output10->checkState() == Qt::Checked)
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[9].nState = 1;
	}
	else
	{
		m_pHarmParas->m_oBinaryConfig.m_binOut[9].nState = 0;
	}
	emit sig_OutPutStateChanged();
}

void QHarmParaWidget::StartInit()
{
	bool bAuto = m_pHarmParas->m_bAuto;

	m_pEdit_Step->setDisabled(bAuto);
	m_pEdit_Steptime->setDisabled(true);
	m_pEdit_Start->setDisabled(true);
	m_pEdit_End->setDisabled(true);

//	m_pLabel_Step->setDisabled(true);
//	m_pLabel_StepTime->setDisabled(true);
//	m_pLabel_Start->setDisabled(true);
//	m_pLabel_End->setDisabled(true);

	m_pCmb_Chanel->setDisabled(true);
	m_pCmb_HarmNum->setDisabled(true);
	SetBinaryInBinaryOutEnable(!bAuto);

	m_pLogicAnd->setDisabled(true);
	m_pLogicOr->setDisabled(true);

	m_RadioBtn_Amplitude->setDisabled(true);
	m_RadioBtn_Percent->setDisabled(true);

	m_pCheck_Auto->setDisabled(true);
}

void QHarmParaWidget::StopInit()
{
	m_pEdit_Step->setDisabled(false);

	m_pEdit_Steptime->setDisabled(!m_pHarmParas->m_bAuto);
	m_pEdit_Start->setDisabled(!m_pHarmParas->m_bAuto);
	m_pEdit_End->setDisabled(!m_pHarmParas->m_bAuto);

	m_pCheck_Auto->setDisabled(false);

	m_pCmb_Chanel->setDisabled(false);
	m_pCmb_HarmNum->setDisabled(false);
	SetBinaryInBinaryOutEnable(true);

	m_pLogicAnd->setDisabled(false);
	m_pLogicOr->setDisabled(false);

	if (m_pHarmParas->m_bAuto)
	{
		m_RadioBtn_Amplitude->setEnabled(false);
		m_RadioBtn_Percent->setEnabled(false);
	} 
	else
	{
		m_RadioBtn_Amplitude->setEnabled(true);
		m_RadioBtn_Percent->setEnabled(true);
	}
}

//void GlobalEa

void QHarmParaWidget::SetBinaryInBinaryOutEnable( bool bFlag )
{
	GlobalSetQcheckEnable_Binary(m_pCheck_Input1,0,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input2,1,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input3,2,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input4,3,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input5,4,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input6,5,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input7,6,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input8,7,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input9,8,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input10,9,g_nBinCount,bFlag);
// 	m_pCheck_Input1->setDisabled(bFlag);
// 	m_pCheck_Input2->setDisabled(bFlag);
// 	m_pCheck_Input3->setDisabled(bFlag);
// 	m_pCheck_Input4->setDisabled(bFlag);
// 	m_pCheck_Input5->setDisabled(bFlag);
// 	m_pCheck_Input6->setDisabled(bFlag);
// 	m_pCheck_Input7->setDisabled(bFlag);
// 	m_pCheck_Input8->setDisabled(bFlag);
// 	if(g_nBinCount == 10)
// 	{
// 		m_pCheck_Input9->setDisabled(bFlag);
// 		m_pCheck_Input10->setDisabled(bFlag);	
// 	}

	GlobalSetQcheckEnable_Binary(m_pCheck_Output1,0,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output2,1,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output3,2,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output4,3,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output5,4,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output6,5,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output7,6,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output8,7,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output9,8,g_nBoutCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Output10,9,g_nBoutCount,bFlag);

// 	m_pCheck_Output1->setDisabled(bFlag);
// 	m_pCheck_Output2->setDisabled(bFlag);
// 	m_pCheck_Output3->setDisabled(bFlag);
// 	m_pCheck_Output4->setDisabled(bFlag);
// 	m_pCheck_Output5->setDisabled(bFlag);
// 	m_pCheck_Output6->setDisabled(bFlag);
// 	m_pCheck_Output7->setDisabled(bFlag);
// 	m_pCheck_Output8->setDisabled(bFlag);
// 	if(g_nBoutCount == 10)
// 	{
// 		m_pCheck_Output9->setDisabled(bFlag);
// 		m_pCheck_Output10->setDisabled(bFlag);
// 	}
}

void QHarmParaWidget::slot_lne_StartClicked()
{
	int n = 0;
	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		n = 0;
	}
	else
	{	
		n = 1;
	}

	QString strValue = m_pEdit_Start->text();
	GetWidgetBoard_DigitData(n, strValue,m_pEdit_Start, this);
// 	m_pEdit_Start->setText(strValue);

	/*
	WidgetKeyboardV_Digit dlg(n,this);
	dlg.m_strEditInfo = m_pEdit_Start->text();
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pEdit_Start->setText(dlg.m_strEditInfo);
	}
	*/
	//slot_lne_StartChanged();
}

void QHarmParaWidget::slot_lne_EndClicked()
{
	int n = 0;
	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		n = 0;
	}
	else
	{	
		n = 1;
	}

	QString strValue = m_pEdit_End->text();
	GetWidgetBoard_DigitData(n, strValue,m_pEdit_End, this);
	//m_pEdit_End->setText(strValue);

	/*
	WidgetKeyboardV_Digit dlg(n,this);
	dlg.m_strEditInfo = m_pEdit_End->text();
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pEdit_End->setText(dlg.m_strEditInfo);
	}
	*/
	//slot_lne_EndChanged();
}

void QHarmParaWidget::slot_lne_StepClicked()
{
	int n = 0;
	if (m_pCmb_Chanel->currentText().contains("U"))
	{
		n = 0;
	}
	else
	{	
		n = 1;
	}

	QString strValue = m_pEdit_Step->text();
	GetWidgetBoard_DigitData(n, strValue,m_pEdit_Step, this);
	//m_pEdit_Step->setText(strValue);

	/*
	WidgetKeyboardV_Digit dlg(n,this);
	dlg.m_strEditInfo = m_pEdit_Step->text();
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pEdit_Step->setText(dlg.m_strEditInfo);
	}
	*/
	//slot_lne_StepChanged();
}

void QHarmParaWidget::slot_lne_StepTimeClicked()
{
	QString strValue = m_pEdit_Steptime->text();
	GetWidgetBoard_DigitData(4, strValue,m_pEdit_Steptime, this);
	//m_pEdit_Steptime->setText(strValue);

	/*
	WidgetKeyboardV_Digit dlg(4,this);
	dlg.m_strEditInfo = m_pEdit_Steptime->text();
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pEdit_Steptime->setText(dlg.m_strEditInfo);
	}
	*/
	//slot_lne_StepTimeChanged();
}

void QHarmParaWidget::slot_radio_AndStateChanged( bool )
{
	if(m_pLogicAnd->isChecked())
	{
		m_pHarmParas->m_oBinaryConfig.m_nBinLogic = 1;
		if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
		{
			if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
			{
				m_pCheck_Input1->setCheckState(Qt::Checked);
			}
			if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
			{
				m_pCheck_Input2->setCheckState(Qt::Checked);
			}	
		}
	}
	else if (m_pLogicOr->isChecked())
	{
		m_pHarmParas->m_oBinaryConfig.m_nBinLogic = 0;
	}
}

void QHarmParaWidget::slot_radio_HarmGradTypeStateChanged( bool bValue)
{
	if (!bValue)
	{
		return;
	}

	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());

	if (pRadioBtn == m_RadioBtn_Amplitude)
	{
		m_nHarmGradType = Amplitude_HarmGradType;
	}
	else if (pRadioBtn == m_RadioBtn_Percent)
	{
		m_nHarmGradType = Percent_HarmGradType;
	}

	UpdateGradLabelUnit();
}

void QHarmParaWidget::slot_radio_OrStateChanged( bool )
{
	if(m_pLogicAnd->isChecked())
	{
		m_pHarmParas->m_oBinaryConfig.m_nBinLogic = 1;
		if (!Global_CheckBinSelect(m_pHarmParas->m_oBinaryConfig.m_binIn,g_nBinCount, m_pHarmParas->m_oBinaryConfig.m_nBinLogic))
		{
			if(m_pHarmParas->m_oBinaryConfig.m_binIn[0].nSelect == 1)
			{
				m_pCheck_Input1->setCheckState(Qt::Checked);
			}
			if(m_pHarmParas->m_oBinaryConfig.m_binIn[1].nSelect == 1)
			{
				m_pCheck_Input2->setCheckState(Qt::Checked);
			}	
		}
	}
	else if (m_pLogicOr->isChecked())
	{
		m_pHarmParas->m_oBinaryConfig.m_nBinLogic = 0;
	}
}

int QHarmParaWidget::GetHarmIndex()
{
	return m_pHarmParas->m_oHarmGradient.nHarmIndex;
//	int nIndex = m_pHarmParas->m_oHarmGradient.nHarmIndex;
// 	CString strTemp;
// 
// 	CString strHarmCount;
// 	xlang_GetLangStrByFile(strHarmCount, "State_HarmCount");
// 	strTemp.Format("%d",nIndex);
// 	strTemp += strHarmCount;
// 
// // 	if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
// // 	{
// // 		strTemp.Format("%d",nIndex);
// // 		strTemp += strHarmCount;
// // 	}
// // 	else
// // 	{
// // 		strTemp = QString("Harm %1").arg(nIndex);
// // 	}
// 
// 	if (nIndex == 0||nIndex == 1)
// 		return nIndex;
// 
// 	int k = 0;
// 	for ( k = 0; k < m_strHarmList.size(); k++)
// 	{
// 		if (m_strHarmList[k] == strTemp)
// 		{
// 			break;
// 		}
// 	}
// 	return k;
}











