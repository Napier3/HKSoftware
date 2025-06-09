#include "QttMacroParaEditViewShortTimOver.h"
#include "ui_QttMacroParaEditViewShortTimOver.h"

#include "../../Module/XLangResource_Native.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//#include "../SttTestCntrFrameBase.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttGlobalDef.h"
#include "../Controls/SttCheckBox.h"

#include "../Controls/SttTabWidget.h"

QttMacroParaEditViewShortTimOver *g_pShortTimeOverTest;

QttMacroParaEditViewShortTimOver::QttMacroParaEditViewShortTimOver(QWidget *parent) : 
ui(new Ui::QttMacroParaEditViewShortTimOver)
{
	g_pShortTimeOverTest = this;
    ui->setupUi(this);

//	m_tabWidget = NULL;

	m_pUIParaWidget = NULL;	
	m_pParaSetSttTestResource = NULL;
	m_pSTOverPara = NULL;

	InitUI();

}

QttMacroParaEditViewShortTimOver::~QttMacroParaEditViewShortTimOver()
{
    delete ui;
}

void QttMacroParaEditViewShortTimOver::InitUI()
{

	ui->m_btnVolSTOver->setChecked(true);
	ui->m_labTotalTime->setEnabled(false);
	ui->m_edtTotalTime->setEnabled(false);
	ui->m_edtInflictFload->setText("0.000");

	ui->m_labFloadID->setText(_T("Un"));
	ui->m_labFloadID->setFixedWidth(30);

// 	m_strParaFileTitle = _T("短时过量模板文件") ; 
// 	m_strParaFilePostfix = tr("project(*.sttxml)");
// 	m_strDefaultParaFile = _P_GetConfigPath();
// 	m_strDefaultParaFile.append("ShortTimeOver.sttxml");

	m_pOriginalSttTestResource = stt_GetSttTestResource();
	//	CreateTestResource();
	stt_Frame_InitTestResource();

	BOOL bRet = OpenTestTestMngrFile(_T(""));

	InitTab_UI();
	SetParasFont();
}

void QttMacroParaEditViewShortTimOver::InitTab_UI()
{
//	m_tabWidget = new QSttTabWidget(this);
	m_pUIParaWidget = new QBasicTestParaSet/*(m_tabWidget)*/;
	ui->m_pVBoxLayout->addWidget(m_pUIParaWidget);
	/*m_tabWidget->insertTab(0,m_pUParaWidget,_T("电压短时过量"));
	m_tabWidget->insertTab(1,m_pIParaWidget,_T("电流短时过量"));*/


	ui->m_pVBoxLayout->addWidget(m_pUIParaWidget);
	/*ui->m_pVBoxLayout->setMargin(0);
	ui->m_pVBoxLayout->setSpacing(0);
	setLayout(ui->m_pVBoxLayout);	*/

	//InitUIGrid();
	SetDatas(NULL);
	InitData();

	//connect(m_pUIParaWidget->m_pParaSetImp->m_tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));
	connect(ui->m_edtOnceInflictTime, SIGNAL(editingFinished()), this, SLOT(on_m_edtOnceInflictTimeChanged()));
	connect(ui->m_edtIntervalTime, SIGNAL(editingFinished()), this, SLOT(on_m_edtIntervalTimeChanged()));
	connect(ui->m_edtInflictFload, SIGNAL(editingFinished()), this, SLOT(on_m_edtInflictFloadChanged()));

	connect(ui->m_btnVolSTOver,SIGNAL(toggled(bool)), this , SLOT(om_m_btnSTOverStateChanged()));
	connect(ui->m_btnVolSTOver,SIGNAL(toggled(bool)), this , SLOT(slot_UpdateChsAmp()));

	if (m_pUIParaWidget)
	{
		m_pUIParaWidget->setMacroType(MACROTYPE_Manual);
		m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pSTOverPara->m_uiVOL,m_pSTOverPara->m_uiCUR);
		m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}
}

void QttMacroParaEditViewShortTimOver::SetParasFont()
{
	ui->m_boxGroupChoose->setFont(*g_pSttGlobalFont);
	ui->m_btnVolSTOver->setFont(*g_pSttGlobalFont);
	ui->m_btnCurSTOver->setFont(*g_pSttGlobalFont);
	ui->m_edtInflictFload->setFont(*g_pSttGlobalFont);
	ui->m_labInflictFload->setFont(*g_pSttGlobalFont);
	ui->m_boxGroup->setFont(*g_pSttGlobalFont);
	ui->m_labFloadID->setFont(*g_pSttGlobalFont);
	ui->m_labInflictCount->setFont(*g_pSttGlobalFont);
	ui->m_cmbInflictCount->setFont(*g_pSttGlobalFont);
	ui->m_labOnceInflictTime->setFont(*g_pSttGlobalFont);
	ui->m_edtOnceInflictTime->setFont(*g_pSttGlobalFont);
	ui->m_labIntervalTime->setFont(*g_pSttGlobalFont);
	ui->m_edtIntervalTime->setFont(*g_pSttGlobalFont);
	ui->m_labTotalTime->setFont(*g_pSttGlobalFont);
	ui->m_edtTotalTime->setFont(*g_pSttGlobalFont);
	ui->m_labFloadID_4->setFont(*g_pSttGlobalFont);
	ui->m_labFloadID_2->setFont(*g_pSttGlobalFont);
	ui->m_labFloadID_3->setFont(*g_pSttGlobalFont);
}

void	QttMacroParaEditViewShortTimOver::InitData()
{

	if(m_pSTOverPara->m_nInflictCount <= 0)
	{
		m_pSTOverPara->m_nInflictCount = 1;
	}

	m_fVolInflictFload = 0.000;
	m_nVolInflictCount = m_pSTOverPara->m_nInflictCount;
	m_fVolOnceInflictTime = m_pSTOverPara->m_fOnceInflictTime;
	m_fVolIntervalTime = m_pSTOverPara->m_fIntervalTime;
	m_fVolTotalTime = 0;

	m_fCurInflictFload = 0.000;
	m_nCurInflictCount = m_pSTOverPara->m_nInflictCount;
	m_fCurOnceInflictTime = m_pSTOverPara->m_fOnceInflictTime;
	m_fCurIntervalTime = m_pSTOverPara->m_fIntervalTime;
	m_fCurTotalTime	= 0;

	CString strOITime,strITime;
	strOITime.Format("%.3f",m_fVolOnceInflictTime);
	strITime.Format("%.3f",m_fVolIntervalTime);
	ui->m_cmbInflictCount->setCurrentIndex(m_nVolInflictCount - 1);
	ui->m_edtOnceInflictTime->setText(strOITime);
	ui->m_edtIntervalTime->setText(strITime);
	UpdateTotalTime();
}

//void QttMacroParaEditViewShortTimOver::InitUIGrid()
//{
//	CDataGroup *pDataset = NULL;
//	//stt_xml_serialize(&m_oSTOverTest.m_oShortTimeOverParas, &oRead);
//
//	if (m_pUIParaWidget)
//	{
//		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-4  UIParaWidget");	}
//		//disconnect(m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()));
//		m_pUIParaWidget->setMacroType(MACROTYPE_State);
//		m_pUIParaWidget->setPropertyOfParaSet(P_Common,stt_GetSttTestResource(),m_pSTOverPara->m_uiVOL,m_pSTOverPara->m_uiCUR);
//		m_pUIParaWidget->setMaxMinAndEDVal();
//		//connect(m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
//		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-4  UIParaWidget");	}
//	}
//
//	m_pSTOverPara = &(m_oSTOverTest.m_oShortTimeOverParas);
//
//}


void QttMacroParaEditViewShortTimOver::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
/*
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	CString strTmpPath = _P_GetLibraryPath();
	strTmpPath.AppendFormat(_T("StateTestParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
		, tm.wHour, tm.wMinute, tm.wSecond);
	pParas->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);*/
}

//#include "../SttTestCntrThread.h"

void QttMacroParaEditViewShortTimOver::SetDatas(CDataGroup *pDataset)
{
	if (m_pUIParaWidget == NULL)
	{
		return;
	}

	if (pDataset != NULL)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-1");	}
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(&m_oSTOverTest.m_oShortTimeOverParas, &oRead);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-1");	}
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}

	//按钮的初始化，在btnWidget的setdatas里，把它里面的按钮状态改变

	m_pSTOverPara = &(m_oSTOverTest.m_oShortTimeOverParas.m_pParaShortTimeOver[0]);
	if (g_nLogDebugInfor == 1)	
	{		
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QttMacroParaEditViewShortTimOver::SetDatas -  >>");	
	}
	stt_Frame_InitVectorWidget(m_pSTOverPara->m_uiVOL,m_pSTOverPara->m_uiCUR);

	//m_pSTOverPara = &(m_oSTOverTest.m_oShortTimeOverParas);

// 	if (m_pUIParaWidget)
// 	{
// 		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-4  UIParaWidget");	}
// 		//disconnect(m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()));
// 		m_pUIParaWidget->setMacroType(MACROTYPE_State);
// 		m_pUIParaWidget->setPropertyOfParaSet(P_Common,stt_GetSttTestResource(),
// 			m_pSTOverPara->m_uiVOL,m_pSTOverPara->m_uiCUR);
// 		m_pUIParaWidget->setMaxMinAndEDVal();
// 
// 	}
		/*connect(m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-4  UIParaWidget");	}
	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitVectorWidget");	}
	stt_Frame_InitVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitPowerWidget");	}
	stt_Frame_InitPowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);*/

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "end State::SetDatas-6   InitVectorWidget");	}

#ifndef SttTestCntrThread_H
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-7  InitStateMonitor");	}
	stt_Frame_InitStateMonitor();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-7   InitStateMonitor");	}

	stt_Frame_ClearInfoWidget();	
#else
	//不能使用这种模式，因为需要new widget，在线程中 new 会崩溃
	CSttMacroParaEditInterface *pMacroParaEditInterface = (CSttMacroParaEditInterface*)this;
	g_theSttTestCntrThread->PostThreadMessage(11, (unsigned long)pMacroParaEditInterface, (unsigned long)pMacroParaEditInterface);
#endif

	UpdateStateParas();
}

void QttMacroParaEditViewShortTimOver::UpdateStateParas_Base()
{
	if (m_pUIParaWidget == NULL)
	{
		return;
	}

	if (m_pUIParaWidget)
	{
		m_pUIParaWidget->setData(m_pSTOverPara->m_uiVOL,m_pSTOverPara->m_uiCUR);
		m_pUIParaWidget->initData();
	}

	// 	if(m_pParaTab->m_pStateParaWidget)
	// 	{
	// 		m_pParaTab->m_pStateParaWidget->setData(m_pStatePara);
	// 	}


	m_pUIParaWidget->setMaxMinAndEDVal();
	//m_pUIParaWidget->DCStateChanged(P_Common,m_pStatePara->m_bDC);

	//UpdateBinBoutExTab();


	InitData();
}

void QttMacroParaEditViewShortTimOver::UpdateStateParas()
{
	UpdateStateParas_Base();
}


void QttMacroParaEditViewShortTimOver::OnViewTestLink(BOOL b)
{
	if(!b)
	{
		OnViewTestStop();
	}
}

void QttMacroParaEditViewShortTimOver::OnViewTestStart()
{
	m_pUIParaWidget->setEnabled(false);
	ui->m_boxGroup->setEnabled(false);
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]OnViewTestStart_StateTest."));

	//InitManuTrigerButton();
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pUIParaWidget->startInit();

	
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();


	/*CString strStateName;

	for(int i = 0; i < m_oStateTest.m_oStateParas.m_nStateNumbers; i++)
	{
		if(m_oStateTest.m_oStateParas.m_paraState[i].m_bSelected)
		{
			strStateName = m_oStateTest.m_oStateParas.m_paraState[i].m_strName;

			if (strStateName.IsEmpty())
			{
				strStateName = g_sLangTxt_State;
				strStateName.AppendFormat(_T("%ld"),i+1);
			}
			m_mapState.insert(m_mapState.size(),strStateName );
		}
	}*/
}

void QttMacroParaEditViewShortTimOver::OnViewTestStop()
{

	m_pUIParaWidget->setEnabled(true);
	ui->m_boxGroup->setEnabled(true);

	m_pUIParaWidget->stopInit();

	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();
}


void QttMacroParaEditViewShortTimOver::UpdateData()
{
	if(/*m_oSTOverTest == NULL || */m_pParaSetSttTestResource == NULL)
	{
		return;
	}

	m_nVChNums = m_pParaSetSttTestResource->m_oVolChRsListRef.GetCount();
	m_nIChNums = m_pParaSetSttTestResource->m_oCurChRsListRef.GetCount();
}


void QttMacroParaEditViewShortTimOver::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
													long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	m_nVolChRsNum = nVolRsNum;
	m_nCurChRsNum = nCurRsNum;
	SerializeTestParas_Base(pMacroParas,pParas,nVolRsNum,nCurRsNum,nBinExNum,nBoutExNum,false,false,false);
}

void QttMacroParaEditViewShortTimOver::SerializeTestParas_Base(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
														 long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub, BOOL bSmvAbnormal,BOOL bGooseAbnormal)
{
	tmt_short_time_over_test *pTmtStateTest = (tmt_short_time_over_test *)pParas;

	stt_xml_serialize_ex2(&pTmtStateTest->m_oShortTimeOverParas, pMacroParas,nVolRsNum,nCurRsNum);

}

void QttMacroParaEditViewShortTimOver::UpdateTotalTime()
{

	m_pSTOverPara->m_nInflictCount = ui->m_cmbInflictCount->currentText().toLong();
	m_pSTOverPara->m_fOnceInflictTime = ui->m_edtOnceInflictTime->text().toFloat();
	m_pSTOverPara->m_fIntervalTime = ui->m_edtIntervalTime->text().toFloat();
	
	float nTotalTime;
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		 nTotalTime = m_nVolInflictCount *( m_fVolOnceInflictTime+m_fVolIntervalTime)/* - m_fVolIntervalTime*/;
	}
	else
	{
		nTotalTime = m_nCurInflictCount *( m_fCurOnceInflictTime+m_fCurIntervalTime)/* - m_fCurIntervalTime*/;
	}

	CString strTotalTime;
	strTotalTime.Format("%.3f", nTotalTime);
	ui->m_edtTotalTime->setText(strTotalTime);
}

void QttMacroParaEditViewShortTimOver::UpdateChsAmp(tmt_Channel* pChannel, float fFload,  BOOL isVol)
{
	if(isVol == TRUE)
	{
		pChannel->Harm[1].fAmp = fFload * g_oSystemParas.m_fVNom;
	}
	else
	{
		pChannel->Harm[1].fAmp =  fFload * g_oSystemParas.m_fINom;
	}

	/*pChannel->Harm[1].fAngle *= fFload;
	pChannel->Harm[1].fFreq *= fFload;*/
}

void QttMacroParaEditViewShortTimOver::UpdateChsAmpEx(tmt_Channel* pChannel)
{
	pChannel->Harm[1].fAmp = 0;
}


void QttMacroParaEditViewShortTimOver::UpdateTestResource(BOOL bCreateChMaps)
{
	// 	ASSERT(g_theTestCntrFrame->m_pSttTestResource);
	// 	g_theTestCntrFrame->OnUpdateTestResource(bCreateChMaps);

	if (m_pUIParaWidget)
	{
		m_pUIParaWidget->initUI(stt_GetSttTestResource());
		m_pUIParaWidget->initData();
		m_pUIParaWidget->setMaxMinAndEDVal();
	}

}

void QttMacroParaEditViewShortTimOver::ChsAmpInRange()
{
	float fTemp;
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		fTemp = m_pSTOverPara->m_uiVOL[1].Harm[1].fAmp;
	}
	else
	{
		fTemp = m_pSTOverPara->m_uiCUR[1].Harm[1].fAmp;
	}

	if(fTemp != m_fCurrentAmp)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("幅值大于最大值，修改为最大值"));
	}

}


//void QttMacroParaEditViewShortTimOver::slot_TabPageChanged(int nIndex)
//{
//	QString strName = m_tabWidget->tabText(nIndex);
//	if (!strName.isEmpty())
//	{
//		if (strName.contains(_T("电压短时过量"))) //lcq
//		{
//			if(m_pUIParaWidget != NULL)
//			{
//				m_pUIParaWidget->initData();
//			}
//		}
//		else if (strName.contains(_T("电流短时过量"))) //lcq
//		{
//			if(m_pUIParaWidget != NULL)
//			{
//				m_pUIParaWidget->initData();
//			}
//		}
//	}
//
//}

void QttMacroParaEditViewShortTimOver::on_m_cmbInflictCount_currentIndexChanged(int index)
{
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		m_nVolInflictCount = index + 1;
	}
	else
	{
		m_nCurInflictCount = index + 1;
	}
	
	UpdateTotalTime();
}

void QttMacroParaEditViewShortTimOver::on_m_edtOnceInflictTimeChanged()
{
	CString strText;
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		if(ui->m_edtOnceInflictTime->text().toFloat() >= 0)
		{
			m_fVolOnceInflictTime = ui->m_edtOnceInflictTime->text().toFloat();
		}
		strText.Format("%.3f",m_fVolOnceInflictTime);
	}
	else
	{
		if(ui->m_edtOnceInflictTime->text().toFloat() >= 0)
		{
			m_fCurOnceInflictTime = ui->m_edtOnceInflictTime->text().toFloat();
		}
		strText.Format("%.3f",m_fCurOnceInflictTime);
	}

	ui->m_edtOnceInflictTime->setText(strText);
	UpdateTotalTime();
}

void QttMacroParaEditViewShortTimOver::on_m_edtIntervalTimeChanged()
{
	CString strText;
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		if(ui->m_edtIntervalTime->text().toFloat() >= 0)
		{
			m_fVolIntervalTime = ui->m_edtIntervalTime->text().toFloat();
		}
		strText.Format("%.3f",m_fVolIntervalTime);
	}
	else
	{
		if(ui->m_edtIntervalTime->text().toFloat() >= 0)
		{
			m_fCurIntervalTime = ui->m_edtIntervalTime->text().toFloat();
		}
		strText.Format("%.3f",m_fCurIntervalTime);
	}
	
	ui->m_edtIntervalTime->setText(strText);
	UpdateTotalTime();
}

void QttMacroParaEditViewShortTimOver::on_m_edtInflictFloadChanged()
{
	CString strText;
	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		if(ui->m_edtInflictFload->text().toFloat() >= 0)
		{
			m_fVolInflictFload = ui->m_edtInflictFload->text().toFloat();
		}
		for(int i=0; i<m_nVolChRsNum; ++i)
		{
			UpdateChsAmp(&m_pSTOverPara->m_uiVOL[i],m_fVolInflictFload, TRUE);
		}
		m_fCurrentAmp = m_pSTOverPara->m_uiVOL[1].Harm[1].fAmp;
		//m_fVolInflictFload = 1.000;
		strText.Format("%.3f",m_fVolInflictFload);
	}
	else
	{
		if(ui->m_edtInflictFload->text().toFloat() >= 0)
		{
			m_fCurInflictFload = ui->m_edtInflictFload->text().toFloat();
		}
		for(int i=0; i<m_nCurChRsNum; ++i)
		{
			UpdateChsAmp(&m_pSTOverPara->m_uiCUR[i],m_fCurInflictFload, FALSE);
		}
		//m_fCurInflictFload = 1.000;
		strText.Format("%.3f",m_fCurInflictFload);
		m_fCurrentAmp = m_pSTOverPara->m_uiCUR[1].Harm[1].fAmp;
	}

	m_pUIParaWidget->UpdateTables();
	ui->m_edtInflictFload->setText(strText);
	ChsAmpInRange();
}


void QttMacroParaEditViewShortTimOver::om_m_btnSTOverStateChanged()
{
	long nInflictCount;
	float fOnceInclictTime,fIntervalTime,fTotalTime;
	float fInflictFload = 0.000;

	nInflictCount = ui->m_cmbInflictCount->currentText().toLong();
	fOnceInclictTime = ui->m_edtOnceInflictTime->text().toFloat();
	fIntervalTime = ui->m_edtIntervalTime->text().toFloat();
	fTotalTime = ui->m_edtTotalTime->text().toFloat();

	if(ui->m_btnVolSTOver->isChecked() == TRUE)
	{
		ui->m_labFloadID->setText(_T("Un"));

		//m_fCurInflictFload = fInflictFload;
		m_nCurInflictCount = nInflictCount;
		m_fCurOnceInflictTime = fOnceInclictTime;
		m_fCurIntervalTime = fIntervalTime;
		m_fCurTotalTime = fTotalTime;

		//fInflictFload = m_fVolInflictFload;
		nInflictCount = m_nVolInflictCount;
		fOnceInclictTime = m_fVolOnceInflictTime;
		fIntervalTime = m_fVolIntervalTime;
		fTotalTime = m_fVolTotalTime;

		for(int i=0; i<m_nCurChRsNum; ++i)
		{
			UpdateChsAmpEx(&m_pSTOverPara->m_uiCUR[i]);
		}
	}
	else
	{

		ui->m_labFloadID->setText(_T("In"));

		//m_fVolInflictFload = fInflictFload;
		m_nVolInflictCount = nInflictCount;
		m_fVolOnceInflictTime = fOnceInclictTime;
		m_fVolIntervalTime = fIntervalTime;
		m_fVolTotalTime = fTotalTime;

		//fInflictFload = m_fCurInflictFload;
		nInflictCount = m_nCurInflictCount;
		fOnceInclictTime = m_fCurOnceInflictTime;
		fIntervalTime = m_fCurIntervalTime;
		fTotalTime = m_fCurTotalTime;

		for(int i=0; i<m_nVolChRsNum; ++i)
		{
			UpdateChsAmpEx(&m_pSTOverPara->m_uiVOL[i]);
		}
	}

	CString strInflictCount,strInflictFload,strOnceInclictTime,strIntervalTime,strTotalTime;
	strInflictFload.Format("%.3f",fInflictFload);
	strInflictCount.Format("%.3f",nInflictCount);
	strOnceInclictTime.Format("%.3f",fOnceInclictTime);
	strIntervalTime.Format("%.3f",fIntervalTime);
	strTotalTime.Format("%.3f",fTotalTime);

	ui->m_edtInflictFload->setText(strInflictFload);
	ui->m_cmbInflictCount->setCurrentIndex(nInflictCount - 1);
	ui->m_edtOnceInflictTime->setText(strOnceInclictTime);
	ui->m_edtIntervalTime->setText(strIntervalTime);
	ui->m_edtTotalTime->setText(strTotalTime);

	m_pUIParaWidget->UpdateTables();
}

void QttMacroParaEditViewShortTimOver::ShowReport( CDvmValues *pValues )
{
    stt_Frame_UpdateRptHtml();
}


void QttMacroParaEditViewShortTimOver::slot_updateParas()
{
    if (stt_Frame_TestCtrlFrame() == NULL)
	{
		return;
	}

	if (stt_Frame_IsTestStarted()) 
	{
		stt_Frame_Ats_UpdateParameter();
	}

	stt_Frame_UpdateVectorData();
	SetParaChanged();
}


