#include "DistanceSearchAddMultDlg.h"
#include "ui_DistanceSearchAddMultDlg.h"
#include "QMessageBox"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLangResource_Native.h"
#include "DistanceSearchCommon.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include <math.h>
#include <qmath.h>

extern CFont *g_pSttGlobalFont;

QDistanceSearchAddMultDlg::QDistanceSearchAddMultDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceSearchAddMultDlg)
{
    ui->setupUi(this);
    m_nInputWidgetWidth = 120;
    InitUI();

    dEndX.clear();
    dEndY.clear();

    connect(m_editLNActionTime, SIGNAL(editingFinished()), this, SLOT(on_m_editLNActionTime_editingFinished()));
    connect(m_editLLActionTime, SIGNAL(editingFinished()), this, SLOT(on_m_editLLActionTime_editingFinished()));
    connect(m_editLLLActionTime, SIGNAL(editingFinished()), this, SLOT(on_m_editLLLActionTime_editingFinished()));

    return;
}

QDistanceSearchAddMultDlg::~QDistanceSearchAddMultDlg()
{
    delete ui;
}

void QDistanceSearchAddMultDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/DistanceSearchTest.png");
#else
	strPngPath =  ":/ctrls/images/DistanceSearchTest.png";
#endif
	this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);

    QColor backgrdColor = this->palette().color(QPalette::Background);
    ui->m_tableWidget->setStyleSheet(QString("QTableWidget { background-color: %1; }").arg(backgrdColor.name()));
    ui->m_tableWidget->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setColumnWidth(0, this->width()*0.6);
    ui->m_tableWidget->setFixedHeight(202);
    for(int i = 0; i < 4; i++)
    {
        ui->m_tableWidget->setRowHeight(i, 50);
    }

    ui->m_tableWidget->item(0, 0)->setText(g_sLangTxt_ActionTime_FaultPhase);
    ui->m_tableWidget->item(0, 1)->setText(g_sLangTxt_Native_ActionTime);

    m_cbAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbCN = new QCheckBox("CN", ui->m_tableWidget);
    QWidget *containerWidget_1 = new QWidget(this);
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout(containerWidget_1);
    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_1->addStretch();
    horizontalLayout_1->addWidget(m_cbAN);
    horizontalLayout_1->addStretch();
    horizontalLayout_1->addWidget(m_cbBN);
    horizontalLayout_1->addStretch();
    horizontalLayout_1->addWidget(m_cbCN);
    horizontalLayout_1->addStretch();
    ui->m_tableWidget->setCellWidget(1, 0, containerWidget_1);

    m_editLNActionTime = new QLineEdit(ui->m_tableWidget);
    QWidget *containerWidget_2 = new QWidget(this);
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(containerWidget_2);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2->addStretch();
    horizontalLayout_2->addWidget(m_editLNActionTime);
    horizontalLayout_2->addStretch();
    ui->m_tableWidget->setCellWidget(1, 1, containerWidget_2);

    m_cbAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbCA = new QCheckBox("CA", ui->m_tableWidget);
    QWidget *containerWidget_3 = new QWidget(this);
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout(containerWidget_3);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbAB);
    horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbBC);
    horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbCA);
    horizontalLayout_3->addStretch();
    ui->m_tableWidget->setCellWidget(2, 0, containerWidget_3);

    m_editLLActionTime = new QLineEdit(ui->m_tableWidget);
    QWidget *containerWidget_4 = new QWidget(this);
    QHBoxLayout *horizontalLayout_4 = new QHBoxLayout(containerWidget_4);
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_4->addStretch();
    horizontalLayout_4->addWidget(m_editLLActionTime);
    horizontalLayout_4->addStretch();
    ui->m_tableWidget->setCellWidget(2, 1, containerWidget_4);

    m_cbABC = new QCheckBox("ABC", ui->m_tableWidget);
    QWidget *containerWidget_5 = new QWidget(this);
    QHBoxLayout *horizontalLayout_5 = new QHBoxLayout(containerWidget_5);
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_5->addStretch();
    horizontalLayout_5->addWidget(m_cbABC);
    horizontalLayout_5->addStretch();
    ui->m_tableWidget->setCellWidget(3, 0, containerWidget_5);

    m_editLLLActionTime = new QLineEdit(ui->m_tableWidget);
    QWidget *containerWidget_6 = new QWidget(this);
    QHBoxLayout *horizontalLayout_6 = new QHBoxLayout(containerWidget_6);
    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_editLLLActionTime);
    horizontalLayout_6->addStretch();
    ui->m_tableWidget->setCellWidget(3, 1, containerWidget_6);

    m_editLNActionTime->setFixedWidth(m_nInputWidgetWidth);
    m_editLLActionTime->setFixedWidth(m_nInputWidgetWidth);
    m_editLLLActionTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOrigImp->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editOrigAng->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultCur->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editFaultVol->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editSearchAngBeg->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editSearchAngEnd->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editAngStep->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbZoneType->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editSearchLen->setFixedWidth(m_nInputWidgetWidth);
    ui->m_cbbErrType->setFixedWidth(m_nInputWidgetWidth + 30);
    ui->m_editAbsErr->setFixedWidth(m_nInputWidgetWidth + 30);
    ui->m_editRelErr->setFixedWidth(m_nInputWidgetWidth + 30);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_ERRORTYPE);
    ui->m_cbbErrType->ShowBaseList(pDataType);

	ui->m_gbOtherParas->setTitle(g_sLangTxt_Gradient_OtherSet);
	ui->m_gbResultEval->setTitle(g_sLangTxt_StateEstimate_ResultEstimate);
	ui->m_labOrigImp->setText(g_sLangTxt_DistanceSearch_OrigImp);
	ui->m_labOrigAng->setText(g_sLangTxt_DistanceSearch_OrigAng);
	ui->m_labFaultCur->setText(g_sLangTxt_Impedance_ShortCurr);
	ui->m_labFaultVol->setText(g_sLangTxt_Impedance_ShortVol);
	ui->m_labSearchAngBeg->setText(g_sLangTxt_DistanceSearch_SearchAngBeg);
	ui->m_labSearchAngEnd->setText(g_sLangTxt_DistanceSearch_SearchAngEnd);
	ui->m_labAngStep->setText(g_sLangTxt_DistanceSearch_AngStep);
	ui->m_labZoneType->setText(g_sLangTxt_DistanceSearch_ZoneTypeSelect);
	ui->m_labSearchLen->setText(g_sLangTxt_DistanceSearch_SearchLen);
	ui->m_labErrType->setText(g_sLangTxt_ActionTime_ErrType);
    ui->m_labAbsErr->setText(g_sLangTxt_DistanceSearch_AbsErr);
    ui->m_labRelErr->setText(g_sLangTxt_ActionTime_RelErr);
	ui->m_btnOk->setText(g_sLangTxt_OK);
	ui->m_btnCancel->setText(g_sLangTxt_Cancel);

	return;
}

void QDistanceSearchAddMultDlg::SetValueToPage(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AN)
    {
        m_cbAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BN)
    {
        m_cbBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CN)
    {
        m_cbCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AB)
    {
        m_cbAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BC)
    {
        m_cbBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CA)
    {
        m_cbCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ABC)
    {
        m_cbABC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LN_TSetting)
    {
        m_editLNActionTime->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LL_TSetting)
    {
        m_editLLActionTime->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LLL_TSetting)
    {
        m_editLLLActionTime->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginImp)
    {
        ui->m_editOrigImp->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVAL_MAX, BEGINVAL_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginAng)
    {
        ui->m_editOrigAng->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngBegVal)
    {
        ui->m_editSearchAngBeg->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngEndVal)
    {
        ui->m_editSearchAngEnd->setText(DistanceSearchValueCheck(pData->m_strValue, ENDVALANG_MAX, ENDVALANG_MIN, 2));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchLength)
    {
        ui->m_editSearchLen->setText(DistanceSearchValueCheck(pData->m_strValue, STEP_MAX, STEP_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AngleStep)
    {
        ui->m_editAngStep->setText(DistanceSearchValueCheck(pData->m_strValue, BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ZoneType)
    {
        int nIndex = CString_To_long(pData->m_strValue);
        if(nIndex > 1)
            nIndex -= 2;
        else
            nIndex += 5;

        ui->m_cbbZoneType->setCurrentIndex(nIndex);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultCur)
    {
        ui->m_editFaultCur->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTIF_MAX, FAULTIF_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultVolt)
    {
        ui->m_editFaultVol->setText(DistanceSearchValueCheck(pData->m_strValue, FAULTVF_MAX, FAULTVF_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ERRORLOGIC)
    {
		CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_DATATYPE_ID_ERRORTYPE);
		CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
		if (pValue != NULL)
			ui->m_cbbErrType->SetCurrSelByName(pValue->m_strName);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_RELERR)
    {
        ui->m_editRelErr->setText(DistanceSearchValueCheck(pData->m_strValue, RELERR_MAX, RELERR_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_ABSERR)
    {
        ui->m_editAbsErr->setText(DistanceSearchValueCheck(pData->m_strValue, ABSERR_MAX, ABSERR_MIN, 3));
    }
}

void QDistanceSearchAddMultDlg::SetDatas(CDataGroup *pParas)
{
    if(pParas == NULL)
        return;

    POS pos = pParas->GetHeadPosition();
    while(pos != NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        SetValueToPage(pData);
    }
}

void QDistanceSearchAddMultDlg::GetPageToValue(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AN)
    {
        pData->m_strValue.setNum(m_cbAN->isChecked());

        if(m_cbAN->isChecked())
            nFaultTypeArr[0] = 1;
        else
            nFaultTypeArr[0] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BN)
    {
        pData->m_strValue.setNum(m_cbBN->isChecked());

        if(m_cbBN->isChecked())
            nFaultTypeArr[1] = 1;
        else
            nFaultTypeArr[1] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CN)
    {
        pData->m_strValue.setNum(m_cbCN->isChecked());

        if(m_cbCN->isChecked())
            nFaultTypeArr[2] = 1;
        else
            nFaultTypeArr[2] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AB)
    {
        pData->m_strValue.setNum(m_cbAB->isChecked());

        if(m_cbAB->isChecked())
            nFaultTypeArr[3] = 1;
        else
            nFaultTypeArr[3] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BC)
    {
        pData->m_strValue.setNum(m_cbBC->isChecked());

        if(m_cbBC->isChecked())
            nFaultTypeArr[4] = 1;
        else
            nFaultTypeArr[4] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CA)
    {
        pData->m_strValue.setNum(m_cbCA->isChecked());

        if(m_cbCA->isChecked())
            nFaultTypeArr[5] = 1;
        else
            nFaultTypeArr[5] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ABC)
    {
        pData->m_strValue.setNum(m_cbABC->isChecked());

        if(m_cbABC->isChecked())
            nFaultTypeArr[6] = 1;
        else
            nFaultTypeArr[6] = 0;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LN_TSetting)
    {
        pData->m_strValue = m_editLNActionTime->text();
        dTSetting[0] = m_editLNActionTime->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LL_TSetting)
    {
        pData->m_strValue = m_editLLActionTime->text();
        dTSetting[1] = m_editLLActionTime->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LLL_TSetting)
    {
        pData->m_strValue = m_editLLLActionTime->text();
        dTSetting[2] = m_editLLLActionTime->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginImp)
    {
        pData->m_strValue = ui->m_editOrigImp->text();
        dOrigImp = ui->m_editOrigImp->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginAng)
    {
        pData->m_strValue = ui->m_editOrigAng->text();
        dOrigAng = ui->m_editOrigAng->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngBegVal)
    {
        pData->m_strValue = ui->m_editSearchAngBeg->text();
        dSearchAngBeg = ui->m_editSearchAngBeg->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngEndVal)
    {
        pData->m_strValue = ui->m_editSearchAngEnd->text();
        dSearchAngEnd = ui->m_editSearchAngEnd->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchLength)
    {
        pData->m_strValue = ui->m_editSearchLen->text();
        dSearchLen = ui->m_editSearchLen->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AngleStep)
    {
        pData->m_strValue = ui->m_editAngStep->text();
        dAngStep = ui->m_editAngStep->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ZoneType)
    {
        int nValue = ui->m_cbbZoneType->currentIndex();
        CString strValue;
        if(nValue < 5)
            nValue += 2;
        else
            nValue -= 5;

        strValue.setNum(nValue);
        pData->m_strValue = strValue;

        nZoneType = nValue;
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultCur)
    {
        pData->m_strValue = ui->m_editFaultCur->text();
        dFaultCur = ui->m_editFaultCur->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultVolt)
    {
        pData->m_strValue = ui->m_editFaultVol->text();
        dFaultVolt = ui->m_editFaultVol->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ERRORLOGIC)
    {
		CDataTypeValue *pValue = (CDataTypeValue*)ui->m_cbbErrType->GetCurrSelObject();
		if (pValue != NULL)
		{
			pData->m_strValue = pValue->m_strIndex;
			nErrType = CString_To_long(pValue->m_strIndex);
		}		
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_RELERR)
    {
        pData->m_strValue = ui->m_editRelErr->text();
        dRelErr = ui->m_editRelErr->text().toDouble();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_ABSERR)
    {
        pData->m_strValue = ui->m_editAbsErr->text();
        dAbsErr = ui->m_editAbsErr->text().toDouble();
    }

}

void QDistanceSearchAddMultDlg::CheckAllPresence(CDataGroup *pParas)
{
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AN);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BN);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CN);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AB);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_BC);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_CA);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ABC);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LN_TSetting);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LL_TSetting);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_LLL_TSetting);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginImp);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_OriginAng);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngBegVal);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchAngEndVal);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_SearchLength);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_AngleStep);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_ZoneType);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultCur);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_MULT_ID_FaultVolt);
}

void QDistanceSearchAddMultDlg::GetDatas(CDataGroup *pParas)
{
    if(pParas == NULL)
        return;

    CheckAllPresence(pParas);

    POS pos = pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        GetPageToValue(pData);
    }
}

void QDistanceSearchAddMultDlg::AddDistanceSearchMultItem()
{
    int nNum = 0;
    double dCurAngle;
    dBegX = dOrigImp*cos(dOrigAng * M_PI / 180.0);
    dBegY = dOrigImp*sin(dOrigAng * M_PI / 180.0);
    nNum = (dSearchAngEnd - dSearchAngBeg)/dAngStep;

    dEndX.clear();
    dEndY.clear();
    for(int i = 0; i <= nNum; i++)
    {
        double dTempEndX, dTempEndY;
        dCurAngle = dSearchAngBeg + dAngStep*i;
        dTempEndX = dBegX + dSearchLen*cos(dCurAngle * M_PI / 180.0);
        dTempEndY = dBegY + dSearchLen*sin(dCurAngle * M_PI / 180.0);

        dEndX.push_back(dTempEndX);
        dEndY.push_back(dTempEndY);
    }

    if(fabs(dSearchAngEnd - dCurAngle) > 0.001)
    {
        double dTempEndX, dTempEndY;
        dTempEndX = dBegX + dSearchLen*cos(dSearchAngEnd * M_PI / 180.0);
        dTempEndY = dBegY + dSearchLen*sin(dSearchAngEnd * M_PI / 180.0);

        dEndX.push_back(dTempEndX);
        dEndY.push_back(dTempEndY);
    }

    for(int i = 0; i < 7; i++)
    {
        if(nFaultTypeArr[i] == 0)
            continue;

        CString strFaultType;
        double dSettingTime;
        int nFaultType; //下拉框索引
        if(i < 3)
        {
            strFaultType = "LN";
            dSettingTime = dTSetting[0];
            nFaultType = i;
        }
        else if(i < 6)
        {
            strFaultType = "LL";
            dSettingTime = dTSetting[1];
            nFaultType = i;
        }
        else
        {
            strFaultType = "LLL";
            dSettingTime = dTSetting[2];
            nFaultType = 9;
        }

        for(int j = 0; j < dEndX.size(); j++)
        {
            QVector<double> dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
                    dTSettingArr, dRelErrArr, dAbsErrArr;
            QVector<int> nErrTypeArr;

            dTSettingArr.push_back(dSettingTime);
            dRelErrArr.push_back(dRelErr);
            dAbsErrArr.push_back(dAbsErr);
            nErrTypeArr.push_back(nErrType);
            BOOL bAdd = CalDistanceSearchItemParas(strFaultType, nZoneType, dBegX, dBegY, dEndX[j], dEndY[j],
                                                   dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
                                                   dTSettingArr, dRelErrArr, dAbsErrArr, nErrTypeArr);
            if(!bAdd)
            {
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("绘制线段【BegX = %.2f, BegY = %.2f, EndX = %.2f, EndY = %.2f】与特性曲线没有交点，不生成测试项。"),
                                           dBegX, dBegY, dEndX[j], dEndY[j]);
                continue;
            }

            for(int k = 0; k < dBegZArr.size(); k++)
            {
                emit sig_AddDistanceSearchItem(nFaultType, dTSettingArr[k], nZoneType, dBegZArr[k], dBegAngArr[k], dEndZArr[k], dEndAngArr[k],
                                               dFaultCur, dFaultVolt, dRelErrArr[k], dAbsErrArr[k], nErrTypeArr[k]);
            }
        }

    }

}

void QDistanceSearchAddMultDlg::on_m_btnOk_clicked()
{
    GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    AddDistanceSearchMultItem();
	this->done(Accepted);
}

void QDistanceSearchAddMultDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QDistanceSearchAddMultDlg::on_m_editLNActionTime_editingFinished()
{
    m_editLNActionTime->setText(DistanceSearchValueCheck(m_editLNActionTime->text(), ACTIONTIME_MAX, ACTIONTIME_MIN, 3));
    return;
}

void QDistanceSearchAddMultDlg::on_m_editLLActionTime_editingFinished()
{
    m_editLLActionTime->setText(DistanceSearchValueCheck(m_editLLActionTime->text(), ACTIONTIME_MAX, ACTIONTIME_MIN, 3));
    return;
}

void QDistanceSearchAddMultDlg::on_m_editLLLActionTime_editingFinished()
{
    m_editLLLActionTime->setText(DistanceSearchValueCheck(m_editLLLActionTime->text(), ACTIONTIME_MAX, ACTIONTIME_MIN, 3));
    return;
}

void QDistanceSearchAddMultDlg::on_m_cbbZoneType_currentIndexChanged(int index)
{
    if(index == 5)
    {
        m_editLNActionTime->setEnabled(true);
        m_editLLActionTime->setEnabled(true);
        m_editLLLActionTime->setEnabled(true);

        ui->m_cbbErrType->setEnabled(true);
        ui->m_editRelErr->setEnabled(true);
        ui->m_editAbsErr->setEnabled(true);
    }
    else
    {
        m_editLNActionTime->setEnabled(false);
        m_editLLActionTime->setEnabled(false);
        m_editLLLActionTime->setEnabled(false);

        ui->m_cbbErrType->setEnabled(false);
        ui->m_editRelErr->setEnabled(false);
        ui->m_editAbsErr->setEnabled(false);
    }

    return;
}


void QDistanceSearchAddMultDlg::on_m_editOrigImp_editingFinished()
{
    ui->m_editOrigImp->setText(DistanceSearchValueCheck(ui->m_editOrigImp->text(), BEGINVAL_MAX, BEGINVAL_MIN, 3));
}

void QDistanceSearchAddMultDlg::on_m_editOrigAng_editingFinished()
{
    ui->m_editOrigAng->setText(DistanceSearchValueCheck(ui->m_editOrigAng->text(), BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
}

void QDistanceSearchAddMultDlg::on_m_editFaultCur_editingFinished()
{
    ui->m_editFaultCur->setText(DistanceSearchValueCheck(ui->m_editFaultCur->text(), FAULTIF_MAX, FAULTIF_MIN, 3));
}

void QDistanceSearchAddMultDlg::on_m_editFaultVol_editingFinished()
{
    ui->m_editFaultVol->setText(DistanceSearchValueCheck(ui->m_editFaultVol->text(), FAULTVF_MAX, FAULTVF_MIN, 3));
}

void QDistanceSearchAddMultDlg::on_m_editSearchAngBeg_editingFinished()
{
    ui->m_editSearchAngBeg->setText(DistanceSearchValueCheck(ui->m_editSearchAngBeg->text(), BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
}

void QDistanceSearchAddMultDlg::on_m_editSearchAngEnd_editingFinished()
{
    ui->m_editSearchAngEnd->setText(DistanceSearchValueCheck(ui->m_editSearchAngEnd->text(), ENDVALANG_MAX, ENDVALANG_MIN, 2));
}

void QDistanceSearchAddMultDlg::on_m_editAngStep_editingFinished()
{
    ui->m_editAngStep->setText(DistanceSearchValueCheck(ui->m_editAngStep->text(), BEGINVALANG_MAX, BEGINVALANG_MIN, 2));
}

void QDistanceSearchAddMultDlg::on_m_editSearchLen_editingFinished()
{
    ui->m_editSearchLen->setText(DistanceSearchValueCheck(ui->m_editSearchLen->text(), STEP_MAX, STEP_MIN, 3));
}

void QDistanceSearchAddMultDlg::on_m_editRelErr_editingFinished()
{
    ui->m_editRelErr->setText(DistanceSearchValueCheck(ui->m_editRelErr->text(), RELERR_MAX, RELERR_MIN, 3));
}

void QDistanceSearchAddMultDlg::on_m_editAbsErr_editingFinished()
{
    ui->m_editAbsErr->setText(DistanceSearchValueCheck(ui->m_editAbsErr->text(), ABSERR_MAX, ABSERR_MIN, 3));
}
