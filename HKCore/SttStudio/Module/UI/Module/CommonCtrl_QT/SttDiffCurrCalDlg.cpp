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
	//strTmp = _T("��������");
	setWindowTitle(g_sLangTxt_State_Difflowcalculation);//��������  LCQ
	
	resize(700, 450);
	m_pParasSet_GridLayout = new QGridLayout;
	m_pParasSet_GridLayout->setSpacing(20);//�����м��
	m_pParasSet_GridLayout->setColumnMinimumWidth(3, 250);
	m_pAllVLayout = new QVBoxLayout(this);

	//strTmp = _T("�����(A)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_DiffCurrentA , "State_DiffCurrentA");//"�����(A)-LCQ
	m_pId_Label = new QLabel(g_sLangTxt_State_DiffCurrentA);
	//strTmp = _T("�ƶ�����(A)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_BrakCurrentA, "State_BrakCurrentA");//�ƶ�����(A)-LCQ
	m_pIr_Label = new QLabel(g_sLangTxt_State_BrakCurrentA);
	//strTmp = _T("�ƶ�����");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Bequation, "State_Bequation");//�ƶ�����-LCQ
	m_pIrEquation_Label = new QLabel(g_sLangTxt_State_Bequation);
	strTmp = _T("K1");
	m_pK1_Label = new QLabel(strTmp);
	strTmp = _T("K2");
	m_pK2_Label = new QLabel(strTmp);
	//strTmp = _T("CT����");
	//xlang_GetLangStrByFile(g_sLangTxt_State_CTpolarity , "State_CTpolarity");//CT����-LCQ
	m_pCTPoint_Label = new QLabel(g_sLangTxt_State_CTpolarity );
	//strTmp = _T("��ѹ��ƽ��ϵ��");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Hsbalancefactor , "State_Hsbalancefactor");//��ѹ��ƽ��ϵ��-LCQ
	m_pKph_Label = new QLabel(g_sLangTxt_State_Hsbalancefactor );
	//strTmp = _T("��ѹ��ƽ��ϵ��");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Lsbalancefactor, "State_Lsbalancefactor");//��ѹ��ƽ��ϵ��-LCQ
	m_pKpl_Label = new QLabel(g_sLangTxt_State_Lsbalancefactor);


	//strTmp = _T("��ѹ�����������ʽ");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Hswindwirtype, "State_Hswindwirtype");//��ѹ�����������ʽ-LCQ
	m_pWindH_Label = new QLabel(g_sLangTxt_State_Hswindwirtype);
	//strTmp = _T("��ѹ�����������ʽ");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Lswindwirtype, "State_Lswindwirtype");//��ѹ�����������ʽ-LCQ
	m_pWindL_Label = new QLabel(g_sLangTxt_State_Lswindwirtype);
	//strTmp = _T("�����ǲ�(�ӵ���)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_HbdiffAngularwind, "State_HbdiffAngularwind");//�����ǲ�(�ӵ���)-LCQ
	m_pTransGroupMode_Label = new QLabel(g_sLangTxt_State_HbdiffAngularwind);
	//strTmp = _T("ƽ��ϵ������");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Bfactorcalculation, "State_Bfactorcalculation");//ƽ��ϵ������-LCQ
	m_pJXFactor_Label = new QLabel(g_sLangTxt_State_Bfactorcalculation);
	//strTmp = _T("У��ѡ��");
	//xlang_GetLangStrByFile(g_sLangTxt_State_Correctionselection, "State_Correctionselection");//У��ѡ��-LCQ
	m_pPhCorrectMode_Label = new QLabel(g_sLangTxt_State_Correctionselection);
	//strTmp = _T("������");
	//xlang_GetLangStrByFile( g_sLangTxt_State_Testphase, "State_Testphase");//������-LCQ
	m_pTestPhase_Label = new QLabel( g_sLangTxt_State_Testphase);
	//strTmp = _T("��ѹ��Ӧ����(I1)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_FirHVoltageSide, "State_FirHVoltageSide");//��ѹ��Ӧ����(I1)-LCQ
	m_pHightUsed_Label = new QLabel(g_sLangTxt_State_FirHVoltageSide);
	//strTmp = _T("��ѹ��Ӧ����(I2)");
	//xlang_GetLangStrByFile(g_sLangTxt_State_SecHVoltageSide, "State_SecHVoltageSide");//��ѹ��Ӧ����(I2)-LCQ
	m_pLowerUsed_Label = new QLabel(g_sLangTxt_State_SecHVoltageSide);

	m_pId_FloatLineEdit = new QFloatLineEdit;
	m_pId_FloatLineEdit->InitCoverage(0,100);
	m_pIr_FloatLineEdit = new QFloatLineEdit;
	m_pIr_FloatLineEdit->InitCoverage(0,100);
	m_pIrEquation_ComboBox = new QScrollComboBox;
	m_astrEquationList<<tr("Ir=(|I1-I2|)/K1 or Ir=(|I1+I2|)/K1")<<tr("Ir=(|I1|+|I2|*K2)/K1")<<tr("Ir=max(|I1|,|I2|)")\
		<<tr("Ir=(|Id-|I1|-|I2||)/K1")<<tr("Ir=|I2|");/*<<tr("Sqrt(K1*I1*I2*Cos(��))");*/
	strTmp = _T("Sqrt(K1*I1*I2*Cos(��))");
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
	strTmp = _T("��");
	m_astrWindList<<strTmp;
	//m_astrWindList<<tr("Y")<<tr("��");
	//strTmp = _T("12��");
	xlang_GetLangStrByFile(g_sLangTxt_State_12Oclock, "State_12Oclock");//12��-LCQ
	m_astrTransGroupMode<<g_sLangTxt_State_12Oclock;
	int nIndex = 1;
	CString strIndex;
	CString strPoint;
	//strPoint = _T("��");
    xlang_GetLangStrByFile(strPoint, "State_Oclock");//��-LCQ
	while (nIndex <= 11)
	{
		strIndex.Format(_T("%d"), nIndex);
		strTmp = strIndex + strPoint;
		m_astrTransGroupMode<<strTmp;
		nIndex++;
	}

	/*m_astrTransGroupMode<<tr("12��")<<tr("1��")<<tr("2��")<<tr("3��")<<tr("4��")\
		<<tr("5��")<<tr("6��")<<tr("7��")<<tr("8��")<<tr("9��")<<tr("10��")<<tr("11��");*/

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

//	m_astrCurrentUsedList<<tr("��1")<<tr("��2")<<tr("��3")<<tr("��4")<<tr("��5")<<tr("��6");
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
	m_pLowerUsed_ComboBox->addItems(m_astrCurrentUsedList);
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

	m_pOK_PushButton = new QPushButton(this);
	//strTmp = _T("ȷ��");
	m_pOK_PushButton->setText(g_sLangTxt_OK/*tr("ȷ��")*/);
	m_pCancel_PushButton = new QPushButton(this);
	//strTmp = _T("ȡ��");
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel/*tr("ȡ��")*/);

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

	if (nCurrGroupNum<2)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("��ǰ��������Ϊ(%ld),������Ҫ2��������ܽ��в�������."),nCurrGroupNum); 
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_CurbanksatleastTwo.GetString(),nCurrGroupNum);//   3.13 lcq
		m_pOK_PushButton->setEnabled(false);
	}

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
	m_pDiffCurrCalParas->m_nHightUsed = m_pHightUsed_ComboBox->currentIndex();
	m_pDiffCurrCalParas->m_nLowerUsed = m_pLowerUsed_ComboBox->currentIndex();

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
	if (m_pHightUsed_ComboBox->currentIndex() != m_pLowerUsed_ComboBox->currentIndex())
	{
		m_nHeightUsedIndex = m_pHightUsed_ComboBox->currentIndex();
		m_nLowerUsedIndex = m_pLowerUsed_ComboBox->currentIndex();
		return;
	}

	QScrollComboBox* pUsed_ComboBox = qobject_cast<QScrollComboBox*>(sender());

	if (pUsed_ComboBox == m_pHightUsed_ComboBox)
	{
		m_pHightUsed_ComboBox->setCurrentIndex(m_nHeightUsedIndex);
	}
	else if (pUsed_ComboBox == m_pLowerUsed_ComboBox)
	{
		m_pLowerUsed_ComboBox->setCurrentIndex(m_nLowerUsedIndex);
	}
}