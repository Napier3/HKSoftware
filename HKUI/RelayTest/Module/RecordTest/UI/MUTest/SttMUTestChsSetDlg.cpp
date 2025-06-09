#include "SttMUTestChsSetDlg.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../XLangResource_Native.h"
#include "SttIecRecordCbInterface.h"
#include "../../../UI/SttTestCntrFrameAPI.h"
#include "../../../../../Module/OSInterface/QT/XMessageBox.h"


QSttMUTestChsSetDlg::QSttMUTestChsSetDlg(QWidget *parent,BOOL bIsFT3MUTest)
	: QDialog(parent)
{
	m_bIsFT3MUTest = bIsFT3MUTest;
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pMain_VLayout = NULL;
	m_pRadioHLayout = NULL;
//	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pPrimaryValueRadioBtn = NULL;
	m_pSecondValueRadioBtn = NULL;
	m_pSttCapAnalysisConfig = NULL;
	m_pLeft_PrimRateGrid = NULL;
	m_pRight_PrimRateGrid = NULL;
	m_pIecCfgSmvInChsGrid = NULL;
	m_pIecCfgPrimRatesIn_External = NULL;
	m_pIecCfgPrimRatesIn_Internal = NULL;
	m_pChNumLabel = NULL;
	m_pChNumLineEdit = NULL;
	m_pCfgChs_External = NULL;
	m_pCfgChs_Internal = NULL;
	m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_NO;

	m_pBtnClickedHLayout = NULL;
	m_pSparcer_BtnClick = NULL;
	m_pClickedAll_PushButton = NULL;
	m_pDisclickedAll_PushButton = NULL;
	m_pInvert_PushButton = NULL;


	InitUI();
	SetMUTestChsSetDlgEnabled();
}

QSttMUTestChsSetDlg::~QSttMUTestChsSetDlg()
{
	m_oVolPrimRateList.RemoveAll();
	m_oCurPrimRateList.RemoveAll();

	if (m_pIecCfgPrimRatesIn_Internal != NULL)
	{
		delete m_pIecCfgPrimRatesIn_Internal;
		m_pIecCfgPrimRatesIn_Internal = NULL;
	}

	if (m_pCfgChs_Internal != NULL)
	{
		delete m_pCfgChs_Internal;
		m_pCfgChs_Internal = NULL;
	}
}

void QSttMUTestChsSetDlg::InitUI()
{
	resize(1024,600);

	//2024-10-18 wuxinyi 应北京需求Dialog可伸缩
#ifndef _PSX_QT_WINDOWS_
	this->setFixedWidth(1024);
	this->setFixedHeight(600);
#endif

	CString strTemp;
	strTemp = /*_T("接收通道设置")*/g_sLangTxt_Gradient_RecvChannel; //lcq
	//setWindowTitle(strTemp/*tr("系统设置")*/);
    setWindowTitle(strTemp); //lcq
	m_pPT_CT_RatesHLayout = new QHBoxLayout;
	m_pBtnClickedHLayout = new QHBoxLayout;

	if (m_bIsFT3MUTest)
	{
		m_pIecCfgSmvInChsGrid = new CIecCfgSmvFT3InChsGrid(this);
	} 
	else
	{
		m_pIecCfgSmvInChsGrid = new CIecCfgSmv92InChsGrid(this);
	}

	m_pIecCfgSmvInChsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont/*m_oIecFont*/); 
	m_pIecCfgSmvInChsGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgSmvInChsGrid->InitGrid();

	m_pLeft_PrimRateGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_PT,this);
	m_pLeft_PrimRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont/*m_oIecFont*/); // 2022-10-22 sy m_oIecFont修改为*g_pSttGlobalFont
	m_pLeft_PrimRateGrid->setFont(*g_pSttGlobalFont);
	m_pRight_PrimRateGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_CT,this);
	m_pRight_PrimRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pRight_PrimRateGrid->setFont(*g_pSttGlobalFont);
	m_pLeft_PrimRateGrid->InitGrid();
	m_pRight_PrimRateGrid->InitGrid();

	strTemp = /*_T("PT/CT变比")*/g_sLangTxt_Gradient_RatioPCT; //lcq
	m_pRateGroupBox = new QGroupBox(strTemp);

	//2023/9/7 wjs 添加按钮
	m_pSparcer_BtnClick= new QSpacerItem(0,30,QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_pClickedAll_PushButton = new QPushButton(this);
	m_pDisclickedAll_PushButton = new QPushButton(this);
	m_pInvert_PushButton = new QPushButton(this);

	m_pClickedAll_PushButton->setText(/*"全选"*/g_sLangTxt_SelAll);
	m_pDisclickedAll_PushButton->setText(/*"全不选"*/g_sLangTxt_SelNone);
	m_pInvert_PushButton->setText(/*"反选"*/g_sLangTxt_Gradient_Inverse);
	m_pClickedAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pDisclickedAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pInvert_PushButton->setFont(*g_pSttGlobalFont);

	m_pBtnClickedHLayout->setSpacing(10);//控件之间间隔 

//	m_pClickedAll_PushButton->setFixedSize(50, 30);
//	m_pDisclickedAll_PushButton->setFixedSize(50, 30);
//	m_pInvert_PushButton->setFixedSize(50, 30);
	m_pBtnClickedHLayout->addWidget(m_pClickedAll_PushButton);
	m_pBtnClickedHLayout->addWidget(m_pDisclickedAll_PushButton);
	m_pBtnClickedHLayout->addWidget(m_pInvert_PushButton);
	m_pBtnClickedHLayout->addItem(m_pSparcer_BtnClick);
	

	m_pPT_CT_RatesHLayout->addWidget(m_pLeft_PrimRateGrid);
	m_pPT_CT_RatesHLayout->addWidget(m_pRight_PrimRateGrid);
	m_pRateGroupBox->setLayout(m_pPT_CT_RatesHLayout);

	strTemp = /*_T("通道数")*/ g_sLangTxt_IEC_ChannelNumber; //lcq
	m_pChNumLabel = new QLabel(strTemp);
	strTemp = _T("--");
	m_pChNumLineEdit = new QLineEdit(strTemp);
	m_pChNumLineEdit->setEnabled(false);
	m_pChNumLineEdit->setFixedWidth(50);
	m_pChNumLineEdit->setAlignment(Qt::AlignCenter);
	strTemp = _T("显示一次值");
	m_pPrimaryValueRadioBtn = new QRadioButton(strTemp);
	xlang_SetLangStrToWidget(m_pPrimaryValueRadioBtn, "Smv_ShowOneValue", XLang_Ctrls_QRadioButton);
	strTemp = _T("显示二次值");
	m_pSecondValueRadioBtn = new QRadioButton(strTemp);
	xlang_SetLangStrToWidget(m_pSecondValueRadioBtn, "Smv_ShowTwoValue", XLang_Ctrls_QRadioButton);

	m_pRadioHLayout = new QHBoxLayout;

	m_pOK_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	m_pCancel_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);

	m_pRadioHLayout->addWidget(m_pChNumLabel);
	m_pRadioHLayout->addWidget(m_pChNumLineEdit);
	m_pRadioHLayout->addWidget(m_pPrimaryValueRadioBtn);
	m_pRadioHLayout->addWidget(m_pSecondValueRadioBtn);
	m_pRadioHLayout->addStretch();
	m_pRadioHLayout->addWidget(m_pOK_PushButton);
	m_pRadioHLayout->addWidget(m_pCancel_PushButton);

	//main
	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pIecCfgSmvInChsGrid,3);
	m_pMain_VLayout->addLayout(m_pBtnClickedHLayout,1);	
 	m_pMain_VLayout->addWidget(m_pRateGroupBox,1);
	m_pMain_VLayout->addLayout(m_pRadioHLayout,1);

	if (m_bIsFT3MUTest)
	{
		m_pRateGroupBox->setHidden(true);
		m_pPrimaryValueRadioBtn->setHidden(true);
		m_pSecondValueRadioBtn->setHidden(true);
	} 
}

void QSttMUTestChsSetDlg::InitData(CIecCfgDataBase *pIecCfgData,CCapAnalysisConfig *pCapAnalysisConfig,CIecCfgPrimRatesIn *pIecCfgPrimRatesIn)
{
	m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_NO;

	if (pIecCfgData != NULL)
	{
		m_pCfgChs_External = pIecCfgData->m_pCfgChs;
		m_pCfgChs_Internal = (CIecCfgChsBase*)m_pCfgChs_External->Clone();
	}

	m_pSttCapAnalysisConfig = pCapAnalysisConfig;
	m_pIecCfgPrimRatesIn_External = pIecCfgPrimRatesIn;
	m_pIecCfgPrimRatesIn_Internal = (CIecCfgPrimRatesIn*)m_pIecCfgPrimRatesIn_External->Clone();
	m_oVolPrimRateList.RemoveAll();
	m_oCurPrimRateList.RemoveAll();

	POS pos = m_pIecCfgPrimRatesIn_Internal->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = m_pIecCfgPrimRatesIn_Internal->GetNext(pos);

		if (pCurrObj->m_strID.Find("U") != -1)
		{
			if (m_oVolPrimRateList.GetCount()<2)
			{
				m_oVolPrimRateList.AddTail(pCurrObj);
			}
		} 
		else
		{
			if (m_oCurPrimRateList.GetCount()<2)
			{
				m_oCurPrimRateList.AddTail(pCurrObj);
			}
		}
	}

	m_pLeft_PrimRateGrid->ShowDatas(&m_oVolPrimRateList);
	m_pRight_PrimRateGrid->ShowDatas(&m_oCurPrimRateList);

	if (m_pSttCapAnalysisConfig->m_nShowPrimaryValue)
	{
		m_pPrimaryValueRadioBtn->setChecked(1);
	} 
	else
	{
		m_pSecondValueRadioBtn->setChecked(1);
	}

	if (m_pCfgChs_Internal != NULL)
	{
		CString strChNum;
		strChNum.Format(_T("%d"),m_pCfgChs_Internal->GetCount());
		m_pChNumLineEdit->setText(strChNum);
		m_pIecCfgSmvInChsGrid->ShowDatas(m_pCfgChs_Internal);
	}

	//设置按钮触发事件
	connect(m_pClickedAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_BtnClickedAllClicked()));
	connect(m_pDisclickedAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_BtnDisClickedAllClicked()));
	connect(m_pInvert_PushButton, SIGNAL(clicked()), this, SLOT(slot_BtnInvertClicked()));

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttMUTestChsSetDlg::SetIsFT3MUTest(BOOL bIsFT3MUTest)
{
	m_bIsFT3MUTest = bIsFT3MUTest;
}

BOOL QSttMUTestChsSetDlg::IsAppChIDEqual(const CString &strAppChID1,const CString &strAppChID2)
{
	if (strAppChID1 == strAppChID2)
	{
		return TRUE;
	}

	CString strAppChID1_new,strAppChID2_new;
	strAppChID1_new = strAppChID1;
	strAppChID2_new = strAppChID2;
	strAppChID1_new.Replace(_T("zero"),_T("none"));

	return (strAppChID1_new == strAppChID2_new);

}

void QSttMUTestChsSetDlg::SaveData()
{
	if (m_pSttCapAnalysisConfig->m_nShowPrimaryValue != m_pPrimaryValueRadioBtn->isChecked())
	{
		m_pSttCapAnalysisConfig->m_nShowPrimaryValue = m_pPrimaryValueRadioBtn->isChecked();
		m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
	}

	POS pos = m_pIecCfgPrimRatesIn_Internal->GetHeadPosition();
	CIecCfgPrimRate *pCurrObj_Internal = NULL;
	CIecCfgPrimRate *pCurrObj_External = NULL;

	while(pos)
	{
		pCurrObj_Internal = (CIecCfgPrimRate*)m_pIecCfgPrimRatesIn_Internal->GetNext(pos);
		pCurrObj_External = (CIecCfgPrimRate*)m_pIecCfgPrimRatesIn_External->FindByID(pCurrObj_Internal->m_strID);

		if (pCurrObj_External != NULL)
		{
			if (fabs(pCurrObj_Internal->m_fPrimValue - pCurrObj_External->m_fPrimValue)>0.0001f)
			{
				pCurrObj_External->m_fPrimValue = pCurrObj_Internal->m_fPrimValue;
				m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
			}

			if (fabs(pCurrObj_Internal->m_fSecondValue - pCurrObj_External->m_fSecondValue)>0.0001f)
			{
				pCurrObj_External->m_fSecondValue = pCurrObj_Internal->m_fSecondValue;
				m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
			}
		}
	}

	if (m_pCfgChs_Internal != NULL)
	{
		BOOL bChMapTypeChanged = FALSE;

		if (m_pCfgChs_Internal->GetClassID() == CFGCLASSID_CIECCFGCHS6044)
		{
			CIecCfg6044CommonChIn *pIecCfg6044CommonChIn_Internal = NULL;
			CIecCfg6044CommonChIn *pIecCfg6044CommonChIn_External = NULL;

			pos = m_pCfgChs_Internal->GetHeadPosition();

			while(pos)
			{
				pIecCfg6044CommonChIn_Internal = (CIecCfg6044CommonChIn*)m_pCfgChs_Internal->GetNext(pos);
				pIecCfg6044CommonChIn_External = (CIecCfg6044CommonChIn*)m_pCfgChs_External->FindByID(pIecCfg6044CommonChIn_Internal->m_strID);

				if (pIecCfg6044CommonChIn_External != NULL)
				{
					if (pIecCfg6044CommonChIn_Internal->m_nAccuratyLevel != pIecCfg6044CommonChIn_External->m_nAccuratyLevel)
					{
						pIecCfg6044CommonChIn_External->m_nAccuratyLevel = pIecCfg6044CommonChIn_Internal->m_nAccuratyLevel;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg6044CommonChIn_Internal->m_strName != pIecCfg6044CommonChIn_External->m_strName)
					{
						pIecCfg6044CommonChIn_External->m_strName = pIecCfg6044CommonChIn_Internal->m_strName;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg6044CommonChIn_Internal->m_nUseFlag != pIecCfg6044CommonChIn_External->m_nUseFlag)
					{
						pIecCfg6044CommonChIn_External->m_nUseFlag = pIecCfg6044CommonChIn_Internal->m_nUseFlag;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg6044CommonChIn_Internal->m_strChType != pIecCfg6044CommonChIn_External->m_strChType)
					{
						pIecCfg6044CommonChIn_External->m_strChType = pIecCfg6044CommonChIn_Internal->m_strChType;
						bChMapTypeChanged = TRUE;
					}

					if (!IsAppChIDEqual(pIecCfg6044CommonChIn_Internal->m_strAppChID , pIecCfg6044CommonChIn_External->m_strAppChID))
					{
						pIecCfg6044CommonChIn_External->m_strAppChID = pIecCfg6044CommonChIn_Internal->m_strAppChID;
						bChMapTypeChanged = TRUE;
					}
					//pIecCfg6044CommonChIn_Internal->CopyOwn(pIecCfg6044CommonChIn_External);
				}
			}
		} 
		else
		{
			CIecCfg92ChIn *pIecCfg92Ch_Internal = NULL;
			CIecCfg92ChIn *pIecCfg92Ch_External = NULL;

			pos = m_pCfgChs_Internal->GetHeadPosition();

			while(pos)
			{
				pIecCfg92Ch_Internal = (CIecCfg92ChIn*)m_pCfgChs_Internal->GetNext(pos);
				pIecCfg92Ch_External = (CIecCfg92ChIn*)m_pCfgChs_External->FindByID(pIecCfg92Ch_Internal->m_strID);

				if (pIecCfg92Ch_External != NULL)
				{
					if (pIecCfg92Ch_Internal->m_nAccuratyLevel != pIecCfg92Ch_External->m_nAccuratyLevel)
					{
						pIecCfg92Ch_External->m_nAccuratyLevel = pIecCfg92Ch_Internal->m_nAccuratyLevel;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg92Ch_Internal->m_strName != pIecCfg92Ch_External->m_strName)
					{
						pIecCfg92Ch_External->m_strName = pIecCfg92Ch_Internal->m_strName;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg92Ch_Internal->m_nUseFlag != pIecCfg92Ch_External->m_nUseFlag)
					{
						pIecCfg92Ch_External->m_nUseFlag = pIecCfg92Ch_Internal->m_nUseFlag;
						m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc;
					}

					if (pIecCfg92Ch_Internal->m_strChType != pIecCfg92Ch_External->m_strChType)
					{
						pIecCfg92Ch_External->m_strChType = pIecCfg92Ch_Internal->m_strChType;
						bChMapTypeChanged = TRUE;
					}

					if (!IsAppChIDEqual(pIecCfg92Ch_Internal->m_strAppChID , pIecCfg92Ch_External->m_strAppChID))
					{
						pIecCfg92Ch_External->m_strAppChID = pIecCfg92Ch_Internal->m_strAppChID;
						bChMapTypeChanged = TRUE;
					}
					//pIecCfg92Ch_Internal->CopyOwn(pIecCfg92Ch_External);
				}
			}
		}

		if (bChMapTypeChanged)
		{
			m_nParasModifyType = STT_MUTEST_CHSSET_MODIFY_TYPE_ChTypeMap;
		}
	}
}

void QSttMUTestChsSetDlg::slot_OKClicked()
{
	if (stt_Frame_IsTestStarted())
	{
		CString strMsgText;
		strMsgText = _T("测试过程中不支持修改接收通道内容.");
		CXMessageBox::information(this,/* tr("提示")*/g_sLangTxt_Message,strMsgText);
		return;
	}

	SaveData();
	accept();
}

void QSttMUTestChsSetDlg::slot_CancelClicked()
{
	close();
}

void QSttMUTestChsSetDlg::slot_BtnClickedAllClicked()
{
	if (m_pCfgChs_Internal != NULL)
	{
		CIecCfgDataChBase *pIecCfgChBase_Internal = NULL;
		POS pos = m_pCfgChs_Internal->GetHeadPosition();

		while(pos)
		{
			pIecCfgChBase_Internal = (CIecCfgDataChBase*)m_pCfgChs_Internal->GetNext(pos);
			pIecCfgChBase_Internal->m_nUseFlag = 1;
		}
		
		CString strChNum;
		strChNum.Format(_T("%d"),m_pCfgChs_Internal->GetCount());
		m_pChNumLineEdit->setText(strChNum);
		m_pIecCfgSmvInChsGrid->ShowDatas(m_pCfgChs_Internal);
	}
}

void QSttMUTestChsSetDlg::slot_BtnDisClickedAllClicked()
{
	if (m_pCfgChs_Internal != NULL)
	{

		CIecCfgDataChBase *pIecCfgChBase_Internal = NULL;
		POS pos = m_pCfgChs_Internal->GetHeadPosition();

		while(pos)
		{
			pIecCfgChBase_Internal = (CIecCfgDataChBase*)m_pCfgChs_Internal->GetNext(pos);
			pIecCfgChBase_Internal->m_nUseFlag = 0;

		}

		CString strChNum;
		strChNum.Format(_T("%d"),m_pCfgChs_Internal->GetCount());
		m_pChNumLineEdit->setText(strChNum);
		m_pIecCfgSmvInChsGrid->ShowDatas(m_pCfgChs_Internal);
	}
}

void QSttMUTestChsSetDlg::slot_BtnInvertClicked()
{
	if (m_pCfgChs_Internal != NULL)
	{

		CIecCfgDataChBase *pIecCfgChBase_Internal = NULL;
		POS pos = m_pCfgChs_Internal->GetHeadPosition();

		while(pos)
		{
			pIecCfgChBase_Internal = (CIecCfgDataChBase*)m_pCfgChs_Internal->GetNext(pos);
			if(pIecCfgChBase_Internal->m_nUseFlag == 1)
			{
				pIecCfgChBase_Internal->m_nUseFlag =0;
			}
			else
			{
				pIecCfgChBase_Internal->m_nUseFlag = 1;
			}
		}

		CString strChNum;
		strChNum.Format(_T("%d"),m_pCfgChs_Internal->GetCount());
		m_pChNumLineEdit->setText(strChNum);
		m_pIecCfgSmvInChsGrid->ShowDatas(m_pCfgChs_Internal);
	}
}

void QSttMUTestChsSetDlg::SetMUTestChsSetDlgEnabled()
{
	if (stt_Frame_IsTestStarted())
	{
		m_pIecCfgSmvInChsGrid->setEnabled(false);
		m_pLeft_PrimRateGrid->setEnabled(false);
		m_pRight_PrimRateGrid->setEnabled(false);
		m_pChNumLabel->setEnabled(false);
		m_pChNumLineEdit->setEnabled(false);
		m_pPrimaryValueRadioBtn->setEnabled(false);
		m_pSecondValueRadioBtn->setEnabled(false);

		m_pClickedAll_PushButton->setEnabled(false);
		m_pDisclickedAll_PushButton->setEnabled(false);
		m_pInvert_PushButton->setEnabled(false);
		m_pOK_PushButton->setEnabled(false);
		
	}
	else
	{
		m_pIecCfgSmvInChsGrid->setEnabled(true);
		m_pLeft_PrimRateGrid->setEnabled(true);
		m_pRight_PrimRateGrid->setEnabled(true);
		m_pChNumLabel->setEnabled(true);
		m_pChNumLineEdit->setEnabled(true);
		m_pPrimaryValueRadioBtn->setEnabled(true);
		m_pSecondValueRadioBtn->setEnabled(true);

		m_pClickedAll_PushButton->setEnabled(true);
		m_pDisclickedAll_PushButton->setEnabled(true);
		m_pInvert_PushButton->setEnabled(true);
		m_pOK_PushButton->setEnabled(true);
	}
}


