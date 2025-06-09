#include "ShortCalcuDig.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

ShortCalcuDig::ShortCalcuDig(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara,ShortCalcuPara para,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ASSERT(pStatePara != NULL);
	m_pStatePara = pStatePara;

	ASSERT(pSttTestResource != NULL);
	m_pSttTestResource = pSttTestResource;

	m_para = para;

	InitData();
        InitLanguage();
	MakeDataToGroup();
	Init();
	
	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	this->setWindowTitle(g_sLangTxt_State_ShortCalc);
}

ShortCalcuDig::~ShortCalcuDig()
{
	
}

void ShortCalcuDig::InitLanguage()
{
  // ui
  xlang_SetLangStrToWidget_Txt(ui.label_18, g_sLangTxt_State_ChGroup,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_15, g_sLangTxt_State_FaultType,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.groupBox, g_sLangTxt_Native_ZeroSeqComp,XLang_Ctrls_QGroupBox);
  xlang_SetLangStrToWidget_Txt(ui.label_17, g_sLangTxt_State_CalcType,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.lab_Para1, g_sLangTxt_State_Amp,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.lab_Para2, g_sLangTxt_State_Angle,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_16, g_sLangTxt_State_CalcMode,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.lab_DLI, g_sLangTxt_State_ShortI,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.lab_DLV, g_sLangTxt_State_ShortU,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_9, g_sLangTxt_LoadI,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_8, g_sLangTxt_State_LoadAngle,XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_Native_Confm,XLang_Ctrls_QPushButton);
  xlang_SetLangStrToWidget_Txt(ui.pbn_Cancel, g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
}



void ShortCalcuDig::InitData()
{
	m_nRadio = m_para.nRadio;
	m_bZPhi = m_para.bZPhi;
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

void ShortCalcuDig::Init()
{
	int num =((m_UChanelDataMap.size()>m_IChanelDataMap.size())?m_IChanelDataMap.size():m_UChanelDataMap.size());
	QStringList list;
	for (int i=0;i<num;i++)
	{
		list.append(QString(/*tr("第%1组")*/g_sLangTxt_Native_groupNumber).arg(i+1));
	}
	ui.cmb_ChGroup->clear();
	ui.cmb_ChGroup->addItems(list);

	m_errorTypeList.clear();
	m_Z_P_R_XList.clear();
	m_CalModList.clear();
	m_CalTypeList.clear();
        m_errorTypeList << /*tr("A相接地")*/ g_sLangTxt_Native_GndA<< /*tr("B相接地")*/ g_sLangTxt_Native_GndB<< /*tr("C相接地")*/ g_sLangTxt_Native_GndC
                  << /*tr("AB短路")*/ g_sLangTxt_Native_ShortAB<< /*tr("BC短路")*/ g_sLangTxt_Native_ShortBC<< /*tr("CA短路")*/ g_sLangTxt_Native_ShortCA
                  << /*tr("AB接地短路")*/ g_sLangTxt_Native_GndShortAB<< /*tr("BC接地短路")*/ g_sLangTxt_Native_GndShortBC<< /*tr("CA接地短路")*/ g_sLangTxt_Native_GndShortCA
                  << /*tr("三相短路")*/ g_sLangTxt_Native_ShortABC<< /*tr("单相系统")*/ g_sLangTxt_Native_SinglePhase;
         m_Z_P_R_XList << "Z,Phi"<< "R,X";
         m_CalModList << /*tr("电流不变")*/ g_sLangTxt_Native_INotChange<< /*tr("电压不变")*/ g_sLangTxt_Native_UNotChange<< /*tr("系统阻抗不变")*/ g_sLangTxt_Native_ZNotChange;
         m_CalTypeList << "KL"<< "Kr,Kx"<< "Z0/Z1";

	ui.cmb_FaultType->clear();
	ui.cmb_CacuMode->clear();
	ui.cmb_CacuType->clear();

	ui.cmb_FaultType->addItems(m_errorTypeList);
	ui.cmb_CacuMode->addItems(m_CalModList);
	ui.cmb_CacuType->addItems(m_CalTypeList);

	ui.cmb_FaultType->setCurrentIndex(m_nFaultType);
	ui.cmb_CacuMode->setCurrentIndex(m_nCalMode);
	ui.cmb_CacuType->setCurrentIndex(m_nCalType);

	if (m_bZPhi)
	{
		ui.rad_ZPhi->setChecked(true);
		ui.rad_RX->setChecked(false);
	}
	else
	{
		ui.rad_ZPhi->setChecked(false);
		ui.rad_RX->setChecked(true);
	}

	ui.lne_ShortI->setText(QString::number(m_fDLI,'f',3));
	ui.lne_ShortU->setText(QString::number(m_fDLV,'f',3));
	ui.lne_ZSZL->setText(QString::number(m_fZSZL,'f',3));
	ui.lne_CacuPara1->setText(QString::number(m_fKr,'f',3));
	ui.lne_CacuPara2->setText(QString::number(m_fKx,'f',3));

	OnRXValue();
	slot_RadioZPhiAndRX_StateChanged();
	slot_CmbCalModeIndexChanged(m_nCalMode);
	slot_CmbCalTypeIndexChanged(m_nCalType);
	
	ui.lne_LoadI->setText(QString::number(m_fIfh,'f',3));
	ui.lne_LoadAngle->setText(QString::number(m_fPowerAngle,'f',3));
	
	InitConnection();
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
	if (m_pSttTestResource->m_oVolChRsListRef.GetCount()<=4) 
	{
		for (int j = 0; j < m_pSttTestResource->m_oVolChRsListRef.GetCount(); j++)
		{
			chanelPara = m_pStatePara->m_uiVOL[j];
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
		for (int j=0;j<m_pSttTestResource->m_oVolChRsListRef.GetCount()/3;j++)
		{
			chanelPara = m_pStatePara->m_uiVOL[j];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_pStatePara->m_uiVOL[j+1];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_pStatePara->m_uiVOL[j+2];
			m_ChanelDataList.append(chanelPara);

			mapKey ++;
			m_UChanelDataMap.insert(mapKey,m_ChanelDataList);
			m_ChanelDataList.clear();
			m_UModuleOfDataKeyMap.insert(mapKey,j);
		}
	}

	mapKey = 0;
	if (m_pSttTestResource->m_oCurChRsListRef.GetCount()<=4 )
	{
		for (int j = 0; j < m_pSttTestResource->m_oCurChRsListRef.GetCount(); j++)
		{
			chanelPara = m_pStatePara->m_uiCUR[j];
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
		for (int j=0;j<m_pSttTestResource->m_oCurChRsListRef.GetCount()/3;j++)
		{
			chanelPara = m_pStatePara->m_uiCUR[j];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_pStatePara->m_uiCUR[j+1];
			m_ChanelDataList.append(chanelPara);
			chanelPara = m_pStatePara->m_uiCUR[j+2];
			m_ChanelDataList.append(chanelPara);

			mapKey ++;
			m_IChanelDataMap.insert(mapKey,m_ChanelDataList);

			m_ChanelDataList.clear();
			m_IModuleOfDataKeyMap.insert(mapKey,j);
		}
	}
}

void ShortCalcuDig::InitConnection()
{
	connect(ui.cmb_FaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbErrorTypeIndexChanged(int)));
	connect(ui.cmb_CacuMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalModeIndexChanged(int)));
	connect(ui.cmb_CacuType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalTypeIndexChanged(int)));
	
	connect(ui.rad_ZPhi, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));
	connect(ui.rad_RX, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));

	connect(ui.lne_Z,SIGNAL(editingFinished()),this,SLOT(slot_lneZ_TextChanged()));
	connect(ui.lne_Phi,SIGNAL(editingFinished()),this,SLOT(slot_lnePhi_TextChanged()));
	connect(ui.lne_R,SIGNAL(editingFinished()),this,SLOT(slot_lneR_TextChanged()));
	connect(ui.lne_X,SIGNAL(editingFinished()),this,SLOT(slot_lneX_TextChanged()));

	connect(ui.lne_ShortI,SIGNAL(editingFinished()),this,SLOT(slot_lneDLDL_TextChanged()));
	connect(ui.lne_ShortU,SIGNAL(editingFinished()),this,SLOT(slot_lneDLDY_TextChanged()));
	connect(ui.lne_ZSZL,SIGNAL(editingFinished() ),this,SLOT(slot_lneZSZL_TextChanged()));

	connect(ui.lne_CacuPara1,SIGNAL(editingFinished()),this,SLOT(slot_lneFZ_TextChanged()));
	connect(ui.lne_CacuPara2,SIGNAL(editingFinished()),this,SLOT(slot_lneXJ_TextChanged()));

	connect(ui.lne_LoadI,SIGNAL(editingFinished()),this,SLOT(slot_lne_LoadI_TextChanged()));
	connect(ui.lne_LoadAngle,SIGNAL(editingFinished()),this,SLOT(slot_lne_LoadAngle_TextChanged()));

	connect(ui.pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_ConfirmClicked()));
	connect(ui.pbn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClicked()));
}

void ShortCalcuDig::slot_CmbErrorTypeIndexChanged(int index)
{
	m_nFaultType = index;
}

void ShortCalcuDig::slot_RadioZPhiAndRX_StateChanged( )
{
	if (ui.rad_ZPhi->isChecked())
	{
		m_nRadio = 0;
		m_bZPhi = true;	
		m_bRX = false;
		ui.rad_RX->setChecked(false);
		ui.lab_Z->setEnabled(true);
		ui.lne_Z->setEnabled(true);
		ui.lne_Phi->setEnabled(true);

		ui.lab_RX->setEnabled(false);
		ui.lne_R->setEnabled(false);
		ui.lne_X->setEnabled(false);
	}
	else
	{
		m_nRadio = 1;
		m_bZPhi = false;	
		m_bRX = true;
		ui.rad_RX->setChecked(true);
		ui.lab_Z->setEnabled(false);
		ui.lne_Z->setEnabled(false);
		ui.lne_Phi->setEnabled(false);

		ui.lab_RX->setEnabled(true);
		ui.lne_R->setEnabled(true);
		ui.lne_X->setEnabled(true);
	}
}

void ShortCalcuDig::slot_lneZ_TextChanged()
{
	m_fZ = ui.lne_Z->text().toFloat();
	OnRXValue();
}

void ShortCalcuDig::slot_lnePhi_TextChanged()
{
	m_fPhi = ui.lne_Phi->text().toFloat();
	OnRXValue();
}

void ShortCalcuDig::slot_lneR_TextChanged()
{
	m_fR = ui.lne_R->text().toFloat();
	OnRXValue();
}

void ShortCalcuDig::slot_lneX_TextChanged()
{
	m_fX = ui.lne_X->text().toFloat();
	OnRXValue();
}

void ShortCalcuDig::slot_CmbCalModeIndexChanged( int index)
{
	m_nCalMode = index;

	switch(index)
	{
	case 0:
		{
			ui.lab_DLI->setDisabled(false);
			ui.lne_ShortI->setDisabled(false);
			ui.lab_DLV->setDisabled(true);
			ui.lne_ShortU->setDisabled(true);
			ui.lab_ZSZL->setDisabled(true);
			ui.lne_ZSZL->setDisabled(true);
		}
		break;
	case 1:
		{
			ui.lab_DLI->setDisabled(true);
			ui.lne_ShortI->setDisabled(true);
			ui.lab_DLV->setDisabled(false);
			ui.lne_ShortU->setDisabled(false);
			ui.lab_ZSZL->setDisabled(true);
			ui.lne_ZSZL->setDisabled(true);
		}
		break;
	case 2:
		{
			ui.lab_DLI->setDisabled(true);
			ui.lne_ShortI->setDisabled(true);
			ui.lab_DLV->setDisabled(true);
			ui.lne_ShortU->setDisabled(true);
			ui.lab_ZSZL->setDisabled(false);
			ui.lne_ZSZL->setDisabled(false);
		}
		break;
	default:
		break;
	}
}

void ShortCalcuDig::slot_lneDLDL_TextChanged()
{
	m_fDLI = ui.lne_ShortI->text().toFloat();
}

void ShortCalcuDig::slot_lneDLDY_TextChanged()
{
	m_fDLV = ui.lne_ShortU->text().toFloat();
}

void ShortCalcuDig::slot_lneZSZL_TextChanged()
{
	m_fZSZL= ui.lne_ZSZL->text().toFloat();
}

void ShortCalcuDig::slot_CmbCalTypeIndexChanged( int index)
{
	m_nCalType = index;
	switch(index)
	{
	case 0:
		{
		  ui.lab_Para1->setText(/*tr("幅值:")*/ g_sLangTxt_State_Amp);
               ui.lab_Para2->setText(/*tr("相角(°)")*/ g_sLangTxt_Native_PhaseAngle);
		}
		break;
	case 1:
		{
			ui.lab_Para1->setText(tr("Kr"));
			ui.lab_Para2->setText(tr("Kx"));
		}
		break;
	case 2:
		{
			 ui.lab_Para1->setText(/*tr("幅值：")*/ g_sLangTxt_State_Amp);
      ui.lab_Para2->setText(/*tr("相角(°)")*/ g_sLangTxt_Native_PhaseAngle);
		}
		break;
	default:
		break;
	}
}

void ShortCalcuDig::slot_lneFZ_TextChanged()
{
	m_fKr= ui.lne_CacuPara1->text().toFloat();
}

void ShortCalcuDig::slot_lneXJ_TextChanged()
{
	m_fKx= ui.lne_CacuPara2->text().toFloat();
}

void ShortCalcuDig::slot_lne_LoadI_TextChanged()
{
	m_fIfh= ui.lne_LoadI->text().toFloat();
}

void ShortCalcuDig::slot_lne_LoadAngle_TextChanged()
{
	m_fPowerAngle= ui.lne_LoadAngle->text().toFloat();
}

void ShortCalcuDig::slot_ConfirmClicked()
{
	Complex p1,p2;
	
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

	int index = ui.cmb_ChGroup->currentIndex();  //组号
	
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

	bool bHas4UModule = false;
	int nUstartpos = 0;
	int nIstartpos = 0;

	//模块只有一个，所以numOfUModule=0，numOfIModule=0
	if (m_pSttTestResource->m_oVolChRsListRef.GetCount()==4) 
	{
		bHas4UModule = true;
	}

	int tempnum = 0;
    if (bHas4UModule == true)
	{
		nUstartpos = index*3-tempnum +1;
	}
	else
	{
		nUstartpos = index*3-tempnum;
	}

	for (int i = 0; i < CHUList.size(); i++)
	{
		m_pStatePara->m_uiVOL[tempnum+nUstartpos+i].Harm[1].fAmp = CHUList[i].Harm[1].fAmp;
		m_pStatePara->m_uiVOL[tempnum+nUstartpos+i].Harm[1].fAngle = CHUList[i].Harm[1].fAngle;
		m_pStatePara->m_uiVOL[tempnum+nUstartpos+i].Harm[1].fFreq = CHUList[i].Harm[1].fFreq;
	}

	tempnum = 0;
    nIstartpos = index*3-tempnum;
	for (int i = 0; i < CHIList.size(); i++)
	{
		m_pStatePara->m_uiCUR[tempnum+nIstartpos+i].Harm[1].fAmp = CHIList[i].Harm[1].fAmp;
		m_pStatePara->m_uiCUR[tempnum+nIstartpos+i].Harm[1].fAngle = CHIList[i].Harm[1].fAngle;
		m_pStatePara->m_uiCUR[tempnum+nIstartpos+i].Harm[1].fFreq = CHIList[i].Harm[1].fFreq;
	}

	emit sig_ShortCalcuOk(m_para);

	close();
}

void ShortCalcuDig::slot_CancelClicked()
{
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

	ui.lne_Z->setText(QString::number(m_fZ,'f',3));
	ui.lne_Phi->setText(QString::number(m_fPhi,'f',3));
	ui.lne_R->setText(QString::number(m_fR,'f',3));
	ui.lne_X->setText(QString::number(m_fX,'f',3));
}

void ShortCalcuDig::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{

	}
}

