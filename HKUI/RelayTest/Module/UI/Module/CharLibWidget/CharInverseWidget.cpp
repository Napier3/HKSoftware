#include "CharInverseWidget.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../Module/TestWinFrame/ZKCharaCurve/QCIFeatureAddDig.h"
#include "../../../XLangResource_Native.h"

CharInverseWidget::CharInverseWidget(QWidget *parent)
	: QWidget(parent)
{	
	ui.setupUi(this);
	
	m_pActionTimeParas = NULL;
	m_pActionTimeTest = NULL;

	m_bCheckBox1 = false;
	m_bCheckBox2 = false;
	m_bCheckBox3 = false;

	InsertActionTime();

	InitCharactWidget();
	initConnect();

	UpdateCharDraw();
}

CharInverseWidget::~CharInverseWidget()
{
	
}

void CharInverseWidget::InsertActionTime()
{
	QFont ft("Microsoft YaHei", 10);

	//tab1
	tab_1 = new QWidget();
	m_hLayout = new QHBoxLayout();
	m_vLayout = new QVBoxLayout();
	m_hLayout_1 = new QHBoxLayout();
	m_vLayout_1 = new QVBoxLayout();

	int nHeight = 25;

	label = new QLabel;
	label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	label->setFont(ft);
	label->setText(QObject::tr("名称"));

	lne_Name = new QLineEdit;
	lne_Name->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	lne_Name->setFixedHeight(nHeight);
	lne_Name->setFont(ft);

	m_hLayout_1->addWidget(label);
	m_hLayout_1->addWidget(lne_Name);
	m_hLayout_1->addStretch();

	pbn_Add	= new QPushButton;
	pbn_Add->setFont(ft);
        pbn_Add->setText(/* QObject::tr("添加试验") */ g_sLangTxt_Gradient_AddExperiment);
        pbn_Add->setIcon(QPixmap("./images/Add.png"));

	pbn_AddSerial = new QPushButton;
	pbn_AddSerial->setFont(ft);
        pbn_AddSerial->setText(/* QObject::tr("添加系列") */ g_sLangTxt_Add_Series);
        pbn_AddSerial->setIcon(QPixmap("./images/Button-New-01.png"));

	pbn_Del	= new QPushButton;
	pbn_Del->setFont(ft);
        pbn_Del->setText(/* QObject::tr("删除试验") */ g_sLangTxt_Delet_Test);
        pbn_Del->setIcon(QPixmap("./images/Delete.png"));

	pbn_DelSerial = new QPushButton;
	pbn_DelSerial->setFont(ft);
        pbn_DelSerial->setText(/* QObject::tr("删除N-1") */ g_sLangTxt_IEC_DeleteAllButFirst);
        pbn_DelSerial->setIcon(QPixmap("./images/clearAll.png"));

	pbn_Clear = new QPushButton;
	pbn_Clear->setFont(ft);
        pbn_Clear->setText(/* QObject::tr("清除结果") */ g_sLangTxt_Clear_Results);
        pbn_Clear->setIcon(QPixmap("./images/standardbutton-delete-32.png"));

	pbn_ClearAll = new QPushButton;
	pbn_ClearAll->setFont(ft);
        pbn_ClearAll->setText(/* QObject::tr("清除所有") */ g_sLangTxt_Clear_All);
        pbn_ClearAll->setIcon(QPixmap("./images/standardbutton-clear-32.png"));

	m_vLayout_1->addWidget(pbn_Add);
	m_vLayout_1->addWidget(pbn_AddSerial);
	m_vLayout_1->addWidget(pbn_Del);
	m_vLayout_1->addWidget(pbn_DelSerial);
	m_vLayout_1->addWidget(pbn_Clear);
	m_vLayout_1->addWidget(pbn_ClearAll);

	m_pActionTimeWidget = new ActionTimeDataWidget(this,false);
	
	m_vLayout->addLayout(m_hLayout_1);
	m_vLayout->addWidget(m_pActionTimeWidget);

	m_hLayout->addLayout(m_vLayout);
	m_hLayout->addLayout(m_vLayout_1);

	tab_1->setLayout(m_hLayout);

    ui.tabWidget->insertTab(0, tab_1, /* tr("试验参数") */ g_sLangTxt_Test_Parameters);
	ui.tabWidget->setCurrentIndex(1);
	ui.tabWidget->setCurrentIndex(0);
}

void CharInverseWidget::setData(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(pCurr != NULL);

	m_pActionTimeTest = (tmt_CurrInverseTimeTest*)pCurr;
	m_pActionTimeParas = &m_pActionTimeTest->m_oActionTimeParas;

	m_pActionTimeWidget->setData(pCurr);

	initData();
}


void CharInverseWidget::initConnect()
{
	connect(ui.checkBox_Set1, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set1_toggled(bool)));
	connect(ui.lineEdit_VSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet1_editFinished()));
	connect(ui.lineEdit_TSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet1_editFinished()));
	connect(ui.checkBox_Set2, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set2_toggled(bool)));
	connect(ui.lineEdit_VSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet2_editFinished()));
	connect(ui.lineEdit_TSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet2_editFinished()));
	connect(ui.checkBox_Set3, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set3_toggled(bool)));
	connect(ui.lineEdit_VSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet3_editFinished()));
	connect(ui.lineEdit_TSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet3_editFinished()));

	connect(pbn_Add,	  SIGNAL(clicked ()), this, SLOT(slot_PbnAddClicked()));
	connect(pbn_AddSerial,SIGNAL(clicked ()), this, SLOT(slot_PbnAddSerialClicked()));
	connect(pbn_Del,	  SIGNAL(clicked ()), this, SLOT(slot_PbnDelClicked()));
	connect(pbn_DelSerial,SIGNAL(clicked ()), this, SLOT(slot_PbnDelAllClicked()));
	connect(pbn_Clear,	  SIGNAL(clicked ()), this, SLOT(slot_PbnClearResultClicked()));
	connect(pbn_ClearAll, SIGNAL(clicked ()), this, SLOT(slot_PbnClearAllClicked()));
	connect(ui.pushButton,SIGNAL(clicked ()), this, SLOT(slot_AddCIFeature()));

	//更新表格数据
	connect(m_pActionTimeWidget,SIGNAL(sig_FaultTypeChange()),this,SLOT(slot_FaultTypeChanged()));
	connect(m_pActionTimeWidget,SIGNAL(sig_FaultCurChange()),this,SLOT(slot_FaultCurChangedFinished()));

	connect(ui.tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));

	//////////////////////////////////////////////////////////////////////////
	connect(this,SIGNAL(updateData()),this,SLOT(slot_UpdateData()));
	connect(this,SIGNAL(sig_UpdataCheck(bool, bool, bool)),this,SLOT(slot_UpdateCheck(bool, bool, bool)));

	connect(this, SIGNAL(sig_CICharChanged()), m_pImpCharactWidget,SLOT(slot_UpdateDrawCharacters()));
	connect(m_pImpCharactWidget, SIGNAL(sig_UpdatePointLocation(float ,float)), this, SLOT(slot_ParaPointChange(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_AddPointLocation(float ,float)), this, SLOT(slot_ParaAddPoint(float ,float)));
}


void CharInverseWidget::initData()
{
	lne_Name->setDisabled(true);
	lne_Name->setFixedSize(200,25);

	CString strName;
	strName = stt_get_test_item_name(m_pActionTimeTest);	//获取故障名称

	lne_Name->setText(strName);
	ui.checkBox_Set1->setChecked(m_bCheckBox1);
	ui.checkBox_Set2->setChecked(m_bCheckBox2);
	ui.checkBox_Set3->setChecked(m_bCheckBox3);

	if(g_theSttXTestMngrBaseApp->m_pCharElementBase == NULL)
	{
		CCharacteristic* p = (CCharacteristic*)g_theSttXTestMngrBaseApp->m_pCharacteristics->GetAtIndex(0);

		if (p != NULL)
		{
			g_theSttXTestMngrBaseApp->m_pCharElementBase = (CCharElementInverse*)p->GetCharacterArea()->GetHead();
		}
		else
			return;
	}

	CCharElementInverse *pElement = g_theSttXTestMngrBaseApp->m_pCharElementBase;

	ui.lineEdit_VSet1->setText(QString::number(pElement->m_fValSection[0], 'f', 3));
	ui.lineEdit_VSet2->setText(QString::number(pElement->m_fValSection[1], 'f', 3));
	ui.lineEdit_VSet3->setText(QString::number(pElement->m_fValSection[2], 'f', 3));
	ui.lineEdit_TSet1->setText(QString::number(pElement->m_fTmSection[0], 'f', 3));
	ui.lineEdit_TSet2->setText(QString::number(pElement->m_fTmSection[1], 'f', 3));
	ui.lineEdit_TSet3->setText(QString::number(pElement->m_fTmSection[2], 'f', 3));

	InitGroup();
}
void CharInverseWidget::InitGroup()
{
	for (int i = 0 ; i < m_labelList.size(); i++)
	{
		delete m_labelList[i];
		m_labelList[i] = NULL;
	}
	for (int i = 0 ; i < m_editList.size(); i++)
	{
		delete m_editList[i];
		m_editList[i] = NULL;
	}

	m_labelList.clear();
	m_editList.clear();

	CCharElementInverse *pElement = g_theSttXTestMngrBaseApp->m_pCharElementBase;
	if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		AddLabelToGroup(QObject::tr("Td"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("A"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("B"),2,0);
		AddEditToGroup(2,1);

		AddLabelToGroup(QObject::tr("P"),3,0);
		AddEditToGroup(3,1);

		AddLabelToGroup(QObject::tr("Q"),0,2);
		AddEditToGroup(0,3);

		AddLabelToGroup(QObject::tr("K1"),1,2);
		AddEditToGroup(1,3);

		AddLabelToGroup(QObject::tr("K2"),2,2);
		AddEditToGroup(2,3);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		AddLabelToGroup(QObject::tr("Td"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("A"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("B"),2,0);
		AddEditToGroup(2,1);

		AddLabelToGroup(QObject::tr("C"),3,0);
		AddEditToGroup(3,1);

		AddLabelToGroup(QObject::tr("D"),0,2);
		AddEditToGroup(0,3);

		AddLabelToGroup(QObject::tr("E"),1,2);
		AddEditToGroup(1,3);

		AddLabelToGroup(QObject::tr("Beta"),2,2);
		AddEditToGroup(2,3);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		AddLabelToGroup(QObject::tr("Tp"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("A"),1,0);
		AddEditToGroup(1,1);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		AddLabelToGroup(QObject::tr("Tp"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("K"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("Alpha"),2,0);
		AddEditToGroup(2,1);
	}
	UpdateGroup();
}

void CharInverseWidget::UpdateGroup()
{
	CCharElementInverse *pElement = g_theSttXTestMngrBaseApp->m_pCharElementBase;
	if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		SetFormulaPic(0);
		CCharElementIEEE *pIEEE = (CCharElementIEEE *)pElement;
		ui.lineEdit_Name->setText(QObject::tr("IEEE"));
		m_editList[0]->setText(pIEEE->m_strTp);
		m_editList[1]->setText(pIEEE->m_strA);
		m_editList[2]->setText(pIEEE->m_strB);
		m_editList[3]->setText(pIEEE->m_strP);
		m_editList[4]->setText(pIEEE->m_strQ);
		m_editList[5]->setText(pIEEE->m_strK1);
		m_editList[6]->setText(pIEEE->m_strK2);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		SetFormulaPic(1);
		CCharElementIAC *pIAC = (CCharElementIAC *)pElement;
		ui.lineEdit_Name->setText(QObject::tr("IAC"));
		m_editList[0]->setText(pIAC->m_strTp);
		m_editList[1]->setText(pIAC->m_strA);
		m_editList[2]->setText(pIAC->m_strB);
		m_editList[3]->setText(pIAC->m_strC);
		m_editList[4]->setText(pIAC->m_strD);
		m_editList[5]->setText(pIAC->m_strE);
		m_editList[6]->setText(pIAC->m_strBeta);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		SetFormulaPic(2);
		CCharElementI2T *pI2T = (CCharElementI2T *)pElement;
		ui.lineEdit_Name->setText(QObject::tr("I2T"));
		m_editList[0]->setText(pI2T->m_strTp);
		m_editList[1]->setText(pI2T->m_strA);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		SetFormulaPic(3);
		CCharElementIEC *pIEC = (CCharElementIEC *)pElement;
		ui.lineEdit_Name->setText(QObject::tr("IEC"));
		m_editList[0]->setText(pIEC->m_strTp);
		m_editList[1]->setText(pIEC->m_strK);
		m_editList[2]->setText(pIEC->m_strAlpha);
	}
}

void CharInverseWidget::InitCharactWidget()
{
	m_pImpCharactWidget = new QImpCharactWidget(this,true,true);
	m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
	ui.m_wgtCharLib->insertTab(-1, m_pImpCharactWidget, /* tr("时间特性图") */ g_sLangTxt_Native_TimeChart);
	ui.m_wgtCharLib->findChildren<QTabBar*>().at(0)->hide();
	m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
	m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
	m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	m_pImpCharactWidget->IsHaveAddAct();
}

//////////////////////////////////////////
void CharInverseWidget::setPara(QLineEdit *A, CString &strTemp)
{
	if (A->text().isEmpty())
	{
		A->setText("0.000");
	}

	QString str = A->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);
	strTemp = QString::number(fv,'f',3);

	A->setText(strTemp); 
}

void CharInverseWidget::setPara( QLineEdit *A, float &fTemp )
{
	if (A->text().isEmpty())
	{
		A->setText("0.000");
	}

	QString str = A->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);
	fTemp = fv;

	A->setText(QString::number(fv,'f',3));
}

void CharInverseWidget::slot_oncheckBox_Set1_toggled(bool b)
{
	if(b)
	{
		ui.checkBox_Set1->setChecked(true);
		m_bCheckBox1 = true;
	}
	else
	{
		ui.checkBox_Set1->setChecked(false);
		ui.checkBox_Set2->setChecked(false);
		ui.checkBox_Set3->setChecked(false);
		m_bCheckBox1 = false;
		m_bCheckBox2 = false;
		m_bCheckBox3 = false;
		 
	}
	ModifyCharByChenk();
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_oncheckBox_Set2_toggled(bool b)
{
	if(b)
	{
		ui.checkBox_Set1->setChecked(true);
		ui.checkBox_Set2->setChecked(true);
		m_bCheckBox1 = true;
		m_bCheckBox2 = true;
	}
	else
	{
		ui.checkBox_Set2->setChecked(false);
		ui.checkBox_Set3->setChecked(false);
		m_bCheckBox2 = false;
		m_bCheckBox3 = false;
	}
	ModifyCharByChenk();

	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_oncheckBox_Set3_toggled(bool b)
{
	 if(b)
	 {
		 ui.checkBox_Set1->setChecked(true);
		 ui.checkBox_Set2->setChecked(true);
		 ui.checkBox_Set3->setChecked(true);
		 m_bCheckBox1 = true;
		 m_bCheckBox2 = true;
		 m_bCheckBox3 = true;
	 }
	 else
	 {
		 ui.checkBox_Set3->setChecked(false);
		 m_bCheckBox3 = false;
	 }
	 ModifyCharByChenk();

	 emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::ModifyCharByChenk()
{
	if (m_bCheckBox1)
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[0] = 1;
	}
	else
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[0] = 0;
	}

	if (m_bCheckBox2)
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[1] = 1;
	}
	else
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[1] = 0;
	}

	if (m_bCheckBox3)
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[2] = 1;
	}
	else
	{
		g_theSttXTestMngrBaseApp->m_pCharElementBase->m_nUseSection[2] = 0;
	}
}

void CharInverseWidget::UpdateCharDraw()
{
	g_theSttXTestMngrBaseApp->DeleteAllDrawPoints();	//清除所有的点

	if (g_theSttXTestMngrBaseApp->m_pCharElementBase == NULL)
	{
		CCharacteristic* p = (CCharacteristic*)g_theSttXTestMngrBaseApp->m_pCharacteristics->GetAtIndex(0);

		if (p != NULL)
		{
			g_theSttXTestMngrBaseApp->m_pCharElementBase = (CCharElementInverse*)p->GetCharacterArea()->GetHead();
		}
		else
		{//保证在没有缺省文件的情况下不奔溃,正确性待验证 20211014 sf
			g_theSttXTestMngrBaseApp->m_pCharElementBase = new CCharElementIEEE;	
			CCharacterArea *pArea = new CCharacterArea;
			pArea->AddHead(g_theSttXTestMngrBaseApp->m_pCharElementBase);
			CCharacteristic *pChar = new CCharacteristic;
			pChar->AddHead(pArea);
			g_theSttXTestMngrBaseApp->m_pCharacteristics = new CCharacteristics;
			g_theSttXTestMngrBaseApp->m_pCharacteristics->AddHead(pChar);
		}
	}

// 	for (int i = 0; i < m_oTmtTestMngr.m_nCount ; i++)
// 	{
// 		PTMT_PARAS_HEAD pPara = m_oTmtTestMngr.m_pParasBuffer[i];
// 
// 		CalCharYAxis(pPara);
// 
// 		CreateCharDraw(pPara);
// 	}
}
void CharInverseWidget::CalCharXYAxis(PTMT_PARAS_HEAD pPara)
{
	tmt_CurrInverseTimeTest *pTest = (tmt_CurrInverseTimeTest*)pPara;

	pTest->m_fCurrCal = pTest->m_oActionTimeParas.m_fFaultCur;

	if (pPara->m_nTestState == 0)
	{
		pTest->m_fTsetCal = g_theSttXTestMngrBaseApp->m_pCharElementBase->CalInverse(pTest->m_fCurrCal);

		pTest->m_oActionTimeParas.m_fSettingFaultTime = pTest->m_fTsetCal;
	}
}

void CharInverseWidget::CalCharYAxis(PTMT_PARAS_HEAD pPara)
{
	tmt_CurrInverseTimeTest *pTest = (tmt_CurrInverseTimeTest*)pPara;

	pTest->m_fCurrCal = pTest->m_oActionTimeParas.m_fFaultCur;

	if (m_pCharElementBase == NULL)
	{
		return;
	}
	CalCharXYAxis(pTest);

// 	if (m_pCharElementBase->m_nUseSection[2] == 1)
// 	{
// 		if (pTest->m_fCurrCal > m_pCharElementBase->m_fValSection[2])
// 		{
// 			pTest->m_fTsetCal = m_pCharElementBase->m_fTmSection[2];
// 		}
// 	}
// 	else
// 	{
// 		CalCharXYAxis(pTest);
// 	}
// 
// 	if (m_pCharElementBase->m_nUseSection[1] == 1)
// 	{
// 		if (pTest->m_fCurrCal > m_pCharElementBase->m_fValSection[1])
// 		{
// 			pTest->m_fTsetCal = m_pCharElementBase->m_fTmSection[1];
// 		}
// 	}
// 	else
// 	{
// 		CalCharXYAxis(pTest);
// 	}
// 
// 	if (m_pCharElementBase->m_nUseSection[0] == 1)
// 	{
// 		if (pTest->m_fCurrCal > m_pCharElementBase->m_fValSection[0])
// 		{
// 			pTest->m_fTsetCal = m_pCharElementBase->m_fTmSection[0];
// 		}
// 	}
// 	else
// 	{
// 		CalCharXYAxis(pTest);
// 	}
}

void CharInverseWidget::resizeEvent( QResizeEvent * pReSizeEvent)
{
	this->QWidget::resizeEvent(pReSizeEvent);

	QSize size = ui.labelbg->size();
	if (bgImage.isNull())
	{
	}
	else
	{
		ui.labelbg->setAlignment(Qt::AlignCenter);
		ui.labelbg->setPixmap(bgImage.scaled(size,Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

void CharInverseWidget::slot_onlineEdit_VSet1_editFinished()
{
	float fv = ui.lineEdit_VSet1->text().toFloat();
	fv = setLimit(0,999.999,fv);
	if (fv < ui.lineEdit_VSet2->text().toFloat())
	{
		ui.lineEdit_VSet1->setText(ui.lineEdit_VSet2->text());
	}

	setPara(ui.lineEdit_VSet1, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strValSection[0]);

	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_onlineEdit_VSet2_editFinished()
{
	float fv = ui.lineEdit_VSet2->text().toFloat();
	fv = setLimit(0,999.999,fv);
	if (fv < ui.lineEdit_VSet3->text().toFloat())
	{
		ui.lineEdit_VSet2->setText(ui.lineEdit_VSet3->text());
	}
	setPara(ui.lineEdit_VSet2, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strValSection[1]);
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_onlineEdit_VSet3_editFinished()
{
	setPara(ui.lineEdit_VSet3, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strValSection[2]);
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_onlineEdit_TSet1_editFinished()
{
	setPara(ui.lineEdit_TSet1, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strTmSection[0]);
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_onlineEdit_TSet2_editFinished()
{
	setPara(ui.lineEdit_TSet2, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strTmSection[1]);
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}


void CharInverseWidget::slot_onlineEdit_TSet3_editFinished()
{
	setPara(ui.lineEdit_TSet3, g_theSttXTestMngrBaseApp->m_pCharElementBase->m_strTmSection[2]);
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::slot_ElementData_editFinished()
{
	CCharElementInverse *pElement = g_theSttXTestMngrBaseApp->m_pCharElementBase;

	if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		CCharElementIEEE *pIEEE = (CCharElementIEEE *)pElement;
		setPara(m_editList[0],pIEEE->m_strTp);
		setPara(m_editList[1],pIEEE->m_strA);
		setPara(m_editList[2],pIEEE->m_strB);
		setPara(m_editList[3],pIEEE->m_strP);
		setPara(m_editList[4],pIEEE->m_strQ);
		setPara(m_editList[5],pIEEE->m_strK1);
		setPara(m_editList[6],pIEEE->m_strK2);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		CCharElementIAC *pIAC = (CCharElementIAC *)pElement;
		setPara(m_editList[0],pIAC->m_strTp);
		setPara(m_editList[1],pIAC->m_strA);
		setPara(m_editList[2],pIAC->m_strB);
		setPara(m_editList[3],pIAC->m_strC);
		setPara(m_editList[4],pIAC->m_strD);
		setPara(m_editList[5],pIAC->m_strE);
		setPara(m_editList[6],pIAC->m_strBeta);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		CCharElementI2T *pI2T = (CCharElementI2T *)pElement;
		setPara(m_editList[0],pI2T->m_strTp);
		setPara(m_editList[1],pI2T->m_strA);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		CCharElementIEC *pIEC = (CCharElementIEC *)pElement;
		setPara(m_editList[0],pIEC->m_strTp);
		setPara(m_editList[1],pIEC->m_strK);
		setPara(m_editList[2],pIEC->m_strAlpha);
	}

	emit sig_CICharChanged();
	emit updateData();
	emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);
}

void CharInverseWidget::initMaxPositiveEdit( QLineEdit *lne )
{
	 QRegExp rx("^[|0-9|(.)|^]{1,16}|(^\\t?$)"); 
	 QRegExpValidator *pReg = new QRegExpValidator(rx, lne);  
	 lne->setValidator(pReg); 
}

void CharInverseWidget::slot_PbnAddClicked()
{
	AddTestDig dig(m_pActionTimeParas,this);
	connect(&dig,SIGNAL(sig_AddTestItemOkClicked(tmt_ActionTimeParasEx &,QList<int>)),this,SLOT(slot_AddOk(tmt_ActionTimeParasEx &,QList<int> )));
	dig.exec();
}

void CharInverseWidget::slot_AddOk(tmt_ActionTimeParasEx &oPara,QList<int> list)
{
	emit sig_AddClicked(oPara,list);
}

void CharInverseWidget::slot_PbnAddSerialClicked()
{
	AddMutiTestItemDig dig(m_pActionTimeParas,this);
	connect(&dig,SIGNAL(sig_AddMutiTestItemOkClicked(tmt_ActionTimeParasEx &,QList<int>,float,float,float)),this,SLOT(slot_AddMutiOk(tmt_ActionTimeParasEx &,QList<int>,float,float,float)));
	dig.exec();
}

void CharInverseWidget::slot_AddMutiOk(tmt_ActionTimeParasEx &oPara,QList<int> list,float fstart,float fend,float fsept)
{
	emit sig_AddMutiClicked(oPara,list,fstart,fend,fsept);
}

void CharInverseWidget::slot_PbnDelClicked()
{
	emit sig_PbnDelClicked();	
}

void CharInverseWidget::slot_PbnDelAllClicked()
{
	emit sig_PbnDelAllClicked();
}

void CharInverseWidget::slot_PbnClearResultClicked()
{
	emit sig_PbnClearResultClicked();
}

void CharInverseWidget::slot_PbnClearAllClicked()
{
	emit sig_PbnClearAllClicked();
}

void CharInverseWidget::slot_FaultTypeChanged()
{
	CString strName;
	strName = stt_get_test_item_name(m_pActionTimeTest);	//获取故障名称
	lne_Name->setText(strName);
}

void CharInverseWidget::slot_FaultCurChangedFinished()
{
	CString strName;
	strName = stt_get_test_item_name(m_pActionTimeTest);	//获取故障名称
	lne_Name->setText(strName);
}

void CharInverseWidget::slot_ParaAddPoint( float fx,float fy )
{
// 	int nRow = m_TestTable->rowCount();

// 	tmt_CurrInverseTimeTest* pNewTest = (tmt_CurrInverseTimeTest*)CreateTestParasEx(m_oTmtTestMngr.m_pParasBuffer[nRow]->m_pszMacroID);

// 	pNewTest->m_oActionTimeParas.m_fFaultCur = fx;

// 	CalCharYAxis(pNewTest);

// 	Test_InsertAt(pNewTest, nRow);
// 	CreateCharDraw(pNewTest);

// 	m_TestTable->InitData();
// 	m_TestTable->SetCurrentRow(nRow);
}

void CharInverseWidget::slot_ParaPointChange( float fx,float fy )
{
// 	int nRow = m_TestTable->currentRow();
// 	tmt_CurrInverseTimeTest *pTest = (tmt_CurrInverseTimeTest *)(m_oTmtTestMngr.m_pParasBuffer[nRow]);

// 	if (pTest->m_nTestState)
// 	{
// 		pTest->m_oActionTimeParas.m_fFaultCur = fx;
// 		pTest->m_fCurrCal = fx;
// 
// 		CalCharYAxis(pTest);

// 		m_TestTable->UpdateItem(nRow);
// 		m_ParaSetWidget->m_pActionTimeWidget->UpdateActTime();
// 	}	
}

void CharInverseWidget::slot_UpdateData()
{
	//m_ParaSetWidget->m_pActionTimeWidget->InitData();
// 	int nRow = m_TestTable->GetCurrentRow();
// 	tmt_CurrInverseTimeTest *pTest = (tmt_CurrInverseTimeTest *)m_oTmtTestMngr.m_pParasBuffer[nRow];
// 
// 	CalAllValue();
// 	UpdateCharDraw();
// 
// 	m_pImpCharactWidget->slot_UpdateDrawCharacters();
// 
// 	m_ParaSetWidget->m_pActionTimeWidget->UpdateActTime();
}

void CharInverseWidget::slot_UpdateCheck( bool bOne, bool bTwo, bool bThr )
{
// 	g_theSttXTestMngrBaseApp->DeleteAllDrawPoints();
// 
// 	for (int i = 0;i < m_oTmtTestMngr.m_nCount; i++)
// 	{
// 		PTMT_PARAS_HEAD pPara = m_oTmtTestMngr.m_pParasBuffer[i];
// 
// 		CalCharYAxis(pPara);
// 
// 		CreateCharDraw(pPara);
// 	}
// 
// 	m_pImpCharactWidget->slot_UpdateDrawCharacters();
}

void CharInverseWidget::stopInit()
{
	m_pActionTimeWidget->stopInit();

	ui.checkBox_Set1->setDisabled(false);
	ui.lineEdit_VSet1->setDisabled(false);
	ui.lineEdit_TSet1->setDisabled(false);
	ui.checkBox_Set2->setDisabled(false);
	ui.lineEdit_VSet2->setDisabled(false);
	ui.lineEdit_TSet2->setDisabled(false);
	ui.checkBox_Set3->setDisabled(false);
	ui.lineEdit_VSet3->setDisabled(false);
	ui.lineEdit_TSet3->setDisabled(false);

	ui.pushButton->setDisabled(false);


	pbn_Add->setDisabled(false);
	pbn_AddSerial->setDisabled(false);
	pbn_Del->setDisabled(false);
	pbn_DelSerial->setDisabled(false);
	pbn_Clear->setDisabled(false);
	pbn_ClearAll->setDisabled(false);

	for (int i = 0;i < m_editList.size();i++)
	{
		m_editList.at(i)->setDisabled(false);
	}
}

void CharInverseWidget::startInit()
{
	m_pActionTimeWidget->startInit();

	ui.checkBox_Set1->setDisabled(true);
	ui.lineEdit_VSet1->setDisabled(true);
	ui.lineEdit_TSet1->setDisabled(true);
	ui.checkBox_Set2->setDisabled(true);
	ui.lineEdit_VSet2->setDisabled(true);
	ui.lineEdit_TSet2->setDisabled(true);
	ui.checkBox_Set3->setDisabled(true);
	ui.lineEdit_VSet3->setDisabled(true);
	ui.lineEdit_TSet3->setDisabled(true);

	ui.pushButton->setDisabled(true);

	pbn_Add->setDisabled(true);
	pbn_AddSerial->setDisabled(true);
	pbn_Del->setDisabled(true);
	pbn_DelSerial->setDisabled(true);
	pbn_Clear->setDisabled(true);
	pbn_ClearAll->setDisabled(true);

	for (int i = 0;i < m_editList.size();i++)
	{
		m_editList.at(i)->setDisabled(true);
	}
}

void CharInverseWidget::slot_AddCIFeature()
{
	QCIFeatureAddDig dig;
	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_CIAddChar(CCharacteristic*)));
	dig.exec();
}

void CharInverseWidget::slot_CIAddChar( CCharacteristic *pObj )
{
	if (pObj == NULL)
	{
		return;
	}
	g_theSttXTestMngrBaseApp->SetModifyPara();

	CCharacteristic* p = (CCharacteristic*)g_theSttXTestMngrBaseApp->m_pCharacteristics->GetAtIndex(0);
	
	if (p != NULL)
	{
		g_theSttXTestMngrBaseApp->m_pCharacteristics->DeleteByID(p->m_strID);
	}

	if (g_theSttXTestMngrBaseApp->m_pCharacteristics->AddCharTempClone(pObj))
	{
		CCharacteristic* p = (CCharacteristic*)g_theSttXTestMngrBaseApp->m_pCharacteristics->GetAtIndex(0);

		g_theSttXTestMngrBaseApp->m_pCharElementBase = (CCharElementInverse *)p->GetCharacterArea()->GetHead();

		InitGroup();
		
		ModifyCharByChenk();
		emit sig_CICharChanged();
		emit updateData();
		emit sig_UpdataCheck(m_bCheckBox1,m_bCheckBox2,m_bCheckBox3);


	}
}

void CharInverseWidget::AddLabelToGroup( QString str,int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLabel *tempLabel = new QLabel;
	tempLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempLabel->setText(str);
	tempLabel->setFont(ft);
	tempLabel->setFixedHeight(nHeight);
	//tempLabel->setFixedWidth(100);
	ui.GroupGrid->addWidget(tempLabel,nRow,nCol);
	m_labelList.append(tempLabel);
}

void CharInverseWidget::AddEditToGroup( int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLineEdit *tempEdit = new QLineEdit;
	tempEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempEdit->setFont(ft);
	tempEdit->setFixedHeight(nHeight);
	initMaxPositiveEdit(tempEdit);
	connect(tempEdit, SIGNAL(editingFinished()),this,SLOT(slot_ElementData_editFinished()));
	ui.GroupGrid->addWidget(tempEdit,nRow,nCol);
	m_editList.append(tempEdit);
}

void CharInverseWidget::slot_TabPageChanged( int nIndex)
{
	if (nIndex == 2 || nIndex == 1)
	{
		QSize size = ui.labelbg->size();
		ui.labelbg->setPixmap(bgImage.scaled(size,Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

void CharInverseWidget::SetFormulaPic( int nType )
{
	
	switch(nType)
	{
	case 0:
		{
			if (m_pActionTimeParas->m_nRefValueType == 0)
			{
				//ui.widget_Express->setStyleSheet("background-color: gainsboro;border-image:url(./images/IEEE.bmp);background-repeat:1;background-position:center;");
				bgImage.load("./images/IEEE_1.bmp");
			}
			else
			{
				//ui.widget_Express->setStyleSheet("background-color: gainsboro;border-image:url(./images/IEEE_2.bmp);background-repeat:1;background-position:center;");
				bgImage.load("./images/IEEE_2.bmp");
			}
		}break;
	case 1:
		{
			if (m_pActionTimeParas->m_nRefValueType == 0)
			{
				bgImage.load("./images/IAC_1.bmp");
			}
			else
			{
				bgImage.load("./images/IAC_2.bmp");
			}
		}break;
	case 2:
		{
			if (m_pActionTimeParas->m_nRefValueType == 0)
			{
				bgImage.load("./images/I2T_1.bmp");
			}
			else
			{
				bgImage.load("./images/I2T_2.bmp");
			}
		}break;
	case 3:
		{
			if (m_pActionTimeParas->m_nRefValueType == 0)
			{
				bgImage.load("./images/IEC_1.bmp");
			}
			else
			{
				bgImage.load("./images/IEC_2.bmp");
			}
		}break;
	}
	QSize size = ui.labelbg->size();
	ui.labelbg->setPixmap(bgImage.scaled(size,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}
