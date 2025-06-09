#include "SttMacroParaEditViewAnalogCirBreaker.h"
#include <QHBoxLayout>
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewAnalogCirBreaker* g_pAnalogCirBreaker = NULL;
QSttMacroParaEditViewAnalogCirBreaker::QSttMacroParaEditViewAnalogCirBreaker( QWidget *parent /*= 0*/ )
{
	g_pAnalogCirBreaker = this;
	m_pAnalogCirBreakerParaset = NULL;
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	
	OpenTestTestMngrFile(_T(""));

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();
	
	InitUI();
	InitConnection();
	InitData();
	SetDatas(NULL);
}

QSttMacroParaEditViewAnalogCirBreaker::~QSttMacroParaEditViewAnalogCirBreaker()
{

}


void QSttMacroParaEditViewAnalogCirBreaker::InitUI()
{	
	m_pAnalogCirBreakerParaset = new AnalogCirBreakerParaset;

	CString strText;
	QGroupBox *pMainGroupBox = new QGroupBox;
	strText = _T("模拟断路器功能测试(弹操机构)");
	pMainGroupBox->setTitle(strText);
	pMainGroupBox->setFont(*g_pSttGlobalFont);
	pMainGroupBox->setMaximumWidth(400);

	QGroupBox *pInitGroupBox = new QGroupBox;
	strText = _T("模断初始位置");
	pInitGroupBox->setTitle(strText);
	pInitGroupBox->setFont(*g_pSttGlobalFont);
	QHBoxLayout *pInitLayout = new QHBoxLayout(pInitGroupBox);
	QLabel *pInitLabel = new QLabel;
	pInitLabel->setFont(*g_pSttGlobalFont);
	strText = _T("模拟断路器初始位置");
	pInitLabel->setText(strText);
	m_pInitPositionCombox = new QScrollComboBox;
	m_pInitPositionCombox->setFont(*g_pSttGlobalFont);
	m_pInitPositionCombox->addItems(QStringList()<<_T("合位")<<_T("分位"));
	pInitLayout->addWidget(pInitLabel);
	pInitLayout->addWidget(m_pInitPositionCombox);
	m_pInitPositionCombox->setMaximumWidth(120);

	QGroupBox *pActionGroupBox = new QGroupBox;
	strText = _T("动作信号输入");
	pActionGroupBox->setTitle(strText);
	pActionGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pActionLayout = new QGridLayout(pActionGroupBox);
	QLabel *pClosingLabel = new QLabel;
	pClosingLabel->setFont(*g_pSttGlobalFont);
	strText = _T("合闸脉冲");
	pClosingLabel->setText(strText);
	m_pClosePulseCombox = new QScrollComboBox(this,false);
	m_pBinComboBoxList.append(m_pClosePulseCombox);
	m_pClosePulseCombox->setFont(*g_pSttGlobalFont);
	m_pClosePulseCombox->addItems(QStringList()<<_T("开入A")<<_T("开入B")<<_T("开入C")<<_T("开入D"));
	
	m_pActionCloseLabel = new QLabel;
	QIcon ActionCloseIcon = SetIconPic(0);
	QPixmap pixmap = ActionCloseIcon.pixmap(20, 20); 
	m_pActionCloseLabel->setPixmap(pixmap);
	m_pActionCloseLabel->setAlignment(Qt::AlignCenter); 
	QLabel *pOpenLabel = new QLabel;
	pOpenLabel->setFont(*g_pSttGlobalFont);
	strText = _T("分闸脉冲");
	pOpenLabel->setText(strText);
	m_pOpenPulseCombox = new QScrollComboBox(this,false);
	m_pBinComboBoxList.append(m_pOpenPulseCombox);
	m_pOpenPulseCombox->setFont(*g_pSttGlobalFont);
	m_pOpenPulseCombox->addItems(QStringList()<<_T("开入A")<<_T("开入B")<<_T("开入C")<<_T("开入D"));

	m_pActionOpenLabel = new QLabel;
	QIcon ActionOpenIcon = SetIconPic(0);
	QPixmap pixmap1 = ActionOpenIcon.pixmap(20, 20); 
	m_pActionOpenLabel->setPixmap(pixmap1);
	m_pActionOpenLabel->setAlignment(Qt::AlignCenter); 
	pActionLayout->addWidget(pClosingLabel,0,0,1,1);
	pActionLayout->addWidget(m_pActionCloseLabel,0,1,1,1);
	pActionLayout->addWidget(m_pClosePulseCombox,0,2,1,1);
	pActionLayout->addWidget(pOpenLabel,1,0,1,1);
	pActionLayout->addWidget(m_pActionOpenLabel,1,1,1,1);
	pActionLayout->addWidget(m_pOpenPulseCombox,1,2,1,1);


	QGroupBox *pPositionGroupBox = new QGroupBox;
	strText = _T("位置信号输出");
	pPositionGroupBox->setTitle(strText);
	pPositionGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pPositionLayout = new QGridLayout(pPositionGroupBox);
	
	QLabel *pCloseSignalLabel = new QLabel;
	pCloseSignalLabel->setFont(*g_pSttGlobalFont);
	strText = _T("合位信号");
	pCloseSignalLabel->setText(strText);
	m_pCloseSignalCombox = new QScrollComboBox(this,false);
	m_pBoutComboBoxList.append(m_pCloseSignalCombox);
	m_pCloseSignalCombox->setFont(*g_pSttGlobalFont);
	QStringList oList;
	for (int i=0; i<g_nBinCount; i++)
	{
		strText.Format(_T("开出%d"),i+1);
		oList.append(strText);
	} 
	oList << _T("空");
 	m_pCloseSignalCombox->addItems(oList);
	m_pPosCloseLabel = new QLabel;
	QIcon PosCloseIcon = SetIconPic(0);
	m_pPosCloseLabel->setPixmap(PosCloseIcon.pixmap(20, 20));
	m_pPosCloseLabel->setAlignment(Qt::AlignCenter); 

	QLabel *pOpenSignalLabel = new QLabel;
	pOpenSignalLabel->setFont(*g_pSttGlobalFont);
	strText = _T("分位信号");
	pOpenSignalLabel->setText(strText);
	m_pOpenSiganlCombox = new QScrollComboBox(this,false);
	m_pBoutComboBoxList.append(m_pOpenSiganlCombox);
	m_pOpenSiganlCombox->setFont(*g_pSttGlobalFont);
	m_pOpenSiganlCombox->addItems(oList);
	m_pPosOpenLabel = new QLabel;
	QIcon PosOpenIcon = SetIconPic(0);
	m_pPosOpenLabel->setPixmap(PosOpenIcon.pixmap(20, 20));
	m_pPosOpenLabel->setAlignment(Qt::AlignCenter); 

	QLabel *pEnergyLabel = new QLabel;
	pEnergyLabel->setFont(*g_pSttGlobalFont);
	strText = _T("未储能信号");
	pEnergyLabel->setText(strText);
	m_pEnergyCombox = new QScrollComboBox(this,false);
	m_pBoutComboBoxList.append(m_pEnergyCombox);
	m_pEnergyCombox->setFont(*g_pSttGlobalFont);
	m_pEnergyCombox->addItems(oList);

	m_pPosUnEnergyLabel = new QLabel;
	QIcon PosUnEnergyIcon = SetIconPic(2);
	m_pPosUnEnergyLabel->setPixmap(PosUnEnergyIcon.pixmap(20, 20));
	m_pPosUnEnergyLabel->setAlignment(Qt::AlignCenter); 
	pPositionLayout->addWidget(pCloseSignalLabel,0,0,1,1);
	pPositionLayout->addWidget(m_pPosCloseLabel,0,1,1,1);
	pPositionLayout->addWidget(m_pCloseSignalCombox,0,2,1,1);
	pPositionLayout->addWidget(pOpenSignalLabel,1,0,1,1);
	pPositionLayout->addWidget(m_pPosOpenLabel,1,1,1,1);
	pPositionLayout->addWidget(m_pOpenSiganlCombox,1,2,1,1);
	pPositionLayout->addWidget(pEnergyLabel,2,0,1,1);
	pPositionLayout->addWidget(m_pPosUnEnergyLabel,2,1,1,1);
	pPositionLayout->addWidget(m_pEnergyCombox,2,2,1,1);


	QGroupBox *pDelayTimeGroupBox = new QGroupBox;
	strText = _T("延时时间设置");
	pDelayTimeGroupBox->setTitle(strText);
	pDelayTimeGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pDelayTimeLayout = new QGridLayout(pDelayTimeGroupBox);
	QLabel *pCloseDelaylLabel = new QLabel;
	pCloseDelaylLabel->setFont(*g_pSttGlobalFont);
	strText = _T("合闸延时");
	pCloseDelaylLabel->setText(strText);
	m_pCloseDelayEdit = new QLineEdit;
	m_pCloseDelayEdit->setFont(*g_pSttGlobalFont);
	m_pCloseDelayEdit->setMaximumWidth(120);
	m_pCloseDelayEdit->setText(_T("0.00"));
	QLabel *pLabel1= new QLabel;
	pLabel1->setFont(*g_pSttGlobalFont);
	strText = _T("ms");
	pLabel1->setText(strText);
	QLabel *pLabel2= new QLabel;
	pLabel2->setFont(*g_pSttGlobalFont);
	pLabel2->setText(strText);
	QLabel *pOpenDelaylLabel = new QLabel;
	pOpenDelaylLabel->setFont(*g_pSttGlobalFont);
	strText = _T("分闸延时");
	pOpenDelaylLabel->setText(strText);
	m_pOpenDelayEdit = new QLineEdit;
	m_pOpenDelayEdit->setFont(*g_pSttGlobalFont);
	m_pOpenDelayEdit->setMaximumWidth(120);
	m_pOpenDelayEdit->setText(_T("0.00"));
	pDelayTimeLayout->addWidget(pCloseDelaylLabel,0,0,1,1);
	pDelayTimeLayout->addWidget(m_pCloseDelayEdit,0,1,1,1);
	pDelayTimeLayout->addWidget(pLabel1,0,2,1,1);
	pDelayTimeLayout->addWidget(pOpenDelaylLabel,0,3,1,1);
	pDelayTimeLayout->addWidget(m_pOpenDelayEdit,0,4,1,1);
	pDelayTimeLayout->addWidget(pLabel2,0,5,1,1);

	QGroupBox *pIntersectGroupBox = new QGroupBox;
	strText = _T("模断当前位置");
	pIntersectGroupBox->setTitle(strText);
	pIntersectGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pIntersectLayout = new QGridLayout(pIntersectGroupBox);
	QLabel *pIntersectLabel= new QLabel;
	pIntersectLabel->setFont(*g_pSttGlobalFont);
	strText = _T("模拟断路当前位置指示");
	pIntersectLabel->setText(strText);
	QLabel *pLabel3= new QLabel;
	pLabel3->setFont(*g_pSttGlobalFont);
	strText = _T("合位");
	pLabel3->setText(strText);
	QLabel *pLabel4= new QLabel;
	pLabel4->setFont(*g_pSttGlobalFont);
	strText = _T("分位");
	pLabel4->setText(strText);
	m_pCurPosCloseLabel = new QLabel;
	QIcon CurPosCloseIcon = SetIconPic(5);
	m_pCurPosCloseLabel->setPixmap(CurPosCloseIcon.pixmap(20, 20));
	m_pCurPosCloseLabel->setAlignment(Qt::AlignCenter); 
	m_pCurPosOpenLabel = new QLabel;
	QIcon CurPosOpenIcon = SetIconPic(5);
	m_pCurPosOpenLabel->setPixmap(CurPosOpenIcon.pixmap(20, 20));
	m_pCurPosOpenLabel->setAlignment(Qt::AlignCenter); 
	
	pIntersectLayout->addWidget(pIntersectLabel,0,0,1,1);
	pIntersectLayout->addWidget(m_pCurPosCloseLabel,0,1,1,1);
	pIntersectLayout->addWidget(pLabel3,0,2,1,1, Qt::AlignLeft);
	pIntersectLayout->addWidget(m_pCurPosOpenLabel,0,3,1,1);
	pIntersectLayout->addWidget(pLabel4,0,4,1,1, Qt::AlignLeft);



	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(pInitGroupBox, 1);
	pMainLayout->addWidget(pActionGroupBox, 1);
	pMainLayout->addWidget(pPositionGroupBox, 2);
	pMainLayout->addWidget(pDelayTimeGroupBox, 1);
	pMainLayout->addWidget(pIntersectGroupBox, 1);
	pMainGroupBox->setLayout(pMainLayout);
	m_pAnalogCirBreakerParaset->m_pMainHBoxLayout->addWidget(pMainGroupBox);

	setLayout(m_pAnalogCirBreakerParaset->m_pMainHBoxLayout);
	setFocusPolicy(Qt::StrongFocus);


	m_pActionCloseLabel->setObjectName(_T("ActionClose"));
	m_pActionOpenLabel->setObjectName(_T("ActionOpen"));
	m_pPosCloseLabel->setObjectName(_T("PosClose"));
	m_pPosOpenLabel->setObjectName(_T("PosOpen"));
	m_pPosUnEnergyLabel->setObjectName(_T("PosUnEnergy"));
	m_pCurPosCloseLabel->setObjectName(_T("CurPosClose"));
	m_pCurPosOpenLabel->setObjectName(_T("CurPosOpen"));

	m_pCloseSignalCombox->setObjectName(_T("CloseSignal"));
	m_pOpenSiganlCombox->setObjectName(_T("OpenSignal"));
	m_pEnergyCombox->setObjectName(_T("EnergySignal"));
}

void QSttMacroParaEditViewAnalogCirBreaker::InitData()
{
	long nCurRsNum = g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum();
	CString strID;
	float fAmp,fAngle,fFreq;
	for(int nIndex = 0; nIndex < nCurRsNum; nIndex++)
	{
		strID.Format(_T("I%d"), nIndex + 1);
		stt_GetDataValueByID(&m_pAnalogCirBreakerData,strID,fAmp);
		m_uiCUR[nIndex].Harm[1].fAmp = fAmp;
		strID.Format(_T("I%dPh"), nIndex + 1);
		stt_GetDataValueByID(&m_pAnalogCirBreakerData,strID,fAngle);
		m_uiCUR[nIndex].Harm[1].fAngle = fAngle;
		strID.Format(_T("I%dFre"), nIndex + 1);
		stt_GetDataValueByID(&m_pAnalogCirBreakerData,strID,fFreq);
		m_uiCUR[nIndex].Harm[1].fFreq = fFreq;
	}

	m_pAnalogCirBreakerParaset->setMacroType(MACROTYPE_Manual);
	m_pAnalogCirBreakerParaset->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_uiCUR);
	m_pAnalogCirBreakerParaset->setMaxMinAndEDVal();

	long nInitPosIndex;
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("InitPos"),nInitPosIndex);
	m_pInitPositionCombox->setCurrentIndex(nInitPosIndex);

	QStringList oListBin,oListBout;
	oListBin << _T("_BinA")<<_T("_BinB")<<_T("_BinC")<<_T("_BinD");

	for (int i=0; i<g_nBinCount; i++)
	{
		strID.Format(_T("_Bout%d"),i+1);
		oListBout.append(strID);
	}
    CString strClosePulse,strOpenPulse;
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("ClosePulse"),strClosePulse);
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("OpenPulse"),strOpenPulse);

	for (int i = 0; i < oListBin.size(); ++i) 
	{
		if (oListBin[i] == strClosePulse) 
		{
			m_pClosePulseCombox->setCurrentIndex(i);
		}
		if (oListBin[i] == strOpenPulse) 
		{
			m_pOpenPulseCombox->setCurrentIndex(i);
		}
	}

	CString strCloseSignal,strOpenSiganl,strEnergySignal;
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("CloseSignal"),strCloseSignal);
	if (strCloseSignal == _T("空"))
	{
		m_pCloseSignalCombox->setCurrentIndex(m_pCloseSignalCombox->count() - 1);
	}
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("OpenSiganl"),strOpenSiganl);
	if (strOpenSiganl == _T("空"))
	{
		m_pOpenSiganlCombox->setCurrentIndex(m_pOpenSiganlCombox->count() - 1);
	}
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("EnergySignal"),strEnergySignal);
	if (strEnergySignal == _T("空"))
	{
		m_pEnergyCombox->setCurrentIndex(m_pEnergyCombox->count() - 1);
	}
	
	for (int i = 0; i < oListBout.size(); ++i) 
	{
		if (oListBout[i] == strCloseSignal) 
		{
			m_pCloseSignalCombox->setCurrentIndex(i);
		}
		if (oListBout[i] == strOpenSiganl) 
		{
			m_pOpenSiganlCombox->setCurrentIndex(i);
		}
		if (oListBout[i] == strEnergySignal)
		{
			m_pEnergyCombox->setCurrentIndex(i);
		}
	}
	
	float fValue;
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("CloseDelayTime"),fValue);
	m_pCloseDelayEdit->setText(QString::number(fValue,'f',0));
	stt_GetDataValueByID(&m_pAnalogCirBreakerData,_T("OpenDelayTime"),fValue);
	m_pOpenDelayEdit->setText(QString::number(fValue,'f', 0));
}

void QSttMacroParaEditViewAnalogCirBreaker::InitConnection()
{
	connect(m_pAnalogCirBreakerParaset,SIGNAL(sig_updataParas(int,int,float)),this,SLOT(slot_updateParas(int,int,float)), Qt::UniqueConnection);
	
	for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
	{
		QScrollComboBox* pComboBox = m_pBinComboBoxList.at(i);
		connect(pComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BinComboBoxChanged(int)));
	}

	for (int i = 0; i < m_pBoutComboBoxList.size(); ++i) 
	{
		QScrollComboBox* pComboBox = m_pBoutComboBoxList.at(i);
		connect(pComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BoutComboBoxChanged(int)));
	}
	connect(m_pInitPositionCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_InitPositionComboBoxChanged(int)));
	connect(m_pCloseDelayEdit, SIGNAL(editingFinished ()), this, SLOT(slot_CloseDelay_editingFinished()));
	connect(m_pOpenDelayEdit, SIGNAL(editingFinished ()), this, SLOT(slot_OpenDelay_editingFinished()));
	connect(m_pAnalogCirBreakerParaset,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);

}

void QSttMacroParaEditViewAnalogCirBreaker::UpdateTestResource( BOOL bCreateChMaps )
{
	m_pAnalogCirBreakerParaset->initUI(g_theTestCntrFrame->GetSttTestResource());	
	m_pAnalogCirBreakerParaset->setMaxMinAndEDVal();
	m_pAnalogCirBreakerParaset->initData();
}

CSttTestResourceBase* QSttMacroParaEditViewAnalogCirBreaker::CreateTestResource()
{
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewAnalogCirBreaker::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();

	UpdateParas();
	m_pAnalogCirBreakerData.CopyChildren(pParas);
}

void QSttMacroParaEditViewAnalogCirBreaker::SetDatas( CDataGroup *pDataset )
{
	g_theTestCntrFrame->InitVectorWidget(NULL,m_uiCUR);
	g_theTestCntrFrame->InitPowerWidget(NULL,m_uiCUR);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();	

	//SaveParasXml();
}

void QSttMacroParaEditViewAnalogCirBreaker::OnViewTestStart()
{
	for (int i = 0; i < m_pBoutComboBoxList.size(); ++i) 
	{
		QScrollComboBox *pComboBox = m_pBoutComboBoxList.at(i);
		pComboBox->setDisabled(true);
	}
	for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
	{
		QScrollComboBox *pComboBox = m_pBinComboBoxList.at(i);
		pComboBox->setDisabled(true);
	}
	m_pCloseDelayEdit->setDisabled(true);
	m_pOpenDelayEdit->setDisabled(true);
	m_pInitPositionCombox->setDisabled(true);
	m_pAnalogCirBreakerParaset->m_pIGroupBox->setDisabled(true);

	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewAnalogCirBreaker::OnViewTestStop()
{
	for (int i = 0; i < m_pBoutComboBoxList.size(); ++i) 
	{
		QScrollComboBox *pComboBox = m_pBoutComboBoxList.at(i);
		pComboBox->setDisabled(false);
	}
	for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
	{
		QScrollComboBox *pComboBox = m_pBinComboBoxList.at(i);
		pComboBox->setDisabled(false);
	}
	m_pCloseDelayEdit->setDisabled(false);
	m_pOpenDelayEdit->setDisabled(false);	
	m_pInitPositionCombox->setDisabled(false);
	m_pAnalogCirBreakerParaset->m_pIGroupBox->setDisabled(false);

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);
	g_theTestCntrFrame->StopPowerWidget();


	m_pActionCloseLabel->clear(); 
	m_pActionCloseLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
	m_pActionOpenLabel->clear(); 
	m_pActionOpenLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
	
	m_pCurPosCloseLabel->clear(); 
	m_pCurPosCloseLabel->setPixmap(SetIconPic(5).pixmap(20, 20));
	m_pCurPosOpenLabel->clear(); 
	m_pCurPosOpenLabel->setPixmap(SetIconPic(5).pixmap(20, 20));


	m_pPosCloseLabel->clear(); 
	if (m_pCloseSignalCombox->currentText() != _T("空"))
	{
		m_pPosCloseLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
	}
	else
	{
		m_pPosCloseLabel->setPixmap(SetIconPic(2).pixmap(20, 20));
	}
	m_pPosOpenLabel->clear(); 
	if (m_pOpenSiganlCombox->currentText() != _T("空"))
	{
		m_pPosOpenLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
	}
	else
	{
		m_pPosOpenLabel->setPixmap(SetIconPic(2).pixmap(20, 20));
	}

	m_pPosUnEnergyLabel->clear(); 
	if (m_pEnergyCombox->currentText() != _T("空"))
	{
		m_pPosUnEnergyLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
	}
	else
	{
		m_pPosUnEnergyLabel->setPixmap(SetIconPic(2).pixmap(20, 20));
	}
}

void QSttMacroParaEditViewAnalogCirBreaker::UpdateComboBox( QStringList pList,QList<QScrollComboBox*> pComboBoxList ,bool b)
{
	QList<QString> pSelectedValues;
	pSelectedValues.clear();
	foreach (QScrollComboBox* pComboBox, pComboBoxList)
	{
		QString currentText = pComboBox->currentText();
		if (currentText != _T("空"))
		{
			pSelectedValues.append(currentText);
		}
	}

	foreach (QScrollComboBox* pComboBox, pComboBoxList)
	{
		QString currentText = pComboBox->currentText();
		pComboBox->blockSignals(true); 
		pComboBox->clear();
		foreach (const QString& value,  pList)
		{
			if (!pSelectedValues.contains(value) || value == currentText)
			{
				pComboBox->addItem(value);
			}
		}
		if (b)
		{
			pComboBox->addItem(_T("空"));
		}

		int nIndex = pComboBox->findText(currentText);
		if (nIndex != -1)
		{
			pComboBox->setCurrentIndex(nIndex);
		}
		else if(b)
		{
			pComboBox->setCurrentIndex(pComboBox->findText(_T("空")));
		}

		pComboBox->blockSignals(false); 
	}
}


BOOL QSttMacroParaEditViewAnalogCirBreaker::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if ((m_pAnalogCirBreakerData.GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,&m_pAnalogCirBreakerData);
	}
	return TRUE;
}

void QSttMacroParaEditViewAnalogCirBreaker::UpdateEventMsg( CEventResult *pCurrEventResult )
{
	if(pCurrEventResult == NULL)
	{
		return;
	}
	CString strText,strID;
	QStringList oListBin,oListBout;
	oListBin << _T("_BinA")<<_T("_BinB")<<_T("_BinC")<<_T("_BinD");
	for (int i=0; i<g_nBinCount; i++)
	{
		strID.Format(_T("_Bout%d"),i+1);
		oListBout.append(strID);
	}

	for (int i=0; i< oListBin.size(); i++)
	{
		strText = oListBin.at(i);
		for (int j = 0; j < m_pBinLabelList.size(); j++) 
		{
			QLabel* pLabel = m_pBinLabelList.at(j).first;
			if (strText == m_pBinLabelList.at(j).second) 
			{
				if (pCurrEventResult->m_BinIn[i] != 0)
				{
					pLabel->clear(); 
					pLabel->setPixmap(SetIconPic(1).pixmap(20, 20));
				}
				else
				{
					pLabel->clear(); 
					pLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
				}
			}
		}
	}
	

	for (int i=0; i< g_nBoutCount; i++)
	{
		strText = oListBout.at(i);
		for (int j = 0; j < m_pBoutLabelList.size(); j++) 
		{
			QLabel* pLabel = m_pBoutLabelList.at(j).first;
			if (strText == m_pBoutLabelList.at(j).second) 
			{
				if (pCurrEventResult->m_BinOut[i] != 0)
				{
					pLabel->clear(); 
					if (pLabel->objectName() == _T("CurPosClose"))
					{
						pLabel->setPixmap(SetIconPic(4).pixmap(20, 20));
					}
					else if (pLabel->objectName() == _T("CurPosOpen"))
					{
						pLabel->setPixmap(SetIconPic(3).pixmap(20, 20));
					}
					else
					{
						pLabel->setPixmap(SetIconPic(1).pixmap(20, 20));
					}
				}
				else
				{
					pLabel->clear(); 
					if (pLabel->objectName() == _T("CurPosClose") || pLabel->objectName() == _T("CurPosOpen"))
					{
						pLabel->setPixmap(SetIconPic(5).pixmap(20, 20));
					}
					else if (pLabel->objectName() == _T("PosUnEnergy"))
					{
						if (m_pEnergyCombox->currentText() == _T("空"))
						{
							pLabel->setPixmap(SetIconPic(2).pixmap(20, 20));
						}
						else
						{
							pLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
						}
					}
					else
					{
					    pLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
					}
				}
			}
		}
	}
}

void QSttMacroParaEditViewAnalogCirBreaker::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/AnalogCirBreaker_Paras.xml");
	m_pAnalogCirBreakerData.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewAnalogCirBreaker::UpdateParas()
{
	m_pBinLabelList.clear();
	m_pBoutLabelList.clear();

	long nInitPosIndex = m_pInitPositionCombox->currentIndex();
	CString strClosePulse = m_pClosePulseCombox->currentText();//合闸脉冲
	CString strOpenPulse = m_pOpenPulseCombox->currentText();//分闸脉冲
	CString strCloseSignal = m_pCloseSignalCombox->currentText();//合位信号
	CString strOpenSignal = m_pOpenSiganlCombox->currentText();//分位信号
	CString strEnergySignal = m_pEnergyCombox->currentText();//未储能信号

	QStringList oListBin,oListBout;
	CString strID;
	oListBin << _T("_BinA")<<_T("_BinB")<<_T("_BinC")<<_T("_BinD");
	for (int i=0; i<g_nBinCount; i++)
	{
		strID.Format(_T("_Bout%d"),i+1);
		oListBout.append(strID);
	}


	CDataGroup *pState1Data = (CDataGroup *)m_pAnalogCirBreakerData.FindByID(_T("state0"));
	CDataGroup *pState2Data = (CDataGroup *)m_pAnalogCirBreakerData.FindByID(_T("state1"));

	if (strOpenPulse != _T("空"))
	{
		strOpenPulse = strOpenPulse.Right(1);
		strOpenPulse = _T("_Bin") + strOpenPulse;
	}

	if (strCloseSignal != _T("空"))
	{
		strCloseSignal = strCloseSignal.Right(1);
		strCloseSignal = _T("_Bout") + strCloseSignal;
	}

	if (strEnergySignal != _T("空"))
	{
		strEnergySignal = strEnergySignal.Right(1);
		strEnergySignal = _T("_Bout") + strEnergySignal;
	}

	if (strClosePulse != _T("空"))
	{
		strClosePulse = strClosePulse.Right(1);
		strClosePulse = _T("_Bin") + strClosePulse;
	}

	if (strOpenSignal != _T("空"))
	{
		strOpenSignal = strOpenSignal.Right(1);
		strOpenSignal = _T("_Bout") + strOpenSignal;
	}

	m_pBinLabelList.append(qMakePair(m_pActionCloseLabel,strClosePulse));
	m_pBinLabelList.append(qMakePair(m_pActionOpenLabel,strOpenPulse));

	m_pBoutLabelList.append(qMakePair(m_pPosCloseLabel,strCloseSignal));
	m_pBoutLabelList.append(qMakePair(m_pPosOpenLabel,strOpenSignal));
	m_pBoutLabelList.append(qMakePair(m_pPosUnEnergyLabel,strEnergySignal));
	m_pBoutLabelList.append(qMakePair(m_pCurPosCloseLabel,strCloseSignal));
	m_pBoutLabelList.append(qMakePair(m_pCurPosOpenLabel,strOpenSignal));

	float fCloseDelay = m_pCloseDelayEdit->text().toFloat();
	float fOpenDelay = m_pOpenDelayEdit->text().toFloat();


	m_pAnalogCirBreakerData.SetDataValue(_T("ClosePulse"), strClosePulse);
	m_pAnalogCirBreakerData.SetDataValue(_T("OpenPulse"), strOpenPulse);
	m_pAnalogCirBreakerData.SetDataValue(_T("CloseSignal"), strCloseSignal);
	m_pAnalogCirBreakerData.SetDataValue(_T("OpenSiganl"), strOpenSignal);
	m_pAnalogCirBreakerData.SetDataValue(_T("EnergySignal"), strEnergySignal);
	m_pAnalogCirBreakerData.SetDataValue(_T("CloseDelayTime"), fCloseDelay);
	m_pAnalogCirBreakerData.SetDataValue(_T("OpenDelayTime"), fOpenDelay);

	fCloseDelay = fCloseDelay / 1000;
	fOpenDelay = fOpenDelay / 1000;


	if (nInitPosIndex == 0)//合位
	{
		//状态1
		if(pState1Data)
		{
			for (int i = 0; i < oListBin.size(); ++i) 
			{
				if (oListBin[i] == strOpenPulse) 
				{
					pState1Data->SetDataValue(strOpenPulse, long(1));
				}
				else
				{
					pState1Data->SetDataValue(oListBin[i], long(0));
				}
			}

			for (int j = 0; j < oListBout.size(); ++j) 
			{
				if (oListBout[j] == strCloseSignal) 
				{
					pState1Data->SetDataValue(strCloseSignal, long(1));
				}
				else
				{
					pState1Data->SetDataValue(oListBout[j], long(0));
				}
			}
			pState1Data->SetDataValue(strEnergySignal, long(1));
			pState1Data->SetDataValue(_T("DelayTime1"), fCloseDelay);
		}

		//状态2
		if(pState2Data)
		{
			for (int i = 0; i < oListBin.size(); ++i) 
			{
				if (oListBin[i] == strClosePulse) 
				{
					pState2Data->SetDataValue(strClosePulse, long(1));
				}
				else
				{
					pState2Data->SetDataValue(oListBin[i], long(0));
				}
			}

			for (int j = 0; j < oListBout.size(); ++j) 
			{
				if (oListBout[j] == strOpenSignal) 
				{
					pState2Data->SetDataValue(strOpenSignal, long(1));
				}
				else
				{
					pState2Data->SetDataValue(oListBout[j], long(0));
				}
			}
			pState2Data->SetDataValue(strEnergySignal, long(1));
			pState2Data->SetDataValue(_T("DelayTime2"), fOpenDelay);
		}
	}
	else //分位
	{
		//状态1
		if(pState1Data)
		{
			for (int i = 0; i < oListBin.size(); ++i) 
			{
				if (oListBin[i] == strClosePulse) 
				{
					pState1Data->SetDataValue(strClosePulse, long(1));
				}
				else
				{
					pState1Data->SetDataValue(oListBin[i], long(0));
				}
			}

			for (int j = 0; j < oListBout.size(); ++j) 
			{
				if (oListBout[j] == strOpenSignal) 
				{
					pState1Data->SetDataValue(strOpenSignal, long(1));
				}
				else
				{
					pState1Data->SetDataValue(oListBout[j], long(0));
				}
			}
			pState1Data->SetDataValue(strEnergySignal, long(1));
			pState1Data->SetDataValue(_T("DelayTime1"), fOpenDelay);
		}

		//状态2
		if(pState2Data)
		{
			for (int i = 0; i < oListBin.size(); ++i) 
			{
				if (oListBin[i] == strOpenPulse) 
				{
					pState2Data->SetDataValue(strOpenPulse, long(1));
				}
				else
				{
					pState2Data->SetDataValue(oListBin[i], long(0));
				}
			}

			for (int j = 0; j < oListBout.size(); ++j) 
			{
				if (oListBout[j] == strCloseSignal) 
				{
					pState2Data->SetDataValue(strCloseSignal, long(1));
				}
				else
				{
					pState2Data->SetDataValue(oListBout[j], long(0));
				}
			}
			pState2Data->SetDataValue(strEnergySignal, long(1));
			pState2Data->SetDataValue(_T("DelayTime2"), fCloseDelay);
		}
	}
}



QIcon QSttMacroParaEditViewAnalogCirBreaker::SetIconPic( int nState )
{
	CString strPicPath;
	const char* iconNames[] = 
	{
		"switch_open.png",
		"switch_close.png",
		"Clip011.png",
		"circle_green.png",
		"circle_red.png",
		"circle_black.png"
	};

	if (nState < 0)  return QIcon(); 

#ifdef _PSX_QT_WINDOWS_
	strPicPath = _P_GetResourcePath();
	strPicPath = strPicPath + iconNames[nState];
#else
	strPicPath = ":/ctrls/images/" + CString(iconNames[nState]);
#endif

	return QIcon(strPicPath);
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_InitPositionComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}
	m_pAnalogCirBreakerData.SetDataValue(_T("InitPos"),long(index));
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_BinComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}
	QStringList oList;
	oList << _T("开入A")<<_T("开入B")<<_T("开入C")<<_T("开入D");
	UpdateComboBox(oList,m_pBinComboBoxList,false);
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_BoutComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}

	QScrollComboBox* pComboBox = qobject_cast<QScrollComboBox*>(sender()); 
	CString strID = pComboBox->objectName();

	if (pComboBox)
	{
		int nIndex = -1;
		if (strID == _T("CloseSignal")) nIndex = 0;
		else if (strID == _T("OpenSignal")) nIndex = 1; 
		else if (strID == _T("EnergySignal")) nIndex = 2;

		if (nIndex != -1  && nIndex < m_pBoutLabelList.size())
		{
			CString strText = pComboBox->currentText();
			QLabel* pLabel = m_pBoutLabelList.at(nIndex).first;
			pLabel->clear(); 
			if (strText != _T("空"))
			{
				pLabel->setPixmap(SetIconPic(0).pixmap(20, 20));
			}
			else
			{
				pLabel->setPixmap(SetIconPic(2).pixmap(20, 20));
			}
		}
	}
	

	QStringList oList;
	CString strText;
	for (int i=0; i<g_nBinCount; i++)
	{
		strText.Format(_T("开出%d"),i+1);
		oList.append(strText);
	}
	UpdateComboBox(oList,m_pBoutComboBoxList,true);	
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_CloseDelay_editingFinished()
{
	float fv = m_pCloseDelayEdit->text().toFloat();
	fv = setLimit(0,100000,fv);
	m_pCloseDelayEdit->setText(QString::number(fv,'f', 0));
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_OpenDelay_editingFinished()
{
	float fv = m_pOpenDelayEdit->text().toFloat();
	fv = setLimit(0,100000,fv);
	m_pOpenDelayEdit->setText(QString::number(fv,'f', 0));
}



void QSttMacroParaEditViewAnalogCirBreaker::slot_updateParas( int channelNum,int valueFlag,float datavalue )//valueFlag=（1:幅值 2:相位 3:频率）
{
	CExBaseList* pCurChList = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetAtIndex(channelNum);
	CString strID;

	if (valueFlag == 1)
	{
		strID = pCurChList->m_strID;
		m_uiCUR[channelNum].Harm[1].fAmp = datavalue;

	}
	else if (valueFlag == 2)
	{
		strID = pCurChList->m_strID + _T("Ph");
		m_uiCUR[channelNum].Harm[1].fAngle = datavalue;
	}
	else
	{
		strID = pCurChList->m_strID + _T("Fre");
		m_uiCUR[channelNum].Harm[1].fFreq = datavalue;
	}

	m_pAnalogCirBreakerData.SetDataValue(strID,datavalue);
}

void QSttMacroParaEditViewAnalogCirBreaker::slot_updateParas()
{
	g_theTestCntrFrame->UpdateVectorData();
	g_theTestCntrFrame->UpdatePowerData();
}
