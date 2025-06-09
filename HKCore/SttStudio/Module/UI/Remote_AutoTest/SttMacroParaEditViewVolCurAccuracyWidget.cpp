#include "SttMacroParaEditViewVolCurAccuracyWidget.h"
#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckableGroupBox.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewVolCurAccuracyWidget::QSttMacroParaEditViewVolCurAccuracyWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pMacroTestValues = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	OpenBinBoutMapXml();
	SetDatas(NULL);
}

QSttMacroParaEditViewVolCurAccuracyWidget::~QSttMacroParaEditViewVolCurAccuracyWidget()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear(); 

	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		delete m_pAllLineEditList.at(i); 
	}
	m_pAllLineEditList.clear(); 
	
	for (int i = 0; i < m_pGroupBoxList.size(); ++i)
	{
		delete m_pGroupBoxList.at(i); 
	}
	m_pGroupBoxList.clear(); 
}

void QSttMacroParaEditViewVolCurAccuracyWidget::InitUI()
{
	CString strText ,strID;
	QStringList oCurList,oVolList;
	oVolList << _T("20%")<< _T("40%")<< _T("60%")<< _T("80%")<< _T("100%")<< _T("120%");
	oCurList << _T("0%") << _T("5%")<< _T("20%")<< _T("40%")<< _T("60%")<< _T("80%")<< _T("100%")<< _T("120%");
	QSttCheckableGroupBox *pPhaseVolGroupBox = new QSttCheckableGroupBox();
	QSttCheckableGroupBox *pPhaseCurGroupBox = new QSttCheckableGroupBox();
	pPhaseVolGroupBox->setObjectName(_T("U_Check"));
	pPhaseCurGroupBox->setObjectName(_T("I_Check"));
// 	GetGroupBoxCheckable(pPhaseVolGroupBox,_T("U_Check"));
// 	GetGroupBoxCheckable(pPhaseCurGroupBox,_T("I_Check"));
	connect(pPhaseVolGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(pPhaseCurGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));

	//相电压精度-测试项选择
	m_pGroupBoxList.append(pPhaseVolGroupBox);

	pPhaseVolGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pPhaseVolLayout = new QGridLayout();
	for (int i = 0; i < oVolList.size(); ++i)
	{
		QSttCheckBox* pVolCheckBox = new QSttCheckBox;
		pVolCheckBox->setFont(*g_pSttGlobalFont);
		strText = oVolList.at(i);
		pVolCheckBox->setText(strText);
		strText = ProcessString(strText);
		strID = _T("U_Rate_") + strText + _T("_Check");
		pVolCheckBox->setObjectName(strID);
		//GetCheckBoxValue(pVolCheckBox,strID);
		pPhaseVolLayout->addWidget(pVolCheckBox,0,i,1,1);
		m_pAllCheckBoxList.append(pVolCheckBox);
		connect(pVolCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}

	QSttCheckBox* pPhaseVolCusCheckBox1 = new QSttCheckBox;
	QSttCheckBox* pPhaseVolCusCheckBox2 = new QSttCheckBox;
	QLineEdit *pPhaseVolCusLineEdit1 = new QLineEdit;
	QLineEdit *pPhaseVolCusLineEdit2 = new QLineEdit;
	QLabel *pLabel1 = new QLabel;
	QLabel *pLabel2 = new QLabel;
	strText = _T("%");
	pLabel1->setText(strText);
	pLabel2->setText(strText);
	pPhaseVolCusCheckBox1->setObjectName(QString::fromUtf8("U_Custom1_Check"));
	pPhaseVolCusLineEdit1->setObjectName(QString::fromUtf8("U_Custom1"));
	pPhaseVolCusCheckBox2->setObjectName(QString::fromUtf8("U_Custom2_Check"));
	pPhaseVolCusLineEdit2->setObjectName(QString::fromUtf8("U_Custom2"));

// 	GetCheckBoxValue(pPhaseVolCusCheckBox1,_T("U_Custom1_Check"));
// 	GetCheckBoxValue(pPhaseVolCusCheckBox2,_T("U_Custom2_Check"));
// 	GetLineEditValue(pPhaseVolCusLineEdit1,_T("U_Custom1"));
// 	GetLineEditValue(pPhaseVolCusLineEdit2,_T("U_Custom2"));

	UpdateLineEditEnable(pPhaseVolCusCheckBox1,pPhaseVolCusLineEdit1);
	UpdateLineEditEnable(pPhaseVolCusCheckBox2,pPhaseVolCusLineEdit2);

	pPhaseVolCusCheckBox1->setFont(*g_pSttGlobalFont);
	pPhaseVolCusCheckBox2->setFont(*g_pSttGlobalFont);
	pPhaseVolCusLineEdit1->setFont(*g_pSttGlobalFont);
	pPhaseVolCusLineEdit2->setFont(*g_pSttGlobalFont);
	pLabel1->setFont(*g_pSttGlobalFont);
	pLabel2->setFont(*g_pSttGlobalFont);

	m_pAllCheckBoxList.append(pPhaseVolCusCheckBox1);
	m_pAllCheckBoxList.append(pPhaseVolCusCheckBox2);
	m_pAllLineEditList.append(pPhaseVolCusLineEdit1);
	m_pAllLineEditList.append(pPhaseVolCusLineEdit2);

	connect(pPhaseVolCusCheckBox1, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pPhaseVolCusCheckBox2, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pPhaseVolCusLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(pPhaseVolCusLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	QHBoxLayout* pPhaseVolCusLayout = new QHBoxLayout;
	pPhaseVolCusLayout->addWidget(pPhaseVolCusCheckBox1);
	pPhaseVolCusLayout->addWidget(pPhaseVolCusLineEdit1);
	pPhaseVolCusLayout->addWidget(pLabel1);
	pPhaseVolCusLayout->addWidget(pPhaseVolCusCheckBox2);
	pPhaseVolCusLayout->addWidget(pPhaseVolCusLineEdit2);
	pPhaseVolCusLayout->addWidget(pLabel2);
	pPhaseVolCusLayout->addStretch(10);

	QVBoxLayout *pPhaseVolMainLayout = new QVBoxLayout;
	pPhaseVolMainLayout->addLayout(pPhaseVolLayout);
	pPhaseVolMainLayout->addLayout(pPhaseVolCusLayout);
	pPhaseVolGroupBox->setLayout(pPhaseVolMainLayout);

	//相电流精度-测试项选择	
	m_pGroupBoxList.append(pPhaseCurGroupBox);
	pPhaseCurGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pPhaseCurLayout = new QGridLayout;
	for (int i = 0; i < oCurList.size(); ++i)
	{
		QSttCheckBox* pCurCheckBox = new QSttCheckBox;
		pCurCheckBox->setFont(*g_pSttGlobalFont);
		strText = oCurList.at(i);
		pCurCheckBox->setText(strText);
		strText = ProcessString(strText);
		strID = _T("I_Rate_") + strText + _T("_Check");
		pCurCheckBox->setObjectName(strID);
		//GetCheckBoxValue(pCurCheckBox,strID);
		pPhaseCurLayout->addWidget(pCurCheckBox,0,i,1,1);
		m_pAllCheckBoxList.append(pCurCheckBox);
		connect(pCurCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}
	QSttCheckBox* pPhaseCurCusCheckBox1 = new QSttCheckBox;
	QSttCheckBox* pPhaseCurCusCheckBox2 = new QSttCheckBox;
	QLineEdit *pPhaseCurCusLineEdit1 = new QLineEdit;
	QLineEdit *pPhaseCurCusLineEdit2 = new QLineEdit;
	pPhaseCurCusCheckBox1->setFont(*g_pSttGlobalFont);
	pPhaseCurCusCheckBox2->setFont(*g_pSttGlobalFont);
	pPhaseCurCusLineEdit1->setFont(*g_pSttGlobalFont);
	pPhaseCurCusLineEdit2->setFont(*g_pSttGlobalFont);
	QLabel *pLabel3 = new QLabel;
	QLabel *pLabel4 = new QLabel;
	strText = _T("%");
	pLabel3->setText(strText);
	pLabel4->setText(strText);
	pLabel3->setFont(*g_pSttGlobalFont);
	pLabel4->setFont(*g_pSttGlobalFont);
	pPhaseCurCusCheckBox1->setObjectName(QString::fromUtf8("I_Custom1_Check"));
	pPhaseCurCusLineEdit1->setObjectName(QString::fromUtf8("I_Custom1"));
	pPhaseCurCusCheckBox2->setObjectName(QString::fromUtf8("I_Custom2_Check"));
	pPhaseCurCusLineEdit2->setObjectName(QString::fromUtf8("I_Custom2"));

// 	GetCheckBoxValue(pPhaseCurCusCheckBox1,_T("I_Custom1_Check"));
// 	GetCheckBoxValue(pPhaseCurCusCheckBox2,_T("I_Custom2_Check"));
// 	GetLineEditValue(pPhaseCurCusLineEdit1,_T("I_Custom1"));
// 	GetLineEditValue(pPhaseCurCusLineEdit2,_T("I_Custom2"));

	UpdateLineEditEnable(pPhaseCurCusCheckBox1,pPhaseCurCusLineEdit1);
	UpdateLineEditEnable(pPhaseCurCusCheckBox2,pPhaseCurCusLineEdit2);


	QHBoxLayout* pPhaseCurCusLayout = new QHBoxLayout;
	pPhaseCurCusLayout->addWidget(pPhaseCurCusCheckBox1);
	pPhaseCurCusLayout->addWidget(pPhaseCurCusLineEdit1);
	pPhaseCurCusLayout->addWidget(pLabel3);

	pPhaseCurCusLayout->addWidget(pPhaseCurCusCheckBox2);
	pPhaseCurCusLayout->addWidget(pPhaseCurCusLineEdit2);
	pPhaseCurCusLayout->addWidget(pLabel4);
	pPhaseCurCusLayout->addStretch(10);
	QVBoxLayout *pPhaseMainLayout = new QVBoxLayout;
	pPhaseMainLayout->addLayout(pPhaseCurLayout);
	pPhaseMainLayout->addLayout(pPhaseCurCusLayout);
	pPhaseCurGroupBox->setLayout(pPhaseMainLayout);

	m_pAllCheckBoxList.append(pPhaseCurCusCheckBox1);
	m_pAllCheckBoxList.append(pPhaseCurCusCheckBox2);
	m_pAllLineEditList.append(pPhaseCurCusLineEdit1);
	m_pAllLineEditList.append(pPhaseCurCusLineEdit2);
	connect(pPhaseCurCusCheckBox1, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pPhaseCurCusCheckBox2, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pPhaseCurCusLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(pPhaseCurCusLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));


	//输出时长
	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setObjectName(QString::fromUtf8("OutputTime"));
	//GetLineEditValue(m_pOutPutTimeEdit,_T("OutputTime"));

	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(m_pOutPutTimeEdit);
	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	m_pEstimateBtn = new QPushButton;
	strText = _T("结果评估");
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	m_pEstimateBtn->setText(strText);
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(pOutPutLabel);
	pHBoxLayout->addWidget(m_pOutPutTimeEdit);
	pHBoxLayout->addStretch(10);
	pHBoxLayout->addWidget(m_pEstimateBtn);
	
// 	QSttCheckBox* pU_Check = new QSttCheckBox;
// 	QSttCheckBox* pI_Check = new QSttCheckBox;
	strText = _T("电流精度-测试项选择");
	pPhaseCurGroupBox->setTitle(strText);
//	pI_Check->setText(strText);
	strText = _T("电压精度-测试项选择");
	pPhaseVolGroupBox->setTitle(strText);

// 	pU_Check->setText(strText);
// 	pU_Check->setObjectName(QString::fromUtf8("U_Check"));
// 	pI_Check->setObjectName(QString::fromUtf8("I_Check"));
// 	pU_Check->setFont(*g_pSttGlobalFont);
// 	pI_Check->setFont(*g_pSttGlobalFont);
// 	GetCheckBoxValue(pU_Check,_T("U_Check"));
// 	GetCheckBoxValue(pI_Check,_T("I_Check"));
// 	m_pAllCheckBoxList.append(pU_Check);
// 	m_pAllCheckBoxList.append(pI_Check);
// 	connect(pU_Check, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
// 	connect(pI_Check, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	
// 	setGroupBoxEnabled(pPhaseVolGroupBox,pU_Check->isChecked());
// 	setGroupBoxEnabled(pPhaseCurGroupBox,pI_Check->isChecked());

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	//pMainLayout->addWidget(pU_Check);
	pMainLayout->addWidget(pPhaseVolGroupBox);
	//pMainLayout->addWidget(pI_Check);
	pMainLayout->addWidget(pPhaseCurGroupBox);
	pMainLayout->addLayout(pHBoxLayout);

	setFocusPolicy(Qt::StrongFocus);
	setLayout(pMainLayout);

	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}


void QSttMacroParaEditViewVolCurAccuracyWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
//  	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
//  	{
//  		QCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
//  		pCheckBox->setDisabled(true);
//  	}
//  	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
//  	{
//  		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
//  		pLineEdit->setDisabled(true);
//  	}

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(true);
	}

	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewVolCurAccuracyWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);

// 	QSttCheckBox* pUCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("U_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[0],pUCheckBox->isChecked());
// 	QSttCheckBox* pICheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("I_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[1],pICheckBox->isChecked());

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(false);
	}

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewVolCurAccuracyWidget::slot_Estimate()
{
	QVolCurErrorEstimateDlg dlg(&m_pVolCurErrorDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewVolCurAccuracyWidget::slot_CheckBoxStateChanged( int )
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	int nGroupBoxIndex = -1;
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pVolCurErrorDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pVolCurErrorDataGroup.SetDataValue(strID,(long)0);
	}
	
// 	if(strID == _T("U_Check"))
// 	{
// 		nGroupBoxIndex = 0;
// 	}
// 	else if (strID == _T("I_Check"))
// 	{
// 		nGroupBoxIndex = 1;
// 	}
// 
// 	if(nGroupBoxIndex != -1)
// 	{
// 		setGroupBoxEnabled(m_pGroupBoxList[nGroupBoxIndex],pCheckBox->isChecked());
// 	}

 	if (strID.contains("U_Custom1_Check") || strID.contains("U_Custom2_Check") ||
 		strID.contains("I_Custom1_Check") || strID.contains("I_Custom2_Check"))  	
 	{
		QLineEdit *pLineEdit = FindLineEditID(m_pAllLineEditList, strID.Left(9));
		UpdateLineEditEnable(pCheckBox,pLineEdit);
   	}
}

QSttCheckBox* QSttMacroParaEditViewVolCurAccuracyWidget::FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID)
{
	for (int i = 0; i < checkBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = checkBoxList.at(i);
		if (pCheckBox->objectName() == strID)
		{
			return pCheckBox;
		}
	}
	return NULL;
}

QLineEdit* QSttMacroParaEditViewVolCurAccuracyWidget::FindLineEditID( const QList<QLineEdit*>& LineEditList, const CString& strID )
{
	for (int i = 0; i < LineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = LineEditList.at(i);
		if (pLineEdit->objectName() == strID)
		{
			return pLineEdit;
		}
	}
	return NULL;
}


BOOL QSttMacroParaEditViewVolCurAccuracyWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (m_pMacroTestValues == NULL)
	{
		m_pMacroTestValues = new CDvmValues;
	}
	long nPhase_Number;
	stt_GetDataValueByID(&m_pVolCurErrorDataGroup, _T("Phase_Number"), nPhase_Number);
	CDvmData *pCurrData = NULL;
	CDvmValue *pDvmValue = NULL;
	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
	
	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD) //通讯命令
 	{
		if (pRptDvmDataset == NULL)
		{
			return FALSE;
		}
		POS pos = pRptDvmDataset->GetHeadPosition();

		while(pos)
		{
			pCurrData = (CDvmData*)pRptDvmDataset->GetNext(pos); 

			if (pCurrData == NULL )
			{
				continue;
			}
			if (pCurrData->m_strID == _T("Ua") || pCurrData->m_strID == _T("Ub") || pCurrData->m_strID == _T("Uc") || pCurrData->m_strID == _T("U0") ||
				pCurrData->m_strID == _T("Ia") || pCurrData->m_strID == _T("Ib") || pCurrData->m_strID == _T("Ic") || pCurrData->m_strID == _T("I0"))
			{
				if (nPhase_Number == 2 && pCurrData->m_strID == _T("Ub"))
				{
					pCurrData->m_strValue = _T("--");
				}
				pDvmValue = new CDvmValue;
				pDvmValue->m_strID = pCurrData->m_strID;
				pDvmValue->m_strValue = pCurrData->m_strValue;
				pDvmValues->AddNewChild(pDvmValue);
			}
		}

		if (m_pMacroTestValues &&m_pMacroTestValues->GetCount() > 0 )
		{
			pDvmValues->AppendCloneEx2(*m_pMacroTestValues);
		}
 	}

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)//电气量
	{
		m_pMacroTestValues->DeleteAll();

		if (pDvmValues == NULL)
		{
			return FALSE;
		}

		POS posValue = pDvmValues->GetHeadPosition();
		while(posValue)
		{
			pCurrData = (CDvmData*)pDvmValues->GetNext(posValue); 
			if (pCurrData == NULL )
			{
				continue;
			}
			if (pCurrData->m_strID == _T("U1") || pCurrData->m_strID == _T("U2") || pCurrData->m_strID == _T("U3") || pCurrData->m_strID == _T("U4") ||
				pCurrData->m_strID == _T("I1") || pCurrData->m_strID == _T("I2") || pCurrData->m_strID == _T("I3") || pCurrData->m_strID == _T("I4"))
			{
				if (nPhase_Number == 2 && pCurrData->m_strID == _T("U2"))
				{
					pCurrData->m_strValue = _T("--");
				}

				pDvmValue = new CDvmValue;
				pDvmValue->m_strID = pCurrData->m_strID;
				pDvmValue->m_strValue = pCurrData->m_strValue;
				m_pMacroTestValues->AddNewChild(pDvmValue);
			}
		}
	}
	return TRUE;
}


void QSttMacroParaEditViewVolCurAccuracyWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(&oDataGroup, strID, strValue);

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_1"));  
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_2"));
		}
		else if (strValue == _T("Din_5") || strValue == _T("2"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_5"));
		}
		else
		{
			oDataGroup.SetDataValue(strID, _T(""));  
		}
	}

	UpdateRemoteBoutData(&oDataGroup);
}

void QSttMacroParaEditViewVolCurAccuracyWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pVolCurErrorDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}


	long nPhase_Number;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhase_Number);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Phase_Number"),nPhase_Number);
}

void QSttMacroParaEditViewVolCurAccuracyWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue));
		m_pVolCurErrorDataGroup.SetDataValue(strID,fValue);
	}
}

void QSttMacroParaEditViewVolCurAccuracyWidget::slot_GroupBoxtoggled( bool )
{
	CString strID;
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender()); 
	if (pGroupBox)
	{	
		strID = pGroupBox->objectName();
		if (pGroupBox->isChecked()) 
		{
			m_pVolCurErrorDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pVolCurErrorDataGroup.SetDataValue(strID,(long)0);
		}
	}
}

void QSttMacroParaEditViewVolCurAccuracyWidget::GetCheckBoxValue(  CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pVolCurErrorDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pCheckBox->setChecked(true);;
	}
	else
	{
		pCheckBox->setChecked(false);;
	}
}

void QSttMacroParaEditViewVolCurAccuracyWidget::GetLineEditValue(  CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pVolCurErrorDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue));
}

void QSttMacroParaEditViewVolCurAccuracyWidget::GetGroupBoxCheckable(  CDataGroup *pParas,QGroupBox * pGroupBox,CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pVolCurErrorDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(true);
	}
	else
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(false);
	}
}

BOOL QSttMacroParaEditViewVolCurAccuracyWidget::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}


	CDataGroup* pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if ((pDataGroup->GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,pDataGroup);
	}

	if (pDataGroup->GetCount()>0)
	{
		pDataGroup->CopyChildren(&m_pVolCurErrorDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewVolCurAccuracyWidget::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();

// 	float fVNom;
// 	if((g_oSystemParas.m_nHasWeek == 1) && (g_oSystemParas.m_nHasAnalog == 0) && (g_oSystemParas.m_nHasDigital == 0))
// 	{
// 		fVNom = g_oSystemParas.m_fVNom ;
// 	}
// 	else
// 	{
// 		fVNom = g_oSystemParas.m_fVNom / SQRT3;
// 	}
	
	m_pVolCurErrorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	m_pVolCurErrorDataGroup.CopyChildren(pParas);
	//SaveParasXml();
}

void QSttMacroParaEditViewVolCurAccuracyWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pVolCurErrorDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pVolCurErrorDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pVolCurErrorDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		if (pGroupBox)
		{
			GetGroupBoxCheckable(&m_pVolCurErrorDataGroup,pGroupBox,pGroupBox->objectName());
		}
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

CString QSttMacroParaEditViewVolCurAccuracyWidget::ProcessString( CString &str )
{
	CString strProcessed = str;
	int index = strProcessed.indexOf('%');
	if (index != -1)
	{
		strProcessed = strProcessed.left(index); 
	}
	if (strProcessed.length() < 3)
	{
		int numZeros = 3 - strProcessed.length();
		strProcessed = QString(numZeros, '0') + strProcessed; // 在前面补足0
	}
	return strProcessed;
}

void QSttMacroParaEditViewVolCurAccuracyWidget::SaveParasXml()
{
	m_pVolCurErrorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pVolCurErrorDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_VolCurAccuracy_Paras.xml");
	m_pVolCurErrorDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

}

void QSttMacroParaEditViewVolCurAccuracyWidget::UpdateLineEditEnable( QSttCheckBox * pCheckBox,QLineEdit * pLineEdit )
{
	if (pCheckBox->isChecked())
	{
		pLineEdit->setEnabled(true);
	}
	else
	{
		pLineEdit->setEnabled(false);
	}
}

//void QSttMacroParaEditViewVolCurAccuracyWidget::setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled)
//{
// 	QList<QCheckBox*> checkboxes = pGroupBox->findChildren<QCheckBox*>();
// 	for (int i = 0; i < checkboxes.size(); ++i) 
// 	{
// 		QCheckBox* checkbox = checkboxes[i];
// 		checkbox->setEnabled(enabled);
// 		
// 		CString strID = checkbox->objectName();
// 		if (strID.contains("U_Custom1_Check") || strID.contains("U_Custom2_Check") ||strID.contains("I_Custom1_Check") || strID.contains("I_Custom2_Check")) 
// 		{
// 			CString lineEditID = strID.left(9);
// 			QLineEdit *pLineEdit = pGroupBox->findChild<QLineEdit *>(lineEditID);
// 
// 	if (enabled)
// 	{
// 				if (pLineEdit)
// 				{
// 					pLineEdit->setEnabled(checkbox->isChecked());
// 				}
// 			}
// 			else
// 		{
// 				pLineEdit->setEnabled(false);
// 			}
// 		}
// 	
// 	}
//}

QVolCurErrorEstimateDlg::QVolCurErrorEstimateDlg(CDataGroup* pParas,QWidget* parent): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 200);

	m_pParas = pParas;
	m_pVolCurErrorLineEdit = NULL;
	InitUI();
}

QVolCurErrorEstimateDlg::~QVolCurErrorEstimateDlg()
{

}

void QVolCurErrorEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("电压电流精度选择");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QLabel *pLabel = new QLabel;
	strText = _T("电压电流误差(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pVolCurErrorLineEdit = new QSttLineEdit;
	m_pVolCurErrorLineEdit->setMinimumWidth(80);
	m_pVolCurErrorLineEdit->setFont(*g_pSttGlobalFont);
	QHBoxLayout* pHLayout = new QHBoxLayout(pGroupBox);
	pHLayout->addStretch();
	pHLayout->addWidget(pLabel);
	pHLayout->addWidget(m_pVolCurErrorLineEdit);
	pHLayout->addStretch();

	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(_T("Val_RelErr"));
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	m_pVolCurErrorLineEdit->setText(QString::number(fValue,'f',3));

	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	QVBoxLayout* pMainVLayout = new QVBoxLayout(this);
	pMainVLayout->addWidget(pGroupBox);
	pMainVLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainVLayout);
	setFocusPolicy(Qt::StrongFocus);

	connect(m_pVolCurErrorLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QVolCurErrorEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Val_RelErr"),m_pVolCurErrorLineEdit->text());
	close();
}

void QVolCurErrorEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QVolCurErrorEstimateDlg::slot_EditFinished()
{
	float fValue = m_pVolCurErrorLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pVolCurErrorLineEdit->setText(QString::number(fValue,'f',3));
}
