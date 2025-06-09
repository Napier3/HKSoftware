#include "SttReplayModuleChWidget.h"
#include "SttReplayParaSetWidget.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Controls/SttCheckBox.h"
#include "../../Module/XLangResource_Native.h"
#include"../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CFont *g_pSttGlobalFont;

CSttReplayModuleChWidget::CSttReplayModuleChWidget(int nModuleIndex,CSttModuleComtradeBind *pModuleInfo,QWidget *pParent)
:QWidget(pParent)
{
	m_nModuleIndex = nModuleIndex;
	m_pModuleInfo = pModuleInfo;
	m_pParentWidget = pParent;

	initUI(); 
	initSignalSlots();
}

CSttReplayModuleChWidget::~CSttReplayModuleChWidget()
{

}

void CSttReplayModuleChWidget::initUI()
{
 	QFont oFont,Font;
 	oFont.setPixelSize(19);
	Font.setPixelSize(30);
 	setFont(oFont);
	m_pMainLayout = new QVBoxLayout(this);
	m_pHLayout_ReplayChs = new QHBoxLayout(this);

	m_pGridLayout_RcdChs = new QGridLayout;
	xlang_GetLangStrByFile(g_sLangTxt_Display,"Display");
	m_plbChanel = new QLabel(g_sLangTxt_Display);
    m_plbChanel->setFixedHeight(30);
	xlang_GetLangStrByFile(g_sLangTxt_AChannel,"AChannel");
	m_plbChanelA = new QLabel(g_sLangTxt_AChannel);
    m_plbChanelA->setFixedHeight(30);
	xlang_GetLangStrByFile(g_sLangTxt_BChannel,"BChannel");
	m_plbChanelB = new QLabel(g_sLangTxt_BChannel);
    m_plbChanelB->setFixedHeight(30);

	m_pGridLayout_RcdChs->addWidget(m_plbChanel, 0, 0, 1, 2,Qt::AlignHCenter);
	m_pGridLayout_RcdChs->addWidget(m_plbChanelA, 0, 2, 1, 4,Qt::AlignHCenter);
	m_pGridLayout_RcdChs->addWidget(m_plbChanelB, 0, 7, 1, 4,Qt::AlignHCenter);

	QCheckBox *pChSel = NULL;
	QScrollComboBox *pAChSel = NULL;
	QScrollComboBox *pBChSel = NULL;
	QLabel *plbOptrSub = NULL;
	QLabel *plbOptrDiv = NULL;
	QLineEdit *pedtK = NULL;

	POS pos = m_pModuleInfo->GetHeadPosition();
	CSttModuleChComtradeBind *pCh = NULL;
	long nChIndex = 1;
	CString strText;

	while(pos != NULL)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetNext(pos);
		strText.Format(_T("%s= ("),pCh->m_strName.GetString());
		strText.Replace("_","-");
		pChSel = new QSttCheckBox(strText);
		pChSel->setMinimumHeight(30);
		
		m_ChSelList.append(pChSel);
		m_pGridLayout_RcdChs->addWidget(pChSel, nChIndex, 0, 1, 2);

		pAChSel = new QScrollComboBox();
		pAChSel->setMinimumWidth(200);
		pAChSel->setMinimumHeight(30);
		pAChSel->setMaxVisibleItems(12);
		m_AChSelList.append(pAChSel);
		m_pGridLayout_RcdChs->addWidget(pAChSel, nChIndex, 2, 1, 4);

		plbOptrSub = new QLabel(tr("-"));
		plbOptrSub->setMinimumHeight(30);
		plbOptrSub->setFont(Font);
		m_OptrSubLabelList.append(plbOptrSub);
		m_pGridLayout_RcdChs->addWidget(plbOptrSub, nChIndex, 6, 1, 1,Qt::AlignHCenter);
//		m_pGridLayout_RcdChs->setAlignment(plbOptrSub,Qt::AlignCenter);
//		plbOptrSub->setFixedWidth(30);
//		plbOptrSub->setAlignment(Qt::AlignCenter);
		

		pBChSel = new QScrollComboBox();
		pBChSel->setMinimumWidth(200);
		pBChSel->setMinimumHeight(30);
		pBChSel->setMaxVisibleItems(12);
		m_BChSelList.append(pBChSel);
		m_pGridLayout_RcdChs->addWidget(pBChSel, nChIndex, 7, 1, 4);

		strText = _T(")÷");
		plbOptrDiv = new QLabel(this);
		plbOptrDiv->setText(strText);
		plbOptrDiv->setMinimumHeight(30);
		plbOptrDiv->setAlignment(Qt::AlignCenter);
		m_OptrDivLabelList.append(plbOptrDiv);
		m_pGridLayout_RcdChs->addWidget(plbOptrDiv, nChIndex, 11, 1, 1);

//		m_pGridLayout_RcdChs->setRowMinimumHeight(nChIndex,50);

		pedtK = new QSttLineEdit(this);
		pedtK->setAlignment(Qt::AlignHCenter);
		pedtK->setMinimumHeight(30);
		pedtK->setFixedWidth(70);
		pedtK->setText(tr("1.0"));
		pedtK->setFont(*g_pSttGlobalFont);
		m_KEditList.append(pedtK);
		m_pGridLayout_RcdChs->addWidget(pedtK, nChIndex, 12, 1, 2,Qt::AlignHCenter);

		nChIndex++;
	}

	m_pGridLayout_RcdChs->setHorizontalSpacing(1);
// 	m_pGridLayout_RcdChs->setRowMinimumHeight(0,30);
// 	m_pGridLayout_RcdChs->setRowMinimumHeight(1,30);
// 	m_pGridLayout_RcdChs->setRowMinimumHeight(2,30);
// 	m_pGridLayout_RcdChs->setRowMinimumHeight(3,30);
// 	m_pGridLayout_RcdChs->setRowStretch(0,10);
// 	m_pGridLayout_RcdChs->setRowStretch(1,20);
// 	m_pGridLayout_RcdChs->setRowStretch(2,10);
// 	m_pGridLayout_RcdChs->setRowStretch(3,20);
// 	m_pGridLayout_RcdChs->setRowStretch(4,10);
// 	m_pGridLayout_RcdChs->setRowStretch(5,10);
//	m_pGridLayout_RcdChs->setSpacing(20);
	m_pHLayout_ReplayChs->addLayout(m_pGridLayout_RcdChs);
//	m_pHLayout_ReplayChs->addStretch();

	m_pVLayout_MaxMinValues = new QVBoxLayout(this);
	m_pOpenRcdFileBtn = new QPushButton;
	xlang_GetLangStrByFile(g_sLangTxt_Open_Record,"Open_Record");
	m_pOpenRcdFileBtn->setText(g_sLangTxt_Open_Record);
	m_pVLayout_MaxMinValues->addWidget(m_pOpenRcdFileBtn);
	m_pGridLayout_MaxMinValues = new QGridLayout(this);

	strText = _T("UMax(V)：");
	m_pVolMax_Label = new QLabel(this);
	m_pVolMax_Label->setText(strText);
	m_pVolMax_Edit = new QFloatLineEdit(this);
	m_pVolMax_Edit->InitCoverage(0,999999,3);
	m_pVolMax_Edit->SetValue(0.0f);
//	m_pVolMax_Edit->setDisabled(true);
	strText = _T("IMax(A)：");
	m_pCurMax_Label = new QLabel(this);
	m_pCurMax_Label->setText(strText);
	m_pCurMax_Edit = new QFloatLineEdit(this);
	m_pCurMax_Edit->InitCoverage(0,999999,3);
	m_pCurMax_Edit->SetValue(0.0f);
//	m_pCurMax_Edit->setDisabled(true);

	strText = _T("T1(s)：");
	m_pTimeA_Label = new QLabel(this);
	m_pTimeA_Label->setText(strText);
	m_pTimeA_Edit = new QFloatLineEdit(this);
	m_pTimeA_Edit->InitCoverage(0,999999,3);
	m_pTimeA_Edit->SetValue(0.0f);
//	m_pTimeA_Edit->setDisabled(true);

	strText = _T("T2(s)：");
	m_pTimeB_Label = new QLabel(this);
	m_pTimeB_Label->setText(strText);
	m_pTimeB_Edit = new QFloatLineEdit(this);
	m_pTimeB_Edit->InitCoverage(0,999999,3);
	m_pTimeB_Edit->SetValue(0.0f);
//	m_pTimeB_Edit->setDisabled(true);

	strText = _T("△T(s)：");
	m_pTimeDiff_Label = new QLabel(this);
	m_pTimeDiff_Label->setText(strText);
	m_pTimeDiff_Edit = new QFloatLineEdit(this);
	m_pTimeDiff_Edit->InitCoverage(-999999,999999,3);
	m_pTimeDiff_Edit->SetValue(0.0f);
//	m_pTimeDiff_Edit->setDisabled(true);

	m_pVolMax_Edit->setFixedWidth(90);
	m_pCurMax_Edit->setFixedWidth(90);
	m_pTimeA_Edit->setFixedWidth(90);
	m_pTimeB_Edit->setFixedWidth(90);
	m_pTimeDiff_Edit->setFixedWidth(90);

	m_pVolMax_Edit->setReadOnly(true);
	m_pCurMax_Edit->setReadOnly(true);
	m_pTimeA_Edit->setReadOnly(true);
	m_pTimeB_Edit->setReadOnly(true);
	m_pTimeDiff_Edit->setReadOnly(true);

	m_pVolMax_Edit->setFocusPolicy(Qt::NoFocus);
	m_pCurMax_Edit->setFocusPolicy(Qt::NoFocus);
	m_pTimeA_Edit->setFocusPolicy(Qt::NoFocus);
	m_pTimeB_Edit->setFocusPolicy(Qt::NoFocus);
	m_pTimeDiff_Edit->setFocusPolicy(Qt::NoFocus);

	m_pVolMax_Label->setAlignment(Qt::AlignRight);
	m_pCurMax_Label->setAlignment(Qt::AlignRight);
	m_pTimeA_Label->setAlignment(Qt::AlignRight);
	m_pTimeB_Label->setAlignment(Qt::AlignRight);
	m_pTimeDiff_Label->setAlignment(Qt::AlignRight);

	m_pVolMax_Edit->setAlignment(Qt::AlignHCenter);
	m_pCurMax_Edit->setAlignment(Qt::AlignHCenter);
	m_pTimeA_Edit->setAlignment(Qt::AlignHCenter);
	m_pTimeB_Edit->setAlignment(Qt::AlignHCenter);
	m_pTimeDiff_Edit->setAlignment(Qt::AlignHCenter);

	m_pGridLayout_MaxMinValues->addWidget(m_pVolMax_Label, 0, 0, 1, 1,Qt::AlignRight);
	m_pGridLayout_MaxMinValues->addWidget(m_pVolMax_Edit, 0, 1, 1, 1,Qt::AlignHCenter);
	m_pGridLayout_MaxMinValues->addWidget(m_pCurMax_Label, 1, 0, 1, 1,Qt::AlignRight);
	m_pGridLayout_MaxMinValues->addWidget(m_pCurMax_Edit, 1, 1, 1, 1,Qt::AlignHCenter);

	m_pGridLayout_MaxMinValues->addWidget(m_pTimeA_Label, 2, 0, 1, 1,Qt::AlignRight);
	m_pGridLayout_MaxMinValues->addWidget(m_pTimeA_Edit, 2, 1, 1, 1,Qt::AlignHCenter);

	m_pGridLayout_MaxMinValues->addWidget(m_pTimeB_Label, 3, 0, 1, 1,Qt::AlignRight);
	m_pGridLayout_MaxMinValues->addWidget(m_pTimeB_Edit, 3, 1, 1, 1,Qt::AlignHCenter);

	m_pGridLayout_MaxMinValues->addWidget(m_pTimeDiff_Label, 4, 0, 1, 1,Qt::AlignRight);
	m_pGridLayout_MaxMinValues->addWidget(m_pTimeDiff_Edit, 4, 1, 1, 1,Qt::AlignHCenter);
//	m_pGridLayout_MaxMinValues->setVerticalSpacing(10);//设置垂直间距
	m_pGridLayout_MaxMinValues->setHorizontalSpacing(10);//设置水平间距

// 	m_pVolMax_Label->setFixedWidth(120);;
// 	m_pCurMax_Label->setFixedWidth(120);;
// 	m_pTimeA_Label->setFixedWidth(120);;
// 	m_pTimeB_Label->setFixedWidth(120);;
// 	m_pTimeDiff_Label->setFixedWidth(120);
// 
// 	m_pGridLayout_MaxMinValues->setAlignment(m_pVolMax_Label,Qt::AlignRight);
// 	m_pGridLayout_MaxMinValues->setAlignment(m_pCurMax_Label,Qt::AlignRight);
// 	m_pGridLayout_MaxMinValues->setAlignment(m_pTimeA_Label,Qt::AlignRight);
// 	m_pGridLayout_MaxMinValues->setAlignment(m_pTimeB_Label,Qt::AlignRight);
// 	m_pGridLayout_MaxMinValues->setAlignment(m_pTimeDiff_Label,Qt::AlignRight);


// 	m_pGridLayout_MaxMinValues->setRowSpacing(0,10);
// 	m_pGridLayout_MaxMinValues->setRowSpacing(1,10);
// 	m_pGridLayout_MaxMinValues->setRowStretch(0,1);
// 	m_pGridLayout_MaxMinValues->setRowStretch(1,2);
//	m_pGridLayout_MaxMinValues->setContentsMargins(0,0,0,0);
//	m_pGridLayout_MaxMinValues->setSpacing(30);
	//CString strTemp = "瞬时值显示";
	xlang_GetLangStrByFile(g_sLangTxt_Instant,"Instant");
	m_pMaxMinGroupBox = new QGroupBox(g_sLangTxt_Instant);
	m_pMaxMinGroupBox->setAlignment(Qt::AlignHCenter);
	m_pMaxMinGroupBox->setLayout(m_pGridLayout_MaxMinValues);
	m_pVLayout_MaxMinValues->addWidget(m_pMaxMinGroupBox);
//	m_pVLayout_MaxMinValues->addLayout(m_pGridLayout_MaxMinValues);
	m_pHLayout_ReplayChs->addLayout(m_pVLayout_MaxMinValues);
	m_pHLayout_ReplayChs->setStretchFactor(m_pGridLayout_RcdChs, 6);
	m_pHLayout_ReplayChs->setStretchFactor(m_pVLayout_MaxMinValues, 1);

	m_pMainLayout->addLayout(m_pHLayout_ReplayChs);
	m_pHLayout_PT_CT_Rate = new QHBoxLayout;
	xlang_GetLangStrByFile(g_sLangTxt_PT ,"PT");
	m_pPTRate_Label = new QLabel(g_sLangTxt_PT);
	m_pHLayout_PT_CT_Rate->addWidget(m_pPTRate_Label);
	m_pPTPrim_Edit = new QFloatLineEdit(this);
	m_pHLayout_PT_CT_Rate->addWidget(m_pPTPrim_Edit);

	m_pPTDivision_Label = new QLabel("/");
	m_pHLayout_PT_CT_Rate->addWidget(m_pPTDivision_Label);
	m_pPTSecond_Edit = new QFloatLineEdit(this);
	m_pHLayout_PT_CT_Rate->addWidget(m_pPTSecond_Edit);

	xlang_GetLangStrByFile(g_sLangTxt_CT ,"CT");
	m_pCTRate_Label = new QLabel(g_sLangTxt_CT);
	m_pHLayout_PT_CT_Rate->addWidget(m_pCTRate_Label);
	m_pCTPrim_Edit = new QFloatLineEdit(this);
	m_pHLayout_PT_CT_Rate->addWidget(m_pCTPrim_Edit);

	m_pCTDivision_Label = new QLabel("/");
	m_pHLayout_PT_CT_Rate->addWidget(m_pCTDivision_Label);
	m_pCTSecond_Edit = new QFloatLineEdit(this);
	m_pHLayout_PT_CT_Rate->addWidget(m_pCTSecond_Edit);
	m_pHLayout_PT_CT_Rate->addStretch();

	m_pMainLayout->addLayout(m_pHLayout_PT_CT_Rate);
	m_pMainLayout->setSpacing(40);
	setLayout(m_pMainLayout);

	m_pPTPrim_Edit->setAlignment(Qt::AlignHCenter);
	m_pPTPrim_Edit->InitCoverage_EditFinished(0.001,99999,3);
	m_pPTPrim_Edit->InitUnit("V");
	m_pPTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0]);
	m_pPTSecond_Edit->setAlignment(Qt::AlignHCenter);
	m_pPTSecond_Edit->InitCoverage_EditFinished(0.001,99999,3);
	m_pPTSecond_Edit->InitUnit("V");
	m_pPTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1]);
	m_pCTPrim_Edit->setAlignment(Qt::AlignHCenter);
	m_pCTPrim_Edit->InitCoverage_EditFinished(0.001,99999,3);
	m_pCTPrim_Edit->InitUnit("A");
	m_pCTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0]);
	m_pCTSecond_Edit->setAlignment(Qt::AlignHCenter);
	m_pCTSecond_Edit->InitCoverage_EditFinished(0.001,99999,3);
	m_pCTSecond_Edit->InitUnit("A");
	m_pCTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1]);

	connect(m_pPTPrim_Edit, SIGNAL(editingFinished()), this, SLOT(slot_ChangedPT1()));
	connect(m_pPTSecond_Edit, SIGNAL(editingFinished()), this, SLOT(slot_ChangedPT2()));
	connect(m_pCTPrim_Edit, SIGNAL(editingFinished()), this, SLOT(slot_ChangedCT1()));
	connect(m_pCTSecond_Edit, SIGNAL(editingFinished()), this, SLOT(slot_ChangedCT2()));

#ifdef _PSX_QT_LINUX_
	connect(m_pPTPrim_Edit,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pPTSecond_Edit,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pCTPrim_Edit,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pCTSecond_Edit,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
#endif

	if(m_pModuleInfo->IsDigitalTypeModule())
	{
		m_pPTPrim_Edit->hide();
		m_pPTSecond_Edit->hide();
		m_pCTPrim_Edit->hide();
		m_pCTSecond_Edit->hide();
		m_pPTRate_Label->hide();
		m_pPTDivision_Label->hide();
		m_pCTRate_Label->hide();		
		m_pCTDivision_Label->hide();
	}

	if (g_pSttGlobalFont != NULL)
	{
		m_pOpenRcdFileBtn->setFont(*g_pSttGlobalFont);
	}

	SetReplayModuleFont();
}

void CSttReplayModuleChWidget::SetReplayModuleFont()
{
	m_pVolMax_Edit->setFont(*g_pSttGlobalFont);
	m_pCurMax_Edit->setFont(*g_pSttGlobalFont);
	m_pTimeA_Edit->setFont(*g_pSttGlobalFont);
	m_pTimeB_Edit->setFont(*g_pSttGlobalFont);
	m_pTimeDiff_Edit->setFont(*g_pSttGlobalFont);

	m_pOpenRcdFileBtn->setFont(*g_pSttGlobalFont);
	

	m_pPTPrim_Edit->setFont(*g_pSttGlobalFont);
	m_pPTSecond_Edit->setFont(*g_pSttGlobalFont);
	m_pCTPrim_Edit->setFont(*g_pSttGlobalFont);
	m_pCTSecond_Edit->setFont(*g_pSttGlobalFont);


}


void CSttReplayModuleChWidget::OnModuleChChanged(int nModuleIndex,int nChIndex)
{
	//需要注意的是，如果是故障回放之前，由AnalogData生成ReplayBuf，始终从AnalogData开始位置解析

    int nRealModuleIndex = GetModulesComtradeBindIndex();
    int nRealChIndex = GetRealChIndex(nRealModuleIndex,nChIndex);

	//重新计算生成指定通道ReplayBuf
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.UpdateChReplayBuf(nRealModuleIndex,nRealChIndex/*,TRUE*/);

	//重新计算最大值
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.CalcReplayChMaxValue(nRealModuleIndex,nRealChIndex);
	//单通道刷新
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nReplayBufFlush = CMTRD_FLUSH_TYPE_FlushOneCh;

	emit sig_ModuleChChanged(m_nModuleIndex,nChIndex);
	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::slot_ChSelChanged(int nIndex)
{
	QCheckBox *pSelCh = (QCheckBox *)sender();
	int nChIndex = m_ChSelList.indexOf(pSelCh);

	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("pCh(%d)"),pCh->GetClassID());
	ASSERT(pCh != NULL);

	if (pSelCh->isChecked())
	{
		if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetTotalChs_SelectedModule() >= BIG_COMTRADE_REPLAY_CH_MAX_NUM)
		{
			pSelCh->setCheckState(Qt::Unchecked);
			return;
		}

		pCh->m_nChSelected = 1;
		
	}
	else
	{
		pCh->m_nChSelected = 0;
	}

	//通知界面刷新指定模块指定通道
	OnModuleChChanged(m_nModuleIndex,nChIndex);

	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::slot_AChSelChanged(int nIndex)
{
	CSttReplayParaSetWidget *pParaSetWidget = (CSttReplayParaSetWidget *)GetParaSetWidget()/*(CSttReplayParaSetWidget*)m_pParentWidget*/;
	ASSERT(pParaSetWidget);
	QScrollComboBox *pASelCh = (QScrollComboBox *)sender();
	int nChIndex = m_AChSelList.indexOf(pASelCh);

	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	ASSERT(pCh != NULL);

	if (pCh->IsModuleType_U())
	{
		pCh->InitCh_A(pParaSetWidget->GetComtradeAnalogU(nIndex-1));
	} 
	else
	{
		pCh->InitCh_A(pParaSetWidget->GetComtradeAnalogI(nIndex-1));
	}

	//通知界面刷新指定模块指定通道
	OnModuleChChanged(m_nModuleIndex,nChIndex);
}

void CSttReplayModuleChWidget::slot_BChSelChanged(int nIndex)
{
	CSttReplayParaSetWidget *pParaSetWidget = (CSttReplayParaSetWidget *)GetParaSetWidget()/*(CSttReplayParaSetWidget*)m_pParentWidget*/;
	QScrollComboBox *pBSelCh = (QScrollComboBox *)sender();
	int nChIndex = m_BChSelList.indexOf(pBSelCh);

	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	ASSERT(pCh != NULL);

	if (pCh->IsModuleType_U())
	{
		pCh->InitCh_B(pParaSetWidget->GetComtradeAnalogU(nIndex-1));
	} 
	else
	{
		pCh->InitCh_B(pParaSetWidget->GetComtradeAnalogI(nIndex-1));
	}

	//通知界面刷新指定模块指定通道
	OnModuleChChanged(m_nModuleIndex,nChIndex);
}

void CSttReplayModuleChWidget::slot_KChanged()
{
	QLineEdit *pedtK = (QLineEdit *)sender();
	int nChIndex = m_KEditList.indexOf(pedtK);
	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	ASSERT(pCh != NULL);

	pCh->m_dK = pedtK->text().toFloat();
	if (pCh->m_dK <= 0)
	{
		pCh->m_dK = 0.01;
	}

	CString strVal = QString::number(pCh->m_dK, 'f', 2);
	pedtK->setText(strVal);

	//通知界面刷新指定模块指定通道
	OnModuleChChanged(m_nModuleIndex,nChIndex);

// 	if (m_pParentWidget != NULL)
// 	{
// 		((CSttReplayParaSetWidget*)m_pParentWidget)->UpdateUIMax();//更新当前界面最大最小值
// 	}

// 	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::initSignalSlots()
{
	int nChNum = m_ChSelList.size();

	for(int i=0; i<nChNum; i++)
	{
		connect(m_ChSelList.at(i),SIGNAL(stateChanged(int)),this,SLOT(slot_ChSelChanged(int)));
		connect(m_AChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_AChSelChanged(int)));
		connect(m_BChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BChSelChanged(int)));
		connect(m_KEditList.at(i), SIGNAL(editingFinished()), this, SLOT(slot_KChanged()));

#ifdef _PSX_QT_LINUX_
		connect(m_KEditList.at(i),SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
#endif
	}

	connect(m_pOpenRcdFileBtn, SIGNAL(clicked()), this, SLOT(slot_OpenRcdFileClicked()));
}

void CSttReplayModuleChWidget::slot_SttLineEditChanged()
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

// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void CSttReplayModuleChWidget::slot_FloatLineEditChanged()
{
	QFloatLineEdit* pEditLine = qobject_cast<QFloatLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->GetValue_String();

	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void CSttReplayModuleChWidget::slot_OpenRcdFileClicked()
{
	disconnect(m_pOpenRcdFileBtn, SIGNAL(clicked()), this, SLOT(slot_OpenRcdFileClicked()));
	((CSttReplayParaSetWidget*)m_pParentWidget)->slot_OpenRcdFileClicked();
	connect(m_pOpenRcdFileBtn, SIGNAL(clicked()), this, SLOT(slot_OpenRcdFileClicked()));
}

void CSttReplayModuleChWidget::uninitSignalSlots()
{
	int nChNum = m_ChSelList.size();
	for(int i=0; i<nChNum; i++)
	{
		disconnect(m_ChSelList.at(i),SIGNAL(stateChanged(int)),this,SLOT(slot_ChSelChanged(int)));
		disconnect(m_AChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_AChSelChanged(int)));
		disconnect(m_BChSelList.at(i),SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BChSelChanged(int)));
		disconnect(m_KEditList.at(i), SIGNAL(editingFinished()), this, SLOT(slot_KChanged()));

#ifdef _PSX_QT_LINUX_
		disconnect(m_KEditList.at(i),SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
#endif
	}
}

void CSttReplayModuleChWidget::SetChSelectList(const QStringList &oUChList,const QStringList &oIChList/*QStringList &oChSelectList*/)
{
	QStringList oUChListNew,oIChListNew;
	oUChListNew = oUChList;
	oIChListNew = oIChList;
	oUChListNew.insert(0,_T("0"));
	oIChListNew.insert(0,_T("0"));

	//更新界面
	uninitSignalSlots();

	QScrollComboBox *pAChSel = NULL;
	QScrollComboBox *pBChSel = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CDvmData *pChData = NULL;

	int nChNum = m_ChSelList.size();
	long nValue = 0;
	long nChIndexA = 0,nChIndexB = 0;

	for(int nIndex=0; nIndex<nChNum; nIndex++)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nIndex);
		pAChSel = m_AChSelList.at(nIndex);
		pBChSel = m_BChSelList.at(nIndex);
		pAChSel->clear();
		pBChSel->clear();
		//更新通道数据
		m_ChSelList.at(nIndex)->setChecked(pCh->m_nChSelected);

		if (pCh->IsModuleType_U())
		{
			pAChSel->addItems(oUChListNew);
			pBChSel->addItems(oUChListNew);
			nChIndexA = oUChListNew.indexOf(pCh->m_strComtradeChID_A);
			nChIndexB = oUChListNew.indexOf(pCh->m_strComtradeChID_B);
		} 
		else
		{
			pAChSel->addItems(oIChListNew);
			pBChSel->addItems(oIChListNew);
			nChIndexA = oIChListNew.indexOf(pCh->m_strComtradeChID_A);
			nChIndexB = oIChListNew.indexOf(pCh->m_strComtradeChID_B);
		}
		
		if (nChIndexA<0)
		{
			nChIndexA = 0;
		}

		if (nChIndexB<0)
		{
			nChIndexB = 0;
		}

		pAChSel->setCurrentIndex(nChIndexA);
		pBChSel->setCurrentIndex(nChIndexB);
		m_KEditList.at(nIndex)->setText(QString::number(pCh->m_dK, 'f', 2));
	}

	m_pPTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0]);
	m_pPTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1]);
	m_pCTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0]);
	m_pCTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1]);
	initSignalSlots();
}

long CSttReplayModuleChWidget::GetChSelectIndex(const CString &strChName)
{
	long nValue = 0;
	CExBaseList* pAnalogList = g_theBigComtradeTransPlay->GetAnalogs();
	CComtradeAnalogData *pAnalogData = (CComtradeAnalogData *)pAnalogList->FindByName(strChName);
	if (pAnalogData != NULL)
	{
		nValue = pAnalogData->m_nChannelIndex;
	}

	return nValue;
}

void CSttReplayModuleChWidget::UpdateEditData()
{
	int nChNum = m_KEditList.size();

	for(int i=0; i<nChNum; i++)
	{
		CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(i);
		ASSERT(pCh != NULL);

		pCh->m_dK = m_KEditList.at(i)->text().toFloat();
	
		if (pCh->m_dK <= 0)
		{
			pCh->m_dK = 0.01;
		}

		CString strVal = QString::number(pCh->m_dK, 'f', 2);
		m_KEditList.at(i)->setText(strVal);
	}
}

void CSttReplayModuleChWidget::setEnableStateUI(bool bEnable)
{
	m_plbChanel->setEnabled(bEnable);
	m_plbChanelA->setEnabled(bEnable);
	m_plbChanelB->setEnabled(bEnable);

	m_pPTPrim_Edit->setEnabled(bEnable);
	m_pPTSecond_Edit->setEnabled(bEnable);
	m_pCTPrim_Edit->setEnabled(bEnable);
	m_pCTSecond_Edit->setEnabled(bEnable);

	int nChNum = m_ChSelList.size();

	for(int nIndex=0; nIndex<nChNum; nIndex++)
	{
		m_ChSelList.at(nIndex)->setEnabled(bEnable);
		m_AChSelList.at(nIndex)->setEnabled(bEnable);
		m_BChSelList.at(nIndex)->setEnabled(bEnable);
		m_KEditList.at(nIndex)->setEnabled(bEnable);
	}

	m_pOpenRcdFileBtn->setEnabled(true);
}

void CSttReplayModuleChWidget::slot_ChangedPT1()
{
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0] = m_pPTPrim_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnPTChanged();
	((CSttReplayParaSetWidget*)m_pParentWidget)->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::slot_ChangedPT2()
{
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1] = m_pPTSecond_Edit->GetValue();;
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnPTChanged();
	((CSttReplayParaSetWidget*)m_pParentWidget)->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::slot_ChangedCT1()
{
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0] = m_pCTPrim_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnCTChanged();
	((CSttReplayParaSetWidget*)m_pParentWidget)->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::slot_ChangedCT2()
{
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1] = m_pCTSecond_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnCTChanged();
	((CSttReplayParaSetWidget*)m_pParentWidget)->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayModuleChWidget::UpdatePT_CT_Rates()
{
	m_pPTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0]);
	m_pPTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1]);
	m_pCTPrim_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0]);
	m_pCTSecond_Edit->SetValue(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1]);
}

void CSttReplayModuleChWidget::UpdateUIMax(double fUMax,double fIMax)
{
	m_pVolMax_Edit->SetValue(fUMax);
	m_pCurMax_Edit->SetValue(fIMax);
}

void CSttReplayModuleChWidget::UpdateTwoCursorTimeValues(double dValueA,double dValueB)
{
	m_pTimeA_Edit->SetValue(dValueA);
	m_pTimeB_Edit->SetValue(dValueB);
	m_pTimeDiff_Edit->SetValue(dValueB-dValueA);
}

void CSttReplayModuleChWidget::SetDefaultFocusCtrl()
{
	m_pOpenRcdFileBtn->setFocus();
}int CSttReplayModuleChWidget::GetModulesComtradeBindIndex()
{
	CString strModuleID = m_pModuleInfo->m_strModuleID;
	POS pos = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;
	int nCount = 0;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetNext(pos);

		if(strModuleID == pModule->m_strModuleID)
		{
			return nCount;
		}
		nCount++;

	}

	return -1;
}

int CSttReplayModuleChWidget::GetRealChIndex( int nRealModuleIndex,int nChIndex )
{
	if (!m_pModuleInfo)
	{
		return -1;
	}
	int nRealChIndex = 0;
	POS pos = m_pModuleInfo->GetHeadPosition();

	while (pos)
	{
		CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetNext(pos);

		if (nChIndex == nRealChIndex)
		{
			if(m_pModuleInfo->IsAnalogTypeModule() || m_pModuleInfo->IsWeekTypeModule() )
			{
				return nRealChIndex;
			}
			else if(m_pModuleInfo->IsDigitalTypeModule())
			{
				CSttModuleComtradeBind *m_pParentModule = (CSttModuleComtradeBind *)m_pModuleInfo->GetParent();
				if(!m_pParentModule)
				{
					return -1;
				}
				return m_pParentModule->FindIndexByID(pCh->m_strID);
			}
		}

		nRealChIndex++;
	}

	return -1;
}

QWidget * CSttReplayModuleChWidget::GetParaSetWidget()
{
	if(m_pModuleInfo->IsAnalogTypeModule() || m_pModuleInfo->IsWeekTypeModule())
	{
		return m_pParentWidget;
	}
	else
	{
		QSttReplayDigitalModuleWidget* pDigitalWidget = (QSttReplayDigitalModuleWidget*)m_pParentWidget;
		return pDigitalWidget->GetParaSetWidget();
	}
}