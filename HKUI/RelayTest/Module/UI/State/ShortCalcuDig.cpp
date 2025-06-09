#include "ShortCalcuDig.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../Controls/SttGroupBox.h"

ShortCalcuDig::ShortCalcuDig(CSttTestResourceBase *pSttTestResource
							 , tmt_channel *uiVOL,tmt_channel *uiCUR
							, ShortCalcuPara para,QWidget *parent)
	: QDialog(parent), ui(new Ui::ShortCalcuDig)
{
	ui->setupUi(this);
	ASSERT(pStatePara != NULL);
//	m_pStatePara = pStatePara;
	m_uiVOL = uiVOL;
	m_uiCUR = uiCUR;

	ASSERT(pSttTestResource != NULL);
	m_pShortCalcuSttTestResource = pSttTestResource;

	m_para = para;
	initPara();

	initUI();
	initConnections();

	MakeDataToGroup();
	initBaseData();
	initData();
	SetShortFont();
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);
}

ShortCalcuDig::~ShortCalcuDig()
{
	
}

void ShortCalcuDig::SetShortFont()
{
	m_pCmb_ChGroup->setFont(*g_pSttGlobalFont);
	m_pCmb_CacuMode->setFont(*g_pSttGlobalFont);
	m_pCmb_FaultType->setFont(*g_pSttGlobalFont);
	m_pCmb_CacuType->setFont(*g_pSttGlobalFont);
	m_pCacuTypeLabel->setFont(*g_pSttGlobalFont);
	m_pAmpLabel->setFont(*g_pSttGlobalFont);
	m_pAngleLabel->setFont(*g_pSttGlobalFont);

}

void ShortCalcuDig::initUI()
{
	resize(501, 309);
// 	QFont font;
// 	font.setPointSize(20);
// 	setFont(font);
	setFont(*g_pSttGlobalFont);

	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	
	m_pbn_Cancel = new QPushButton(tr("取消"),this);
//	gridLayout->addWidget(m_pbn_Cancel, 9, 4, 1, 1);

	m_pbn_Ok = new QPushButton(tr("确定"),this);
//	gridLayout->addWidget(m_pbn_Ok, 9, 3, 1, 1);

	QHBoxLayout* pOkCancelLayout = new QHBoxLayout();

	pOkCancelLayout->addWidget(m_pbn_Ok);
	pOkCancelLayout->addWidget(m_pbn_Cancel);

	gridLayout->addLayout(pOkCancelLayout, 9, 3, 1, 2);

	m_pZLabel = new QLabel(QString::fromLocal8Bit("Z(Ω),Phi(°):"),this);
	gridLayout->addWidget(m_pZLabel, 4, 0, 1, 1);

	m_pFaultTypeLabel = new QLabel(tr("故障类型:"),this);
	gridLayout->addWidget(m_pFaultTypeLabel, 2, 0, 1, 1);

	m_pCmb_ChGroup = new QScrollComboBox(this);
	gridLayout->addWidget(m_pCmb_ChGroup, 1, 1, 1, 2);

	m_pNulllabel = new QLabel(this);
	gridLayout->addWidget(m_pNulllabel, 3, 0, 1, 1);

	m_pCmb_FaultType = new QScrollComboBox(this);
	gridLayout->addWidget(m_pCmb_FaultType, 2, 1, 1, 2);

	m_pChGroupLabel = new QLabel(tr("组号:"),this);
	gridLayout->addWidget(m_pChGroupLabel, 1, 0, 1, 1);

	m_pPhiEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pPhiEdit, 4, 2, 1, 1);

	m_pRXLabel = new QLabel(QString::fromLocal8Bit("R(Ω),X(Ω):"),this);
	gridLayout->addWidget(m_pRXLabel, 5, 0, 1, 1);

	m_pRad_ZPhi = new QRadioButton(tr("Z,Phi"),this);
	gridLayout->addWidget(m_pRad_ZPhi, 3, 1, 1, 1);

	m_pRad_RX = new QRadioButton(tr("R,X"),this);
	gridLayout->addWidget(m_pRad_RX, 3, 2, 1, 1);

	m_pZEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pZEdit, 4, 1, 1, 1);

	m_pXEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pXEdit, 5, 2, 1, 1);

	m_pCacuModeLabel = new QLabel(tr("计算模型:"),this);
	gridLayout->addWidget(m_pCacuModeLabel, 6, 0, 1, 1);

	m_pREdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pREdit, 5, 1, 1, 1);

	m_pCmb_CacuMode = new QScrollComboBox(this);
	gridLayout->addWidget(m_pCmb_CacuMode, 6, 1, 1, 2);

	m_pLoadIEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pLoadIEdit, 6, 4, 1, 1);

	m_pLoadILabel = new QLabel(tr("负荷电流(A):"),this);
	gridLayout->addWidget(m_pLoadILabel, 6, 3, 1, 1);

	m_pDLILabel = new QLabel(tr("短路电流(A):"),this);
	gridLayout->addWidget(m_pDLILabel, 7, 0, 1, 1);

	m_pLoadAngleLabel = new QLabel(tr("负荷功角(°):"),this);
	gridLayout->addWidget(m_pLoadAngleLabel, 7, 3, 1, 1);

	m_pShortIEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pShortIEdit, 7, 1, 1, 2);

	m_pLoadAngleEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pLoadAngleEdit, 7, 4, 1, 1);

	m_pDLVLabel = new QLabel(tr("短路电压(V):"),this);
	gridLayout->addWidget(m_pDLVLabel, 8, 0, 1, 1);

	m_pZSZLEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pZSZLEdit, 9, 1, 1, 2);

	m_pShortUEdit = new QSttLineEdit(this);
	gridLayout->addWidget(m_pShortUEdit, 8, 1, 1, 2);

	m_pZSZLLabel = new QLabel(tr("|ZS/ZL|:"),this);
	gridLayout->addWidget(m_pZSZLLabel, 9, 0, 1, 1);

	QSttGroupBox* groupBox = new QSttGroupBox(tr("零序补偿系数"),this);
	QGridLayout* gridLayoutSub = new QGridLayout(groupBox);
	gridLayoutSub->setSpacing(6);
	gridLayoutSub->setContentsMargins(11, 11, 11, 11);
	
	m_pCacuTypeLabel = new QLabel(tr("计算方式:"),groupBox);
	gridLayoutSub->addWidget(m_pCacuTypeLabel, 0, 0, 1, 1);

	m_pCmb_CacuType = new QScrollComboBox(groupBox);
	gridLayoutSub->addWidget(m_pCmb_CacuType, 0, 1, 1, 1);

	m_pAmpLabel = new QLabel(tr("幅值:"),groupBox);
	gridLayoutSub->addWidget(m_pAmpLabel, 1, 0, 1, 1);

	m_pAmpEdit = new QSttLineEdit(groupBox);
	gridLayoutSub->addWidget(m_pAmpEdit, 1, 1, 1, 1);

	m_pAngleLabel = new QLabel(tr("相角:"),groupBox);
	gridLayoutSub->addWidget(m_pAngleLabel, 2, 0, 1, 1);

	m_pAngleEdit = new QSttLineEdit(groupBox);
	gridLayoutSub->addWidget(m_pAngleEdit, 2, 1, 1, 1);

	gridLayout->addWidget(groupBox, 1, 3, 4, 2);

	m_pAmpEdit->setFont(*g_pSttGlobalFont);
	m_pAngleEdit->setFont(*g_pSttGlobalFont); // 20240511 xueyangfan 幅值 相角字体大小

	xlang_SetLangStrToWidget(m_pbn_Ok, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pbn_Cancel, "sCancel", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pFaultTypeLabel, "State_FaultType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pChGroupLabel, "State_ChGroup", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pCacuModeLabel, "State_CalcMode", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pLoadILabel, "State_LoadI", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pDLILabel, "State_ShortI", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pLoadAngleLabel, "State_LoadAngle", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pDLVLabel, "State_ShortU", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(groupBox, "State_ZeroCoeff", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(m_pCacuTypeLabel, "State_CalcType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);

//	setWindowTitle(tr("短路计算"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"State_ShortCalc");
	setWindowTitle(strTitle);
}

void ShortCalcuDig::initConnections()
{
	connect(m_pCmb_FaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbErrorTypeIndexChanged(int)));
	connect(m_pCmb_CacuMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalModeIndexChanged(int)));
	connect(m_pCmb_CacuType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalTypeIndexChanged(int)));

	connect(m_pRad_ZPhi, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));
	connect(m_pRad_RX, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));

 	connect(m_pZEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneZ_TextKeyBoard()));
	connect(m_pPhiEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhi_TextKeyBoard()));
	connect(m_pREdit,SIGNAL(editingFinished()),this,SLOT(slot_lneR_TextKeyBoard()));
	connect(m_pXEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneX_TextKeyBoard()));
	connect(m_pShortIEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLDL_TextKeyBoard()));
	connect(m_pShortUEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLDY_TextKeyBoard()));
	connect(m_pZSZLEdit,SIGNAL(editingFinished() ),this,SLOT(slot_lneZSZL_TextKeyBoard()));
	connect(m_pAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFZ_TextKeyBoard()));
	connect(m_pAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneXJ_TextKeyBoard()));
	connect(m_pLoadIEdit,SIGNAL(editingFinished()),this,SLOT(slot_lne_LoadI_TextKeyBoard()));
	connect(m_pLoadAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lne_LoadAngle_TextKeyBoard()));

#ifdef _PSX_QT_LINUX_
	connect(m_pLoadAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lne_LoadAngle_TextChanged()));
	connect(m_pLoadIEdit,SIGNAL(clicked()),this,SLOT(slot_lne_LoadI_TextChanged()));
	connect(m_pAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lneXJ_TextChanged()));
	connect(m_pAmpEdit,SIGNAL(clicked()),this,SLOT(slot_lneFZ_TextChanged()));
	connect(m_pZSZLEdit,SIGNAL(clicked()),this,SLOT(slot_lneZSZL_TextChanged()));
	connect(m_pShortUEdit,SIGNAL(clicked()),this,SLOT(slot_lneDLDY_TextChanged()));
	connect(m_pShortIEdit,SIGNAL(clicked()),this,SLOT(slot_lneDLDL_TextChanged()));
	connect(m_pXEdit,SIGNAL(clicked()),this,SLOT(slot_lneX_TextChanged()));
	connect(m_pREdit,SIGNAL(clicked()),this,SLOT(slot_lneR_TextChanged()));
	connect(m_pPhiEdit,SIGNAL(clicked()),this,SLOT(slot_lnePhi_TextChanged()));
	connect(m_pZEdit,SIGNAL(clicked()), this, SLOT(slot_lneZ_TextChanged()));

#endif

	connect(m_pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_ConfirmClicked()));
	connect(m_pbn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClicked()));
}

void ShortCalcuDig::initBaseData()
{
	int num =((m_UChanelDataMap.size()>m_IChanelDataMap.size())?m_IChanelDataMap.size():m_UChanelDataMap.size());
	QStringList list;
	CString strTemp,strGroup;
	xlang_GetLangStrByFile(strGroup, "Native_Group");

	for (int i=0;i<num;i++)
	{
		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			strTemp.Format(_T("%d"),i+1);
			strTemp += strGroup;
			list.append(strTemp); //QString::fromLocal8Bit("第%1组").arg(i+1)
		}
		else
		{
			//list.append(QString(tr("Group %1")).arg(i+1));
			list.append(strGroup + QString(" %1").arg(i+1));
		}
	}

	m_pCmb_ChGroup->clear();
	m_pCmb_ChGroup->addItems(list);

	m_errorTypeList.clear();
	m_Z_P_R_XList.clear();
	m_CalModList.clear();
	m_CalTypeList.clear();

    CString strGndA,strGndB,strGndC,strShortAB,strShortBC,strShortCA,strGndShortAB,strGndShortBC,strGndShortCA,
		strShortABC,strSinglePhase;
//	m_errorTypeList << tr("A相接地")<< tr("B相接地")<< tr("C相接地")<< tr("AB短路")<< tr("BC短路")<< tr("CA短路")\
//		<< tr("AB接地短路")<< tr("BC接地短路")<< tr("CA接地短路")<< tr("三相短路")<<tr("单相系统");
	
	xlang_GetLangStrByFile(strGndA, "Native_GndA");
	xlang_GetLangStrByFile(strGndB, "Native_GndB");
	xlang_GetLangStrByFile(strGndC, "Native_GndC");
	xlang_GetLangStrByFile(strShortAB, "Native_ShortAB");
	xlang_GetLangStrByFile(strShortBC, "Native_ShortBC");
	xlang_GetLangStrByFile(strShortCA, "Native_ShortCA");
	xlang_GetLangStrByFile(strGndShortAB, "Native_GndShortAB");
	xlang_GetLangStrByFile(strGndShortBC, "Native_GndShortBC");
	xlang_GetLangStrByFile(strGndShortCA, "Native_GndShortCA");
	xlang_GetLangStrByFile(strShortABC, "Native_ShortABC");
	xlang_GetLangStrByFile(strSinglePhase, "Native_SinglePhase");

	m_errorTypeList << strGndA<< strGndB<< strGndC<< strShortAB<< strShortBC<< strShortCA\
		<< strGndShortAB<< strGndShortBC<< strGndShortCA<< strShortABC<< strSinglePhase;

	m_Z_P_R_XList << "Z,Phi" << "R,X";

    CString strINotChange,strUNotChange,strZNotChange;
//	m_CalModList <<tr("电流不变") <<tr("电压不变")<<tr("系统阻抗不变");

	xlang_GetLangStrByFile(strINotChange, "Native_INotChange");
	xlang_GetLangStrByFile(strUNotChange, "Native_UNotChange");
	xlang_GetLangStrByFile(strZNotChange, "Native_ZNotChange");

	m_CalModList <<strINotChange <<strUNotChange<<strZNotChange;

	m_CalTypeList << "KL" << "Kr,Kx" << "Z0/Z1";

	m_pCmb_FaultType->clear();
	m_pCmb_CacuMode->clear();
	m_pCmb_CacuType->clear();

	m_pCmb_FaultType->addItems(m_errorTypeList);
	m_pCmb_CacuMode->addItems(m_CalModList);
	m_pCmb_CacuType->addItems(m_CalTypeList);
}

void ShortCalcuDig::initPara()
{
	m_nRadio = m_para.nRadio;
	m_bZPhi = m_para.bZPhi;;
	m_bRX = m_para.bRX;
	m_bPrimaryPara = m_para.bPrimaryPara;
	m_nFaultType = m_para.nFaultType;
	m_fZ = m_para.fZ;
	m_fR = m_para.fR;
	m_fX  = m_para.fX;
	m_fPhi = m_para.fPhi;

	m_fImax = m_para.fImax;
	m_fVmax = m_para.fVmax;
	m_fKr=m_para.fKr;
	m_fKx=m_para.fKx;
	m_fDLI = m_para.fDLI;
	m_fDLV = m_para.fDLV;
	m_fZSZL=m_para.fZSZL;
	m_nCalMode=m_para.nCalMode;
	m_nCalType=m_para.nCalType;
	m_fVnom=m_para.fVnom;

	m_bFaultDir=m_para.bFaultDir;
	m_bCTPoint=m_para.bCTPoint;
	m_fIfh=m_para.fIfh;
	m_fPowerAngle=m_para.fPowerAngle;
}

void ShortCalcuDig::initData()
{
	m_nFaultType = m_para.nFaultType;
	m_nCalMode=m_para.nCalMode;
	m_nCalType=m_para.nCalType;

	m_pCmb_FaultType->setCurrentIndex(m_nFaultType);
	m_pCmb_CacuMode->setCurrentIndex(m_nCalMode);
	m_pCmb_CacuType->setCurrentIndex(m_nCalType);

	if (m_bZPhi)
	{
		m_pRad_ZPhi->setChecked(true);
		m_pRad_RX->setChecked(false);
	}
	else
	{
		m_pRad_ZPhi->setChecked(false);
		m_pRad_RX->setChecked(true);
	}

	m_pShortIEdit->setText(QString::number(m_fDLI,'f',3));
	m_pShortUEdit->setText(QString::number(m_fDLV,'f',3));
	m_pZSZLEdit->setText(QString::number(m_fZSZL,'f',3));
	m_pAmpEdit->setText(QString::number(m_fKr,'f',3));
	m_pAngleEdit->setText(QString::number(m_fKx,'f',3));

	OnRXValue();
	slot_RadioZPhiAndRX_StateChanged();
	slot_CmbCalModeIndexChanged(m_nCalMode);
	slot_CmbCalTypeIndexChanged(m_nCalType);
	
	m_pLoadIEdit->setText(QString::number(m_fIfh,'f',3));
	m_pLoadAngleEdit->setText(QString::number(m_fPowerAngle,'f',3));
}

void ShortCalcuDig::MakeDataToGroup()
{
	m_UChanelDataMap.clear();
	m_IChanelDataMap.clear();
	
	QList<tmt_Channel> m_ChanelDataList;
	m_ChanelDataList.clear();
	
	tmt_Channel chanelPara;

	//数据分组
	int mapKey = 0;
	if (m_pShortCalcuSttTestResource->m_oVolChRsListRef.GetCount()<=4) 
	{
		for (int j = 0; j < m_pShortCalcuSttTestResource->m_oVolChRsListRef.GetCount(); j++)
		{
			chanelPara = m_uiVOL[j];
			m_ChanelDataList.append(chanelPara);
		}

		mapKey ++;
		m_UChanelDataMap.insert(mapKey,m_ChanelDataList);

		m_ChanelDataList.clear();
		m_UModuleOfDataKeyMap.insert(mapKey,0);
	}
	else
	{
		//每3个量一组
		for (int j=0;j<m_pShortCalcuSttTestResource->m_oVolChRsListRef.GetCount()/3;j++)
		{
			chanelPara = m_uiVOL[j];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_uiVOL[j+1];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_uiVOL[j+2];
			m_ChanelDataList.append(chanelPara);

			mapKey ++;
			m_UChanelDataMap.insert(mapKey,m_ChanelDataList);
			m_ChanelDataList.clear();
			m_UModuleOfDataKeyMap.insert(mapKey,j);
		}
	}

	mapKey = 0;
	if (m_pShortCalcuSttTestResource->m_oCurChRsListRef.GetCount()<=4 )
	{
		for (int j = 0; j < m_pShortCalcuSttTestResource->m_oCurChRsListRef.GetCount(); j++)
		{
			chanelPara = m_uiCUR[j];
			m_ChanelDataList.append(chanelPara);
		}

		mapKey ++;
		m_IChanelDataMap.insert(mapKey,m_ChanelDataList);

		m_ChanelDataList.clear();
		m_IModuleOfDataKeyMap.insert(mapKey,0);
	}
	else
	{
		//每3个量一组
		for (int j=0;j<m_pShortCalcuSttTestResource->m_oCurChRsListRef.GetCount()/3;j++)
		{
			chanelPara = m_uiCUR[j];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_uiCUR[j+1];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_uiCUR[j+2];
			m_ChanelDataList.append(chanelPara);

			mapKey ++;
			m_IChanelDataMap.insert(mapKey,m_ChanelDataList);

			m_ChanelDataList.clear();
			m_IModuleOfDataKeyMap.insert(mapKey,j);
		}
	}
}


void ShortCalcuDig::slot_CmbErrorTypeIndexChanged(int index)
{
	if(m_pCmb_FaultType->IsScrolling())
	{
		return;
	}

	m_nFaultType = index;
}

void ShortCalcuDig::slot_RadioZPhiAndRX_StateChanged( )
{
	if (m_pRad_ZPhi->isChecked())
	{
		m_nRadio = 0;
		m_bZPhi = true;	
		m_bRX = false;
		m_pRad_RX->setChecked(false);
		m_pZLabel->setEnabled(true);
		m_pZEdit->setEnabled(true);
		m_pPhiEdit->setEnabled(true);

		m_pRXLabel->setEnabled(false);
		m_pREdit->setEnabled(false);
		m_pXEdit->setEnabled(false);
	}
	else
	{
		m_nRadio = 1;
		m_bZPhi = false;	
		m_bRX = true;
		m_pRad_RX->setChecked(true);
		m_pZLabel->setEnabled(false);
		m_pZEdit->setEnabled(false);
		m_pPhiEdit->setEnabled(false);

		m_pRXLabel->setEnabled(true);
		m_pREdit->setEnabled(true);
		m_pXEdit->setEnabled(true);
	}
}

void ShortCalcuDig::slot_lneZ_TextChanged()
{
 	QString strValue = m_pZEdit->text();
// 	QDockWidget *pWindow = new QDockWidget();
// 	pWindow->move(0,920);
// 	pWindow->setFixedSize(720,360);
// 	this->addDockWidget(Qt::LeftDockWidgetArea,pWindow);
// 	pWindow->show();
// 	WidgetKeyboardV_Digit *pWidgetKeyboardV_Digit = new WidgetKeyboardV_Digit();
// 	pWidgetKeyboardV_Digit->setParent(this);
// 	pWidgetKeyboardV_Digit->show();
// 	setview
// 	this->show();

// 	CreateKeyBoardWidget();
 	GetWidgetBoard_DigitData(4,strValue,m_pZEdit,g_theTestCntrFrame);

	//m_pZEdit->setText(strValue);
// 	m_fZ = strValue.toFloat();
// 	if (m_fZ<0)
// 	{
// 		m_fZ = 0.0;
// 	}
// 	else if(m_fZ>9999)
// 	{
// 		m_fZ = 9999;
// 	}
// 	m_pZEdit->setText(QString::number(m_fZ,'f',3));
// 	OnRXValue();
}

void ShortCalcuDig::slot_lneZ_TextKeyBoard()
{
 	QString strValue = m_pZEdit->text();

//  	GetWidgetBoard_DigitData(4,strValue,m_pZEdit,g_theTestCntrFrame);

	//m_pZEdit->setText(strValue);
	m_fZ = strValue.toFloat();
	if (m_fZ<0)
	{
		m_fZ = 0.0;
	}
	else if(m_fZ>9999)
	{
		m_fZ = 9999;
	}
	m_pZEdit->setText(QString::number(m_fZ,'f',3));
	OnRXValue();
}
void ShortCalcuDig::slot_lnePhi_TextChanged()
{
	QString strValue = m_pPhiEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pPhiEdit,g_theTestCntrFrame);

// 	//m_pPhiEdit->setText(strValue);
// 	m_fPhi = strValue.toFloat();
// 	while (m_fPhi<0)
// 	{
// 		m_fPhi += 360;
// 	}
// 	while (m_fPhi>360)
// 	{
// 		m_fPhi -= 360;
// 	}
// 	m_pPhiEdit->setText(QString::number(m_fPhi,'f',3));
// 
// 	OnRXValue();
}

void ShortCalcuDig::slot_lnePhi_TextKeyBoard()
{
	QString strValue = m_pPhiEdit->text();
// 	GetWidgetBoard_DigitData(2,strValue,g_theTestCntrFrame);

	//m_pPhiEdit->setText(strValue);
	m_fPhi = strValue.toFloat();
	while (m_fPhi<0)
	{
		m_fPhi += 360;
	}
	while (m_fPhi>360)
	{
		m_fPhi -= 360;
	}
	m_pPhiEdit->setText(QString::number(m_fPhi,'f',3));

	OnRXValue();
}
void ShortCalcuDig::slot_lneR_TextChanged()
{
	QString strValue = m_pREdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pREdit,g_theTestCntrFrame);

	//m_pREdit->setText(strValue);
// 	m_fR = strValue.toFloat();
// 	if (m_fR<0)
// 	{
// 		m_fR = 0.0;
// 	}
// 	else if(m_fR>9999)
// 	{
// 		m_fR = 9999;
// 	}
// 	m_pREdit->setText(QString::number(m_fR,'f',3));
// 
// 	OnRXValue();
}

void ShortCalcuDig::slot_lneR_TextKeyBoard()
{
	QString strValue = m_pREdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	//m_pREdit->setText(strValue);
	m_fR = strValue.toFloat();
	if (m_fR<0)
	{
		m_fR = 0.0;
	}
	else if(m_fR>9999)
	{
		m_fR = 9999;
	}
	m_pREdit->setText(QString::number(m_fR,'f',3));

	OnRXValue();
}
void ShortCalcuDig::slot_lneX_TextChanged()
{
	QString strValue = m_pXEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pXEdit,g_theTestCntrFrame);

	//m_pXEdit->setText(strValue);
// 	m_fX = strValue.toFloat();
// 	if (m_fX<0)
// 	{
// 		m_fX = 0.0;
// 	}
// 	else if(m_fX>9999)
// 	{
// 		m_fX = 9999;
// 	}
// 	m_pXEdit->setText(QString::number(m_fX,'f',3));
// 
// 	OnRXValue();
}

void ShortCalcuDig::slot_lneX_TextKeyBoard()
{
	QString strValue = m_pXEdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	//m_pXEdit->setText(strValue);
	m_fX = strValue.toFloat();
	if (m_fX<0)
	{
		m_fX = 0.0;
	}
	else if(m_fX>9999)
	{
		m_fX = 9999;
	}
	m_pXEdit->setText(QString::number(m_fX,'f',3));

	OnRXValue();
}

void ShortCalcuDig::slot_CmbCalModeIndexChanged( int index)
{
	if(m_pCmb_CacuMode->IsScrolling())
	{
		return;
	}

	m_nCalMode = index;

	switch(index)
	{
	case 0:
		{
			m_pDLILabel->setDisabled(false);
			m_pShortIEdit->setDisabled(false);
			m_pDLVLabel->setDisabled(true);
			m_pShortUEdit->setDisabled(true);
			m_pZSZLLabel->setDisabled(true);
			m_pZSZLEdit->setDisabled(true);
		}
		break;
	case 1:
		{
			m_pDLILabel->setDisabled(true);
			m_pShortIEdit->setDisabled(true);
			m_pDLVLabel->setDisabled(false);
			m_pShortUEdit->setDisabled(false);
			m_pZSZLLabel->setDisabled(true);
			m_pZSZLEdit->setDisabled(true);
		}
		break;
	case 2:
		{
			m_pDLILabel->setDisabled(true);
			m_pShortIEdit->setDisabled(true);
			m_pDLVLabel->setDisabled(true);
			m_pShortUEdit->setDisabled(true);
			m_pZSZLLabel->setDisabled(false);
			m_pZSZLEdit->setDisabled(false);
		}
		break;
	default:
		break;
	}
}

void ShortCalcuDig::slot_lneDLDL_TextChanged()
{
	QString strValue = m_pShortIEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pShortIEdit,g_theTestCntrFrame);

	//m_pShortIEdit->setText(strValue);
// 	m_fDLI = strValue.toFloat();
// 	if (m_fDLI<0)
// 	{
// 		m_fDLI = 0;
// 	}
// 
// 	m_fDLI = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,m_fDLI);
// 	m_pShortIEdit->setText(QString::number(m_fDLI,'f',3));
}

void ShortCalcuDig::slot_lneDLDL_TextKeyBoard()
{
	QString strValue = m_pShortIEdit->text();
// 	GetWidgetBoard_DigitData(1,strValue,g_theTestCntrFrame);

	//m_pShortIEdit->setText(strValue);
	m_fDLI = strValue.toFloat();
	if (m_fDLI<0)
	{
		m_fDLI = 0;
	}

	m_fDLI = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,m_fDLI);
	m_pShortIEdit->setText(QString::number(m_fDLI,'f',3));
}

void ShortCalcuDig::slot_lneDLDY_TextChanged()
{
	QString strValue = m_pShortUEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pShortUEdit,g_theTestCntrFrame);

	//m_pShortUEdit->setText(strValue);
// 	m_fDLV = strValue.toFloat();
// 	if (m_fDLV<0)
// 	{
// 		m_fDLV = 0;
// 	}
// 
// 	m_fDLV = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,m_fDLV);
// 	m_pShortUEdit->setText(QString::number(m_fDLV,'f',3));
}

void ShortCalcuDig::slot_lneDLDY_TextKeyBoard()
{
	QString strValue = m_pShortUEdit->text();
// 	GetWidgetBoard_DigitData(0,strValue,g_theTestCntrFrame);

	//m_pShortUEdit->setText(strValue);
	m_fDLV = strValue.toFloat();
	if (m_fDLV<0)
	{
		m_fDLV = 0;
	}

	m_fDLV = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,m_fDLV);
	m_pShortUEdit->setText(QString::number(m_fDLV,'f',3));
}

void ShortCalcuDig::slot_lneZSZL_TextChanged()
{
	QString strValue = m_pZSZLEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pZSZLEdit,g_theTestCntrFrame);

	//m_pZSZLEdit->setText(strValue);
// 	m_fZSZL = strValue.toFloat();
// 	if(m_fZSZL<0)
// 	{
// 		m_fZSZL = 0.0;
// 	}
// 	else if(m_fZSZL>10)
// 	{
// 		m_fZSZL = 10;
// 	}
// 	m_pZSZLEdit->setText(QString::number(m_fZSZL,'f',3));
}
void ShortCalcuDig::slot_lneZSZL_TextKeyBoard()
{
	QString strValue = m_pZSZLEdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	//m_pZSZLEdit->setText(strValue);
	m_fZSZL = strValue.toFloat();
	if(m_fZSZL<0)
	{
		m_fZSZL = 0.0;
	}
	else if(m_fZSZL>10)
	{
		m_fZSZL = 10;
	}
	m_pZSZLEdit->setText(QString::number(m_fZSZL,'f',3));
}
void ShortCalcuDig::slot_CmbCalTypeIndexChanged( int index)
{
	if(m_pCmb_CacuType->IsScrolling())
	{
		return;
	}

	m_nCalType = index;
	switch(index)
	{
	case 0:
		{
//			m_pAmpLabel->setText(tr("幅值:"));
//			m_pAngleLabel->setText(tr("相角(°)"));
			xlang_SetLangStrToWidget(m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
		}
		break;
	case 1:
		{
			m_pAmpLabel->setText(tr("Kr"));
			m_pAngleLabel->setText(tr("Kx"));
		}
		break;
	case 2:
		{
//			m_pAmpLabel->setText(tr("幅值："));
//			m_pAngleLabel->setText(tr("相角(°)"));
			xlang_SetLangStrToWidget(m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
		}
		break;
	default:
		break;
	}
}

void ShortCalcuDig::slot_lneFZ_TextChanged()
{
	QString strValue = m_pAmpEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pAmpEdit,g_theTestCntrFrame);

	//m_pAmpEdit->setText(strValue);
// 	m_fKr = strValue.toFloat();
// 	if(m_fKr<0)
// 	{
// 		m_fKr = 0.0;
// 	}
// 	else if(m_fKr>10)
// 	{
// 		m_fKr = 10;
// 	}
// 	m_pAmpEdit->setText(QString::number(m_fKr,'f',3));
}

void ShortCalcuDig::slot_lneFZ_TextKeyBoard()
{
	QString strValue = m_pAmpEdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	//m_pAmpEdit->setText(strValue);
	m_fKr = strValue.toFloat();
	if(m_fKr<0)
	{
		m_fKr = 0.0;
	}
	else if(m_fKr>10)
	{
		m_fKr = 10;
	}
	m_pAmpEdit->setText(QString::number(m_fKr,'f',3));
}

void ShortCalcuDig::slot_lneXJ_TextChanged()
{
	QString strValue = m_pAngleEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pAngleEdit,g_theTestCntrFrame);

	//m_pAngleEdit->setText(strValue);
// 	m_fKx = strValue.toFloat();
// 	if(m_nCalType == 1)
// 	{
// 		if(m_fKx<0)
// 		{
// 			m_fKx = 0.0;
// 		}
// 		else if(m_fKx>10)
// 		{
// 			m_fKx = 10;
// 		}
// 	}
// 	else
// 	{
// 		while(m_fKx<0)
// 		{
// 			m_fKx += 360;
// 		}
// 		while(m_fKx>360)
// 		{
// 			m_fKx -= 360;
// 		}
// 	}
// 	m_pAngleEdit->setText(QString::number(m_fKx,'f',3));
}

void ShortCalcuDig::slot_lneXJ_TextKeyBoard()
{
	QString strValue = m_pAngleEdit->text();
// 	GetWidgetBoard_DigitData(4,strValue,g_theTestCntrFrame);

	//m_pAngleEdit->setText(strValue);
	m_fKx = strValue.toFloat();
	if(m_nCalType == 1)
	{
		if(m_fKx<0)
		{
			m_fKx = 0.0;
		}
		else if(m_fKx>10)
		{
			m_fKx = 10;
		}
	}
	else
	{
		while(m_fKx<0)
		{
			m_fKx += 360;
		}
		while(m_fKx>360)
		{
			m_fKx -= 360;
		}
	}
	m_pAngleEdit->setText(QString::number(m_fKx,'f',3));
}

void ShortCalcuDig::slot_lne_LoadI_TextChanged()
{
	QString strValue = m_pLoadIEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pLoadIEdit,g_theTestCntrFrame);

	//m_pLoadIEdit->setText(strValue);
// 	m_fIfh = strValue.toFloat();
// 	if(m_fIfh<0)
// 	{
// 		m_fIfh = 0.0;
// 	}
// 	else if(m_fIfh>1)
// 	{
// 		m_fIfh = 1;
// 	}
// 	m_pLoadIEdit->setText(QString::number(m_fIfh,'f',3));
}

void ShortCalcuDig::slot_lne_LoadI_TextKeyBoard()
{
	QString strValue = m_pLoadIEdit->text();
// 	GetWidgetBoard_DigitData(1,strValue,g_theTestCntrFrame);

	//m_pLoadIEdit->setText(strValue);
	m_fIfh = strValue.toFloat();
	if(m_fIfh<0)
	{
		m_fIfh = 0.0;
	}
	else if(m_fIfh>1)
	{
		m_fIfh = 1;
	}
	m_pLoadIEdit->setText(QString::number(m_fIfh,'f',3));
}

void ShortCalcuDig::slot_lne_LoadAngle_TextChanged()
{
	QString strValue = m_pLoadAngleEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pLoadAngleEdit,g_theTestCntrFrame);

	//m_pLoadAngleEdit->setText(strValue);
// 	m_fPowerAngle = strValue.toFloat();
// 	while(m_fPowerAngle<0)
// 	{
// 		m_fPowerAngle += 360;
// 	}
// 	while(m_fPowerAngle>360)
// 	{
// 		m_fPowerAngle -= 360;
// 	}
// 	m_pLoadAngleEdit->setText(QString::number(m_fPowerAngle,'f',3));
}

void ShortCalcuDig::slot_lne_LoadAngle_TextKeyBoard()
{
	QString strValue = m_pLoadAngleEdit->text();
// 	GetWidgetBoard_DigitData(2,strValue,g_theTestCntrFrame);

	//m_pLoadAngleEdit->setText(strValue);
	m_fPowerAngle = strValue.toFloat();
	while(m_fPowerAngle<0)
	{
		m_fPowerAngle += 360;
	}
	while(m_fPowerAngle>360)
	{
		m_fPowerAngle -= 360;
	}
	m_pLoadAngleEdit->setText(QString::number(m_fPowerAngle,'f',3));
}

void ShortCalcuDig::slot_ConfirmClicked()
{
	ExitHideKeyboardWidget();
	Complex p1,p2;
// 	CString strTmp;
// 	strTmp.getlocal8
	
	m_fVnom = g_oSystemParas.m_fVNom/SQRT3;
	int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};
	if(m_fDLV<0.0)m_fDLV=0.0;
	if(m_fDLV>m_fVmax)m_fDLV=m_fVmax;

	if(m_fDLI<0.0)m_fDLI=0.0;
	if(m_fDLI>m_fImax)m_fDLI=m_fImax;
	OnRXValue();
	CFaultCalculat m_FaultCalculat;
	m_fVa=p1.polar(m_fVnom,0.0);
	m_fVb=p1.polar(m_fVnom,-120.0);
	m_fVc=p1.polar(m_fVnom,120.0);
	m_fIa=p1.polar(m_fIfh,0.0-m_fPowerAngle);
	m_fIb=p1.polar(m_fIfh,-120.0-m_fPowerAngle);
	m_fIc=p1.polar(m_fIfh,120.0-m_fPowerAngle);
	float nAngle[11] = {p1.arg(m_fVb),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVb),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVb),p1.arg(m_fVa),p1.arg(m_fVa)};
	
	p1=m_FaultCalculat.GroundFactor(m_nCalType,m_fKr,m_fKx,m_fPhi);
	m_fK0l=p2.norm(p1);
	m_fK0lPh=p2.arg(p1);
	Complex fV1,fV2,fV3,fI1,fI2,fI3;
	double fIt,fVt;
	float fValueFactor;
	if(m_bPrimaryPara)
	{
		fValueFactor=1000.0;
		fIt=m_fDLI/m_fIFactor;
		fVt=m_fDLV/m_fVFactor;
		m_FaultCalculat.Calculat(1.0,m_bFaultDir,m_bCTPoint,m_nCalMode,m_nFaultType,
			nPhaseRef[m_nFaultType],nAngle[m_nFaultType],
			m_fVmax/m_fVFactor,m_fVnom/m_fVFactor,m_fImax/m_fIFactor,
			&fIt,&fVt,
			p1.polar(m_fIfh/m_fIFactor,-m_fPowerAngle),
			p1.polar(m_fZ/m_fVFactor/fValueFactor*m_fIFactor,m_fPhi),p1.polar(m_fK0l,m_fK0lPh),
			p1.polar(m_fZ*m_fZSZL/m_fVFactor/fValueFactor*m_fIFactor,m_fPhi),
			p1.polar(m_fK0l,m_fK0lPh),
			&fV1,&fV2,&fV3,&fI1,&fI2,&fI3);
		m_fVa=fV1*m_fVFactor;
		m_fVb=fV2*m_fVFactor;
		m_fVc=fV3*m_fVFactor;
		m_fIa=fI1*m_fIFactor;
		m_fIb=fI2*m_fIFactor;
		m_fIc=fI3*m_fIFactor;
		m_fDLI=fIt*m_fIFactor;
		m_fDLV=fVt*m_fVFactor;
	}
	else
	{
		fIt=m_fDLI;
		fVt=m_fDLV;
		m_FaultCalculat.Calculat(1.0,m_bFaultDir,m_bCTPoint,m_nCalMode,m_nFaultType,
			nPhaseRef[m_nFaultType],nAngle[m_nFaultType],
			m_fVmax,m_fVnom,m_fImax,
			&fIt,&fVt,
			p1.polar(m_fIfh,-m_fPowerAngle),
			p1.polar(m_fZ,m_fPhi),p1.polar(m_fK0l,m_fK0lPh),
			p1.polar(m_fZ*m_fZSZL,m_fPhi),
			p1.polar(m_fK0l,m_fK0lPh),
			&fV1,&fV2,&fV3,&fI1,&fI2,&fI3);
		m_fVa=fV1;
		m_fVb=fV2;
		m_fVc=fV3;
		m_fIa=fI1;
		m_fIb=fI2;
		m_fIc=fI3;
		m_fDLI=fIt;
		m_fDLV=fVt;
	}
	
	QList<tmt_Channel> CHUList;
	QList<tmt_Channel> CHIList;
	tmt_Channel channelPara;

	int index = m_pCmb_ChGroup->currentIndex();  //组号
	
	int numOfUModule = m_UModuleOfDataKeyMap.value(index+1);	//根据分组号(分组索引+1)得到模块索引
	int numOfIModule = m_IModuleOfDataKeyMap.value(index+1);	
	for (int i = 0; i < m_UChanelDataMap.value(index+1).size(); i++)
	{
		channelPara.Harm[1].fAmp = m_UChanelDataMap.value(index+1)[i].Harm[1].fAmp;
		channelPara.Harm[1].fAngle = m_UChanelDataMap.value(index+1)[i].Harm[1].fAngle;
		channelPara.Harm[1].fFreq = m_UChanelDataMap.value(index+1)[i].Harm[1].fFreq;
		CHUList.append(channelPara);
	}
	for (int i = 0; i < m_IChanelDataMap.value(index+1).size(); i++)
	{
		channelPara.Harm[1].fAmp = m_IChanelDataMap.value(index+1)[i].Harm[1].fAmp;
		channelPara.Harm[1].fAngle = m_IChanelDataMap.value(index+1)[i].Harm[1].fAngle;
		channelPara.Harm[1].fFreq = m_IChanelDataMap.value(index+1)[i].Harm[1].fFreq;
		CHIList.append(channelPara);
	}
	
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;

	Complex p11;
	if (CHIList.size()>0)
	{
		CHIList[0].Harm[1].fAmp = (p11.norm(m_fIa) > fAcIMax)? fAcIMax:p11.norm(m_fIa);
		CHIList[1].Harm[1].fAmp = (p11.norm(m_fIb) > fAcIMax)? fAcIMax:p11.norm(m_fIb);
		CHIList[2].Harm[1].fAmp = (p11.norm(m_fIc) > fAcIMax)? fAcIMax:p11.norm(m_fIc);
		CHIList[0].Harm[1].fAngle = p11.arg(m_fIa);
		CHIList[1].Harm[1].fAngle = p11.arg(m_fIb);
		CHIList[2].Harm[1].fAngle = p11.arg(m_fIc);
	}

	if (CHUList.size()>0)
	{
		CHUList[0].Harm[1].fAmp = (p11.norm(m_fVa) > fAcVMax)? fAcVMax:p11.norm(m_fVa);
		CHUList[1].Harm[1].fAmp = (p11.norm(m_fVb) > fAcVMax)? fAcVMax:p11.norm(m_fVb);
		CHUList[2].Harm[1].fAmp = (p11.norm(m_fVc) > fAcVMax)? fAcVMax:p11.norm(m_fVc);
		CHUList[0].Harm[1].fAngle = p11.arg(m_fVa);
		CHUList[1].Harm[1].fAngle = p11.arg(m_fVb);
		CHUList[2].Harm[1].fAngle = p11.arg(m_fVc);
	}
	
	m_para.nRadio = m_nRadio;
	m_para.bZPhi=m_bZPhi;
	m_para.bRX =m_bRX ;
	m_para.bPrimaryPara=m_bPrimaryPara;
	m_para.nFaultType=m_nFaultType;
	m_para.fZ=m_fZ;
	m_para.fR=m_fR;
	m_para.fX=m_fX;
	m_para.fPhi=m_fPhi;

	m_para.fImax=m_fImax;
	m_para.fVmax=m_fVmax;
	m_para.fKr=m_fKr;
	m_para.fKx=m_fKx;
	m_para.fDLI=m_fDLI;
	m_para.fDLV=m_fDLV;
	m_para.fZSZL=m_fZSZL;
	m_para.nCalMode=m_nCalMode;
	m_para.nCalType=m_nCalType;
	m_para.fVnom=m_fVnom;

	m_para.bFaultDir=m_bFaultDir;
	m_para.bCTPoint=m_bCTPoint;
	m_para.fIfh=m_fIfh;
	m_para.fPowerAngle=m_fPowerAngle;

//	bool bHas4UModule = false;
	int nUstartpos = 0;
	int nIstartpos = 0;

	//模块只有一个，所以numOfUModule=0，numOfIModule=0
// 	if (m_pShortCalcuSttTestResource->m_oVolChRsListRef.GetCount()==4) 
// 	{
// 		bHas4UModule = true;
// 	}

	int tempnum = 0;
//     if (bHas4UModule == true)
// 	{
// 		nUstartpos = index*3-tempnum +1;
// 	}
// 	else
	{
		nUstartpos = index*3-tempnum;
	}

	for (int i = 0; i < CHUList.size(); i++)
	{
		m_uiVOL[tempnum+nUstartpos+i].Harm[1].fAmp = CHUList[i].Harm[1].fAmp;
		m_uiVOL[tempnum+nUstartpos+i].Harm[1].fAngle = CHUList[i].Harm[1].fAngle;
		m_uiVOL[tempnum+nUstartpos+i].Harm[1].fFreq = CHUList[i].Harm[1].fFreq;
	}

	tempnum = 0;
    nIstartpos = index*3-tempnum;
	for (int i = 0; i < CHIList.size(); i++)
	{
		m_uiCUR[tempnum+nIstartpos+i].Harm[1].fAmp = CHIList[i].Harm[1].fAmp;
		m_uiCUR[tempnum+nIstartpos+i].Harm[1].fAngle = CHIList[i].Harm[1].fAngle;
		m_uiCUR[tempnum+nIstartpos+i].Harm[1].fFreq = CHIList[i].Harm[1].fFreq;
	}

	emit sig_ShortCalcuOk(m_para);

	close();
}

void ShortCalcuDig::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}

void ShortCalcuDig::OnRXValue()
{
	if(m_nRadio==0)
	{	
		if(m_fZ<0.0)m_fZ=0.0;
		if(m_fPhi<-180.0)m_fPhi+=360.0;
		if(m_fPhi>360.0)m_fPhi-=360.0;
		m_fX=m_fZ*sin(m_fPhi*3.14159/180.0);
		m_fR=m_fZ*cos(m_fPhi*3.14159/180.0);
	}
	else
	{
		m_fZ=hypot(m_fR,m_fX);
		if(fabs(m_fR)>0.0001)m_fPhi=atan2(m_fX,m_fR)*180.0/3.14159;
		else m_fPhi=0.0;
	}

	m_pZEdit->setText(QString::number(m_fZ,'f',3));
	m_pPhiEdit->setText(QString::number(m_fPhi,'f',3));
	m_pREdit->setText(QString::number(m_fR,'f',3));
	m_pXEdit->setText(QString::number(m_fX,'f',3));
}

