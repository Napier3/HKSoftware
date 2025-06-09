#include "QDeviceModelAttrWidget_Eng.h"
#include "ui_QDeviceModelAttrWidget_Eng.h"

QDeviceModelAttrWidget_Eng::QDeviceModelAttrWidget_Eng(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDeviceModelAttrWidget_Eng)
{
    ui->setupUi(this);
    m_pAttrWidgetDeviceAttrs = NULL;
    ui->groupBox->setGeometry(18,3,400,330);
    ui->groupBox_2->setGeometry(18,340,400,115);
    ui->groupBox_3->setGeometry(18,465,400,115);
    ui->groupBox_4->setGeometry(437,3,490,280);
    ui->groupBox_5->setGeometry(437,295,490,280);
    ui->groupBox_6->setGeometry(947,3,300,80);
    ui->groupBox_7->setGeometry(947,95,300,130);
    ui->groupBox_8->setGeometry(947,230,300,130);
    ui->groupBox_9->setGeometry(947,365,300,130);
}

QDeviceModelAttrWidget_Eng::~QDeviceModelAttrWidget_Eng()
{
    if(m_pAttrWidgetDeviceAttrs != NULL)
    {
        delete m_pAttrWidgetDeviceAttrs;
        m_pAttrWidgetDeviceAttrs = NULL;
    }
    delete ui;
}

BOOL QDeviceModelAttrWidget_Eng::CreateQDeviceModelAttrWidget_Eng(CDvmDataset *pDeviceAttrs)
{
    InitObjectValue(pDeviceAttrs);
    InitDeviceModelAttrWidget();
    InitConnnect();
    return TRUE;
}

void QDeviceModelAttrWidget_Eng::InitObjectValue(CDvmDataset *pDeviceAttrs)
{
    CDvmDataset *pDataset = NULL;
    pDataset = pDeviceAttrs;
//    //DEVICE_NAMEPLATE
    UpdateObjectValue(m_strValueDeviceModel,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_MODEL,pDataset);
    UpdateObjectValue(m_strValueManufacturer,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_MANUFACTURER,pDataset);
    UpdateObjectValue(m_strValueDeviceType,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_TYPE,pDataset);
    UpdateObjectValue(m_strValueSerialnr,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_SERIALNR,pDataset);
    UpdateObjectValue(m_strValueAdditionalINF02,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2,pDataset);
//    //DEVICE_LOCATION
    UpdateObjectValue(m_strValueDeviceAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS,pDataset);
    UpdateObjectValue(m_strValueSubstation,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION,pDataset);
    UpdateObjectValue(m_strValueSubstatioAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS,pDataset);
    UpdateObjectValue(m_strValueBay,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY,pDataset);
    UpdateObjectValue(m_strValueBayAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY_ADDRESS,pDataset);
    UpdateObjectValue(m_strValueProtectedObjectName,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME,pDataset);
//    //DEVICE_NOMINALVALUES
    UpdateObjectValue(m_strValuePhases,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_PHASES,pDataset);
    UpdateObjectValue(m_strValueFNom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_FNOM,pDataset);
    UpdateObjectValue(m_strValueVNom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VNOM,pDataset);
    UpdateObjectValue(m_strValueVPrimLL,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VPRIM_LL,pDataset);
    UpdateObjectValue(m_strValueINom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_INOM,pDataset);
    UpdateObjectValue(m_strValueIprim,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_IPRIM,pDataset);
//    //DEVICE_RESIDUALFACTORS
    UpdateObjectValue(m_strValueVLNVN,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS,XRIO_DEVICE_MODEL_ID_VLNVN,pDataset);
    UpdateObjectValue(m_strValueININOM,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS,XRIO_DEVICE_MODEL_ID_ININOM,pDataset);
//    //DEVICE_LIMITS
    UpdateObjectValue(m_strValueVMAX_LL,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_VMAX_LL,pDataset);
    UpdateObjectValue(m_strValueIMAX,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_IMAX,pDataset);
//    //DEVICE_MISC
    UpdateObjectValue(m_strValueDEBOUNCETIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME,pDataset);
    UpdateObjectValue(m_strValueDEGLITCHTIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME,pDataset);
    UpdateObjectValue(m_strValueOVERLOADSUPTIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME,pDataset);


////    //DEVICE_NAMEPLATE
//    UpdateObjectDataOrValue(m_strValueDeviceModel,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_MODEL,RIO_DEVICE_MODEL_ID_NAME,pDataset);
//    UpdateObjectDataOrValue(m_strValueManufacturer,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_MANUFACTURER,XRIO_DEVICE_MODEL_ID_MANUFACTURER,pDataset);
//    UpdateObjectDataOrValue(m_strValueDeviceType,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_TYPE,RIO_DEVICE_MODEL_ID_DEVICE_TYPE,pDataset);
//    UpdateObjectDataOrValue(m_strValueSerialnr,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_SERIALNR,RIO_DEVICE_MODEL_ID_SERIALNO,pDataset);
//    UpdateObjectValue(m_strValueAdditionalINF02,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2,pDataset);
//    //    //DEVICE_LOCATION
//    UpdateObjectDataOrValue(m_strValueDeviceAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS,RIO_DEVICE_MODEL_ID_DEVICE_ADDRESS,pDataset);
//    UpdateObjectDataOrValue(m_strValueSubstation,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION,XRIO_DEVICE_MODEL_ID_SUBSTATION,pDataset);
//    UpdateObjectDataOrValue(m_strValueSubstatioAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS,RIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS,pDataset);
//    UpdateObjectDataOrValue(m_strValueBay,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY,XRIO_DEVICE_MODEL_ID_BAY,pDataset);
//    UpdateObjectDataOrValue(m_strValueBayAddress,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY_ADDRESS,RIO_DEVICE_MODEL_ID_BAY_ADDRESS,pDataset);
//    UpdateObjectDataOrValue(m_strValueProtectedObjectName,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME,RIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME,pDataset);
//    //    //DEVICE_NOMINALVALUES
//    UpdateObjectDataOrValue(m_strValuePhases,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_PHASES,XRIO_DEVICE_MODEL_ID_PHASES,pDataset);
//    UpdateObjectDataOrValue(m_strValueFNom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_FNOM,XRIO_DEVICE_MODEL_ID_FNOM,pDataset);
//    UpdateObjectDataOrValue(m_strValueVNom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VNOM,XRIO_DEVICE_MODEL_ID_VNOM,pDataset);
//    UpdateObjectDataOrValue(m_strValueVPrimLL,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VPRIM_LL,RIO_DEVICE_MODEL_ID_VPRIM_LL,pDataset);
//    UpdateObjectDataOrValue(m_strValueINom,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_INOM,XRIO_DEVICE_MODEL_ID_INOM,pDataset);
//    UpdateObjectDataOrValue(m_strValueIprim,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_IPRIM,XRIO_DEVICE_MODEL_ID_IPRIM,pDataset);
//    //    //DEVICE_RESIDUALFACTORS
//    UpdateObjectDataOrValue(m_strValueVLNVN,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS,XRIO_DEVICE_MODEL_ID_VLNVN,XRIO_DEVICE_MODEL_ID_VLNVN,pDataset);
//    UpdateObjectDataOrValue(m_strValueININOM,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS,XRIO_DEVICE_MODEL_ID_ININOM,XRIO_DEVICE_MODEL_ID_ININOM,pDataset);
//    //    //DEVICE_LIMITS
//    UpdateObjectDataOrValue(m_strValueVMAX_LL,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_VMAX_LL,RIO_DEVICE_MODEL_ID_VMAX_LL,pDataset);
//    UpdateObjectDataOrValue(m_strValueIMAX,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_IMAX,XRIO_DEVICE_MODEL_ID_IMAX,pDataset);
//    //    //DEVICE_MISC
//    UpdateObjectDataOrValue(m_strValueDEBOUNCETIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME,pDataset);
//    UpdateObjectDataOrValue(m_strValueDEGLITCHTIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME,pDataset);
//    UpdateObjectValue(m_strValueOVERLOADSUPTIME,XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME,pDataset);

    if(m_strValueININOM.isEmpty())//默认电流比例为1
    {
        m_strValueININOM = _T("1");
    }
    if(m_strValueVLNVN.isEmpty())//默认电压比例为1.7321
    {
        m_strValueVLNVN = _T("1.7321");
    }
}

void QDeviceModelAttrWidget_Eng::InitConnnect()
{
    connect(this,SIGNAL(sig_m_editDeviceMode_editingFinished_Widget(QString)),this,SLOT(slot_m_editDeviceMode_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editManufacturer_editingFinished_Widget(QString)),this,SLOT(slot_m_editManufacturer_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editDeviceType_editingFinished_Widget(QString)),this,SLOT(slot_m_editDeviceType_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editDeviceAddress_editingFinished_Widget(QString)),this,SLOT(slot_m_editDeviceAddress_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editSerialnr_editingFinished_Widget(QString)),this,SLOT(slot_m_editSerialnr_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editProtectedObjectName_editingFinished_Widget(QString)),this,SLOT(slot_m_editProtectedObjectName_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editAdditionalINF02_editingFinished_Widget(QString)),this,SLOT(slot_m_editAdditionalINF02_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editSubstation_editingFinished_Widget(QString)),this,SLOT(slot_m_editSubstation_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editSubstatioAddress_editingFinished_Widget(QString)),this,SLOT(slot_m_editSubstatioAddress_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editFNom_editingFinished_Widget(QString)),this,SLOT(slot_m_editFNom_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editBay_editingFinished_Widget(QString)),this,SLOT(slot_m_editBay_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editBayAddress_editingFinished_Widget(QString)),this,SLOT(slot_m_editBayAddress_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVPrimLL_editingFinished_Widget(QString)),this,SLOT(slot_m_editVPrimLL_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVPrimLL2_editingFinished_Widget(QString)),this,SLOT(slot_m_editVPrimLL2_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVPrimLL3_editingFinished_Widget(QString)),this,SLOT(slot_m_editVPrimLL3_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVNom_editingFinished_Widget(QString)),this,SLOT(slot_m_editVNom_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVNom2_editingFinished_Widget(QString)),this,SLOT(slot_m_editVNom2_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVNom3_editingFinished_Widget(QString)),this,SLOT(slot_m_editVNom3_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editIPRIM_editingFinished_Widget(QString)),this,SLOT(slot_m_editIPRIM_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editIPRIM2_editingFinished_Widget(QString)),this,SLOT(slot_m_editIPRIM2_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editINom_editingFinished_Widget(QString)),this,SLOT(slot_m_editINom_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editINom2_editingFinished_Widget(QString)),this,SLOT(slot_m_editINom2_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editVMaxLL_editingFinished_Widget(QString)),this,SLOT(slot_m_editVMaxLL_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editIMax_editingFinished_Widget(QString)),this,SLOT(slot_m_editIMax_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editOverloadSupTime_editingFinished_Widget(QString)),this,SLOT(slot_m_editOverloadSupTime_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editDeBounceTime_editingFinished_Widget(QString)),this,SLOT(slot_m_editDeBounceTime_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_editDeGlitchTime_editingFinished_Widget(QString)),this,SLOT(slot_m_editDeGlitchTime_editingFinished(QString)));
    connect(this,SIGNAL(sig_m_radPhases2_clicked_Widget()),this,SLOT(slot_m_radPhases2_clicked()));
    connect(this,SIGNAL(sig_m_radPhases3_clicked_Widget()),this,SLOT(slot_m_radPhases3_clicked()));

    connect(ui->m_radCustomize, SIGNAL(clicked(bool)), this, SLOT(on_m_radCustomize_clicked()));
    connect(ui->m_radHigh, SIGNAL(clicked(bool)), this, SLOT(on_m_radHigh_clicked()));
    connect(ui->m_radLow, SIGNAL(clicked(bool)), this, SLOT(on_m_radLow_clicked()));
    connect(ui->m_radDisconnect, SIGNAL(clicked(bool)), this, SLOT(on_m_radDisconnect_clicked()));
}

void QDeviceModelAttrWidget_Eng::InitDeviceModelAttrWidget()
{
//    CString strTemp = _T("：");
    ui->tabWidget->setTabText(0,g_sLangTxt_Xrio_DeviceSetting);

    ui->groupBox->setTitle(g_sLangTxt_Device);
    ui->label->setText(g_sLangTxt_Xrio_DeviceAttr_Name_Description);
    ui->label_4->setText(g_sLangTxt_Xrio_DeviceAttr_Manufacturer);
    ui->label_5->setText(g_sLangTxt_Xrio_DeviceAttr_DeviceType);
    ui->label_6->setText(g_sLangTxt_Report_DeviceAddr);
    ui->label_7->setText(g_sLangTxt_Xrio_DeviceAttr_SerialNumber);
    ui->label_8->setText(g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationOne);
    ui->label_9->setText(g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationTwo);

    ui->groupBox_2->setTitle(g_sLangTxt_Xrio_DeviceAttr_TransformerSubstation);
    ui->label_10->setText(g_sLangTxt_Name);
    ui->label_11->setText(g_sLtxt_Address);

    ui->groupBox_3->setTitle(g_sLangTxt_Internal);
    ui->label_12->setText(g_sLangTxt_Name);
    ui->label_13->setText(g_sLtxt_Address);

    ui->groupBox_4->setTitle(g_sLangTxt_State_SettingValue);
    ui->label_14->setText(g_sLangTxt_Xrio_DeviceAttr_NumberOfPhases);
    ui->label_2->setText(g_sLangTxt_Report_Fnom);
    ui->label_16->setText(g_sLangTxt_IEC_OnceValue);
    ui->label_17->setText(g_sLangTxt_IEC_TwiceValue);
    ui->label_15->setText(g_sLangTxt_Report_Vnom);
    ui->label_18->setText(g_sLangTxt_Native_EDCurrent);

    ui->groupBox_5->setTitle(g_sLangTxt_Xrio_DeviceAttr_ZSVAndZSC);
    ui->label_19->setText(g_sLangTxt_Xrio_DeviceAttr_ZSVDirection);
    ui->label_20->setText(g_sLangTxt_Xrio_DeviceAttr_ZSCDirection);
    ui->checkBox->setText(g_sLangTxt_Xrio_DeviceAttr_UseOfMutualInductor);
    ui->label_22->setText(g_sLangTxt_IEC_OnceValue);
    ui->label_23->setText(g_sLangTxt_IEC_TwiceValue);
    ui->label_21->setText(g_sLangTxt_Report_Vnom);
    ui->label_24->setText(g_sLangTxt_Native_EDCurrent);

    ui->groupBox_6->setTitle(g_sLangTxt_Xrio_DeviceAttr_OtherDeviceProperties);
    ui->label_3->setText(g_sLangTxt_Native_ReturnTime);

    ui->groupBox_7->setTitle(g_sLangTxt_Xrio_DeviceAttr_MaxValueSetting);

    ui->groupBox_8->setTitle(g_sLangTxt_Xrio_DeviceAttr_OvDetSens);
    ui->m_radHigh->setText(g_sLangTxt_Diff_High);
    ui->m_radCustomize->setText(g_sLangTxt_Custom);
    ui->m_radLow->setText(g_sLangTxt_Diff_Low);
    ui->m_radDisconnect->setText(g_sLangTxt_SOE_Break);

    ui->groupBox_9->setTitle(g_sLangTxt_Xrio_DeviceAttr_Damping);
    ui->label_27->setText(g_sLangTxt_Xrio_DeviceAttr_BroadeningTime);
    ui->label_28->setText(g_sLangTxt_Report_AntiShakeTime);

    ui->m_btnOK->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    ui->m_editDeviceMode->setText(m_strValueDeviceModel);
    ui->m_editManufacturer->setText(m_strValueManufacturer);
    ui->m_editDeviceType->setText(m_strValueDeviceType);
    ui->m_editDeviceAddress->setText(m_strValueDeviceAddress);
    ui->m_editSerialnr->setText(m_strValueSerialnr);
    ui->m_editProtectedObjectName->setText(m_strValueProtectedObjectName);
    ui->m_editAdditionalINF02->setText(m_strValueAdditionalINF02);
    ui->m_editSubstation->setText(m_strValueSubstation);
    ui->m_editSubstatioAddress->setText(m_strValueSubstatioAddress);
    ui->m_editBay->setText(m_strValueBay);
    ui->m_editBayAddress->setText(m_strValueBayAddress);

    ui->m_editFNom->setText(QString::number(m_strValueFNom.toDouble(),'f',3) + " " + "Hz");
    m_strValueFNomlastValidInput = QString::number(m_strValueFNom.toDouble(),'f',3) + " " + "Hz";


    ui->m_editVNom->setText(QString::number(m_strValueVNom.toDouble(),'f',3) + " " + "V(L-L)");
    m_strValueVNomlastValidInput = QString::number(m_strValueVNom.toDouble(),'f',3) + " " + "V(L-L)";

    ui->m_editVNom2->setText((QString::number(((m_strValueVNom.toDouble())/1.73205),'f',3)) + "  " + "V(L-N)");
    m_strValueVNomlastValidInput2 = (QString::number(((m_strValueVNom.toDouble())/1.73205),'f',3)) + " " + "V(L-N)";

    ui->m_editVNom3->setText((QString::number(((m_strValueVNom.toDouble())/1.73205/(m_strValueVLNVN.toDouble())),'f',3)) + "  " + "V");
    m_strValueVNomlastValidInput3 = (QString::number(((m_strValueVNom.toDouble())/1.73205/(m_strValueVLNVN.toDouble())),'f',3)) + " " + "V";

    ui->m_editVPrimLL->setText(QString::number(m_strValueVPrimLL.toDouble(),'f',3) + " " + "V(L-L)");
    m_strValueVPrimLLlastValidInput = QString::number(m_strValueVPrimLL.toDouble(),'f',3) + " " + "V(L-L)";

    ui->m_editVPrimLL2->setText((QString::number(((m_strValueVPrimLL.toDouble())/1.73205),'f',3)) + "  " + "V(L-N)");
    m_strValueVPrimLLlastValidInput2 = (QString::number(((m_strValueVPrimLL.toDouble())/1.73205),'f',3)) + " " + "V(L-N)";

    ui->m_editVPrimLL3->setText((QString::number(((m_strValueVPrimLL.toDouble())/1.73205),'f',3))+ "  " + "V");
    m_strValueVPrimLLlastValidInput3 = (QString::number(((m_strValueVPrimLL.toDouble())/1.73205),'f',3))+ " " + "V";

    ui->m_editINom->setText(QString::number(m_strValueINom.toDouble(),'f',3) + " " + "A");
    m_strValueINomlastValidInput = QString::number(m_strValueINom.toDouble(),'f',3) + " " + "A";

    ui->m_editINom2->setText((QString::number(((m_strValueINom.toDouble())/(m_strValueININOM.toDouble())),'f',3)) + "  " + "A");
    m_strValueINomlastValidInput2 = (QString::number(((m_strValueINom.toDouble())/(m_strValueININOM.toDouble())),'f',3)) + " " + "A";

    ui->m_editIPRIM->setText(QString::number(m_strValueIprim.toDouble(),'f',3) + " " + "A");
    m_strValueIPRIMlastValidInput = QString::number(m_strValueIprim.toDouble(),'f',3) + " " + "A";

    ui->m_editIPRIM2->setText(QString::number(m_strValueIprim.toDouble(),'f',3) + " " + "A");
    m_strValueIPRIMlastValidInput2 = QString::number(m_strValueIprim.toDouble(),'f',3) + " " + "A";


    ui->m_editVMaxLL->setText(QString::number(m_strValueVMAX_LL.toDouble(),'f',3) + " " + "V(L-L)");
    m_strValueVMAXLLValidInput = QString::number(m_strValueVMAX_LL.toDouble(),'f',3) + " " + "V(L-L)";

    ui->m_editIMax->setText(QString::number(m_strValueIMAX.toDouble(),'f',3) + " " + "A");
    m_strValueIMAXValidInput = QString::number(m_strValueIMAX.toDouble(),'f',3) + " " + "A";

    ui->m_editDeBounceTime->setText(QString::number(m_strValueDEBOUNCETIME.toDouble(),'f',3) + " " + "s");
    m_strValueDeBounceTimeValidInput = QString::number(m_strValueDEBOUNCETIME.toDouble(),'f',3) + " " + "s";

    ui->m_editDeGlitchTime->setText(QString::number(m_strValueDEGLITCHTIME.toDouble(),'f',3) + " " + "s");
    m_strValueDeGlitchTimeValidInput = QString::number(m_strValueDEGLITCHTIME.toDouble(),'f',3) + " " + "s";

    ui->m_editOverloadSupTime->setText(QString::number(m_strValueOVERLOADSUPTIME.toDouble(),'f',3) + " " + "s");
    m_strValueOVERLOADSUPTIMEValidInput = QString::number(m_strValueOVERLOADSUPTIME.toDouble(),'f',3) + " " + "s";
    ui->m_editOverloadSupTime->setEnabled(false);

    ui->m_editBackTime->setText("0.020 s");
    m_strValueBackTimeValidInput = _T("0.020 s");

    ui->checkBox->setChecked(true);

    if(m_strValuePhases.toInt() == 2)
    {
        ui->m_radPhases2->click();
    }
    else if(m_strValuePhases.toInt() == 3)
    {
        ui->m_radPhases3->click();
    }

    if(DOUBLE_EQUAL == DoubleFuzzyCompare(m_strValueOVERLOADSUPTIME.toDouble(),0.05))
    {
        ui->m_radHigh->click();
    }
    else if(DOUBLE_EQUAL == DoubleFuzzyCompare(m_strValueOVERLOADSUPTIME.toDouble(),0.2))
    {
        ui->m_radLow->click();
    }
    else if(DOUBLE_EQUAL == DoubleFuzzyCompare(m_strValueOVERLOADSUPTIME.toDouble(),0.0))
    {
        ui->m_radDisconnect->click();
    }
    else if(m_strValueOVERLOADSUPTIME.isEmpty())//默认为灵敏度为高
    {
        ui->m_radHigh->click();
    }
}

BOOL QDeviceModelAttrWidget_Eng::UpdateObjectValue(CString &strObject, const CString &strParentID, const CString &strObjectID,CDvmDataset *pDataset)
{
    CString strTempIDPath = GetObjectIDPath(strParentID,strObjectID);
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = pDataset->FindDataObjValueByID_Has(strTempIDPath);
    if(TargetValueObject)
    {
        strObject = TargetValueObject->m_strValue;
        return TRUE;
    }
    return FALSE;
}

BOOL QDeviceModelAttrWidget_Eng::UpdateObjectDataOrValue(CString &strObject, const CString &strXrioParentID, const CString &strXrioObjectID, const CString &strRioParentID, CDvmDataset *pDataset)
{
    CString strTempIDPath = GetObjectIDPath(strXrioParentID,strXrioObjectID);
    CDvmValue* XrioTargetValueObject = NULL;
    CDvmData* RioTargetValueObject = NULL;
    XrioTargetValueObject = pDataset->FindDataObjValueByID_Has(strTempIDPath);
    RioTargetValueObject = pDataset->FindDataObjByID_Has(strRioParentID);
    if(XrioTargetValueObject)
    {
        //xrio
        strObject = XrioTargetValueObject->m_strValue;
        return TRUE;
    }
    else if(RioTargetValueObject)
    {
        //rio
        strObject = RioTargetValueObject->m_strValue;
        return TRUE;
    }
    return FALSE;
}

CDvmValue *QDeviceModelAttrWidget_Eng::FindValueObject(const CString &strParentID, const CString &strObjectID)
{
    CDvmValue* TargetValueObject = NULL;
    CString strTempIDPath = GetObjectIDPath(strParentID,strObjectID);
	TargetValueObject = m_pAttrWidgetDeviceAttrs->FindDataObjValueByID_Has(strTempIDPath); 
    return TargetValueObject;
}

BOOL QDeviceModelAttrWidget_Eng::ProcessInput(QLineEdit *pLineEdit, const QString &unit, QString &lastValidInput)
{
    QString CurrentText = pLineEdit->text().trimmed();

    // 移除末尾的" Hz"（包括空格）
    if(unit == _T(" Hz"))
    {
        CurrentText.remove(QRegExp("\\s*Hz\\s*$"));
    }
    else if(unit == _T(" V(L-L)"))
    {
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
    }
    else if(unit == _T(" V(L-N)"))
    {
        CurrentText.remove(QRegExp("\\s*V\\(L-N\\)\\s*$"));
    }
    else if(unit == _T(" V"))
    {
        CurrentText.remove(QRegExp("\\s*V\\s*$"));
    }
    else if(unit == _T(" A"))
    {
        CurrentText.remove(QRegExp("\\s*A\\s*$"));
    }
    else if(unit == _T(" s"))
    {
        CurrentText.remove(QRegExp("\\s*s\\s*$"));
    }



    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        // 格式化值并添加" Hz"后缀
        QString formattedInput = QString::number(value, 'f', 3) + unit;
        pLineEdit->setText(formattedInput);

        // 更新上次合法输入
        lastValidInput = formattedInput;
        return TRUE;
    }
    else
    {
        // 显示错误消息并恢复为上次的合法输入（如果有的话）
        CXMessageBox::information(this, g_sLangTxt_Xrio_InvalidInput/*_T("无效输入")*/, g_sLangTxt_Xrio_InputRestrictionTypeOne/*_T("输入必须是大于或等于0的数字。")*/);
        if (!lastValidInput.isEmpty())
        {
            pLineEdit->setText(lastValidInput);
            return FALSE;
        }
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVPrimLLToValueVPrimLL2(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput;
        if(ui->m_radPhases2->isChecked())
        {
            formattedInput  = QString::number(value/2, 'f', 3) + QString(" V(L-N)");
        }
        else if(ui->m_radPhases3->isChecked())
        {
            formattedInput  = QString::number(value/1.73205, 'f', 3) + QString(" V(L-N)");
        }

        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVPrimLL2ToValueVPrimLL(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-N\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {

        QString formattedInput;
        if(ui->m_radPhases2->isChecked())
        {
            formattedInput  = QString::number(value*2, 'f', 3) + QString(" V(L-L)");
        }
        else if(ui->m_radPhases3->isChecked())
        {
            formattedInput  = QString::number(value*1.73205, 'f', 3) + QString(" V(L-L)");
        }

        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVPrimLL3ToValueVPrimLL(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput  = QString::number(value*1.73205, 'f', 3) + QString(" V(L-L)");
        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVNomToValueVNom2(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput;
        if(ui->m_radPhases2->isChecked())
        {
            formattedInput  = QString::number(value/2, 'f', 3) + QString(" V(L-N)");
        }
        else if(ui->m_radPhases3->isChecked())
        {
            formattedInput  = QString::number(value/1.73205, 'f', 3) + QString(" V(L-N)");
        }
        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVNom2ToValueVNom(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-N\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput;
        if(ui->m_radPhases2->isChecked())
        {
            formattedInput  = QString::number(value*2, 'f', 3) + QString(" V(L-L)");
        }
        else if(ui->m_radPhases3->isChecked())
        {
            formattedInput  = QString::number(value*1.73205, 'f', 3) + QString(" V(L-L)");
        }

        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueVNom3ToValueVNom(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*A\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput  = QString::number(value*m_strValueININOM.toDouble(), 'f', 3) + QString(" A");
        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValueINom2ToValueINom(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*A\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput  = QString::number(value*1.73205*m_strValueVLNVN.toDouble(), 'f', 3) + QString(" A");
        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValuePhases2ToValueVPrimLL2_ValueVNom2(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput = QString::number(value/2, 'f', 3) + QString(" V(L-N)");
        return formattedInput;
    }
}

QString QDeviceModelAttrWidget_Eng::ValuePhases3ToValueVPrimLL2_ValueVNom2(QString &text)
{
    QString CurrentText = text.trimmed();

    CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));

    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0)
    {
        QString formattedInput = QString::number(value/1.73205, 'f', 3) + QString(" V(L-N)");
        return formattedInput;
    }
}

void QDeviceModelAttrWidget_Eng::on_m_radCustomize_clicked()
{
    ui->m_editOverloadSupTime->setEnabled(true);
}
void QDeviceModelAttrWidget_Eng::on_m_radHigh_clicked()
{
    ui->m_editOverloadSupTime->setEnabled(false);
    ui->m_editOverloadSupTime->setText("0.050 s");
}
void QDeviceModelAttrWidget_Eng::on_m_radLow_clicked()
{
    ui->m_editOverloadSupTime->setEnabled(false);
    ui->m_editOverloadSupTime->setText("0.200 s");
}
void QDeviceModelAttrWidget_Eng::on_m_radDisconnect_clicked()
{
    ui->m_editOverloadSupTime->setEnabled(false);
    ui->m_editOverloadSupTime->setText("0.000 s");
}

void QDeviceModelAttrWidget_Eng::on_m_btnOK_clicked()
{
    if(m_pAttrWidgetDeviceAttrs)
    {
        emit sig_UpdataDeviceAttrs(m_pAttrWidgetDeviceAttrs/*(CDvmDataset*)m_pAttrWidgetDeviceAttrs->Clone()*/);
    }
    emit sig_CancelClicked();  // 发射信号
}

void QDeviceModelAttrWidget_Eng::on_m_btnCancel_clicked()
{
    emit sig_CancelClicked();  // 发射信号
}

void QDeviceModelAttrWidget_Eng::on_m_editDeviceMode_editingFinished()
{
    QString CurrentText = ui->m_editDeviceMode->text();
    emit sig_m_editDeviceMode_editingFinished_Widget(CurrentText);
}

QDeviceModelAttrDlg_Eng::QDeviceModelAttrDlg_Eng(CXDeviceModel *pXDeviceModel, QWidget *parent):QDialog(parent)
{
    pDeviceModelAttrWidget = new QDeviceModelAttrWidget_Eng(this);
    CDvmDataset *pDeviceAttrs = NULL;
	if (pXDeviceModel)
	{
        pDeviceAttrs = pXDeviceModel->GetDeviceAttrs();
	}
    if(pDeviceAttrs)
    {
        pDeviceModelAttrWidget->m_pAttrWidgetDeviceAttrs = (CDvmDataset*)pDeviceAttrs->Clone();
		pDeviceModelAttrWidget->CreateQDeviceModelAttrWidget_Eng(pDeviceModelAttrWidget->m_pAttrWidgetDeviceAttrs);
    }
    pDeviceModelAttrWidget->setAttribute(Qt::WA_DeleteOnClose);
    pDeviceModelAttrWidget->setGeometry(0, -4, 1285, 670);
    setFixedSize(1280, 650);
    //setFixedSize(1400, 970);

//修改为使用QT4的版本
//#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//    connect(pDeviceModelAttrWidget, &QDeviceModelAttrWidget_Eng::sig_CancelClicked, this, &QDeviceModelAttrDlg_Eng::close);  // 连接信号和槽
//#else
//	connect(pDeviceModelAttrWidget, SIGNAL(sig_CancelClicked()), this, SLOT(close()));  // 连接信号和槽
//#endif
    connect(pDeviceModelAttrWidget, SIGNAL(sig_CancelClicked()), this, SLOT(close()));
    connect(pDeviceModelAttrWidget, SIGNAL(sig_UpdataDeviceAttrs(CDvmDataset*)),this,SLOT(slot_UpdataDeviceAttrs(CDvmDataset*)));
}

QDeviceModelAttrDlg_Eng::~QDeviceModelAttrDlg_Eng()
{
    if(pDeviceModelAttrWidget != NULL)
    {
        delete pDeviceModelAttrWidget;
        pDeviceModelAttrWidget = NULL;
    }
}

void QDeviceModelAttrDlg_Eng::slot_UpdataDeviceAttrs(CDvmDataset *pDataset)
{
    emit sig_UpdataDeviceAttrs(pDataset);
}

void QDeviceModelAttrWidget_Eng::on_m_editManufacturer_editingFinished()
{
    QString CurrentText = ui->m_editManufacturer->text();
    emit sig_m_editManufacturer_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editDeviceType_editingFinished()
{
    QString CurrentText = ui->m_editDeviceType->text();
    emit sig_m_editDeviceType_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editDeviceAddress_editingFinished()
{
    QString CurrentText = ui->m_editDeviceAddress->text();
    emit sig_m_editDeviceAddress_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editSerialnr_editingFinished()
{
    QString CurrentText = ui->m_editSerialnr->text();
    emit sig_m_editSerialnr_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editProtectedObjectName_editingFinished()
{
    QString CurrentText = ui->m_editProtectedObjectName->text();
    emit sig_m_editProtectedObjectName_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editAdditionalINF02_editingFinished()
{
    QString CurrentText = ui->m_editAdditionalINF02->text();
    emit sig_m_editAdditionalINF02_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editSubstation_editingFinished()
{
    QString CurrentText = ui->m_editSubstation->text();
    emit sig_m_editSubstation_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editSubstatioAddress_editingFinished()
{
    QString CurrentText = ui->m_editSubstatioAddress->text();
    emit sig_m_editSubstatioAddress_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editBay_editingFinished()
{
    QString CurrentText = ui->m_editBay->text();
    emit sig_m_editBay_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editBayAddress_editingFinished()
{
    QString CurrentText = ui->m_editBayAddress->text();
    emit sig_m_editBayAddress_editingFinished_Widget(CurrentText);
}

void QDeviceModelAttrWidget_Eng::on_m_editFNom_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editFNom,_T(" Hz"),m_strValueFNomlastValidInput);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueFNomlastValidInput;
        CurrentText.remove(QRegExp("\\s*Hz\\s*$"));
        emit sig_m_editFNom_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editVPrimLL_editingFinished()
{
    BOOL bIsSuccess= ProcessInput(ui->m_editVPrimLL,_T(" V(L-L)"),m_strValueVPrimLLlastValidInput);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVPrimLLToValueVPrimLL2(m_strValueVPrimLLlastValidInput);
        ui->m_editVPrimLL2->setText(formattedInput);
        m_strValueVPrimLLlastValidInput2 = formattedInput;

        QString CurrentText = m_strValueVPrimLLlastValidInput;
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVPrimLL_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editVNom_editingFinished()
{
    BOOL bIsSuccess= ProcessInput(ui->m_editVNom,_T(" V(L-L)"),m_strValueVNomlastValidInput);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVNomToValueVNom2(m_strValueVNomlastValidInput);
        ui->m_editVNom2->setText(formattedInput);
        m_strValueVNomlastValidInput2 = formattedInput;

        QString CurrentText = m_strValueVNomlastValidInput;
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVNom_editingFinished_Widget(CurrentText);
    }

}

void QDeviceModelAttrWidget_Eng::on_m_editVPrimLL2_editingFinished()
{
    BOOL bIsSuccess= ProcessInput(ui->m_editVPrimLL2,_T(" V(L-N)"),m_strValueVPrimLLlastValidInput2);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVPrimLL2ToValueVPrimLL(m_strValueVPrimLLlastValidInput2);
        ui->m_editVPrimLL->setText(formattedInput);
        m_strValueVPrimLLlastValidInput = formattedInput;

        QString CurrentText = m_strValueVPrimLLlastValidInput;
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVPrimLL2_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editVNom2_editingFinished()
{
    BOOL bIsSuccess= ProcessInput(ui->m_editVNom2,_T(" V(L-N)"),m_strValueVNomlastValidInput2);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVNom2ToValueVNom(m_strValueVNomlastValidInput2);
        ui->m_editVNom->setText(formattedInput);
        m_strValueVNomlastValidInput = formattedInput;

        QString CurrentText = m_strValueVNomlastValidInput;
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVNom2_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editIPRIM_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editIPRIM,_T(" A"),m_strValueIPRIMlastValidInput);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueIPRIMlastValidInput;
        CurrentText.remove(QRegExp("\\s*A\\s*$"));
        emit sig_m_editIPRIM_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editINom_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editINom,_T(" A"),m_strValueINomlastValidInput);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueINomlastValidInput;
        CurrentText.remove(QRegExp("\\s*A\\s*$"));
        emit sig_m_editINom_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editVPrimLL3_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editVPrimLL3,_T(" V"),m_strValueVPrimLLlastValidInput3);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVPrimLL3ToValueVPrimLL(m_strValueVPrimLLlastValidInput3);

        formattedInput.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVPrimLL3_editingFinished_Widget(formattedInput);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editVNom3_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editVNom3,_T(" V"),m_strValueVNomlastValidInput3);
    if(bIsSuccess)
    {
        QString formattedInput = ValueVPrimLL3ToValueVPrimLL(m_strValueVNomlastValidInput3);

        formattedInput.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVNom3_editingFinished_Widget(formattedInput);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editIPRIM2_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editIPRIM2,_T(" A"),m_strValueIPRIMlastValidInput2);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueIPRIMlastValidInput2;
        CurrentText.remove(QRegExp("\\s*A\\s*$"));
        emit sig_m_editIPRIM2_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editINom2_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editINom2,_T(" A"),m_strValueINomlastValidInput2);
    if(bIsSuccess)
    {
        QString formattedInput = ValueINom2ToValueINom(m_strValueINomlastValidInput2);

        formattedInput.remove(QRegExp("\\s*A\\s*$"));
        emit sig_m_editINom2_editingFinished_Widget(formattedInput);
    }

}

void QDeviceModelAttrWidget_Eng::on_m_editVMaxLL_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editVMaxLL,_T(" V(L-L)"),m_strValueVMAXLLValidInput);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueVMAXLLValidInput;
        CurrentText.remove(QRegExp("\\s*V\\(L-L\\)\\s*$"));
        emit sig_m_editVMaxLL_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editIMax_editingFinished()
{
    BOOL bIsSuccess = ProcessInput(ui->m_editIMax,_T(" A"),m_strValueIMAXValidInput);
    if(bIsSuccess)
    {
        QString CurrentText = m_strValueIMAXValidInput;
        CurrentText.remove(QRegExp("\\s*A\\s*$"));
        emit sig_m_editIMax_editingFinished_Widget(CurrentText);
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editOverloadSupTime_editingFinished()
{
    QString CurrentText = ui->m_editOverloadSupTime->text().trimmed();

    CurrentText.remove(QRegExp("\\s*s\\s*$"));


    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0 && value <= 800)
    {
        // 格式化值并添加" Hz"后缀
        QString formattedInput = QString::number(value, 'f', 3) + " s";
        ui->m_editOverloadSupTime->setText(formattedInput);

        // 更新上次合法输入
        m_strValueOVERLOADSUPTIMEValidInput = formattedInput;

        emit sig_m_editOverloadSupTime_editingFinished_Widget(m_strValueIMAXValidInput.remove(QRegExp("\\s*s\\s*$")));
    }
    else
    {
        // 显示错误消息并恢复为上次的合法输入（如果有的话）
        CXMessageBox::information(this, g_sLangTxt_Xrio_InvalidInput/*_T("无效输入")*/, g_sLangTxt_Xrio_InputRestrictionTypeTwo/*_T("请输入介于0和800之间的值。")*/);
        if (!m_strValueOVERLOADSUPTIMEValidInput.isEmpty())
        {
            ui->m_editOverloadSupTime->setText(m_strValueOVERLOADSUPTIMEValidInput);
        }
    }
}

void QDeviceModelAttrWidget_Eng::on_m_editDeBounceTime_editingFinished()
{
    QString CurrentText = ui->m_editDeBounceTime->text().trimmed();

    CurrentText.remove(QRegExp("\\s*s\\s*$"));


    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0 && value <= 0.025)
    {
        // 格式化值并添加" Hz"后缀
        QString formattedInput = QString::number(value, 'f', 3) + " s";
        ui->m_editDeBounceTime->setText(formattedInput);

        // 更新上次合法输入
        m_strValueDeBounceTimeValidInput = formattedInput;

        emit sig_m_editDeBounceTime_editingFinished_Widget(m_strValueDeBounceTimeValidInput.remove(QRegExp("\\s*s\\s*$")));
    }
    else
    {
        // 显示错误消息并恢复为上次的合法输入（如果有的话）
        CXMessageBox::information(this, g_sLangTxt_Xrio_InvalidInput/*_T("无效输入")*/, g_sLangTxt_Xrio_InputRestrictionTypeThree/*_T("请输入介于0.00和0.025之间的值。")*/);
        if (!m_strValueDeBounceTimeValidInput.isEmpty())
        {
            ui->m_editDeBounceTime->setText(m_strValueDeBounceTimeValidInput);
        }
    }


}

void QDeviceModelAttrWidget_Eng::on_m_editDeGlitchTime_editingFinished()
{
    QString CurrentText = ui->m_editDeGlitchTime->text().trimmed();

    CurrentText.remove(QRegExp("\\s*s\\s*$"));


    // 尝试将剩余文本转换为double
    bool ok;
    double value = CurrentText.toDouble(&ok);

    // 检查转换是否成功且值大于等于0
    if(ok && value >= 0 && value <= 0.025)
    {
        // 格式化值并添加" Hz"后缀
        QString formattedInput = QString::number(value, 'f', 3) + " s";
        ui->m_editDeGlitchTime->setText(formattedInput);

        // 更新上次合法输入
        m_strValueDeGlitchTimeValidInput = formattedInput;

        emit sig_m_editDeGlitchTime_editingFinished_Widget(m_strValueDeGlitchTimeValidInput.remove(QRegExp("\\s*s\\s*$")));
    }
    else
    {
        // 显示错误消息并恢复为上次的合法输入（如果有的话）
        CXMessageBox::information(this, g_sLangTxt_Xrio_InvalidInput/*_T("无效输入")*/, g_sLangTxt_Xrio_InputRestrictionTypeThree/*_T("请输入介于0.00和0.025之间的值。")*/);
        if (!m_strValueDeGlitchTimeValidInput.isEmpty())
        {
            ui->m_editDeGlitchTime->setText(m_strValueDeGlitchTimeValidInput);
        }
    }
}

void QDeviceModelAttrWidget_Eng::on_m_radPhases2_clicked()
{
    emit sig_m_radPhases2_clicked_Widget();
    QString formattedInput = ValuePhases2ToValueVPrimLL2_ValueVNom2(m_strValueVPrimLLlastValidInput);
    ui->m_editVPrimLL2->setText(formattedInput);
    m_strValueVPrimLLlastValidInput2 = formattedInput;

    formattedInput = ValuePhases2ToValueVPrimLL2_ValueVNom2(m_strValueVNomlastValidInput);
    ui->m_editVNom2->setText(formattedInput);
    m_strValueVNomlastValidInput2 = formattedInput;
}

void QDeviceModelAttrWidget_Eng::on_m_radPhases3_clicked()
{
    emit sig_m_radPhases3_clicked_Widget();
    QString formattedInput = ValuePhases3ToValueVPrimLL2_ValueVNom2(m_strValueVPrimLLlastValidInput);

    ui->m_editVPrimLL2->setText(formattedInput);
    m_strValueVPrimLLlastValidInput2 = formattedInput;

    formattedInput = ValuePhases3ToValueVPrimLL2_ValueVNom2(m_strValueVNomlastValidInput);
    ui->m_editVNom2->setText(formattedInput);
    m_strValueVNomlastValidInput2 = formattedInput;
}


void QDeviceModelAttrWidget_Eng::on_m_editBackTime_editingFinished()
{
    ProcessInput(ui->m_editBackTime,_T(" s"),m_strValueBackTimeValidInput);
}

void QDeviceModelAttrWidget_Eng::slot_m_editDeviceMode_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_MODEL);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editManufacturer_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_MANUFACTURER);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editDeviceType_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_DEVICE_TYPE);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editDeviceAddress_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editSerialnr_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_SERIALNR);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editProtectedObjectName_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editAdditionalINF02_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE,XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editSubstation_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editSubstatioAddress_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editFNom_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_FNOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editBay_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editBayAddress_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION,XRIO_DEVICE_MODEL_ID_BAY_ADDRESS);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVPrimLL_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VPRIM_LL);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVPrimLL2_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VPRIM_LL);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVPrimLL3_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VPRIM_LL);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVNom_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VNOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVNom2_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VNOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVNom3_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_VNOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editIPRIM_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_IPRIM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editIPRIM2_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_IPRIM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editINom_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_INOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editINom2_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_INOM);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editVMaxLL_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_VMAX_LL);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editIMax_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS,XRIO_DEVICE_MODEL_ID_IMAX);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editOverloadSupTime_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editDeBounceTime_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_editDeGlitchTime_editingFinished(const QString &CurrentText)
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_MISC,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = CurrentText;
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_radPhases2_clicked()
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_PHASES);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = _T("2");
    }
}

void QDeviceModelAttrWidget_Eng::slot_m_radPhases3_clicked()
{
    CDvmValue* TargetValueObject = NULL;
    TargetValueObject = FindValueObject(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES,XRIO_DEVICE_MODEL_ID_PHASES);
    if(TargetValueObject)
    {
        TargetValueObject->m_strValue = _T("3");
    }
}
