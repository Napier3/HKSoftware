#include "SttMacroParaEditViewFreqFactorErrorWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../Controls/SttCheckableGroupBox.h"


QSttMacroParaEditViewFreqFactorErrorWidget::QSttMacroParaEditViewFreqFactorErrorWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pMacroTestValues = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewFreqFactorErrorWidget::~QSttMacroParaEditViewFreqFactorErrorWidget()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear();
}

void QSttMacroParaEditViewFreqFactorErrorWidget::InitUI()
{
	CString strText;
	QSttCheckableGroupBox *pFreqGroupBox = new QSttCheckableGroupBox;
	m_pGroupBoxList.append(pFreqGroupBox);
	pFreqGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pFreqLayout = new QGridLayout(pFreqGroupBox);
	QSttCheckBox* p45hzCheckBox = new QSttCheckBox;
	p45hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("45Hz");
	p45hzCheckBox->setText(strText);
	QSttCheckBox* p47hzCheckBox = new QSttCheckBox;
	p47hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("47Hz");
	p47hzCheckBox->setText(strText);
	QSttCheckBox* p49hzCheckBox = new QSttCheckBox;
	p49hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("49Hz");
	p49hzCheckBox->setText(strText);
	QSttCheckBox* p50hzCheckBox = new QSttCheckBox;
	p50hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("50Hz");
	p50hzCheckBox->setText(strText);
	QSttCheckBox* p51hzCheckBox = new QSttCheckBox;
	p51hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("51Hz");
	p51hzCheckBox->setText(strText);
	QSttCheckBox* p53hzCheckBox = new QSttCheckBox;
	p53hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("53Hz");
	p53hzCheckBox->setText(strText);
	QSttCheckBox* p55hzCheckBox = new QSttCheckBox;
	p55hzCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("55Hz");
	p55hzCheckBox->setText(strText);

	p45hzCheckBox->setObjectName(QString::fromUtf8("Fre_045_Check"));
	p47hzCheckBox->setObjectName(QString::fromUtf8("Fre_047_Check"));
	p49hzCheckBox->setObjectName(QString::fromUtf8("Fre_049_Check"));
	p50hzCheckBox->setObjectName(QString::fromUtf8("Fre_050_Check"));
	p51hzCheckBox->setObjectName(QString::fromUtf8("Fre_051_Check"));
	p53hzCheckBox->setObjectName(QString::fromUtf8("Fre_053_Check"));
	p55hzCheckBox->setObjectName(QString::fromUtf8("Fre_055_Check"));

// 	GetCheckBoxValue(p45hzCheckBox,_T("Fre_045_Check"));
// 	GetCheckBoxValue(p47hzCheckBox,_T("Fre_047_Check"));
// 	GetCheckBoxValue(p49hzCheckBox,_T("Fre_049_Check"));
// 	GetCheckBoxValue(p50hzCheckBox,_T("Fre_050_Check"));
// 	GetCheckBoxValue(p51hzCheckBox,_T("Fre_051_Check"));
// 	GetCheckBoxValue(p53hzCheckBox,_T("Fre_053_Check"));
// 	GetCheckBoxValue(p55hzCheckBox,_T("Fre_055_Check"));

	pFreqLayout->addWidget(p45hzCheckBox,0,0,1,1);
	pFreqLayout->addWidget(p47hzCheckBox,0,1,1,1);
	pFreqLayout->addWidget(p49hzCheckBox,0,2,1,1);
	pFreqLayout->addWidget(p50hzCheckBox,0,3,1,1);
	pFreqLayout->addWidget(p51hzCheckBox,1,0,1,1);
	pFreqLayout->addWidget(p53hzCheckBox,1,1,1,1);
	pFreqLayout->addWidget(p55hzCheckBox,1,2,1,1);

	m_pAllCheckBoxList.append(p45hzCheckBox);
	m_pAllCheckBoxList.append(p47hzCheckBox);
	m_pAllCheckBoxList.append(p49hzCheckBox);
	m_pAllCheckBoxList.append(p50hzCheckBox);
	m_pAllCheckBoxList.append(p51hzCheckBox);
	m_pAllCheckBoxList.append(p53hzCheckBox);
	m_pAllCheckBoxList.append(p55hzCheckBox);
	connect(p45hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p47hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p49hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p50hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p51hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p53hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p55hzCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));

	QSttCheckableGroupBox *pFactorGroupBox = new QSttCheckableGroupBox;
	m_pGroupBoxList.append(pFactorGroupBox);
	pFactorGroupBox->setFont(*g_pSttGlobalFont);
	QGridLayout *pFactorLayout = new QGridLayout(pFactorGroupBox);
	QSttCheckBox* pN90CheckBox = new QSttCheckBox;
	pN90CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("-90°");
	pN90CheckBox->setText(strText);
	QSttCheckBox* pN60CheckBox = new QSttCheckBox;
	pN60CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("-60°");
	pN60CheckBox->setText(strText);
	QSttCheckBox* pN45CheckBox = new QSttCheckBox;
	pN45CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("-45°");
	pN45CheckBox->setText(strText);
	QSttCheckBox* pN30CheckBox = new QSttCheckBox;
	pN30CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("-30°");
	pN30CheckBox->setText(strText);
	QSttCheckBox* pZeroCheckBox = new QSttCheckBox;
	pZeroCheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("0°");
	pZeroCheckBox->setText(strText);
	QSttCheckBox* p90CheckBox = new QSttCheckBox;
	p90CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("90°");
	p90CheckBox->setText(strText);
	QSttCheckBox* p60CheckBox = new QSttCheckBox;
	p60CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("60°");
	p60CheckBox->setText(strText);
	QSttCheckBox* p45CheckBox = new QSttCheckBox;
	p45CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("45°");
	p45CheckBox->setText(strText);
	QSttCheckBox* p30CheckBox = new QSttCheckBox;
	p30CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("30°");
	p30CheckBox->setText(strText);

	pN90CheckBox->setObjectName(QString::fromUtf8("Ang_90_Check"));
	pN60CheckBox->setObjectName(QString::fromUtf8("Ang_60_Check"));
	pN45CheckBox->setObjectName(QString::fromUtf8("Ang_45_Check"));
	pN30CheckBox->setObjectName(QString::fromUtf8("Ang_30_Check"));
	pZeroCheckBox->setObjectName(QString::fromUtf8("Ang0_Check"));
	p90CheckBox->setObjectName(QString::fromUtf8("Ang90_Check"));
	p60CheckBox->setObjectName(QString::fromUtf8("Ang60_Check"));
	p45CheckBox->setObjectName(QString::fromUtf8("Ang45_Check"));
	p30CheckBox->setObjectName(QString::fromUtf8("Ang30_Check"));

// 	GetCheckBoxValue(pN90CheckBox,_T("Ang_90_Check"));
// 	GetCheckBoxValue(pN60CheckBox,_T("Ang_60_Check"));
// 	GetCheckBoxValue(pN45CheckBox,_T("Ang_45_Check"));
// 	GetCheckBoxValue(pN30CheckBox,_T("Ang_30_Check"));
// 	GetCheckBoxValue(pZeroCheckBox,_T("Ang0_Check"));
// 	GetCheckBoxValue(p90CheckBox,_T("Ang90_Check"));
// 	GetCheckBoxValue(p60CheckBox,_T("Ang60_Check"));
// 	GetCheckBoxValue(p45CheckBox,_T("Ang45_Check"));
// 	GetCheckBoxValue(p30CheckBox,_T("Ang30_Check"));

	pFactorLayout->addWidget(pN90CheckBox,0,0,1,1);
	pFactorLayout->addWidget(pN60CheckBox,0,1,1,1);
	pFactorLayout->addWidget(pN45CheckBox,0,2,1,1);
	pFactorLayout->addWidget(pN30CheckBox,0,3,1,1);
	pFactorLayout->addWidget(pZeroCheckBox,0,4,1,1);
	pFactorLayout->addWidget(p90CheckBox,1,0,1,1);
	pFactorLayout->addWidget(p60CheckBox,1,1,1,1);
	pFactorLayout->addWidget(p45CheckBox,1,2,1,1);
	pFactorLayout->addWidget(p30CheckBox,1,3,1,1);

	m_pAllCheckBoxList.append(pN90CheckBox);
	m_pAllCheckBoxList.append(pN60CheckBox);
	m_pAllCheckBoxList.append(pN45CheckBox);
	m_pAllCheckBoxList.append(pN30CheckBox);
	m_pAllCheckBoxList.append(pZeroCheckBox);
	m_pAllCheckBoxList.append(p90CheckBox);
	m_pAllCheckBoxList.append(p60CheckBox);
	m_pAllCheckBoxList.append(p45CheckBox);
	m_pAllCheckBoxList.append(p30CheckBox);
	connect(pN90CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pN60CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pN45CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pN30CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(pZeroCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p90CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p60CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p45CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	connect(p30CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));

	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
	CDvmData* pCurData = (CDvmData*)m_pFreqFactorDataGroup.FindByID(_T("OutputTime"));
	m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	m_pEstimateBtn = new QPushButton;
	strText = _T("结果评估");
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	m_pEstimateBtn->setText(strText);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(pOutPutLabel);
	pHBoxLayout->addWidget(m_pOutPutTimeEdit);
	pHBoxLayout->addStretch(10);
	pHBoxLayout->addWidget(m_pEstimateBtn);


// 	QSttCheckBox* pFreq_Check = new QSttCheckBox;
// 	QSttCheckBox* pFactor_Check = new QSttCheckBox;
	strText = _T("频率基本误差-输入频率选择");
	//pFreq_Check->setText(strText);
	pFreqGroupBox->setTitle(strText);
	strText = _T("功率因数基本误差-功率因素角选择");
	//pFactor_Check->setText(strText);
	pFactorGroupBox->setTitle(strText);
	pFreqGroupBox->setObjectName(_T("Fre_Check"));
	pFactorGroupBox->setObjectName(_T("Ang_Check"));
// 	GetGroupBoxCheckable(pFreqGroupBox,_T("Fre_Check"));
// 	GetGroupBoxCheckable(pFactorGroupBox,_T("Ang_Check"));
	connect(pFreqGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(pFactorGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
// 	pFreq_Check->setObjectName(QString::fromUtf8("Fre_Check"));
// 	pFactor_Check->setObjectName(QString::fromUtf8("Ang_Check"));
// 	pFreq_Check->setFont(*g_pSttGlobalFont);
// 	pFactor_Check->setFont(*g_pSttGlobalFont);
// 	GetCheckBoxValue(pFreq_Check,_T("Fre_Check"));
// 	GetCheckBoxValue(pFactor_Check,_T("Ang_Check"));
// 	m_pAllCheckBoxList.append(pFreq_Check);
// 	m_pAllCheckBoxList.append(pFactor_Check);
// 	connect(pFreq_Check, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
// 	connect(pFactor_Check, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	//setGroupBoxEnabled(pFreqGroupBox,pFreq_Check->isChecked());
	//setGroupBoxEnabled(pFactorGroupBox,pFactor_Check->isChecked());

	
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	//pMainLayout->addWidget(pFreq_Check);
	pMainLayout->addWidget(pFreqGroupBox);
	//pMainLayout->addWidget(pFactor_Check);
	pMainLayout->addWidget(pFactorGroupBox);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));

	OpenBinBoutMapXml();


	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}

void QSttMacroParaEditViewFreqFactorErrorWidget::SaveParasXml()
{
	m_pFreqFactorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pFreqFactorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pFreqFactorDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pFreqFactorDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_FreqFactor_Paras.xml");
	m_pFreqFactorDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}



void QSttMacroParaEditViewFreqFactorErrorWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
// 	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
// 	{
// 		QCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
// 		pCheckBox->setDisabled(true);
// 	}
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

void QSttMacroParaEditViewFreqFactorErrorWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
// 	QSttCheckBox* pUCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Fre_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[0],pUCheckBox->isChecked());
// 	QSttCheckBox* pICheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Ang_Check"));
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

void QSttMacroParaEditViewFreqFactorErrorWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();

	m_pFreqFactorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pFreqFactorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pFreqFactorDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewFreqFactorErrorWidget::GetCheckBoxValue( CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pFreqFactorDataGroup.*/pParas->FindByID(strID);
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

BOOL QSttMacroParaEditViewFreqFactorErrorWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pFreqFactorDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewFreqFactorErrorWidget::slot_Estimate()
{
	QFreqFactorErrorEstimateDlg dlg(&m_pFreqFactorDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewFreqFactorErrorWidget::slot_CheckBoxStateChanged( int )
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
		m_pFreqFactorDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pFreqFactorDataGroup.SetDataValue(strID,(long)0);
	}

// 	if(strID == _T("Fre_Check"))
// 	{
// 		nGroupBoxIndex = 0;
// 	}
// 	else if (strID == _T("Ang_Check"))
// 	{
// 		nGroupBoxIndex = 1;
// 	}
// 
// 	if(nGroupBoxIndex != -1)
// 	{
// 		setGroupBoxEnabled(m_pGroupBoxList[nGroupBoxIndex],pCheckBox->isChecked());
// 	}
}

void QSttMacroParaEditViewFreqFactorErrorWidget::slot_GroupBoxtoggled( bool )
{
	CString strID;
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender()); 
	if (pGroupBox)
	{	
		strID = pGroupBox->objectName();
		if (pGroupBox->isChecked()) 
		{
			m_pFreqFactorDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pFreqFactorDataGroup.SetDataValue(strID,(long)0);
		}
	}
}

void QSttMacroParaEditViewFreqFactorErrorWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pFreqFactorDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewFreqFactorErrorWidget::setGroupBoxEnabled( QGroupBox *pGroupBox, bool enabled )
{
	QList<QWidget *> widgets = pGroupBox->findChildren<QWidget *>();
	QList<QWidget *>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); ++it)
	{
		QWidget *pWidget = *it;
		pWidget->setEnabled(enabled);
	}
}

QSttCheckBox* QSttMacroParaEditViewFreqFactorErrorWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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

void QSttMacroParaEditViewFreqFactorErrorWidget::GetGroupBoxCheckable( CDataGroup *pParas, QGroupBox * pGroupBox,CString strID )
{
	pGroupBox->setCheckable(true);

	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pGroupBox->setChecked(true);
	}
	else
	{
		pGroupBox->setChecked(false);
	}
}

void QSttMacroParaEditViewFreqFactorErrorWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pFreqFactorDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pFreqFactorDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	CDvmData* pCurData = (CDvmData*)m_pFreqFactorDataGroup.FindByID(_T("OutputTime"));
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	m_pOutPutTimeEdit->setText(QString::number(fValue));

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{	
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		if (pGroupBox)
		{
			if (pParas != NULL)
			{
				GetGroupBoxCheckable(pParas,pGroupBox,pGroupBox->objectName());
			}
			else
			{
				GetGroupBoxCheckable(&m_pFreqFactorDataGroup,pGroupBox,pGroupBox->objectName());
			}
		}
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

BOOL QSttMacroParaEditViewFreqFactorErrorWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (m_pMacroTestValues == NULL)
	{
		m_pMacroTestValues = new CDvmValues;
	}

	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
	POS pos = pRptDvmDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CDvmValue *pDvmValue = NULL;

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD) //通讯命令
	{
 		if (pRptDvmDataset == NULL)
 		{
 			return FALSE;
 		}
 		while(pos)
 		{
 			pCurrData = (CDvmData*)pRptDvmDataset->GetNext(pos); 
 
 			if (pCurrData == NULL )
 			{
 				continue;
 			}
 			if (pCurrData->m_strID == _T("F") || pCurrData->m_strID == _T("cos"))
 			{
 				pDvmValue = new CDvmValue;
 				pDvmValue->m_strID = pCurrData->m_strID;
 				pDvmValue->m_strValue = pCurrData->m_strValue;
 				pDvmValues->AddNewChild(pDvmValue);
 			}
 		}
 
 		if (m_pMacroTestValues)
 		{
 			if (m_pMacroTestValues->GetCount() > 0 )
 			{
 				pDvmValues->AppendCloneEx2(*m_pMacroTestValues);
 			}
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
 			if (pCurrData->m_strID == _T("Foutput") || pCurrData->m_strID == _T("cosoutput"))
 			{
 				pDvmValue = new CDvmValue;
 				pDvmValue->m_strID = pCurrData->m_strID;
 				pDvmValue->m_strValue = pCurrData->m_strValue;
				m_pMacroTestValues->AddNewChild(pDvmValue);
 			}
 		}
 	}
	
	return TRUE;
}


void QSttMacroParaEditViewFreqFactorErrorWidget::OpenBinBoutMapXml()
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


void QSttMacroParaEditViewFreqFactorErrorWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pFreqFactorDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}

	long nPhase_Number;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhase_Number);
	m_pFreqFactorDataGroup.SetDataValue(_T("Phase_Number"),nPhase_Number);
}


QFreqFactorErrorEstimateDlg::QFreqFactorErrorEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 250);
	m_pFreqRelLineEdit = NULL;
	m_pPFRelLineEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

QFreqFactorErrorEstimateDlg::~QFreqFactorErrorEstimateDlg()
{

}
void QFreqFactorErrorEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("频率基本误差");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QLabel *pLabel = new QLabel;
	strText = _T("频率基本误差(Hz)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pFreqRelLineEdit = new QSttLineEdit;
	m_pFreqRelLineEdit->setFont(*g_pSttGlobalFont);
	QGroupBox *pGroupBox1 = new QGroupBox;
	strText = _T("功率因数基本误差");
	pGroupBox1->setFont(*g_pSttGlobalFont);
	pGroupBox1->setTitle(strText);
	QLabel *pLabel1 = new QLabel;
	strText = _T("功率因数误差(%)");
	pLabel1->setFont(*g_pSttGlobalFont);
	pLabel1->setText(strText);
	m_pPFRelLineEdit = new QSttLineEdit;
	m_pPFRelLineEdit->setFont(*g_pSttGlobalFont);

	QHBoxLayout* pHLayout = new QHBoxLayout(pGroupBox);
	pHLayout->addStretch();
	pHLayout->addWidget(pLabel);
	pHLayout->addWidget(m_pFreqRelLineEdit);
	pHLayout->addStretch();


	QHBoxLayout* pHLayout1 = new QHBoxLayout(pGroupBox1);
	pHLayout1->addStretch();
	pHLayout1->addWidget(pLabel1);
	pHLayout1->addWidget(m_pPFRelLineEdit);
	pHLayout1->addStretch();

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
	pMainVLayout->addWidget(pGroupBox1);
	pMainVLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainVLayout);
	setFocusPolicy(Qt::StrongFocus);

	m_pFreqRelLineEdit->setObjectName(QString::fromUtf8("Freq_RelErr"));
	m_pPFRelLineEdit->setObjectName(QString::fromUtf8("PF_RelErr"));
	GetLineEditValue(m_pFreqRelLineEdit,_T("Freq_RelErr"));
	GetLineEditValue(m_pPFRelLineEdit,_T("PF_RelErr"));

	connect(m_pFreqRelLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_FreqRelEditFinished()));
	connect(m_pPFRelLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_PFRelEditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QFreqFactorErrorEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Freq_RelErr"),m_pFreqRelLineEdit->text());
	m_pParas->SetDataValue(_T("PF_RelErr"),m_pPFRelLineEdit->text());

	close();
}

void QFreqFactorErrorEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QFreqFactorErrorEstimateDlg::slot_FreqRelEditFinished()
{
	float fValue = m_pFreqRelLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pFreqRelLineEdit->setText(QString::number(fValue,'f',3));
}

void QFreqFactorErrorEstimateDlg::slot_PFRelEditFinished()
{
	float fValue = m_pPFRelLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pPFRelLineEdit->setText(QString::number(fValue,'f',3));
}

void QFreqFactorErrorEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}


