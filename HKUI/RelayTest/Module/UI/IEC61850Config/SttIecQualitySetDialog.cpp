#include "SttIecQualitySetDialog.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRates.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"

QSttIecQualitySetDialog::QSttIecQualitySetDialog(CIecCfg92Ch *pIecCfgSmv92Ch,QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pIecCfgSmv92Ch = pIecCfgSmv92Ch;
	m_pQualitySetGridLayout = NULL;
	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	InitUI();
	InitDatas();
	SetIecQualitySetDialogFont();

}

QSttIecQualitySetDialog::~QSttIecQualitySetDialog()
{
}

void QSttIecQualitySetDialog::InitUI()
{
	resize(560,280);
	this->setFixedWidth(560);
	this->setFixedHeight(280);

	CString strTemp;
	xlang_GetLangStrByFile(strTemp, _T("IEC_QualityParaSet"));
	//= _T("品质参数设置");
	setWindowTitle(strTemp);

	m_pQualitySetGridLayout = new QGridLayout;

	m_pValid_Label = new QLabel(g_sLangTxt_IEC_Validity ,this);
	m_pValid_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pValid_Label,"IEC_Validity", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pValid_Label, 0, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pValid_ComBox, 0, 1, 1, 1);

	m_pOverFlow_Label = new QLabel(g_sLangTxt_IEC_Overflow ,this);
	m_pOverFlow_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pOverFlow_Label, "IEC_Overflow", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pOverFlow_Label, 0, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pOverFlow_ComBox, 0, 3, 1, 1);

	m_pOutOfRange_Label = new QLabel(g_sLangTxt_IEC_OutOfRange ,this);
	m_pOutOfRange_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pOutOfRange_Label, "IEC_OutOfRange", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pOutOfRange_Label, 1, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pOutOfRange_ComBox, 1, 1, 1, 1);

	m_pBadRef_Label = new QLabel(g_sLangTxt_IEC_BadReference,this);
	m_pBadRef_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pBadRef_Label, "IEC_BadReference", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pBadRef_Label, 1, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pBadRef_ComBox, 1, 3, 1, 1);

	m_pOscilatory_Label = new QLabel(g_sLangTxt_IEC_Oscillatory,this);
	m_pOscilatory_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pOscilatory_Label, "IEC_Oscillatory", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pOscilatory_Label, 2, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pOscilatory_ComBox, 2, 1, 1, 1);

	m_pFailure_Label = new QLabel(g_sLangTxt_IEC_Failure,this);
	m_pFailure_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pFailure_Label, "IEC_Failure", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pFailure_Label, 2, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pFailure_ComBox, 2, 3, 1, 1);

	m_pOldData_Label = new QLabel(g_sLangTxt_IEC_OldData,this);
	m_pOldData_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pOldData_Label, "IEC_OldData", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pOldData_Label, 3, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pOldData_ComBox, 3, 1, 1, 1);

	m_pInconsistent_Label = new QLabel(g_sLangTxt_IEC_Inconsistent,this);
	m_pInconsistent_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pInconsistent_Label, "IEC_Inconsistent", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pInconsistent_Label, 3, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pInconsistent_ComBox, 3, 3, 1, 1);

	m_pInaccureate_Label = new QLabel(g_sLangTxt_IEC_Inaccurate,this);
	m_pInaccureate_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pInaccureate_Label, "IEC_Inaccurate", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pInaccureate_Label, 4, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pInaccureate_ComBox, 4, 1, 1, 1);

	m_pSource_Label = new QLabel(g_sLangTxt_Channel_Source,this);
	m_pSource_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pSource_Label, "Channel_Source", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pSource_Label, 4, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pSource_ComBox, 4, 3, 1, 1);

	m_pTest_Label = new QLabel(g_sLangTxt_Channel_Test,this);
	m_pTest_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pTest_Label, "Channel_Test", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pTest_Label, 5, 0, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pTest_ComBox, 5, 1, 1, 1);

	m_pOpb_Label = new QLabel(g_sLangTxt_IEC_Opb,this);
	m_pOpb_ComBox = new QScrollComboBox;
	xlang_SetLangStrToWidget(m_pOpb_Label, "IEC_Opb", XLang_Ctrls_QLabel);
	m_pQualitySetGridLayout->addWidget(m_pOpb_Label, 5, 2, 1, 1);
	m_pQualitySetGridLayout->addWidget(m_pOpb_ComBox, 5, 3, 1, 1);
	m_pQualitySetGridLayout->setVerticalSpacing(10);


	m_pModifyAllChs_Check = new QNumberCheckBox(this);
	xlang_SetLangStrToWidget(m_pModifyAllChs_Check, "IEC_ModifyAllChs", XLang_Ctrls_QCheckBox);
	//m_pModifyAllChs_Check->setText(tr("修改全部通道"));
	m_pValue_LineEdit = new QIecLineEdit(QIecLineEdit::HEX_TEXT,_T("0000"));
	m_pValue_LineEdit->setText(_T("0X0000"));
	m_pDirectSet_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pDirectSet_PushButton, "IEC_DirectSet", XLang_Ctrls_QPushButton);
	//m_pDirectSet_PushButton->setText(tr("直接设置"));

	CString strName;
	xlang_GetLangStrByFile(strName,"IEC_good");
	m_pValid_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_invalid");
	m_pValid_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_reserved");
	m_pValid_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_questionable");	
	m_pValid_ComBox->addItem(strName);
	/*m_pValid_ComBox->addItem(tr("00:好"));
	m_pValid_ComBox->addItem(tr("01:无效"));
	m_pValid_ComBox->addItem(tr("10:保留"));
	m_pValid_ComBox->addItem(tr("11:可疑"));*/

	xlang_GetLangStrByFile(strName,"IEC_nooverflow");
	m_pOverFlow_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_overflow");
	m_pOverFlow_ComBox->addItem(strName);
	/*m_pOverFlow_ComBox->addItem(tr("0:无溢出"));
	m_pOverFlow_ComBox->addItem(tr("1:溢出"));*/

	xlang_GetLangStrByFile(strName,"IEC_normal");
	m_pOutOfRange_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_outofrange");
	m_pOutOfRange_ComBox->addItem(strName);
	/*m_pOutOfRange_ComBox->addItem(tr("0:正常"));
	m_pOutOfRange_ComBox->addItem(tr("1:超值域"));*/

	xlang_GetLangStrByFile(strName,"IEC_normal");
	m_pBadRef_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_badreference");
	m_pBadRef_ComBox->addItem(strName);
	/*m_pBadRef_ComBox->addItem(tr("0:正常"));
	m_pBadRef_ComBox->addItem(tr("1:坏基准值"));*/

	xlang_GetLangStrByFile(strName,"IEC_noOscillatory");
	m_pOscilatory_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_oscillatory");
	m_pOscilatory_ComBox->addItem(strName);
	/*m_pOscilatory_ComBox->addItem(tr("0:无抖动"));
	m_pOscilatory_ComBox->addItem(tr("1:有抖动"));*/

	xlang_GetLangStrByFile(strName,"IEC_nofailure");
	m_pFailure_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_failure");
	m_pFailure_ComBox->addItem(strName);
	/*m_pFailure_ComBox->addItem(tr("0:无故障"));
	m_pFailure_ComBox->addItem(tr("1:有故障"));*/

	xlang_GetLangStrByFile(strName,"IEC_noovertime");
	m_pOldData_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_overtime");
	m_pOldData_ComBox->addItem(strName);
	/*m_pOldData_ComBox->addItem(tr("0:无超时"));
	m_pOldData_ComBox->addItem(tr("1:数据超时"));*/

	xlang_GetLangStrByFile(strName,"IEC_noinconsistent");
	m_pInconsistent_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_inconsistent");
	m_pInconsistent_ComBox->addItem(strName);
	/*m_pInconsistent_ComBox->addItem(tr("0:一致"));
	m_pInconsistent_ComBox->addItem(tr("1:不一致"));*/

	xlang_GetLangStrByFile(strName,"IEC_accurate");
	m_pInaccureate_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_inaccurate");
	m_pInaccureate_ComBox->addItem(strName);
	/*m_pInaccureate_ComBox->addItem(tr("0:精确"));
	m_pInaccureate_ComBox->addItem(tr("1:不精确"));*/

	xlang_GetLangStrByFile(strName,"IEC_process");
	m_pSource_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_substituted");
	m_pSource_ComBox->addItem(strName);
	/*m_pSource_ComBox->addItem(tr("0:过程"));
	m_pSource_ComBox->addItem(tr("1:被取代"));*/

	xlang_GetLangStrByFile(strName,"IEC_run");
	m_pTest_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_test");
	m_pTest_ComBox->addItem(strName);
	/*m_pTest_ComBox->addItem(tr("0:运行"));
	m_pTest_ComBox->addItem(tr("1:测试"));*/

	xlang_GetLangStrByFile(strName,"IEC_nolock");
	m_pOpb_ComBox->addItem(strName);
	xlang_GetLangStrByFile(strName,"IEC_lock");
	m_pOpb_ComBox->addItem(strName);
	/*m_pOpb_ComBox->addItem(tr("0:不闭锁"));
	m_pOpb_ComBox->addItem(tr("1:闭锁"));*/


	m_pOK_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	m_pCancel_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);
	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addWidget(m_pModifyAllChs_Check);
	m_pOK_CancelHLayout->addWidget(m_pValue_LineEdit);
	m_pOK_CancelHLayout->addWidget(m_pDirectSet_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addSpacing(20);
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
// 	m_pOK_CancelHLayout->addStretch();
// 	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addLayout(m_pQualitySetGridLayout);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
	connect(m_pValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_EditValueClicked()));
	connect(m_pDirectSet_PushButton, SIGNAL(clicked()), this, SLOT(slot_DirectSetClicked()));
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttIecQualitySetDialog::SetIecQualitySetDialogFont()
{
	m_pValid_ComBox->setFont(*g_pSttGlobalFont);
	m_pOverFlow_ComBox->setFont(*g_pSttGlobalFont);
	m_pOutOfRange_ComBox->setFont(*g_pSttGlobalFont);
	m_pBadRef_ComBox->setFont(*g_pSttGlobalFont);
	m_pOscilatory_ComBox->setFont(*g_pSttGlobalFont);
	m_pFailure_ComBox->setFont(*g_pSttGlobalFont);
	m_pOldData_ComBox->setFont(*g_pSttGlobalFont);
	m_pInconsistent_ComBox->setFont(*g_pSttGlobalFont);
	m_pInaccureate_ComBox->setFont(*g_pSttGlobalFont);
	m_pSource_ComBox->setFont(*g_pSttGlobalFont);
	m_pTest_ComBox->setFont(*g_pSttGlobalFont);
	m_pOpb_ComBox->setFont(*g_pSttGlobalFont);

	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pDirectSet_PushButton->setFont(*g_pSttGlobalFont);
	m_pValue_LineEdit->setFont(*g_pSttGlobalFont);
	m_pOpb_Label->setFont(*g_pSttGlobalFont);
	m_pTest_Label->setFont(*g_pSttGlobalFont);
	m_pSource_Label->setFont(*g_pSttGlobalFont);
	m_pInaccureate_Label->setFont(*g_pSttGlobalFont);
	m_pInconsistent_Label->setFont(*g_pSttGlobalFont);
	m_pOldData_Label->setFont(*g_pSttGlobalFont);
	m_pFailure_Label->setFont(*g_pSttGlobalFont);
	m_pOscilatory_Label->setFont(*g_pSttGlobalFont);
	m_pBadRef_Label->setFont(*g_pSttGlobalFont);
	m_pOutOfRange_Label->setFont(*g_pSttGlobalFont);
	m_pOverFlow_Label->setFont(*g_pSttGlobalFont);
	m_pValid_Label->setFont(*g_pSttGlobalFont);
	m_pModifyAllChs_Check->setFont(*g_pSttGlobalFont);
}

void QSttIecQualitySetDialog::InitDatas()
{
	CString strValue;
	strValue.Format(_T("0X%04X"),m_pIecCfgSmv92Ch->m_nQuality);
	m_pValue_LineEdit->setText(strValue);
	ShowQuality();
}


void QSttIecQualitySetDialog::SaveData()
{
	DWORD dwValue = GetCurrQuality();
	 m_pIecCfgSmv92Ch->m_nQuality = dwValue;

	if (m_pModifyAllChs_Check->GetValue())
	{
		CIecCfgChsBase *pCfgChs = (CIecCfgChsBase*)m_pIecCfgSmv92Ch->GetParent();
		CIecCfg92Ch *p92Ch = NULL;
		POS pos = pCfgChs->GetHeadPosition();

		while (pos != NULL)
		{
			p92Ch = (CIecCfg92Ch *)pCfgChs->GetNext(pos);
			p92Ch->m_nQuality = dwValue;
		}
	}
}

void QSttIecQualitySetDialog::slot_EditValueClicked()
{
	QString strValue = m_pValue_LineEdit->text();
	GetEngWidgetBoard_DigitData(strValue,parentWidget()->parentWidget()->parentWidget());
	m_pValue_LineEdit->setText(strValue);
}

void QSttIecQualitySetDialog::slot_DirectSetClicked()
{
	ShowQuality();
}

void QSttIecQualitySetDialog::slot_OKClicked()
{
	SaveData();
	this->accept();
}

void QSttIecQualitySetDialog::slot_CancelClicked()
{
	close();
}

void QSttIecQualitySetDialog::ShowQuality()
{
	CIecCfg92ChQuality oQuality;
	bool bRet = FALSE;
	DWORD dwValue = m_pValue_LineEdit->text().toUInt(&bRet,16);
	oQuality.SetQuality(dwValue);
	m_pValid_ComBox->setCurrentIndex(oQuality.m_nValidity);
	m_pOverFlow_ComBox->setCurrentIndex(oQuality.m_nOverflow);
	m_pOutOfRange_ComBox->setCurrentIndex(oQuality.m_nOutOfRange);
	m_pBadRef_ComBox->setCurrentIndex(oQuality.m_nBadReference);
	m_pOscilatory_ComBox->setCurrentIndex(oQuality.m_nOscillation);
	m_pFailure_ComBox->setCurrentIndex(oQuality.m_nFailure);
	m_pOldData_ComBox->setCurrentIndex(oQuality.m_nOldData);
	m_pInconsistent_ComBox->setCurrentIndex(oQuality.m_nInconsistent);
	m_pInaccureate_ComBox->setCurrentIndex(oQuality.m_nInaccurate);
	m_pSource_ComBox->setCurrentIndex(oQuality.m_nSource);
	m_pTest_ComBox->setCurrentIndex(oQuality.m_nTest);
	m_pOpb_ComBox->setCurrentIndex(oQuality.m_nOPB);
}

DWORD QSttIecQualitySetDialog::GetCurrQuality()
{
	CIecCfg92ChQuality oQuality;

	oQuality.m_nValidity = m_pValid_ComBox->currentIndex();
	oQuality.m_nOverflow = m_pOverFlow_ComBox->currentIndex();
	oQuality.m_nOutOfRange = m_pOutOfRange_ComBox->currentIndex();
	oQuality.m_nBadReference = m_pBadRef_ComBox->currentIndex();
	oQuality.m_nOscillation = m_pOscilatory_ComBox->currentIndex();
	oQuality.m_nFailure = m_pFailure_ComBox->currentIndex();
	oQuality.m_nOldData = m_pOldData_ComBox->currentIndex();
	oQuality.m_nInconsistent = m_pInconsistent_ComBox->currentIndex();
	oQuality.m_nInaccurate = m_pInaccureate_ComBox->currentIndex();
	oQuality.m_nSource = m_pSource_ComBox->currentIndex();
	oQuality.m_nTest = m_pTest_ComBox->currentIndex();
	oQuality.m_nOPB = m_pOpb_ComBox->currentIndex();

	DWORD dwValue = oQuality.GetQuality();
	return dwValue;
}

