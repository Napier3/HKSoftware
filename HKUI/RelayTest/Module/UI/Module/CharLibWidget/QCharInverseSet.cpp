#include "QCharInverseSet.h"
#include "ui_QCharInverseSet.h"
#include "../../../XLangResource_Native.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QCharInverseSet::QCharInverseSet(CCharElement *pCharElement, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::QCharInverseSet){
	ui->setupUi(this);

	m_nIsOK = 0;

	this->setWindowTitle(QObject::tr("特性曲线元素"));
	m_pCurCharElement = pCharElement;
	m_pCharElementInverse = (CCharElementInverse *)m_pCurCharElement;
	m_bCheckBox1 = m_pCharElementInverse->m_nUseSection[0];
	m_bCheckBox2 = m_pCharElementInverse->m_nUseSection[1];
	m_bCheckBox3 = m_pCharElementInverse->m_nUseSection[2];

	InitData();
	InitConnect();
        InitLanguage();
}

QCharInverseSet::~QCharInverseSet()
{
delete ui;
}

//////////////////////////////////////////////////////////////////////////
void QCharInverseSet::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui->label_26, g_sLangTxt_Native_actionSetting, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_27, g_sLangTxt_Gradient_ActionTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->checkBox_Set1, g_sLangTxt_Native_SingleTimeLimit, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui->checkBox_Set2, g_sLangTxt_Native_DoubleTimeLimit, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui->checkBox_Set3, g_sLangTxt_Native_TripleTimeLimit, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui->pushButton_OK, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pushButton_CANCEL, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}
void QCharInverseSet::InitData()
{
// 	lne_Name->setDisabled(true);
// 	lne_Name->setFixedSize(200,25);

// 	CString strName;
// 	strName = stt_get_test_item_name(m_pActionTimeTest);	//获取故障名称

// 	lne_Name->setText(strName);
    ui->checkBox_Set1->setChecked(m_bCheckBox1);
    ui->checkBox_Set2->setChecked(m_bCheckBox2);
    ui->checkBox_Set3->setChecked(m_bCheckBox3);

	CCharElementInverse *pElement = m_pCharElementInverse;

    ui->lineEdit_VSet1->setText(QString::number(pElement->m_fValSection[0], 'f', 3));
    ui->lineEdit_VSet2->setText(QString::number(pElement->m_fValSection[1], 'f', 3));
    ui->lineEdit_VSet3->setText(QString::number(pElement->m_fValSection[2], 'f', 3));
    ui->lineEdit_TSet1->setText(QString::number(pElement->m_fTmSection[0], 'f', 3));
    ui->lineEdit_TSet2->setText(QString::number(pElement->m_fTmSection[1], 'f', 3));
    ui->lineEdit_TSet3->setText(QString::number(pElement->m_fTmSection[2], 'f', 3));

	InitGroup();
}

void QCharInverseSet::InitConnect()
{
    connect(ui->checkBox_Set1, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set1_toggled(bool)));
    connect(ui->lineEdit_VSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet1_editFinished()));
    connect(ui->lineEdit_TSet1,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet1_editFinished()));
    connect(ui->checkBox_Set2, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set2_toggled(bool)));
    connect(ui->lineEdit_VSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet2_editFinished()));
    connect(ui->lineEdit_TSet2,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet2_editFinished()));
    connect(ui->checkBox_Set3, SIGNAL(toggled(bool)),	this,SLOT(slot_oncheckBox_Set3_toggled(bool)));
    connect(ui->lineEdit_VSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_VSet3_editFinished()));
    connect(ui->lineEdit_TSet3,SIGNAL(editingFinished()),this,SLOT(slot_onlineEdit_TSet3_editFinished()));

// 	connect(pbn_Add,	  SIGNAL(clicked ()), this, SLOT(slot_PbnAddClicked()));
// 	connect(pbn_AddSerial,SIGNAL(clicked ()), this, SLOT(slot_PbnAddSerialClicked()));
// 	connect(pbn_Del,	  SIGNAL(clicked ()), this, SLOT(slot_PbnDelClicked()));
// 	connect(pbn_DelSerial,SIGNAL(clicked ()), this, SLOT(slot_PbnDelAllClicked()));
// 	connect(pbn_Clear,	  SIGNAL(clicked ()), this, SLOT(slot_PbnClearResultClicked()));
// 	connect(pbn_ClearAll, SIGNAL(clicked ()), this, SLOT(slot_PbnClearAllClicked()));
    connect(ui->pushButton_OK,SIGNAL(clicked ()), this, SLOT(slot_PbnOkClicked()));
    connect(ui->pushButton_CANCEL,SIGNAL(clicked ()), this, SLOT(slot_PbnCancelClicked()));

	//更新表格数据
// 	connect(m_pActionTimeWidget,SIGNAL(sig_FaultTypeChange()),this,SLOT(slot_FaultTypeChanged()));
// 	connect(m_pActionTimeWidget,SIGNAL(sig_FaultCurChange()),this,SLOT(slot_FaultCurChangedFinished()));
// 
// 	connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));
}

void QCharInverseSet::InitGroup()
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

	if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
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
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
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
	else if(m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		AddLabelToGroup(QObject::tr("Tp"),0,0);
		AddEditToGroup(0,1);

		AddLabelToGroup(QObject::tr("A"),1,0);
		AddEditToGroup(1,1);
	}
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
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

void QCharInverseSet::UpdateGroup()
{
	if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
// 		SetFormulaPic(0);
		CCharElementIEEE *pIEEE = (CCharElementIEEE *)m_pCurCharElement;
		this->setWindowTitle(QObject::tr("IEEE曲线元素设置"));
		m_editList[0]->setText(pIEEE->m_strTp);
		m_editList[1]->setText(pIEEE->m_strA);
		m_editList[2]->setText(pIEEE->m_strB);
		m_editList[3]->setText(pIEEE->m_strP);
		m_editList[4]->setText(pIEEE->m_strQ);
		m_editList[5]->setText(pIEEE->m_strK1);
		m_editList[6]->setText(pIEEE->m_strK2);
	}
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
// 		SetFormulaPic(1);
		CCharElementIAC *pIAC = (CCharElementIAC *)m_pCurCharElement;
		this->setWindowTitle(QObject::tr("IAC曲线元素设置"));
		m_editList[0]->setText(pIAC->m_strTp);
		m_editList[1]->setText(pIAC->m_strA);
		m_editList[2]->setText(pIAC->m_strB);
		m_editList[3]->setText(pIAC->m_strC);
		m_editList[4]->setText(pIAC->m_strD);
		m_editList[5]->setText(pIAC->m_strE);
		m_editList[6]->setText(pIAC->m_strBeta);
	}
	else if(m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
// 		SetFormulaPic(2);
		CCharElementI2T *pI2T = (CCharElementI2T *)m_pCurCharElement;
		this->setWindowTitle(QObject::tr("I2T曲线元素设置"));
		m_editList[0]->setText(pI2T->m_strTp);
		m_editList[1]->setText(pI2T->m_strA);
	}
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
// 		SetFormulaPic(3);
		CCharElementIEC *pIEC = (CCharElementIEC *)m_pCurCharElement;
		this->setWindowTitle(QObject::tr("IEC曲线元素设置"));
		m_editList[0]->setText(pIEC->m_strTp);
		m_editList[1]->setText(pIEC->m_strK);
		m_editList[2]->setText(pIEC->m_strAlpha);
	}
}

void QCharInverseSet::initMaxPositiveEdit( QLineEdit *lne )
{
	QRegExp rx("^[|0-9|(.)|^]{1,16}|(^\\t?$)"); 
	QRegExpValidator *pReg = new QRegExpValidator(rx, lne);  
	lne->setValidator(pReg); 
}

void QCharInverseSet::setPara(QLineEdit *A, CString &strTemp)
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

void QCharInverseSet::setPara( QLineEdit *A, float &fTemp )
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

void QCharInverseSet::AddLabelToGroup( QString str,int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLabel *tempLabel = new QLabel;
	tempLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempLabel->setText(str);
	tempLabel->setFont(ft);
	tempLabel->setFixedHeight(nHeight);
	//tempLabel->setFixedWidth(100);
    ui->GroupGrid->addWidget(tempLabel,nRow,nCol);
	m_labelList.append(tempLabel);
}

void QCharInverseSet::AddEditToGroup( int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLineEdit *tempEdit = new QLineEdit;
	tempEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempEdit->setFont(ft);
	tempEdit->setFixedHeight(nHeight);
	initMaxPositiveEdit(tempEdit);
	connect(tempEdit, SIGNAL(editingFinished()),this,SLOT(slot_ElementData_editFinished()));
    ui->GroupGrid->addWidget(tempEdit,nRow,nCol);
	m_editList.append(tempEdit);
}

void QCharInverseSet::ModifyCharByCheck()
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

	emit sig_CharChanged();
}


void QCharInverseSet::slot_oncheckBox_Set1_toggled(bool b)
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
// 	emit sig_CharChanged();
}

void QCharInverseSet::slot_oncheckBox_Set2_toggled(bool b)
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

// 	emit sig_CharChanged();
}

void QCharInverseSet::slot_oncheckBox_Set3_toggled(bool b)
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

// 	emit sig_CharChanged();
}

void QCharInverseSet::slot_onlineEdit_VSet1_editFinished()
{
    float fv = ui->lineEdit_VSet1->text().toFloat();
	fv = setLimit(0,999.999,fv);
    if (fv < ui->lineEdit_VSet2->text().toFloat())
	{
        ui->lineEdit_VSet1->setText(ui->lineEdit_VSet2->text());
	}

    setPara(ui->lineEdit_VSet1, m_pCharElementInverse->m_strValSection[0]);

	emit sig_CharChanged();
}

void QCharInverseSet::slot_onlineEdit_VSet2_editFinished()
{
    float fv = ui->lineEdit_VSet2->text().toFloat();
	fv = setLimit(0,999.999,fv);
    if (fv < ui->lineEdit_VSet3->text().toFloat())
	{
        ui->lineEdit_VSet2->setText(ui->lineEdit_VSet3->text());
	}
    setPara(ui->lineEdit_VSet2, m_pCharElementInverse->m_strValSection[1]);
	emit sig_CharChanged();
}

void QCharInverseSet::slot_onlineEdit_VSet3_editFinished()
{
    setPara(ui->lineEdit_VSet3, m_pCharElementInverse->m_strValSection[2]);
	emit sig_CharChanged();
}

void QCharInverseSet::slot_onlineEdit_TSet1_editFinished()
{
    setPara(ui->lineEdit_TSet1, m_pCharElementInverse->m_strTmSection[0]);
	emit sig_CharChanged();
}

void QCharInverseSet::slot_onlineEdit_TSet2_editFinished()
{
    setPara(ui->lineEdit_TSet2, m_pCharElementInverse->m_strTmSection[1]);
	emit sig_CharChanged();
}


void QCharInverseSet::slot_onlineEdit_TSet3_editFinished()
{
    setPara(ui->lineEdit_TSet3, m_pCharElementInverse->m_strTmSection[2]);
	emit sig_CharChanged();
}

void QCharInverseSet::slot_ElementData_editFinished()
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

	emit sig_CharChanged();
}

void QCharInverseSet::slot_PbnOkClicked()
{
	m_nIsOK = 1;
	close();
}

void QCharInverseSet::slot_PbnCancelClicked()
{
	m_nIsOK = 2;
	close();
}
