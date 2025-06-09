#include "ActionTimeAddMultDlg.h"
#include "ui_ActionTimeAddMultDlg.h"
#include "ActionTimeCommon.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../XLangResource_Native.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include <QMessageBox>
extern CFont *g_pSttGlobalFont;

QActionTimeAddMultDlg::QActionTimeAddMultDlg(QWidget *parent) :
ui(new Ui::QActionTimeAddMultDlg)
{
	ui->setupUi(this);
	m_pCurrDataGroup = NULL;
    m_nInputWidgetWidth = 120;
	InitUI();
    InitConnect();

}

QActionTimeAddMultDlg::~QActionTimeAddMultDlg()
{
    delete ui;
}

void QActionTimeAddMultDlg::InitConnect()
{
    connect(m_cbLN, SIGNAL(stateChanged(int)), this, SLOT(on_LN_Check_StateChanged(int)));
    connect(m_cbLL, SIGNAL(stateChanged(int)), this, SLOT(on_LL_Check_StateChanged(int)));
    connect(m_cbThreePhase, SIGNAL(stateChanged(int)), this, SLOT(on_ThreePhase_Check_StateChanged(int)));
    connect(m_cbI0, SIGNAL(stateChanged(int)), this, SLOT(on_I0_Check_StateChanged(int)));
    connect(m_cbI2, SIGNAL(stateChanged(int)), this, SLOT(on_I2_Check_StateChanged(int)));
    connect(m_cbLN, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_cbLL, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_cbThreePhase, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_cbI0, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_cbI2, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_cbThreeParallel, SIGNAL(stateChanged(int)), this, SLOT(on_TestCheck_StateChanged()));
    connect(m_editLNVol,SIGNAL(editingFinished()),this,SLOT(on_m_editLNVol_editingFinished()));
    connect(m_editLLVol,SIGNAL(editingFinished()),this,SLOT(on_m_editLLVol_editingFinished()));
    connect(m_editThreePhaseVol,SIGNAL(editingFinished()),this,SLOT(on_m_editThreePhaseVol_editingFinished()));
    connect(m_editI0Vol,SIGNAL(editingFinished()),this,SLOT(on_m_editI0Vol_editingFinished()));
    connect(m_editI2Vol,SIGNAL(editingFinished()),this,SLOT(on_m_editI2Vol_editingFinished()));
}

void QActionTimeAddMultDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/ActionTimeTest.png");
#else
	strPngPath =  ":/ctrls/images/ActionTimeTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);

    QColor backgrdColor = this->palette().color(QPalette::Background);
    ui->m_tableWidget->setStyleSheet(QString("QTableWidget { background-color: %1; }").arg(backgrdColor.name()));
    ui->m_tableWidget->setFont(*g_pSttGlobalFont);
	ui->m_tableWidget->setColumnWidth(0,0.25*this->width());
	ui->m_tableWidget->setColumnWidth(1,0.45*this->width());
    for(int i = 0; i < 7; i++)
	{
        ui->m_tableWidget->setRowHeight(i, 50);
	}

    ui->m_tableWidget->item(0, 0)->setText(g_sLangTxt_ActionTime_TestItem);
    ui->m_tableWidget->item(0, 1)->setText(g_sLangTxt_Native_FaultVoltage);
    ui->m_tableWidget->item(0, 2)->setText(g_sLangTxt_ActionTime_FaultPhase);
	ui->m_tableWidget->verticalHeader()->setVisible(false);
	ui->m_tableWidget->setShowGrid(true);
    ui->m_tableWidget->setFixedHeight(352);
	this->setFont(*g_pSttGlobalFont);

	QWidget *containerWidget_1 = new QWidget();
	QHBoxLayout *horizontalLayout_1 = new QHBoxLayout(containerWidget_1);
    horizontalLayout_1->setContentsMargins(7, 0, 0, 0);
	m_cbLN = new QCheckBox(/*单相接地短路*/g_sLangTxt_ActionTime_LNShort, ui->m_tableWidget);
    //horizontalLayout_1->addStretch();
	horizontalLayout_1->addWidget(m_cbLN);
    //horizontalLayout_1->addStretch();
    ui->m_tableWidget->setCellWidget(1, 0, containerWidget_1);

	QWidget *containerWidget_2 = new QWidget();
	QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(containerWidget_2);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    m_editLNVol = new QLineEdit(ui->m_tableWidget);
    m_editLNVol->setFixedWidth(80);
	m_rbLNFaultVolShort = new QRadioButton(/*短路电压*/g_sLangTxt_ActionTime_ShortVol, ui->m_tableWidget);
	m_rbLNFaultVolZero = new QRadioButton(/*零序电压*/g_sLangTxt_ActionTime_ZeroVol, ui->m_tableWidget);
    horizontalLayout_2->addStretch();
    horizontalLayout_2->addWidget(m_editLNVol);
    horizontalLayout_2->addStretch();
	horizontalLayout_2->addWidget(m_rbLNFaultVolShort);
    horizontalLayout_2->addStretch();
	horizontalLayout_2->addWidget(m_rbLNFaultVolZero);
    horizontalLayout_2->addStretch();
    ui->m_tableWidget->setCellWidget(1, 1, containerWidget_2);

	QWidget *containerWidget_3 = new QWidget();
	QHBoxLayout *horizontalLayout_3 = new QHBoxLayout(containerWidget_3);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    m_cbLNAN = new QCheckBox(QString("AN"), ui->m_tableWidget);
	horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbLNAN);
    m_cbLNBN = new QCheckBox(QString("BN"), ui->m_tableWidget);
	horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbLNBN);
    m_cbLNCN = new QCheckBox(QString("CN"), ui->m_tableWidget);
	horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbLNCN);
	horizontalLayout_3->addStretch();
    ui->m_tableWidget->setCellWidget(1, 2, containerWidget_3);

	QWidget *containerWidget_4 = new QWidget();
	QHBoxLayout *horizontalLayout_4 = new QHBoxLayout(containerWidget_4);
    horizontalLayout_4->setContentsMargins(7, 0, 0, 0);
	m_cbLL = new QCheckBox(/*相间短路*/g_sLangTxt_ActionTime_LLShort, ui->m_tableWidget);
    //horizontalLayout_4->addStretch();
	horizontalLayout_4->addWidget(m_cbLL);
    //horizontalLayout_4->addStretch();
    ui->m_tableWidget->setCellWidget(2, 0, containerWidget_4);

	QWidget *containerWidget_5 = new QWidget();
	QHBoxLayout *horizontalLayout_5 = new QHBoxLayout(containerWidget_5);
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    m_editLLVol = new QLineEdit(ui->m_tableWidget);
    m_editLLVol->setFixedWidth(80);
	m_rbLLFaultVolShort = new QRadioButton(/*短路电压*/g_sLangTxt_ActionTime_ShortVol, ui->m_tableWidget);
    m_rbLLFaultVolNeg = new QRadioButton(/*负序电压*/g_sLangTxt_ActionTime_NegVol, ui->m_tableWidget);
    horizontalLayout_5->addStretch();
    horizontalLayout_5->addWidget(m_editLLVol);
    horizontalLayout_5->addStretch();
	horizontalLayout_5->addWidget(m_rbLLFaultVolShort);
    horizontalLayout_5->addStretch();
    horizontalLayout_5->addWidget(m_rbLLFaultVolNeg);
    horizontalLayout_5->addStretch();
    ui->m_tableWidget->setCellWidget(2, 1, containerWidget_5);

	QWidget *containerWidget_6 = new QWidget();
	QHBoxLayout *horizontalLayout_6 = new QHBoxLayout(containerWidget_6);
    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    m_cbLLAB = new QCheckBox(QString("AB"), ui->m_tableWidget);
	horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLLAB);
    m_cbLLBC = new QCheckBox(QString("BC"), ui->m_tableWidget);
	horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLLBC);
    m_cbLLCA = new QCheckBox(QString("CA"), ui->m_tableWidget);
	horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLLCA);
	horizontalLayout_6->addStretch();
    ui->m_tableWidget->setCellWidget(2, 2,containerWidget_6);

	QWidget *containerWidget_7 = new QWidget();
	QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(containerWidget_7);
    horizontalLayout_7->setContentsMargins(7, 0, 0, 0);
	m_cbThreePhase = new QCheckBox(/*三相短路*/g_sLangTxt_ActionTime_ThreePhaseShort, ui->m_tableWidget);
    //horizontalLayout_7->addStretch();
	horizontalLayout_7->addWidget(m_cbThreePhase);
    //horizontalLayout_7->addStretch();
    ui->m_tableWidget->setCellWidget(3, 0,containerWidget_7);

    QWidget *containerWidget_8 = new QWidget();
    QHBoxLayout *horizontalLayout_8 = new QHBoxLayout(containerWidget_8);
    horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
    m_editThreePhaseVol = new QLineEdit(ui->m_tableWidget);
    horizontalLayout_8->addStretch();
    horizontalLayout_8->addWidget(m_editThreePhaseVol);
    horizontalLayout_8->addStretch();
    ui->m_tableWidget->setCellWidget(3, 1, containerWidget_8);

    QTableWidgetItem *pItem;
    pItem = new QTableWidgetItem(QString("---"));
    pItem->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(3, 2, pItem);

    QWidget *containerWidget_9 = new QWidget();
    QHBoxLayout *horizontalLayout_9 = new QHBoxLayout(containerWidget_9);
    horizontalLayout_9->setContentsMargins(7, 0, 0, 0);
    m_cbI0 = new QCheckBox(/*零序电流3I0*/g_sLangTxt_ActionTime_ZeroCur, ui->m_tableWidget);
    //horizontalLayout_9->addStretch();
    horizontalLayout_9->addWidget(m_cbI0);
    //horizontalLayout_9->addStretch();
    ui->m_tableWidget->setCellWidget(4, 0, containerWidget_9);

    QWidget *containerWidget_10 = new QWidget();
    QHBoxLayout *horizontalLayout_10 = new QHBoxLayout(containerWidget_10);
    horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
    m_editI0Vol = new QLineEdit(ui->m_tableWidget);
    horizontalLayout_10->addStretch();
    horizontalLayout_10->addWidget(m_editI0Vol);
    horizontalLayout_10->addStretch();
    ui->m_tableWidget->setCellWidget(4, 1, containerWidget_10);

    pItem = new QTableWidgetItem(QString("---"));
    pItem->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(4, 2, pItem);

    QWidget *containerWidget_11 = new QWidget();
    QHBoxLayout *horizontalLayout_11 = new QHBoxLayout(containerWidget_11);
    horizontalLayout_11->setContentsMargins(7, 0, 0, 0);
    m_cbI2 = new QCheckBox(/*负序电流I2*/g_sLangTxt_ActionTime_NegCur, ui->m_tableWidget);
    //horizontalLayout_11->addStretch();
    horizontalLayout_11->addWidget(m_cbI2);
    //horizontalLayout_11->addStretch();
    ui->m_tableWidget->setCellWidget(5, 0, containerWidget_11);

    QWidget *containerWidget_12 = new QWidget();
    QHBoxLayout *horizontalLayout_12 = new QHBoxLayout(containerWidget_12);
    horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
    m_editI2Vol = new QLineEdit(ui->m_tableWidget);
    horizontalLayout_12->addStretch();
    horizontalLayout_12->addWidget(m_editI2Vol);
    horizontalLayout_12->addStretch();
    ui->m_tableWidget->setCellWidget(5, 1, containerWidget_12);

    pItem = new QTableWidgetItem(QString("---"));
    pItem->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(5, 2, pItem);

    QWidget *containerWidget_13 = new QWidget();
    QHBoxLayout *horizontalLayout_13 = new QHBoxLayout(containerWidget_13);
    horizontalLayout_13->setContentsMargins(7, 0, 0, 0);
    m_cbThreeParallel = new QCheckBox(/*三相电流并联*/g_sLangTxt_ActionTime_ThreeParallel, ui->m_tableWidget);
    //horizontalLayout_13->addStretch();
    horizontalLayout_13->addWidget(m_cbThreeParallel);
    //horizontalLayout_13->addStretch();
    ui->m_tableWidget->setCellWidget(6, 0, containerWidget_13);

    pItem = new QTableWidgetItem(QString("---"));
    pItem->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(6, 1, pItem);
    pItem = new QTableWidgetItem(QString("---"));
    pItem->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(6, 2, pItem);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_ERRORTYPE);
    ui->m_cbbErrType->ShowBaseList(pDataType);

    ui->m_btnOk->setFont(*g_pSttGlobalFont);
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);
    ui->m_labSettingTime->setFont(*g_pSttGlobalFont);
    ui->m_labFaultCur->setFont(*g_pSttGlobalFont);
    ui->m_labFaultAngle->setFont(*g_pSttGlobalFont);
    ui->m_labErrType->setFont(*g_pSttGlobalFont);
    ui->m_labRelErr->setFont(*g_pSttGlobalFont);
    ui->m_labAbsErrNeg->setFont(*g_pSttGlobalFont);
    ui->m_labAbsErrPos->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setFont(*g_pSttGlobalFont);

    ui->m_editAbsErrNeg->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAbsErrPos->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultAngle->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultCurrent->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editSettingTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbErrType->setFixedWidth(m_nInputWidgetWidth);

    ui->m_gbFault->setTitle(g_sLangTxt_Gradient_Failure);
    ui->m_gbResultEval->setTitle(g_sLangTxt_StateEstimate_ResultEstimate);
    ui->m_labSettingTime->setText(g_sLangTxt_Manual_ActionTime);
    ui->m_labFaultCur->setText(g_sLangTxt_Swing_SCurrent);
    ui->m_labFaultAngle->setText(g_sLangTxt_ActionTime_FaultAngle);
    ui->m_labErrType->setText(g_sLangTxt_ActionTime_ErrType);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);
    ui->m_labAbsErrPos->setText(g_sLangTxt_ActionTime_AbsErrPos);
    ui->m_labAbsErrNeg->setText(g_sLangTxt_ActionTime_AbsErrNeg);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

	return;
}

void QActionTimeAddMultDlg::SetValueToPage(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LN_CHECK)
    {
        m_cbLN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LL_CHECK)
    {
        m_cbLL->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASE_CHECK)
    {
        m_cbThreePhase->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURR_CHECK)
    {
        m_cbI0->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURR_CHECK)
    {
        m_cbI2->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPARALLEL_CHECK)
    {
        m_cbThreeParallel->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOL)
    {
        m_editLNVol->setText(ActTimeValueCheck(pData->m_strValue,FAULTVOL_MAX, FAULTVOL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOLTYPE_RADIO)
    {
        m_rbLNFaultVolShort->setChecked(pData->m_strValue == "0");
        m_rbLNFaultVolZero->setChecked(pData->m_strValue == "3");   //零序电压是3
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOL)
    {
        m_editLLVol->setText(ActTimeValueCheck(pData->m_strValue,FAULTVOL_MAX, FAULTVOL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOLTYPE_RADIO)
    {
        m_rbLLFaultVolShort->setChecked(pData->m_strValue == "0");
        m_rbLLFaultVolNeg->setChecked(pData->m_strValue == "2");    //负序电压是2
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEAN_CHECK)
    {
        m_cbLNAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEBN_CHECK)
    {
        m_cbLNBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPECN_CHECK)
    {
        m_cbLNCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEAB_CHECK)
    {
        m_cbLLAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEBC_CHECK)
    {
        m_cbLLBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPECA_CHECK)
    {
        m_cbLLCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASEFAULTVOL)
    {
        m_editThreePhaseVol->setText(ActTimeValueCheck(pData->m_strValue,FAULTVOL_MAX, FAULTVOL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURRFAULTVOL)
    {
        m_editI0Vol->setText(ActTimeValueCheck(pData->m_strValue,FAULTVOL_MAX, FAULTVOL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURRFAULTVOL)
    {
        m_editI2Vol->setText(ActTimeValueCheck(pData->m_strValue,FAULTVOL_MAX, FAULTVOL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_SETTINGTIME)
    {
        //ui->m_editSettingTime->setText(ActTimeValueCheck(pData->m_strValue,SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
        ui->m_editSettingTime->UpdateObjectText(pData,ActTimeValueCheck(pData->m_strValue,SETTINGTIME_MAX, SETTINGTIME_MIN, 3), 3);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTCURRENT)
    {
        ui->m_editFaultCurrent->setText(ActTimeValueCheck(pData->m_strValue,FAULTCUR_MAX, FAULTCUR_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTANGLE)
    {
        ui->m_editFaultAngle->setText(ActTimeValueCheck(pData->m_strValue,FAULTANGLE_MAX, FAULTANGLE_MIN, 2));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ERRORLOGIC)
    {
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_DATATYPE_ID_ERRORTYPE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_cbbErrType->SetCurrSelByName(pValue->m_strName);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_RELERR)
    {
        ui->m_editRelErr->setText(ActTimeValueCheck(pData->m_strValue, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_POS)
    {
        ui->m_editAbsErrPos->setText(ActTimeValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_NEG)
    {
        ui->m_editAbsErrNeg->setText(ActTimeValueCheck(pData->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    }

    return;
}

void QActionTimeAddMultDlg::SetDatas(CDataGroup *pParas)
{
    if(pParas == NULL)
        return;

    m_pCurrDataGroup = pParas;
    POS pos = pParas->GetHeadPosition();
    while(pos != NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        SetValueToPage(pData);
    }

    if(m_cbLN->isChecked())
    {
        this->m_editLNVol->setEnabled(true);
        this->m_rbLNFaultVolShort->setEnabled(true);
        this->m_rbLNFaultVolZero->setEnabled(true);
        this->m_cbLNAN->setEnabled(true);
        this->m_cbLNBN->setEnabled(true);
        this->m_cbLNCN->setEnabled(true);
    }
    else
    {
        this->m_editLNVol->setEnabled(false);
        this->m_rbLNFaultVolShort->setEnabled(false);
        this->m_rbLNFaultVolZero->setEnabled(false);
        this->m_cbLNAN->setEnabled(false);
        this->m_cbLNBN->setEnabled(false);
        this->m_cbLNCN->setEnabled(false);
    }

    if(m_cbLL->isChecked())
    {
        this->m_editLLVol->setEnabled(true);
        this->m_rbLLFaultVolShort->setEnabled(true);
        this->m_rbLLFaultVolNeg->setEnabled(true);
        this->m_cbLLAB->setEnabled(true);
        this->m_cbLLBC->setEnabled(true);
        this->m_cbLLCA->setEnabled(true);
    }
    else
    {
        this->m_editLLVol->setEnabled(false);
        this->m_rbLLFaultVolShort->setEnabled(false);
        this->m_rbLLFaultVolNeg->setEnabled(false);
        this->m_cbLLAB->setEnabled(false);
        this->m_cbLLBC->setEnabled(false);
        this->m_cbLLCA->setEnabled(false);
    }

    if(m_cbThreePhase->isChecked())
    {
        this->m_editThreePhaseVol->setEnabled(true);
    }
    else
    {
        this->m_editThreePhaseVol->setEnabled(false);
    }


    if(m_cbI0->isChecked())
    {
        this->m_editI0Vol->setEnabled(true);
    }
    else
    {
        this->m_editI0Vol->setEnabled(false);
    }

    if(m_cbI2->isChecked())
    {
        this->m_editI2Vol->setEnabled(true);
    }
    else
    {
        this->m_editI2Vol->setEnabled(false);
    }

	return;
}

void QActionTimeAddMultDlg::CheckAllPresence()
{
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LN_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LL_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASE_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURR_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURR_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPARALLEL_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOL);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOLTYPE_RADIO);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOL);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOLTYPE_RADIO);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEAN_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEBN_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPECN_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEAB_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEBC_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPECA_CHECK);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASEFAULTVOL);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURRFAULTVOL);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURRFAULTVOL);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_SETTINGTIME);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTCURRENT);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTANGLE);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ERRORLOGIC);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_RELERR);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_POS);
    ActTimeCheckParaExist(m_pCurrDataGroup,STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_NEG);

    return;
}

void QActionTimeAddMultDlg::GetPageToValue(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LN_CHECK)
    {
        pData->m_strValue.setNum(m_cbLN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LL_CHECK)
    {
        pData->m_strValue.setNum(m_cbLL->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASE_CHECK)
    {
        pData->m_strValue.setNum(m_cbThreePhase->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURR_CHECK)
    {
        pData->m_strValue.setNum(m_cbI0->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURR_CHECK)
    {
        pData->m_strValue.setNum(m_cbI2->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPARALLEL_CHECK)
    {
        pData->m_strValue.setNum(m_cbThreeParallel->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOL)
    {
        pData->m_strValue = m_editLNVol->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTVOLTYPE_RADIO)
    {
        if(m_rbLNFaultVolZero->isChecked())
            pData->m_strValue = "3";    //零序电压是3
        else
            pData->m_strValue = "0";
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOL)
    {
        pData->m_strValue = m_editLLVol->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTVOLTYPE_RADIO)
    {
        if(m_rbLLFaultVolNeg->isChecked())
            pData->m_strValue = "2";    //负序电压是2
        else
            pData->m_strValue = "0";
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEAN_CHECK)
    {
        pData->m_strValue.setNum(m_cbLNAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPEBN_CHECK)
    {
        pData->m_strValue.setNum(m_cbLNBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LNFAULTTYPECN_CHECK)
    {
        pData->m_strValue.setNum(m_cbLNCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEAB_CHECK)
    {
        pData->m_strValue.setNum(m_cbLLAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPEBC_CHECK)
    {
        pData->m_strValue.setNum(m_cbLLBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_LLFAULTTYPECA_CHECK)
    {
        pData->m_strValue.setNum(m_cbLLCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_THREEPHASEFAULTVOL)
    {
        pData->m_strValue = m_editThreePhaseVol->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ZEROCURRFAULTVOL)
    {
        pData->m_strValue = m_editI0Vol->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_NEGCURRFAULTVOL)
    {
        pData->m_strValue = m_editI2Vol->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_SETTINGTIME)
    {
        // pData->m_strValue = ui->m_editSettingTime->text();
         pData->m_strValue = ui->m_editSettingTime->GetText();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTCURRENT)
    {
         pData->m_strValue = ui->m_editFaultCurrent->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTANGLE)
    {
         pData->m_strValue = ui->m_editFaultAngle->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ERRORLOGIC)
    {       
         CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbErrType->GetCurrSelObject();
         if(pValue != NULL)
             pData->m_strValue = pValue->m_strIndex;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_RELERR)
    {
         pData->m_strValue = ui->m_editRelErr->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_POS)
    {
         pData->m_strValue = ui->m_editAbsErrPos->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_TTRIP_ABSERR_NEG)
    {
         pData->m_strValue = ui->m_editAbsErrNeg->text();
    }
}

void QActionTimeAddMultDlg::GetDatas(CDataGroup *pParas)
{  
    if(pParas == NULL)
        return;

    m_pCurrDataGroup = pParas;
    CheckAllPresence();

    POS pos = pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        GetPageToValue(pData);
    }

	return;	
}

void QActionTimeAddMultDlg::on_LN_Check_StateChanged(int state)
{
	if(state == Qt::Checked)
	{
        this->m_editLNVol->setEnabled(true);
		this->m_rbLNFaultVolShort->setEnabled(true);
		this->m_rbLNFaultVolZero->setEnabled(true);
        this->m_cbLNAN->setEnabled(true);
        this->m_cbLNBN->setEnabled(true);
        this->m_cbLNCN->setEnabled(true);
	}
	else
	{
        this->m_editLNVol->setEnabled(false);
		this->m_rbLNFaultVolShort->setEnabled(false);
		this->m_rbLNFaultVolZero->setEnabled(false);
        this->m_cbLNAN->setEnabled(false);
        this->m_cbLNBN->setEnabled(false);
        this->m_cbLNCN->setEnabled(false);
	}
}

void QActionTimeAddMultDlg::on_LL_Check_StateChanged(int state)
{
	if(state == Qt::Checked)
	{
        this->m_editLLVol->setEnabled(true);
		this->m_rbLLFaultVolShort->setEnabled(true);
        this->m_rbLLFaultVolNeg->setEnabled(true);
        this->m_cbLLAB->setEnabled(true);
        this->m_cbLLBC->setEnabled(true);
        this->m_cbLLCA->setEnabled(true);
	}
	else
	{
        this->m_editLLVol->setEnabled(false);
		this->m_rbLLFaultVolShort->setEnabled(false);
        this->m_rbLLFaultVolNeg->setEnabled(false);
        this->m_cbLLAB->setEnabled(false);
        this->m_cbLLBC->setEnabled(false);
        this->m_cbLLCA->setEnabled(false);
	}
}

void QActionTimeAddMultDlg::on_ThreePhase_Check_StateChanged(int state)
{
    if(state == Qt::Checked)
    {
        this->m_editThreePhaseVol->setEnabled(true);
    }
    else
    {
        this->m_editThreePhaseVol->setEnabled(false);
    }

    return;
}

void QActionTimeAddMultDlg::on_I0_Check_StateChanged(int state)
{
    if(state == Qt::Checked)
    {
        this->m_editI0Vol->setEnabled(true);
    }
    else
    {
        this->m_editI0Vol->setEnabled(false);
    }

    return;
}

void QActionTimeAddMultDlg::on_I2_Check_StateChanged(int state)
{
    if(state == Qt::Checked)
    {
        this->m_editI2Vol->setEnabled(true);
    }
    else
    {
        this->m_editI2Vol->setEnabled(false);
    }

    return;
}

void QActionTimeAddMultDlg::on_TestCheck_StateChanged()
{
	if(this->m_cbLN->isChecked() ||
		this->m_cbLL->isChecked() ||
		this->m_cbThreePhase->isChecked() ||
		this->m_cbI0->isChecked() ||
		this->m_cbI2->isChecked() ||
		this->m_cbThreeParallel->isChecked())
	{
		return;
	}
	this->m_cbLN->setChecked(true);
	CString strTitle = "添加系列";
	CString strInfo = "请至少勾选一个测试项！";
	QMessageBox::information(this, strTitle, strInfo);  
}


void QActionTimeAddMultDlg::on_m_editSettingTime_editingFinished()
{
    if(ui->m_editSettingTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_editSettingTime)->IsSetting())
        {
            return;
        }
    }

    ui->m_editSettingTime->setText(ActTimeValueCheck(ui->m_editSettingTime->text(),SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
	return;
}

void QActionTimeAddMultDlg::on_m_editFaultCurrent_editingFinished()
{
    ui->m_editFaultCurrent->setText(ActTimeValueCheck(ui->m_editFaultCurrent->text(),FAULTCUR_MAX, FAULTCUR_MIN, 3));
	return;  
}

void QActionTimeAddMultDlg::on_m_editFaultAngle_editingFinished()
{
    ui->m_editFaultAngle->setText(ActTimeValueCheck(ui->m_editFaultAngle->text(),FAULTANGLE_MAX, FAULTANGLE_MIN, 2));
	return;  
}

void QActionTimeAddMultDlg::on_m_editLNVol_editingFinished()
{
    m_editLNVol->setText(ActTimeValueCheck(m_editLNVol->text(),FAULTVOL_MAX, FAULTVOL_MIN, 3));
	return;
}

void QActionTimeAddMultDlg::on_m_editLLVol_editingFinished()
{
    m_editLLVol->setText(ActTimeValueCheck(m_editLLVol->text(),FAULTVOL_MAX, FAULTVOL_MIN, 3));
	return;
}

void QActionTimeAddMultDlg::on_m_editThreePhaseVol_editingFinished()
{
    m_editThreePhaseVol->setText(ActTimeValueCheck(m_editThreePhaseVol->text(),FAULTVOL_MAX, FAULTVOL_MIN, 3));
}

void QActionTimeAddMultDlg::on_m_editI0Vol_editingFinished()
{
    m_editI0Vol->setText(ActTimeValueCheck(m_editI0Vol->text(),FAULTVOL_MAX, FAULTVOL_MIN, 3));
}

void QActionTimeAddMultDlg::on_m_editI2Vol_editingFinished()
{
    m_editI2Vol->setText(ActTimeValueCheck(m_editI2Vol->text(),FAULTVOL_MAX, FAULTVOL_MIN, 3));
}

void QActionTimeAddMultDlg::on_m_editRelErr_editingFinished()
{
    ui->m_editRelErr->setText(ActTimeValueCheck(ui->m_editRelErr->text(), TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
}

void QActionTimeAddMultDlg::on_m_editAbsErrPos_editingFinished()
{
    ui->m_editAbsErrPos->setText(ActTimeValueCheck(ui->m_editAbsErrPos->text(), TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
}

void QActionTimeAddMultDlg::on_m_editAbsErrNeg_editingFinished()
{
    ui->m_editAbsErrNeg->setText(ActTimeValueCheck(ui->m_editAbsErrNeg->text(), TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
}

//确认
void QActionTimeAddMultDlg::on_m_btnOk_clicked()
{
	GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
	this->done(Accepted);
}

//取消
void QActionTimeAddMultDlg::on_m_btnCancel_clicked()
{
	this->close();
}

