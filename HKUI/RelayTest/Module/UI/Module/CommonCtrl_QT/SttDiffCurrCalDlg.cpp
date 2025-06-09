#include "SttDiffCurrCalDlg.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

SttDiffCurrCalDlg::SttDiffCurrCalDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_nHeightUsedIndex = 0;
	m_nLowerUsedIndex = 0;
	m_pDiffCurrCalParas = NULL;
}

SttDiffCurrCalDlg::~SttDiffCurrCalDlg()
{

}

void SttDiffCurrCalDlg::InitUI(Stt_DiffCurrCalParas *pDiffCurrCalParas)
{
	m_pDiffCurrCalParas = pDiffCurrCalParas;
	CString strTmp;
	//strTmp = _T("差流计算");
	setWindowTitle(g_sLangTxt_State_Difflowcalculation);//差流计算  LCQ
	
	resize(700, 450);
	m_pParasSet_GridLayout = new QGridLayout;
	m_pParasSet_GridLayout->setSpacing(20);//设置行间距
	m_pParasSet_GridLayout->setColumnMinimumWidth(3, 250);
	m_pAllVLayout = new QVBoxLayout(this);

	//strTmp = _T("差动电流(A)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_DiffCurrentA , "State_DiffCurrentA");//"差动电流(A)-LCQ
	m_pId_Label = new QLabel(g_sLangTxt_State_DiffCurrentA);
	//strTmp = _T("制动电流(A)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_BrakCurrentA, "State_BrakCurrentA");//制动电流(A)-LCQ
	m_pIr_Label = new QLabel(g_sLangTxt_State_BrakCurrentA);
	//strTmp = _T("制动方程");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Bequation, "State_Bequation");//制动方程-LCQ
	m_pIrEquation_Label = new QLabel(g_sLangTxt_State_Bequation);
	strTmp = _T("K1");
	m_pK1_Label = new QLabel(strTmp);
	strTmp = _T("K2");
	m_pK2_Label = new QLabel(strTmp);
	//strTmp = _T("CT极性");
	//xlang_GetLangStrByFile(g_sLangTxt_State_CTpolarity , "State_CTpolarity");//CT极性-LCQ
	m_pCTPoint_Label = new QLabel(g_sLangTxt_State_CTpolarity );
	//strTmp = _T("高压侧平衡系数");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Hsbalancefactor , "State_Hsbalancefactor");//高压侧平衡系数-LCQ
	m_pKph_Label = new QLabel(g_sLangTxt_State_Hsbalancefactor );
	//strTmp = _T("低压侧平衡系数");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Lsbalancefactor, "State_Lsbalancefactor");//低压侧平衡系数-LCQ
	m_pKpl_Label = new QLabel(g_sLangTxt_State_Lsbalancefactor);


	//strTmp = _T("高压侧绕组接线型式");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Hswindwirtype, "State_Hswindwirtype");//高压侧绕组接线型式-LCQ
	m_pWindH_Label = new QLabel(g_sLangTxt_State_Hswindwirtype);
	//strTmp = _T("低压侧绕组接线型式");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Lswindwirtype, "State_Lswindwirtype");//低压侧绕组接线型式-LCQ
	m_pWindL_Label = new QLabel(g_sLangTxt_State_Lswindwirtype);
	//strTmp = _T("绕组间角差(钟点数)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_HbdiffAngularwind, "State_HbdiffAngularwind");//绕组间角差(钟点数)-LCQ
	m_pTransGroupMode_Label = new QLabel(g_sLangTxt_State_HbdiffAngularwind);
	//strTmp = _T("平衡系数计算");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Bfactorcalculation, "State_Bfactorcalculation");//平衡系数计算-LCQ
	m_pJXFactor_Label = new QLabel(g_sLangTxt_State_Bfactorcalculation);
	//strTmp = _T("校正选择");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Correctionselection, "State_Correctionselection");//校正选择-LCQ
	m_pPhCorrectMode_Label = new QLabel(g_sLangTxt_State_Correctionselection);
	//strTmp = _T("测试相");
	//xlang_GetLangStrByFile( g_sLangTxt_State_Testphase, "State_Testphase");//测试相-LCQ
	m_pTestPhase_Label = new QLabel( g_sLangTxt_State_Testphase);
	//strTmp = _T("高压侧应用于(I1)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_FirHVoltageSide, "State_FirHVoltageSide");//高压侧应用于(I1)-LCQ
	m_pHightUsed_Label = new QLabel(g_sLangTxt_State_FirHVoltageSide);
	//strTmp = _T("高压侧应用于(I2)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_SecHVoltageSide, "State_SecHVoltageSide");//高压侧应用于(I2)-LCQ
	m_pLowerUsed_Label = new QLabel(g_sLangTxt_State_SecHVoltageSide);

	m_pId_FloatLineEdit = new QFloatLineEdit;
	m_pId_FloatLineEdit->InitCoverage(0,100);
	m_pIr_FloatLineEdit = new QFloatLineEdit;
	m_pIr_FloatLineEdit->InitCoverage(0,100);
	m_pIrEquation_ComboBox = new QScrollComboBox;
	m_astrEquationList<<tr("Ir=(|I1-I2|)/K1 or Ir=(|I1+I2|)/K1")<<tr("Ir=(|I1|+|I2|*K2)/K1")<<tr("Ir=max(|I1|,|I2|)")\
		<<tr("Ir=(|Id-|I1|-|I2||)/K1")<<tr("Ir=|I2|");/*<<tr("Sqrt(K1*I1*I2*Cos(δ))");*/
	strTmp = _T("Sqrt(K1*I1*I2*Cos(δ))");
	m_astrEquationList<<strTmp;
	m_pIrEquation_ComboBox->addItems(m_astrEquationList);

	m_pK1_FloatLineEdit = new QFloatLineEdit;
	m_pK1_FloatLineEdit->InitCoverage(0,100);
	m_pK2_FloatLineEdit = new QFloatLineEdit;
	m_pK2_FloatLineEdit->InitCoverage(0,100);
	m_pCTPoint_ComboBox = new QScrollComboBox;

	CString strTrans1, strTrans2;
	xlang_GetLangStrByFile(strTrans1, "State_Trans1");
	xlang_GetLangStrByFile(strTrans2, "State_Trans2");
	m_astrCTPointList<< strTrans2 << strTrans1;
	m_pCTPoint_ComboBox->addItems(m_astrCTPointList);

	m_pKph_FloatLineEdit = new QFloatLineEdit;
	m_pKph_FloatLineEdit->InitCoverage(0,100);
	m_pKpl_FloatLineEdit = new QFloatLineEdit;
	m_pKpl_FloatLineEdit->InitCoverage(0,100);

	strTmp = _T("Y");
	m_astrWindList<<strTmp;
	strTmp = _T("△");
	m_astrWindList<<strTmp;
	//m_astrWindList<<tr("Y")<<tr("△");
	//strTmp = _T("12点");
	xlang_GetLangStrByFile(g_sLangTxt_State_12Oclock, "State_12Oclock");//12点-LCQ
	m_astrTransGroupMode<<g_sLangTxt_State_12Oclock;
	int nIndex = 1;
	CString strIndex;
	CString strPoint;
	//strPoint = _T("点");
    xlang_GetLangStrByFile(strPoint, "State_Oclock");//点-LCQ
	while (nIndex <= 11)
	{
		strIndex.Format(_T("%d"), nIndex);
		strTmp = strIndex + strPoint;
		m_astrTransGroupMode<<strTmp;
		nIndex++;
	}

	/*m_astrTransGroupMode<<tr("12点")<<tr("1点")<<tr("2点")<<tr("3点")<<tr("4点")\
		<<tr("5点")<<tr("6点")<<tr("7点")<<tr("8点")<<tr("9点")<<tr("10点")<<tr("11点");*/

	CString strWinding, strNotWinding;
	xlang_GetLangStrByFile(strWinding, "State_Winding");
	xlang_GetLangStrByFile(strNotWinding, "State_NotconWindconnection");
	m_astrJXFactorList<< strNotWinding << strWinding;

	CString strNoAdjust, strTriAdjust, strYAdjust;
	xlang_GetLangStrByFile(strNoAdjust, "State_NoAdjust");
	xlang_GetLangStrByFile(strTriAdjust, "State_Triangulationcorrection");
	xlang_GetLangStrByFile(strYAdjust, "State_YAdjust");
	m_astrPhCorrectMode<<strNoAdjust<<strTriAdjust<<strYAdjust;

	m_astrTestPhaseList<<tr("A")<<tr("B")<<tr("C")<<tr("ABC")<<tr("AB")<<tr("BC")<<tr("CA");

	long nCurrGroupNum = 2,nVolGroupNum = 0;

	if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
	{
		g_oSttTestResourceMngr.m_pTestResouce->GetCurrVolGroupNum(nCurrGroupNum,nVolGroupNum);
	}

	xlang_GetLangStrByFile(strTmp, "Native_Group");

	for (int nGroupIndex = 0;nGroupIndex<nCurrGroupNum;nGroupIndex++)
	{
		m_astrCurrentUsedList.append(strTmp + QString("%1").arg(nGroupIndex+1));
	}

//	m_astrCurrentUsedList<<tr("组1")<<tr("组2")<<tr("组3")<<tr("组4")<<tr("组5")<<tr("组6");
	m_pWindH_ComboBox = new QScrollComboBox;
	m_pWindH_ComboBox->addItems(m_astrWindList);
	m_pWindL_ComboBox = new QScrollComboBox;
	m_pWindL_ComboBox->addItems(m_astrWindList);
	m_pTransGroupMode_ComboBox = new QScrollComboBox;
	m_pTransGroupMode_ComboBox->addItems(m_astrTransGroupMode);
	m_pJXFactor_ComboBox = new QScrollComboBox;
	m_pJXFactor_ComboBox->addItems(m_astrJXFactorList);
	m_pPhCorrectMode_ComboBox = new QScrollComboBox;
	m_pPhCorrectMode_ComboBox->addItems(m_astrPhCorrectMode);
	m_pTestPhase_ComboBox = new QScrollComboBox;
	m_pTestPhase_ComboBox->addItems(m_astrTestPhaseList);
	m_pHightUsed_ComboBox = new QScrollComboBox;
	m_pHightUsed_ComboBox->addItems(m_astrCurrentUsedList);
	m_pLowerUsed_ComboBox = new QScrollComboBox;
	
	if (m_astrCurrentUsedList.size() <= 1)
	{
		CString strNull = _T("空");
		m_pLowerUsed_ComboBox->addItem(strNull);
	}
	else
	{
	m_pLowerUsed_ComboBox->addItems(m_astrCurrentUsedList);
	}
//	m_pLowerUsed_ComboBox->setFixedWidth(100);

	m_pParasSet_GridLayout->addWidget(m_pId_Label, 0, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pId_FloatLineEdit, 0, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pWindH_Label, 0, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pWindH_ComboBox, 0, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pIr_Label, 1, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pIr_FloatLineEdit, 1, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pWindL_Label, 1, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pWindL_ComboBox, 1, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pIrEquation_Label, 2, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pIrEquation_ComboBox, 2, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pTransGroupMode_Label, 2, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pTransGroupMode_ComboBox, 2, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pK1_Label, 3, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pK1_FloatLineEdit, 3, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pJXFactor_Label, 3, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pJXFactor_ComboBox, 3, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pK2_Label, 4, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pK2_FloatLineEdit, 4, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pPhCorrectMode_Label, 4, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pPhCorrectMode_ComboBox, 4, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pCTPoint_Label, 5, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pCTPoint_ComboBox, 5, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pTestPhase_Label, 5, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pTestPhase_ComboBox, 5, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pKph_Label, 6, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pKph_FloatLineEdit, 6, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pHightUsed_Label, 6, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pHightUsed_ComboBox, 6, 3, 1, 1);

	m_pParasSet_GridLayout->addWidget(m_pKpl_Label, 7, 0, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pKpl_FloatLineEdit, 7, 1, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pLowerUsed_Label, 7, 2, 1, 1);
	m_pParasSet_GridLayout->addWidget(m_pLowerUsed_ComboBox, 7, 3, 1, 1);

    // chenling 2024.7.16 设置每列的拉伸因子,自适应窗口变化
    m_pParasSet_GridLayout->setColumnStretch(0, 1);
    m_pParasSet_GridLayout->setColumnStretch(1, 1);
    m_pParasSet_GridLayout->setColumnStretch(2, 1);
    m_pParasSet_GridLayout->setColumnStretch(3, 1);


	m_pOK_PushButton = new QPushButton(this);
	//strTmp = _T("确定");
	m_pOK_PushButton->setText(g_sLangTxt_OK/*tr("确定")*/);
	m_pCancel_PushButton = new QPushButton(this);
	//strTmp = _T("取消");
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel/*tr("取消")*/);

	m_pOkCancel_HBoxLayout = new QHBoxLayout;
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addLayout(m_pParasSet_GridLayout);
	m_pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);
	setLayout(m_pAllVLayout);
	InitDatas();

	//2024-8-28 wuxinyi 应北京需求确认按钮保持使能
// 	if (nCurrGroupNum<2)
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前电流组数为(%ld),至少需要2组电流才能进行差流计算."),nCurrGroupNum); 
// 		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_CurbanksatleastTwo.GetString(),nCurrGroupNum);//   3.13 lcq
// 		m_pOK_PushButton->setEnabled(false);
// 	}

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pHightUsed_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrGroupChanged(int)));
	connect(m_pLowerUsed_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrGroupChanged(int)));
}

void SttDiffCurrCalDlg::InitDatas()
{
	if (m_pDiffCurrCalParas == NULL)
	{
		return;
	}

	m_pId_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fId);
	m_pIr_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fIr);
	m_pIrEquation_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nIrEquation);
	m_pK1_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fK1);
	m_pK2_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fK2);
	m_pCTPoint_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nCTPoint);
	m_pKph_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fKph);
	m_pKpl_FloatLineEdit->SetValue(m_pDiffCurrCalParas->m_fKpl);

	m_pWindH_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nWindH);
	m_pWindL_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nWindL);
	m_pTransGroupMode_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nTransGroupMode);
	m_pJXFactor_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nJXFactor);
	m_pPhCorrectMode_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nPhCorrectMode);
	m_pTestPhase_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nTestPhase);
	m_pHightUsed_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nHightUsed);
	m_pLowerUsed_ComboBox->setCurrentIndex(m_pDiffCurrCalParas->m_nLowerUsed);
	m_nHeightUsedIndex = m_pDiffCurrCalParas->m_nHightUsed;
	m_nLowerUsedIndex = m_pDiffCurrCalParas->m_nLowerUsed;

	UpdateUsed_ComboBox();
}

void SttDiffCurrCalDlg::UpdateUsed_ComboBox()
{
	if (!m_pHightUsed_ComboBox || !m_pLowerUsed_ComboBox)
	{
		return;
	}


	if (m_astrCurrentUsedList.size() <= 1)
	{		
		m_pHightUsed_ComboBox->setCurrentIndex(0);
		m_pLowerUsed_ComboBox->setCurrentIndex(0);
	}
	else
	{
		QList<QScrollComboBox*> pComboBoxList;
		pComboBoxList.append(m_pHightUsed_ComboBox);
		pComboBoxList.append(m_pLowerUsed_ComboBox);

		QList<QString> pSelectedValues;
		pSelectedValues.clear();
		// 获取当前选中的项
		foreach(QScrollComboBox* pComboBox, pComboBoxList)
		{
			QString currentText = pComboBox->currentText();
			pSelectedValues.append(currentText);
		}
	
		foreach(QScrollComboBox* pComboBox, pComboBoxList)
		{
			QString currentText = pComboBox->currentText();
			pComboBox->blockSignals(true);
			pComboBox->clear();
			foreach(const QString& value, m_astrCurrentUsedList)
			{
				if (!pSelectedValues.contains(value) || value == currentText)
				{
					pComboBox->addItem(value);
				}
			}

			int nIndex = pComboBox->findText(currentText);
			if (nIndex >= 0)
			{
				pComboBox->setCurrentIndex(nIndex);
			}
			pComboBox->blockSignals(false);
		}
	}

}

void SttDiffCurrCalDlg::slot_OKClicked()
{
	m_pDiffCurrCalParas->m_fId = m_pId_FloatLineEdit->GetValue();
	m_pDiffCurrCalParas->m_fIr = m_pIr_FloatLineEdit->GetValue();
	m_pDiffCurrCalParas->m_nIrEquation = m_pIrEquation_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_fK1 = m_pK1_FloatLineEdit->GetValue();
	m_pDiffCurrCalParas->m_fK2 = m_pK2_FloatLineEdit->GetValue();
	m_pDiffCurrCalParas->m_nCTPoint = m_pCTPoint_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_fKph = m_pKph_FloatLineEdit->GetValue();
	m_pDiffCurrCalParas->m_fKpl = m_pKpl_FloatLineEdit->GetValue();

	m_pDiffCurrCalParas->m_nWindH = m_pWindH_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nWindL = m_pWindL_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nTransGroupMode = m_pTransGroupMode_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nJXFactor = m_pJXFactor_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nPhCorrectMode = m_pPhCorrectMode_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nTestPhase = m_pTestPhase_ComboBox->currentIndex();
// 	m_pDiffCurrCalParas->m_nHightUsed = m_pHightUsed_ComboBox->currentIndex();
// 	m_pDiffCurrCalParas->m_nLowerUsed = m_pLowerUsed_ComboBox->currentIndex();

	CString strCbbText = m_pHightUsed_ComboBox->currentText();
	if (strCbbText == _T("空"))
	{
		m_pDiffCurrCalParas->m_nHightUsed = -1;
	}
	else
	{
		CString strNum = strCbbText.mid(1);
		m_pDiffCurrCalParas->m_nHightUsed = CString_To_long(strNum)-1;
	}

	strCbbText = m_pLowerUsed_ComboBox->currentText();
	if (strCbbText == _T("空"))
	{
		m_pDiffCurrCalParas->m_nLowerUsed = -1;
	}
	else
	{
		CString strNum = strCbbText.mid(1);
		m_pDiffCurrCalParas->m_nLowerUsed = CString_To_long(strNum) - 1;
	}
	m_nHeightUsedIndex = m_pDiffCurrCalParas->m_nHightUsed;
	m_nLowerUsedIndex = m_pDiffCurrCalParas->m_nLowerUsed;

	m_oDiffCalTool.Init();
	m_oDiffCalTool.InitSysParas(g_oLocalSysPara.m_fAC_CurMax,g_oSystemParas.m_fFNom);
	int nAngleMode = m_pPhCorrectMode_ComboBox->currentIndex();
	int nIbiasCal = m_pIrEquation_ComboBox->currentIndex();
	int nWindH = m_pWindH_ComboBox->currentIndex();
	int nWindL = m_pWindL_ComboBox->currentIndex();
	float fK1 = m_pK1_FloatLineEdit->GetValue();
	float fK2 = m_pK2_FloatLineEdit->GetValue();
	int nConnectMode = m_pTransGroupMode_ComboBox->currentIndex();
	int nPhase = m_pTestPhase_ComboBox->currentIndex();
	int nCTStarPoint = m_pCTPoint_ComboBox->currentIndex();
	int nJXFactor = m_pJXFactor_ComboBox->currentIndex();

 	m_oDiffCalTool.InitParas6I(0,5,0,0,nAngleMode,nIbiasCal,nWindH,0,nWindL,0,
 		fK1,fK2,nConnectMode,nPhase,nCTStarPoint,nJXFactor);

	m_oDiffCalTool.InitParas_SetBalanceFactors(m_pKph_FloatLineEdit->GetValue(),1,m_pKpl_FloatLineEdit->GetValue());
	float fCurrScanVal = m_pId_FloatLineEdit->GetValue();
	float fIbias = m_pIr_FloatLineEdit->GetValue();

	m_oDiffCalTool.CurrentCal(&fCurrScanVal,fIbias);

	this->accept();
}

void SttDiffCurrCalDlg::slot_CancelClicked()
{
	close();
}

void SttDiffCurrCalDlg::slot_CurrGroupChanged(int nCurrIndex)
{
// 	if (m_pHightUsed_ComboBox->currentIndex() != m_pLowerUsed_ComboBox->currentIndex())
// 	{
// 		m_nHeightUsedIndex = m_pHightUsed_ComboBox->currentIndex();
// 		m_nLowerUsedIndex = m_pLowerUsed_ComboBox->currentIndex();
// 		return;
// 	}
// 
// 	QScrollComboBox* pUsed_ComboBox = qobject_cast<QScrollComboBox*>(sender());
// 
// 	if (pUsed_ComboBox == m_pHightUsed_ComboBox)
// 	{
// 		m_pHightUsed_ComboBox->setCurrentIndex(m_nHeightUsedIndex);
// 	}
// 	else if (pUsed_ComboBox == m_pLowerUsed_ComboBox)
// 	{
// 		m_pLowerUsed_ComboBox->setCurrentIndex(m_nLowerUsedIndex);
// 	}
	//2024-8-21 wuxinyi 修改高压/低压下拉框选择一个，另一个下拉框不显示该选项
 	UpdateUsed_ComboBox();
}