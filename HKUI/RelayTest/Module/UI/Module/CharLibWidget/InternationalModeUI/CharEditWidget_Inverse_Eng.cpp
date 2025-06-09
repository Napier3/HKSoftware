#include "CharEditWidget_Inverse_Eng.h"
#include "ui_CharEditWidget_Inverse_Eng.h"

#include "CharEditMainDialog.h"
#include "../../../SttTestCntrFrameAPI.h"
#include "../../ZKCharaCurve/QCIFeatureAddDig.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../CommonMethod/commonMethod.h"

QCharEditWidget_Inverse_Eng::QCharEditWidget_Inverse_Eng(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCharEditWidget_Inverse_Eng)
{
	m_pCharEditWidget = this;
    ui->setupUi(this);
	m_pLowVolModeRadio = NULL;
	m_pOverVolModeRadio = NULL;

	m_pCharElementInverse = NULL;

	if (stt_FrameTestCntrFrameHeight()>700)
	{
		ui->GroupGrid->setSpacing(10);//设置行间距
	}
	m_pCharacteristics_Inner = NULL;
	InitChar();//20240812 gongyiping 获取克隆的唯一变量
	InitData();
	InitConnect();
	InitLanguage();
	
	SetInverseFont();
	emit sig_CharChanged(NULL,FALSE);
}

QCharEditWidget_Inverse_Eng::~QCharEditWidget_Inverse_Eng()
{
	//if (m_pCharacteristics_Inner != NULL)
	//{
	//	m_pCharacteristics_Inner->DeleteAll();
	//	delete m_pCharacteristics_Inner;
	//	m_pCharacteristics_Inner = NULL;
	//}

    delete ui;
}

void QCharEditWidget_Inverse_Eng::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->txtName, g_sLangTxt_Native_CurveName, XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->btnSelect, g_sLangTxt_Select, XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->label_26, g_sLangTxt_Native_actionSetting, XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_27, g_sLangTxt_Gradient_ActionTime, XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->checkBox_Set1, g_sLangTxt_Native_SingleTimeLimit, XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui->checkBox_Set2, g_sLangTxt_Native_DoubleTimeLimit, XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui->checkBox_Set3, g_sLangTxt_Native_TripleTimeLimit, XLang_Ctrls_QCheckBox);
	//xlang_SetLangStrToWidget_Txt(ui->label_CurrValue, g_sLangTxt_Native_CurrentValueI, XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget_Txt(ui->Btn_AddUserPoint, g_sLangTxt_Gradient_AddCusp, XLang_Ctrls_QPushButton);
	//xlang_SetLangStrToWidget_Txt(ui->Btn_ClearUserPoints, g_sLangTxt_Gradient_Emptycusp, XLang_Ctrls_QPushButton);
}

void QCharEditWidget_Inverse_Eng::InitData()
{

	CCharacteristic *p = m_pCharacteristics_Inner->GetAtIndex_Char(0);

	if (p == NULL)
	{
		return;
	}

	m_pCharElementInverse = (CCharElementInverse*)p->GetCharacterArea()->GetHead();

	if (m_pCharElementInverse == NULL)
	{
		return;
	}

	if (!IsCurrInverse())//电压反时限模式,不显示选择按钮,不显示定时限选择
	{
		ui->groupBox_1->setVisible(false);
		ui->btnSelect->setVisible(false);
	}

	m_bCheckBox1 = m_pCharElementInverse->m_nUseSection[0];
	m_bCheckBox2 = m_pCharElementInverse->m_nUseSection[1];
	m_bCheckBox3 = m_pCharElementInverse->m_nUseSection[2];

	ui->checkBox_Set1->setChecked(m_bCheckBox1);
	ui->checkBox_Set2->setChecked(m_bCheckBox2);
	ui->checkBox_Set3->setChecked(m_bCheckBox3);

	ui->lineEdit_VSet1->setText(QString::number(m_pCharElementInverse->m_fValSection[0], 'f', 3));
	ui->lineEdit_VSet2->setText(QString::number(m_pCharElementInverse->m_fValSection[1], 'f', 3));
	ui->lineEdit_VSet3->setText(QString::number(m_pCharElementInverse->m_fValSection[2], 'f', 3));
	ui->lineEdit_TSet1->setText(QString::number(m_pCharElementInverse->m_fTmSection[0], 'f', 3));
	ui->lineEdit_TSet2->setText(QString::number(m_pCharElementInverse->m_fTmSection[1], 'f', 3));
	ui->lineEdit_TSet3->setText(QString::number(m_pCharElementInverse->m_fTmSection[2], 'f', 3));

	ui->txtID->setText(m_pCharElementInverse->m_strID);
	UpdateImage();
	InitGroup();
}

void QCharEditWidget_Inverse_Eng::UpdateImage()
{
#ifdef _PSX_QT_WINDOWS_
	CString strImage = _P_GetResourcePath();
	strImage += "images/";
#else
	CString strImage = ":/ctrls/images/";
#endif
	CString strCostomText;
	strCostomText = _T("I*");

	if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		strImage += "IEEE";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		strImage += "IAC";
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		strImage += "I2T";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		strImage += "IEC";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRXIDG)
	{
		strImage += "RXIDG";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		strImage += "RICURVE";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		strImage += "LABIECCURVE";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIT)
	{
		strImage += "IT";
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		strImage += "I2TEx";
	}

	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)
	{
		strImage += "UIVP";
		strCostomText = /*"故障电压(V)"*/g_sLangTxt_Native_Faultcurrent;
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)
	{
		strImage += "IUF";
		strCostomText = "U*/F*";
	}
	strImage += "_1.bmp";

	QPixmap pixmap(strImage);
	pixmap = pixmap.scaled(QSize(380, 120), Qt::KeepAspectRatio);
	ui->m_txtImg->setPixmap(pixmap);
	ui->txtID->setText(m_pCharElementInverse->m_strID);
	//ui->label_CurrValue->setText(strCostomText);
}

void QCharEditWidget_Inverse_Eng::InitConnect()
{
	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	connect(ui->checkBox_Set1, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set1_toggled(bool)));
	connect(ui->lineEdit_VSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet1_editFinished()));
	connect(ui->lineEdit_TSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet1_editFinished()));
	connect(ui->checkBox_Set2, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set2_toggled(bool)));
	connect(ui->lineEdit_VSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet2_editFinished()));
	connect(ui->lineEdit_TSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet2_editFinished()));
	connect(ui->checkBox_Set3, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set3_toggled(bool)));
	connect(ui->lineEdit_VSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet3_editFinished()));
	connect(ui->lineEdit_TSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet3_editFinished()));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	//	connect(this, SIGNAL(sig_CharChanged()), pMainWidget,SLOT(slot_CharChanged()));

	//connect(ui->Btn_ClearUserPoints, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	//connect(ui->Btn_AddUserPoint, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));

	//connect(ui->lineEdit_CurrValue,  SIGNAL(editingFinished ()), this, SLOT(slot_CurrValue_editingFinished()));

#ifdef _PSX_QT_LINUX_
	connect(ui->lineEdit_VSet1,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	connect(ui->lineEdit_TSet1,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	connect(ui->lineEdit_VSet2,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	connect(ui->lineEdit_TSet2,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	connect(ui->lineEdit_VSet3,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	connect(ui->lineEdit_TSet3,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
#endif
}

void QCharEditWidget_Inverse_Eng::disConnectAll()
{
	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	disconnect(ui->checkBox_Set1, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set1_toggled(bool)));
	disconnect(ui->lineEdit_VSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet1_editFinished()));
	disconnect(ui->lineEdit_TSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet1_editFinished()));
	disconnect(ui->checkBox_Set2, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set2_toggled(bool)));
	disconnect(ui->lineEdit_VSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet2_editFinished()));
	disconnect(ui->lineEdit_TSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet2_editFinished()));
	disconnect(ui->checkBox_Set3, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set3_toggled(bool)));
	disconnect(ui->lineEdit_VSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet3_editFinished()));
	disconnect(ui->lineEdit_TSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet3_editFinished()));
	disconnect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	//	disconnect(this, SIGNAL(sig_CharChanged()), pMainWidget,SLOT(slot_CharChanged()));

	//disconnect(ui->Btn_ClearUserPoints, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	//disconnect(ui->Btn_AddUserPoint, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));

	//disconnect(ui->lineEdit_CurrValue,  SIGNAL(editingFinished ()), this, SLOT(slot_CurrValue_editingFinished()));

#ifdef _PSX_QT_LINUX_
	disconnect(ui->lineEdit_VSet1,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	disconnect(ui->lineEdit_TSet1,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	disconnect(ui->lineEdit_VSet2,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	disconnect(ui->lineEdit_TSet2,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	disconnect(ui->lineEdit_VSet3,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
	disconnect(ui->lineEdit_TSet3,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
#endif
}

void QCharEditWidget_Inverse_Eng::InitChar()
{
	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_LOGARITHM,FALSE);
	pMainWidget->m_pImpCharactWidget->SetChangePlot(TRUE);
	pMainWidget->m_pImpCharactWidget->EnableSetting(FALSE);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
	if (m_pCharacteristics_Inner == NULL)
	{
		//20240812 gongyiping 坐标轴显示数据为唯一变量则克隆唯一变量，指针指向不为唯一变量数据则获取复制变量
		//if (pMainWidget->m_pImpCharactWidget->m_pCharacteristics == stt_Frame_Characteristics())
		//{
		//	m_pCharacteristics_Inner = (CCharacteristics *)stt_Frame_Characteristics()->Clone();
		//	pMainWidget->m_pImpCharactWidget->m_pCharacteristics = m_pCharacteristics_Inner;
		//}
		//else
		//{
		//	m_pCharacteristics_Inner = pMainWidget->m_pImpCharactWidget->m_pCharacteristics;
		//}
		//为空时获取父窗口内部对象
		m_pCharacteristics_Inner = pMainWidget->GetCharacteristics_Inner();
	}
	if (IsVolInverse())
	{
		pMainWidget->m_pImpCharactWidget->SetAxisName(_T("U(V)"),_T("t(s)"),_T(" "));
	}
	else if (IsUFInverse())
	{
		pMainWidget->m_pImpCharactWidget->SetAxisName(_T("U*/F*"),_T("t(s)"),_T(" "));
	} 
	else
	{
		pMainWidget->m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T(" "));
	}
	pMainWidget->resize(800, 660);
}

void QCharEditWidget_Inverse_Eng::InitGroup()
{
	for (int i = 0 ; i < m_labelList.size(); i++)
	{
		delete m_labelList[i];
		m_labelList[i] = NULL;
	}
	for (int i = 0 ; i < m_editList.size(); i++)
	{
#ifdef _PSX_QT_LINUX_
		disconnect(m_editList[i],SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
#endif
		delete m_editList[i];
		m_editList[i] = NULL;
	}

	m_labelList.clear();
	m_editList.clear();

	if (m_pLowVolModeRadio != NULL)
	{
		m_pLowVolModeRadio->setVisible(FALSE);
	}

	if (m_pOverVolModeRadio != NULL)
	{
		m_pOverVolModeRadio->setVisible(FALSE);
	}

	if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
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
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
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
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		AddLabelToGroup(QObject::tr("Tp"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("A"),1,0);
		AddEditToGroup(1,1);
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		AddLabelToGroup(QObject::tr("Tp"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("K"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("Alpha"),2,0);
		AddEditToGroup(2,1);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRXIDG)
	{
		AddLabelToGroup(QObject::tr("Td"),0,0);
		AddEditToGroup(0,1);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		AddLabelToGroup(QObject::tr("K"),0,0);
		AddEditToGroup(0,1);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		AddLabelToGroup(QObject::tr("a"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("b"),1,0);
		AddEditToGroup(1,1);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIT)
	{
		AddLabelToGroup(QObject::tr("Td"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("P"),1,0);
		AddEditToGroup(1,1);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		AddLabelToGroup(QObject::tr("A"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("P"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("Q"),2,0);
		AddEditToGroup(2,1);

		AddLabelToGroup(QObject::tr("Td"),3,0);
		AddEditToGroup(3,1);
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)
	{
		AddLabelToGroup(QObject::tr("A"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("B"),1,0);
		AddEditToGroup(1,1);

		AddLabelToGroup(QObject::tr("C"),2,0);
		AddEditToGroup(2,1);

		AddLabelToGroup(QObject::tr("D"),3,0);
		AddEditToGroup(3,1);

		AddLabelToGroup(QObject::tr("E"),0,2);
		AddEditToGroup(0,3);

		AddLabelToGroup(QObject::tr("K"),1,2);
		AddEditToGroup(1,3);

		AddLabelToGroup(QObject::tr("p"),2,2);
		AddEditToGroup(2,3);

		AddLabelToGroup(QObject::tr("Vp"),3,2);
		AddEditToGroup(3,3);

		CString strText;

		if (m_pLowVolModeRadio == NULL)
		{
			m_pLowVolModeRadio = new QRadioButton(this);
			m_pLowVolModeRadio->setFont(*g_pSttGlobalFont);
			//strText = _T("低压保护");
			m_pLowVolModeRadio->setText(g_sLangTxt_State_LowVoltageprotection);
			ui->GroupGrid->addWidget(m_pLowVolModeRadio,4,1);
		}

		if (m_pOverVolModeRadio == NULL)
		{
			m_pOverVolModeRadio = new QRadioButton(this);
			m_pOverVolModeRadio->setFont(*g_pSttGlobalFont);
			//strText = _T("过压保护");
			m_pOverVolModeRadio->setText(g_sLangTxt_State_Overvoltageprotection);
			ui->GroupGrid->addWidget(m_pOverVolModeRadio,4,3);
		}

		m_pLowVolModeRadio->setVisible(TRUE);
		m_pOverVolModeRadio->setVisible(TRUE);
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)
	{
		AddLabelToGroup(QObject::tr("D"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("p"),0,2);
		AddEditToGroup(0,3);

		AddLabelToGroup(QObject::tr("Pickup"),1,0);
		AddEditToGroup(1,1);


	}

	UpdateGroup();
}

void QCharEditWidget_Inverse_Eng::UpdateGroup()
{
	if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		// 		SetFormulaPic(0);
		CCharElementIEEE *pIEEE = (CCharElementIEEE *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("IEEE曲线参数设置")*/g_sLangTxt_State_IEEECurset);
		m_editList[0]->setText(pIEEE->m_strTp);
		m_editList[1]->setText(pIEEE->m_strA);
		m_editList[2]->setText(pIEEE->m_strB);
		m_editList[3]->setText(pIEEE->m_strP);
		m_editList[4]->setText(pIEEE->m_strQ);
		m_editList[5]->setText(pIEEE->m_strK1);
		m_editList[6]->setText(pIEEE->m_strK2);
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		// 		SetFormulaPic(1);
		CCharElementIAC *pIAC = (CCharElementIAC *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("IAC曲线参数设置")*/g_sLangTxt_State_IACCurSet);
		m_editList[0]->setText(pIAC->m_strTp);
		m_editList[1]->setText(pIAC->m_strA);
		m_editList[2]->setText(pIAC->m_strB);
		m_editList[3]->setText(pIAC->m_strC);
		m_editList[4]->setText(pIAC->m_strD);
		m_editList[5]->setText(pIAC->m_strE);
		m_editList[6]->setText(pIAC->m_strBeta);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		// 		SetFormulaPic(2);
		CCharElementI2T *pI2T = (CCharElementI2T *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("I2T曲线参数设置")*/g_sLangTxt_State_I2TCurSet);
		m_editList[0]->setText(pI2T->m_strTp);
		m_editList[1]->setText(pI2T->m_strA);
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		// 		SetFormulaPic(3);
		CCharElementIEC *pIEC = (CCharElementIEC *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("IEC曲线参数设置")*/g_sLangTxt_State_IECCurSet);
		m_editList[0]->setText(pIEC->m_strTp);
		m_editList[1]->setText(pIEC->m_strK);
		m_editList[2]->setText(pIEC->m_strAlpha);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRXIDG)
	{
		// 		SetFormulaPic(2);
		CCharElementRXIDG *pRXIDG = (CCharElementRXIDG *)m_pCharElementInverse;
		this->setWindowTitle(QObject::tr("RXIDG曲线参数设置")/*g_sLangTxt_State_I2TCurSet*/);
		m_editList[0]->setText(pRXIDG->m_strTp);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		// 		SetFormulaPic(2);
		CCharElementRICurve *pRICurve = (CCharElementRICurve *)m_pCharElementInverse;
		this->setWindowTitle(QObject::tr("RICURVE曲线参数设置")/*g_sLangTxt_State_I2TCurSet*/);
		m_editList[0]->setText(pRICurve->m_strK);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		// 		SetFormulaPic(2);
		CCharElementLabIecCurve *pLaborelecCurve = (CCharElementLabIecCurve *)m_pCharElementInverse;
		this->setWindowTitle(QObject::tr("LABIECCURVE曲线参数设置")/*g_sLangTxt_State_I2TCurSet*/);
		m_editList[0]->setText(pLaborelecCurve->m_strA);
		m_editList[1]->setText(pLaborelecCurve->m_strB);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIT)
	{
		// 		SetFormulaPic(2);
		CCharElementIT *pIT = (CCharElementIT *)m_pCharElementInverse;
		this->setWindowTitle(QObject::tr("IT曲线参数设置")/*g_sLangTxt_State_I2TCurSet*/);
		m_editList[0]->setText(pIT->m_strTp);
		m_editList[1]->setText(pIT->m_strP);
	}
	else if(m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		// 		SetFormulaPic(2);
		CCharElementI2TEx *pI2TEx = (CCharElementI2TEx *)m_pCharElementInverse;
		this->setWindowTitle(QObject::tr("I2TEx曲线参数设置")/*g_sLangTxt_State_I2TCurSet*/);
		m_editList[0]->setText(pI2TEx->m_strA);
		m_editList[1]->setText(pI2TEx->m_strP);
		m_editList[2]->setText(pI2TEx->m_strQ);
		m_editList[3]->setText(pI2TEx->m_strTp);

	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)
	{
		// 		SetFormulaPic(3);
		CCharElementUIVP *pUIVP = (CCharElementUIVP *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("电压反时限参数设置")*/g_sLangTxt_State_VolLimitSet);
		m_editList[0]->setText(pUIVP->m_strA);
		m_editList[1]->setText(pUIVP->m_strB);
		m_editList[2]->setText(pUIVP->m_strC);
		m_editList[3]->setText(pUIVP->m_strD);
		m_editList[4]->setText(pUIVP->m_strE);
		m_editList[5]->setText(pUIVP->m_strK);
		m_editList[6]->setText(pUIVP->m_strP);
		m_editList[7]->setText(pUIVP->m_strVp);

		disconnect(m_pLowVolModeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnVolModeRadioChanged(bool)));
		disconnect(m_pOverVolModeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnVolModeRadioChanged(bool)));
		m_pLowVolModeRadio->setChecked(!pUIVP->m_nUType);
		m_pOverVolModeRadio->setChecked(pUIVP->m_nUType);

		connect(m_pLowVolModeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnVolModeRadioChanged(bool)));
		connect(m_pOverVolModeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnVolModeRadioChanged(bool)));
	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)
	{
		// 		SetFormulaPic(3);
		CCharElementIUF *pUIVP = (CCharElementIUF *)m_pCharElementInverse;
		this->setWindowTitle(/*QObject::tr("电压反时限参数设置")*/g_sLangTxt_State_VolLimitSet);
		m_editList[0]->setText(pUIVP->m_strD);
		m_editList[1]->setText(pUIVP->m_strP);
		m_editList[2]->setText(pUIVP->m_strPickup);
	}
}

void QCharEditWidget_Inverse_Eng::AddLabelToGroup( QString str,int nRow,int nCol )
{
	//	QFont ft("Microsoft YaHei", 10);//2022-10-31 sy 采用g_pSttGlobalFont
	int nHeight = 25;

	QLabel *tempLabel = new QLabel;
	tempLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempLabel->setText(str);
	tempLabel->setFont(*g_pSttGlobalFont/*ft*/);
	tempLabel->setFixedHeight(nHeight);
	ui->GroupGrid->addWidget(tempLabel,nRow,nCol);
	m_labelList.append(tempLabel);
}

void QCharEditWidget_Inverse_Eng::AddEditToGroup( int nRow,int nCol )
{
	// 	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLineEdit *tempEdit = new QSttLineEdit;
	tempEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempEdit->setFont(*g_pSttGlobalFont/*ft*/);
	tempEdit->setFixedHeight(nHeight);
	initMaxPositiveEdit(tempEdit);
	connect(tempEdit, SIGNAL(editingFinished()),this,SLOT(slot_ElementData_editFinished()));

#ifdef _PSX_QT_LINUX_
	connect(tempEdit,SIGNAL(clicked()),this,SLOT(slot_onlineEdit_Changed()));
#endif
	ui->GroupGrid->addWidget(tempEdit,nRow,nCol);
	m_editList.append(tempEdit);
}

void QCharEditWidget_Inverse_Eng::initMaxPositiveEdit(QLineEdit *lne)
{
	QRegExp rx("^[|0-9|(.)|^]{1,16}|(^\\t?$)"); 
	QRegExpValidator *pReg = new QRegExpValidator(rx, lne);  
	lne->setValidator(pReg); 
}

void QCharEditWidget_Inverse_Eng::setPara(QLineEdit *pEdit, CString &strTemp)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);
	strTemp = QString::number(fv,'f',3);

	pEdit->setText(strTemp); 
}

//void QCharEditWidget_Inverse::setPara(QLineEdit *pEdit, float &fTemp)
//{
//	if (pEdit->text().isEmpty())
//	{
//		pEdit->setText("0.000");
//	}
//
//	QString str = pEdit->text();
//	if (str.right(1).contains("."))
//	{
//		str.append("000");
//	}
//	float fv= str.toFloat();
//	fv = setLimit(0,999.999,fv);
//	fTemp = fv;
//
//	pEdit->setText(QString::number(fv,'f',3));
//}

void QCharEditWidget_Inverse_Eng::ModifyCharByCheck()
{
	if (m_bCheckBox1)
	{
		m_pCharElementInverse->m_nUseSection[0] = 1;
	}
	else
	{
		m_pCharElementInverse->m_nUseSection[0] = 0;
	}

	if (m_bCheckBox2)
	{
		m_pCharElementInverse->m_nUseSection[1] = 1;
	}
	else
	{
		m_pCharElementInverse->m_nUseSection[1] = 0;
	}

	if (m_bCheckBox3)
	{
		m_pCharElementInverse->m_nUseSection[2] = 1;
	}
	else
	{
		m_pCharElementInverse->m_nUseSection[2] = 0;
	}

	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Inverse_Eng::slot_oncheckBox_Set1_toggled(bool b)
{
	if(b)
	{
		ui->checkBox_Set1->setChecked(true);
		m_bCheckBox1 = true;
	}
	else
	{
		ui->checkBox_Set1->setChecked(false);
		ui->checkBox_Set2->setChecked(false);
		ui->checkBox_Set3->setChecked(false);
		m_bCheckBox1 = false;
		m_bCheckBox2 = false;
		m_bCheckBox3 = false;

	}
	ModifyCharByCheck();
}

void QCharEditWidget_Inverse_Eng::slot_oncheckBox_Set2_toggled(bool b)
{
	if(b)
	{
		ui->checkBox_Set1->setChecked(true);
		ui->checkBox_Set2->setChecked(true);
		m_bCheckBox1 = true;
		m_bCheckBox2 = true;
	}
	else
	{
		ui->checkBox_Set2->setChecked(false);
		ui->checkBox_Set3->setChecked(false);
		m_bCheckBox2 = false;
		m_bCheckBox3 = false;
	}
	ModifyCharByCheck();
}

void QCharEditWidget_Inverse_Eng::slot_oncheckBox_Set3_toggled(bool b)
{
	if(b)
	{
		ui->checkBox_Set1->setChecked(true);
		ui->checkBox_Set2->setChecked(true);
		ui->checkBox_Set3->setChecked(true);
		m_bCheckBox1 = true;
		m_bCheckBox2 = true;
		m_bCheckBox3 = true;
	}
	else
	{
		ui->checkBox_Set3->setChecked(false);
		m_bCheckBox3 = false;
	}
	ModifyCharByCheck();
}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_VSet1_editFinished()
{
	float fv = ui->lineEdit_VSet1->text().toFloat();
	fv = setLimit(0,999.999,fv);
	if (fv < ui->lineEdit_VSet2->text().toFloat())
	{
		ui->lineEdit_VSet1->setText(ui->lineEdit_VSet2->text());
	}

	setPara(ui->lineEdit_VSet1, m_pCharElementInverse->m_strValSection[0]);

	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_VSet2_editFinished()
{
	float fv = ui->lineEdit_VSet2->text().toFloat();
	fv = setLimit(0,999.999,fv);
	if (fv < ui->lineEdit_VSet3->text().toFloat())
	{
		ui->lineEdit_VSet2->setText(ui->lineEdit_VSet3->text());
	}
	setPara(ui->lineEdit_VSet2, m_pCharElementInverse->m_strValSection[1]);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_VSet3_editFinished()
{
	setPara(ui->lineEdit_VSet3, m_pCharElementInverse->m_strValSection[2]);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_TSet1_editFinished()
{
	setPara(ui->lineEdit_TSet1, m_pCharElementInverse->m_strTmSection[0]);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_TSet2_editFinished()
{
	setPara(ui->lineEdit_TSet2, m_pCharElementInverse->m_strTmSection[1]);
	emit sig_CharChanged(NULL,TRUE);
}


void QCharEditWidget_Inverse_Eng::slot_onlineEdit_TSet3_editFinished()
{
	setPara(ui->lineEdit_TSet3, m_pCharElementInverse->m_strTmSection[2]);
	emit sig_CharChanged(NULL,TRUE);
}

//void QCharEditWidget_Inverse::slot_CurrValue_editingFinished()
//{
//	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
//	CString strCurrValue = ui.lineEdit_CurrValue->text();
//	pMainWidget->m_pImpCharactWidget->UpdateVertLine(CString_To_double(strCurrValue));
//}

void QCharEditWidget_Inverse_Eng::slot_onlineEdit_Changed()
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

void QCharEditWidget_Inverse_Eng::slot_ElementData_editFinished()
{
	CCharElementInverse *pElement = m_pCharElementInverse;

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
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTRXIDG)
	{
		CCharElementRXIDG *pRXIDG = (CCharElementRXIDG *)pElement;
		setPara(m_editList[0],pRXIDG->m_strTp);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		CCharElementRICurve *pRICurve = (CCharElementRICurve *)pElement;
		setPara(m_editList[0],pRICurve->m_strK);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		CCharElementLabIecCurve *pLaborelecCurve = (CCharElementLabIecCurve *)pElement;
		setPara(m_editList[0],pLaborelecCurve->m_strA);
		setPara(m_editList[1],pLaborelecCurve->m_strB);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIT)
	{
		CCharElementIT *pIT = (CCharElementIT *)pElement;
		setPara(m_editList[0],pIT->m_strTp);
		setPara(m_editList[1],pIT->m_strP);
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		CCharElementI2TEx *pI2TEx = (CCharElementI2TEx *)pElement;
		setPara(m_editList[0],pI2TEx->m_strA);
		setPara(m_editList[1],pI2TEx->m_strP);
		setPara(m_editList[2],pI2TEx->m_strQ);
		setPara(m_editList[3],pI2TEx->m_strTp);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)
	{
		CCharElementUIVP *pUIVP = (CCharElementUIVP *)pElement;
		setPara(m_editList[0],pUIVP->m_strA);
		setPara(m_editList[1],pUIVP->m_strB);
		setPara(m_editList[2],pUIVP->m_strC);
		setPara(m_editList[3],pUIVP->m_strD);
		setPara(m_editList[4],pUIVP->m_strE);
		setPara(m_editList[5],pUIVP->m_strK);
		setPara(m_editList[6],pUIVP->m_strP);
		setPara(m_editList[7],pUIVP->m_strVp);
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)
	{
		CCharElementIUF *pUIVP = (CCharElementIUF *)pElement;
		setPara(m_editList[0],pUIVP->m_strD);
		setPara(m_editList[1],pUIVP->m_strP);
		setPara(m_editList[2],pUIVP->m_strPickup);
	}

	emit sig_CharChanged(NULL,TRUE);
}

bool QCharEditWidget_Inverse_Eng::IsCurrInverse()
{
	if (m_pCharElementInverse == NULL)
	{
		return true;
	}

	if ((m_pCharElementInverse->GetClassID() != CHARCLASSID_CCHARELEMENTUIVP)&&
		(m_pCharElementInverse->GetClassID() != CHARCLASSID_CCHARELEMENTIUF))
	{
		return true;
	}

	return false;
}

bool QCharEditWidget_Inverse_Eng::IsVolInverse()
{
	if (m_pCharElementInverse == NULL)
	{
		return false;
	}

	return (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP);
}

bool QCharEditWidget_Inverse_Eng::IsUFInverse()
{
	if (m_pCharElementInverse == NULL)
	{
		return false;
	}

	return (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF);
}

//void QCharEditWidget_Inverse_Eng::UpdateEdit_CurrValueUserPoint()
//{
//	CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
//	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
//
//	if(!pPoint)
//	{
//		return;
//	}
//
//	CString strValue;
//	strValue.Format(_T("%.03f"),pPoint->m_fX);
//	disconnect(ui->lineEdit_CurrValue,  SIGNAL(editingFinished ()), this, SLOT(slot_CurrValue_editingFinished()));
//	ui->lineEdit_CurrValue->setText(strValue);
//	connect(ui->lineEdit_CurrValue,  SIGNAL(editingFinished ()), this, SLOT(slot_CurrValue_editingFinished()));
//}

void QCharEditWidget_Inverse_Eng::on_btnSelect_clicked()
{
	CString strPath;
	strPath = _P_GetConfigPath();

	if (IsVolInverse())
	{
		strPath += _T("CharLib-volinverse.xml");
	}
	else if (IsUFInverse())
	{
		strPath += _T("CharLib-UFInverse.xml");
	}
	else
	{
		strPath += _T("CharLib-currinverse.xml");
	}

	QCIFeatureAddDig dig(strPath);
	dig.setFont(*g_pSttGlobalFont);
	//	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_CIAddChar(CCharacteristic*)));
	//	dig.exec();

	if (dig.exec() != QDialog::Accepted)
	{
		return;
	}

	slot_CIAddChar(dig.GetSelectedChar());
	UpdateImage();
}

void QCharEditWidget_Inverse_Eng::slot_CIAddChar(CCharacteristic *pObj)
{
	if (pObj == NULL)
	{
		return;
	}
	
	//20240812 gongyiping 
	//CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);
	CCharacteristic* pCurrCharacteristic = m_pCharacteristics_Inner->GetAtIndex_Char(0);
	if (pCurrCharacteristic != NULL)
	{
		//stt_Frame_Characteristics()->DeleteByID(pCurrCharacteristic->m_strID);
		m_pCharacteristics_Inner->DeleteByID(pCurrCharacteristic->m_strID);
	}

	//if (stt_Frame_Characteristics()->AddCharTempClone(pObj))
	if (m_pCharacteristics_Inner->AddCharTempClone(pObj))
	{
		//pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);
		pCurrCharacteristic = m_pCharacteristics_Inner->GetAtIndex_Char(0);

		m_pCharElementInverse = (CCharElementInverse *)pCurrCharacteristic->GetCharacterArea()->GetHead();

		InitGroup();

		ModifyCharByCheck();
		emit sig_CharChanged(NULL,TRUE);
	}
}

void QCharEditWidget_Inverse_Eng::UpdateCharacters(BOOL bCharChaged)
{
	disConnectAll();
	InitData();
	InitConnect();
	InitChar();
	emit sig_CharChanged(NULL,bCharChaged);
}

void QCharEditWidget_Inverse_Eng::GroupDatasToChar(CDataGroup *pDatas)
{
	//20240812 gongyiping 
	//if ((stt_Frame_Characteristics() == NULL)||(m_pCharElementInverse == NULL))
	if ((m_pCharacteristics_Inner == NULL) || (m_pCharElementInverse == NULL))
	{
		return;
	}

	
	//CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);
	CCharacteristic* pCurrCharacteristic = m_pCharacteristics_Inner->GetAtIndex_Char(0);
	
	if (pCurrCharacteristic == NULL)
	{
		return;
	}

	CCharacterArea* pCharacterArea = pCurrCharacteristic->GetCharacterArea();
	CCharInterface *pCharacteristicInterface = pCurrCharacteristic->GetCharInterface();
	CCharInterfaceVariable *pBeginValue = NULL,*pEndValue = NULL,*pStepValue = NULL;
	pBeginValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("BeginValue"));
	pEndValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("EndValue"));
	pStepValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("StepValue"));

	double dBeginValue = 1.0f,dEndValue = 1.0f,dStepValue = 1.0f;
	stt_GetDataValueByID(pDatas,CharInverse_ID_CurrentChangeStart,dBeginValue);
	stt_GetDataValueByID(pDatas,CharInverse_ID_CurrentChangeFinal,dEndValue);
	stt_GetDataValueByID(pDatas,CharInverse_ID_CurrentChangeStep,dStepValue);

	if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)//电压反时限
	{
		// 		CDvmData *pVp = (CDvmData*)pDatas->FindByID(_T("Vp"));
		// 		double dVp = 100.0f;
		// 
		// 		if (pVp != NULL)
		// 		{
		// 			dVp = CString_To_double(pVp->m_strValue);
		// 		}
		// 
		// 		dBeginValue /= dVp;
		// 		dEndValue /= dVp;
		// 		dStepValue /= dVp;

	}
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)//过励磁
	{
		CCharElementIUF *pCCharElementIUF = (CCharElementIUF*)m_pCharElementInverse;
		pCCharElementIUF->m_fK = g_oSystemParas.m_fVNom/(1.7320508*g_oSystemParas.m_fFNom);
		pCCharElementIUF->m_strK.Format(_T("%lf"),pCCharElementIUF->m_fK);
	}	
	else
	{
		CDvmData *pRefValueType = (CDvmData*)pDatas->FindByID(_T("RefValueType"));
		CDvmData *pIn = (CDvmData*)pDatas->FindByID(_T("In"));
		CDvmData *pIpu = (CDvmData*)pDatas->FindByID(_T("Ipu"));

		if ((pRefValueType != NULL)&&(pIn != NULL)&& (pIpu != NULL))
		{
			double dStdValue = 1.0f;
			long nRefValueType = CString_To_long(pRefValueType->m_strValue);

			if (nRefValueType == 0)
			{
				dStdValue = CString_To_double(pIn->m_strValue);
			} 
			else
			{
				dStdValue = CString_To_double(pIn->m_strValue)*CString_To_double(pIpu->m_strValue);
			}

			dBeginValue *= dStdValue;
			dEndValue *= dStdValue;
			dStepValue *= dStdValue;
		}
	}

	if (pBeginValue)
	{
		pBeginValue->m_strValue.Format(_T("%lf"),dBeginValue);
	}

	if (pEndValue)
	{
		pEndValue->m_strValue.Format(_T("%lf"),dEndValue);
	}

	if (pStepValue)
	{
		pStepValue->m_strValue.Format(_T("%lf"),dStepValue);
	}

    CCharTestObjects *pTestLines = pCharacterArea->GetCharTestObjects();

	if (pTestLines != NULL)
	{
		//根据始值、终止、步长添加测试点
        CCharTestPoints *pTestPoints = pTestLines->GetCharTestPoints();

		if(pTestPoints != NULL)
		{
			pTestPoints->m_dFrom = dBeginValue;
			pTestPoints->m_dTo = dEndValue;
			pTestPoints->m_dStep = dStepValue;
		}
	}

	emit sig_CharChanged(NULL,FALSE);
}

void QCharEditWidget_Inverse_Eng::UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas)
{
	//20240812 gongyiping 
	//if ((stt_Frame_Characteristics() == NULL)||(m_pCharElementInverse == NULL))
	if ((m_pCharacteristics_Inner == NULL) || (m_pCharElementInverse == NULL))
	{
		return;
	}

	//CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);
	CCharacteristic* pCurrCharacteristic = m_pCharacteristics_Inner->GetAtIndex_Char(0);

	if (pCurrCharacteristic == NULL)
	{
		return;
	}

	CCharInterface *pCharacteristicInterface = pCurrCharacteristic->GetCharInterface();
	CCharInterfaceVariable *pBeginValue = NULL,*pEndValue = NULL,*pStepValue = NULL;
	pBeginValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("BeginValue"));
	pEndValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("EndValue"));
	pStepValue = (CCharInterfaceVariable*)pCharacteristicInterface->FindByID(_T("StepValue"));

	if ((pBeginValue == NULL)||(pEndValue == NULL)|| (pStepValue == NULL))
	{
		return;
	}

	if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)//电压反时限
	{
		CDvmData *pVp = (CDvmData*)pCurrentUIParas->FindByID(_T("Vp"));

		if (pVp == NULL)
		{
			return;
		}

		double dVp = 100.0f;

		pBeginValue->m_strScript = CharInverse_ID_CurrentChangeStart/*.Format(_T("%s/%lf"),CharInverse_ID_CurrentChangeStart,dVp)*/;
		pEndValue->m_strScript = CharInverse_ID_CurrentChangeFinal/*.Format(_T("%s/%lf"),CharInverse_ID_CurrentChangeFinal,dVp)*/;
		pStepValue->m_strScript = CharInverse_ID_CurrentChangeStep/*.Format(_T("%s/%lf"),CharInverse_ID_CurrentChangeStep,dVp)*/;
	} 
	else if (m_pCharElementInverse->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)//过励磁
	{
		// 		CDvmData *pVp = (CDvmData*)pCurrentUIParas->FindByID(_T("Vp"));
		// 
		// 		if (pVp == NULL)
		// 		{
		// 			return;
		// 		}
		// 
		// 		double dVp = 100.0f;
		// 
		pBeginValue->m_strScript = CharInverse_ID_CurrentChangeStart;
		pEndValue->m_strScript = CharInverse_ID_CurrentChangeFinal;
		pStepValue->m_strScript = CharInverse_ID_CurrentChangeStep;
	} 
	else//电流反时限
	{
		CDvmData *pRefValueType = (CDvmData*)pCurrentUIParas->FindByID(_T("RefValueType"));
		CDvmData *pIn = (CDvmData*)pCurrentUIParas->FindByID(_T("In"));
		CDvmData *pIpu = (CDvmData*)pCurrentUIParas->FindByID(_T("Ipu"));

		if ((pRefValueType == NULL)||(pIn == NULL)|| (pIpu == NULL))
		{
			return;
		}

		double dStdValue = 1.0f;
		long nRefValueType = CString_To_long(pRefValueType->m_strValue);

		if (nRefValueType == 0)
		{
			dStdValue = CString_To_double(pIn->m_strValue);
		} 
		else
		{
			dStdValue = CString_To_double(pIn->m_strValue)*CString_To_double(pIpu->m_strValue);
		}

		pBeginValue->m_strScript.Format(_T("%s*%lf"),CharInverse_ID_CurrentChangeStart,dStdValue);
		pEndValue->m_strScript.Format(_T("%s*%lf"),CharInverse_ID_CurrentChangeFinal,dStdValue);
		pStepValue->m_strScript.Format(_T("%s*%lf"),CharInverse_ID_CurrentChangeStep,dStdValue);
	}
}

void QCharEditWidget_Inverse_Eng::SetInverseFont()
{
	ui->label_26->setFont(*g_pSttGlobalFont);
	ui->lineEdit_VSet1->setFont(*g_pSttGlobalFont);
	ui->label_34->setFont(*g_pSttGlobalFont);
	ui->label_35->setFont(*g_pSttGlobalFont);
	ui->lineEdit_TSet2->setFont(*g_pSttGlobalFont);
	ui->label_30->setFont(*g_pSttGlobalFont);
	ui->checkBox_Set3->setFont(*g_pSttGlobalFont);
	ui->lineEdit_TSet3->setFont(*g_pSttGlobalFont);
	ui->checkBox_Set2->setFont(*g_pSttGlobalFont);
	ui->label_27->setFont(*g_pSttGlobalFont);
	ui->label_31->setFont(*g_pSttGlobalFont);
	ui->lineEdit_VSet3->setFont(*g_pSttGlobalFont);
	ui->lineEdit_VSet2->setFont(*g_pSttGlobalFont);
	ui->label_38->setFont(*g_pSttGlobalFont);
	ui->label_39->setFont(*g_pSttGlobalFont);
	ui->lineEdit_TSet1->setFont(*g_pSttGlobalFont);
	ui->checkBox_Set1->setFont(*g_pSttGlobalFont);
	ui->btnSelect->setFont(*g_pSttGlobalFont);
	ui->txtID->setFont(*g_pSttGlobalFont);
	ui->txtName->setFont(*g_pSttGlobalFont);

	//ui->Btn_ClearUserPoints->setFont(*g_pSttGlobalFont);
	//ui->label_CurrValue->setFont(*g_pSttGlobalFont);
	//ui->lineEdit_CurrValue->setFont(*g_pSttGlobalFont);
	//ui->Btn_AddUserPoint->setFont(*g_pSttGlobalFont);
}

//void QCharEditWidget_Inverse::slot_btnUserClear(bool bState)
//{
//	if (stt_Frame_Characteristics() == NULL)
//	{
//		return;
//	}
//
//	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->GetHead();
//	CCharacterArea* pArea = pChar->GetCharacterArea();
//	CCharElementTestLines *pTestLines = pArea->GetCharTestObjects();
//
//	if (pTestLines == NULL)
//	{
//		return;
//	}
//
//	CExBaseObject *pCurrObj = NULL;
//	POS pos = pTestLines->GetHeadPosition();
//	long nIndex = 0;
//	while (pos)
//	{
//		pCurrObj = pTestLines->GetNext(pos);
//
//		{
//			continue;
//		}
//
//		pTestLines->Delete(pCurrObj);
//	}
//
//	emit sig_CharChanged(NULL,TRUE);
//}

void QCharEditWidget_Inverse_Eng::slot_OnVolModeRadioChanged(bool bState)
{
	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());

	if (pRadioBtn != m_pOverVolModeRadio)
	{
		return;
	}

	CCharElementUIVP *pUIVP = (CCharElementUIVP *)m_pCharElementInverse;
	pUIVP->m_nUType = bState;
	emit sig_CharChanged(NULL,TRUE);
}

//void QCharEditWidget_Inverse::slot_btnUserAdd(bool bState)
//{
//	CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
//
//	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
//
//	if(!pPoint)
//	{
//		return;
//	}
//
//	CCharacteristic* pChar = (CCharacteristic*)stt_Frame_Characteristics()->GetHead();
//	CCharacterArea* pArea = pChar->GetCharacterArea();
//	CCharElementTestLines *pTestLines = pArea->GetCharTestObjects();
//
//	if (pTestLines == NULL)
//	{
//		return;
//	}
//
//	//	long nPoints = pCharElementInverse->GetTestLines_Sys() + pCharElementInverse->GetUserTestPoints();
//	CCharElementTestLine* pTestLine = new CCharElementTestLine();
//	pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
//	//	pTestLine->m_nTestLineID = char_GetTestLineID(pTestLines,pTestLines->GetCount());
//	pTestLine->m_fPos = pPoint->m_fX;
//	pTestLine->m_fXset = pPoint->m_fX;
//	pTestLine->m_fYset = pPoint->m_fY;
//	pTestLine->m_fXb = pPoint->m_fX;
//	pTestLine->m_fXe = pPoint->m_fX;
//
//	double dValue1 = log10(pPoint->m_fY);
//	double dValue2 = dValue1 + CharElementInverse_ErrorLenth/2;
//	pTestLine->m_fYb = pow(10,dValue2)/* pPoint->m_fY + pCharElementInverse->GetErrorLength()*/;
//	dValue2 = dValue1 - CharElementInverse_ErrorLenth/2;
//	pTestLine->m_fYe = pow(10,dValue2)/*pPoint->m_fY - pCharElementInverse->GetErrorLength()*/;
//	pTestLines->AddNewChild(pTestLine);
//	//	pTestLines->SetUserTestPoint(pTestLines->GetCount());
//	emit sig_CharChanged(NULL,TRUE);
//}

//void QCharEditWidget_Inverse_Eng::OnLeftButtonDown()
//{
    //QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
    //pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0);
	//emit sig_CharChanged();
	//UpdateEdit_CurrValueUserPoint();
//}

void QCharEditWidget_Inverse_Eng::UpDataParas()
{

	//CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	//pCharacteristics->DeleteAll();
	//pCharacteristics->AppendClone(m_pCharacteristics_Inner);

}
